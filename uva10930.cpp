/*** System Library ***/
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
#define output(x) printf("%d",x)
#define outputs(x) printf("%s", x)
#define lnBrk() printf("\n")

#define from(i, x, y) for (int i = x; i < y; ++i)
#define fromNeg(i, x, y) for (int i = x; i >= y; --i)
#define foreach(i,n) for (int i = 0 ;  i< n ; ++i)

#define eps 1e-6

using namespace std;

double cross(double cx, double cy, double x1, double y1,double x2, double y2){
	return (x1-cx)*(y2-cy) - (y1-cy)*(x2-cx);
}

int T;

void mainFunction()
{
	int array[31] ;
	bool all[1001];
	int t = 1;
	while(cin >> T)
	{
		bool possible = true;

		memset(all,false,sizeof all);
		cin >> array[0];
		from(i,1,T){
			cin >> array[i];

			if (array[i] < array[i-1] ){
				possible = false;
			}
		}
		if (possible){
			from (i,0,T){
				if (all[array[i]]){
					possible = false;
					break;
				}else{
					all[array[i]] = true;
					from(j,0,array[i]){
						if (all[j] == true && array[i] + j <= 1000 ){
							all[array[i] + j] = true;
						}
					}
				}
			}
		}

		cout << "Case #" << t << ":";
		from (i,0,T){
			cout <<" " << array[i] ;
		}
		if (possible){
			cout << "\nThis is an A-sequence.\n";
		}else{
			cout << "\nThis is not an A-sequence.\n";
		}
		t++;
	}
}

int main()
{

	if (getenv("vscode") != NULL)
	{
		freopen("in.txt", "r", stdin);
		freopen("out.txt","w",stdout);
	}
	// std::ios_base::sync_with_stdio(false);
	// std::cin.tie(NULL);
	// testCaseGenerator();
	mainFunction();
	return 0;
}

