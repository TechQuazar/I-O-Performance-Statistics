#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <cstring>
#include <chrono>

using namespace std;
using namespace chrono;

int NUM_THREADS = 4;

void readBlock(const char *fileName, int threadId, int blockSize, vector<int> &result)
{
	ifstream inFile(fileName, ios::binary);

	if (!inFile.is_open())
	{
		cerr << "Error opening file for reading." << endl;
		return;
	}

	inFile.seekg(threadId * blockSize, ios::beg);

	char buffer[blockSize];
	int *intBuffer = reinterpret_cast<int *>(buffer);

	while (inFile)
	{
		inFile.read(buffer, blockSize);
		long long bytesRead = static_cast<long long>(inFile.gcount());

		for (long long i = 0; i < bytesRead / sizeof(int); ++i)
		{
			result[threadId] ^= intBuffer[i];
		}

		inFile.seekg((NUM_THREADS - 1) * blockSize, ios::cur);
	}

	inFile.close();
}
int clearCache()
{
	// Clear the file system cache by dropping caches
	return system("sudo sh -c \"/usr/bin/echo 3 > /proc/sys/vm/drop_caches\"");
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: ./fast <file_to_read>" << endl;
		return 1;
	}

	const char *fileName = argv[1];

	ifstream inFile(fileName, ios::binary | ios::ate);
	if (!inFile.is_open())
	{
		cerr << "Error opening file for reading." << endl;
		return 1;
	}

	size_t fileSize = static_cast<size_t>(inFile.tellg());
	inFile.close();

	// vector<int> blockSizes = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304};
	vector<int> blockSizes = {1048576};
	cout << "Block Size \t\tXOR \t\tDuration" << endl;
	for (auto blockSize : blockSizes)
	{
		int res = clearCache();
		// The no. of blocks that each thread will run
		long long numBlocks = fileSize / (NUM_THREADS * blockSize);
		vector<int> result(NUM_THREADS, 0); // Results from threads

		vector<thread> threads;
		auto start = high_resolution_clock::now();
		for (int i = 0; i < NUM_THREADS; ++i)
		{
			threads.emplace_back(readBlock, fileName, i, blockSize, ref(result));
			// emplace_back is better when using a vector of threads
		}
		// Wait for all threads to finish
		for (thread &t : threads)
		{
			t.join();
		}
		// Calculate the final XOR result
		int finalResult = result[0];
		for (int i = 1; i < result.size(); ++i)
		{
			finalResult ^= result[i];
		}
		auto stop = high_resolution_clock::now();
		int duration = duration_cast<seconds>(stop - start).count();
		// Print the result
		// cout << blockSize << "\t\t" << (finalResult) << endl;
		printf("%d \t\t\t%08x\t\t%d \n", blockSize, finalResult, duration);
	}

	return 0;
}
