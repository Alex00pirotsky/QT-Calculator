#include "count.h"
#include "resolver.h"

Count::Count(QObject *parent) : QObject(parent)
{

}
void Count::Set_root(QVector<QString> new_root)
{
    this->root = new_root;
}
QVector<QString> Count::Get_resolve()
{
    return root;
}
bool Count::im_what_you(QString val, QString opt)
{
    if(opt[0] == 'S' || opt[0] == 's')
        return(val.contains(QChar('+')) || val.contains(QChar('-')) || val.contains(QChar('/')) || val.contains(QChar('x')));
    if(opt[0] == 'G' || opt[0] == 'g')
        return(val.contains(QChar('/')) || val.contains(QChar('x')));
    if(opt[0] == 'D' || opt[0] == 'd')
        return(val.length() > 1 || ( val.contains(QChar('-')) && val.length() > 1) || (val <= '9' && val >= '0'));

    return false;
}
void Count::put_all_skob(QString option)
{
    QVector<QString> tmp;
    int n;
    n = root.length();

    for(int i = 0; i < n; i++)
    {
        if(i + 2 < n && im_what_you(root[i + 1], option))
        {
            if(im_what_you(root[i], "Digits") && im_what_you(root[i + 2], "Digits"))
            {
                root.insert(i, "(");
                root.insert(i + 4, ")");
                n -= 4;
            }
        }
    }
}
void Count::cleaner()
{
    int n;
    n = root.length();
    for(int i = 0; i < n; i++)
    {
        if(i + 2 < root.length() && root[i].contains('(') && im_what_you(root[i + 1], "Digit") && root[i + 2].contains(')'))
        {
            root.remove(i);
            root.remove(i + 1);
            n -= 2;
        }
    }
}
void Count::open_break()
{
    double cont;
    int n;
    n = root.length();
    for(int i = 0; i < n; i++)
    {
        if(i + 4 < n)
        {
            if(root[i].contains(QChar('(')) && root[i + 4].contains(QChar(')')))
            {
                if(root[i+2].contains('/') && root[i + 3] == "0")
                {
                    root.clear();
                    root.append("DIVISION ZERO...");
                    break;
                }
                cont = may[root[i + 2]].f(root[i + 1].toDouble(), root[i + 3].toDouble());
                root[i] = QString::number(cont);
                root.remove(i+1, 4);
                n -= 5;
            }
        }
    }
}
void Count::add_mult()
{
    int n;
    n = root.length();
    for(int i = 0; i < n; i++)
    {
        if(i + 1 < n)
        {
            if((im_what_you(root[i], "Digit") && root[i+1].contains("(")) || (im_what_you(root[i+1], "Digit") && root[i].contains(")")))
            {
                root.insert(i + 1, "x");
                n += 1;
            }
        }
    }
}
void Count::what_extra()
{
    int counter;
    counter = root.count("(") - root.count(")");
    if(counter < 0)
    {
        root.remove(root.indexOf(")"));
        what_extra();
    }
    if(counter > 0)
    {
        root.remove(root.indexOf("("));
        what_extra();
    }
}
void Count::make_mess()
{
    if(root.length() > 2)
    {
        if(root.count("x") > 0 || root.count("/") > 0)
            put_all_skob("Greater_sighn");
        else
            put_all_skob("Sighn_all");

        open_break();
        cleaner();
        make_mess();
    }
    else if(root.length() == 2)
        root.pop_back();
}
void Count::solve()
{
    add_mult();
    what_extra();
    make_mess();
}



//if(i + 1 < root.length() && i > 0 && root[i - 1] != "(" && (root[i + 1] == ("x") || root[i + 1] == ("/")))
//    tmp.append("(");
//tmp.append(root[i]);
//if(i > 0 && i + 1 < root.length() && root[i + 1] != ")" && (root[i - 1] == ("x") || root[i - 1] == ("/")))
//    tmp.append(")");
