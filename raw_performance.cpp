#include <iostream>
#include <fstream>
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
	// cout << "Block count: " << block_count << endl;
	// cout << "Block size:" << block_size << endl;
	// cout << "Duration: " << duration.count() << endl;
	double performance = (double)(block_count) / (duration.count()) * (block_size) / (1024 * 1024) * (1000); // MiB/s
	cout << "Performance is: " << performance << " MiB/s" << endl;
	cout << "----------------------------" << endl;
	return performance;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cerr << "Usage: ./raw_performance <filename>  <block_size>" << endl;
		return 1;
	}

	const char *filename = argv[1];
	int block_size = stoi(argv[2]);

	// int duration = resonableTime(filename, block_size);

	int rate = rawPerformance(filename, block_size);

	return 0;
}
