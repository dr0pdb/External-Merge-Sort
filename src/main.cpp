#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <ctime>
using namespace std;

/*
	Generates a random text file with the name and the size provided as arguments.
*/
void generate_random_text_file(string file_name, int file_size) {
	ofstream created_file;
	created_file.open(file_name.c_str());

	int current_size = 0; // stores the current size of the generated file.
	int word_size; // stores the size of the random word generated.
	char letter; // stores the current letter being written in the generated file.

	while(current_size < file_size) {
		word_size = 1 + rand()%10;
		
		// prevents accidentally surpassing the desired file size.
		while(current_size + word_size > file_size) {
			word_size = 1 + rand()%10;
		}

		for (int i = 0; i < word_size; ++i)
		{
			letter = 'a' + rand()%26; // assign a random letter.
			created_file << letter;
		}
	}

	created_file.close();
	cout<<file_name<<" has been successfully generated\n";
}

int main(int argc, char const *argv[])
{
	
	return 0;
}