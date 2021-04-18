#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager> // to make requests
#include <QNetworkReply> // to handle replies
#include <QJsonArray> // to work with images
#include <QSslSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString urlApi = "https://api.themoviedb.org/3/";
    QString apiKey = "api_key=968df0642a0c04c353f6f10c04456413";
    QString language = "language=fr-FR";
    QString query = "query=";
    Ui::MainWindow *ui;

private slots:
    void downloadFinished(QNetworkReply*);
    void getSimilar(QNetworkReply*);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
#endif // MAINWINDOW_H
