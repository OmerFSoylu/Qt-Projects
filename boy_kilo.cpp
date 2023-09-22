#include "boy_kilo.h"
#include "qlabel.h"
#include "ui_boy_kilo.h"


boy_kilo::boy_kilo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::boy_kilo)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setDatabaseName("connectionSQL");
    db.setUserName("root");
    db.setPassword("Hewalius1");

    if(!db.open())
    {
        QMessageBox::information(this, "Connection Failed", "Connection Failed");
    }

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("boy_kilo");

    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->resize(300, 600);

    model->select();
    tableView->show();

}

boy_kilo::~boy_kilo()
{
    delete ui;
}




void boy_kilo::on_pushButton_clicked()
{

    bool ok1, ok2;
    int boyValue = ui->boyLineEdit->text().toInt(&ok1);
    int kiloValue = ui->kiloLineEdit->text().toInt(&ok2);

    // Validate if both lineEdits have valid integer values
    if (!ok1 || !ok2)
    {

        QMessageBox::information(this, "Error", "Lütfen boy ve kilo değerlerini giriniz");
        return;
    }

    QSqlQuery duplicateCheckQuery;
    duplicateCheckQuery.prepare("SELECT COUNT(*) FROM boy_kilo WHERE boy = :boy AND kilo = :kilo");
    duplicateCheckQuery.bindValue(":boy", boyValue);
    duplicateCheckQuery.bindValue(":kilo", kiloValue);

    if (duplicateCheckQuery.exec() && duplicateCheckQuery.next())
    {
        int recordCount = duplicateCheckQuery.value(0).toInt();
        if (recordCount > 0)
        {
            QMessageBox::information(this, "Error", "Please enter an unique height and weight pair");
            return;
        }
    }


    QSqlQuery query;
    query.prepare("INSERT INTO boy_kilo (boy,kilo) VALUES (:boy, :kilo)" );
    query.bindValue(":boy", boyValue);
    query.bindValue(":kilo", kiloValue);

    if (query.exec()) {
        qDebug() << "Insertion successful";
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable("boy_kilo");

        QTableView *tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->resize(300, 600);

        model->select();
        tableView->show();
    } else {
        qDebug() << "Error inserting record:" << query.lastError().text();
    }

}





void boy_kilo::on_pushButton_2_clicked()
{
    bool ok1, ok2;
    int boyValue = ui->boyLineEdit->text().toInt(&ok1);
    int kiloValue = ui->kiloLineEdit->text().toInt(&ok2);

    // Validate if both lineEdits have valid integer values
    if (!ok1 || !ok2)
    {

        QMessageBox::information(this, "Error", "Lütfen boy ve kilo değerlerini giriniz");
        return;
    }

    QSqlQuery CheckQuery;
    CheckQuery.prepare("SELECT COUNT(*) FROM boy_kilo WHERE boy = :boy AND kilo = :kilo");
    CheckQuery.bindValue(":boy", boyValue);
    CheckQuery.bindValue(":kilo", kiloValue);

    if (CheckQuery.exec() && CheckQuery.next())
    {
        int recordCount = CheckQuery.value(0).toInt();
        if (recordCount == 0)
        {
            QMessageBox::information(this, "Error", "The record does not exist");
            return;
        }
    }

    QSqlQuery query;
    query.prepare("DELETE FROM boy_kilo WHERE boy = ? AND kilo = ?");
    query.addBindValue(boyValue);
    query.addBindValue(kiloValue);

    // Execute the query
    if (query.exec())
    {
        QMessageBox::information(this, "Success", "The record is deleted");
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable("boy_kilo");

        QTableView *tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->resize(300, 600);

        model->select();
        tableView->show();
    }
    else
    {
        QMessageBox::information(this, "Error", "The record does not exist");
        return;
    }

}

