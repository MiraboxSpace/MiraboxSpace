#ifndef EXAMPLEACTION_H
#define EXAMPLEACTION_H

#include <Action.h>
#include <QJsonObject>

class ExampleAction : public Action
{
public:
    ExampleAction(ConnectionManager *connection, const QString &action, const QString &context);

    virtual void DidReceiveSettings(const QJsonObject &payload);
    virtual void KeyDown(const QJsonObject &payload);
    virtual void KeyUp(const QJsonObject &payload);
    virtual void SendToPlugin(const QJsonObject &payload);
    virtual void WillAppear(const QJsonObject &payload);
    virtual void WillDisappear(const QJsonObject &payload);
};

#endif // EXAMPLEACTION_H
