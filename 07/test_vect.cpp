#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iterator>
#include <memory>
#include <initializer_list>

#include "vect.hpp"


class man
{
	std::string name;
	size_t age;

public:
	man(){}

	man(std::string name, size_t age) : name(name), age(age) {}

	man(const man & other) : name(other.name), age(other.age) {}

	man & operator=(const man & other)
	{
		name = other.name;
		age = other.age;
		return *this;
	}

	bool operator==(const man & other) const
	{
		return other.name == name && other.age == age;
	}

	bool operator!=(const man & other) const
	{
		return other.name != name || other.age != age;
	}

	virtual ~man(){}
};


class TestVect : public ::testing::Test
{
protected:
	virtual void SetUp(){}

	virtual void TearDown() {}
};


TEST_F(TestVect, test_vect_ctr)
{
	ASSERT_NO_THROW(my_namespace::Vector<size_t> v1{});
	ASSERT_NO_THROW(my_namespace::Vector<std::string> v2(10));
	ASSERT_NO_THROW(my_namespace::Vector<char> v3(10, 'a'));
	ASSERT_NO_THROW(my_namespace::Vector<int> v4({5, 5, 5, 5}));
	my_namespace::Vector<int> v4({5, 5, 5, 5});
	ASSERT_NO_THROW(my_namespace::Vector<int> v5 = v4);
}


TEST_F(TestVect, test_vect_assign)
{
	my_namespace::Vector<int> v1 = {1, 2, 3, 4};
	my_namespace::Vector<int> v2(1);
	v2 = v1;
	ASSERT_EQ(v1.size(), v2.size());
	for (size_t i = 0; i < v1.size(); ++i)
		ASSERT_EQ(v1[i], v2[i]);
}


TEST_F(TestVect, test_vect_push_back)
{
	my_namespace::Vector<int> v1(10);
	for(size_t i = 0; i < 10; ++i)
		v1.push_back(i);
	for (size_t i = 0; i < 10; ++i)
		ASSERT_EQ(v1[i], i);
	ASSERT_EQ(v1.size(), 10);

}


TEST_F(TestVect, test_vect_pop_back)
{
	my_namespace::Vector<unsigned> v1(10);
	for(size_t i = 0; i < 15; ++i)
		v1.push_back(i);
	for (size_t i = 0; i < 15; ++i)
		ASSERT_EQ(v1[i], i);
	ASSERT_EQ(v1.size(), 15);

	for(size_t i = 0; i < 5; ++i)
		v1.pop_back();
	ASSERT_EQ(v1.size(), 10);
}


TEST_F(TestVect, test_vect_emplace_back)
{
	my_namespace::Vector<man> v1(10);
	for(size_t i = 0; i < 15; ++i)
		v1.emplace_back("Andrey", i);
	for (size_t i = 0; i < 15; ++i)
		ASSERT_EQ(v1[i], man("Andrey", i));
	ASSERT_EQ(v1.size(), 15);
}


TEST_F(TestVect, test_vect_empty)
{
	my_namespace::Vector<unsigned> v1(10);
	ASSERT_TRUE(v1.empty());

    v1.push_back(1);
	ASSERT_FALSE(v1.empty());

    v1.pop_back();
	ASSERT_TRUE(v1.empty());
}

TEST_F(TestVect, test_vect_clear)
{
	my_namespace::Vector<unsigned> v1(10);
	for(size_t i = 0; i < 15; ++i)
		v1.push_back(i);
	ASSERT_EQ(v1.size(), 15);
	ASSERT_EQ(v1.capacity(), 16);

	v1.clear();
	ASSERT_EQ(v1.size(), 0);
	ASSERT_EQ(v1.capacity(), 0);

	for(size_t i = 0; i < 15; ++i)
		v1.push_back(i);
	ASSERT_EQ(v1.size(), 15);
	ASSERT_EQ(v1.capacity(), 16);
}


TEST_F(TestVect, test_vect_resize)
{
	my_namespace::Vector<signed> v1{};
	v1.resize(10);
	ASSERT_EQ(v1.capacity(), 16);
	ASSERT_EQ(v1.size(), 0);

	for(size_t i = 0; i < 25; ++i)
		v1.push_back(i);
	ASSERT_EQ(v1.capacity(), 32);
	ASSERT_EQ(v1.size(), 25);

	v1.resize(40);
	ASSERT_EQ(v1.capacity(), 64);
	ASSERT_EQ(v1.size(), 25);

	v1.resize(10);
	ASSERT_EQ(v1.capacity(), 16);
	ASSERT_EQ(v1.size(), 10);
	for (size_t i = 0; i < 10; ++i)
		ASSERT_EQ(v1[i], i);
}


TEST_F(TestVect, test_vect_reserve)
{
	my_namespace::Vector<short> v1(10);
	ASSERT_EQ(v1.capacity(), 16);

	v1.reserve(10);
	ASSERT_EQ(v1.capacity(), 32);

	v1.reserve(20);
	ASSERT_EQ(v1.capacity(), 64);
}


TEST_F(TestVect, test_vect_capacity)
{
	my_namespace::Vector<short> v1(10);
	ASSERT_EQ(v1.capacity(), 16);
	for(size_t i = 0; i < 25; ++i)
		v1.push_back(i);
	ASSERT_EQ(v1.capacity(), 32);

	for(size_t i = 0; i < 20; ++i)
		v1.pop_back();
	ASSERT_EQ(v1.capacity(), 16);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}