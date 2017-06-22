#ifndef TLOGPARSET_H
#define TLOGPARSET_H

#include <QObject>
#include "../LogParser/LogParser.h"

class TLogParset : public QObject
{
    Q_OBJECT
public:
    explicit TLogParset(QObject *parent = nullptr);

private slots:
    void TestParseAndCalc_data();
    void TestParseAndCalc();

protected:
    void deleteFile(const QString &fileName);
    void createFile(const QString &fileName, const QString &data);
    bool compare(const QString &fileName, const QString &data);
};

#endif // TLOGPARSET_H
