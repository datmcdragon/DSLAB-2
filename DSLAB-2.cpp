#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define GET_ARRAY_LENGHT _countof
int UniversalPluralSize;
int* UniversalPlural;

int A[] = { 1, 2, 3, 4, 5 ,6, 7, 11, 12, 13, 17, 18 };
int B[] = { 1, 2, 3, 4, 5, 13, 14, 16, 20, 24 };
int C[] = { 1, 9, 10, 11, 12, 13, 17, 18, 22 };

const int SizeA = GET_ARRAY_LENGHT(A);
const int SizeB = GET_ARRAY_LENGHT(B);
const int SizeC = GET_ARRAY_LENGHT(C);

// from = -100, to = 200 = {-100, -99, -98 ... 198, 199, 200 }
void SetUniversalPlural(const int from, const int to)
{
	UniversalPluralSize = to - from + 1;
	UniversalPlural = new int[UniversalPluralSize];
	for (int i = 0; i < UniversalPluralSize; i++)
	{
		UniversalPlural[i] = from + i;
	}
}
// Print array
void PrintPluar(const int* p, const int size, const char* addString = nullptr)
{
	if (addString != nullptr)
	{
		cout << "[" << addString << "] ";
	}
	cout << "{";
	for (int i = 0; i < size; i++)
	{
		cout << p[i];
		if (i != size - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
}
// A \ B
int* hiatus(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
{
	int index = 0;
	int* tmp = new int[size_a];
	for (int i = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				tmp[index] = i;
				index++;
			}
		}
	}
	size = size_a - index;
	int* res = new int[size];

	for (int i = 0, i1 = 0; i < size_a; i++)
	{
		if (i == tmp[i1])
		{
			i1++;
		}
		else
		{
			res[i - i1] = a[i];
		}
	}

	delete[] tmp;
	tmp = nullptr;
	if (isSort)
		sort(res, res + size);
	return res;
}
// A + B
int* augment(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
{
	size = size_a + size_b;
	int* res = new int[size];
	int total = 0;

	for (int i = 0; i < size_a; i++, total++)
	{
		res[i] = a[i];
	}
	for (int i = 0; i < size_b && total < size; i++, total++)
	{
		res[total] = b[i];
	}

	if (isSort)
		sort(res, res + size);
	return res;
}
// A u B
int* bAnd(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
{
	int* tmp = new int[size_b];
	int indexTmpArray = 0;

	for (int i = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				tmp[indexTmpArray] = a[i];
				indexTmpArray++;
			}
		}
	}
	int* tmp1 = new int[indexTmpArray];
	for (int i = 0; i < indexTmpArray; i++)
	{
		tmp1[i] = tmp[i];
		//cout << tmp[i] << " ";
	}

	delete[] tmp;
	tmp = nullptr;
	int s;
	int* tmp2 = hiatus(b, size_b, tmp1, indexTmpArray, s);

	delete[] tmp1;

	int* res = augment(tmp2, s, a, size_a, size);

	if (isSort)
		sort(res, res + size);
	return res;
}
// !A
int* Not(const int* a, const int size_a, int& size, bool isSort = true)
{
	return hiatus(UniversalPlural, UniversalPluralSize, a, size_a, size);
}

// A ^ B
int* Sdelete(const int* a, const int size_a, const int* b, const int size_b, int& size, bool isSort = true)
{
	int s = 0;
	for (int i = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				s++;
			}
		}
	}
	size = s;
	int* res = new int[size];
	for (int i = 0, s = 0; i < size_a; i++)
	{
		for (int j = 0; j < size_b; j++)
		{
			if (a[i] == b[j])
			{
				res[s] = a[i];
				s++;
			}
		}
	}
	if (isSort)
		sort(res, res + size);
	return res;
}

int main()
{
	// U[25]
	SetUniversalPlural(1, 25);

	PrintPluar(UniversalPlural, UniversalPluralSize, "U");
	PrintPluar(A, SizeA, "A");
	PrintPluar(B, SizeB, "B");
	PrintPluar(C, SizeC, "C");
	cout << endl;

	// !B
	int size_p1;
	int* p1 = Not(B, SizeB, size_p1);
	PrintPluar(p1, size_p1, "!B");

	//A ^ !B
	int size_p2;
	int* p2 = Sdelete(A, SizeA, p1, size_p1, size_p2);
	PrintPluar(p2, size_p2, "A ^ !B");

	// !(A ^ !B)
	int size_p3;
	int* p3 = Not(p2, size_p2, size_p3);
	PrintPluar(p3, size_p3, "!(A ^ !B)");

	// !(A ^ !B) \ A
	int size_p4;
	int* p4 = hiatus(p3, size_p3, A, SizeA, size_p4);
	PrintPluar(p4, size_p4, "(!(A ^ !B) \\ A");

	// (!(A ^ !B) \ A) u B
	int size_p5;
	int* p5 = bAnd(p4, size_p4, B, SizeB, size_p5);
	PrintPluar(p5, size_p5, "(!(A ^ !B) \\ A) u B");

	// (!(A ^ !B) \ A u B) u C
	int size_p6;
	int* p6 = bAnd(p5, size_p5, C, SizeC, size_p6);
	PrintPluar(p6, size_p6, "(!(A ^ !B) \\ A u B) u C");

	return 0;
}
