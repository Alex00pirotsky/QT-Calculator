#ifndef COUNT_H
#define COUNT_H

#include <QObject>

class Count : public QObject
{
    Q_OBJECT
private:
    QVector<QString> root;
    bool im_what_you(QString val, QString opt);
    void put_all_skob(QString option);
    void open_break();
    void cleaner();
    void what_extra();
    void add_mult();
    void make_mess();
    
public:
    explicit Count(QObject *parent = nullptr);
    void Set_root(QVector<QString> new_root);
    QVector<QString> Get_resolve();
    void solve();
signals:

};

#endif // COUNT_H
