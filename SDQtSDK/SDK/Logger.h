#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class ConnectionManager;

class Logger
{
public:
    Logger() = delete;
    static void SetConnectionManager(ConnectionManager *connection);

    static void LogToServer(const QString &message);
    static void LogToFile(const QString &message);
};

#endif // LOGGER_H
