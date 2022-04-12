#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "Tokenparser.hpp"

void TokenParser::SetStartCallback(FooPtrVoid f)
{
    this->StartF = f;
}
void TokenParser::SetEndCallback(FooPtrVoid f)
{
    this->EndF = f;
}
void TokenParser::SetDigitTokenCallback(FooPtrInt f)
{
    this->DigitF = f;
}

void TokenParser::SetStrTokenCallback(FooPtrStr f)
{
    this->StrF = f;
}

bool TokenParser::IsDigitToken(std::string line)
{
    int digit_flag = 0;
    int str_flag = 0;
    for (char c : line)
    {
        if (c <= '9' && c >= '0') 
            digit_flag = 1;
        else
            str_flag = 1;
    }
    if (digit_flag && !str_flag)
        return true;
    else
        return false;
}




void TokenParser :: Parse(const std::string & line)
{
    if (StartF)
        StartF();
    int start = 0;
    int stop = 0;
    unsigned long long i = 0;
    // проходим мимо возможных пробелов и символов табуляции в начале

    for (; i < line.size(); i++)
    {
        while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\0')
        {
			i++;
		}
        start = i;
        break;
    }  
    // обрабатываем оставшуюся часть строки
    for (; i < line.size(); i++)    
    {
        while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'  && line[i] != '\0' && i < line.size())
        {
			i++;
		}
        stop = i;
        std::string token = line.substr(start, stop-start);
        if (token.size() > 0)
        {
            if (IsDigitToken(token))
            {
                if(DigitF)
                {   
                    try
                    {
                        DigitF(std::stoull(token));
                    }
                    catch(const std::exception& e)
                    {
                        if(StrF)
                        {
                            StrF(token);
                        }
                    }
                    
                   
                }
            }
            else
            {
                if(StrF)
                {
                    StrF(token);
                }
            }
        }
        start = stop + 1;
    }
    if (EndF)
        EndF(); 
}
