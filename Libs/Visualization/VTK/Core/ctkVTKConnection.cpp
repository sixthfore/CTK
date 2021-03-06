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
#include <QDebug>
#include <QRegExp>
#include <QString>
#include <QTextStream>

// CTK includes
#include "ctkVTKConnection.h"

// VTK includes
#include <vtkObject.h>
#include <vtkSmartPointer.h>
#include <vtkCallbackCommand.h>

//-----------------------------------------------------------------------------
QString convertPointerToString(void* pointer)
{
  QString pointerAsString;
  QTextStream(&pointerAsString) << pointer;
  return pointerAsString;
}

//-----------------------------------------------------------------------------
class ctkVTKConnectionPrivate: public ctkPrivate<ctkVTKConnection>
{
public:
  enum
    {
    ARG_UNKNOWN = 0,
    ARG_VTKOBJECT_AND_VTKOBJECT,
    ARG_VTKOBJECT_VOID_ULONG_VOID
    };

  typedef ctkVTKConnectionPrivate Self;
  ctkVTKConnectionPrivate();
  ~ctkVTKConnectionPrivate();

  void connect();
  void disconnect();

  /// 
  /// VTK Callback
  static void DoCallback(vtkObject* vtk_obj, unsigned long event,
                         void* client_data, void* call_data);

  /// 
  /// Called by 'DoCallback' to emit signal
  void Execute(vtkObject* vtk_obj, unsigned long vtk_event, void* client_data, void* call_data);

  vtkSmartPointer<vtkCallbackCommand> Callback;
  vtkObject*                          VTKObject;
  const QObject*                      QtObject;
  unsigned long                       VTKEvent;
  QString                             QtSlot;
  float                               Priority;
  int                                 SlotType;
  bool                                Connected;
  bool                                Blocked;
  QString                             Id;
  bool                                AboutToBeDeleted;
};

//-----------------------------------------------------------------------------
// ctkVTKConnectionPrivate methods

//-----------------------------------------------------------------------------
ctkVTKConnectionPrivate::ctkVTKConnectionPrivate()
{
  this->Callback    = vtkSmartPointer<vtkCallbackCommand>::New();
  this->Callback->SetCallback(ctkVTKConnectionPrivate::DoCallback);
  this->Callback->SetClientData(this);
  this->VTKObject   = 0;
  this->QtObject    = 0;
  this->VTKEvent    = vtkCommand::NoEvent;
  this->Priority    = 0.0;
  this->SlotType    = ARG_UNKNOWN;
  this->Connected   = false;
  this->Blocked     = false;
  this->Id          = convertPointerToString(this);
  this->AboutToBeDeleted = false;
}

//-----------------------------------------------------------------------------
ctkVTKConnectionPrivate::~ctkVTKConnectionPrivate()
{
  /*
  if(this->VTKObject && this->Connected)
    {
    this->VTKObject->RemoveObserver(this->Callback);
    //Qt takes care of disconnecting slots
    }
  */

}

//-----------------------------------------------------------------------------
void ctkVTKConnectionPrivate::connect()
{
  CTK_P(ctkVTKConnection);
  
  if (this->Connected) 
    {
    qDebug() << "ctkVTKConnection already connected.";
    return; 
    }

  switch (this->SlotType)
    {
    case ctkVTKConnectionPrivate::ARG_VTKOBJECT_AND_VTKOBJECT:
      QObject::connect(p, SIGNAL(emitExecute(vtkObject*, vtkObject*)),
                       this->QtObject, this->QtSlot.toLatin1().data());
      break;
    case ctkVTKConnectionPrivate::ARG_VTKOBJECT_VOID_ULONG_VOID:
      QObject::connect(p, SIGNAL(emitExecute(vtkObject*, void*, unsigned long, void*)),
                       this->QtObject, this->QtSlot.toLatin1().data());
      break;
    default:
      Q_ASSERT(false);
      qCritical() << "Failed to connect - "
                  << "The slot (" << this->QtSlot <<  ") owned by "
                  << "QObject(" << this->QtObject->objectName() << ")"
                  << " seems to have a wrong signature.";
      break;
    }

  // Make a connection between this and the vtk object
  this->VTKObject->AddObserver(this->VTKEvent, this->Callback, this->Priority);

  // If necessary, observe vtk DeleteEvent
  if(this->VTKEvent != vtkCommand::DeleteEvent)
    {
    this->VTKObject->AddObserver(vtkCommand::DeleteEvent, this->Callback);
    }

  // Remove itself from its parent when vtkObject is deleted
  QObject::connect(this->QtObject, SIGNAL(destroyed(QObject*)), 
                   p, SLOT(deleteConnection()));

  this->Connected = true;
}

//-----------------------------------------------------------------------------
void ctkVTKConnectionPrivate::disconnect()
{
  CTK_P(ctkVTKConnection);
  
  if (!this->Connected) 
    { 
    Q_ASSERT(this->Connected);
    return; 
    }

  this->VTKObject->RemoveObserver(this->Callback);

  switch (this->SlotType)
    {
    case ctkVTKConnectionPrivate::ARG_VTKOBJECT_AND_VTKOBJECT:
      QObject::disconnect(p, SIGNAL(emitExecute(vtkObject*, vtkObject*)),
                          this->QtObject,this->QtSlot.toLatin1().data());
      break;
    case ctkVTKConnectionPrivate::ARG_VTKOBJECT_VOID_ULONG_VOID:
      QObject::disconnect(p, SIGNAL(emitExecute(vtkObject*, void*, unsigned long, void*)),
                          this->QtObject, this->QtSlot.toLatin1().data());
      break;
    default:
      Q_ASSERT(false);
      qCritical() << "Failed to disconnect - "
                  << "The slot (" << this->QtSlot <<  ") owned by "
                  << "QObject(" << this->QtObject->objectName() << ")"
                  << " seems to have a wrong signature.";
      break;
    }

  QObject::disconnect(this->QtObject, SIGNAL(destroyed(QObject*)),
                      p, SLOT(deleteConnection()));

  this->Connected = false;
}

//-----------------------------------------------------------------------------
// ctkVTKConnection methods

//-----------------------------------------------------------------------------
ctkVTKConnection::ctkVTKConnection(QObject* _parent):
  Superclass(_parent)
{
  CTK_INIT_PRIVATE(ctkVTKConnection);
}

//-----------------------------------------------------------------------------
ctkVTKConnection::~ctkVTKConnection()
{
  this->setEnabled(false);
}

//-----------------------------------------------------------------------------
CTK_GET_CXX(ctkVTKConnection, QString, id, Id);

//-----------------------------------------------------------------------------
void ctkVTKConnection::printAdditionalInfo()
{
  this->Superclass::dumpObjectInfo();

  CTK_D(ctkVTKConnection);
  
  qDebug() << "ctkVTKConnection:" << this << endl
           << "Id:" << d->Id << endl
           << " VTKObject:" << d->VTKObject->GetClassName()
             << "(" << d->VTKObject << ")" << endl
           << " QtObject:" << d->QtObject << endl
           << " VTKEvent:" << d->VTKEvent << endl
           << " QtSlot:" << d->QtSlot << endl
           << " SlotType:" << d->SlotType << endl
           << " Priority:" << d->Priority << endl
           << " Connected:" << d->Connected << endl
           << " Blocked:" << d->Blocked;
}

//-----------------------------------------------------------------------------
QString ctkVTKConnection::shortDescription()
{
  CTK_D(ctkVTKConnection);
  
  return Self::shortDescription(d->VTKObject, d->VTKEvent, d->QtObject, d->QtSlot);
}

//-----------------------------------------------------------------------------
QString ctkVTKConnection::shortDescription(vtkObject* vtk_obj, unsigned long vtk_event,
    const QObject* qt_obj, QString qt_slot)
{
  QString ret;
  QTextStream ts( &ret );
  ts << (vtk_obj ? vtk_obj->GetClassName() : "NULL") << " "
     << vtk_event << " " << qt_obj << " " << qt_slot;
  return ret;
}

//-----------------------------------------------------------------------------
bool ctkVTKConnection::ValidateParameters(vtkObject* vtk_obj, unsigned long vtk_event,
                                        const QObject* qt_obj, QString qt_slot)
{
  Q_UNUSED(vtk_event);
  if (!vtk_obj)
    {
    return false;
    }
  if (!qt_obj)
    {
    return false;
    }
  if (qt_slot.isEmpty())
    {
    return false;
    }
  return true;
}

//-----------------------------------------------------------------------------
void ctkVTKConnection::SetParameters(vtkObject* vtk_obj, unsigned long vtk_event,
  const QObject* qt_obj, QString qt_slot, float priority)
{
  CTK_D(ctkVTKConnection);
  
  if (!Self::ValidateParameters(vtk_obj, vtk_event, qt_obj, qt_slot)) 
    { 
    return; 
    }

  d->VTKObject = vtk_obj;
  d->QtObject = qt_obj;
  d->VTKEvent = vtk_event;
  d->QtSlot = qt_slot;
  d->Priority = priority;

  if (qt_slot.contains(QRegExp(QString("\\( ?vtkObject ?\\* ?, ?vtkObject ?\\* ?\\)"))))
    {
    d->SlotType = ctkVTKConnectionPrivate::ARG_VTKOBJECT_AND_VTKOBJECT;
    }
  else
    {
    d->SlotType = ctkVTKConnectionPrivate::ARG_VTKOBJECT_VOID_ULONG_VOID;
    }
}

//-----------------------------------------------------------------------------
void ctkVTKConnection::setEnabled(bool enable)
{
  CTK_D(ctkVTKConnection);
  
  if (d->Connected == enable)
    {
    return;
    }

  if (enable)
    {
    d->connect();
    }
  else
    {
    d->disconnect();
    }
}

//-----------------------------------------------------------------------------
bool ctkVTKConnection::isEnabled()const
{
  CTK_D(const ctkVTKConnection);
  return d->Connected;
}

//-----------------------------------------------------------------------------
void ctkVTKConnection::setBlocked(bool block)
{
  CTK_D(ctkVTKConnection);
  d->Blocked = block;
}

//-----------------------------------------------------------------------------
bool ctkVTKConnection::isBlocked()const
{
  CTK_D(const ctkVTKConnection);
  return d->Blocked;
}

//-----------------------------------------------------------------------------
bool ctkVTKConnection::isEqual(vtkObject* vtk_obj, unsigned long vtk_event,
    const QObject* qt_obj, QString qt_slot)const
{
  CTK_D(const ctkVTKConnection);
  
  if (d->VTKObject != vtk_obj)
    {
    return false;
    }
  if (vtk_event != vtkCommand::NoEvent && d->VTKEvent != vtk_event)
    {
    return false;
    }
  if (qt_obj && d->QtObject != qt_obj)
    {
    return false;
    }
  if (!qt_slot.isEmpty() && 
      (QString(d->QtSlot).remove(' ').compare(
        QString(qt_slot).remove(' ')) != 0))
    {
    return false;
    }
  return true;
}

//-----------------------------------------------------------------------------
void ctkVTKConnectionPrivate::DoCallback(vtkObject* vtk_obj, unsigned long event,
                                 void* client_data, void* call_data)
{
  ctkVTKConnectionPrivate* conn = static_cast<ctkVTKConnectionPrivate*>(client_data);
  Q_ASSERT(conn);
  conn->Execute(vtk_obj, event, client_data, call_data);
}

//-----------------------------------------------------------------------------
// callback from VTK to emit signal
void ctkVTKConnectionPrivate::Execute(vtkObject* vtk_obj, unsigned long vtk_event,
  void* client_data, void* call_data)
{
  CTK_P(ctkVTKConnection);
  
  Q_ASSERT(this->Connected);
  if (this->Blocked) 
    { 
    return; 
    }
  if (vtk_event == vtkCommand::DeleteEvent)
    {
    this->AboutToBeDeleted = true;
    }

  if(vtk_event != vtkCommand::DeleteEvent ||
     (vtk_event == vtkCommand::DeleteEvent && this->VTKEvent == vtkCommand::DeleteEvent))
    {
    vtkObject* callDataAsVtkObject = 0;
    switch (this->SlotType)
      {
      case ctkVTKConnectionPrivate::ARG_VTKOBJECT_AND_VTKOBJECT:
        if (this->VTKEvent == vtk_event)
          {
          callDataAsVtkObject = reinterpret_cast<vtkObject*>( call_data );
          if (!callDataAsVtkObject)
            {
            qCritical() << "The VTKEvent(" << this->VTKEvent<< ") triggered by vtkObject("
              << this->VTKObject->GetClassName() << ") "
              << "doesn't return data of type vtkObject." << endl
              << "The slot (" << this->QtSlot <<  ") owned by "
              << "QObject(" << this->QtObject->objectName() << ")"
              << " may be incorrect.";
            }
          emit p->emitExecute(vtk_obj, callDataAsVtkObject);
          }
        break;
      case ctkVTKConnectionPrivate::ARG_VTKOBJECT_VOID_ULONG_VOID:
        emit p->emitExecute(vtk_obj, call_data, vtk_event, client_data);
        break;
      default:
        // Should never reach
        qCritical() << "Unknown SlotType:" << this->SlotType;
        return;
        break;
      }
    }

  if(vtk_event == vtkCommand::DeleteEvent)
    {
    this->AboutToBeDeleted = false;
    p->deleteConnection();
    }
}

void ctkVTKConnection::deleteConnection()
{
  CTK_D(ctkVTKConnection);
  if (d->AboutToBeDeleted)
    {
    return;
    }
  delete this;
}
