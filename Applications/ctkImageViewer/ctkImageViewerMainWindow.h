#ifndef __ctkImageViewerMainWindow_h
#define __ctkImageViewerMainWindow_h 

// Qt includes
#include <QMainWindow>

// CTK includes
#include "ctkPimpl.h"

class ctkImageViewerMainWindowPrivate;

class ctkImageViewerMainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  typedef QMainWindow Superclass;
  ctkImageViewerMainWindow(QWidget *newParent = 0);
  
  
private:
  CTK_DECLARE_PRIVATE(ctkImageViewerMainWindow);
};


#endif
