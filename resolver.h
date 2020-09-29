#ifndef RESOLVER_H
#define RESOLVER_H
#include "oper.h"
#include <QMap>




operat operations[] =
{
  {&sum},
  {&minus},
  {&divi},
  {&multi}
};


QMap<QString, operat> may =
{
    {"+", operations[0]},
    {"-", operations[1]},
    {"/", operations[2]},
    {"x", operations[3]}
};


#endif // RESOLVER_H
