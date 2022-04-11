#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "Tokenparser.hpp"

//дефолтные функции приведены для примера работы

int DigitTokenCnt = 0;
int StrTokenCnt = 0;

void  DefaultStartF()
{
    std::cout << "Start parsing" << std::endl;
}
void DefaultEndF()
{
    std::cout << "Finished parsing" << std::endl;
}
int DefaultDigitF(uint64_t num)
{
    std::cout << "got digit token " << num << std::endl;
    DigitTokenCnt++;
    return DigitTokenCnt;
}
int  DefaultStrF(std::string line)
{
    std::cout << "got str token " << line << std::endl;
    StrTokenCnt++;
    return StrTokenCnt;
}

int main()
{
    TokenParser parser;
    std::string line;
    parser.SetStartCallback(DefaultStartF);
    parser.SetEndCallback(DefaultEndF);
    parser.SetDigitTokenCallback(DefaultDigitF);
    parser.SetStrTokenCallback(DefaultStrF);
    while (std::getline(std::cin, line))
    {
        parser.Parse(line);
    } 
    return 0;
}