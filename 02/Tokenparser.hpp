#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>

using FooPtrVoid = std::function<void()>;
using FooPtrStr = std::function<int(std :: string)>;
using FooPtrInt = std::function<int(uint64_t)>;

class TokenParser
{
public:
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(FooPtrVoid f);

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(FooPtrVoid f);

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(FooPtrInt f);
   
    // Устанавливаем callback-функцию для обработки строк.
    void SetStrTokenCallback(FooPtrStr f);

    void Parse(const std::string &);
    // возвращает 1, если токен цифровой
    bool IsDigitToken(std::string line);
    
    FooPtrVoid StartF;
    FooPtrVoid EndF;
    FooPtrInt DigitF;
    FooPtrStr StrF;
};

