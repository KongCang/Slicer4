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

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

#ifndef __qSlicerCoreModule_h
#define __qSlicerCoreModule_h

// CTK includes
#include <ctkPimpl.h>

// SlicerQt includes
#include "qSlicerAbstractModule.h"

#include "qSlicerBaseQTCoreModulesExport.h"

class qSlicerCoreModulePrivate;

class Q_SLICER_BASE_QTCOREMODULES_EXPORT qSlicerCoreModule : public qSlicerAbstractModule
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModule Superclass;
  qSlicerCoreModule(QObject *parent=0);
  virtual ~qSlicerCoreModule();

protected:
  virtual void setup();

protected:
  QScopedPointer<qSlicerCoreModulePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerCoreModule);
  Q_DISABLE_COPY(qSlicerCoreModule);
};

#endif
