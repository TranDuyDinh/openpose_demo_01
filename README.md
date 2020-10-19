/* This example is a very small one designed to show how compact SYCL code
* can be. That said, it includes no error checking and is rather terse. */

//#include <cassert>
#include <iostream>

#include <CL/sycl.hpp>
//#include "multiple2Matrices.h"

namespace sycl = cl::sycl;
using namespace std;

// OPTION:
// =1		setting totally work items
// =2		setting work items and work group
#define		OPTION		2

const size_t N = 40;

//void plusConstant(float constant, sycl::queue queueGPU)
//{
//	/// Generate buffer
//	sycl::buffer<float, 1> bufVec(sycl::range<1>{N});
//
//	/// Initialize
//	queueGPU.submit([&](sycl::handler& cgh)
//	{
//		auto acc = bufVec.get_access<sycl::access::mode::write>(cgh);
//
//		cgh.parallel_for<class initVec>(sycl::range<1>{N}, [=](sycl::id<1> index)
//		{
//			acc[index] = index[0];
//		});
//	});
//
//	if (OPTION == 1)
//	{
//		/// Setting totally work_items
//		/// work item = N
//		std::cout << "Option 1" << std::endl;
//		queueGPU.submit([&](sycl::handler& cgh) {
//			auto acc = bufVec.get_access<sycl::access::mode::read_write>(cgh);
//			cgh.parallel_for<class plusVecOp1>
//				(sycl::range<1>(N), [=](sycl::item<1> myItem)
//			{
//				size_t index = myItem.get_linear_id();
//				acc[index] += constant;
//			});
//		});
//	}
//	else if (OPTION == 2)
//	{
//		/// Setting work_items and work_groups
//		/// work item		= N
//		/// work group		= N / 4
//		std::cout << "Option 2" << std::endl;
//		queueGPU.submit([&](sycl::handler& cgh) {
//			auto acc = bufVec.get_access<sycl::access::mode::read_write>(cgh);
//			cgh.parallel_for<class plusVecOp2>
//				(sycl::nd_range<1>(sycl::range<1>(N), sycl::range<1>(N / 4)), [=](sycl::nd_item<1> myItem)
//			{
//				size_t index = myItem.get_global_linear_id();
//				acc[index] += constant;
//			});
//		});
//	}
//
//	auto accReadOut = bufVec.get_access<sycl::access::mode::read>();
//	std::cout << "Output:" << std::endl;
//	for (size_t i = 0; i < N; i++)
//	{
//		std::cout << accReadOut[i] << ", ";
//	}
//	std::cout << "END Output" << std::endl;
//}

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

	{
		/// Generate buffer
		sycl::buffer<float, 1> bufVec(sycl::range<1>{N});

		/// Initialize
		queueGPU.submit([&](sycl::handler& cgh)
		{
			auto acc = bufVec.get_access<sycl::access::mode::write>(cgh);

			cgh.parallel_for<class initVec>(sycl::range<1>{N}, [=](sycl::id<1> index)
			{
				acc[index] = index[0];
			});
		});

		if (OPTION == 1)
		{
			/// Setting totally work_items
			/// work item = N
			std::cout << "Option 1" << std::endl;
			queueGPU.submit([&](sycl::handler& cgh) {
				auto acc = bufVec.get_access<sycl::access::mode::read_write>(cgh);
				cgh.parallel_for<class plusVecOp1>
					(sycl::range<1>(N), [=](sycl::item<1> myItem)
				{
					size_t index = myItem.get_linear_id();
					acc[index] += constant;
				});
			});
		}
		else if (OPTION == 2)
		{
			/// Setting work_items and work_groups
			/// work item		= N
			/// work group		= N / 4
			std::cout << "Option 2" << std::endl;
			queueGPU.submit([&](sycl::handler& cgh) {
				auto acc = bufVec.get_access<sycl::access::mode::read_write>(cgh);
				cgh.parallel_for<class plusVecOp2>
					(sycl::nd_range<1>(sycl::range<1>(N), sycl::range<1>(N / 4)), [=](sycl::nd_item<1> myItem)
				{
					size_t index = myItem.get_global_linear_id();
					acc[index] += constant;
				});
			});
		}

		auto accReadOut = bufVec.get_access<sycl::access::mode::read>();
		std::cout << "Output:" << std::endl;
		for (size_t i = 0; i < N; i++)
		{
			std::cout << accReadOut[i] << ", ";
		}
		std::cout << "END Output" << std::endl;
	}


	//plusConstant(constant, queueGPU);

	/// Pauses
	std::cin.get();
	return 0;
}






