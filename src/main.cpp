#include <utils.h>
#include <sort.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ctime>

int main(int argc, char const *argv[])
{
	std::cout<<"-------------------------------------------------------\n";
	std::cout<<"Welcome to the External Merge Sort Algorithm  Program\n";
	std::cout<<"-------------------------------------------------------\n\n";

	std::cout<<"Generating a random file....\n";
	std::string input_file = "random_text_file.txt";
	std::string output_file = "output_file.txt";
	generate_random_text_file(input_file, 10240); // Generate a random 10 KB file.

	int page_size = 1024; // 1 KB page size.
	int number_blocks = 10; // 10 runs. page_size * number_blocks == file size.

	std::cout<<"Creating initial runs....\n";
	// create initial runs/partitions of the file to be sorted.
	create_initial_runs(input_file, page_size, number_blocks);

	std::cout<<"Merging scratch files....\n";

	// merge the sorted file together to form the final sorted file.
	merge_files(output_file, page_size, number_blocks);
	std::cout<<"Sorted Output file has been successfully created!";
	std::cout<<"-------------------------------------------------------\n";
	std::cout<<"---------------        Bye        --------------------\n";
	std::cout<<"-------------------------------------------------------\n\n";
	return 0;
}