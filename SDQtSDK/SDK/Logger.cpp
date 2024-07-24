#include "Logger.h"
#include <ConnectionManager.h>
#include <QMutex>
#include <QMutexLocker>
#include <QFile>
#include <QDateTime>

namespace {
    ConnectionManager *mConnectionManager = nullptr;
    QMutex LogMutex;
}// namespace

void Logger::SetConnectionManager(ConnectionManager *connection)
{
    mConnectionManager = connection;
}

void Logger::LogToServer(const QString &message)
{
    if (mConnectionManager) {
        mConnectionManager->LogMessage(message);
    }
}

void Logger::LogToFile(const QString &message)
{
    QMutexLocker LogMutexLocker(&LogMutex);

    QFile file("log.txt");
    if (file.open(QFile::ReadWrite | QFile::Append)) {
        QString timeString = QString("[%1]").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QString messageString = QString("%1 %2 %3\r\n").arg(timeString).arg(__FILEW__).arg(message);
        file.write(messageString.toUtf8());
        file.flush();
    }
    file.close();
}
