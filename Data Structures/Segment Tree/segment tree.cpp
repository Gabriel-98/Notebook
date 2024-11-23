#include<bits/stdc++.h>
using namespace std;

struct SegmentTreeNode{

	int null, valor;

	SegmentTreeNode(){ null = 1; }

	SegmentTreeNode(const SegmentTreeNode& s){
		null = s.null;
		valor = s.valor;
	}

	SegmentTreeNode(int valor){
		null = 0;
		this->valor = valor;
	}

};

struct SegmentTree{
	int n;
	vector<SegmentTreeNode> vect;
	vector<SegmentTreeNode> T;

	SegmentTreeNode funcion(SegmentTreeNode a, SegmentTreeNode b){
		if(a.null == 1 && b.null == 1)
		return SegmentTreeNode();
		if(a.null == 1)
		return b;
		if(b.null == 1)
		return a;
		return SegmentTreeNode(min(a.valor, b.valor));
	}

	void build(vector<SegmentTreeNode> V){
		vect.clear();
		vect.resize(V.size());
		for(int i=0; i<vect.size(); i++){
			vect[i] = V[i];
		}
		n = 4 * V.size();
		T.clear();
		T.resize(n, SegmentTreeNode());
		build2(1,0,vect.size()-1);
	}

	void build2(int pos, int i, int j){
		if(i==j)
		T[pos] = SegmentTreeNode(vect[i]);
		else{
			build2(2*pos, i, (i+j)/2);
			build2(2*pos+1, (i+j+2)/2, j);
			T[pos] = funcion(T[2*pos], T[2*pos+1]);
		}
	}

	void update(int id, SegmentTreeNode valor){
		vect[id] = valor;
		update2(1,0,vect.size()-1,id,valor);
	}

	void update2(int pos, int i, int j, int id, SegmentTreeNode valor){
		if(i==j){
			if(id==i)
			T[pos] = valor;
		}
		else{
			if(i<=id && id<=j){
				update2(2*pos, i,(i+j)/2, id, valor);
				update2(2*pos+1, (i+j+2)/2,j, id, valor);
				T[pos] = funcion(T[2*pos],T[2*pos+1]);
			}
		}
	}

	SegmentTreeNode query(int i, int j){
		return query2(1, 0,vect.size()-1, i,j);
	}

	SegmentTreeNode query2(int pos, int x, int y, int i, int j){
		if(j<x || i>y)
		return SegmentTreeNode();
		else if(i<=x && y<=j)
		return T[pos];
		else
		return funcion(query2(2*pos, x,(x+y)/2, i,j), query2(2*pos+1, (x+y+2)/2,y, i,j));
	}
};