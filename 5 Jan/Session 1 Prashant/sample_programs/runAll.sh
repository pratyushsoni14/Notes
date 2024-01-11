#!/bin/bash

rm -rf a.out myfile.txt sample.txt

echo "\n##########Running normal write in file.##########\n"
g++ write_normal.cpp 
./a.out 

echo "\n##########Running write in append mode in file.##########\n"
g++ write_append.cpp 
./a.out 

echo "\n##########Running write in truncate mode in file.##########\n"
g++ write_truncate.cpp 
./a.out 

echo "\n##########Running tellg and tellp function in file.##########\n"
g++ file_pos_tell.cpp 
./a.out 

echo "\n##########Running seekg and seekp function in file.##########\n"
g++ file_pos_seek.cpp 
./a.out 

echo "\n##########Running read with get in file.##########\n"
g++ read_get.cpp 
./a.out 

echo "\n##########Running read with getline in file.##########\n"
g++ read_getline.cpp 
./a.out 

rm -rf a.out myfile.txt sample.txt
