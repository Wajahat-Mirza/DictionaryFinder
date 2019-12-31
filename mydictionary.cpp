/*========================================================Welcome========================================================
Code Written by: Liyan Ibrahim and Muhammad Wajahat Mirza
========================================================Start OF CODE========================================================*/

#include <iostream>
#include <string>
#include<vector> 
#include "binary_search.h"
#include <fstream>
#include <algorithm>

using namespace std; 

char asciitolower(char in) 						
{												
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;									// this is a standard "asciitolower" function, available on and taken from StackOverflow
}

string lower_string(string s)				    // this is the function that converts the Capitalized words to lower 
{												// it is necessary as words "Explore" and "explore" will be interpretted differently
	string t = "";
	int i; 
	for(i = 0; i < s.length(); i++)
	{
		t += asciitolower(s[i]);
	}
	return t;
}

int main(int argc, char** argv)
{
	vector <string> dict; 						// vector stores values in the files  
	vector <string> output;
	string userI; 
	string filename;								//user given dictionary name 
	int max_length = 0;							// this is a variable that holds the longest length of the word available in both dictionaries
	int count = 0; 								// counter
	int num_to_output;

	for (int i = 0; i < argc; i++)				// Code taken from the Lab slides for file name and num of outputs to display
	{
		if (strcmp(argv[i], "-d") == 0 && i < argc-1){
			filename = argv[i+1];				
		}
		else if (strcmp(argv[i], "-l") == 0 && i < argc-1){
			num_to_output = stoi(argv[i+1]);
		}
	}

	cout<< "Filename of dictionary: " << filename << endl;		// Just for user information on which dictionary is being searched
	cout << "Usage ./mydictionary -d <filename> -l < number of words output>" << endl;
	
	ifstream fin(filename);
	if(not fin.is_open()) 						//if file cannot be opened the file
	{
		cout<< "Can not open the dictionary file" <<endl;
		return EXIT_FAILURE;
	}
	
	string str1; 
	while (fin)
	{
		fin >>str1;
		dict.push_back(lower_string(str1));						// this read file's content into the dict vector
		max_length = max(max_length, (int)str1.length());		// this is to find the length of the longest word in the file. To be used later
	}
	fin.close();
	
	while (true)
	{  
		cout << "Please enter your query >> ";
		cin >> userI;
		output.clear();												// this is to clear the output vector 
		userI = lower_string(userI); 								// this de-capitalizes the user input

		if (userI=="quit")
			return EXIT_SUCCESS; 									// quit the program if user types "quit"
		
		count = 0;													// reset the count to zero

/*========================================Case 1: Full word Search====================================================================*/
		if (userI.find('*')==string::npos && userI.find("?")==string::npos)
		{ 
			int left = binary_search(dict, userI, count); 			// call binary search to compare with UserI 
			if(userI.compare(dict[left]) == 0)						// compare the word given by binary search with the User Input 
			{
				cout << "Word found. It is: " << userI << endl;
				cout << count << " word comparisons are carried out" << endl;
			}
			else 
				cout << "Word not found. Try another query" << endl;
		}
/*========================================Case 2: Prefix word Search====================================================================*/

		else if (userI.find("*")!= string::npos)
		{
			int position = userI.find("*");
			string string_1 = userI.substr(0, position);				// this is substring 1 
			string string_2 = userI.substr(0, position);				// this is substring 2

			for (int i = 0; i < max_length - position;i++)				// this finds the max length that is possible for a word in the after "*"
			{															// it does it by subtracting the length of prefix from the length of the longest word in the file
				string_1 += (char)0;									// string 1 is incremented on (char)0
				string_2 += (char)255;									// string 2 is incremented on (char)255
			}

			int below = binary_search(dict, string_1, count);			// binary search is called using substring 1 and stored in below
			int above = binary_search(dict, string_2, count);			// binary search is called using substring 2 and stored in above
			
			if (dict[below].substr(0, position).compare(userI.substr(0, position)) != 0)		// the result of binary search is compared with userI prefix
			{
				below ++;																		// ++ to get the exact word while doing binary search. increase below 
			} 
			if (dict[above].substr(0, position).compare(userI.substr(0, position)) != 0)
			{
				above --;																		// -- to get the exact word while doing binary search. decrease above 
			} 
			
			if (above < below)											// if above becomes smaller than below, no word is found
			{
				cout << "ZERO word found" << endl;
				continue;
			}
			
			cout << above - below + 1 << " words found with the given prefix " << userI.substr(0,position) << endl;		// above - below gives the range of words that match with the prefix. + 1 is added to avoid index count error

			for (int i = below; i <= above; i ++)
			{
			 	output.push_back(dict[i]);								// in the range of above - below, those matched words are pushed back into the output vector
			 }
			for (int i=0; i < min(num_to_output, (above-below + 1)); i++)				// there is min here to check whether the num of words found are smaller or the "-l"
			{
				cout << output[i]<<endl;
			}
			cout << count<< " Total ccomparisons up-to first match" << endl;

		}
/*========================================Case 3: Wildcard word Search====================================================================*/

		else if (userI.find("?")!= string::npos)
		{
			int position = userI.find("?");						// finds the position of "?"
			for (int i = 33; i < 127; i++)						// iterate through ASCII code from 33 to 126
			{
				userI[position] = (char) i;						// replace "?" with the ASCII code at i

				int left = binary_search(dict, userI, count); 	// call binary search on the ith ASCII code at "?"
				if(userI.compare(dict[left]) == 0)				// compare between the UserI and binary search return value
				{
					output.push_back(userI);					// push back the match into output vector
				}
			}
			if (output.size() == 0)
			{
				cout << "No word was matched in this case" << endl;
			} 
			else
			{
				for (int i=0; i < min(num_to_output, (int)output.size()); i++)		// this is to satisfy the user need of "-l"
				{
					cout << output[i]<<endl;						// matched words are displayed to the number of outputs asked at -l
				}
			}
			cout << count << " Total ccomparisons" << endl;
		}
	}
return 0; 

}
/*========================================================END OF CODE========================================================*/
