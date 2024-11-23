#include<bits/stdc++.h>
using namespace std;

struct FenwickTreeNode {
	long long value;
	FenwickTreeNode() : value(0) {}
	FenwickTreeNode(long long _value) : value(_value) {}
	void SetNeutral(){ value = 0; } // Modify according to the operation (e.g. 0 for sum, 1 for multiplication, ...)
};

struct FenwickTree{
	int size;
	vector<FenwickTreeNode> nodes, blocks;

	FenwickTreeNode combine(FenwickTreeNode a, FenwickTreeNode b);
	FenwickTreeNode decombine(FenwickTreeNode a, FenwickTreeNode b);
	FenwickTreeNode calculatePrefix(int pos);
	void Build(int size);
	void Update(int pos, FenwickTreeNode newValue);
	FenwickTreeNode Query(int l, int r);
};

FenwickTreeNode FenwickTree::combine(FenwickTreeNode a, FenwickTreeNode b){
	// Modify the combination logic here.
	return FenwickTreeNode(a.value + b.value);
}

FenwickTreeNode FenwickTree::decombine(FenwickTreeNode a, FenwickTreeNode b){
	// Modify the decombination logic here.
	return FenwickTreeNode(a.value - b.value);
}

FenwickTreeNode FenwickTree::calculatePrefix(int pos){
	FenwickTreeNode prefix = FenwickTreeNode();
	prefix.SetNeutral();
	while(pos > 0){
		prefix = combine(prefix, blocks[pos]);
		pos -= pos & -pos;
	}
	return prefix;
}

void FenwickTree::Build(int size) {
	this->size = size;
	nodes.clear(); blocks.clear();
	nodes.resize(size+1);
	blocks.resize(size+1);
	for(int i=0; i<=size; i++){
		nodes[i].SetNeutral();
		blocks[i].SetNeutral();
	}
}

void FenwickTree::Update(int pos, FenwickTreeNode newValue){
	FenwickTreeNode oldValue = nodes[pos];
	nodes[pos] = newValue;
	while(pos <= size){
		blocks[pos] = decombine(blocks[pos], oldValue);
		blocks[pos] = combine(blocks[pos], newValue);
		pos += pos & -pos;
	}
}

// 1 <= l <= r <= size
FenwickTreeNode FenwickTree::Query(int l, int r){
	return decombine(calculatePrefix(r), calculatePrefix(l-1));
}