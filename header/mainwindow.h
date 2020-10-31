#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "count.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void pr_vect();
    int skob = 0;


private:
    Ui::MainWindow *ui;
    QVector<QString> root;
    Count resolver;
    void pr_h();

private slots:
    void digits_number();
    void on_push_neg_clicked();
    void on_push_dot_clicked();
    void on_push_C_clicked();
    void push_sign();
    void on_pushButton_LS_clicked();
    void on_pushButton_RS_clicked();
    void on_pushButton_eq_clicked();
};
#endif // MAINWINDOW_H
