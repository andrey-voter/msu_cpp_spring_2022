#include <iostream>
#include <functional>
#include <string>
#include <gtest/gtest.h>
#include "Tokenparser.hpp"

class TestTokenParser : public ::testing::Test 
{
protected:
	TokenParser parser;
	void SetUp() 
    {
        std::cout << "SetUp" << std::endl;
	}
	void TearDown() 
    {
        std::cout << "TearDown" << std::endl;
	}
};


int DigitF (std::vector<uint64_t> *v, uint64_t num)
{
    (*v).push_back(num);
    return 0;
}
int StrF (std::vector<std::string> *v, std::string line)
{
    (*v).push_back(line);
    return 0;
}


TEST_F(TestTokenParser, TestIsDigitToken) 
{
    std::string test_string = "";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    
    test_string = "11111111111111111111111111111111";
    ASSERT_TRUE(parser.IsDigitToken(test_string));
    //пробел посередине
    test_string = "1111111111 2222222222222222";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    //еще немного вариантов с пробелами
    test_string = "1111111 ";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    
    test_string = " 1111111";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    //проверим, как работает с символом табуляции в начале
    test_string = "     1111111";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    //а теперь в конце
    test_string = "1111111      ";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    //добавим другие символы
    test_string = "a111111111";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "11111111111a";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    
    test_string = "aaaaaaaaa";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "AAAAAAA";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "vifeommivocm";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "EFVMOVEROVM";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "         ";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "1";
    ASSERT_TRUE(parser.IsDigitToken(test_string));

    test_string = "a";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "1331132asdadasd";
    ASSERT_FALSE(parser.IsDigitToken(test_string));

    test_string = "18446744073709551616";
    ASSERT_TRUE(parser.IsDigitToken(test_string));

    test_string = "18446744073709551615";
    ASSERT_TRUE(parser.IsDigitToken(test_string));

    test_string = "36893488147419103232";
    ASSERT_TRUE(parser.IsDigitToken(test_string));
}

TEST_F(TestTokenParser, TestNullptrCallback) 
{
    std::string test_string = "3233434fvfvfvfvvf";
    parser.SetStartCallback(nullptr);
    parser.SetEndCallback(nullptr);
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStrTokenCallback(nullptr);
    ASSERT_EQ(parser.StrF, nullptr);
    ASSERT_EQ(parser.DigitF, nullptr);
    ASSERT_EQ(parser.StartF, nullptr);
    ASSERT_EQ(parser.EndF, nullptr);
    parser.Parse(test_string);
}


TEST_F(TestTokenParser, TestCallbackUseOrder) 
{
    std::vector<uint64_t> DigitV;
    std::vector<std::string> StrV;
    auto TestDigitF = std::bind(DigitF, &DigitV, std::placeholders::_1);
    auto TestStrF = std::bind(StrF, &StrV, std::placeholders::_1);
    parser.SetDigitTokenCallback(TestDigitF);
    parser.SetStrTokenCallback(TestStrF);
    std::string test_string = "";

    //проверяем порядок вызова колбеков, а также правильность их аргументов
    test_string = "12345 abcdef";
    std::vector<uint64_t>test_vector_dig =  {12345};
    std::vector<std::string>test_vector_str =  {"abcdef"};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

    test_string = "1234 abcdef fffff lulU 11";
    test_vector_dig =  {1234, 11};
    test_vector_str =  {"abcdef", "fffff", "lulU"};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

    test_string = "1";
    test_vector_dig =  {1};
    test_vector_str =  {};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

	test_string = "a";
    test_vector_dig =  {};
    test_vector_str =  {"a"};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

	test_string = "1323131132ddsdvfdeecc";
    test_vector_dig =  {};
    test_vector_str =  {"1323131132ddsdvfdeecc"};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

    //проверяем пустую строку
    test_string = "";
    test_vector_dig =  {};
    test_vector_str =  {};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

    //проверяем строку из символов табуляции
    test_string = "						";
    test_vector_dig =  {};
    test_vector_str =  {};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

    //проверяем строку из пробелов
    test_string = "     ";
    test_vector_dig =  {};
    test_vector_str =  {};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

	//проверяем что 2^64 будет обработан как строка
	test_string = "18446744073709551616";
    test_vector_dig =  {};
    test_vector_str =  {"18446744073709551616"};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

	//проверяем что 2^64-1 будет обработан как число
	test_string = "18446744073709551615";
    test_vector_dig =  {18446744073709551615ULL};
    test_vector_str =  {};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

	//проверяем что 2^65 будет обработан как строка
	test_string = "36893488147419103232";
    test_vector_dig =  {};
    test_vector_str =  {"36893488147419103232"};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();

	test_string = "12345678 abcdefgh 12345 abcd";
    test_vector_dig =  {12345678, 12345};
    test_vector_str =  {"abcdefgh", "abcd"};
    parser.Parse(test_string);
    ASSERT_EQ(DigitV, test_vector_dig);
    ASSERT_EQ(StrV, test_vector_str);
    test_vector_dig.clear();
    test_vector_str.clear();
    DigitV.clear();
    StrV.clear();
}



int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}