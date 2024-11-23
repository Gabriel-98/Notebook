#include<bits/stdc++.h>
using namespace std;

struct SuffixArray {
	int alpsize, size, levels;
	vector<int> text, sortedIds, lcp;

	vector<int> sortStringsFromLevel0();
	vector<int> sortStringsFromLevelK(int k, const vector<int>& rank);
	void Build(vector<int> text, int alpsize);
	void BuildLcpTable();
};

// Sort the suffixes for its first character.
// Sorting algorithm: Counting sort O(n).
vector<int> SuffixArray::sortStringsFromLevel0(){
	// Sort ids by first character.
	vector<int> v[alpsize];
	for(int i=0; i<size; i++)
	v[text[i]].push_back(i);
	for(int i=0,pos=0; i<alpsize; i++){
		for(int j=0; j<v[i].size(); j++)
		sortedIds[pos++] = v[i][j];
	}
	
	// Calculates the rank for each id.
	vector<int> rank2(size);
	rank2[sortedIds[0]] = 1;
	for(int i=1; i<size; i++){
		int id = sortedIds[i], previd = sortedIds[i-1];
		if(text[id] == text[previd]) rank2[id] = rank2[previd];
		else rank2[id] = rank2[previd] + 1;
	}
	return rank2;
}

// Sort the suffixes by its first 2^k characters.
// The sorting is on the pair<id_rank, next_id_rank> of previous level
// and run in O(n), taking advantage that suffixes are already sorted by
// id_rank (and therefore also by next_id_rank).
//
// Sorting algorithm:
//   Iterates through the suffixes in ascending order of next_id_rank and places
//   them in the next available position for the block with the same id_rank.
//   Complexity: O(n)
vector<int> SuffixArray::sortStringsFromLevelK(int k, const vector<int>& rank){
	// Sort ids by first 2^k characters.
	int pw2 = 1<<(k-1);
	vector<int> last(size+1, 0), auxSortedIds(sortedIds);
	for(int i=0; i<size; i++)
	last[rank[sortedIds[i]]]++;
	for(int i=1; i<last.size(); i++)
	last[i] += last[i-1];

	for(int i=-pw2; i<size; i++){
		int nextId = (i < 0) ? size + pw2 + i : auxSortedIds[i];
		int id = nextId - pw2;
		if(id >= 0)
		sortedIds[last[rank[id]-1]++] = id;
	}

	// Calculates the rank for each id.
	vector<int> rank2(size);
	rank2[sortedIds[0]] = 1;
	for(int i=1; i<size; i++){
		int id = sortedIds[i], previd = sortedIds[i-1];
		int c11, c12, c21, c22;
		c11 = rank[previd];
		c21 = rank[id];
		c12 = (previd+pw2 >= size) ? 0 : rank[previd+pw2];
		c22 = (id+pw2 >= size) ? 0 : rank[id+pw2];

		rank2[id] = rank2[previd];
		if(c21 > c11 || c22 > c12)
		rank2[id]++;
	}
	return rank2;
}

// Builds the suffix array using standard algorithm in O(n * log n).
void SuffixArray::Build(vector<int> text, int alpsize){
	this->text = text;
	this->alpsize = alpsize;
	size = text.size();
	levels = log2(size-1) + 2;

	sortedIds.resize(size);

	vector<int> rank = sortStringsFromLevel0();
	for(int k=1; k<levels; k++)
	rank = sortStringsFromLevelK(k, rank);
}

// Builds the Longest Common Prefix table in O(n).
void SuffixArray::BuildLcpTable(){
	vector<int> position(size);
	for(int i=0; i<size; i++)
	position[sortedIds[i]] = i;
	
	lcp.resize(size);
	for(int id=0; id<size; id++){
		lcp[position[id]] = 0;
		if(position[id] != 0){
			int previd = sortedIds[position[id]-1];
			int counter = (id == 0) ? 0 : max(0, lcp[position[id-1]] - 1);
			while(max(id,previd)+counter < size && text[id+counter] == text[previd+counter])
			counter++;
			lcp[position[id]] = counter;
		}
	}
}
