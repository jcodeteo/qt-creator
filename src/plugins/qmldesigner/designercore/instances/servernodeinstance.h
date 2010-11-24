/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#ifndef SERVERNODEINSTANCE_H
#define SERVERNODEINSTANCE_H

#include "corelib_global.h"
#include <QSharedPointer>
#include <QHash>
#include <QRectF>

#include <nodeinstanceserverinterface.h>
#include <propertyvaluecontainer.h>

QT_BEGIN_NAMESPACE
class QPainter;
class QStyleOptionGraphicsItem;
class QDeclarativeContext;
class QGraphicsItem;
class QGraphicsTransform;
QT_END_NAMESPACE

namespace QmlDesigner {

class NodeInstanceServer;
class InstanceContainer;

namespace Internal {
    class ObjectNodeInstance;
    class QmlGraphicsItemNodeInstance;
    class QmlPropertyChangesNodeInstance;
    class GraphicsObjectNodeInstance;
    class QmlStateNodeInstance;
}

class CORESHARED_EXPORT ServerNodeInstance
{
    friend CORESHARED_EXPORT class NodeInstanceServer;
    friend class QHash<qint32, ServerNodeInstance>;
    friend CORESHARED_EXPORT uint qHash(const ServerNodeInstance &instance);
    friend CORESHARED_EXPORT bool operator==(const ServerNodeInstance &first, const ServerNodeInstance &second);
    friend CORESHARED_EXPORT QDebug operator<<(QDebug debug, const ServerNodeInstance &instance);
    friend CORESHARED_EXPORT class NodeMetaInfo;
    friend class QmlDesigner::Internal::QmlGraphicsItemNodeInstance;
    friend class QmlDesigner::Internal::GraphicsObjectNodeInstance;
    friend class QmlDesigner::Internal::ObjectNodeInstance;
    friend class QmlDesigner::Internal::QmlPropertyChangesNodeInstance;
    friend class QmlDesigner::Internal::QmlStateNodeInstance;

public:
    ServerNodeInstance();
    ~ServerNodeInstance();
    ServerNodeInstance(const ServerNodeInstance &other);
    ServerNodeInstance& operator=(const ServerNodeInstance &other);

    void paint(QPainter *painter);
    QImage renderImage() const;

    ServerNodeInstance parent() const;
    bool hasParent() const;

    bool equalGraphicsItem(QGraphicsItem *item) const;

    QRectF boundingRect() const;
    QPointF position() const;
    QSizeF size() const;
    QTransform transform() const;
    QTransform customTransform() const;
    QTransform sceneTransform() const;
    double rotation() const;
    double scale() const;
    QList<QGraphicsTransform *> transformations() const;
    QPointF transformOriginPoint() const;
    double zValue() const;

    double opacity() const;
    QVariant property(const QString &name) const;
    QVariant defaultValue(const QString &name) const;
    QString instanceType(const QString &name) const;
    QStringList propertyNames() const;


    bool hasBindingForProperty(const QString &name, bool *hasChanged = 0) const;

    bool isValid() const;
    void makeInvalid();
    bool hasContent() const;
    bool isResizable() const;
    bool isMovable() const;
    bool isInPositioner() const;

    bool isSubclassOf(const QString &superTypeName) const;
    bool isRootNodeInstance() const;

    bool isWrappingThisObject(QObject *object) const;

    QVariant resetVariant(const QString &name) const;

    bool hasAnchor(const QString &name) const;
    bool isAnchoredBySibling() const;
    bool isAnchoredByChildren() const;
    QPair<QString, ServerNodeInstance> anchor(const QString &name) const;

    int penWidth() const;

    static void registerDeclarativeTypes();

    void doComponentComplete();

    QString id() const;
    qint32 instanceId() const;

    QObject* testHandle() const;
    QSharedPointer<Internal::ObjectNodeInstance> internalInstance() const;

private: // functions
    ServerNodeInstance(const QSharedPointer<Internal::ObjectNodeInstance> &abstractInstance);

    void setPropertyVariant(const QString &name, const QVariant &value);
    void setPropertyDynamicVariant(const QString &name, const QString &typeName, const QVariant &value);

    void setPropertyBinding(const QString &name, const QString &expression);
    void setPropertyDynamicBinding(const QString &name, const QString &typeName, const QString &expression);

    void resetProperty(const QString &name);
    void refreshProperty(const QString &name);

    void activateState();
    void deactivateState();
    void refreshState();

    bool updateStateVariant(const ServerNodeInstance &target, const QString &propertyName, const QVariant &value);
    bool updateStateBinding(const ServerNodeInstance &target, const QString &propertyName, const QString &expression);
    bool resetStateProperty(const ServerNodeInstance &target, const QString &propertyName, const QVariant &resetValue);

    static ServerNodeInstance create(NodeInstanceServer *nodeInstanceServer, const InstanceContainer &instanceContainer);

    void setDeleteHeldInstance(bool deleteInstance);
    void reparent(const ServerNodeInstance &oldParentInstance, const QString &oldParentProperty, const ServerNodeInstance &newParentInstance, const QString &newParentProperty);


    void setId(const QString &id);

    static QSharedPointer<Internal::ObjectNodeInstance> createInstance(QObject *objectToBeWrapped);
    QSharedPointer<Internal::QmlGraphicsItemNodeInstance> qmlGraphicsItemNodeInstance() const;

    void paintUpdate();

    static bool isSubclassOf(QObject *object, const QByteArray &superTypeName);


    QObject *internalObject() const; // should be not used outside of the nodeinstances!!!!

private: // variables
    QSharedPointer<Internal::ObjectNodeInstance> m_nodeInstance;
};

CORESHARED_EXPORT uint qHash(const ServerNodeInstance &instance);
CORESHARED_EXPORT bool operator==(const ServerNodeInstance &first, const ServerNodeInstance &second);
CORESHARED_EXPORT QDebug operator<<(QDebug debug, const ServerNodeInstance &instance);
}

Q_DECLARE_METATYPE(QmlDesigner::ServerNodeInstance);

#endif // SERVERNODEINSTANCE_H
