#pragma once

#include <thread>
#include <vector>
#include <future>
#include <atomic>


template <typename F>
void parallelFor(int begin, int end, F func);