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

#ifndef __ctkVTKImageView_p_h
#define __ctkVTKImageView_p_h

// Qt includes
#include <QObject>
#include <QColor>
#include <QList>
#include <QSharedPointer>

// CTK includes
#include <ctkPimpl.h>
#include <ctkVTKObject.h>
#include "ctkVTKImageView.h"

// VTK includes
#include <QVTKWidget.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkWeakPointer.h>
#include <vtkImageViewer2.h>


class vtkRenderWindowInteractor;


//-----------------------------------------------------------------------------
class ctkVTKImageViewPrivate : public QObject,
                               public ctkPrivate<ctkVTKImageView>
{
  Q_OBJECT
  CTK_DECLARE_PUBLIC(ctkVTKImageView);
public:
  ctkVTKImageViewPrivate();

  /// Convenient setup methods
  void setupRendering();

  QVTKWidget*                                   VTKWidget;
  vtkSmartPointer<vtkRenderWindow>              RenderWindow;
  vtkSmartPointer<vtkImageViewer2>              ImageViewer;

  vtkWeakPointer<vtkImageData>                  ImageData;
};

#endif
