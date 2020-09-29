#ifndef OPER_H
#define OPER_H



typedef struct op
{
    double(*f)(double,double);
}operat;




double sum(double a, double b);
double minus(double a, double b);
double divi(double a, double b);
//double modul(double a, double b);
double multi(double a, double b);





#endif // OPER_H
