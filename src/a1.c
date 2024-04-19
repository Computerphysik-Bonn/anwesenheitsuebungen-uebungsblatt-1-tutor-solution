//If you have questions how several functions like fgets() work. Go into your terminal (supposedly the program "man" is installed) and type in: "man fgets()" to see full documentation and possible examples. 


//If you open up the first dataset, dataset1. You see it is all ASCII text, so literal text we can see and interprete. The first line shows uf the number of lines the file has for data. 
//We first will extract that number and use it as a iteration boundary for our for loop.

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 8 

int main()
{
	FILE *fp; //fp: File pointer
	
	if( (fp = fopen("../data/dataset1", "r") ) == NULL) // Creating a If-Statement in case for some reason the function cannot access the file.
	{
		fprintf(stderr, "Something went wrong opening the file.\n");
		exit(-1);
	}

	char buffer[BUFFER_LENGTH]; //Create buffer for later data storing
	int lines; //Declare variable for the amount of lines to store
	
	//Get the amount of lines
	fgets(buffer, BUFFER_LENGTH, fp); //Stores a line in a file specific to the fp. fgets() will read the line until it encounters a '\n' (new line)-character.
	lines = atoi(buffer);	//Interestingly, this atoi() function can filter a '\n' character if it appears in the buffer.


	//Making sure everything is alright
	//Be careful, here we use some pre-processor definitions, if you don't what it is or what is going on in here, it is neccessary to look it up.
	#ifdef DEBUG
	fprintf(stdout, "%s", buffer);
	fprintf(stdout, "%d\n", lines);
	#endif 
	return 0;
}
