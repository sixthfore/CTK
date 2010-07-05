
// Qt includes
#include <QDebug>
#include <QFileDialog>
#include <QDir>

// CTK includes
#include "ctkLogger.h"
#include "ctkImageViewerMainWindow.h" 
#include "ctkImageViewerMainWindow_p.h"

//--------------------------------------------------------------------------
static ctkLogger logger("org.commontk.applications.ctkImageViewer.ctkImageViewerMainWindow");
//--------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ctkImageViewerMainWindowPrivate methods

//-----------------------------------------------------------------------------
void ctkImageViewerMainWindowPrivate::setupUi(QMainWindow * mainWindow)
{ 
  this->Ui_ctkImageViewerMainWindow::setupUi(mainWindow);
  this->mainwindow = mainWindow;
  // Connection between widgets should be done here ...
  

  this->setupMenuActions();
}

//-----------------------------------------------------------------------------
// Helper macro allowing to connect the MainWindow action with the corresponding slot
#define ctkImageViewerMainWindow_connect(ACTION_NAME)   \
  this->connect(                                        \
    this->action##ACTION_NAME, SIGNAL(triggered()),     \
    SLOT(on##ACTION_NAME##ActionTriggered()));
    
//-----------------------------------------------------------------------------
void ctkImageViewerMainWindowPrivate::setupMenuActions()
{
  this->connect(
    this->actionFileQuit, SIGNAL(triggered()),
    QApplication::instance(), SLOT(quit()));
  
  ctkImageViewerMainWindow_connect(FileOpen);
  
}

#undef ctkImageViewerMainWindow_connect

//-----------------------------------------------------------------------------
void ctkImageViewerMainWindowPrivate::onFileOpenActionTriggered()
{
  QString fileName = QFileDialog::getOpenFileName(this->mainwindow, tr("Open File"), QDir::currentPath());
  
  if (!fileName.isEmpty()){
	this->reader->SetFileName(fileName.toAscii().constData() );
	this->reader->Update();
  }
	
	
  qDebug() << "onFileOpenActionTriggered";
}

//-----------------------------------------------------------------------------
// ctkImageViewerMainWindow methods

//-----------------------------------------------------------------------------
ctkImageViewerMainWindow::ctkImageViewerMainWindow(QWidget *newParent):Superclass(newParent)
{
  CTK_INIT_PRIVATE(ctkImageViewerMainWindow);
  CTK_D(ctkImageViewerMainWindow);
  
  d->setupUi(this);
}
