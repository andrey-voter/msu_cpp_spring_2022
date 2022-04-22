#include <gtest/gtest.h>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string>

#include "BigInt.hpp"


class TestBigInt : public ::testing::Test
{
public:
	custom::BigInt zero;
	custom::BigInt positive_1;
	custom::BigInt negative_1;
	custom::BigInt positive_2;
	custom::BigInt negative_2;
	custom::BigInt long_1;
	custom::BigInt long_2;

	virtual void SetUp()
	{
		zero = custom::BigInt(0);
		positive_1 = custom::BigInt(300);
		negative_1 = custom::BigInt(-200);
		positive_2 = custom::BigInt(400);
		negative_2 = custom::BigInt(-100);
		long_1 = custom::BigInt("123456789987654321123456789987654321");
		long_2 = custom::BigInt("328672379569256821356235826358162573123");
	}

	virtual void TearDown() {}
};

TEST_F(TestBigInt, test_1)
{
	custom::BigInt n1;
	ASSERT_EQ(n1, custom::BigInt(0));

	custom::BigInt n2(100);
	ASSERT_EQ(n2, custom::BigInt(100));

	custom::BigInt n3 = -100;
	ASSERT_EQ(n3, custom::BigInt(-100));

	custom::BigInt n4("111111111");
	ASSERT_EQ(n4, custom::BigInt(111111111));

	custom::BigInt n5("-0000000000");
	ASSERT_EQ(n5, custom::BigInt(0));

	ASSERT_THROW(custom::BigInt num("5656465rdtrdtrdt"), std::invalid_argument);

	custom::BigInt n6(n5);
	ASSERT_EQ(n6, n5);

}

TEST_F(TestBigInt, test_2)
{
	custom::BigInt n1 = 100;
	custom::BigInt n2 = 200;
	n2 = n1;
	ASSERT_EQ(n1, n2);
	ASSERT_EQ(n1, custom::BigInt(100));
	ASSERT_EQ(n2, n1);
}

TEST_F(TestBigInt, test_3)
{
	custom::BigInt n1 = -280;
	custom::BigInt n2 = 300;
	n2 = std::move(n1);
	ASSERT_NE(n1, custom::BigInt(-280));
	ASSERT_EQ(n2, custom::BigInt(-280));
}

TEST_F(TestBigInt, test_4)
{
	ASSERT_EQ(positive_1 + positive_2, custom::BigInt(700));
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(positive_2, custom::BigInt(400));

	ASSERT_EQ(positive_1 + negative_1, custom::BigInt(100));
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(negative_1, custom::BigInt(-200));

	ASSERT_EQ(positive_1 + zero, positive_1);
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(zero + positive_1, positive_1);
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(zero + zero, zero);
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(long_1 + long_2, custom::BigInt("328795836359244475677359283148150227444"));
	ASSERT_EQ(long_1, custom::BigInt("123456789987654321123456789987654321"));
	ASSERT_EQ(long_2, custom::BigInt("328672379569256821356235826358162573123"));
}

TEST_F(TestBigInt, test_5)
{
	ASSERT_EQ(positive_1 + 420, custom::BigInt(720));
	ASSERT_EQ(positive_1, custom::BigInt(300));

	ASSERT_EQ(positive_1 + 0, positive_1);
	ASSERT_EQ(positive_1, custom::BigInt(300));

	ASSERT_EQ(zero + 300, positive_1);
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(zero + 0, zero);
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(long_1 + 300, custom::BigInt("123456789987654321123456789987654621"));
	ASSERT_EQ(long_1, custom::BigInt("123456789987654321123456789987654321"));
}


TEST_F(TestBigInt, test_6)
{
	ASSERT_EQ(positive_2 - positive_1, custom::BigInt(100));
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(positive_2, custom::BigInt(400));

	ASSERT_EQ(positive_1 - negative_1, custom::BigInt(500));
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(negative_1, custom::BigInt(-200));

	ASSERT_EQ(positive_1 - zero, positive_1);
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(zero - negative_1, -negative_1);
	ASSERT_EQ(negative_1, custom::BigInt(-200));
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(zero - zero, zero);
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(long_2 - long_1, custom::BigInt("328548922779269167035112369568174918802"));
	ASSERT_EQ(long_1, custom::BigInt("123456789987654321123456789987654321"));
	ASSERT_EQ(long_2, custom::BigInt("328672379569256821356235826358162573123"));
}




TEST_F(TestBigInt, test_7)
{
	ASSERT_EQ(positive_1 - 200, custom::BigInt(100));
	ASSERT_EQ(positive_1, custom::BigInt(300));

	ASSERT_EQ(positive_1 - (-300), custom::BigInt(600));
	ASSERT_EQ(positive_1, custom::BigInt(300));

	ASSERT_EQ(positive_1 - 0, positive_1);
	ASSERT_EQ(positive_1, custom::BigInt(300));

	ASSERT_EQ(zero - (-200), -negative_1);
	ASSERT_EQ(negative_1, custom::BigInt(-200));
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(zero - 0, zero);
	ASSERT_EQ(zero, custom::BigInt(0));

	ASSERT_EQ(long_1 - 300, custom::BigInt("123456789987654321123456789987654021"));
	ASSERT_EQ(long_1, custom::BigInt("123456789987654321123456789987654321"));
}

TEST_F(TestBigInt, test_8)
{
	ASSERT_EQ(-zero, custom::BigInt(0));
	ASSERT_EQ(-positive_1, custom::BigInt(-300));
	ASSERT_EQ(-negative_1, custom::BigInt(200));
	ASSERT_EQ(-long_1, custom::BigInt("-123456789987654321123456789987654321"));

	ASSERT_EQ(zero, custom::BigInt(0));
	ASSERT_EQ(positive_1, custom::BigInt(300));
	ASSERT_EQ(negative_1, custom::BigInt(-200));
	ASSERT_EQ(long_1, custom::BigInt("123456789987654321123456789987654321"));
}



TEST_F(TestBigInt, test_9)
{
	ASSERT_TRUE(negative_1 < negative_2);
	ASSERT_TRUE(negative_1 < zero);
	ASSERT_TRUE(negative_1 < positive_1);
	ASSERT_TRUE(zero < positive_1);
	ASSERT_TRUE(positive_1 < positive_2);
	ASSERT_TRUE(long_1 < long_2);

    ASSERT_TRUE(negative_1 <= negative_2);
    ASSERT_TRUE(negative_1 <= zero);
    ASSERT_TRUE(negative_1 <= positive_1);
    ASSERT_TRUE(zero <= positive_1);
    ASSERT_TRUE(positive_1 <= positive_2);
    ASSERT_TRUE(long_1 <= long_2);

}

TEST_F(TestBigInt, test_10)
{
	ASSERT_TRUE(negative_1 < negative_2);
	ASSERT_TRUE(zero > negative_1);
	ASSERT_TRUE(positive_1 > negative_1);
	ASSERT_TRUE(positive_1 > zero);
	ASSERT_TRUE(positive_2 > positive_1);
	ASSERT_TRUE(long_2 > long_1);

    ASSERT_TRUE(negative_1 <= negative_2);
    ASSERT_TRUE(zero >= negative_1);
    ASSERT_TRUE(positive_1 >= negative_1);
    ASSERT_TRUE(positive_1 >= zero);
    ASSERT_TRUE(positive_2 >= positive_1);
    ASSERT_TRUE(long_2 >= long_1);
}

TEST_F(TestBigInt, test_11)
{
	ASSERT_TRUE(positive_1 == positive_1);
	ASSERT_TRUE(negative_1 == negative_1);
	ASSERT_TRUE(zero == zero);
	ASSERT_TRUE(long_2 == long_2);

	ASSERT_FALSE(zero == positive_1);
	ASSERT_FALSE(zero == negative_1);
	ASSERT_FALSE(positive_1 == negative_1);
	ASSERT_FALSE(long_1 == long_2);
}

TEST_F(TestBigInt, test_12)
{
	ASSERT_TRUE(zero != positive_1);
	ASSERT_TRUE(zero != negative_1);
	ASSERT_TRUE(positive_1 != negative_1);
	ASSERT_TRUE(long_1 != long_2);

	ASSERT_FALSE(positive_1 != positive_1);
	ASSERT_FALSE(negative_1 != negative_1);
	ASSERT_FALSE(zero != zero);
	ASSERT_FALSE(long_2 != long_2);
}

TEST_F(TestBigInt, test_13)
{
	std::ostringstream os;
	os << zero;
	ASSERT_EQ(os.str(), "0");

	os.str(std::string());
	os << positive_1;
	ASSERT_EQ(os.str(), "300");

	os.str(std::string());
	os << negative_1;
	ASSERT_EQ(os.str(), "-200");

	os.str(std::string());
	os << long_1;
	ASSERT_EQ(os.str(), "123456789987654321123456789987654321");

}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}