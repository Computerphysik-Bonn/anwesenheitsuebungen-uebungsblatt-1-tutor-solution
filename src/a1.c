//If you have questions how several functions like fgets() work. Go into your terminal (supposedly the program "man" is installed) and type in: "man fgets()" to see full documentation and possible examples. 


//If you open up the first dataset, dataset1. You see it is all ASCII text, so literal text we can see and interprete. The first line shows uf the number of lines the file has for data. 
//We first will extract that number and use it as a iteration boundary for our for loop.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 16 //Arbitralely chosen, just to be big enough for the given line size.

int main()
{
	FILE *fp; //fp: File pointer
	
	if( (fp = fopen("../data/dataset1", "r") ) == NULL) // Creating a If-Statement in case for some reason the function cannot access the file.
	{
		fprintf(stderr, "Something went wrong opening the file.\n");
		exit(-1);
	}
	
	#ifdef CSQSUM
	FILE *fp_csqsum;
	if ( (fp_csqsum = fopen("../data/csqsum", "w")) == NULL)
	{
		fprintf(stderr, "Something went wrong opening the file.\n");
		exit(-1);
	}
	#endif
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
	
	//One of the tasks is it to store the data into an array. We could use a static array with "data[1000]", but since we cannot guarantee that this would be for every dataset and we want to be a bit more general, we will use a malloc() funtion to store the data in the heap, so we can manage data dynamically.
	//We  create a pointer * of type float, called data. Thise pointer should now point to the first address of a datastructure which is called by malloc(). Each element has the size of float and has lines-times elements.
	//Since the malloc function returns a void pointer, we need to cast it into a float pointer.
	
	float *data = (float*) malloc(sizeof(float)*lines); 
	
	#ifdef CSQSUM
	float csq_sum = 0;
	#endif
	//Now iterating through the dataset1 file.
	for(int i = 0; i < lines; i++)
	{
		fgets(buffer, BUFFER_LENGTH, fp);
		#ifdef DEBUG
			fprintf(stdout, "Data after atof(): %f\n", atof(buffer));
		#endif
		data[i] = atof(buffer);
		#ifdef DEBUG
			fprintf(stdout, "Data in Heap: %f\n", data[i]);
		#endif
		
		#ifdef CSQSUM
		csq_sum += data[i]*data[i];
			#ifdef DEBUG
			fprintf(stdout, "CSQSUM: %f\n", csq_sum);
			#endif
		fprintf(fp_csqsum, "%f\n", csq_sum);
		#endif
	}
	return 0;
}
