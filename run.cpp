#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

using namespace std;

int writeFile(const char *filename, int block_size, int block_count)
{
	ofstream file(filename, ios::binary);

	if (!file.is_open())
	{
		// cerr << "Error opening file for writing." << endl;
		return 0;
	}

	// Initialize a buffer for writing to file
	char *buffer = new char[block_size];
	// Set that buffer to some value, here 'A'*block_size
	memset(buffer, '0', block_size);
	// Write that buffer to file
	for (int i = 0; i < block_count; ++i)
	{
		file.write(buffer, block_size);
	}

	delete[] buffer;
	file.close();

	// cout << "File written successfully!" << endl;
	// Return 1 for success, 0 for failure -> print statements take time
	return 1;
}

int readFile(const char *filename, long long block_size, long long block_count)
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
	long long vc = 0;

	for (int i = 0; i < block_count; ++i)
	{
		if (!file.eof())
		{
			file.read(buffer, block_size);
		}
		else
		{
			flag = 1;
			break;
		}
		vc += 1;
		// printf("Block: %d => %s\n", i, buffer);
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "Duration: " << duration << " seconds" << endl;
	// cout << "Flag: " << flag << endl;
	// cout << "VC: " << vc << endl;

	delete[] buffer;
	file.close();
	return 1;
}

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		cerr << "Usage: ./run <filename> [-r|-w] <block_size> <block_count>" << endl;
		return 1;
	}

	const char *filename = argv[1];
	const char *mode = argv[2];
	long long block_size = stoll(argv[3]);
	long long block_count = stoll(argv[4]);

	if (strcmp(mode, "-w") == 0)
	{
		int res = writeFile(filename, block_size, block_count);
		if (res == 1)
		{
			cout << "File written successfully!" << endl;
		}
		else
		{
			cout << "Error in writing to file!" << endl;
		}
	}
	else if (strcmp(mode, "-r") == 0)
	{
		int res = readFile(filename, block_size, block_count);
		if (res == 1)
		{
			cout << "File read successfully!" << endl;
		}
		else
		{
			cout << "Error in reading file!" << endl;
		}
	}
	else
	{
		cerr << "Invalid mode. Use -r for reading or -w for writing." << endl;
		return 1;
	}

	return 0;
}
