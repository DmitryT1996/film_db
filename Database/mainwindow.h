#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QString>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QModelIndex>
#include <QVariant>
#include <addrecord.h>
#include <ui_addrecord.h>
#include <inform.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void update();
    ~MainWindow();

private slots:
    void on_add_clicked();
    void update_table();
    void on_reset_clicked();
    void on_search_clicked();
    void on_info_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    addrecord *add;
    Inform *inf;
    QSqlQuery *query;
};

#endif // MAINWINDOW_H
