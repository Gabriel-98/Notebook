#include <bits/stdc++.h>
using namespace std;

vector<int> prefixFunctionKMP(string cadena){
	vector<int> prefixFunction(cadena.size());
	prefixFunction[0] = 0;
	for(int i=1,j=0; i<cadena.size(); i++){
		while(j > 0 && cadena[i] != cadena[j]){
			j = prefixFunction[j-1];
		}
		if(cadena[i] == cadena[j])
		j++;
		prefixFunction[i] = j;
	}
	return prefixFunction;
}