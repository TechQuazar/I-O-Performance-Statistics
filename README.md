\*Some results are obtained manually and hence can not be put in the script. Therefore, script.sh will compile all files and
give instructions on how to run them. More detailed instructions to replicate everything are given below.

1. Please ensure you have root access before running the files
2. For Part 1, generate the executable using: g++ -O3 run.cpp -o run
3. To execute: ./run <filename> [-r|-w] <block_size> <block_count>
4. To reproduce result, create a file size of 2.00 GiB using: ./run test -w 1024 1048576
5. To check reasonable time, ./run test -r 1024 1048576
6. For Part 2, generate the executable using: g++ -O3 run2.cpp -o run2
7. To check the block count, ./run2 <filename> <block_size>
8. For Part 3, generate the executable using: g++ -O3 raw_performance.cpp -o raw_performance
9. To generate the results in the report, for each block size run: ./raw_performance <filename> <block_size>
10. For Part 4, generate the executable using: g++ -O3 caching.cpp -o caching
11. To generate all the results at once (all block_sizes have been coded already), run: ./caching <filename>
12. For Part 5, four executables need to be generated - syscall_normal, syscall_lseek, syscall_pid, syscall_hostid
13. Generate the executables using: g++ -O3 syscall*<name>.cpp -o syscall*<name>
14. Run the executables using (everything else has been coded): ./syscall\_<name> <filename>
15. For Part 6, generate the executables using: g++ -O3 -pthread fast.cpp -o fast
16. To get the XOR value (with optimal settings): ./fast <filename>
17. To reproduce report results, uncomment line 69 and comment line 70, compile and run again.
18. End, thank you! (Graphs have been generated using a Graphs.ipynb which will be included)
