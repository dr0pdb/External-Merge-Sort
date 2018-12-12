#include <sort.h>
#include <utils.h>
#include <vector>
#include <algorithm>
#include <queue>

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

/*
	Merges the created input scratch files to sort the entries.
*/
void merge_files(std::string output_file, int page_size, int number_blocks) {
	FILE *input_scratch_files[number_blocks]; // These are output scratch files created in the first step.
	char read_mode = 'r', write_mode = 'w';
	for (int i = 0; i < number_blocks; ++i)
	{
		input_scratch_files[i] = openFile(std::to_string(i), &read_mode);
	}

	FILE *final_output = openFile(output_file, &write_mode);

	// sort using heap-sort.
	std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int> >, std::greater<std::pair<int,int> > > heap;
	int i, value; 
    for (i = 0; i < number_blocks; i++) 
    { 
        if (fscanf(input_scratch_files[i], "%d ", &value) != 1) 
            break; 
  
  		heap.push({value, i}); // push the value and index of the scratch file in the min heap. 
    } 

    int done = 0; // holds the number of scratch file which are done.
    while(done != i) {
    	std::pair<int,int> current = heap.top();
    	heap.pop();

    	fprintf(final_output, "%d ", current.first);

  		if (fscanf(input_scratch_files[current.second], "%d ", &value) != 1) {
  			done++; // we are done with this input file.
  		} else {
  			//insert next value from the input file to the heap.
  			heap.push({value, current.second});
  		}
    }

	// close the file streams.
	for (int i = 0; i < number_blocks; ++i)
	{
		fclose(input_scratch_files[i]);
	}

	fclose(final_output);
}
