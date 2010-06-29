#ifndef __ctkImageViewerMainWindowPrivate_p_h
#define __ctkImageViewerMainWindowPrivate_p_h

// CTK includes
#include "ctkPimpl.h"
#include "ctkImageViewerMainWindow.h"
#include "ui_ctkImageViewerMainWindow.h"


//-----------------------------------------------------------------------------
class ctkImageViewerMainWindowPrivate: public QObject, 
                                       public ctkPrivate<ctkImageViewerMainWindow>, 
                                       public Ui_ctkImageViewerMainWindow
{
  Q_OBJECT
public:
  CTK_DECLARE_PUBLIC(ctkImageViewerMainWindow);
  ctkImageViewerMainWindowPrivate()
    {

    }

  void setupUi(QMainWindow * mainWindow);
  
  ///
  /// Connect MainWindow menu actions with corresponding slots
  void setupMenuActions();

public slots:
  /// Handle actions
  /// \sa setupMenuActions
  void onFileOpenActionTriggered();

public: 
 
};

#endif

