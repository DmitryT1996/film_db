#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class addrecord;
}

class addrecord : public QWidget
{
    Q_OBJECT

public:
    explicit addrecord(QWidget *parent = 0);
    void lol();
    ~addrecord();
private slots:
    void enableFindButton(const QString &);
    void on_add_clicked();
    void add_text();
    void no_add_text();
signals:
    void refresh_table();
private:
    Ui::addrecord *ui;
    QSqlQuery *query;
};

#endif // ADDRECORD_H
