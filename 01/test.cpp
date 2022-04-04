#include <iostream>

#include "allocator.hpp"

#include <gtest/gtest.h>


class TestFoo : public ::testing::Test
{
protected:
    Allocator a;
    
	void SetUp()
	{
        std::cout << "SetUp" << std::endl;
	}
	void TearDown()
	{
        std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestFoo, alloc)
{
    // trying to alloc smth before makeAllocator
	ASSERT_EQ(a.alloc(10), nullptr);
	
	a.makeAllocator(100);
	//we allocated 100 so we can get 10
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

	//added some more test
	a.makeAllocator(1);
	ASSERT_NE(a.alloc(1), nullptr);
	ASSERT_EQ(a.alloc(1), nullptr);
	a.makeAllocator(50);
	ASSERT_NE(a.alloc(20), nullptr);
	ASSERT_NE(a.alloc(30), nullptr);
	ASSERT_EQ(a.alloc(1), nullptr);
	a.reset();
	ASSERT_NE(a.alloc(50), nullptr);
	a.reset();
	char* p1 = a.alloc(10); 
	char* p2 = a.alloc(10); 
	ASSERT_EQ(p2 - p1, 10);
}

TEST_F(TestFoo, makeAllocator)
{
	//using makeAllocator two times in a row
	a.makeAllocator(10);
	a.makeAllocator(5);
	//shows that we cant get 6, but can get 5
	ASSERT_EQ(a.alloc(6), nullptr);	
	ASSERT_NE(a.alloc(5), nullptr);		
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}