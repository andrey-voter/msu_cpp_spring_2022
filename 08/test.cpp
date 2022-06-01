#include <iostream>
#include <thread>
#include <typeinfo>
#include <gtest/gtest.h>
#include <sstream>
#include <unistd.h>
#include <string>
#include "thread_pool.hpp"

class TestThreadPool : public ::testing::Test
{
protected:
    virtual void SetUp(){}
    virtual void TearDown() {}
};

class Example
{
    int ex;
public:
    Example(int k = 0): ex(k){}
    bool operator == (const Example& Example) const
    {
        return ex == Example.ex;
    }
};


TEST_F(TestThreadPool, test_make_thread)
{
	ThreadPool pool(10);
	std::future<std::thread::id> f = pool.exec([](){return std::this_thread::get_id();});
	ASSERT_NE(f.get(), std::this_thread::get_id());
}


TEST_F(TestThreadPool, test_no_threads)
{
	ThreadPool pool(0);
	std::future<void> f = pool.exec([](){return;});
	ASSERT_EQ(f.wait_for(std::chrono::seconds(3)), std::future_status::timeout);
}


TEST_F(TestThreadPool, test_a_lot_of_tasks)
{
	size_t quantity = std::thread::hardware_concurrency();
	ThreadPool pool(quantity);
	std::vector<std::future<void>> vect_future;
	for (size_t i = 0; i < quantity + 2; i++)
		vect_future.push_back(pool.exec([](){std::this_thread::sleep_for(std::chrono::milliseconds(50));}));
	std::chrono::system_clock::time_point second_passed = std::chrono::system_clock::now() + std::chrono::seconds(1);
	for (size_t i = 0; i < quantity + 2; i++)
		ASSERT_EQ(vect_future[i].wait_until(second_passed), std::future_status::ready);
}

void func1(const Example&) {}
std::string func2() { return "Example string"; }
int mul(int a, int b, int c) { return a*b*c; }

TEST_F(TestThreadPool, DifferentTests)
{
    ThreadPool pool(10);

    auto pool1 = pool.exec(func1, Example());
    pool1.get();

    auto pool2 = pool.exec(mul, 1, 2, 3);
    ASSERT_DOUBLE_EQ(6, pool2.get());

    auto pool3 = pool.exec(func2);
    ASSERT_EQ("Example string", pool3.get());
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}