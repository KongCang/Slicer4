#ifndef __vtkLiverAblationMRMLManager_h
#define __vtkLiverAblationMRMLManager_h

#include "vtkSlicerModuleLogic.h"
#include "vtkLiverAblation.h"
#include <vtkSetGet.h>

class vtkMRMLScene;
class vtkMRMLVolumeNode;
class vtkMRMLFiducialListNode;
class vtkMRMLModelNode;

#include <vtksys/stl/string>
#include <vtksys/stl/map>
#include <vtksys/stl/vector>

class VTK_LIVERABLATION_EXPORT vtkLiverAblationMRMLManager : 
  public vtkObject
{
public:
  static vtkLiverAblationMRMLManager *New();
  vtkTypeMacro(vtkLiverAblationMRMLManager,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  // the current mrml scene
  vtkSetObjectMacro(MRMLScene, vtkMRMLScene);
  vtkGetObjectMacro(MRMLScene, vtkMRMLScene);

  // functions for accessing volumes
  virtual int GetVolumeNumberOfChoices();
  virtual vtkIdType GetVolumeNthID(int n);
  virtual const char* GetVolumeName(vtkIdType volumeID);

  // functions for accessing models
  virtual int GetModelNumberOfChoices();
  virtual vtkIdType GetModelNthID(int n);
  virtual const char* GetModelName(vtkIdType volumeID);

  //functions for accessing fiducial marks
  virtual int GetFiducialNumberOfChoices();
  virtual vtkIdType GetFiducialNthID(int n);
  virtual const char* GetFiducialName(vtkIdType volumeID);

  // this will be be passed along by the logic node 
  virtual void ProcessMRMLEvents ( vtkObject *caller, unsigned long event,
                                   void *callData );

  // convenience functions for managing MRML nodes 
  virtual vtkMRMLVolumeNode*              GetVolumeNode(vtkIdType);
  virtual vtkMRMLFiducialListNode*        GetFiducialNode(vtkIdType);
  virtual vtkMRMLModelNode*               GetModelNode(vtkIdType);

  //
  // this functions registers all of the MRML nodes needed by this
  // class with the MRML scene
  //
  virtual void      RegisterMRMLNodesWithScene();

private:
  vtkLiverAblationMRMLManager();
  ~vtkLiverAblationMRMLManager();
  vtkLiverAblationMRMLManager(const vtkLiverAblationMRMLManager&);
  void operator=(const vtkLiverAblationMRMLManager&);

  virtual vtkIdType                       GetNewVTKNodeID();

  //
  // convienience functions for managing ID mapping (mrml id <-> vtkIdType)
  //
  virtual vtkIdType    MapMRMLNodeIDToVTKNodeID(const char* MRMLNodeID);
  virtual const char*  MapVTKNodeIDToMRMLNodeID(vtkIdType vtkID);

  virtual void         IDMapInsertPair(vtkIdType vtkID, 
                                       const char* MRMLNodeID);
  virtual void         IDMapRemovePair(vtkIdType vtkID);
  virtual void         IDMapRemovePair(const char* MRMLNodeID);

  virtual int          IDMapContainsMRMLNodeID(const char* MRMLNodeID);
  virtual int          IDMapContainsVTKNodeID(vtkIdType id);

  vtkMRMLScene*   MRMLScene;

  //
  // The api of this class exposes vtkIdType ids for tree nodes and
  // volumes.  This esentially hides the mrml ids from client code and
  // insulates the client from changes in the slicer mrml id
  // mechanism.
  //

  vtkIdType NextVTKNodeID;
  //BTX
  typedef vtksys_stl::map<vtkIdType, vtksys_stl::string>  VTKToMRMLMapType;
  VTKToMRMLMapType                                VTKNodeIDToMRMLNodeIDMap;
  typedef vtksys_stl::map<vtksys_stl::string, vtkIdType>  MRMLToVTKMapType;
  MRMLToVTKMapType                                MRMLNodeIDToVTKNodeIDMap;
  //ETX
};

#endif
