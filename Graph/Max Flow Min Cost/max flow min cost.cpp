#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
typedef pair<int,int> pii;

const int maxNodes = 500;
int residual[maxNodes][maxNodes];
int cost[maxNodes][maxNodes];

// Return the minimum cost between the all augmenting paths.
// use Bellman Ford algorithm.
pii FindAugmentingPath(int n, int s, int t, bool unit){
	queue<int> Q;
	vector<int> P(n,-1), dist(n,inf), flow(n,0);
	Q.push(s);
	dist[s] = 0;
	flow[s] = inf;
	while(!Q.empty()){
		int x = Q.front(); Q.pop();
		for(int y=0; y<n; y++){
			if(residual[x][y] > 0 && dist[x] + cost[x][y] < dist[y]){
				Q.push(y);
				P[y] = x;
				dist[y] = dist[x] + cost[x][y];
				flow[y] = min(flow[x], residual[x][y]);				
			}
		}
	}

	if(dist[t] != inf){
		int f = unit ? 1 : flow[t];
		int x = t;
		while(x != s){
			int p = P[x];
			residual[p][x] -= f;
			residual[x][p] += f;
			x = p;
		}
		return pii(f, dist[t]);
	}
	return pii(0,0);
}

pii MaxFlowMinCost(int n, int s, int t){
	int flow = 0, cost = 0;
	while(true){
		pii p = FindAugmentingPath(n,s,t,false);
		flow += p.first;
		cost += p.first * p.second;
		if(p.first == 0)
		break;
	}
	return pii(flow, cost);
}