#include "LogParser.h"

#include <iostream>
#include <fstream>
#include <regex>

LogParser::LogParser(const std::string &logFileName,
                     const std::string &resultFileName,
                     const int &topCount) :
    _logFileName(logFileName),
    _resultFileName(resultFileName),
    _topCount(topCount),
    _totalUrls(0),
    _totalDomains(0),
    _totalPaths(0)
{

}

void LogParser::make()
{
    const std::string dataString = parse();
    std::ofstream stream(_resultFileName);
    stream << dataString;
    stream.close();
}

std::string LogParser::parse()
{
    std::ifstream stream(_logFileName);
    std::string buffer;
    while(std::getline(stream, buffer))
    {
        parseLine(buffer);
    }
    stream.close();

    return toString();
}

void LogParser::parseLine(const std::string &buffer)
{
    const std::regex rx("http[s]?://([A-Za-z0-9\.\-]+)([^\?]+)");
    std::smatch match;
    if(std::regex_search(buffer, match, rx))
    {
        for(auto i = match.begin(); i != match.end(); i++)
        {
            calc(*i);
        }
    }
}

std::string LogParser::toString() const
{
    std::string result = "total urls " + std::to_string(_totalUrls)
            + ", domains " + std::to_string(_totalDomains)
            + ", paths " + std::to_string(_totalPaths)
            + "\n\n";

    return result;
}

void LogParser::calc(const std::string &url)
{
    std::cout << url << std::endl;
}
