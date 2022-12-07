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
#include <QPainter>

static const QString fa_light_ttf   = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-light-300.ttf";
static const QString fa_solid_ttf   = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-solid-900.ttf";
static const QString fa_regular_ttf = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-regular-400.ttf";
static const QString fa_duotone_ttf = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/fa-duotone-900.ttf";
static const QString fa_css_file    = ":/iconfont/FontAwesome_Pro5.11.2/webfonts/font-awesome.css";

static bool  loadFont(const QString& ttf, QFont& font, QMap<QString, QString>& m_iconUnicodeMap);
static QChar iconUnicode(const QMap<QString, QString>& m_iconUnicodeMap, const QString &iconName);
static void  setWidgetIcon(QFont& font, const QMap<QString, QString>& m_iconUnicodeMap,
                          QWidget *widget, const QString &iconName, int iconSize, const QColor& iconColor);

/// The painter icon engine.
#include <QIconEngine>
class IconFontEngine : public QIconEngine
{
public:
    IconFontEngine(QIconEngine* parent = nullptr){}
    IconFontEngine(QFont& font, const QMap<QString, QString>& iconUnicodeMap, const QString& iconName,
                   int iconSize, QColor iconColor = QColor(), QIconEngine* parent = nullptr)
        :m_font(font),m_iconUnicodeMap(iconUnicodeMap), m_iconName(iconName), m_iconSize(iconSize), m_iconColor(iconColor){

    }
    IconFontEngine* clone() const
    {
        return new IconFontEngine(nullptr);
    }
    virtual void paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state)
    {
        painter->save();
        if(mode == QIcon::Disabled)
            m_iconColor = Qt::gray;
        painter->setPen(m_iconColor);
        m_font.setPointSize(m_iconSize);
        painter->setFont(m_font);
        QChar text = iconUnicode(m_iconUnicodeMap, m_iconName);
        painter->drawText(rect, QString(text), QTextOption( Qt::AlignCenter | Qt::AlignVCenter));
        painter->restore();
    }
    virtual QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state)
    {
        QPixmap pm(size);
        pm.fill( Qt::transparent ); // we need transparency
        {
            QPainter p(&pm);
            paint(&p, QRect(QPoint(0,0),size), mode, state);
        }
        return pm;
    }
private:
    QFont   m_font;
    QMap<QString, QString> m_iconUnicodeMap;
    QString m_iconName;
    int     m_iconSize;
    QColor  m_iconColor;
};

#define IconFontHelperClass(type, ttf) \
    struct IconFont##type##Helper{ \
        static void setIcon(QWidget* widget, const QString& iconName, int iconSize, const QColor& iconColor = QColor()){ \
            if(!m_loadFont){ \
                m_loadFont = loadFont(ttf, m_font, m_iconUnicodeMap); \
                if(!m_loadFont) { \
                    qDebug() << "Error: Icon font read failed."; \
                    return; \
                } \
            } \
            setWidgetIcon(m_font, m_iconUnicodeMap, widget, iconName, iconSize, iconColor); \
        } \
        static QIcon icon(const QString& iconName, int iconSize, const QColor& iconColor = QColor()){ \
            if(!m_loadFont) { \
                m_loadFont = loadFont(ttf, m_font, m_iconUnicodeMap); \
                if(!m_loadFont) { \
                    qDebug() << "Error: Icon font read failed."; \
                    return QIcon(); \
                } \
            } \
            return QIcon(new IconFontEngine(m_font, m_iconUnicodeMap, iconName, iconSize, iconColor, nullptr)); \
        } \
    protected: \
        static bool  m_loadFont; \
        static QFont m_font; \
        static QMap<QString, QString> m_iconUnicodeMap; \
    }; \
    _declspec(selectany) bool  IconFont##type##Helper::m_loadFont = false; \
    _declspec(selectany) QFont IconFont##type##Helper::m_font; \
    _declspec(selectany) QMap<QString, QString> IconFont##type##Helper::m_iconUnicodeMap;


IconFontHelperClass(Light,  fa_light_ttf) // IconFontLightHelper
IconFontHelperClass(Solid,  fa_solid_ttf) // IconFontSolidHelper
IconFontHelperClass(Duotone, fa_duotone_ttf) // IconFontDuotoneHelper
IconFontHelperClass(Regular, fa_regular_ttf) // IconFontRegularHelper

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
