#ifndef FONTAWESOMEICONS_H
#define FONTAWESOMEICONS_H

#include <QFont>
#include <QMap>
#include <QColor>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

static const QString fa_light_ttf   = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-light-300.ttf";
static const QString fa_solid_ttf   = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-solid-900.ttf";
static const QString fa_regular_ttf = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-regular-400.ttf";
static const QString fa_duotone_ttf = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-duotone-900.ttf";
static const QString fa_css_file    = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/font-awesome.css";

static bool  loadFont(const QString& ttf, QFont& font, QMap<QString, QString>& m_iconUnicodeMap);
static QChar iconUnicode(const QMap<QString, QString>& m_iconUnicodeMap, const QString &iconName);
static void  setWidgetIcon(QFont& font, const QMap<QString, QString>& m_iconUnicodeMap,
                          QWidget *widget, const QString &iconName, int iconSize, const QColor& iconColor);

class IconFontLightHelper
{
public:
    static void setIcon(QWidget* widget, const QString& iconName, int iconSize, const QColor& iconColor = QColor()){
        static bool loadSuccess = false;
        if(!loadSuccess)
        {
            loadSuccess = loadFont(fa_light_ttf, m_font, m_iconUnicodeMap);
            if(!loadSuccess)
            {
                qDebug() << "Icon font loaded failed, setIcon will not work properly.";
                return;
            }
        }
        setWidgetIcon(m_font, m_iconUnicodeMap, widget, iconName, iconSize, iconColor);
    }

protected:
    static QFont m_font;
    static QMap<QString, QString> m_iconUnicodeMap;
};

class IconFontSolidHelper
{
public:
    static void setIcon(QWidget* widget, const QString& iconName, int iconSize, const QColor& iconColor = QColor()){
        static bool loadSuccess = false;
        if(!loadSuccess)
        {
            loadSuccess = loadFont(fa_solid_ttf, m_font, m_iconUnicodeMap);
            if(!loadSuccess)
            {
                qDebug() << "Icon font loaded failed, setIcon will not work properly.";
                return;
            }
        }
        setWidgetIcon(m_font, m_iconUnicodeMap, widget, iconName, iconSize, iconColor);
    }
private:
    static QFont m_font;
    static QMap<QString, QString> m_iconUnicodeMap;
};

class IconFontDuotoneHelper
{
public:
    static void setIcon(QWidget* widget, const QString& iconName, int iconSize, const QColor& iconColor = QColor()){
        static bool loadSuccess = false;
        if(!loadSuccess)
        {
            loadSuccess = loadFont(fa_duotone_ttf, m_font, m_iconUnicodeMap);
            if(!loadSuccess)
            {
                qDebug() << "Icon font loaded failed, setIcon will not work properly.";
                return;
            }
        }
        setWidgetIcon(m_font, m_iconUnicodeMap, widget, iconName, iconSize, iconColor);
    }
private:
    static QFont m_font;
    static QMap<QString, QString> m_iconUnicodeMap;
};

class IconFontRegularHelper
{
public:
    static void setIcon(QWidget* widget, const QString& iconName, int iconSize, const QColor& iconColor = QColor()){
        static bool loadSuccess = false;
        if(!loadSuccess)
        {
            loadSuccess = loadFont(fa_regular_ttf, m_font, m_iconUnicodeMap);
            if(!loadSuccess)
            {
                qDebug() << "Icon font loaded failed, setIcon will not work properly.";
                return;
            }
        }
        setWidgetIcon(m_font, m_iconUnicodeMap, widget, iconName, iconSize, iconColor);
    }
private:
    static QFont m_font;
    static QMap<QString, QString> m_iconUnicodeMap;
};

// fa regular 400
_declspec(selectany) QFont IconFontLightHelper::m_font;
_declspec(selectany) QMap<QString, QString> IconFontLightHelper::m_iconUnicodeMap;

// fa solid 900
_declspec(selectany) QFont IconFontSolidHelper::m_font;
_declspec(selectany) QMap<QString, QString> IconFontSolidHelper::m_iconUnicodeMap;

// fa duotone 900
_declspec(selectany) QFont IconFontDuotoneHelper::m_font;
_declspec(selectany) QMap<QString, QString> IconFontDuotoneHelper::m_iconUnicodeMap;

//fa-light-300.ttf(default)
_declspec(selectany) QFont IconFontRegularHelper::m_font;
_declspec(selectany) QMap<QString, QString> IconFontRegularHelper::m_iconUnicodeMap;

static QChar iconUnicode(const QMap<QString, QString>& m_iconUnicodeMap, const QString &iconName)
{
    for(auto iter = m_iconUnicodeMap.begin(); iter != m_iconUnicodeMap.end(); iter++)
    {
        if(iter.key() == iconName)
        {
            bool ok;
            QString content = iter.value();
            QChar c = QString(content).toInt(&ok, 16);
            return c;
        }
    }
    qDebug() << "Wanning: Couldn't find " << iconName;
    return QChar();
}

static bool loadFont(const QString& ttf, QFont& font, QMap<QString, QString>& m_iconUnicodeMap)
{
    int fId = QFontDatabase::addApplicationFont(ttf);
    QStringList fontFamily = QFontDatabase::applicationFontFamilies(fId);
    Q_ASSERT(fontFamily.size() > 0);
    font.setFamily(fontFamily.at(0));
    Q_ASSERT(QFileInfo(fa_css_file).exists());
    QFile fontCssFile(fa_css_file);
    if(!fontCssFile.open(QFile::Text | QFile::ReadOnly))
    {
        qDebug() << "Could not open font css file.";
        return false;
    }
    while(!fontCssFile.atEnd())
    {
        QString line = fontCssFile.readLine();
        if(line.contains(".fa-") && line.contains(":before"))
        {
            QString nextLine = fontCssFile.readLine();
            if(nextLine.contains("content"))
            {
                QString key = line.split(':')[0].remove(".fa-");
                QString content = nextLine.split(':')[1].simplified().remove(";").remove("\"").remove("\\");
                m_iconUnicodeMap.insert(key, content);
            }
        }
    }
    qDebug() << "Font css file load successfully.";
    return m_iconUnicodeMap.size() != 0;
}

static void setWidgetIcon(QFont& font, const QMap<QString, QString>& m_iconUnicodeMap,
                          QWidget *widget, const QString &iconName, int iconSize, const QColor& iconColor)
{
    font.setPointSize(iconSize);
    if(!widget) return;

    widget->setFont(font);
    if(iconColor.isValid())
        widget->setStyleSheet(QString("color:%1").arg(iconColor.name()));

    QLabel* label = qobject_cast<QLabel*>(widget);
    if(label)   label->setText(iconUnicode(m_iconUnicodeMap, iconName));

    QAbstractButton* button = qobject_cast<QAbstractButton*>(widget);
    if(button)  button->setText(iconUnicode(m_iconUnicodeMap, iconName));
}


#endif // FONTAWESOMEICONS_H
