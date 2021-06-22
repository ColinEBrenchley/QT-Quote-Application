#ifndef QUOTES_H
#define QUOTES_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui { class Quotes; }
QT_END_NAMESPACE

class Quotes : public QMainWindow
{
    Q_OBJECT

public:
    Quotes(QWidget *parent = nullptr);
    ~Quotes();

private slots:
    void on_Submit_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::Quotes *ui;
    void Search();
    void EnterQuote();
    void GetQuoteoftheDay();
};

class Quote{
public:
    Quote();
    ~Quote(){};
    QString quote = "";
    QString author = "";

    bool boolMovie = false;
    bool boolBook = false;
    bool boolPersonal = false;
    bool boolFunny = false;
    bool boolSad = false;
    bool boolInspiring = false;
    bool boolGeneral = false;
    bool boolFavorite = false;

private:

};

class QuoteVector : public Quote
{

public:
    QuoteVector();
    ~QuoteVector();
    QVector <Quote> listOfQuotes;
};

#endif // QUOTES_H
