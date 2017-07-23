#include "inform.h"
#include "ui_inform.h"

Inform::Inform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Inform)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

void Inform::inf(int &&id, QString &&name)
{
    query = new QSqlQuery();
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->append("Краткое описание фильма: " + name + "\n");
    ui->textEdit->setAlignment(Qt::AlignAbsolute);
    query->prepare("SELECT inform FROM information WHERE id_name = :id");
    query->bindValue(":id", id);
    query->exec();
    while (query->next())
    {
        ui->textEdit->append(query->value(0).toString());
        break;
    }
}

Inform::~Inform()
{
    delete query;
    delete ui;
}
