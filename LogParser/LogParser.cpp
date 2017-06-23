#include "LogParser.h"

#include <iostream>
#include <fstream>
#include <regex>

LogParser::LogParser(const std::string &logFileName,
                     const std::string &resultFileName,
                     const int &topCount) :
    _logFileName(logFileName),
    _resultFileName(resultFileName),
    _topCount(topCount)
{

}

bool LogParser::make()
{
    const std::string dataString = parse();

    if(dataString.empty())
    {
        return false;
    }
    std::ofstream stream(_resultFileName);
    stream << dataString;
    stream.close();

    return true;
}

std::string LogParser::parse()
{
    std::ifstream stream(_logFileName);
    std::string buffer;

    bool empty = true;
    while(std::getline(stream, buffer))
    {
        empty = false;
        parseLine(buffer);
    }
    stream.close();

    if(empty)
    {
        return std::string();
    }

    return toString();
}

void LogParser::parseLine(const std::string &buffer)
{
    const std::regex rx("http[s]?://([A-Za-z0-9\\.\\-]+)([a-zA-Z0-9\\.\\,\\/\\+\\_]+)");
    std::smatch match;

    std::string local = buffer;
    while(std::regex_search(local, match, rx))
    {
        for(unsigned i = 0; i < match.size(); i += 3)
        {
            _urls_.insert(match[i]);
            _topDomains[match[i + 1]]++;
            _topPaths[match[i + 2]]++;
        }
        local = match.suffix().str();
    }
}

std::string LogParser::toString() const
{
    std::string result;

    result += "total urls " + std::to_string(_urls_.size());
    result += ", domains " + std::to_string(_topDomains.size());
    result += ", paths " + std::to_string(_topPaths.size());
    result += "\n\n";

    result += "top domains\n" + getTopString(_topDomains) + "\n";
    result += "top paths\n" + getTopString(_topPaths);

    return result;
}

std::string LogParser::getTopString(const std::map<std::string, unsigned> &data) const
{
    std::string result;

    unsigned counter = 0;
    for(const auto& item : data)
    {
        result += std::to_string(item.second) + " " + item.first + "\n";

        ++counter;
        if(counter == _topCount)
        {
            break;
        }
    }

    return result;
}
