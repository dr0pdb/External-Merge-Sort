#ifndef _SORT_H
#define _SORT_H

	#include <iostream>

	void create_initial_runs(std::string input_file, int page_size, int number_blocks);
	void merge_files(std::string output_file, int page_size, int number_blocks);

#endif 