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

TEST_F(TestTokenParser, test_IsDigitToken) {
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
}

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}