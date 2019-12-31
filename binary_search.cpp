/*========================================================Welcome============================================================
Code Written by: Liyan Ibrahim and Muhammad Wajahat Mirza
========================================================Start OF CODE========================================================*/

#include <iostream>
#include <string>
#include<vector> 
#include <fstream>

using namespace std;

int binary_search(vector<string> dic, string user_I, int& count)  // args: vector of dictionary strings, user input as String, and reference to the counter
{
	int middle;
	int left = 0; 
	int right = dic.size() - 1;        							  // this finds the size of right 

	while (left < right)										  // left should always be less than right. 
	{
		count++;
		middle = left + ((right - left)/2);						  // finds middle of the vector. right - left is subtracting smaller num from bigger so it does not overflow
																  // This middle will always be less than right
		if (user_I.compare(dic[middle]) == 0)					  // User input is compared with the middle of the dictionary vector
		{
			return middle;										  // if it is == 0, return the middle
		}
		else if (user_I.compare(dic[middle]) > 0)
		{
			left = middle + 1;									  // if it is > 0, then left will become increment of middle
		}
		else 
		{
			right = middle - 1;									  // else i.e. if it is < 0, right will become decrement of middle
		}
	}
	return left;
}
/*========================================================End OF CODE========================================================*/
