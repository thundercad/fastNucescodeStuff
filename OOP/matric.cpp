#include<iostream>
using namespace std;
class Matrix {
	int** matrix;
	int numRows;
	int numCols;
public:
	//default constructor
	Matrix() { numRows = 0; numCols = 0; matrix = nullptr; }
	//parameterized constructor
	Matrix(int rows, int cols)
	{
		numRows = rows;
		numCols = cols;
		matrix = new int*[numRows];
		for (int i = 0;i < rows;i++)
			matrix[i] = new int[numCols];
	}
	//deep copy constructor
	Matrix( const Matrix& obj)
	{
		numRows = obj.numRows;
		numCols = obj.numCols;
		matrix = nullptr;
		matrix = new int* [numRows];
		for (int i = 0;i < numRows;i++)
		{
			matrix[i] = new int[numCols];
			for (int j = 0;j < numCols;j++)
				matrix[i][j] = obj.matrix[i][j];
		}

	}
	int get_rows()
	{
		return numRows;
	}
	int get_Cols()
	{
		return numCols;
	}
	friend istream &operator>>(istream& in, Matrix& grid);
	friend ostream &operator<<(ostream& out,const Matrix grid);
	//uniary minus
	Matrix operator-()
	{
		Matrix temp(numRows, numCols);
		for (int i = 0;i < numRows;i++)
		{
			for (int j = 0;j < numCols;j++)
				temp.matrix[i][j] = -matrix[i][j];
		}
		return temp;
	}
	Matrix operator + (Matrix grid)
	{
		if (numRows == grid.numRows && numCols == grid.numCols)
		{
			Matrix temp(numRows, numCols);
			for (int i = 0;i < numRows;i++)
			{
				for (int j = 0;j < numCols;j++)
					temp.matrix[i][j] = matrix[i][j] + grid.matrix[i][j];
			}
			return temp;
        }
			cout << "the addition is not possible";
			return {};
	}
	Matrix operator - (Matrix grid)
	{
		if (numRows == grid.numRows && numCols == grid.numCols)
		{
			Matrix temp(numRows, numCols);
			for (int i = 0;i < numRows;i++)
			{
				for (int j = 0;j < numCols;j++)
					temp.matrix[i][j] = matrix[i][j] - grid.matrix[i][j];
			}
			return temp;
		}
		cout << "the subtraction is not possible";

		return {};
	}
	Matrix operator * (Matrix grid)
	{
		if (numCols == grid.numRows)
		{
			Matrix temp(numRows, grid.numCols);
			for (int i = 0;i < numRows;i++)
			{
				for (int j = 0;j < grid.numCols;j++)
				{
					temp.matrix[i][j] = 0;
					for (int k = 0;k < grid.numCols;k++)
						temp.matrix[i][j] += matrix[i][k] + grid.matrix[j][k];
				}
			}
			return temp;
		}

		cout << "multiplication not possible";
		return {};
	}
	//subscript operator
	int* operator[](const int i)
	{
		if (i >= 0 && i < numRows && i < numCols)
		{
			return matrix[i];
		}
	}
	//assignment operator
	Matrix& operator=(const Matrix& obj)
	{
		for (int i = 0;i < numRows;i++)
			delete matrix[i];

		delete matrix;
		numCols = obj.numCols;
		numRows = obj.numRows;
		matrix = new int* [numRows];
		for (int i = 0;i < numRows;i++)
		{
			matrix[i] = new int[numCols];
			for (int j = 0;j < numCols;j++)
				matrix[i][j] = obj.matrix[i][j];
		}

		return *this;
	}

};
istream& operator>>(istream& in, Matrix &grid)
{
	for (int i = 0;i < grid.numRows;i++)
	{
		for (int j = 0;j < grid.numCols;j++)
			in >>grid.matrix[i][j];
		cout << endl;
	}
	return in;
}
ostream& operator<<(ostream& out, const Matrix grid)
{
	for (int i = 0;i < grid.numRows;i++)
	{
		for (int j = 0;j < grid.numCols;j++)
			out<< grid.matrix[i][j]<<" ";
		out << endl;
	}
	return out;
}
int main()
{

Matrix m1(2, 2);
cin >> m1;
Matrix m2(2, 2);
cin >> m2;
Matrix sum = m1 + m2;
Matrix product = m1 * m2;
cout << sum << product;
}



