#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <cstring>
#include <chrono>

using namespace std;

int readFile(const char *filename, int block_size)
{
	ifstream file(filename, ios::binary);

	if (!file.is_open())
	{
		return -1;
	}
	long long block_count = 0;

	while (!file.eof())
	{
		char buffer[block_size];
		file.read(buffer, block_size);

		// Increment the block count
		block_count++;
	}

	file.close();
	return block_count;
}

double rawPerformance(const char *filename, int block_size)
{
	cout << "----------------------------" << endl;
	auto start = chrono::high_resolution_clock::now();
	int block_count = readFile(filename, block_size);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	if (block_count != -1)
	{
		cout << "File read successfully!" << endl;
	}
	else
	{
		cout << "Error in reading file!" << endl;
	}
	cout << "Block count: " << block_count << endl;
	cout << "Block size:" << block_size << endl;
	cout << "Duration: " << duration.count() << endl;
	double performance = (double)(block_count) / (duration.count()) * (block_size) / (1024 * 1024) * (1000); // MiB/s
	cout << "Performance is: " << performance << " MiB/s" << endl;
	cout << "----------------------------" << endl;
	return performance;
}

int clearCache()
{
	// Clear the file system cache by dropping caches
	return system("sudo sh -c \"/usr/bin/echo 3 > /proc/sys/vm/drop_caches\"");
}
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "Usage: ./caching <filename> " << endl;
		return 1;
	}

	const char *filename = argv[1];
	// int block_size = stoi(argv[2]);
	vector<int> blockSizes = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304};
	vector<int> perf = {};
	vector<int> perf_c = {};
	int res = clearCache();
	for (int block_size : blockSizes)
	{
		// Run without cache
		cout << "Without Caching:" << endl;
		int rate = rawPerformance(filename, block_size);
		perf.push_back(rate);
		// Run with cache
		cout << "With Caching:" << endl;
		rate = rawPerformance(filename, block_size);
		perf_c.push_back(rate);
		res = clearCache();
	}
	cout << "Performace Array without Caching:" << endl;
	for (auto x : perf)
	{
		cout << x << ", ";
	}
	cout << endl;

	cout << "Performace Array with Caching:" << endl;
	for (auto x : perf_c)
	{
		cout << x << ", ";
	}
	cout << endl;

	// int duration = resonableTime(filename, block_size);

	return 0;
}
