#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QByteArray>
#include <QDateTime>
#include <QUrlQuery>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setvolumeLevelLabelIcon(int value);
    void on_playPushButton_clicked(bool checked);
    void onFinish(QNetworkReply *repplay);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer = new QMediaPlayer();
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
};
#endif // MAINWINDOW_H
