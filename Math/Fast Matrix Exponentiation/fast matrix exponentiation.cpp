#include<bits/stdc++.h>
using namespace std;

// Allocates memory to create a square matrix nxn and returns it.
long long** MakeSquareMatrix(int n){
	long long** ans = (long long**)malloc(sizeof(long long*) * n);
	for(int i=0; i<n; i++)
	ans[i] = (long long*)malloc(sizeof(long long) * n);
	return ans;
}

// Frees the memory allocated to a square matrix.
void ClearSquareMatrix(long long** matrix, int n){
	for(int i=0; i<n; i++)
	free(matrix[i]);
	free(matrix);
}

// Multiply two square matrices nxn in O(n^3).
long long** MatrixMultiplication(long long** a, long long** b, int n, long long mod){
	long long** c = MakeSquareMatrix(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			long long sum = 0;
			for(int l=0; l<n; l++)
			sum = (sum + a[i][l] * b[l][j]) % mod;
			c[i][j] = sum;
		}
	}
	return c;
}

// Calculates f(k) in O((n^3) * log(k)) using fast matrix exponentiation.
//
// Where f(k) = c_k-1 * f_k-1 + c_k-2 * f_k-2 + c_k-3 * f_k-3 + ...
//
// Given:
//   c_0, c_1, c_2, ..., c_n-1
//   f_0, f_1, f_2, ..., f_n-1
//
// Initial matrix:
//
//         const  ...  f_k-4  f_k-3  f_k-2  f_k-1
// const     1    ...    0      0      0      0
// ...      ...   ...   ...    ...    ...    ...
// f_k-3     0    ...    0      1      0      0
// f_k-2     0    ...    0      0      1      0
// f_k-1     0    ...    0      0      0      1
// f_k       1    ...  c_k-4  c_k-3  c_k-2  c_k-1
long long SolveRecurrence(vector<long long>& c, vector<long long>& f, long long cst, long long k, long long mod){
	if(k < f.size())
	return f[k];
	k -= f.size() - 1;

	int n = f.size() + 1;

	// Build initial matrix.
	long long** mpw2 = MakeSquareMatrix(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
		mpw2[i][j] = 0;
	}
	mpw2[0][0] = mpw2[n-1][0] = 1;
	for(int i=1; i<n-1; i++)
	mpw2[i][i+1] = 1;
	for(int j=1; j<n; j++)
	mpw2[n-1][j] = c[j-1];

	// Build answer matrix, initially equal to the identity matrix.
	long long** matrix = MakeSquareMatrix(n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
		matrix[i][j] = 0;
		matrix[i][i] = 1;
	}

	// Calculate f(k) using fast matrix exponentiation.
	for(int i=0; k > 0; i++){
		if((k & (1ll<<i)) > 0){
			long long** mult = MatrixMultiplication(matrix, mpw2, n, mod);
			ClearSquareMatrix(matrix, n);
			matrix = mult;
			k ^= (1ll<<i);
		}
		long long** mult = MatrixMultiplication(mpw2, mpw2, n, mod);
		ClearSquareMatrix(mpw2, n);
		mpw2 = mult;
	}
	long long ans = (matrix[n-1][0] * cst) % mod;
	for(int j=1; j<n; j++)
	ans = (ans + matrix[n-1][j] * f[j-1]) % mod;

	ClearSquareMatrix(matrix, n);
	ClearSquareMatrix(mpw2, n);

	return ans;
}