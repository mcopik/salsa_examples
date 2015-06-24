#include <cstdint>
#include <vector>
#include <iostream>
#include <cassert>

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/nonblocking.hpp>

/**
 * In this example each process communicates with every other process.
 * No other method calls, just communicate N times with N process.
 */

namespace mpi = boost::mpi;

using std::vector;
using std::cout;
using std::endl;

int main(int argc, char ** argv) 
{

	mpi::environment env(argc, argv);
	mpi::communicator world;

	int32_t my_rank = world.rank();
	int32_t size = world.size();


	vector<mpi::request> requests;
	int32_t * recvs = new int32_t[size];

	for(int32_t i = 0; i < size; ++i) {

		if(my_rank == i) {
			//dont send msg to yourself
			continue;
		}

		// send i+1 times
		for(int32_t j = 0; j < (i + 1); ++j) {
			requests.push_back( world.isend(i, 0, j) );
		}
		// receive my_rank + 1 times
		for(int32_t j = 0; j < (my_rank + 1); ++j) {
			requests.push_back( world.irecv(i, 0, recvs[i]) );
		}
	}

	mpi::wait_all( requests.begin(), requests.end() );

	// the order of messages for same rank/src/dst should not be changed
	// so test if everything is order - for i-th process, we should get i in exchange

	for(int32_t i = 0;i < size; ++i) {
		if(my_rank == i) {
			continue;
		}

		assert( recvs[i] == my_rank);
	}

	delete[] recvs;

	return 0;
}
