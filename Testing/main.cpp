#include <QTest>

#include "TLogParset.h"

int main()
{
    TLogParset tLogParser;
    return QTest::qExec(&tLogParser);
}
