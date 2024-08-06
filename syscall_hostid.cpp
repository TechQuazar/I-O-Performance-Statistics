#include <iostream>
#include <fstream>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>

using namespace std;
using namespace chrono;

double measureLseek_block_count(const char *fileName)
{
	int fd = open(fileName, O_RDONLY);

	if (fd == -1)
	{
		cerr << "Error opening file for reading." << endl;
		return -1.0;
	}
	long long counter = 0;
	auto start = high_resolution_clock::now();

	while (true)
	{
		int id = gethostid();

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<seconds>(stop - start);
		if (duration.count() == 10)
		{
			break;
		}
		counter += 1;
	}

	// auto stop = high_resolution_clock::now();
	// auto duration = duration_cast<seconds>(stop - start);

	close(fd);

	return counter;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: ./syscall_gethostid <filename>" << endl;
		return 1;
	}

	const char *fileName = argv[1];
	// long long block_size = stoi(argv[2]);
	// long long block_count = stoll(argv[3]);
	// As small block will take forever, we will find the performance for 10 seconds of read operation

	double blocks = measureLseek_block_count(fileName);
	// cout << "Lseek duration: " << durationLseek << " seconds" << endl;
	double performance = (double)(blocks) * (1) / (10) / (1024 * 1024); // MiB/s
	cout << "gethostid Performance: " << performance << " MiB/s" << endl;
	cout << "Number of equivalent system calls: " << performance * (1024 * 1024) << " syscall/s" << endl;
	return 0;
}
