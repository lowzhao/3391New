/*** System Library ***/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <math.h>
#include <complex>
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

#define eps 1e-6
using namespace std;

int T;



struct Path{
	int p1;
	int p2;
	int length;
	Path(){}
	Path(int p1,int p2, int length):p1(p1),p2(p2),length(length){}
	// bool operator< (const Path& b){
	// 	return length > b.length;
	// }
};

struct Point{
	int x;
	int y;
};
double squaredDistance(Point a, Point b){
	return (a.x-b.x) *(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
bool sorter(Path a, Path b){
	// _(a.p1);
	// _(a.p2);
	// _(b.p1);
	// $(b.p2);
	return a.length < b.length;
}

int getRoot(int unionSet[],int node){
	if (unionSet[node] == -1){
		return node;
	}else{
		return getRoot(unionSet,unionSet[node]);
	}
}

int findMinDistanceTo(vector<Path> mst[],int start,int end){

	_(start);
	_(end);
	int minL = INF;
	from(i,0,mst[start].size()){
		int otherIndex = mst[start][i].p1==start?mst[start][i].p2:mst[start][i].p1;
		if (otherIndex == end){
			return mst[start][i].length;
		}else{
			minL = min(mst[start][i].length,findMinDistanceTo(mst,otherIndex,end));
		}
	}
	return minL;

}


void mainFunction()
{
	// int s[200][200];
	vector<Point > nodes;
	vector<Path> allPaths;
	int n;
	vector<Path> mst[201];
	vector <int> soRandom ;
	int unionSet[201];
	int x,y;
	T =1;
	while(1){
		input(n);
		if (n==0){
			break;
		}

		// memset(s,-1,sizeof s);

		nodes.clear();
		allPaths.clear();


		// complex <int > node;
		Point node;

		// memset(mst,complex<int>(-1,0),sizeof mst);
		memset(unionSet,-1,sizeof unionSet);
		from(i,0,n){
			
			input(x);
			input(y);
			node.x = x;
			node.y = y;
			mst[i].clear();
			soRandom.push_back(n-i);
			nodes.push_back(node);
			from(j,0,i){
				allPaths.push_back(Path(j,i,squaredDistance(nodes[j],nodes[i])));
			}
		}
		from(i,0,allPaths.size()){
			_(allPaths[i].p1);
			_(allPaths[i].p2);
			$(allPaths[i].length);
		}
		// _(allPaths.max_size());
		sort(allPaths.begin(),allPaths.end(),sorter);
		// sort(soRandom.begin(),soRandom.end(),sorter);
		from(i,0,allPaths.size()){
			Path p = allPaths[i];
			if (unionSet[p.p2] == -1){
				unionSet[p.p2] = p.p1;
				mst[p.p1].push_back(p);
				mst[p.p2].push_back(p);
			}else if (unionSet[p.p1] == -1){ // and p2 is not -1
				unionSet[p.p1] = p.p2;
				mst[p.p1].push_back(p);
				mst[p.p2].push_back(p);
			}else if (getRoot(unionSet,unionSet[p.p1]) != getRoot(unionSet,unionSet[p.p2])) { // both not -1
				unionSet[p.p2] = p.p1;
				mst[p.p1].push_back(p);
				mst[p.p2].push_back(p);
			}
		}

		;


		printf("Scenario #%d\nFrog Distance = %.3f\n\n",T++,sqrt(findMinDistanceTo(mst,1,0)));


	}
}

int main()
{

	if (getenv("vscode") != NULL)
	{
		freopen("in.txt", "r", stdin);
	}
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	// testCaseGenerator();
	mainFunction();
	return 0;
}

