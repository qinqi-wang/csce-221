//============================================================================
// Name        : sort.cpp
// Author      : Qinqi Wang and Dhananjay Khanna
// Date        : September 27, 2015
// Copyright   : Open Source
// Description : Read an integer sequence and display the sorted sequence
/*
 *     Usage: ./sort [-a ALGORITHM] [-f INPUTFILE] [-o OUTPUTFILE] [-h] 
 *     [-d] [-p] [-t] [-c] 
 *     Example: ./sort -a S -f input.txt -o output.txt -t -c -d
 *              ./sort -h
 *     Options: 
 *       -a ALGORITHM    Use ALGORITHM to sort. 
 *                       ALGORITHM is a single character representing an algorithm: 
 *                         S   (selection sort) 
 *                         B   (bubble sort) 
 *                         I   (insertion sort) 
 *                         H   (shell sort)
 *                         R   (radix sort) 
 *       -f INPUTFILE    Obtain integers from INPUTFILE instead of STDIN 
 *       -o OUTPUTFILE   Place output message into OUTPUTFILE instead of STDOUT 
 *       -h              Display this help and exit 
 *       -d              Display input: unsorted integer sequence
 *       -p              Display output: sorted integer sequence 
 *       -t              Display running time of the chosen algorithm in milliseconds 
 *       -c              Display number of element comparisons (excluding radix sort)
 */
//============================================================================

#include <iostream>
#include <iterator>
#include <sys/time.h>
#include <cstdio>
#include "option.h"
#include "sort.h"
#include <limits>
#include <cstdlib>
#include <vector>
#include <ostream>
#include <fstream>
#include "rand-file.h"

using namespace std;

/* read input sequence from STDIN */
int readInput(int A[], int& size) {
   /* read integers to sort */
   for (int i = 0; i < size; i++)
      if (!(cin >> A[i])) {
         cerr << "sort: input data error" << endl;
         return 1; //exit abnormally
      }  
   
   return 0; //exit normally
}

/* display elements of array A seperated by new lines */
void printArray(const int A[], int size) {
   copy(A, A+size, ostream_iterator<int>(cout,"\n"));// call standard function
                                                     // "copy" to display
                                                     // the array
   cout << endl;  
}

// returns true if sorted as increasing sequence
// returns false otherwise
bool Sort::testIfSorted(int A[], int size)
{
   for (int i = 1; i < size; ++i)
      if (A[i-1] > A[i]) return false;
   return true;
}

int main(int argc, char** argv)
{
   Option op;
   bool radixsortQ = false;
   
   /* initialize program options */
   try {
      op.init(argc,argv);
   } catch (Option::InvalidArgument& ex) {
      cerr << ex.what() << endl;
      return 1;
   }
   
   /* show help message and exit */
   if (op.showHelp()) {
      op.printUsage();
      const unsigned int max_int = std::numeric_limits<int>::max();
      cout << "NOTE: The Radix Sort sorts " << -(int)((max_int+1)/2) << " to " << (max_int+1)/2-1 << endl;
      return 0; //exit normally
   }
   
   const char *input_file, *output_file;

   cout << "How do you wish for the numbers to be generated? " << endl
		 << "1. Random order" << endl
		 << "2. Increasing order" << endl
		 << "3. Decreasing order" << endl;
	int order_int=0;
	cin >> order_int;
   
   /* If provided input file, reopen standard input onto that file
      so that we only need to deal with standard input. */
   if ((input_file=op.getInputFile()) &&
       freopen(input_file, "r", stdin) == 0) {
      cerr << "sort: " << input_file << ": no such file" << endl;
      return 1;
   }
	
   /* If provided output file, reopen standard output onto that file
      so that we only need to deal with standard output. */
   if ((output_file=op.getOutputFile()) &&
       freopen(output_file, "w", stdout) == 0) {
      cerr << "sort: " << output_file << ": No such file" << endl;
      return 1; //exit abnormally
   }  
  
   /* read number of integers */
   int size; //number of integers  
   if (!(cin >> size)) return 1; //exit abnormally
    
   /* read input integers */
   int* A=new int[size]; //stores integers  
   if (readInput(A,size)) //call global function
      return 1; //exit abnormally

   /* create an sorting object with appropriate algorithm */
   Sort* s;
   switch(op.getAlg()) 
      {
      case 'S':
         s=new SelectionSort();
         break;
      case 'I':
         s=new InsertionSort();
         break;
      case 'B':
         s=new BubbleSort();
         break;
      case 'H':
         s=new ShellSort();
         break;
      case 'R':
         s=new RadixSort();
         radixsortQ = true;
         break;
      }

	struct timeval start, end;
	double total_time, avg_time, diff, total_cmps, avg_cmps;
	int times_run=1;
	for(int i=0; i<times_run; ++i) {
		generate(A, size, order_int);
	   
	    /* show unsorted input sequence */
		if (op.showInput()) {
			cout << "Unsorted sequence:" << endl;
			printArray(A,size); //call global function to display the array
        }
	    s->resetNumCmps();
	    /* begin timing the chosen algorithm using time.h library*/
	    gettimeofday(&start,0);
	   
	    /* call sorting function to sort */
	    s->sort(A,size);  
	   
	    /* end timing */
	    gettimeofday(&end,0);
	   
	    /* output sorted sequence */
	    if (op.showOutput()) {
		    cout << "Sorted sequence:" << endl;
		    printArray(A,size); //call global function to display the array
	    }
	    //add time to get total time
	    diff = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec)/1e6;
	    total_time+=diff;
		total_cmps+=s->getNumCmps();
    }
	avg_time=total_time/times_run;
	avg_cmps=total_cmps/times_run;
   
   /* show running time of the algorithm to sort input data */
   if (op.showTime()) {
      cout << "Average Running time: "
           << avg_time  
           << " sec" << endl;
   }
   /* show number of comparisons in the algorithm */
   if (op.showNumCmps()) {
      if (radixsortQ) {
         cout << "No comparisons for radix sort"
              << endl;
      } else {
         cout << "Average # Comparisons: "
              << avg_cmps << endl;
      }
   }

   if (!s->testIfSorted(A, size)) {
      cerr << "Warning: The sorted sequence IS NOT sorted!\n"
           << endl;
   }
   
  // it may be useful for Windows
   // char ch;
   // cin >> ch;
   return 0;

}
