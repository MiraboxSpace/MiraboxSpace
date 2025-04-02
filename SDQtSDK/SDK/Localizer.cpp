#include "Localizer.h"
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>

static Localizer *sLocalizer = nullptr;

void Localizer::Initialize(const QString &inLanguageCode)
{
    if (!sLocalizer) {
        sLocalizer = new Localizer(inLanguageCode);
    }
}

QString Localizer::GetLocalizedString(const QString &inDefaultString)
{
    if (sLocalizer) {
      return sLocalizer->GetLocalizedStringIntern(inDefaultString);
    }

    return inDefaultString;
}

Localizer::Localizer(const QString &inLanguageCode)
{
    try {
        QString pluginPath = qApp->applicationDirPath();
        if (!inLanguageCode.isEmpty() && !pluginPath.isEmpty()) {
            QString localizationFilePath = pluginPath + inLanguageCode + ".json";
            QFile file(localizationFilePath);
            if (file.open(QFile::ReadOnly)) {
                QJsonDocument languageJsonDocument = QJsonDocument::fromJson(file.readAll());
                QJsonObject languageJsonObject = languageJsonDocument.object();
                if (languageJsonObject.contains("Localization")) {
                    mLocalizationData = languageJsonObject.value("Localization").toObject();
                } else {
                    mLocalizationData = QJsonObject();
                }
            }
            file.close();
        }
    } catch (...) {
    }
}

QString Localizer::GetLocalizedStringIntern(const QString &inDefaultString)
{
    return mLocalizationData.value(inDefaultString).toString(inDefaultString);
}
