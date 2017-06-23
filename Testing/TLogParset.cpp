#include "TLogParset.h"

#include <QtTest>
#include <QFile>
#include <QTextStream>

TLogParset::TLogParset(QObject *parent) : QObject(parent)
{

}

void TLogParset::TestParseAndCalc_data()
{
    QTest::addColumn<QString>("file");
    QTest::addColumn<int>("topCount");
    QTest::addColumn<QString>("expected");

    QTest::newRow("empty") << QString()
                           << 0
                           << QString();

    QTest::newRow("simple-1") << "GET https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                              << 5
                              << "total urls 1, domains 1, paths 1\n\n"
                                 "top domains\n"
                                 "1 en.wikipedia.org\n\n"
                                 "top paths\n"
                                 "1 /w/index.php\n";

    QTest::newRow("simple-2") << "ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET "
                                 "https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                                 "	NONE/wikimedia - https://en.wikipedia.org/wiki/Kirschkuchen	- Mozilla/5.0 "
                                 "(Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 "
                                 "Safari/537.36 en-US,en;q=0.8 - sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 "
                                 "0 1.2.3.4 TCP_MEM_HIT/200\n"
                              << 5
                              << "total urls 2, domains 1, paths 2\n\n"
                                 "top domains\n"
                                 "2 en.wikipedia.org\n\n"
                                 "top paths\n"
                                 "1 /w/index.php\n"
                                 "1 /wiki/Kirschkuchen\n";


    QTest::newRow("simple-3") << "ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET "
                                 "https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                                 "	NONE/wikimedia - https://en.wikipedia.org/wiki/Kirschkuchen	- Mozilla/5.0 "
                                 "(Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 "
                                 "Safari/537.36 en-US,en;q=0.8 - sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 "
                                 "0 1.2.3.4 TCP_MEM_HIT/200\n\n"
                                 "ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET "
                                 "https://en.wikkpedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                                 "	NONE/wikimedia - https://en.wikkpedia.org/wiki/Kirschkuchen	- Mozilla/5.0 "
                                 "(Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 "
                                 "Safari/537.36 en-US,en;q=0.8 - sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 "
                                 "0 1.2.3.4 TCP_MEM_HIT/200\n"
                              << 5
                              << "total urls 4, domains 2, paths 2\n\n"
                                 "top domains\n"
                                 "2 en.wikipedia.org\n"
                                 "2 en.wikkpedia.org\n\n"
                                 "top paths\n"
                                 "2 /w/index.php\n"
                                 "2 /wiki/Kirschkuchen\n";

    QTest::newRow("simple-4") << "ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET "
                                 "https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                                 "	NONE/wikimedia - https://en.wikipedia.org/wiki/Kirschkuchen	- Mozilla/5.0 "
                                 "(Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 "
                                 "Safari/537.36 en-US,en;q=0.8 - sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 "
                                 "0 1.2.3.4 TCP_MEM_HIT/200\n\n"
                                 "ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET "
                                 "https://en.wikkpedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                                 "	NONE/wikimedia - https://en.wikkpedia.org/wiki/Kirschkuchen	- Mozilla/5.0 "
                                 "(Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 "
                                 "Safari/537.36 en-US,en;q=0.8 - sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 "
                                 "0 1.2.3.4 TCP_MEM_HIT/200\n"
                              << 1
                              << "total urls 4, domains 2, paths 2\n\n"
                                 "top domains\n"
                                 "2 en.wikipedia.org\n\n"
                                 "top paths\n"
                                 "2 /w/index.php\n";

    QTest::newRow("from-case-1") << "ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET "
                                    "https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                                    "	NONE/wikimedia - https://en.wikipedia.org/wiki/Kirschkuchen	- Mozilla/5.0 "
                                    "(Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 "
                                    "Safari/537.36 en-US,en;q=0.8 - sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 "
                                    "0 1.2.3.4 TCP_MEM_HIT/200\n"
                                    "13208 GET http://en.wikipedia.org/wiki/Main_Page	NONE/- text/html - - "
                                    "Mozilla/4.0%20(compatible;%20MSIE%206.0;%20Windows%20NT%205.1;%20.NET%20CLR%201."
                                    "1.4322) en-US -\n"
                                    "cp1048.eqiad.wmnet 8883921154 2013-09-26T06:28:16 0.001308203 1.2.3.4 hit/200 "
                                    "52362 GET http://en.wikipedia.org/wiki/Free_software	- text/html https://w"
                                    "ww.google.com/search?q=free+software	4.3.2.1 Mozilla/5.0 (Windows NT 6.1) Apple"
                                    "WebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.76 Safari/537.36 en-US,en;q="
                                    "0.8 -"
                                 << 5
                                 << "total urls 5, domains 2, paths 5\n\n"
                                    "top domains\n"
                                    "4 en.wikipedia.org\n"
                                    "1 www.google.com\n\n"
                                    "top paths\n"
                                    "1 /search\n"
                                    "1 /w/index.php\n"
                                    "1 /wiki/Free_software\n"
                                    "1 /wiki/Kirschkuchen\n"
                                    "1 /wiki/Main_Page\n";

    QTest::newRow("from-case-2") << "cp1048.eqiad.wmnet 8883921154 2013-09-26T06:28:16 0.001308203 1.2.3.4 hit/200 "
                                    "52362 GET http://en.wikipedia.org/wiki/Free_software	- text/html https://w"
                                    "ww.google.com/search?q=free+software	4.3.2.1 Mozilla/5.0 (Windows NT 6.1) Apple"
                                    "WebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.76 Safari/537.36 en-US,en;q="
                                    "0.8 -"
                                    "13208 GET http://en.wikipedia.org/wiki/Main_Page	NONE/- text/html - - "
                                    "Mozilla/4.0%20(compatible;%20MSIE%206.0;%20Windows%20NT%205.1;%20.NET%20CLR%201."
                                    "1.4322) en-US -\n"
                                    "ssl1001 129960997 2014-01-21T08:36:33.097 0.426 1.2.3.4 -/200 12324 GET "
                                    "https://en.wikipedia.org/w/index.php?title=Kirschkuchen&action=edit&section=8"
                                    "	NONE/wikimedia - https://en.wikipedia.org/wiki/Kirschkuchen	- Mozilla/5.0 "
                                    "(Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1700.76 "
                                    "Safari/537.36 en-US,en;q=0.8 - sq18.wikimedia.org 1715898 2010-12-01T21:57:22.331 "
                                    "0 1.2.3.4 TCP_MEM_HIT/200\n"
                                 << 5
                                 << "total urls 5, domains 2, paths 5\n\n"
                                    "top domains\n"
                                    "4 en.wikipedia.org\n"
                                    "1 www.google.com\n\n"
                                    "top paths\n"
                                    "1 /search\n"
                                    "1 /w/index.php\n"
                                    "1 /wiki/Free_software\n"
                                    "1 /wiki/Kirschkuchen\n"
                                    "1 /wiki/Main_Page\n";
}

void TLogParset::TestParseAndCalc()
{
    QFETCH(QString, file);
    QFETCH(int, topCount);
    QFETCH(QString, expected);

    const QString fileName = "Test" + QString(QTest::currentDataTag()) + QString(QTest::currentTestFunction()) + "_log.txt";
    const QString newFileName = "Test" + QString(QTest::currentDataTag()) + QString(QTest::currentTestFunction()) + "_res.txt";

    deleteFile(fileName);
    deleteFile(newFileName);

    createFile(fileName, file);

    LogParser(fileName.toStdString(), newFileName.toStdString(), topCount).make();

    QVERIFY(compare(newFileName, expected));
}

void TLogParset::deleteFile(const QString &fileName)
{
    if(QFile::exists(fileName))
    {
        if(!QFile::remove(fileName))
        {
            QFAIL("cannot delete file");
        }
    }

}

void TLogParset::createFile(const QString &fileName,
                            const QString &data)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        stream << data;
        stream.flush();
    }
    file.close();
}

bool TLogParset::compare(const QString &fileName,
                         const QString &data)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        const QString fileData = stream.readAll();

        return fileData == data;

    }
    file.close();

    return data.isEmpty();
}
