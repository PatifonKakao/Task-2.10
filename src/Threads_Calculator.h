#pragma once

#include <vector>
#include <thread>

#include <omp.h>



namespace my_Ths_Calc 
{

	template <typename Iter, class Operation>
	void calculation_in_threads(
		Iter & begin,
		Iter & end,
		Operation & op,
		uint16_t amount_theads = std::thread::hardware_concurrency())
	{
		auto size = std::distance(begin, end);
		auto amount_th = amount_theads;

		if (size <= 0)
			return;
		if (size < amount_th)
			amount_th = size;


		std::vector<std::thread> threads;
		threads.resize(amount_th);

		uint16_t step = size / amount_th;

		for (auto i = 0; i < amount_th; ++i)
		{
			std::thread th([i, step, &begin, &op]
			{
				auto current_end = step * (i + 1);
				auto current_start = step * i;
				for (auto j = current_start; j < current_end; ++j)
				{
					auto it = begin + j;
					*it = op(*it);
				}
			});
			threads[i] = std::move(th);
		}

		uint16_t rest = size % amount_th;
		auto current_start = step * amount_th;
		auto current_end = current_start + rest;
		for (auto j = current_start; j < current_end; ++j)
		{
			auto it = begin + j;
			*it = op(*it);
		}


		for (std::thread & th : threads)
		{
			if (th.joinable())
				th.join();
		}

	}
}


namespace omp_Ths_Calc 
{
	template <typename Iter, class Operation>
	void calculation_in_threads(
		Iter & begin,
		Iter & end,
		Operation & op,
		uint16_t amount_theads = std::thread::hardware_concurrency())
	{

		auto size = std::distance(begin, end);
        #pragma omp parallel for num_threads(amount_theads) 
			for (auto j = 0; j < size; ++j)
			{
				auto it = begin + j;
				*it = op(*it);

			}
	}
}