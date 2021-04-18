#include "mainwindow.h"
#include "ui_mainwindow.h"

// TODO: Pour récupérer des films en fonction de 1 film
// L'api fonctionne mais je n'arrive pas à récupérer les valeurs comprisse à l'intérieur
// j'ai essayé de mettre l'iterateur ita qui est un object dans un objetJson, sans success.

// Je laisse sur l'ui api visible pour montrer qu'elle focntionne, elle est grande et il faut retourner au début pour voir les valeurs

// J'ajoute la reponse api de la similitude des films dans l'ui avec 'Pirate des caraïbes' dans la recherche pour vous montrer.

// J'ai du travailler sur le projet tout seul en demandant de l'aide à mes camarades mais sans réponse, ou même un essai de leur par.

// L'ui sera à modifier pour rentrer le nom du film pour le mettre dans le param query de la requete

// Faire en sorte de récupérer l'id du film avec sa requete
// https://api.themoviedb.org/3/search/movie?api_key=968df0642a0c04c353f6f10c04456413&query=pirates%20des&language=fr-FR

// Faire en sorte de récupérer les films similaires au film (movie/{{id du film}}/similar?)
// https://api.themoviedb.org/3/movie/285/similar?api_key=968df0642a0c04c353f6f10c04456413&language=fr-FR

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
            if (it->isArray() == true ) {
                QJsonArray myArr = it->toArray();
                QString myStrArr = "[";
                for (auto ita = myArr.begin(); ita != myArr.end(); ita++) {
                    //if (ita->isObject()) {
                    //    QJsonObject myObj2 = ita->toObject();
                    //    for (auto itO = myObj2.begin(); itO != myObj2.end(); it++) {
                    //        myStrArr.append("Key-> " + itO.key().toUtf8() + " : Value->" + itO.value().toString());
                    //    }
                    //}
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

void MainWindow::getSimilar(QNetworkReply *reply) {
    QString jsonStr = reply->readAll();
    ui->similitude->append(jsonStr);
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


void MainWindow::on_pushButton_2_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::getSimilar);
    const QString search = ui->textEditSearch1->toPlainText();
    const QUrl url = QUrl(urlApi + "/movie/285/similar?" + apiKey + "&" + language);
    QNetworkRequest request(url);
    manager->get(request);
}
