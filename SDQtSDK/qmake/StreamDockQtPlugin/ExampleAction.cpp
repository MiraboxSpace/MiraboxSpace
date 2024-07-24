#include "ExampleAction.h"
#include <Logger.h>
#include <QJsonDocument>

ExampleAction::ExampleAction(ConnectionManager *connection, const QString &action, const QString &context)
    : Action{connection, action, context}
{

}

void ExampleAction::DidReceiveSettings(const QJsonObject &payload)
{
    Logger::LogToServer("DidReceiveSettings");
}

void ExampleAction::KeyDown(const QJsonObject &payload)
{
    Logger::LogToServer("KeyDown");
    if (payload.value("state").toInt() == 0) {
        SetState(1);
    } else {
        SetState(0);
    }
}

void ExampleAction::KeyUp(const QJsonObject &payload)
{
    // Log in release and debug builds
    Logger::LogToServer("KeyUp");
}

void ExampleAction::WillAppear(const QJsonObject &payload)
{
    Logger::LogToServer("WillAppear");
}

void ExampleAction::WillDisappear(const QJsonObject &payload)
{
    Logger::LogToServer("WillAppear");
}

void ExampleAction::SendToPlugin(const QJsonObject &payload)
{
    QString payloadString = QJsonDocument(payload).toJson(QJsonDocument::Compact);
    Logger::LogToServer(QString("Received message from property inspector: %1").arg(payloadString));
}
