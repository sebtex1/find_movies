#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::downloadFinished(QNetworkReply *reply) {
    QString replyText = reply->readAll();
    //QJsonDocument doc = QJsonDocument::fromJson(replyText.toUtf8());
    //QJsonObject obj = doc.object();
    ui->textEdit->setText(replyText);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::downloadFinished);
    const QUrl url = QUrl(myUrl + "movie/550?" + apiKey + "&" + language);
    QNetworkRequest request(url);
    manager->get(request);
}
