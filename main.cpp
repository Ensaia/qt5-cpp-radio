#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QNetworkAccessManager>

int main(int argc, char *argv[])
{
    QFile file(":/style/style/style.qss");
          file.open(QFile::ReadOnly);
          QString styleSheet = QLatin1String(file.readAll());
     QApplication app(argc, argv);

     app.setStyleSheet(styleSheet);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Miraath_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    MainWindow window;
    window.show();
    return app.exec();
}
