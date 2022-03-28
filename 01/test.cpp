#include <iostream>

#include "allocator.hpp"

#include <gtest/gtest.h>



class TestFoo : public ::testing::Test
{
protected:
    Allocator a;
    
	void SetUp()
	{
        a.makeAllocator(100);
        std::cout << "SetUp" << std::endl;
	}
	void TearDown()
	{
        std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestFoo, alloc)
{
    // in SetUp() we allocated 100 so we can get 10
	ASSERT_NE(a.alloc(10), nullptr);
	
	// cant get 91, cause 91 + 10 > 100
	ASSERT_EQ(a.alloc(91), nullptr);
	
	// can get 90, cause 90 + 10 == 100
	ASSERT_NE(a.alloc(90), nullptr);
	
	// test shows that we cant get more than allocated with initialisation
	a.makeAllocator(100);
	ASSERT_EQ(a.alloc(101), nullptr);
	
	// test shows that reset() works correctly
	ASSERT_NE(a.alloc(50), nullptr);
	ASSERT_EQ(a.alloc(60), nullptr);
	a.reset();
	ASSERT_NE(a.alloc(60), nullptr);
	
	//test shows that alloc works correctly with numbers <= 0
	ASSERT_EQ(a.alloc(-1), nullptr);
	ASSERT_EQ(a.alloc(0), nullptr);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}