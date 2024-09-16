#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <time.h>

using namespace std;

void OutputOfMatrix(vector<vector<double>> matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (auto j : matrix[i])
		{
			cout <<setw(9)<< j << ' ';
		}
		cout << '\n'<<'\n';
	}
}

void CreateRandomMatrix(vector<vector<double>>& matrix, int SizeOfUnknown, int Accuracy)
{
	double input;
	for(int i=0; i<matrix.size();++i)
		for (int j=0; j<matrix.size() + SizeOfUnknown; ++j)
		{
			do {
				input = rand();
				matrix[i].push_back(input);
			} while (abs(input) < 5 * pow(10, -Accuracy - 1));
		}
}

void CreateOwnMatrix(vector<vector<double>>& matrix, int SizeOfUnknown, int Accuracy)
{
	double input;
	cout << "Введите всю дополненую матрицу построчно(не менее заданной точности): \n";
	for(int i=0; i<matrix.size(); ++i)
		for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
		{
			do {
				cin >> input;
			} while ((abs(input) < 5*pow(10, -Accuracy-1))&&(input!=0));
			matrix[i].push_back(round(input*pow(10,Accuracy))/pow(10,Accuracy));
		}
}

void DirectMoveOfGaussWithoutChoosingOfMainElement(vector<vector<double>> &matrix, int steps, int Accuracy)
{
	for (int j = matrix[steps].size()-1; j >= steps; --j)
	{
		matrix[steps][j] = round(matrix[steps][j]/matrix[steps][steps]*pow(10,Accuracy))/pow(10,Accuracy);
	}
	for (int i = matrix[steps].size()-1; i >= 0; --i)
		for (int j = steps+1; j < matrix.size(); ++j)
		{
			matrix[j][i] -= (matrix[steps][i] * matrix[j][steps]);
			matrix[j][i] = round(matrix[j][i] * pow(10, Accuracy)) / pow(10, Accuracy);
		}
	if(steps<matrix.size()-1)
	DirectMoveOfGaussWithoutChoosingOfMainElement(matrix, steps + 1, Accuracy);
}

void DirectMoveOfGaussWithChoosingOfMainElementInColumn(vector<vector<double>>& matrix, int steps, int Accuracy)
{
	double max_element = 0;
	int max_element_position = steps;
	for (int k = steps; k < matrix.size(); ++k)
	{
		if (abs(matrix[k][steps]) > max_element)
		{
			max_element = matrix[k][steps];
			max_element_position = k;
		}
	}
	swap(matrix[max_element_position], matrix[steps]);

	for (int j = matrix[steps].size() - 1; j >= steps; --j)
	{
		matrix[steps][j] = round(matrix[steps][j] / matrix[steps][steps] * pow(10, Accuracy)) / pow(10, Accuracy);
	}
	for (int i = matrix[steps].size() - 1; i >= 0; --i)
		for (int j = steps + 1; j < matrix.size(); ++j)
		{
			matrix[j][i] -= (matrix[steps][i] * matrix[j][steps]);
			matrix[j][i] = round(matrix[j][i] * pow(10, Accuracy)) / pow(10, Accuracy);
		}
	OutputOfMatrix(matrix);
	if (steps < matrix.size() - 1)
		DirectMoveOfGaussWithChoosingOfMainElementInColumn(matrix, steps + 1, Accuracy);
}

void ReverseMoveOfGauss(vector<vector<double>> &matrix, int steps, int Accuracy)
{
	for (int i = matrix[steps].size() - 1; i >= 0; --i)
		for (int j = steps-1; j >=0; --j)
		{
			matrix[j][i] -= (matrix[steps][i] * matrix[j][steps]);
			matrix[j][i] = round(matrix[j][i] * pow(10, Accuracy)) / pow(10, Accuracy);
		}
	if(steps>0)
	ReverseMoveOfGauss(matrix, steps - 1, Accuracy);
}

void GaussWithoutChoosingMainElement(vector<vector<double>>& matrix, int Accuracy)
{
	DirectMoveOfGaussWithoutChoosingOfMainElement(matrix, 0, Accuracy);
	ReverseMoveOfGauss(matrix, matrix.size() - 1, Accuracy);
	cout << "Полученная матрица:\n\n";
	OutputOfMatrix(matrix);
}

void GaussWithChoosingMainElementInColumn(vector<vector<double>>& matrix, int Accuracy)
{
	DirectMoveOfGaussWithChoosingOfMainElementInColumn(matrix, 0, Accuracy);
	ReverseMoveOfGauss(matrix, matrix.size() - 1, Accuracy);
	cout << "Полученная матрица:\n\n";
	OutputOfMatrix(matrix);
}

int main()
{
	setlocale(LC_ALL, ".1251");
	vector<vector<double>> matrix;
	int SizeOfMatrix,SizeOfUnknown, choice, Accuracy;
	do {
		cout << "Введите размеры матрицы: \n";
	cin >> SizeOfMatrix;
	} while ((SizeOfMatrix < 1) || (SizeOfMatrix > 6));
	matrix.resize(SizeOfMatrix);
	do {
		cout << "Введите количество неизвестных\n";
		cin >> SizeOfUnknown;
	} while ((SizeOfUnknown < 1) || (SizeOfUnknown > 6));
	do {
		cout << "Своя генерация или случайная?\n1-случайная генерация\n2-своя генерация\n";
		cin >> choice;
	} while ((choice != 1) && (choice != 2));
	do {
		cout << "Введите количество знаков после запятой нужной Вам точности: \n";
		cin >> Accuracy;
	} while ((Accuracy < 0) || (Accuracy > 7));
	if (choice == 1)
	{
		srand(time(0));
		CreateRandomMatrix(matrix, SizeOfUnknown, Accuracy);
	}
	if (choice == 2)
	{
		CreateOwnMatrix(matrix, SizeOfUnknown, Accuracy);
	}
	cout << "Изначальная матрица:\n\n";
	OutputOfMatrix(matrix);
	vector<vector<double>> matrix2=matrix;
	GaussWithoutChoosingMainElement(matrix, Accuracy);
	GaussWithChoosingMainElementInColumn(matrix2, Accuracy);
	return 0;
}