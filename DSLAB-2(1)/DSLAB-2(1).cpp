#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define GET_ARRAY_LENGHT _countof

int UniversalPluralSize;
int* UniversalPlural;

int A[] = { 3, 5 };
const int SizeA = GET_ARRAY_LENGHT(A);
int B[] = { 3, 6, 7 };
const int SizeB = GET_ARRAY_LENGHT(B);


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

// A x B
// {0, 3, 5} x {3, 7} = { (0, 3), {0, 7}, (3, 3), (3, 7), (5, 3), (5, 7) }
int*** MxM(const int* a, const int size_a, const int* b, const int size_b, int size[], bool isPrinted = false, const char* addString = nullptr)
{
	if (size != nullptr)
	{
		size[0] = size_a;
		size[1] = size_b;
		size[2] = 2;
	}

	int*** res = new int** [size_a];
	for (int i = 0; i < size_a; i++)
	{
		res[i] = new int* [size_b];
		for (int j = 0; j < size_b; j++)
		{
			int* consist = new int[2]{ a[i], b[j] };
			res[i][j] = consist;
		}
	}

	if (isPrinted) {
		if (addString != nullptr)
		{
			cout << "[" << addString << "] ";
		}

		cout << "{";
		for (int i = 0; i < size_a; i++)
		{
			for (int j = 0; j < size_b; j++)
			{
				cout << "(" << res[i][j][0] << ", " << res[i][j][1] << ") ";
			}
			if (i == size_a - 1)
			{
				cout << "}" << endl;
			}
		}
	}

	return res;
}

// A^2
// {0, 3, 5}^2 = {(0, 0), (0, 3), (0, 5), ()}
int*** Pow2(const int* a, const int size_a, int size[], bool isPrinted = false, const char* addString = nullptr)
{
	if (size != nullptr)
	{
		size[0] = size_a;
		size[1] = 2;
	}

	int*** res = new int** [size_a];
	for (int i = 0; i < size_a; i++)
	{
		res[i] = new int* [size_a];
		for (int j = 0; j < size_a; j++)
		{
			int* consist = new int[2]{ a[i], a[j] };
			res[i][j] = consist;
		}
	}

	if (isPrinted) {
		if (addString != nullptr)
		{
			cout << "[" << addString << "] ";
		}

		cout << "{";
		for (int i = 0; i < size_a; i++)
		{
			for (int j = 0; j < size_a; j++)
			{
				cout << "(" << res[i][j][0] << ", " << res[i][j][1] << ") ";
			}
			if (i == size_a - 1)
			{
				cout << "}" << endl;
			}
		}
	}

	return res;
}

// AxB, A^2
int main()
{
	// U[25]
	SetUniversalPlural(1, 25);

	PrintPluar(A, SizeA, "A");
	PrintPluar(B, SizeB, "B");
	cout << endl;

	int* size = nullptr;
	int*** pluar = MxM(A, SizeA, B, SizeB, size, true, "AxB");
	pluar = Pow2(A, SizeA, size, true, "A^2");

	return 0;
}
