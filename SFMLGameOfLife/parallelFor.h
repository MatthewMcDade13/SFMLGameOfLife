#pragma once

#include <thread>
#include <vector>
#include <future>
#include <atomic>

// Thanks to http://www.andythomason.com/2016/08/21/c-multithreading-an-effective-parallel-for-loop/ for 
// this implementation of a parallel for loop!

template <typename F>
void parallelFor(int begin, int end, F func)
{
	int numThread = std::thread::hardware_concurrency();
	std::vector<std::future<void>> futures(numThread);
	std::atomic<int> offset;
	offset = begin;

	for (size_t i = 0; i < futures.size(); i++)
	{
		futures[i] = std::async(std::launch::async,
			[i, &offset, end, &func]() {
			while (true)
			{
				int ind = offset++;
				if (ind >= end) break;
				func(ind);
			}
		});
	}

	for (size_t i = 0; i < futures.size(); i++)
	{
		futures[i].get();
	}

}