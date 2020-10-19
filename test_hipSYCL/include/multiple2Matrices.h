//#include <cassert>
#include <iostream>

#include <CL/sycl.hpp>

namespace sycl = cl::sycl;
using namespace std;

// OPTION:
// =1		setting totally work items
// =2		setting work items and work group
#define		OPTION		2

const size_t N = 40;

void plusConstant(float constant, sycl::queue queueGPU);