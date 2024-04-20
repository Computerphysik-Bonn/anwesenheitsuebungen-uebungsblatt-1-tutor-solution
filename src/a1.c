//If you have questions how several functions like fgets() work. Go into your terminal (supposedly the program "man" is installed) and type in: "man fgets()" to see full documentation and possible examples. 


//If you open up the first dataset, dataset1. You see it is all ASCII text, so literal text we can see and interprete. The first line shows uf the number of lines the file has for data. 
//We first will extract that number and use it as a iteration boundary for our for loop.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DATASET2
	#include <math.h>
#endif

//Arbitralely chosen, just to be big enough for the given line size.
#define BUFFER_LENGTH 16 

int main()
{
	//fp: File pointer
	FILE *fp; 
	
	//Be careful, here we use some pre-processor definitions, if you don't what it is or what is going on in here, it is neccessary to look it up. But do not worry it is not hard.
	#ifdef DATASET1
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
		//We can redirect the output not only to stdout or stderr, but directly into a file, by using the defined file pointer.
		fprintf(fp_csqsum, "%f\n", csq_sum);
		#endif
	}
	#endif




	#ifdef DATASET2
	if( (fp = fopen("../data/dataset2", "r")) == NULL)
	{
		fprintf(stderr, "Something went wrong opening the file.\n");
		exit(-1);
	}
	FILE *fp_store;
	if( (fp_store = fopen("../data/tabular", "w")) == NULL)
	{
		fprintf(stderr, "Something went wrong opening the file.\n");
	}
	int length;
	//Since dataset2 is literally a binary file where we cannot read from it as it was with the dataset1, we have to use other functions. 
	//fread has 4 Arguments
	//	1. Address of value to store.
	//	2. Size of bytes to be read.
	//	3. Amount of byte-blocks to be read.
	//	4. File pointer.
	//
	//	For further documentation see "man fread" in the terminal or on the linux C documentation pages.
	fread(&length ,4, 1, fp);
	#ifdef DEBUG
		fprintf(stdout, "%d\n", length);
	#endif

	//Create array in the heap with malloc just as before.
	double *data = (double *) malloc(sizeof(double)*length);
	for(int i = 0; i < length; i++)
	{
		fread(&(data[i]), 8, 1, fp);
		#ifdef DEBUG
		fprintf(stdout, "%f\t%f\n", data[i], sin(data[i]));
		#endif
		fprintf(fp_store, "%f\t%f\n", data[i], sin(data[i]));
		
	}
	#endif

	//If you look closely, you maybe see that we actually do not need the malloc function in here. We could just simply offloaded the current read value into a variable and then directly wrote it into a file which would make the code much more efficient. The malloc function is just here for demonstration purposes.
	//If you are curious about efficiency in you programs. You can use the "perf" programm in you terminal and make benchmarks. But not only for benchmarks, you can also debug with it. Give it a try!

	return 0;
}
