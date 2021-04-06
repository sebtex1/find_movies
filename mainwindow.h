#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager> // to make requests
#include <QNetworkReply> // to handle replies
#include <QPixmap> // to work with images
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
    QString myUrl = "https://api.themoviedb.org/3/";
    // QString myUrl = "https://interactive-examples.mdn.mozilla.net/media/cc0-images/grapefruit-slice-332-332.jpg";
    QString apiKey = "api_key=968df0642a0c04c353f6f10c04456413";
    QString language = "language=fr-FR";
    Ui::MainWindow *ui;

private slots:
    void downloadFinished(QNetworkReply*);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
