PROJECT(ctkImageViewer)

#
# 3rd party dependencies
#

FIND_PACKAGE(VTK)
IF(NOT VTK_FOUND)
  MESSAGE(FATAL_ERROR "error: VTK package is required to build ${PROJECT_NAME}")
ENDIF()
INCLUDE(${VTK_USE_FILE})

#
# See CTK/CMake/ctkMacroBuildApp.cmake for details
#
  
# Source files
SET(KIT_SRCS
  ctkImageViewerMain.cpp
  ctkImageViewerMainWindow.cpp
  ctkImageViewerMainWindow.h
  ctkImageViewerMainWindow_p.h
  
  ctkVTKImageView.cpp
  ctkVTKImageView.h
  ctkVTKImageView_p.h
  )

# Headers that should run through moc
SET(KIT_MOC_SRCS
  ctkImageViewerMainWindow.h
  ctkImageViewerMainWindow_p.h
  ctkVTKImageView.h
  ctkVTKImageView_p.h
  )

# UI files
SET(KIT_UI_FORMS
  ctkImageViewerMainWindow.ui
)

# Resources
SET(KIT_resources
)
  
# Target libraries - See CMake/ctkMacroGetTargetLibraries.cmake
# The following macro will read the target libraries from the file 'target_libraries.cmake'
ctkMacroGetTargetLibraries(KIT_target_libraries)

# Additional directories to include - Not that CTK_INCLUDE_LIBRARIES is already included
SET(KIT_include_directories
  )

ctkMacroBuildApp(
  NAME ${PROJECT_NAME}
  INCLUDE_DIRECTORIES ${KIT_include_directories}
  SRCS ${KIT_SRCS}
  MOC_SRCS ${KIT_MOC_SRCS}
  UI_FORMS ${KIT_UI_FORMS}
  TARGET_LIBRARIES ${KIT_target_libraries}
  RESOURCES ${KIT_resources}
  )

# Testing
IF(BUILD_TESTING)
  ADD_SUBDIRECTORY(Testing)
ENDIF(BUILD_TESTING)
