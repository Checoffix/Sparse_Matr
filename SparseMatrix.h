#pragma once
#include <set>
#include <string>
#include <iostream>


typedef struct
{
	int x, y, value;

} Cell;


class SparseMatrix
{
	int M, N, ElemCount;
	Cell* Matrix;

	void InsertWithSum(const Cell& right);
public:
	SparseMatrix() : Matrix(), M(), N(), ElemCount() {};
	SparseMatrix(const Cell& right);
	SparseMatrix(const SparseMatrix& right);
	~SparseMatrix();

	SparseMatrix& operator=(const SparseMatrix& right); 
	SparseMatrix& operator=(const Cell& right);          

	void insert(const Cell& right);       

	SparseMatrix operator*(int num) const;             
	SparseMatrix& operator*=(int num);

	SparseMatrix operator*(const SparseMatrix& right) const;
	SparseMatrix& operator*=(const SparseMatrix& right);


	SparseMatrix operator+(const SparseMatrix& right) const;  
	SparseMatrix& operator+=(const SparseMatrix& right); 
	SparseMatrix operator-(const SparseMatrix& right) const;
	SparseMatrix& operator-=(const SparseMatrix& right);

	SparseMatrix& operator-();
	SparseMatrix operator-(int);

	SparseMatrix& operator++();
	SparseMatrix operator++(int);

	SparseMatrix& operator--();
	SparseMatrix operator--(int);

	int operator[](const Cell& WhatFind) const;
	Cell operator[](int WhatFind) const;

	SparseMatrix& Transposing();                         
	void PrintMatrix() const;             
	void PrintMatrix(int index) const;             
	void clear();
	friend SparseMatrix operator*(int num, const SparseMatrix& Matr);  
};

SparseMatrix operator*(int num, const SparseMatrix& Matr);