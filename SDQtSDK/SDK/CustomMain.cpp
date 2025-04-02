#include "CustomMain.h"
#include <SDKDefines.h>
#include <Localizer.h>
#include <ConnectionManager.h>
#include <Logger.h>
#include <QJsonDocument>
#include <QJsonObject>

int CustomMain(int argc, const char **argv, BasePlugin *plugin)
{
    if (argc != 9) {
        Logger::LogToFile(QString("Invalid number of parameters %1 instead of 9").arg(argc));
        return 1;
    }

    int port = 0;
    QString pluginUUID;
    QString registerEvent;
    QString info;
    for (int argumentIndex = 0; argumentIndex < 4; argumentIndex++) {
        QString parameter(argv[1 + 2 * argumentIndex]);
        QString value(argv[1 + 2 * argumentIndex + 1]);

        if (parameter == mSDKPortParameter) {
            port = value.toInt();
        } else if (parameter == mSDKPluginUUIDParameter) {
            pluginUUID = value;
        } else if (parameter == mSDKRegisterEventParameter) {
            registerEvent = value;
        } else if (parameter == mSDKInfoParameter) {
            info = value;
        }
    }

    if (port == 0) {
        Logger::LogToFile(QString("Invalid port number"));
        return 1;
    }

    if (pluginUUID.isEmpty()) {
        Logger::LogToFile(QString("Invalid plugin UUID"));
        return 1;
    }

    if (registerEvent.isEmpty()) {
        Logger::LogToFile(QString("Invalid registerEvent"));
        return 1;
    }

    if (info.isEmpty()) {
        Logger::LogToFile(QString("Invalid info"));
        return 1;
    }

    // Initialize localization helper
    QString language = "en";
    try {
        QJsonObject infoJsonObject = QJsonDocument::fromJson(info.toUtf8()).object();
        QJsonObject applicationInfo = infoJsonObject.value(mSDKApplicationInfo).toObject();
        if (applicationInfo.contains(mSDKApplicationInfoLanguage)) {
            language = applicationInfo.value(mSDKApplicationInfoLanguage).toString("en");
        }
    } catch (...) {
    }
    Localizer::Initialize(language);

    // Create the connection manager
    ConnectionManager *connectionManager = new ConnectionManager(port, pluginUUID, registerEvent, info, plugin);
    Logger::SetConnectionManager(connectionManager);

    // Connect and start the event loop
    connectionManager->Run();
    return 0;
}
