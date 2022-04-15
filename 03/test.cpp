#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "my_matrix.hpp"

class TestMatrix : public ::testing::Test 
{
protected:
	
	void SetUp() 
    {
        std::cout << "SetUp" << std::endl;
	}
	void TearDown() 
    {
        std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestMatrix, TestGetElem) 
{
    Matrix m(5, 3);
    m[0][0] = 1;
    ASSERT_EQ(m[0][0], 1);
    ASSERT_NO_THROW(m[0][2] = 1;);
    ASSERT_THROW(m[0][3] = 1, std::out_of_range);
    ASSERT_THROW(m[5][0] = 1, std::out_of_range);

    ASSERT_THROW(Matrix m1(0, 5), std::invalid_argument);
    ASSERT_THROW(Matrix m2(1, 0), std::invalid_argument);
}

TEST_F(TestMatrix, TestGetSize) 
{
    Matrix m(5, 3);
    ASSERT_EQ(m.getRows(), 5);
    ASSERT_EQ(m.getColumns(), 3); 
}

TEST_F(TestMatrix, TestMultiply) 
{
    Matrix m1(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m1[i][j] = 1;
    Matrix m2(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m2[i][j] = 2;
    Matrix m3(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m3[i][j] = -2;

    ASSERT_TRUE(m1 != m2);
    m1 *= 2;
    ASSERT_TRUE(m1 == m2);

    ASSERT_TRUE(m2 != m3);
    m2 *= -1;
    ASSERT_TRUE(m2 == m3);

    ASSERT_TRUE(m1 != m3);
    m1 *= 0;
    m3 *= 0;
    ASSERT_TRUE(m1 == m3);
}
TEST_F(TestMatrix, TestAdd) 
{
    Matrix m1(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m1[i][j] = 1;    
    Matrix m2(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m2[i][j] = 2;
    Matrix m_test(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m_test[i][j] = 3;
    Matrix m3 = m1 + m2;
    ASSERT_TRUE(m3 == m_test); 

    Matrix m4(5, 4);
    ASSERT_THROW(m4 + m1, std::logic_error);
    Matrix m5(4, 3);
    ASSERT_THROW(m5 + m1, std::logic_error);
    Matrix m6(1, 1);
    ASSERT_THROW(m6 + m1, std::logic_error);
    ASSERT_NO_THROW(m1 + m2);
}
TEST_F(TestMatrix, TesEquality)
{
    Matrix m1(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m1[i][j] = 1;
    Matrix m2(5, 3);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            m2[i][j] = 1;
    ASSERT_TRUE(m1 == m2); 
    m2[0][0] = 2;
    ASSERT_TRUE(m1 != m2); 
    ASSERT_FALSE(m1 == m2); 
}
int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}