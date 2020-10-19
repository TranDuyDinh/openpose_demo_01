/* This example is a very small one designed to show how compact SYCL code
* can be. That said, it includes no error checking and is rather terse. */

//#include <cassert>
#include <iostream>

#include <CL/sycl.hpp>
#include "multiple2Matrices.h"

namespace sycl = cl::sycl;
using namespace std;



int main(int, char**) 
{
	/// Initialize device selector
	sycl::amd_selector oland_amd;

	/// Initialize queue
	sycl::queue queueGPU(oland_amd);
	std::cout << "Running on "
		<< queueGPU.get_device().get_info<sycl::info::device::name>()
		<< "\n";

	float constant = 10.0;

	plusConstant(constant, queueGPU);

	/// Pauses
	std::cin.get();
	return 0;
}






