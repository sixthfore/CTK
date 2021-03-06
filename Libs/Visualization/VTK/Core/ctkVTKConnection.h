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

#ifndef __ctkVTKConnection_h
#define __ctkVTKConnection_h

// Qt includes
#include <QObject>
#include <QVector>

// CTK includes
#include <ctkPimpl.h>

#include "CTKVisualizationVTKCoreExport.h"

class vtkObject;
class ctkVTKConnectionPrivate;

class CTK_VISUALIZATION_VTK_CORE_EXPORT ctkVTKConnection : public QObject
{
Q_OBJECT

public:
  typedef QObject Superclass;
  explicit ctkVTKConnection(QObject* parent);

  /// 
  virtual void printAdditionalInfo();
  QString shortDescription();
  static QString shortDescription(vtkObject* vtk_obj, unsigned long vtk_event,
    const QObject* qt_obj, QString qt_slot = "");

  /// 
  void SetParameters(vtkObject* vtk_obj, unsigned long vtk_event,
    const QObject* qt_obj, QString qt_slot, float priority = 0.f);

  /// 
  /// Check the validity of the parameters. Parameters must be valid to add 
  /// a connection
  static bool ValidateParameters(vtkObject* vtk_obj, unsigned long vtk_event,
    const QObject* qt_obj, QString qt_slot);

  /// 
  /// Actually do the connection. Parameters must have been set prior to it
  /// Disconnecting (enable = false) removes the connection.
  void setEnabled(bool enable);
  bool isEnabled()const;

  /// 
  /// Temporarilly block any signals/slots. If the event is fired, the slot
  /// won't be called. You can restore the connection by calling SetBlocked
  /// with block = false.
  void setBlocked(bool block);
  bool isBlocked()const;

  /// 
  bool isEqual(vtkObject* vtk_obj, unsigned long vtk_event,
               const QObject* qt_obj, QString qt_slot)const;

  /// 
  /// Return a string uniquely identifying the connection within the current process
  QString id()const;
public slots:
  ///
  /// Safe deletion
  void deleteConnection();

signals:
  /// 
  /// The qt signal emited by the VTK Callback
  /// The signal corresponding to the slot will be emited
  void emitExecute(vtkObject* caller, vtkObject* call_data);

  /// Note: even if the signal has a signature with 4 args, you can
  /// connect it to a slot with less arguments as long as the types of the 
  /// argument are matching:
  /// connect(obj1,SIGNAL(signalFunc(A,B,C,D)),obj2,SLOT(slotFunc(A)));
  void emitExecute(vtkObject* caller, void* call_data, unsigned long vtk_event, void* client_data);
protected:
  virtual ~ctkVTKConnection();

private:
  CTK_DECLARE_PRIVATE(ctkVTKConnection);
};

#endif
