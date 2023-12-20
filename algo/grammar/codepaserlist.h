#ifndef CODEPASERLIST_H
#define CODEPASERLIST_H
#include <QList>
#include "codeparser.h"
#include "qlist.h"

class CodePaserList: public QList<CodeParser*>
{
public:
    CodePaserList();
};

#endif // CODEPASERLIST_H
