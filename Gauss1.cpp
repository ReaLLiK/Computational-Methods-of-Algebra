#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <time.h>

using namespace std;

void CreateRandomMatrix(vector<vector<double>>& matrix, int SizeOfUnknown)
{
	double input;
	for(int i=0; i<matrix.size();++i)
		for (int j=0; j<matrix.size() + SizeOfUnknown; ++j)
		{
				input = rand();
				matrix[i].push_back(input);
		}
}

void CreateRandomMatrixWithDiagonalDominance(vector<vector<double>>& matrix, int SizeOfUnknown)
{
	double input;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
		{
			input = rand();
			matrix[i].push_back(input);
		}
		for (int j = 0; j < matrix.size(); ++j)
			if (i != j)
				matrix[i][i] += matrix[i][j];
	}
}

void CreateRandomMatrixWithDiagonalDominanceDividedBy100(vector<vector<double>>& matrix, int SizeOfUnknown)
{
	double input;
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
		{
			input = rand();
			matrix[i].push_back(input/100);
		}
		for (int j = 0; j < matrix.size(); ++j)
			if (i != j)
				matrix[i][i] += matrix[i][j];
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

void CreateOwnFractionMatrix(vector<vector<double>>& matrix, int SizeOfUnknown, int Accuracy)
{
	double Numerator, Denominator;
	cout << "Введите всю дополненую матрицу построчно, первым вводится числитель, затем знаменатель(не менее заданной точности): \n";
	for (int i = 0; i < matrix.size(); ++i)
		for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
		{
				cin >> Numerator>>Denominator;
			matrix[i].push_back(round(Numerator/Denominator * pow(10, Accuracy)) / pow(10, Accuracy));
		}
}

void CreateOwnMatrixByFormula(vector<vector<double>>& matrix, int SizeOfUnknown, int Accuracy)   //   a=1/i+j-1
{
	for (double i = 0; i < matrix.size(); ++i)
	{
		for (double j = 0; j < matrix.size() + SizeOfUnknown; ++j)
		{
			if(j<matrix.size())
			matrix[i].push_back(round(1 / (i + 1 + j) * pow(10, Accuracy)) / pow(10, Accuracy));
			else
			{
				if (j == matrix.size() + i)
				{
					matrix[i].push_back(1);
				}
				else
					matrix[i].push_back(0);
			}
		}
	}
} 

void OutputOfMatrixWithAccuracy(vector<vector<double>> matrix, int Accuracy)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (auto j : matrix[i])
		{
			cout <<setw(Accuracy+5)<<setprecision(Accuracy)<< j << ' ';
		}
		cout << '\n'<<'\n';
	}
}

void OutputOfMatrixWithoutAccuracy(vector<vector<double>> matrix, int Accuracy)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (auto j : matrix[i])
		{
			cout << setw(9) << j << ' ';
		}
		cout << '\n' << '\n';
	}
}

void OutPutOfAnswer(vector<vector<double>> matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[0].size()-matrix.size(); ++j)
		{
			cout << "x[" << j + 1 << "][" << i + 1 << "] = " << matrix[i][j + matrix.size()] << "   ";
		}
		cout << "\n\n";
	}
}

void OutPutOfAnswerWithSwitches(vector<vector<double>> matrix, vector<int> switches)
{
	vector<vector<double>> answers(matrix[0].size() - matrix.size());
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = matrix.size(); j < matrix[0].size(); ++j)
			answers[j-matrix.size()].push_back(matrix[i][j]);
	}
	int k = switches.size();
		while (k)
		{
			for (int i = 0; i < switches.size(); ++i)
			{
				if (switches[i] != i)
				{
					for (int j = 0; j < answers.size(); ++j)
						swap(answers[j][i], answers[j][switches[i]]);
				}
				swap(switches[i], switches[switches[i]]);
			}
			k /= 2;
		}
	for (int i = 0; i <answers[0].size(); ++i)
	{
		for (int j = 0; j < answers.size(); ++j)
		{
			cout << "x[" << j+1 << "][" << i+1 << "] = " << answers[j][i] << "   ";
		}
		cout << "\n\n";
	}
}

void DirectMove(vector<vector<double>>& matrix, int steps, int Accuracy)
{
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
}

void DirectMoveOfGaussWithoutChoosingOfMainElement(vector<vector<double>> &matrix, int steps, int Accuracy, double &Det)
{
	DirectMove(matrix, steps, Accuracy);
	if(steps<matrix.size()-1)
	DirectMoveOfGaussWithoutChoosingOfMainElement(matrix, steps + 1, Accuracy, Det);
}

void DirectMoveOfGaussWithChoosingOfMainElementInColumn(vector<vector<double>>& matrix, int steps, int Accuracy, double &Det)
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
	Det *= matrix[steps][steps];
	DirectMove(matrix, steps, Accuracy);
	if (steps < matrix.size() - 1)
		DirectMoveOfGaussWithChoosingOfMainElementInColumn(matrix, steps + 1, Accuracy, Det);
}

void DirectMoveOfGaussWithChoosingOfMainElementInLine(vector<vector<double>>& matrix, int steps, int Accuracy, vector<int>&switches, double &Det)
{
	double max_element = 0;
	int max_element_position = steps;
	for (int k = steps; k < matrix.size(); ++k)
	{
		if (abs(matrix[steps][k]) > max_element)
		{
			max_element = matrix[steps][k];
			max_element_position = k;
		}
	}
	for (int k = 0; k < matrix.size(); ++k)
	{
		swap(matrix[k][steps], matrix[k][max_element_position]);
	}
	swap(switches[steps], switches[max_element_position]);
	Det *= matrix[steps][steps];
	DirectMove(matrix, steps, Accuracy);
	if (steps < matrix.size() - 1)
		DirectMoveOfGaussWithChoosingOfMainElementInLine(matrix, steps + 1, Accuracy, switches, Det);
}

void DirectMoveOfGaussWithChoosingOfMainElementInMatrix(vector<vector<double>>& matrix, int steps, int Accuracy, vector<int>& switches, double &Det)
{
	double max_element = 0;
	pair<int, int> max_element_position;
	max_element_position.first = steps;
	max_element_position.second = steps;
	for (int k = steps; k < matrix.size(); ++k)
	{
		for(int l=steps; l<matrix.size(); ++l)
		if (abs(matrix[k][l]) > max_element)
		{
			max_element = matrix[k][l];
			max_element_position.first = k;
			max_element_position.second = l;
		}
	}
	for (int k = 0; k < matrix.size(); ++k)
	{
		swap(matrix[k][steps], matrix[k][max_element_position.second]);
	}
	swap(switches[steps], switches[max_element_position.second]);
	swap(matrix[max_element_position.first], matrix[steps]);
	Det *= matrix[steps][steps];
	DirectMove(matrix, steps, Accuracy);
	if (steps < matrix.size() - 1)
		DirectMoveOfGaussWithChoosingOfMainElementInMatrix(matrix, steps + 1, Accuracy, switches, Det);
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
	double Det = 1;
	DirectMoveOfGaussWithoutChoosingOfMainElement(matrix, 0, Accuracy, Det);
	ReverseMoveOfGauss(matrix, matrix.size() - 1, Accuracy);
	cout << "Полученный матрица(Метод Гаусса без выбора главного элемента):\n\n";
	OutPutOfAnswer(matrix);
	cout << '\n' << setprecision(Accuracy) << "Определитель матрицы: \n" << Det << '\n'<<'\n';
}

void GaussWithChoosingMainElementInColumn(vector<vector<double>>& matrix, int Accuracy)
{
	double Det = 1;
	DirectMoveOfGaussWithChoosingOfMainElementInColumn(matrix, 0, Accuracy, Det);
	ReverseMoveOfGauss(matrix, matrix.size() - 1, Accuracy);
	cout << "Полученный результат(Метод Гаусса с выбором главного элемента в столбце):\n\n";
	OutPutOfAnswer(matrix);
	cout << '\n' << setprecision(Accuracy) << "Определитель матрицы: \n" << Det << '\n'<<'\n';
}

void GaussWithChoosingMainElementInLine(vector<vector<double>>& matrix, int Accuracy)
{
	double Det = 1;
	vector<int> switches(matrix.size());
	for (int i = 0; i < switches.size(); ++i)
		switches[i]=i;
	DirectMoveOfGaussWithChoosingOfMainElementInLine(matrix, 0, Accuracy, switches, Det);
	ReverseMoveOfGauss(matrix, matrix.size() - 1, Accuracy);
	cout << "Полученный результат(Метод Гаусса с выбором главного элемента в строке):\n\n";
	OutPutOfAnswerWithSwitches(matrix, switches);
	cout << '\n' << setprecision(Accuracy) << "Определитель матрицы: \n" << Det << '\n'<<'\n';
}

void GaussWithChoosingMainElementInMatrix(vector<vector<double>>& matrix, int Accuracy)
{
	double Det = 1;
	vector<int> switches(matrix.size());
	for (int i = 0; i < switches.size(); ++i)
		switches[i] = i;
	DirectMoveOfGaussWithChoosingOfMainElementInMatrix(matrix, 0, Accuracy, switches, Det);
	ReverseMoveOfGauss(matrix, matrix.size() - 1, Accuracy);
	cout << "Полученный результат(Метод Гаусса с выбором главного элемента в Матрице):\n\n";
	OutPutOfAnswerWithSwitches(matrix, switches);
	cout << '\n' <<setprecision(Accuracy)<< "Определитель матрицы: \n" << Det<<'\n'<<'\n';
}

int main()
{
	setlocale(LC_ALL, ".1251");
	vector<vector<double>> matrix;
	int SizeOfMatrix,SizeOfUnknown, choice, Accuracy;
	do {
		cout << "Введите размеры матрицы: \n";
	cin >> SizeOfMatrix;
	} while (SizeOfMatrix < 1);
	matrix.resize(SizeOfMatrix);
	do {
		cout << "Введите количество неизвестных\n";
		cin >> SizeOfUnknown;
	} while (SizeOfUnknown < 1);
	do {
		cout << "Своя генерация или случайная?\n1-случайная генерация\n2-своя генерация\n3-своя генерация дробных чисел\n4-генерация по формуле 1/(i+j-1)\n5-случайная генерация с диагональным доминированием\n6-случайная генерация с диагональным доминированием действительных чисел с 2 знаками после запятой\n";
		cin >> choice;
	} while ((choice != 1) && (choice != 2)&&(choice!=3)&&(choice!=4)&&(choice!=5) && (choice != 6));
	do {
		cout << "Введите количество знаков после запятой нужной Вам точности: \n";
		cin >> Accuracy;
	} while ((Accuracy < 0)||(Accuracy>153));
	if (choice == 1)
	{
		srand(time(0));
		CreateRandomMatrix(matrix, SizeOfUnknown);
	}
	if (choice == 2)
	{
		CreateOwnMatrix(matrix, SizeOfUnknown, Accuracy);
	}
	if (choice == 3)
	{
		CreateOwnFractionMatrix(matrix, SizeOfUnknown, Accuracy);
	}
	if (choice == 4)
	{
		CreateOwnMatrixByFormula(matrix, SizeOfUnknown, Accuracy);
	}
	if (choice == 5)
	{
		CreateRandomMatrixWithDiagonalDominance(matrix, SizeOfUnknown);
	}
	if (choice == 6)
	{
		CreateRandomMatrixWithDiagonalDominanceDividedBy100(matrix, SizeOfUnknown);
	}
	cout << "\nИзначальная матрица:\n\n";
	OutputOfMatrixWithoutAccuracy(matrix, Accuracy);
	//vector<vector<double>> matrix2=matrix;
	//vector<vector<double>> matrix3=matrix;
	vector<vector<double>> matrix4=matrix;
	//GaussWithoutChoosingMainElement(matrix, Accuracy);
	//GaussWithChoosingMainElementInColumn(matrix2, Accuracy);
	//GaussWithChoosingMainElementInLine(matrix3, Accuracy);
	GaussWithChoosingMainElementInMatrix(matrix4, Accuracy);
	return 0;
}
