#include "addrecord.h"
#include "ui_addrecord.h"

addrecord::addrecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addrecord)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(true);
    connect(ui->name, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
    connect(ui->year, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
    connect(ui->producer, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
    connect(ui->radioButton_2, SIGNAL(clicked(bool)), this, SLOT(no_add_text()));
    connect(ui->radioButton, SIGNAL(clicked(bool)), this, SLOT(add_text()));
}

addrecord::~addrecord()
{
    delete ui;
}

void addrecord::enableFindButton(const QString &)
{
    if(!ui->name->text().isEmpty() && !ui->year->text().isEmpty()
            && !ui->producer->text().isEmpty())
        ui->add->setEnabled(true);
}

void addrecord::on_add_clicked()
{
    if(ui->radioButton_2->isChecked())
        lol();
    if(ui->radioButton->isChecked())
    {
        lol();
        query = new QSqlQuery("SELECT COUNT(last_insert_rowid()) FROM films");
        query->next();
        int id = query->value(0).toInt();
        query->prepare("INSERT INTO information(id_name, inform) VALUES(:id_name, :inform)");
        query->bindValue(":id_name", id);
        query->bindValue(":inform", ui->textEdit->toPlainText());
        query->exec();
        delete query;
    }

}

void addrecord::lol()
{
    query = new QSqlQuery();
    QString _name = ui->name->text();
    QString _producer = ui->producer->text();

    query->prepare("SELECT name FROM films WHERE name = :_name");
    query->bindValue(":_name", _name);
    query->exec();
    if(query->next())
    {
        QMessageBox::warning(0,"Предупреждение", "Фильм с таким названием уже существует");
        return;
        delete query;
    }

    query->prepare("SELECT producer FROM films WHERE producer = :_producer");
    query->bindValue(":_producer", _producer);
    query->exec();
    if(!query->next())
    {
        int n = QMessageBox::warning(0,"Предупреждение", "Режиссер не найден в БД. Добавить его и закончить добавление фильма?", "Да", "Нет",
                                     QString(), 0, 1 );
        if(!n)
        {
            query->prepare("INSERT INTO films(name, year, rating, producer) VALUES(:name, :year, :rating, :producer)");
            query->bindValue(":name",ui->name->text());
            query->bindValue(":year",ui->year->text());
            query->bindValue(":rating",ui->rating->text());
            query->bindValue(":producer",ui->producer->text());
            query->exec();
            emit refresh_table();
            return;
        }
        return;
    }
    query->prepare("INSERT INTO films(name, year, rating, producer) VALUES(:name, :year, :rating, :producer)");
    query->bindValue(":name",ui->name->text());
    query->bindValue(":year",ui->year->text());
    query->bindValue(":rating",ui->rating->text());
    query->bindValue(":producer",ui->producer->text());
    query->exec();
    emit refresh_table();
}

void addrecord::no_add_text()
{
    ui->textEdit->clear();
    ui->textEdit->setEnabled(false);
}

void addrecord::add_text()
{
    ui->textEdit->setEnabled(true);
}
