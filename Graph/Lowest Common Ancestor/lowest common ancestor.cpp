#include<bits/stdc++.h>
using namespace std;

const int maxN = 200000;
const int maxSTN = 2 * maxN - 1;
const int maxLogSTN = __lg(maxSTN);
vector<int> tree[maxN];
vector<int> P(maxN), depth(maxN), firstoccur(maxN);
vector<int> seq;
int stmindepth[maxSTN][maxLogSTN+1];

void DfsForLcaVisit(vector<int>& S, int p, int x){
	S[x] = 1;
	P[x] = p;
	depth[x] = (p == -1) ? 0 : depth[p] + 1;
	firstoccur[x] = seq.size();
	seq.push_back(x);
	for(int i=0; i<tree[x].size(); i++){
		int y = tree[x][i];
		if(S[y] == 0){
			DfsForLcaVisit(S, x, y);
			seq.push_back(x);
		}
	}
}

void DfsForLca(int n, int root){
	vector<int> S(n, 0);
	DfsForLcaVisit(S, -1, root);
}

void BuildLcaSolver(int n, int root){
	DfsForLca(n, root);
	int lg2 = __lg(seq.size());
	for(int i=0; i<seq.size(); i++)
	stmindepth[i][0] = seq[i];
	for(int j=1,pw2=1; j<=lg2; j++,pw2<<=1){
		for(int i=0; i<seq.size(); i++){
			stmindepth[i][j] = stmindepth[i][j-1];
			if(i+pw2 < seq.size()){
				if(depth[stmindepth[i+pw2][j-1]] < depth[stmindepth[i][j-1]])
				stmindepth[i][j] = stmindepth[i+pw2][j-1];
			}
		}
	}
}

// Find LCA in O(1).
int LCA(int x, int y){
	int l, r, lg2, pw2, op1, op2;
	l = min(firstoccur[x], firstoccur[y]);
	r = max(firstoccur[x], firstoccur[y]);
	lg2 = __lg(r+1-l); pw2 = 1<<lg2;
	op1 = stmindepth[l][lg2];
	op2 = stmindepth[r+1-pw2][lg2];
	return (depth[op1] < depth[op2]) ? op1 : op2;
}