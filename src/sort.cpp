#include <sort.h>
#include <utils.h>
#include <vector>
#include <algorithm>

/*
	Creates initial runs for the external merge sort algorithm.
*/
void create_initial_runs(std::string input_file, int page_size, int number_blocks) {
	char read_mode = 'r', write_mode = 'w';
	FILE *in = openFile(input_file, &read_mode);

	FILE *out_scratch_files[number_blocks];
	for (int i = 0; i < number_blocks; ++i)
	{
		out_scratch_files[i] = openFile(std::to_string(i), &write_mode); // name the files 0,1,2, .... number_blocks-1
	}

	std::vector<int> v(page_size);
	bool done = false;
	int current_file = 0, index;

	while(!done) {
		// write run_size elements into in-memory vector from input file
        for (index = 0; index < page_size; index++) 
        { 
            if (fscanf(in, "%d ", &v[index]) != 1) 
            { 
                done = true;
                break; 
            }
        }

        // sort the vector
        std::sort(v.begin(), v.end());

        // write the sorted data to output scratch file.
        for (int j = 0; j < index; ++j)
        {
        	fprintf(out_scratch_files[current_file], "%d ", v[j]);
        }

        current_file++;
        current_file %= number_blocks;
	}

	// close the file streams.
	for (int i = 0; i < number_blocks; ++i)
	{
		fclose(out_scratch_files[i]);
	}

	fclose(in);
}