#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <string>
#include <map>
#include <unordered_set>

class LogParser
{

public:
    LogParser(const std::string &logFileName,
              const std::string &resultFileName,
              const int &topCount = 5);
    bool make();

private:
    std::string parse();
    void parseLine(const std::string &buffer);
    std::string toString() const;
    std::string getTopString(const std::map<std::string, unsigned> &data) const;

private:
    std::string _logFileName;
    std::string _resultFileName;
    unsigned _topCount;

    std::unordered_set<std::string> _urls;

    std::map<std::string, unsigned> _topDomains;
    std::map<std::string, unsigned> _topPaths;
};

#endif // LOGPARSER_H
