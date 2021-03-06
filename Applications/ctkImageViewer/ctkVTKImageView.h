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

#ifndef __ctkVTKImageView_h
#define __ctkVTKImageView_h

// Qt includes
#include <QWidget>

// CTK includes
#include <ctkPimpl.h>

#include "CTKVisualizationVTKWidgetsExport.h"

class ctkVTKImageViewPrivate;
class vtkRenderWindow;
class vtkImageData;

class CTK_VISUALIZATION_VTK_WIDGETS_EXPORT ctkVTKImageView : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(bool renderEnabled READ renderEnabled WRITE setRenderEnabled)

public:
  /// Constructors
  typedef QWidget   Superclass;
  explicit ctkVTKImageView(QWidget* parent = 0);
  virtual ~ctkVTKImageView();

  /// If a render has already been scheduled, this called is a no-op
  void scheduleRender();

public slots:

  /// Force a render even if a render is already ocurring
  void forceRender();


public:

  /// Set image data
  void setImageData(vtkImageData* newImageData);
 
 /// Return if rendering is enabled
  bool renderEnabled() const;

  /// Enable/Disable rendering
  void setRenderEnabled(bool value);

 
private:
  CTK_DECLARE_PRIVATE(ctkVTKImageView);
}; 

#endif
