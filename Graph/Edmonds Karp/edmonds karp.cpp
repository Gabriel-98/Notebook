#include<bits/stdc++.h>
using namespace std;
#define inf 1e9

const int maxNodes = 500;
int residual[maxNodes][maxNodes];

int FindAugmentingPath(int n, int s, int t, bool unit){
	queue<int> Q;
	vector<int> S(n,0), P(n,-1), flow(n, 0);
	Q.push(s);
	S[s] = 1;
	flow[s] = inf;
	while(!Q.empty()){
		int x = Q.front(); Q.pop();
		for(int y=0; y<n; y++){
			if(residual[x][y] > 0 && S[y] == 0){
				Q.push(y);
				S[y] = 1;
				P[y] = x;
				flow[y] = min(flow[x], residual[x][y]);
			}
		}
	}
	if(flow[t] > 0){
		int f = unit ? 1 : flow[t];
		int x = t;
		while(x != s){
			int p = P[x];
			residual[p][x] -= f;
			residual[x][p] += f;
			x = p;
		}
		return f;
	}
	return 0;
}

int MaxFlow(int n, int s, int t){
	int flow = 0;
	for(int f; f = FindAugmentingPath(n,s,t,false); )
	flow += f;
	return flow;
}