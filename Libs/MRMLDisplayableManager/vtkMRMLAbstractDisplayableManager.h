/*==============================================================================

  Program: 3D Slicer

  Copyright (c) 2010 Kitware Inc.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

/// Superclass for displayable manager classes.
/// 
/// A displayable manager class is responsible to represent a
/// MRMLDisplayable node in a renderer.
/// 


#ifndef __vtkMRMLAbstractDisplayableManager_h
#define __vtkMRMLAbstractDisplayableManager_h

// MRMLLogic includes
#include "vtkMRMLAbstractLogic.h"

#include "vtkMRMLDisplayableManagerWin32Header.h"

class vtkMRMLInteractionNode;
class vtkMRMLSelectionNode;
class vtkMRMLDisplayableManagerGroup;
class vtkMRMLNode;
class vtkMRMLScene;
class vtkRenderer;
class vtkRenderWindowInteractor;

class VTK_MRML_DISPLAYABLEMANAGER_EXPORT vtkMRMLAbstractDisplayableManager : public vtkMRMLAbstractLogic 
{
public:
  
  static vtkMRMLAbstractDisplayableManager *New();
  void PrintSelf(ostream& os, vtkIndent indent);
  vtkTypeRevisionMacro(vtkMRMLAbstractDisplayableManager, vtkMRMLAbstractLogic);

  ///
  /// Return True if the DisplayableManager has already been initialized
  bool IsInitialized();

  ///
  /// Return True if Create() method has been invoked
  /// \sa CreateIfPossible() Create()
  bool IsCreated();

  ///
  /// Get Renderer
  vtkRenderer* GetRenderer();

  ///
  /// Convenient method to get the WindowInteractor associated with the Renderer
  vtkRenderWindowInteractor* GetInteractor();

  /// Convenient method to get the current InteractionNode
  vtkMRMLInteractionNode* GetInteractionNode();

  /// Convenient method to get the current SelectionNode
  vtkMRMLSelectionNode* GetSelectionNode();

protected:

  vtkMRMLAbstractDisplayableManager();
  virtual ~vtkMRMLAbstractDisplayableManager();

  ///
  /// Get MRML Displayable Node
  vtkMRMLNode * GetMRMLDisplayableNode();

  //BTX
  /// Access to Initialize, SetMRMLDisplayableNode and CreateIfPossible methods
  friend class vtkMRMLDisplayableManagerGroup;
  //ETX

  /// Set Renderer and Interactor
  /// No-op if already initialized.
  /// Called by vtkMRMLDisplayableManagerGroup
  /// \sa IsInitialized
  void Initialize(vtkMRMLDisplayableManagerGroup * group, vtkRenderer* newRenderer);

  /// Called by Initialize();
  /// Sub-class could overload that function and perform additional initialization steps
  /// \note Initialization occurs before the MRMLDisplayableNode is set and observed
  /// \warning That function should NOT be used directly !
  /// \sa Initialize
  virtual void AdditionnalInitializeStep(){}

  virtual void ProcessMRMLEvents(vtkObject* caller, unsigned long event, void * callData);

  /// Called by SetMRMLScene - Used to initialize the Scene
  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);

  /// Could be overloaded in DisplayableManager subclass
  virtual void OnMRMLDisplayableNodeModifiedEvent(vtkObject* vtkNotUsed(caller)){}

  /// \brief Allow to specify additonal events that the DisplayableNode will observe
  /// \warning Should be called within AdditionnalInitializeStep() method
  /// \sa AdditionnalInitializeStep()
  void AddMRMLDisplayableManagerEvent(int eventId);

  /// Set MRML DisplayableNode
  /// Called by vtkMRMLDisplayableManagerFactory
  void SetAndObserveMRMLDisplayableNode(vtkMRMLNode * newMRMLDisplayableNode);

  /// Get associated DisplayableManager group
  vtkMRMLDisplayableManagerGroup * GetDisplayableManagerGroup();

  /// Invoke Create() and set Created flag to True
  /// A no-op if IsCreated() return True
  void CreateIfPossible();

  /// Called after a valid MRML DisplayableNode is set
  /// \note GetRenderer() and GetMRMLDisplayableNode() will return valid object
  virtual void Create(){}

  /// Remove MRML observers
  virtual void RemoveMRMLObservers();

  /// Specify if UodateFromMRML() should be called
  /// \sa UpdateFromMRML()
  void SetUpdateFromMRMLRequested(bool requested);

  /// Called from RequestRender method if UpdateFromMRMLRequested is true
  /// \sa RequestRender() SetUpdateFromMRMLRequested()
  virtual void UpdateFromMRML(){}

  /// Invoke vtkCommand::UpdateEvent and then call
  /// vtkMRMLThreeDViewDisplayableManagerFactory::RequestRender() which will also
  /// invoke vtkCommand::UpdateEvent.
  /// An observer can then listen for that event and "compress" the different Render requests
  /// to efficiently call RenderWindow->Render()
  void RequestRender();

  /// Usually used inside AdditionnalInitializeStep()
  /// Allows to add observer to the current interactor style that will call the
  /// virtual method OnInteractorStyleEvent accordingly.
  /// \sa AdditionnalInitializeStep RemoveInteractorStyleObservableEvent
  void AddInteractorStyleObservableEvent(int eventid);

  /// \sa AddInteractorStyleObservableEvent
  void RemoveInteractorStyleObservableEvent(int eventid);

  /// Called after interactor style event specified using AddInteractorStyleObservableEvent
  /// are invoked.
  /// \note The following events are observed by default:
  /// <ul>
  ///   <li>vtkCommand::LeftButtonPressEvent</li>
  ///   <li>vtkCommand::LeftButtonReleaseEvent</li>
  ///   <li>vtkCommand::RightButtonPressEvent</li>
  ///   <li>vtkCommand::RightButtonReleaseEvent</li>
  ///   <li>vtkCommand::MiddleButtonPressEvent</li>
  ///   <li>vtkCommand::MiddleButtonReleaseEvent</li>
  ///   <li>vtkCommand::MouseWheelBackwardEvent</li>
  ///   <li>vtkCommand::MouseWheelForwardEvent</li>
  /// </ul>
  /// \sa AddInteractorStyleObservableEvent RemoveInteractorStyleObservableEvent
  virtual void OnInteractorStyleEvent(int eventid);
  
private:

  vtkMRMLAbstractDisplayableManager(const vtkMRMLAbstractDisplayableManager&); // Not implemented
  void operator=(const vtkMRMLAbstractDisplayableManager&);                    // Not implemented

  //BTX
  class vtkInternal;
  vtkInternal* Internal;
  friend class vtkInternal; // For access from the callback function
  //ETX
};

#endif

