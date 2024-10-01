#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <time.h>

using namespace std;

class ComputationalMethods
{
	int SizeOfMatrix;
	int SizeOfUnknown;
	vector<vector<double>> matrix;
	vector<vector<double>> matrix2;
	vector<vector<double>> Reverse; //обратная матрица
	double Det;
	vector<double> Unknown;
	vector<vector<double>> answers;
	vector<double> Answers; //Вектор решений
	vector<int> switches;
	vector<double> residual; //невязка
public:

	ComputationalMethods(int SizeOfMatrix1, int SizeOfUnknown1)
	{
		SizeOfMatrix = SizeOfMatrix1;
		matrix.resize(SizeOfMatrix);
		SizeOfUnknown = SizeOfUnknown1;
		Det = 1;
		Unknown.resize(SizeOfMatrix);
		Answers.resize(SizeOfMatrix);
		answers.resize(SizeOfMatrix);
		switches.resize(SizeOfMatrix);
		residual.resize(SizeOfMatrix);
		Reverse.resize(SizeOfMatrix);
		for (int i = 0; i < SizeOfMatrix; ++i)
		{
			Reverse[i].resize(SizeOfMatrix);
			Reverse[i][i]++;
		}
	};
	~ComputationalMethods()
	{
	};

	void FindingUnknowns()
	{
		for(int i=0; i<SizeOfMatrix; ++i)
			for (int j = 0; j < SizeOfMatrix; ++j)
			{
				Unknown[i] += matrix[i][j] * Answers[j];
			}
	}

	void Unite()
	{
		for (int i = 0; i < SizeOfMatrix; ++i)
		{
			matrix[i].push_back(Unknown[i]);
		}
	}
	
	//void FindReverse()
	//{
	//	for (int i = 0; i < SizeOfMatrix; ++i)
	//	{
	//		for (int j = 0; j < SizeOfMatrix; ++j)
	//		{
	//			matrix2[i].push_back(Reverse[i][j]);
	//		}
	//	}
	//	GaussWithChoosingMainElementInMatrix();
	//	cout << "Обратная матрица:\n";
	//	for (int i = 0; i < SizeOfMatrix; ++i)
	//		for (int j = 0; j < SizeOfMatrix; ++j)
	//		{
	//			cout<<mat
	//		}
	//}

	void CreateRandomMatrix()
	{
		srand(time(0));
		double input;
		for (int i = 0; i < matrix.size(); ++i)
			for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
			{
				input = rand();
				matrix[i].push_back(input);
			}
	}

	void CreateRandomMatrixWithDiagonalDominance()
	{
		srand(time(0));
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

	void CreateRandomMatrixWithDiagonalDominanceWithoutUnknown()
	{
		srand(time(0));
		double input;
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix.size(); ++j)
			{
				input = rand();
				matrix[i].push_back(input);
				if (i != j)
					matrix[i][i] += matrix[i][j];
			}
		}
	}

	void CreateRandomMatrixWithDiagonalDominanceDividedBy100()
	{
		srand(time(0));
		double input;
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
			{
				input = rand();
				matrix[i].push_back(input / 100);
			}
			for (int j = 0; j < matrix.size(); ++j)
				if (i != j)
					matrix[i][i] += matrix[i][j];
		}
	}

	void CreateRandomMatrixWithDiagonalDominanceDividedBy100WithoutUnknown()
	{
		srand(time(0));
		double input;
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix.size(); ++j)
			{
				input = rand();
				matrix[i].push_back(input / 100);

			}
			for (int j = 0; j < matrix.size(); ++j)
			{
				if (i != j)
					matrix[i][i] += matrix[i][j];
			}
		}
		matrix2 = matrix;
	}

	void CreateOwnMatrix()
	{
		double input;
		cout << "Введите всю дополненую матрицу построчно: \n";
		for (int i = 0; i < matrix.size(); ++i)
			for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
			{
					cin >> input;
				matrix[i].push_back(input);
			}
	}

	void CreateOwnMatrixWithoutUnknown()
	{
		double input;
		cout << "Введите всю матрицу построчно: \n";
		for (int i = 0; i < matrix.size(); ++i)
			for (int j = 0; j < matrix.size(); ++j)
			{
					cin >> input;
				matrix[i].push_back(input);
			}
	}

	void CreateOwnFractionMatrix()
	{
		double Numerator, Denominator;
		cout << "Введите всю дополненую матрицу построчно, первым вводится числитель, затем знаменатель: \n";
		for (int i = 0; i < matrix.size(); ++i)
			for (int j = 0; j < matrix.size() + SizeOfUnknown; ++j)
			{
				do {
					cin >> Numerator >> Denominator;
				} while (Denominator == 0);
				matrix[i].push_back(Numerator / Denominator);
			}
	}

	void CreateOwnFractionMatrixWithoutUnknown()
	{
		double Numerator, Denominator;
		cout << "Введите всю матрицу построчно, первым вводится числитель, затем знаменатель: \n";
		for (int i = 0; i < matrix.size(); ++i)
			for (int j = 0; j < matrix.size(); ++j)
			{
				do {
					cin >> Numerator >> Denominator;
				} while (Denominator == 0);
				matrix[i].push_back(Numerator / Denominator);
			}
	}

	void CreateOwnMatrixByFormula()   //   a=1/i+j-1
	{
		for (double i = 0; i < matrix.size(); ++i)
		{
			for (double j = 0; j < matrix.size() + SizeOfUnknown; ++j)
			{
				if (j < matrix.size())
					matrix[i].push_back(1 / (i + 1 + j));
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

	void CreateOwnMatrixByFormulaWithoutUnknown()   //   a=1/i+j-1
	{
		for (double i = 0; i < matrix.size(); ++i)
		{
			for (double j = 0; j < matrix.size(); ++j)
			{
				matrix[i].push_back(1 / (i + 1 + j));
			}
		}
	}

	void CreateRandomAnswers()
	{
		srand(time(0));
		double input;
		cout << "Вектор решений:\n";
		for (int i=0; i<SizeOfMatrix; ++i)
		{
			input = rand();
			Answers[i] = input / 100;
			cout << Answers[i] << '\n';
		}
		cout << '\n';
	}

	void OutputOfMatrix()
	{
		cout << "Матрица имеет вид:\n\n";
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (auto j : matrix[i])
			{
				cout << setw(9) << j << ' ';
			}
			cout << '\n' << '\n';
		}
	}

	void OutPutOfAnswer()
	{
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix[0].size() - matrix.size(); ++j)
			{
				cout << "x[" << j + 1 << "][" << i + 1 << "] = " << matrix[i][j + matrix.size()] << "   ";
			}
			cout << "\n\n";
		}
	}

	void OutPutOfAnswerWithSwitches()
	{
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = matrix.size(); j < matrix[0].size(); ++j)
				answers[j - matrix.size()].push_back(matrix[i][j]);
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
		for (int i = 0; i < answers[0].size(); ++i)
		{
			for (int j = 0; j < answers.size(); ++j)
			{
				cout << "x[" << j + 1 << "][" << i + 1 << "] = " << answers[j][i] << "   ";
			}
			cout << "\n\n";
		}
	}

	void DirectMove(int steps)
	{
		Det *= matrix[steps][steps];
		for (int j = matrix[steps].size() - 1; j >= steps; --j)
		{
			matrix[steps][j] = matrix[steps][j] / matrix[steps][steps];
		}
		for (int i = matrix[steps].size() - 1; i >= 0; --i)
			for (int j = steps + 1; j < matrix.size(); ++j)
				matrix[j][i] -= (matrix[steps][i] * matrix[j][steps]);
	}

	void DirectMoveOfGaussWithoutChoosingOfMainElement(int steps)
	{
		DirectMove(steps);
		if (steps < matrix.size() - 1)
			DirectMoveOfGaussWithoutChoosingOfMainElement(steps + 1);
	}

	void DirectMoveOfGaussWithChoosingOfMainElementInColumn(int steps)
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
		DirectMove(steps);
		if (steps < matrix.size() - 1)
			DirectMoveOfGaussWithChoosingOfMainElementInColumn(steps + 1);
	}

	void DirectMoveOfGaussWithChoosingOfMainElementInLine( int steps)
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
		DirectMove(steps);
		if (steps < matrix.size() - 1)
			DirectMoveOfGaussWithChoosingOfMainElementInLine(steps + 1);
	}

	void DirectMoveOfGaussWithChoosingOfMainElementInMatrix(int steps)
	{
		double max_element = 0;
		pair<int, int> max_element_position;
		max_element_position.first = steps;
		max_element_position.second = steps;
		for (int k = steps; k < matrix.size(); ++k)
		{
			for (int l = steps; l < matrix.size(); ++l)
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
		DirectMove(steps);
		if (steps < matrix.size() - 1)
			DirectMoveOfGaussWithChoosingOfMainElementInMatrix(steps + 1);
	}

	void ReverseMoveOfGauss(int steps)
	{
		for (int i = matrix[steps].size() - 1; i >= 0; --i)
			for (int j = steps - 1; j >= 0; --j)
				matrix[j][i] -= (matrix[steps][i] * matrix[j][steps]);
		if (steps > 0)
			ReverseMoveOfGauss(steps - 1);
	}

	void GaussWithoutChoosingMainElement()
	{
		DirectMoveOfGaussWithoutChoosingOfMainElement(0);
		ReverseMoveOfGauss(matrix.size() - 1);
		cout << "Полученный результат(Метод Гаусса без выбора главного элемента):\n\n";
		OutPutOfAnswer();
		cout << '\n' << "Определитель матрицы: \n" << Det << '\n' << '\n';
	}

	void GaussWithChoosingMainElementInColumn()
	{
		DirectMoveOfGaussWithChoosingOfMainElementInColumn(0);
		ReverseMoveOfGauss(matrix.size() - 1);
		cout << "Полученный результат(Метод Гаусса с выбором главного элемента в столбце):\n\n";
		OutPutOfAnswer();
		cout << '\n'  << "Определитель матрицы: \n" << Det << '\n' << '\n';
	}

	void GaussWithChoosingMainElementInLine()
	{
		vector<int> switches(matrix.size());
		for (int i = 0; i < switches.size(); ++i)
			switches[i] = i;
		DirectMoveOfGaussWithChoosingOfMainElementInLine(0);
		ReverseMoveOfGauss(matrix.size() - 1);
		cout << "Полученный результат(Метод Гаусса с выбором главного элемента в строке):\n\n";
		OutPutOfAnswerWithSwitches();
		cout << '\n' << "Определитель матрицы: \n" << Det << '\n' << '\n';
	}

	void GaussWithChoosingMainElementInMatrix()
	{
		for (int i = 0; i < switches.size(); ++i)
			switches[i] = i;
		DirectMoveOfGaussWithChoosingOfMainElementInMatrix(0);
		ReverseMoveOfGauss(matrix.size() - 1);
		cout << "Полученный результат(Метод Гаусса с выбором главного элемента в Матрице):\n\n";
		OutPutOfAnswerWithSwitches();
		cout << '\n'<< "Определитель матрицы: \n" << Det << '\n' << '\n';
	}

	void CountResidual()
	{
		cout << "Вектор невязки:\n";
		for (int i = 0; i < SizeOfMatrix; ++i)
		{
			residual[i] = matrix[i][SizeOfMatrix] - Answers[i];
			cout << residual[i] << '\n';
		}
		cout << '\n';
	}
};
