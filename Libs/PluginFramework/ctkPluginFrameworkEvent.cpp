/*=============================================================================

  Library: CTK

  Copyright (c) 2010 German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include "ctkPluginFrameworkEvent.h"


  ctkPluginFrameworkEvent::ctkPluginFrameworkEvent()
    : d(0)
  {

  }

  ctkPluginFrameworkEvent::ctkPluginFrameworkEvent(Type type, ctkPlugin* plugin, const std::exception& fwException)
    : d(new ctkPluginFrameworkEventData(type, plugin, fwException.what()))
  {

  }

  ctkPluginFrameworkEvent::ctkPluginFrameworkEvent(Type type, ctkPlugin* plugin)
    : d(new ctkPluginFrameworkEventData(type, plugin, QString()))
  {

  }

  ctkPluginFrameworkEvent::ctkPluginFrameworkEvent(const ctkPluginFrameworkEvent& other)
    : d(other.d)
  {

  }

  QString ctkPluginFrameworkEvent::getErrorString() const
  {
    return d->errorString;
  }

  ctkPlugin* ctkPluginFrameworkEvent::getPlugin() const
  {
    return d->plugin;
  }

  ctkPluginFrameworkEvent::Type ctkPluginFrameworkEvent::getType() const
  {
    return d->type;

}
