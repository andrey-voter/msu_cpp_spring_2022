#include <gtest/gtest.h>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "format.hpp"

struct Streamable {};

std::ostream & operator<<(std::ostream & os, Streamable x)
{
	os << "OK";
	(void)x;
	return os;
}


struct NonStreamable {};


class TestFormat : public ::testing::Test
{
protected:
	virtual void SetUp(){}

	virtual void TearDown() {}
};


TEST_F(TestFormat, test_format)
{
	ASSERT_EQ(my_namespace::format("as{0}as", 1), "as1as");
	ASSERT_EQ(my_namespace::format("as{0}as", Streamable(), NonStreamable()), "asOKas");
	ASSERT_EQ(my_namespace::format("{2}__{0}__{2}__{1}", 1, "abc", 5.7), "5.7__1__5.7__abc");
	ASSERT_EQ(my_namespace::format("{0}", 5), "5");
	ASSERT_EQ(my_namespace::format("{0}_{3}_{2}_{1}", 1, 2.5, '3', "4"), "1_4_3_2.5");
	ASSERT_EQ(my_namespace::format("", 5), "");
	ASSERT_EQ(my_namespace::format("lol", 5), "lol");
	ASSERT_EQ(my_namespace::format("a{0}b", 5), "a5b");
	ASSERT_EQ(my_namespace::format("abc"), "abc");
	ASSERT_EQ(my_namespace::format(""), "");
}


TEST_F(TestFormat, test_invalid_string_format)
{
	ASSERT_THROW(my_namespace::format("{{0}}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("}{0}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{-1}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{0{1}}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{0", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{a}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{}"), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{a}"), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("}"), my_namespace::invalid_string_format);
	ASSERT_THROW(my_namespace::format("{"), my_namespace::invalid_string_format);
}


TEST_F(TestFormat, test_non_streamable_param)
{
	ASSERT_THROW(my_namespace::format("{0}", std::vector<int>()), my_namespace::non_streamable_param);
	ASSERT_THROW(my_namespace::format("{0} {1}", 1, std::map<int, int>()), my_namespace::non_streamable_param);
	ASSERT_THROW(my_namespace::format("{0} {1}", std::queue<int>(), 2), my_namespace::non_streamable_param);
	ASSERT_THROW(my_namespace::format("{0}", NonStreamable(), 3), my_namespace::non_streamable_param);

	ASSERT_NO_THROW(my_namespace::format("0", std::vector<int>()));
	ASSERT_NO_THROW(my_namespace::format("{0} 1", 1, std::map<int, int>()));
	ASSERT_NO_THROW(my_namespace::format("0 {1}", std::queue<int>(), 2));
	ASSERT_NO_THROW(my_namespace::format("{0}", Streamable()));
}


TEST_F(TestFormat, test_invalid_params_count)
{
	ASSERT_THROW(my_namespace::format("{0}"), my_namespace::invalid_params_count);
	ASSERT_THROW(my_namespace::format("{0} {1} {0}", 5), my_namespace::invalid_params_count);
	ASSERT_THROW(my_namespace::format("{1}", 5), my_namespace::invalid_params_count);
	ASSERT_THROW(my_namespace::format("{10}", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10), my_namespace::invalid_params_count);

	ASSERT_NO_THROW(my_namespace::format("{0}", 5));
	ASSERT_NO_THROW(my_namespace::format("{0}", 5, 6));
	ASSERT_NO_THROW(my_namespace::format("0", 5));
	ASSERT_NO_THROW(my_namespace::format("", 5));
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}