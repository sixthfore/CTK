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

// Qt includes
#include <QTimer>
#include <QDebug>

// CTK includes
#include "ctkVTKImageView.h"
#include "ctkVTKImageView_p.h"
#include "ctkLogger.h"

// VTK includes
#include <vtkRenderWindowInteractor.h>
#include <vtkImageViewer2.h>
#include <vtkImageData.h>

// Convenient macro
#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

//--------------------------------------------------------------------------
static ctkLogger logger("org.commontk.visualization.vtk.widgets.ctkVTKImageView");
//--------------------------------------------------------------------------


// --------------------------------------------------------------------------
// ctkVTKImageViewPrivate methods

// --------------------------------------------------------------------------
ctkVTKImageViewPrivate::ctkVTKImageViewPrivate()
{
  this->RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  this->ImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
}

//---------------------------------------------------------------------------
void ctkVTKImageViewPrivate::setupRendering()
{
  CTK_P(ctkVTKImageView);

  Q_ASSERT(this->RenderWindow);
  this->RenderWindow->SetAlphaBitPlanes(1);
  this->RenderWindow->SetMultiSamples(0);
  this->RenderWindow->StereoCapableWindowOn();
  
  this->RenderWindow->GetRenderers()->RemoveAllItems();

  this->VTKWidget->SetRenderWindow(this->RenderWindow);
}

//---------------------------------------------------------------------------
void ctkVTKImageViewPrivate::setupDefaultInteractor()
{
  CTK_P(ctkVTKImageView);
  p->setInteractor(this->RenderWindow->GetInteractor());
}

//---------------------------------------------------------------------------
// ctkVTKImageView methods

// --------------------------------------------------------------------------
ctkVTKImageView::ctkVTKImageView(QWidget* _parent) : Superclass(_parent)
{
  CTK_INIT_PRIVATE(ctkVTKImageView);
  CTK_D(ctkVTKImageView);
  
  d->VTKWidget = new QVTKWidget(this);
  this->setLayout(new QVBoxLayout);
  this->layout()->setMargin(0);
  this->layout()->setSpacing(0);
  this->layout()->addWidget(d->VTKWidget);

  this->setRenderWindowLayout(1, 1);
  d->setupDefaultInteractor();
}

// --------------------------------------------------------------------------
ctkVTKImageView::~ctkVTKImageView()
{
}

//----------------------------------------------------------------------------
void ctkVTKImageView::setImageData(vtkImageData* newImageData)
{
  CTK_D(ctkVTKImageView);

  if (newImageData)
    {
    }

  d->ImageData = newImageData;
}
