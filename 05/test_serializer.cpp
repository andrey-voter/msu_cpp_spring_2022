#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <sstream>

#include "serializer.hpp"


struct DataEmpty
{
	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer();
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer();
	}

	bool operator==(const DataEmpty &) const
	{
		return true;
	}
};


struct DataBool1
{
	bool a;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a);
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a);
	}

	bool operator==(const DataBool1 & other) const
	{
		return a == other.a;
	}
};


struct DataBool4
{
	bool a;
	bool b;
	bool c;
	bool d;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c, d);
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c, d);
	}

	bool operator==(const DataBool4 & other) const
	{
		return a == other.a && b == other.b && c == other.c && d == other.d;
	}
};


struct DataInt1
{
	uint64_t a;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a);
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a);
	}

	bool operator==(const DataInt1 & other) const
	{
		return a == other.a;
	}
};


struct DataInt4
{
	uint64_t a;
	uint64_t b;
	uint64_t c;
	uint64_t d;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c, d);
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c, d);
	}

	bool operator==(const DataInt4 & other) const
	{
		return a == other.a && b == other.b && c == other.c && d == other.d;
	}
};


struct Data1
{
	bool a;
	bool b;
	bool c;
	uint64_t d;
	uint64_t e;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c, d, e);
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c, d, e);
	}

	bool operator==(const Data1 & other) const
	{
		return a == other.a && b == other.b && c == other.c && d == other.d && e == other.e;
	}
};


struct Data2
{
	bool a;
	bool b;
	uint64_t c;
	uint64_t d;
	uint64_t e;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c, d, e);
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c, d, e);
	}

	bool operator==(const Data2 & other) const
	{
		return a == other.a && b == other.b && c == other.c && d == other.d && e == other.e;
	}
};


struct DataIncType
{
	bool a;
	bool b;
	uint64_t c;
	uint64_t d;
	std::string s;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c, d, s);
	}

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c, d, s);
	}

	bool operator==(const DataIncType & other) const
	{
		return a == other.a && b == other.b && c == other.c && d == other.d && s == other.s;
	}
};


struct DataNonDes
{
	bool a;
	bool b;
	uint64_t c;
	uint64_t d;

	template <typename Serializer>
	my_namespace::Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c, d);
	}
};


struct DataNonSer
{
	bool a;
	bool b;
	uint64_t c;
	uint64_t d;

	template <typename Deserializer>
	my_namespace::Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c, d);
	}
};


struct DataNonDesSer
{
	bool a;
	bool b;
	uint64_t c;
	uint64_t d;
};


class TestSerializer : public ::testing::Test
{
public:
	std::stringstream stream;
	my_namespace::Serializer serializer;
	my_namespace::Deserializer deserializer;

	void reset()
	{
		stream.str(std::string());
		serializer = my_namespace::Serializer(stream);
		deserializer = my_namespace::Deserializer(stream);
	}
protected:
	virtual void SetUp()
	{
		reset();
	}

	virtual void TearDown() { }
};

TEST_F(TestSerializer, test_serializer_with_different_structure_sizes)
{
    DataInt4 x;
    Data1 y;
    ASSERT_EQ(serializer.save(x), my_namespace::Error::Ok);
    ASSERT_EQ(deserializer.load(y), my_namespace::Error::Spoiled);
}

TEST_F(TestSerializer, test_serializer_empty)
{
	DataEmpty x;
	DataEmpty y;

	ASSERT_EQ(serializer.save(x), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y), my_namespace::Error::Ok);
	ASSERT_EQ(x, y);
}


TEST_F(TestSerializer, test_serializer_bool)
{
	DataBool1 x1 {true};
	DataBool1 y1 {false};
	ASSERT_EQ(serializer.save(x1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Ok);
	ASSERT_EQ(x1, y1);
	reset();

	DataBool4 x4 {true, false, true, true};
	DataBool4 y4 {false, false, true, false};
	ASSERT_EQ(serializer.save(x4), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y4), my_namespace::Error::Ok);
	ASSERT_EQ(x4, y4);
	reset();

	ASSERT_EQ(serializer.save(x1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y4), my_namespace::Error::Spoiled);
	reset();

	ASSERT_EQ(serializer.save(x4), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Spoiled);
	reset();

	DataInt1 xi1 {1};
	ASSERT_EQ(serializer.save(xi1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Spoiled);
}


TEST_F(TestSerializer, test_serializer_int)
{
	DataInt1 x1 {5};
	DataInt1 y1 {9};
	ASSERT_EQ(serializer.save(x1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Ok);
	ASSERT_EQ(x1, y1);
	reset();

	DataInt4 x4 {1, 2, 3, 5};
	DataInt4 y4 {9, 6, 3, 0};
	ASSERT_EQ(serializer.save(x4), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y4), my_namespace::Error::Ok);
	ASSERT_EQ(x4, y4);
	reset();

	ASSERT_EQ(serializer.save(x1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y4), my_namespace::Error::Spoiled);
	reset();

	ASSERT_EQ(serializer.save(x4), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Spoiled);
	reset();

	DataBool1 xb1 {true};
	ASSERT_EQ(serializer.save(xb1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Spoiled);
}


TEST_F(TestSerializer, test_serializer_common)
{
	Data1 x1 {true, true, false, 5, 10};
	Data1 y1 {false, true, true, 6, 11};
	ASSERT_EQ(serializer.save(x1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Ok);
	ASSERT_EQ(x1, y1);
	reset();

	Data2 x2 {false, false, 1, 3, 5};
	Data2 y2 {true, true, 0,1, 0};
	ASSERT_EQ(serializer.save(x2), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y2), my_namespace::Error::Ok);
	ASSERT_EQ(x2, y2);
	reset();

	ASSERT_EQ(serializer.save(x1), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y2), my_namespace::Error::Spoiled);
	reset();

	ASSERT_EQ(serializer.save(x2), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y1), my_namespace::Error::Spoiled);
}


TEST_F(TestSerializer, test_serializer_non_serializable)
{
	DataIncType x1 {true, false, 100, 1000, "false"};
	ASSERT_EQ(serializer.save(x1), my_namespace::Error::CantSerialize);
	reset();

	DataNonDes x2 {true, false, 100, 1000};
	DataNonDes y2 {false, false, 150, 15};
	ASSERT_EQ(serializer.save(x2), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y2), my_namespace::Error::CantSerialize);
	reset();

	DataNonSer x3 {true, true, 9, 10};
	DataNonSer y3 {true, false, 42, 1337};
	ASSERT_EQ(serializer.save(x3), my_namespace::Error::CantSerialize);
	reset();

	ASSERT_EQ(serializer.save(x2), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y3), my_namespace::Error::Ok);
	ASSERT_EQ(x2.a, y3.a);
	ASSERT_EQ(x2.b, y3.b);
	ASSERT_EQ(x2.c, y3.c);
	ASSERT_EQ(x2.d, y3.d);
	reset();


	DataNonDesSer x4 {true, true, 300, 420};
	DataNonDesSer y4 {false, false, 666, 777};
	ASSERT_EQ(serializer.save(x4), my_namespace::Error::CantSerialize);

	reset();
	ASSERT_EQ(serializer.save(x2), my_namespace::Error::Ok);
	ASSERT_EQ(deserializer.load(y4), my_namespace::Error::CantSerialize);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}