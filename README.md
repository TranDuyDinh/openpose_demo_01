/* This example is a very small one designed to show how compact SYCL code
* can be. That said, it includes no error checking and is rather terse. */

//#include <cassert>
#include <iostream>

#include <CL/sycl.hpp>

namespace sycl = cl::sycl;
using namespace std;
using data_type = float;

#define		SIZE		9
// OPTION:
// =1		setting totally work items
// =2		setting work items and work group
#define		OPTION		2

const size_t N = 40;
const size_t M = 5;


int main(int, char**) 
{
	/// Initialize device selector
	sycl::amd_selector oland_amd;

	/// Initialize queue
	sycl::queue queueGPU(oland_amd);
	std::cout << "Running on "
		<< queueGPU.get_device().get_info<sycl::info::device::name>()
		<< "\n";
	

	float num01[SIZE], num02[SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		num01[i] = (float)i;
		//num02[i] = (float)(SIZE - i);
	}

	{
		/// Submit kernel 
		//sycl::buffer<float, 1> buf01(num01, sycl::range<1>(SIZE));
		//sycl::buffer<float, 1> buf02(num01, sycl::range<1>(SIZE));

		sycl::buffer<float, 2> bufMat(sycl::range<2>{N, M});
		sycl::buffer<float, 1> bufVec(sycl::range<1>{N});


		queueGPU.submit([&](sycl::handler& cgh) 
		{
			auto acc = bufMat.get_access<sycl::access::mode::write>(cgh);

			cgh.parallel_for<class initMat>(sycl::range<2>{N, M}, [=](sycl::id<2> index)
			{
				acc[index] = index[0] + index[1];
			});
		});

		/// Initation
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
					acc[index] += 10.0;
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
					(sycl::nd_range<1>(sycl::range<1>(N), sycl::range<1>(N/4)), [=](sycl::nd_item<1> myItem)
				{
					size_t index = myItem.get_global_linear_id();
					acc[index] += 10.0;
				});
			});
		}

		//auto accR = bufMat.get_access<sycl::access::mode::read>();
		//std::cout << "Input:" << std::endl;
		//for (size_t i = 0; i < N; i++)
		//{
		//	for (size_t j = 0; j < M; j++)
		//	{
		//		std::cout << accR[i][j] << ", ";
		//	}
		//	std::cout << std::endl;
		//}
		//std::cout << "END Input" << std::endl;

		auto accReadOut = bufVec.get_access<sycl::access::mode::read>();
		std::cout << "Output:" << std::endl;
		for (size_t i = 0; i < N; i++)
		{
			std::cout << accReadOut[i] << ", ";
		}
		std::cout << "END Output" << std::endl;
	}

	//std::cout << num01[0] << ", " << num01[1] << ", " << num01[2] << ", " << num01[SIZE-1] << std::endl;
	//std::cout << num02[0] << ", " << num02[1] << ", " << num02[2] << ", " << num02[SIZE - 1] << std::endl;

	/// Pauses
	std::cin.get();
	return 0;
}


