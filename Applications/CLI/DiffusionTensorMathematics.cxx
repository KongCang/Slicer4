#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#ifdef __BORLANDC__
#define ITK_LEAN_AND_MEAN
#endif

#include <iostream>
#include <algorithm>
#include <string>

#include "itkPluginFilterWatcher.h"
#include "itkPluginUtilities.h"

#include "vtkDiffusionTensorMathematicsSimple.h"

#include "vtkNRRDReader.h"
#include "vtkNRRDWriter.h"
#include "vtkImageData.h"
#include "DiffusionTensorMathematicsCLP.h"


int main( int argc, char * argv[] )
{

  PARSE_ARGS;

  vtkNRRDReader *reader = vtkNRRDReader::New();
  reader->SetFileName(inputVolume.c_str());
  reader->Update();
  
  if ( reader->GetOutput()->GetPointData()->GetTensors() == NULL )
    {
    std::cerr << argv[0] << ": No tensor data" << std::endl;
    return EXIT_FAILURE;
    }
  vtkDiffusionTensorMathematicsSimple *math = vtkDiffusionTensorMathematicsSimple::New();

  math->SetInput(0, reader->GetOutput());
  math->SetInput(1, reader->GetOutput());


  if (operation == std::string("Trace"))
    {
    math->SetOperationToTrace();
    }
  else if(operation == std::string("Determinant"))
    {
    math->SetOperationToDeterminant();
    }
  else if (operation == std::string("RelativeAnisotropy"))
    {
    math->SetOperationToRelativeAnisotropy();
    }
  else if (operation == std::string("FractionalAnisotropy"))
    {
    math->SetOperationToFractionalAnisotropy();
    }
  else if (operation == std::string("Mode"))
    {
    math->SetOperationToMode();
    }
  else if (operation == std::string("LinearMeasurement") || operation == std::string("LinearMeasure"))
    {
    math->SetOperationToLinearMeasure();
    }
  else if (operation == std::string("PlanarMeasurement") || operation == std::string("PlanarMeasure"))
    {
    math->SetOperationToPlanarMeasure();
    }
  else if (operation == std::string("SphericalMeasurement") || operation == std::string("SphericalMeasure"))
    {
    math->SetOperationToSphericalMeasure();
    }
  else if (operation == std::string("MinEigenvalue"))
    {
    math->SetOperationToMinEigenvalue();
    }
  else if (operation == std::string("MiddleEigenvalue"))
    {
    math->SetOperationToMiddleEigenvalue();
    }
  else if (operation == std::string("MaxEigenvalue"))
    {
    math->SetOperationToMaxEigenvalue();
    }
  else if (operation == std::string("ColorByOrientation"))
    {
    math->SetOperationToColorByOrientation();
    }
  else if (operation == std::string("ColorByMode"))
    {
    math->SetOperationToColorByMode();
    }
  else if (operation == std::string("MaxEigenvalueProjectionX"))
    {
    math->SetOperationToMaxEigenvalueProjectionX();
    }
  else if (operation == std::string("MaxEigenvalueProjectionY"))
    {
    math->SetOperationToMaxEigenvalueProjectionY();
    }
  else if (operation == std::string("MaxEigenvalueProjectioZ"))
    {
    math->SetOperationToMaxEigenvalueProjectionZ();
    }
  else if (operation == std::string("RAIMaxEigenvecX"))
    {
    math->SetOperationToRAIMaxEigenvecX();
    }
  else if (operation == std::string("RAIMaxEigenvecY"))
    {
    math->SetOperationToRAIMaxEigenvecY();
    }
  else if (operation == std::string("RAIMaxEigenvecZ"))
    {
    math->SetOperationToRAIMaxEigenvecZ();
    }
  else if (operation == std::string("D11"))
    {
    math->SetOperationToD11();
    }
  else if (operation == std::string("D22"))
    {
    math->SetOperationToD22();
    }
  else if (operation == std::string("D33"))
    {
    math->SetOperationToD33();
    }
  else if (operation == std::string("ParallelDiffusivity"))
    {
    math->SetOperationToParallelDiffusivity();
    }
  else if (operation == std::string("PerpendicularDffusivity"))
    {
    math->SetOperationToPerpendicularDiffusivity();
    }
  else
    {
    std::cerr << argv[0] <<": Operation "<< operation<< "not supported"<< std::endl;
    return EXIT_FAILURE;
    }            

  math->Update();

  //Save result
  vtkNRRDWriter *writer = vtkNRRDWriter::New();
  writer->SetInput(math->GetOutput());
  writer->SetFileName( outputScalar.c_str() );
  writer->UseCompressionOn();
  //Compute IjkToRas (used by Writer)
  reader->GetRasToIjkMatrix()->Invert();
  writer->SetIJKToRASMatrix( reader->GetRasToIjkMatrix() );
  writer->Write();

  reader->Delete();
  writer->Delete();
  math->Delete();

  return EXIT_SUCCESS;
}
