#include "Plugin.h"
#include "Action.h"
#include "ConnectionManager.h"
#include "Logger.h"

Plugin::Plugin()
    : BasePlugin()
{
}

Plugin::~Plugin()
{
}

void Plugin::KeyDownForAction(const QString &inAction,
                              const QString &inContext,
                              const QJsonObject &inPayload,
                              const QString &inDeviceID)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("No action for keydown - %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    action->KeyDown(inPayload);
}

void Plugin::KeyUpForAction(const QString &inAction,
                            const QString &inContext,
                            const QJsonObject &inPayload,
                            const QString &inDeviceID)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("No action for keyup - %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    action->KeyUp(inPayload);
}

void Plugin::DialPressForAction(const QString &inAction,
                                const QString &inContext,
                                const QJsonObject &inPayload,
                                const QString &inDeviceID)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("No action for dialPress - %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    bool pressed = inPayload.value("pressed").toBool();
    if (pressed) {
        action->DialDown(inPayload);
    } else {
        action->DialUp(inPayload);
    }
}

void Plugin::DialRotateForAction(const QString &inAction,
                                 const QString &inContext,
                                 const QJsonObject &inPayload,
                                 const QString &inDeviceID)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("No action for dialRotate - %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    int ticks = inPayload.value("ticks").toInt();
    bool pressed = inPayload.value("pressed").toBool();
    if (ticks < 0) {
        action->RotateCounterClockwise(inPayload, static_cast<const unsigned int>(-ticks), pressed);
    } else {
        action->RotateClockwise(inPayload, static_cast<const unsigned int>(ticks), pressed);
    }
}

void Plugin::WillAppearForAction(const QString &inAction,
                                 const QString &inContext,
                                 const QJsonObject &inPayload,
                                 const QString &inDeviceID)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("No action for WillAppear - %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    action->WillAppear(inPayload);
}

void Plugin::WillDisappearForAction(const QString &inAction,
                                    const QString &inContext,
                                    const QJsonObject &inPayload,
                                    const QString &inDeviceID)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("No action for WillDisappear - %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    action->WillDisappear(inPayload);
    RemoveAction(inAction, inContext);
}

void Plugin::SendToPlugin(const QString &inAction,
                          const QString &inContext,
                          const QJsonObject &inPayload,
                          const QString &inDevice)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("Received plugin request for unknown action %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    action->SendToPlugin(inPayload);
}

void Plugin::DidReceiveSettings(const QString &inAction,
                                const QString &inContext,
                                const QJsonObject &inPayload,
                                const QString &inDevice)
{
    auto action = GetOrCreateAction(inAction, inContext);
    if (!action) {
        Logger::LogToFile(QString("No action for DidReceiveSettings: %1 %2")
                          .arg(inAction).arg(inContext));
        return;
    }
    action->DidReceiveSettings(inPayload);
}
