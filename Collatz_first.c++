// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

//-----------------
// struct Cache
//-----------------

struct Precomp_Cache
{
	int b;
	int e;
	int max_cycle_length;
};

//Precomp_Cache * my_precomp_cache = new Precomp_Cache[10000];

int * my_precomp_cache = new int[10001];

void precompute_cache(void)
{
	int i, x, c;
	my_precomp_cache[0] = 0;
	for (i = 0; i<10000; i++)
	{
		x = i;
		c = 1;
		while (x > 1)
		{
			if ((x % 2) == 0)
				x = (x / 2);
			else
				x = (3 * x) + 1;
			++c;
		}
		my_precomp_cache[i] = c;
	}
}

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
	// <your code>
	int curr_num, x, b, e;
	int curr_cycle_length;
	int max_cycle_length = 1;

	//Identify beginning and end

	if (i <= j)
	{
		b = i;
		e = j;
	}
	else
	{
		b = j;
		e = i;
	}

	//cout << "Find max cycle length for range " << b << " to " << e << endl;
	//Loop through the range including the ending number
//	while (curr_num <= end_num)
	for(x = b; x <= e; x++)
	{
		curr_num = x;
		//cout << "Getting the cycle length for " << curr_num << endl;
		curr_cycle_length = 1;
		while (curr_num > 1)
		{
			if ((curr_num % 2) == 0)
				curr_num = (curr_num / 2);
			else
				curr_num = (3 * curr_num) + 1;
			// if (curr_num <= 10000)
			// {
			// 	curr_cycle_length += my_precomp_cache[curr_num];
			// 	break;
			// }
			++curr_cycle_length;
		}

		//cout << "Curr cycle length = " << curr_cycle_length << endl;
		if (curr_cycle_length > max_cycle_length)
			max_cycle_length = curr_cycle_length;
		//cout << "Max cycle length = " << max_cycle_length << endl;
		++curr_num;
	}

	//Save the range and max_cycle_length in an array

	//return 1;
	return max_cycle_length;
}


// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

