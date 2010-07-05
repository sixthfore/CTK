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
#include <QVBoxLayout>

// CTK includes
#include "ctkVTKImageView.h"
#include "ctkVTKImageView_p.h"
#include "ctkLogger.h"

// VTK includes
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
  this->Renderer = vtkSmartPointer<vtkRenderer>::New();
  this->ImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
  
  this->InteractorStyle = vtkSmartPointer <vtkInteractorStyleImage>::New();
  this->Interactor = vtkSmartPointer <vtkRenderWindowInteractor>::New();
}

//---------------------------------------------------------------------------
void ctkVTKImageViewPrivate::setupRendering()
{
  CTK_P(ctkVTKImageView);

  Q_ASSERT(this->RenderWindow);
  this->RenderWindow->SetAlphaBitPlanes(1);
  this->RenderWindow->SetMultiSamples(0);
  this->RenderWindow->StereoCapableWindowOn();
  this->RenderWindow->AddRenderer(this->Renderer);
  //this->RenderWindow->SetInteractor(this->Interactor);
  this->Interactor = this->RenderWindow->GetInteractor();

  this->ImageViewer->SetRenderWindow(this->RenderWindow);
  this->ImageViewer->SetRenderer(this->Renderer);
  this->ImageViewer->SetupInteractor(this->Interactor);
  //this->Interactor->SetInteractorStyle(this->InteractorStyle);

  this->VTKWidget->SetRenderWindow(this->RenderWindow);
}

//----------------------------------------------------------------------------
CTK_SET_CXX(ctkVTKImageView, bool, setRenderEnabled, RenderEnabled);
CTK_GET_CXX(ctkVTKImageView, bool, renderEnabled, RenderEnabled);

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
  
  d->setupRendering();

}

// --------------------------------------------------------------------------
ctkVTKImageView::~ctkVTKImageView()
{
}

//----------------------------------------------------------------------------
void ctkVTKImageView::scheduleRender()
{
  CTK_D(ctkVTKImageView);

  logger.trace("scheduleRender");
  if (!d->RenderEnabled)
    {
    return;
    }
  if (!d->RenderPending)
    {
    d->RenderPending = true;
    QTimer::singleShot(0, this, SLOT(forceRender()));
    }
}

//----------------------------------------------------------------------------
void ctkVTKImageView::forceRender()
{
  CTK_D(ctkVTKImageView);
  if (!d->RenderEnabled)
    {
    return;
    }
  logger.trace("forceRender");
  d->RenderWindow->Render();
  d->RenderPending = false;
}


//----------------------------------------------------------------------------
void ctkVTKImageView::setImageData(vtkImageData* newImageData)
{
  CTK_D(ctkVTKImageView);

  if (newImageData)
    {
    d->ImageViewer->SetInput(newImageData);
    }

  d->ImageData = newImageData;
}
