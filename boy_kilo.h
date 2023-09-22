#ifndef BOY_KILO_H
#define BOY_KILO_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSqlQuery>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class boy_kilo; }
QT_END_NAMESPACE

class boy_kilo : public QMainWindow
{
    Q_OBJECT

public:
    boy_kilo(QWidget *parent = nullptr);
    ~boy_kilo();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::boy_kilo *ui;
};
#endif // BOY_KILO_H
