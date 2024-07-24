#ifndef LOCALIZER_H
#define LOCALIZER_H

#include <QString>
#include <QJsonObject>

class Localizer
{
public:
    static void Initialize(const QString &inLanguageCode);
    static QString GetLocalizedString(const QString &inDefaultString);

private:
    Localizer(const QString &inLanguageCode);
    QString GetLocalizedStringIntern(const QString &inDefaultString);

private:
    QJsonObject mLocalizationData;
};

#endif // LOCALIZER_H
