#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include<QMessageBox>
#include<QTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->result_show->setGeometry(0,75,395,90);
    ui->history_show->setGeometry(0,0,400,110);
    ui ->skob_podsk->hide();


    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_number()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_number()));


    connect(ui->push_plus,  SIGNAL(clicked()), this,SLOT(push_sign()));
    connect(ui->push_minus, SIGNAL(clicked()), this,SLOT(push_sign()));
    connect(ui->push_X,     SIGNAL(clicked()), this,SLOT(push_sign()));
    connect(ui->push_divi,  SIGNAL(clicked()), this,SLOT(push_sign()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pr_vect()
{
    QString new_res;

    for (int i = 0; i < root.size() ;i++ )
    {
        new_res.append(root[i]);
        new_res.append(" ");
    }

    ui->result_show->setText(new_res);
}
void MainWindow::pr_h()
{
    resolver.Set_root(root);
    resolver.solve();
    ui->history_show->setText(resolver.Get_resolve()[0]);
}

void MainWindow::digits_number()
{
    QPushButton *button;
    int i;
    button = (QPushButton *)sender();
    i = root.size() - 1;
    if(i >= 0)
    {
        if(root[i].length() > 1 || (root[i] <= '9' && root[i] >= '0'))
           root[i].push_back(button->text());
        else if(i > 0 && root[i] == '-' && root[i - 1] == '(')
            root[i].push_back(button->text());
        else
            root.append(button->text());
    }
    else
        root.append(button->text());

    pr_vect();
    //pr_h();

}
void MainWindow::on_push_neg_clicked() // TODO 3 + (3-6)(-
{

    int i;
    i = root.size();
    if(i > 0 && (root[i - 1][0] == '-' || root[i - 1].length() > 1 || (root[i - 1] <= '9' && root[i - 1] >= '0')))
    {
        if(i > 1 && root[i - 2] == '(' && root[i - 1][0] == '-')
        {
            skob--;
            root[i - 1].remove('-');
            root[i - 2] = root[i - 1];
            root.pop_back();
            if(i > 2 && (root[i - 3].length() > 1 || (root[i - 3] <= '9' && root[i - 3] >= '0')))
                root.insert(i - 2, "x");
        }
        else if(i > 1 && root[i - 2] != '(')
        {
            skob++;
            root.insert(i - 1, "(");
            root[i].push_front("-");
        }
        else if(i > 1 && root[i - 2] == '(' && root[i - 1][0] != '-')
        {
            skob++;
            root[i-1].push_front("-");
        }
    }
    else
    {
        skob++;
        root.append("(");
        root.append("-");
    }

    (skob == 0) ? ui->skob_podsk->hide() : ui->skob_podsk->show();
    pr_vect();
}
void MainWindow::on_push_dot_clicked()
{
    int i;
    i = root.size() - 1;
    if(i >= 0 && root[i].count('.') == 0)
    {
        root[i].push_back('.');
        pr_vect();
    }
}
void MainWindow::on_push_C_clicked()
{
    root.pop_back();
    (skob == 0) ? ui->skob_podsk->hide() : ui->skob_podsk->show();
    pr_vect();
}
void MainWindow::push_sign()
{
    QPushButton *button;
    int i;
    button = (QPushButton *)sender();
    i = root.size() - 1;
    if(i >= 0)
    {
        if(root[i] == ')' || root[i].length() > 1 || (root[i] <= '9' && root[i] >= '0'))
            root.append(button->text());
        else if(root[i] == 'x' || root[i] == '/' || root[i] == '+' || root[i] == '-' )
            root[i] = button->text();
        pr_vect();
    }
}


//void MainWindow::on_push_C_pressed()
//{
//    QTime t;
//    t.start();
//    if(t.elapsed() > 10)
//    {
//        root.clear();
//    }
//        pr_vect();
//}

void MainWindow::on_pushButton_LS_clicked()
{
    root.append(QChar('('));
    skob += 1;
    ui ->skob_podsk->show();
    pr_vect();
}

void MainWindow::on_pushButton_RS_clicked()
{
    int i;
    i = root.size() - 1;
    if(i > 0 && skob > 0 && root[i - 1] != "(")
    {
        root.append(QChar(')'));
        skob -= 1;
    }
    if(skob <= 0)
        ui ->skob_podsk->hide();
    pr_vect();
}

void MainWindow::on_pushButton_eq_clicked()
{
    resolver.Set_root(root);
    resolver.solve();
    root = resolver.Get_resolve();
    skob = 0;
    ui->skob_podsk->hide();
    ui->history_show->setText(ui->result_show->text() + "= " + root[0] + " ");
    pr_vect();
}
