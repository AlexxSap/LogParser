#ifndef LOGPARSER_H
#define LOGPARSER_H

#include <string>
#include <map>

class LogParser
{
private:
    struct TopLine
    {
        TopLine(const std::string &name,
                const unsigned &count)
            : name(name),
              count(count) {}

        bool operator < (const TopLine &other)
        {
            if(count == other.count)
            {
                return name < other.name;
            }
            return count < other.count;
        }

        std::string name;
        unsigned count;
    };
public:
    LogParser(const std::string &logFileName,
              const std::string &resultFileName,
              const int &topCount = 5);

    void make();

private:
    std::string parse();
    void parseLine(const std::string &buffer);
    std::string toString() const;
    void calc(const std::string &url);

private:
    std::string _logFileName;
    std::string _resultFileName;
    int _topCount;

    unsigned int _totalUrls;
    unsigned int _totalDomains;
    unsigned int _totalPaths;

    std::map<std::string, unsigned> _topDomains;
    std::map<std::string, unsigned> _topPaths;
};

#endif // LOGPARSER_H
