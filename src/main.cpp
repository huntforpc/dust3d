#include <QApplication>
#include <QDesktopWidget>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QPointer>
#include <QDebug>
#include <QtGlobal>
#include "logbrowser.h"
#include "skeletondocumentwindow.h"
#include "theme.h"

QPointer<LogBrowser> g_logBrowser;

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (g_logBrowser)
        g_logBrowser->outputMessage(type, msg);
}

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    
    // QuantumCD/Qt 5 Dark Fusion Palette
    // https://gist.github.com/QuantumCD/6245215
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(0x25,0x25,0x25));
    darkPalette.setColor(QPalette::WindowText, QColor(239,239,239));
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, QColor(239,239,239));
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, Theme::white);
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #fc6621; border: 1px solid white; }");
    
    QCoreApplication::setApplicationName("Dust 3D");
    
    QFont font;
    font.setWeight(QFont::Light);
    font.setPixelSize(9);
    font.setBold(false);
    QApplication::setFont(font);

    g_logBrowser = new LogBrowser;
    qInstallMessageHandler(&outputMessage);
    
    SkeletonDocumentWindow mainWindow;
    mainWindow.showMaximized();
    return app.exec();
}