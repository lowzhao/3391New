#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib> // random
#include <ctime>
#include <climits>	// all useful constants
#include <functional> // for hash
#include <algorithm>
#include <sstream>
#include <iomanip>
// #include <regex>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*** Data Structure ***/
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <deque> // double ended queue
#include <list>  // priority queue
#include <map>
#include <set>
// using namespace std;
#define ull unsigned long long
#define DUBUG true
#define $(x) {if (DUBUG) std::cout << #x << " = " << x << " " << "\n";}
#define _(x) {if (DUBUG) std::cout << #x << " = " << x << " ";}

#define INF 0x3f3f3f3f
#define INF2 0x7fffffff
#define NEGINF 0x80000000

#define input(x) scanf("%d",&x)
#define inputs(x) scanf("%s",x)
#define output(x) printf("%d",x)
#define outputs(x) printf("%s", x)
#define lnBrk() printf("\n")

#define from(i, x, y) for (int i = x; i < y; ++i)
#define fromNeg(i, x, y) for (int i = x; i >= y; --i)

#define eps 1e-6

using namespace std;


void computeLPSArray(char* pat, int M, int* lps);
int maxFound = 0;
int maxFoundLen = 0;
int found = 0;
string maxFoundS;
// Prints occurrences of pat[] in txt[] 
void KMPSearch(char* pat, char* txt)
{
	int M = strlen(pat);
	int N = strlen(txt);

	// create lps[] that will hold the longest prefix suffix 
	// values for pattern 
	int* lps = new int[M];

	// Preprocess the pattern (calculate lps[] array) 
	computeLPSArray(pat, M, lps);

	int i = 0; // index for txt[] 
	int j = 0; // index for pat[] 
	while (i < N) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			//printf("Found pattern at index %d ", i - j);
			found++;
			j = lps[j - 1];
		}

		// mismatch after j matches 
		else if (i < N && pat[j] != txt[i]) {
			// Do not match lps[0..lps[j-1]] characters, 
			// they will match anyway 
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}

// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(char* pat, int M, int* lps)
{
	// length of the previous longest prefix suffix 
	int len = 0;

	lps[0] = 0; // lps[0] is always 0 

				// the loop calculates lps[i] for i = 1 to M-1 
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else // (pat[i] != pat[len]) 
		{
			// This is tricky. Consider the example. 
			// AAACAAAA and i = 7. The idea is similar 
			// to search step. 
			if (len != 0) {
				len = lps[len - 1];

				// Also, note that we do not increment 
				// i here 
			}
			else // if (len == 0) 
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}


int T;

void mainFunction()
{
	input(T);
	string s;
	char s1[1001];
	char s2[1001];
	while (T--) {
		cin >> s1;
		maxFound = 0;
		maxFoundLen = 0;
		bool foundAnything = false;
		for (int i = 0; i < strlen(s1) ; i++) {
			// make s2 copy
			for (int k = i+1; k < strlen(s1)+1 ;k++) {
				if (k - i < maxFoundLen){
					continue;
				}
				found = 0;
				int indexF = 0;
				for (int j = i; j < k; j++) {
					s2[indexF++] = s1[j];
				}
				s2[indexF] = '\0';
				KMPSearch(s2, s1);
				if (found > 1 && maxFoundLen < k-i) {
					foundAnything = true;
					maxFound = found;
					maxFoundLen = k - i;
					maxFoundS = string(s2);
				}
				else if (found > 1 && maxFoundLen == k - i) {
					if (string(s2) < maxFoundS) {
						maxFoundS = string(s2);
					}
				}
			}
		}
		if (foundAnything) {

			cout << maxFoundS << " " << maxFound << '\n';
		}
		else {
			cout << "No repetitions found!\n";
		}
	}
}

int main()
{

	/*if (getenv("vscode") != NULL)
	{
		freopen("in.txt", "r", stdin);
	}*/
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	// testCaseGenerator();
	mainFunction();
	return 0;
}

/*
6
GATTACA
GAGAGAG
GATTACAGATTACA
TGAC
TGTAC
TTGGAACC
*/