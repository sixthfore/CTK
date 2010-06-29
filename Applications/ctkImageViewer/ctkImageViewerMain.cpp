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
#include <QApplication>

// CTK includes
#include "ctkLogger.h"
#include "ctkCommandLineParser.h"
#include "ctkImageViewerMainWindow.h"

// STD includes
#include <cstdlib>
#include <iostream>

//--------------------------------------------------------------------------
static ctkLogger logger("org.commontk.applications.ctkImageViewer");
//--------------------------------------------------------------------------

int main(int argc, char** argv)
{
  ctkLogger::configure();
  QApplication app(argc, argv);
  
  // Arguments
  bool displayHelp = false;
  bool debugOutput = false;
  
  // Command line parser
  ctkCommandLineParser parser;
  parser.addBooleanArgument("--help", "-h", &displayHelp);
  parser.addBooleanArgument("--debut-output", "-d", &debugOutput);
  if (!parser.parseArguments(app.arguments()))
    {
    std::cerr << qPrintable(parser.errorString()) << std::endl;
    return EXIT_FAILURE;
    }
  
  // Process arguments
  if (debugOutput)
    {
    logger.setTrace();
    logger.trace("Debug output - ON");
    }
    
  if (displayHelp)
    {
    // Display help ...
    return EXIT_SUCCESS;
    }
  
  // Display main widgets
  ctkImageViewerMainWindow mainWindow;
  mainWindow.show();

  return app.exec();  
}
