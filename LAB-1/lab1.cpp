#include "header.h"

int main()
{
	setlocale(LC_ALL, ".1251");
	ComputationalMethods example(5, 1);
	example.CreateRandomMatrixWithDiagonalDominanceDividedBy100WithoutUnknown();
	example.CreateRandomAnswers();
	example.FindingUnknowns();
	example.Unite();
	example.OutputOfMatrix();
	example.GaussWithoutChoosingMainElement();
	example.CountResidual();
	example.OutputOfMatrix();
	return 0;
}
