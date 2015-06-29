#include <cstdint>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <functional>

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
	int32_t prev = (my_rank + size - 1) % size;
	int32_t next = (my_rank + 1) % size;
	const int32_t DATA_SIZE = 10000;

	mpi::request request;
	int32_t * data = new int32_t[DATA_SIZE];
	int32_t * rcv_buff = new int32_t[DATA_SIZE];
	int32_t * snd_buff = new int32_t[DATA_SIZE];
	int ind = 0;
	std::generate(data, data + DATA_SIZE, [&] () -> int32_t { return ind++; });
	std::copy(data, data + DATA_SIZE, snd_buff);
	int32_t sum = std::accumulate(data, data + DATA_SIZE, 0);

	for(int32_t i = 0; i < size; ++i) {

		if( i > 0 ) {
			world.recv(prev, my_rank, rcv_buff, DATA_SIZE);

			std::transform(data, data + DATA_SIZE, rcv_buff, data, std::plus<int32_t>() );
			request.wait();

			std::swap(rcv_buff, snd_buff);
		}

		if( i < size - 1) {
			request = world.isend(next, next, snd_buff, DATA_SIZE);
		}
	}
	int32_t new_sum = std::accumulate(data, data + DATA_SIZE, 0);
	assert( size*sum == new_sum);

	delete[] data;
	delete[] rcv_buff;
	delete[] snd_buff;

	return 0;
}
