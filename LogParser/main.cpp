#include <iostream>
#include "LogParser.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::string log;
    std::string parsed;
    unsigned count = 5;

    if(argc == 3)
    {
        log = argv[1];
        parsed = argv[2];
    }
    else if(argc == 5)
    {
        if(argv[1] == "-n")
        {
            count = atoi(argv[2]);
        }
        log = argv[3];
        parsed = argv[4];
    }
    else
    {
        std::cout << "wrong parameters count" << std::endl;
        return 1;
    }

    if(log.empty())
    {
        std::cout << "cant recognize log file name" << std::endl;
        return 2;
    }

    if(parsed.empty())
    {
        std::cout << "cant recognize result file name" << std::endl;
        return 3;
    }

    if(LogParser(log, parsed, count).make())
    {
        std::cout << "done!" << std::endl;
    }
    else
    {
        std::cout << "cant parsed file " << log << std::endl;
    }

    return 0;
}
