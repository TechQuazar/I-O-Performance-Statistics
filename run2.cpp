#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

using namespace std;

void printUsage()
{
	cout << "Usage: ./run2 <filename> <block_size>\n";
}

long long estimateFileSize(const char *filename, int block_size)
{
	auto start = chrono::high_resolution_clock::now();
	ifstream file(filename, ios::binary);

	if (!file.is_open())
	{
		// cerr << "Error opening file for reading." << endl;
		return 0;
	}

	char *buffer = new char[block_size];
	int flag = 0;
	long long block_count = 0;

	while (!file.eof())
	{
		file.read(buffer, block_size);
		block_count += 1;
		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
		if (duration > 15)
		{
			cout << "File too large! Time Taken: " << duration << " seconds" << endl;
			return -1;
		}
		// printf("Block: %d => %s\n", i, buffer);
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
	if (duration < 5)
	{
		cout << "File not large enough! Time Taken: " << duration << " seconds" << endl;
		return -1;
	}

	cout << "File read in: " << duration << " seconds! [Reasonable Time]" << endl;
	// cout << "Flag: " << flag << endl;
	// cout << "VC: " << vc << endl;
	delete[] buffer;
	file.close();
	return block_count;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printUsage();
		return EXIT_FAILURE;
	}

	const char *filename = argv[1];
	int block_size = atoi(argv[2]);

	if (block_size <= 0)
	{
		cerr << "Block size must be a positive integer.\n";
		return EXIT_FAILURE;
	}

	long long block_count = estimateFileSize(filename, block_size);
	cout << "Block count for reasonable read time: " << block_count << endl;
	cout << "Estimated file size for a reasonable read time: " << block_count * block_size << " bytes\n";

	return EXIT_SUCCESS;
}
