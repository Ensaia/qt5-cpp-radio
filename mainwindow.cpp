#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(360);
    this->setFixedWidth(360);

    ui->playPushButton->setCheckable(true);

    ui->volumeControlSlider->setOrientation(Qt::Horizontal);
    ui->volumeControlSlider->setRange(0,100);
    ui->volumeControlSlider->setValue(80);
    ui->volumeControlSlider->setToolTip(QString("مستوى الصوت"));
    connect(ui->volumeControlSlider,&QSlider::valueChanged,mediaPlayer,&QMediaPlayer::setVolume);
    connect(ui->volumeControlSlider,&QSlider::valueChanged,this,&MainWindow::setvolumeLevelLabelIcon);
    connect(ui->volumeControlSlider,&QSlider::valueChanged,ui->volumeLevelLabel,qOverload<int>(&QLabel::setNum));

    ui->volumeLevelLabelIcon->setPixmap(QPixmap(":/images/images/volume.png"));
    ui->volumeLevelLabel->setText(QString::number(ui->volumeControlSlider->value()));

    QUrlQuery params;
    params.addQueryItem("rsys", "scv26");
    params.addQueryItem("port", "8010");
    QDateTime cd = QDateTime::currentDateTime();
    params.addQueryItem("NoCache", QString::number(cd.toTime_t()));    

    connect(networkAccessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinish(QNetworkReply*)));

    QNetworkRequest request(QUrl(QStringLiteral("https://radio.al7eah.net/cp/widgets/player/single/nowplay.php")));
    request.setHeader(QNetworkRequest::ContentTypeHeader,QStringLiteral("application/x-www-form-urlencoded"));
    networkAccessManager->post(request, params.query().toUtf8());

}

MainWindow::~MainWindow()
{
    delete ui;
    delete mediaPlayer;
    delete networkAccessManager;
}


void MainWindow::setvolumeLevelLabelIcon(int value){
    if (value == 0){
        ui->volumeLevelLabelIcon->setPixmap(QPixmap(":/images/images/volume-off.png"));
        }else if(value > 0 && value <= 30){
        ui->volumeLevelLabelIcon->setPixmap(QPixmap(":/images/images/volume-min.png"));
        }else if (value > 30 && value <= 70) {
        ui->volumeLevelLabelIcon->setPixmap(QPixmap(":/images/images/volume-mid.png"));
        }else if (value > 70) {
        ui->volumeLevelLabelIcon->setPixmap(QPixmap(":/images/images/volume-high.png"));
    }
}

void MainWindow::on_playPushButton_clicked(bool checked)
{

    if(checked){
        mediaPlayer->setMedia(QUrl("https://radio.al7eah.net/8010/stream"));
        mediaPlayer->play();
        ui->playPushButton->setIcon(QIcon(":/images/images/pause.png"));
        ui->playPushButton->setToolTip(QString("إيقاف مؤقت"));
    }else{
        mediaPlayer->pause();
        ui->playPushButton->setIcon(QIcon(":/images/images/play.png"));
        ui->playPushButton->setToolTip(QString("تشغيل"));
    }

}
void MainWindow::onFinish(QNetworkReply *replay)
{
    QByteArray responseBytes = replay->readAll();
    QString responseString(responseBytes);
    ui->playingNowLabel->setText(responseString.remove(QRegExp("<[^>]*>")));
}
