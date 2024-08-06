#!/bin/bash

# Check for root access
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

# Part 1
echo "------Compiling run.cpp------"
g++ -O3 run.cpp -o run
echo "Successful!"

# Execute Part 1
# ./run <filename> [-r|-w] <block_size> <block_count>
echo "To reproduce result (File Size: 2.00 GB): ./run test -w 1024 1048576"
echo "To check reasonable time: ./run test -r 1024 1048576"

# Part 2
echo "------Compiling run2.cpp------"
g++ -O3 run2.cpp -o run2
echo "Successful!"

# Execute Part 2
# ./run2 <filename> <block_size> 
echo "To check block count: ./run2 test 1024"

# Part 3
echo "------Compiling raw_performance.cpp------"
g++ -O3 raw_performance.cpp -o raw_performance
echo "Successful!"

# Execute Part 3
echo "For each block size: ./raw_performance <filename> <block_size>"

# Part 4
echo "------Compiling caching.cpp------"
g++ -O3 caching.cpp -o caching
echo "Successful!"

# Execute Part 4
# To generate all results at once: ./caching <filename>
echo "For all caching results: ./caching <filename>"

# Part 5
# Generate executables for Part 5

echo "------Compiling syscall_normal.cpp, syscall_lseek.cpp, syscall_pid.cpp, syscall_hostid.cpp------"
g++ -O3 syscall_normal.cpp -o syscall_normal
g++ -O3 syscall_lseek.cpp -o syscall_lseek
g++ -O3 syscall_pid.cpp -o syscall_pid
g++ -O3 syscall_hostid.cpp -o syscall_hostid
echo "Successful!"

# Execute Part 5
echo "To run syscall results: ./syscall_<name> <filename>"

# Part 6
# Generate executables for Part 6
echo "------Compiling fast.cpp------"
g++ -O3 -pthread fast.cpp -o fast
echo "Successful!"

# Execute Part 6
echo "To get XOR value: ./fast <filename>"
echo "To reproduce report results: uncomment line 69, comment line 70, compile, and run again"

# End
echo "All files have been compiled! Please see README.txt for additional information. Thank you!"
