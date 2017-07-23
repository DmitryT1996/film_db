#ifndef INFORM_H
#define INFORM_H

#include <QWidget>
#include <QSqlQuery>
#include <QString>

namespace Ui {
class Inform;
}

class Inform : public QWidget
{
    Q_OBJECT
public:
    explicit Inform(QWidget *parent = 0);
    void inf(int &&id, QString &&name);
    ~Inform();
private:
    Ui::Inform *ui;
    QSqlQuery *query;
};

#endif // INFORM_H
