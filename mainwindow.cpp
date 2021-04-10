#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::downloadFinished(QNetworkReply *reply) {
    QString jsonStr = reply->readAll();
    ui->response1->append(jsonStr);
    QJsonDocument myJson = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject myObj = myJson.object();
    if (myObj.isEmpty()) {
        ui->response1->setText("Object is empty");
    } else {
        for (auto it = myObj.begin(); it != myObj.end(); it++) {
            QString myStr = "Key-> " + it.key().toUtf8() + " : Value->";
            if (it->isArray()) {
                QJsonArray myArr = it->toArray();
                QString myStrArr = "[";
                for (auto ita = myArr.begin(); ita != myArr.end(); ita++) {
                    myStrArr.append(ita->toString().toUtf8() + ", ");
                }
                myStrArr.append("]");
                myStr.append(myStrArr);
            } else {
                myStr.append(it.value().toString());
            }
            ui->response1->append(myStr);
        }

    }
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
    const QString search = ui->textEditSearch1->toPlainText();
    const QUrl url = QUrl(urlApi + "search/movie?" + apiKey + "&" + language + "&" + query + search);
    QNetworkRequest request(url);
    manager->get(request);
}

// TODO: Pour récupérer des films en fonction de 1 film

// L'ui sera à modifier pour rentrer le nom du film pour le mettre dans le param query de la requete

// Faire en sorte de récupérer l'id du film avec sa requete
// https://api.themoviedb.org/3/search/movie?api_key=968df0642a0c04c353f6f10c04456413&query=pirates%20des&language=fr-FR

// Faire en sorte de récupérer les films similaires au film (movie/{{id du film}}/similar?)
// https://api.themoviedb.org/3/movie/285/similar?api_key=968df0642a0c04c353f6f10c04456413&language=fr-FR
