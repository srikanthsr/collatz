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

const int LAZY_CACHE_SIZE = 1000000;
unsigned short lazy_cache[LAZY_CACHE_SIZE] = {0};

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

int collatz_eval (int i, int j)
{
        // <your code>
	int curr_num, x, b, e;
	int curr_cycle_length;
	int max_cycle_length = 1;

	// Identify beginning and end
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

	//Populate first 2 entries of lazy cache
	lazy_cache[0] = 0;
	lazy_cache[1] = 1;

	// Loop through the range to compute the cycle length, update max cycle length
	for (x = b; x <= e; x++) {

		curr_cycle_length = 1;
		curr_num = x;

		while (curr_num > 1) {
			//Read cycle length from lazy cache if it exists
			if (curr_num < LAZY_CACHE_SIZE && lazy_cache[curr_num] != 0) {
				curr_cycle_length += lazy_cache[curr_num] - 1;
				break;
			}
			else if ((curr_num & 1) == 0) {
				curr_num >>= 1;
				curr_cycle_length++;
			}
			else {
				curr_num = curr_num + (curr_num >> 1) + 1;
				curr_cycle_length += 2;
			}

		}

		//Update max cycle length for this range
		if (curr_cycle_length > max_cycle_length) {
			max_cycle_length = curr_cycle_length;
		}
		//Update cache entry with cycle length for each number in the range i to j (inclusive)
		if (x < LAZY_CACHE_SIZE) {
			lazy_cache[x] = curr_cycle_length;
		}
	}

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
