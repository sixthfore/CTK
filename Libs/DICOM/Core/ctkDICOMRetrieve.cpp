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
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDate>
#include <QStringList>
#include <QSet>
#include <QFile>
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>

// ctkDICOM includes
#include "ctkDICOMRetrieve.h"
#include "ctkLogger.h"

// DCMTK includes
#ifndef WIN32
  #define HAVE_CONFIG_H 
#endif
#include "dcmtk/dcmnet/dimse.h"
#include "dcmtk/dcmnet/diutil.h"

#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/ofstd/ofcond.h>
#include <dcmtk/ofstd/ofstring.h>
#include <dcmtk/ofstd/ofstd.h>        /* for class OFStandard */
#include <dcmtk/dcmdata/dcddirif.h>   /* for class DicomDirInterface */

#include <dcmtk/dcmnet/scu.h>

static ctkLogger logger ( "org.commontk.dicom.DICOMRetrieve" );

//------------------------------------------------------------------------------
class ctkDICOMRetrievePrivate: public ctkPrivate<ctkDICOMRetrieve>
{
public:
  ctkDICOMRetrievePrivate();
  ~ctkDICOMRetrievePrivate();
  QString CallingAETitle;
  QString CalledAETitle;
  QString Host;
  int CallingPort;
  int CalledPort;
  DcmSCU SCU;
  DcmDataset* query;
};

//------------------------------------------------------------------------------
// ctkDICOMRetrievePrivate methods

//------------------------------------------------------------------------------
ctkDICOMRetrievePrivate::ctkDICOMRetrievePrivate()
{
  query = new DcmDataset();
}

//------------------------------------------------------------------------------
ctkDICOMRetrievePrivate::~ctkDICOMRetrievePrivate()
{
  delete query;
}



//------------------------------------------------------------------------------
// ctkDICOMRetrieve methods

//------------------------------------------------------------------------------
ctkDICOMRetrieve::ctkDICOMRetrieve()
{
}

//------------------------------------------------------------------------------
ctkDICOMRetrieve::~ctkDICOMRetrieve()
{
}

/// Set methods for connectivity
void ctkDICOMRetrieve::setCallingAETitle ( QString callingAETitle )
{
  CTK_D(ctkDICOMRetrieve);
  d->CallingAETitle = callingAETitle;
}
const QString& ctkDICOMRetrieve::callingAETitle() 
{
  CTK_D(ctkDICOMRetrieve);
  return d->CallingAETitle;
}
void ctkDICOMRetrieve::setCalledAETitle ( QString calledAETitle )
{
  CTK_D(ctkDICOMRetrieve);
  d->CalledAETitle = calledAETitle;
}
const QString& ctkDICOMRetrieve::calledAETitle()
{
  CTK_D(ctkDICOMRetrieve);
  return d->CalledAETitle;
}
void ctkDICOMRetrieve::setHost ( QString host )
{
  CTK_D(ctkDICOMRetrieve);
  d->Host = host;
}
const QString& ctkDICOMRetrieve::host()
{
  CTK_D(ctkDICOMRetrieve);
  return d->Host;
}
void ctkDICOMRetrieve::setCallingPort ( int port ) 
{
  CTK_D(ctkDICOMRetrieve);
  d->CallingPort = port;
}
int ctkDICOMRetrieve::callingPort()
{
  CTK_D(ctkDICOMRetrieve);
  return d->CallingPort;
}

void ctkDICOMRetrieve::setCalledPort ( int port ) 
{
  CTK_D(ctkDICOMRetrieve);
  d->CalledPort = port;
}
int ctkDICOMRetrieve::calledPort()
{
  CTK_D(ctkDICOMRetrieve);
  return d->CalledPort;
}



//------------------------------------------------------------------------------
void ctkDICOMRetrieve::retrieveSeries ( QString seriesInstanceUID, QDir directory ) {
}
