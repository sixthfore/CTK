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

#ifndef CTKSERVICEREFERENCE_H
#define CTKSERVICEREFERENCE_H

#include <QVariant>

#include "ctkPlugin.h"

#include "CTKPluginFrameworkExport.h"


  class ctkServiceRegistrationPrivate;
  class ctkServiceReferencePrivate;

  /**
   * A reference to a service.
   *
   * <p>
   * The Framework returns <code>ctkServiceReference</code> objects from the
   * <code>ctkPluginContext::getServiceReference</code> and
   * <code>ctkPluginContext::getServiceReferences</code> methods.
   * <p>
   * A <code>ctkServiceReference</code> object may be shared between plugins and
   * can be used to examine the properties of the service and to get the service
   * object.
   * <p>
   * Every service registered in the Framework has a unique
   * <code>ctkServiceRegistration</code> object and may have multiple, distinct
   * <code>ctkServiceReference</code> objects referring to it.
   * <code>ctkServiceReference</code> objects associated with a
   * <code>ctkServiceRegistration</code> are considered equal
   * (more specifically, their <code>operator==()</code>
   * method will return <code>true</code> when compared).
   * <p>
   * If the same service object is registered multiple times,
   * <code>ctkServiceReference</code> objects associated with different
   * <code>ctkServiceRegistration</code> objects are not equal.
   *
   * @see ctkPluginContext::getServiceReference
   * @see ctkPluginContext::getServiceReferences
   * @see ctkPluginContext::getService
   * @threadsafe
   */
  class CTK_PLUGINFW_EXPORT ctkServiceReference {

    Q_DECLARE_PRIVATE(ctkServiceReference)

  public:

    ~ctkServiceReference();

    /**
     * Returns the property value to which the specified property key is mapped
     * in the properties <code>ServiceProperties</code> object of the service
     * referenced by this <code>ctkServiceReference</code> object.
     *
     * <p>
     * Property keys are case-insensitive.
     *
     * <p>
     * This method must continue to return property values after the service has
     * been unregistered. This is so references to unregistered services can
     * still be interrogated.
     *
     * @param key The property key.
     * @return The property value to which the key is mapped; an invalid QVariant
     *         if there is no property named after the key.
     */
    QVariant getProperty(const QString& key) const;

    /**
     * Returns a list of the keys in the <code>ServiceProperties</code>
     * object of the service referenced by this <code>ctkServiceReference</code>
     * object.
     *
     * <p>
     * This method will continue to return the keys after the service has been
     * unregistered. This is so references to unregistered services can
     * still be interrogated.
     *
     * <p>
     * This method is not <i>case-preserving</i>; this means that every key in the
     * returned array is in lower case, which may not be the case for the corresponding key in the
     * properties <code>ServiceProperties</code> that was passed to the
     * {@link ctkPluginContext::registerService(const QStringList&, QObject*, const ServiceProperties&)} or
     * {@link ctkServiceRegistration::setProperties} methods.
     *
     * @return A list of property keys.
     */
    QStringList getPropertyKeys() const;

    /**
     * Returns the plugin that registered the service referenced by this
     * <code>ctkServiceReference</code> object.
     *
     * <p>
     * This method must return <code>0</code> when the service has been
     * unregistered. This can be used to determine if the service has been
     * unregistered.
     *
     * @return The plugin that registered the service referenced by this
     *         <code>ctkServiceReference</code> object; <code>0</code> if that
     *         service has already been unregistered.
     * @see ctkPluginContext::registerService(const QStringList&, QObject* , const ServiceProperties&)
     */
    ctkPlugin* getPlugin() const;

    /**
     * Returns the plugins that are using the service referenced by this
     * <code>ctkServiceReference</code> object. Specifically, this method returns
     * the plugins whose usage count for that service is greater than zero.
     *
     * @return A list of plugins whose usage count for the service referenced
     *         by this <code>ctkServiceReference</code> object is greater than
     *         zero.
     */
    QList<ctkPlugin*> getUsingPlugins() const;

    /**
     * Compares this <code>ctkServiceReference</code> with the specified
     * <code>ctkServiceReference</code> for order.
     *
     * <p>
     * If this <code>ctkServiceReference</code> and the specified
     * <code>ctkServiceReference</code> have the same {@link PluginConstants::SERVICE_ID
     * service id} they are equal. This <code>ctkServiceReference</code> is less
     * than the specified <code>ctkServiceReference</code> if it has a lower
     * {@link PluginConstants::SERVICE_RANKING service ranking} and greater if it has a
     * higher service ranking. Otherwise, if this <code>ctkServiceReference</code>
     * and the specified <code>ctkServiceReference</code> have the same
     * {@link PluginConstants::SERVICE_RANKING service ranking}, this
     * <code>ctkServiceReference</code> is less than the specified
     * <code>ctkServiceReference</code> if it has a higher
     * {@link PluginConstants::SERVICE_ID service id} and greater if it has a lower
     * service id.
     *
     * @param reference The <code>ctkServiceReference</code> to be compared.
     * @return Returns a false or true if this
     *         <code>ctkServiceReference</code> is less than or greater
     *         than the specified <code>ctkServiceReference</code>.
     * @throws std::invalid_argument If the specified
     *         <code>ctkServiceReference</code> was not created by the same
     *         framework instance as this <code>ctkServiceReference</code>.
     */
    bool operator<(const ctkServiceReference& reference) const;

    bool operator==(const ctkServiceReference& reference) const;


  protected:

    friend class ctkServiceRegistrationPrivate;
    friend class ctkPluginContext;

    ctkServiceReference(ctkServiceRegistrationPrivate* reg);

    ctkServiceReferencePrivate * const d_ptr;

  };


#endif // CTKSERVICEREFERENCE_H
