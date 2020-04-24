#include <gtest/gtest.h>
#include "Threads_Calculator.h"

#include <iostream>
#include <ctime>


class Square {
public:
	size_t operator() (const int value)
	{
		return pow(value, 2);
	}
};


TEST(th_clac_th, stat_test_1)
{
	std::vector<size_t> v(32), ref(32);
	for (auto i = 0; i < v.size(); ++i)
	{
		v[i] = i + 1;
		ref[i] = v[i] * v[i];
	}

	auto v2 = v;
	Square sq;

	my_Ths_Calc::calculation_in_threads(v.begin(), v.end(), sq, 4);
	omp_Ths_Calc::calculation_in_threads(v2.begin(), v2.end(), sq, 4);

    EXPECT_TRUE(v == ref);
	EXPECT_TRUE(v2 == ref);
}

TEST(th_clac_th, stat_test_2)
{
	std::vector<size_t> v(32), ref(32);
	for (auto i = 0; i < v.size(); ++i)
	{
		v[i] = i + 1;
		ref[i] = v[i] * v[i];
	}

	auto v2 = v;
	Square sq;

	my_Ths_Calc::calculation_in_threads(v.begin(), v.end(), sq);
	omp_Ths_Calc::calculation_in_threads(v2.begin(), v2.end(), sq);

	EXPECT_TRUE(v == ref);
	EXPECT_TRUE(v2 == ref);

}


TEST(th_clac_th, stat_test_3)
{
	std::vector<size_t> v(0), ref(0);

	auto v2 = v;
	Square sq;

	my_Ths_Calc::calculation_in_threads(v.begin(), v.end(), sq, 4);
	omp_Ths_Calc::calculation_in_threads(v2.begin(), v2.end(), sq, 4);


	EXPECT_TRUE(v == ref);
	EXPECT_TRUE(v2 == ref);

}


TEST(th_clac_th, stat_test_4)
{
	std::vector<size_t> v(997), ref(997);
	for (auto i = 0; i < v.size(); ++i)
	{
		v[i] = i + 1;
		ref[i] = v[i] * v[i];
	}
	auto v2 = v;
	Square sq;

	my_Ths_Calc::calculation_in_threads(v.begin(), v.end(), sq);
	omp_Ths_Calc::calculation_in_threads(v2.begin(), v2.end(), sq);


	EXPECT_TRUE(v == ref);
	EXPECT_TRUE(v2 == ref);

}

TEST(th_clac_th, rand_test_1)
{
	srand(time(NULL));
	size_t size = rand() % 10000 + 100;
	std::vector<size_t> v(size), ref(size);
	for (auto i = 0; i < v.size(); ++i)
	{
		v[i] = rand()%1000;
		ref[i] = v[i] * v[i];
	}
	auto v2 = v;
	Square sq;

	my_Ths_Calc::calculation_in_threads(v.begin(), v.end(), sq);
	omp_Ths_Calc::calculation_in_threads(v2.begin(), v2.end(), sq);

	EXPECT_TRUE(v == ref);
	EXPECT_TRUE(v2 == ref);

}


TEST(th_clac_th, rand_test_2)
{
	srand(time(NULL));
	size_t size = rand() % 10000 + 100;
	std::vector<size_t> v(size), ref(size);
	for (auto i = 0; i < v.size(); ++i)
	{
		v[i] = rand() % 1000 - 500;
		ref[i] = v[i] * v[i];
	}
	auto v2 = v;
	Square sq;

	uint8_t num_th = rand() % 20 + 1;

	my_Ths_Calc::calculation_in_threads(v.begin(), v.end(), sq, num_th);
	omp_Ths_Calc::calculation_in_threads(v2.begin(), v2.end(), sq, num_th);


	EXPECT_TRUE(v == ref);
	EXPECT_TRUE(v2 == ref);

}
int main(int argc, char* argv[])
{
	

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}