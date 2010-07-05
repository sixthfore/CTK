#ifndef __ctkImageViewerMainWindowPrivate_p_h
#define __ctkImageViewerMainWindowPrivate_p_h

// CTK includes
#include "ctkPimpl.h"
#include "ctkImageViewerMainWindow.h"
#include "ui_ctkImageViewerMainWindow.h"
#include "vtkPNGReader.h"
#include "vtkSmartPointer.h"
#include "ctkVTKSliceView.h"

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
    this->reader = vtkSmartPointer<vtkPNGReader>::New();
    this->sliceviewer = new ctkVTKSliceView;
    }

  void setupUi(QMainWindow * mainWindow);
  void openFileName(const char *fileName);  
  ///
  /// Connect MainWindow menu actions with corresponding slots
  void setupMenuActions();

public slots:
  /// Handle actions
  /// \sa setupMenuActions
  void onFileOpenActionTriggered();

public: 

private:
  vtkSmartPointer <vtkPNGReader> reader;
  QMainWindow *mainwindow;
  ctkVTKSliceView *sliceviewer;
  
};

#endif

