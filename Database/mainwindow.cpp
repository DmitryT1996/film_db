#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QModelIndex>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(729,343);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/sqlite/films.db");
    if(!db.open())
    {
        QMessageBox::critical(0,"Error", "No connection");
        exit(1);
    }
    update();
}

void MainWindow::update()
{
    model = new QSqlTableModel(this, db);
    model->setTable("films");
    model->select();
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Режиссер");
    model->setHeaderData(3, Qt::Horizontal, "Год");
    model->setHeaderData(4, Qt::Horizontal, "Рейтинг");
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->resizeColumnToContents(2);

}

MainWindow::~MainWindow()
{
    db.close();
    delete inf;
    delete add;
    delete ui;
}


void MainWindow::on_add_clicked()
{
    add = new addrecord();
    connect(add, SIGNAL(refresh_table()), this, SLOT(update_table()));
    add->show();
}

void MainWindow::update_table()
{
    update();
}


void MainWindow::on_reset_clicked()
{
    update();
    ui->film->setText("");
    ui->year->setText("");
    ui->rating->setText("");
}

void MainWindow::on_search_clicked()
{
    model->setFilter(QString("name = '%1' OR year = '%2' OR rating = '%3'")
                     .arg(ui->film->text(), ui->year->text(), ui->rating->text()));
    model->select();
}

void MainWindow::on_info_clicked()
{
    inf = new Inform();
    int id = ui->tableView->currentIndex().row();
    int name = ui->tableView->currentIndex().row();

    QModelIndex myId, MyName;

    myId = ui->tableView->model()->index( id, 0, QModelIndex());
    MyName = ui->tableView->model()->index(name, 1, QModelIndex());

    QVariant myData_id = ui->tableView->model()->data(myId).toInt();
    QVariant myData_name = ui->tableView->model()->data(MyName);

    id = myData_id.toInt();
    QString lol = myData_name.toString();

    inf->inf(static_cast<int&&> (id), static_cast<QString&&> (lol));
    inf->show();
}
