#pragma once

#include <iostream>
#include <string>
#include <functional>

class TokenParser
{
public:
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(std :: function<void()>f);

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(std :: function<void()>f);

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(std :: function<int(std::string)> f);
   
    // Устанавливаем callback-функцию для обработки строк.
    void SetStrTokenCallback(std :: function<int(std::string)> f);

    void Parse(const std::string &);
    // возвращает 1, если токен цифровой
    bool IsDigitToken(std :: string line);
    
    std :: function<void()> StartF;
    std :: function<void()> EndF;
    std :: function<int(std::string)> DigitF;
    std :: function<int(std::string)> StrF;
};

