#include "quotes.h"
#include "./ui_quotes.h"
#include <QFileDialog>

Quotes::Quotes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Quotes)
{
    ui->setupUi(this);

    ui->QuoteTextEdit->setPlaceholderText("Enter Quote Here");
    ui->AuthorLineEdit_2->setPlaceholderText("Enter Author Here");

    QSqlDatabase database;
    QString favorites = "";
    QFont f( "Arial", 12);


    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("../QuoteManagerSQL/QuoteData.db");

    if(database.open()){
        QSqlQueryModel qry;
            qry.setQuery("SELECT * FROM data");

            int randomValue = QRandomGenerator::global()->bounded(qry.rowCount());
            QString dailyQuote = "\"" + qry.record(randomValue).value("quote").toString()+ "\" \n" + "            -" + qry.record(randomValue).value("author").toString();
            ui->QuoteLabel_2->setText(dailyQuote);
            ui->QuoteLabel_2->setFont(f);

            for (int i = 0; i < qry.rowCount(); ++i) {
                if(qry.record(i).value("favorite").toString() == "1"){
                        favorites += "\"" + qry.record(i).value("quote").toString()+ "\" \n" + "            -" + qry.record(i).value("author").toString() + "\n" + "\n" + "\n";
                    }
            }
        ui->FavoritesScroll->setFont(f);
        ui->FavoritesScroll->setText(favorites);
    }


}

Quotes::~Quotes()
{
    delete ui;
}

void Quotes::on_Submit_2_clicked()
{     
    QString quote = "";
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("../QuoteManagerSQL/QuoteData.db");


    if(database.open()){

        quote = ui->QuoteTextEdit->text();
        QString author = ui->AuthorLineEdit_2->text();
        QString favorite = "0";
        QString book = "0";
        QString movie = "0";
        QString personal = "0";
        QString funny = "0";
        QString sad = "0";
        QString inspiring = "0";
        QString general = "0";

        if(ui->FavoriteCheckBox_2->isChecked()){
            favorite = "1";
        }
        if(ui->BookCat_2->isChecked()){
            book = "1";
        }
        if(ui->MovieCat_2->isChecked()){
            movie ="1";
        }
        if(ui->PersonalCat_2->isChecked()){
            personal ="1";
        }
        if(ui->FunnyGenre_2->isChecked()){
            funny ="1";
        }
        if(ui->SadGenre_2->isChecked()){
            sad ="1";
        }
        if(ui->InspiringGenre_2->isChecked()){
            inspiring ="1";
        }
        if(ui->GeneralGenre_2->isChecked()){
            general ="1";
        }

        QSqlQuery qry;

        qry.prepare("INSERT INTO data (quote, author, favorite, movie, personal, funny, sad, general, inspiring) "
                      "VALUES (:quote, :author, :favorite, :movie, :personal, :funny, :sad, :general, :inspiring)");
        qry.bindValue(":quote", quote);
        qry.bindValue(":author", author);
        qry.bindValue(":favorite", favorite);
        //qry.bindValue(":book", book);
        qry.bindValue(":movie", movie);
        qry.bindValue(":personal", personal);
        qry.bindValue(":funny", funny);
        qry.bindValue(":sad", sad);
        qry.bindValue(":general", general);
        qry.bindValue(":inspiring", inspiring);

        if(qry.exec()){
            QMessageBox::information(this, "Inserted", "Data Inserted Successfully");
        }
        else{
            qDebug() << qry.lastError();
        }

    }

   database.close();

    ui->textBrowser_2->setPlainText(quote);
}

void Quotes::on_pushButton_3_clicked()
{
    QString quote = ui->plainTextEdit_2->toPlainText();
    QString displayMessage = "";
    QString book = "0";
    QString movie = "0";
    QString personal = "0";
    QString funny = "0";
    QString sad = "0";
    QString inspiring = "0";
    QString general = "0";


    if(ui->BookCheck->isChecked()){
        book = "1";
    }
    if(ui->MovieCheck->isChecked()){
        movie = "1";
    }
    if(ui->PersonalCheck->isChecked()){
        personal = "1";
    }
    if(ui->FunnyCheck->isChecked()){
        funny = "1";
    }
    if(ui->SadCheck->isChecked()){
        sad = "1";
    }
    if(ui->InspiringCheck->isChecked()){
        inspiring = "1";
    }
    if(ui->GeneralCheck->isChecked()){
        general = "1";
    }


    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("../QuoteManagerSQL/QuoteData.db");

    if(database.open()){
        QSqlQueryModel qry;
            qry.setQuery("SELECT * FROM data");

            for (int i = 0; i < qry.rowCount(); ++i) {
                if(qry.record(i).value("quote").toString().contains(quote,Qt::CaseInsensitive)){
                        if(book == "1"){
                            if(qry.record(i).value("book").toString() != "1"){
                                continue;
                            }
                        }
                        if(movie == "1"){
                            if(qry.record(i).value("movie").toString() != "1"){
                                continue;
                            }
                        }
                        if(personal == "1"){
                            if(qry.record(i).value("personal").toString() != "1"){
                                continue;
                            }
                        }
                        if(funny == "1"){
                            if(qry.record(i).value("funny").toString() != "1"){
                                continue;
                            }
                        }
                        if(sad == "1"){
                            if(qry.record(i).value("sad").toString() != "1"){
                                continue;
                            }
                        }
                        if(inspiring == "1"){
                            if(qry.record(i).value("inspiring").toString() != "1"){
                                continue;
                            }
                        }
                        if(general == "1"){
                            if(qry.record(i).value("general").toString() != "1"){
                                continue;
                            }
                        }

                        displayMessage += qry.record(i).value("quote").toString()+ "\n" + "            -" + qry.record(i).value("author").toString() + "\n" + "\n";
                    }
            }
        ui->QuoteResult->setText(displayMessage);
    }

}
