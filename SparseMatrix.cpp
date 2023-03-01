#include "SparseMatrix.h"


void SparseMatrix::InsertWithSum(const Cell& right)
{
	for (int f = 0; f < ElemCount; f++)
	{
		if ((Matrix + f)->x == right.x && (Matrix + f)->y == right.y)
		{
			(Matrix + f)->value += right.value;
			return;
		}
	}
	(*this).insert(right);
}

SparseMatrix::SparseMatrix(const Cell& right)
{
	if (right.x < 0 || right.y < 0)
	{
		throw ferror;
	}
	M = right.x;
	N = right.y;
	ElemCount = 1;
	Matrix = new Cell[ElemCount];
	Matrix->x = right.x;
	Matrix->y = right.y;
	Matrix->value = right.value;
}

SparseMatrix::SparseMatrix(const SparseMatrix& right)
{
	M = right.M;
	N = right.N;
	ElemCount = right.ElemCount;
	Matrix = new Cell[right.ElemCount];
	for (int f = 0; f < ElemCount; f++)
	{
		(Matrix + f)->x = (right.Matrix + f)->x;
		(Matrix + f)->y = (right.Matrix + f)->y;
		(Matrix + f)->value = (right.Matrix + f)->value;
	}
}

SparseMatrix::~SparseMatrix()
{
	if (Matrix != nullptr)
	{
		delete[] Matrix;
	}
}


SparseMatrix& SparseMatrix::operator++()
{
	for (int i = 0; i < ElemCount; i++)
	{
		(Matrix + i)->value = (Matrix + i)->value + 1;
	}
	return *this;
}

SparseMatrix& SparseMatrix::operator--()
{
	for (int i = 0; i < ElemCount; i++)
	{
		(Matrix + i)->value = (Matrix + i)->value - 1;
	}
	return *this;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& right)
{
	M = right.M;
	N = right.N;
	ElemCount = right.ElemCount;
	if (Matrix != nullptr)
	{
		delete[] Matrix;
	}
	Matrix = new Cell[ElemCount];
	for (int f = 0; f < right.ElemCount; f++)
	{
		(Matrix + f)->x = (right.Matrix + f)->x;
		(Matrix + f)->y = (right.Matrix + f)->y;
		(Matrix + f)->value = (right.Matrix + f)->value;
	}
	return *this;
}

SparseMatrix SparseMatrix::operator++(int)
{
	SparseMatrix temp = *this;
	++(*this);
	return temp;
}

SparseMatrix& SparseMatrix::operator=(const Cell& right)
{
	M = right.x;
	N = right.y;
	ElemCount = 1;
	Matrix = new Cell[1];
	Matrix->x = right.x;
	Matrix->y = right.y;
	Matrix->value = right.value;
	return *this;
}

void SparseMatrix::insert(const Cell& right)
{
	for (int f = 0; f < ElemCount; f++)
	{
		if ((Matrix + f)->x == right.x && (Matrix + f)->y == right.y)
		{
			(Matrix + f)->value = right.value;
			return;
		}
	}
	Cell* TempMatrix = new Cell[ElemCount + 1];
	for (int f = 0; f < ElemCount; f++)
	{
		(TempMatrix + f)->x = (Matrix + f)->x;
		(TempMatrix + f)->y = (Matrix + f)->y;
		(TempMatrix + f)->value = (Matrix + f)->value;
	}
	if (Matrix != nullptr)
	{
		delete[] Matrix;
	}
	Matrix = new Cell[ElemCount + 1];
	Matrix = TempMatrix;
	(Matrix + ElemCount)->x = right.x;
	(Matrix + ElemCount)->y = right.y;
	(Matrix + ElemCount)->value = right.value;
	if (M < right.x)
	{
		M = right.x;
	}
	if (N < right.y)
	{
		N = right.y;
	}
	ElemCount++;
}

SparseMatrix SparseMatrix::operator*(int num) const
{
	SparseMatrix temp = *this;
	for (int i = 0; i < ElemCount; i++)
	{
		(temp.Matrix + i)->value = (temp.Matrix + i)->value * num;
	}
	return temp;
}

SparseMatrix& SparseMatrix::operator*=(int num)
{
	for (int i = 0; i < ElemCount; i++)
	{
		(Matrix + i)->value = (Matrix + i)->value * num;
	}
	return *this;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix& right) const
{
	if (M == right.N)
	{
		SparseMatrix temp = {};
		int res = 0;
		Cell TempCell;
		for (int f = 0; f < ElemCount; f++)
		{
			for (int g = 0; g < right.ElemCount; g++)
			{
				if ((Matrix + f)->x == (right.Matrix + g)->y)
				{
					res = (Matrix + f)->value * (right.Matrix + g)->value;
					TempCell = { (right.Matrix + g)->x, (Matrix + f)->y, res };
					temp.InsertWithSum(TempCell);
				}
			}
		}
		return temp;
	}
	else
	{
		return *this;
	}
}

SparseMatrix& SparseMatrix::operator*=(const SparseMatrix& right)
{
	if (M == right.N)
	{
		SparseMatrix temp = *this;
		(*this).clear();
		M = right.M;
		N = right.N;
		int res = 0;
		Cell TempCell;
		for (int f = 0; f < temp.ElemCount; f++)
		{
			for (int g = 0; g < right.ElemCount; g++)
			{
				if ((temp.Matrix + f)->x == (right.Matrix + g)->y)
				{
					res = (temp.Matrix + f)->value * (right.Matrix + g)->value;
					TempCell = { (right.Matrix + g)->x, (temp.Matrix + f)->y, res };
					(*this).InsertWithSum(TempCell);
				}
			}
		}
		return *this;
	}
	else
	{
		return *this;
	}
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& right) const
{
	SparseMatrix temp = *this;
	if (N == right.N && M == right.M)
	{
		bool inserted;
		for (int f = 0; f < right.ElemCount; f++)
		{
			inserted = false;
			for (int g = 0; g < ElemCount; g++)
			{
				if ((Matrix + g)->x == (right.Matrix + f)->x && (Matrix + g)->y == (right.Matrix + f)->y)
				{
					(temp.Matrix + g)->value += (right.Matrix + f)->value;
					inserted = true;
					break;
				}
			}
			if (!inserted)
			{
				temp.insert(*(right.Matrix + f));
			}
		}
		return temp;
	}
	else
	{
		std::cout << "Unable to sum" << '\n';
		return temp;
	}
}

SparseMatrix& SparseMatrix::operator+=(const SparseMatrix& right)
{
	if (N == right.N && M == right.M)
	{
		bool inserted;
		for (int f = 0; f < right.ElemCount; f++)
		{
			inserted = false;
			for (int g = 0; g < ElemCount; g++)
			{
				if ((Matrix + g)->x == (right.Matrix + f)->x && (Matrix + g)->y == (right.Matrix + f)->y)
				{
					(Matrix + g)->value += (right.Matrix + f)->value;
					inserted = true;
					break;
				}
			}
			if (!inserted)
			{
				(*this).insert(*(right.Matrix + f));
			}
		}
		return *this;
	}
	else
	{
		std::cout << "Unable to sum" << '\n';
		return *this;
	}
}

SparseMatrix SparseMatrix::operator-(const SparseMatrix& right) const
{
	SparseMatrix temp = *this;
	if (N == right.N && M == right.M)
	{
		bool inserted;
		for (int f = 0; f < right.ElemCount; f++)
		{
			inserted = false;
			for (int g = 0; g < ElemCount; g++)
			{
				if ((Matrix + g)->x == (right.Matrix + f)->x && (Matrix + g)->y == (right.Matrix + f)->y)
				{
					(temp.Matrix + g)->value -= (right.Matrix + f)->value;
					inserted = true;
					break;
				}
			}
			if (!inserted)
			{
				temp.insert(*(right.Matrix + f));
			}
		}
		return temp;
	}
	else
	{
		std::cout << "Unable to -" << '\n';
		return temp;
	}
}

SparseMatrix& SparseMatrix::operator-=(const SparseMatrix& right)
{
	if (N == right.N && M == right.M)
	{
		bool inserted;
		for (int f = 0; f < right.ElemCount; f++)
		{
			inserted = false;
			for (int g = 0; g < ElemCount; g++)
			{
				if ((Matrix + g)->x == (right.Matrix + f)->x && (Matrix + g)->y == (right.Matrix + f)->y)
				{
					(Matrix + g)->value -= (right.Matrix + f)->value;
					inserted = true;
					break;
				}
			}
			if (!inserted)
			{
				(*this).insert(*(right.Matrix + f));
			}
		}
		return *this;
	}
	else
	{
		std::cout << "Unable to -" << '\n';
		return *this;
	}
}

SparseMatrix& SparseMatrix::operator-()
{
	for (int i = 0; i < ElemCount; i++)
	{
		(Matrix + i)->value = -(Matrix + i)->value;
	}
	return *this;
}

SparseMatrix SparseMatrix::operator-(int)
{
	SparseMatrix temp = *this;
	-(*this);
	return temp;
}

SparseMatrix SparseMatrix::operator--(int)
{
	SparseMatrix temp = *this;
	--(*this);
	return temp;
}

void SparseMatrix::PrintMatrix() const
{
	for (int f = 0; f < ElemCount; f++)
	{
		std::cout << (Matrix + f)->x << ' ';
		std::cout << (Matrix + f)->y << ' ';
		std::cout << (Matrix + f)->value << '\n';
	}
}

void SparseMatrix::PrintMatrix(int index) const
{
	std::cout << (Matrix + index)->x << ' ';
	std::cout << (Matrix + index)->y << ' ';
	std::cout << (Matrix + index)->value << '\n';
}

void SparseMatrix::clear()
{
	N = 0;
	M = 0;
	ElemCount = 0;
	if (Matrix != nullptr)
	{
		delete[] Matrix;
	}
	Matrix = {};
}

int SparseMatrix::operator[](const Cell& WhatFind) const
{
	for (int f = 0; f < ElemCount; f++)
	{
		if ((Matrix + f)->x == WhatFind.x && (Matrix + f)->y == WhatFind.y && (Matrix + f)->value == WhatFind.value)
		{
			return f;
		}
	}
	throw std::out_of_range("Matrix");
}

Cell SparseMatrix::operator[](int WhatFind) const
{
	if (WhatFind >= ElemCount)
	{
		return Cell{};
	}
	return *(Matrix + WhatFind);
}

SparseMatrix& SparseMatrix::Transposing()
{
	for (int f = 0; f < ElemCount; f++)
	{
		int Temp = (Matrix + f)->x;
		(Matrix + f)->x = (Matrix + f)->y;
		(Matrix + f)->y = Temp;
	}
	return *this;
}

SparseMatrix operator*(int num, const SparseMatrix& Matr)
{
	for (int i = 0; i < Matr.ElemCount; i++)
	{
		(Matr.Matrix + i)->value = (Matr.Matrix + i)->value * num;
	}
	return Matr;
}