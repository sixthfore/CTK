/*=========================================================================

  Library:   CTK
 
  Copyright (c) 2010  Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 
=========================================================================*/

#ifndef __ctkVTKRenderView_p_h
#define __ctkVTKRenderView_p_h

// Qt includes
#include <QObject>

// CTK includes
#include <ctkPimpl.h>
#include <ctkVTKObject.h>
#include "ctkVTKRenderView.h"

// VTK includes
#include <QVTKWidget.h>
#include <vtkAxesActor.h>
#include <vtkCornerAnnotation.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkWeakPointer.h>

class vtkRenderWindowInteractor;

//-----------------------------------------------------------------------------
class ctkVTKRenderViewPrivate : public QObject,
                                public ctkPrivate<ctkVTKRenderView>
{
  Q_OBJECT
  CTK_DECLARE_PUBLIC(ctkVTKRenderView);
public:
  ctkVTKRenderViewPrivate();

  /// Convenient setup methods
  void setupCornerAnnotation();
  void setupRendering();
  void setupDefaultInteractor();

  QVTKWidget*                                   VTKWidget;
  vtkSmartPointer<vtkRenderer>                  Renderer;
  vtkSmartPointer<vtkRenderWindow>              RenderWindow;
  bool                                          RenderPending;
  bool                                          RenderEnabled;
  
  vtkSmartPointer<vtkAxesActor>                 Axes;
  vtkSmartPointer<vtkOrientationMarkerWidget>   Orientation;
  vtkSmartPointer<vtkCornerAnnotation>          CornerAnnotation;

  vtkWeakPointer<vtkRenderWindowInteractor>     CurrentInteractor;

};

#endif
