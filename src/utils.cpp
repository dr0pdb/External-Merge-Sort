#include <utils.h>

/*
	Generates a random text file with the name and the size provided as arguments.
*/
void generate_random_text_file(std::string file_name, int file_size) {
	std::ofstream created_file;
	created_file.open(file_name.c_str());

	int current_size = 0; // stores the current size of the generated file.
	int word_size; // stores the size of the random word generated.
	int number; // stores the current number being written in the generated file.

	while(current_size < file_size) {
		word_size = 1 + rand()%10;
		
		// prevents accidentally surpassing the desired file size.
		while(current_size + word_size > file_size) {
			word_size = 1 + rand()%10;
		}

		for (int i = 0; i < word_size; ++i)
		{
			number = rand(); // assign a random number.
			created_file << number;
		}
	}

	created_file.close();
	std::cout<<file_name<<" has been successfully generated\n";
}

FILE* openFile(std::string file_name, char* mode) 
{ 
    FILE* fp = fopen(file_name.c_str(), mode); 
    if (fp == NULL) 
    { 
        perror("Error while opening the file.\n"); 
        exit(EXIT_FAILURE);
    } 
    return fp; 
} 