#include <iostream>
#include <fstream>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

using namespace std;
using namespace chrono;

double measureRead_block_count(const char *fileName)
{
	int fd = open(fileName, O_RDONLY);

	if (fd == -1)
	{
		cerr << "Error opening file for reading." << endl;
		return -1.0;
	}
	long long block_count = 0;
	char buffer[1]; // 1 byte to be read
	auto start = high_resolution_clock::now();
	while (true)
	{
		int res = read(fd, buffer, sizeof(buffer));

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(stop - start);
		if (duration.count() == 10)
		{
			break;
		}
		block_count += 1;
	}

	close(fd);
	return block_count;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: ./syscall_normal <filename>" << endl;
		return 1;
	}

	const char *fileName = argv[1];
	// long long block_size = stoi(argv[2]);
	// long long block_count = stoll(argv[3]);
	// As small block will take forever, we will find the performance for 10 seconds of read operation
	double blocks = measureRead_block_count(fileName);
	double performance = (double)(blocks) * (1) / (10) / (1024 * 1024); // MiB/s
	cout << "Read Performance: " << performance << " MiB/s" << endl;
	cout << "Number of equivalent system calls: " << performance * (1024 * 1024) << " syscall/s" << endl;

	return 0;
}
