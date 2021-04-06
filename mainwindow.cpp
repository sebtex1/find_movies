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

// TODO: Pour récupérer des films en fonction de 1 film

// L'ui sera à modifier pour rentrer le nom du film pour le mettre dans le param query de la requete

// Faire en sorte de récupérer l'id du film avec sa requete
// https://api.themoviedb.org/3/search/movie?api_key=968df0642a0c04c353f6f10c04456413&query=pirates%20des&language=fr-FR

// Faire en sorte de récupérer les films similaires au film (movie/{{id du film}}/similar?)
// https://api.themoviedb.org/3/movie/285/similar?api_key=968df0642a0c04c353f6f10c04456413&language=fr-FR
