#include "TSM.h"

TSM::TSM()
{
	string name;
	cout << "Wprowadz nazwe pliku: ";
	cin >> name;
	ReadFromFile(name);
	for (int i = 0; i < distancesMatrix.size(); i++)
	{
		for (int j = 0; j < distancesMatrix[i].size(); j++)
		{
			cout << distancesMatrix[i][j] << " ";
		}
		cout << endl;
	}
	RunBruteForce();
	RunGreedyAlgorithm();
}

TSM::~TSM()
{
}

void TSM::RunBruteForce()
{
	cost = 0;
	if (permutation.size() != 0)
	{	
		permutation.clear();
		minimumPermutation.clear();
	}

	for (int i = 0; i < distancesMatrix.size(); i++)
	{
		permutation.push_back(i);
	}

	cost = CalculateCost(permutation);
	minimumPermutation = permutation;

	do
	{
		if (CalculateCost(permutation) < cost)
		{
			cost = CalculateCost(permutation);
			minimumPermutation = permutation;
		}
	} while (next_permutation(permutation.begin() + 1, permutation.end()));
	
	minimumPermutation.push_back(0);
	cout << endl << endl << "Minimalny koszt: " << cost << endl;
	for (int i = 0; i < minimumPermutation.size(); i++)
	{
		cout << minimumPermutation[i] << " ";
	}
	cout << endl;
}

void TSM::RunGreedyAlgorithm()
{
	cost = 0;
	vector<bool> checkedTable;
	checkedTable.resize(distancesMatrix.size(), false);
	int min;
	int index = 0;
	int tempIndex;

	if (minimumPermutation.size() != 0)
	{
		permutation.clear();
		minimumPermutation.clear();
	}

	checkedTable[0] = true;

	int i = 0;
	int ind = 0;
	minimumPermutation.push_back(0);

	while (i < distancesMatrix.size() - 1)
	{
		int k;
		for (k = 0; k < checkedTable.size(); k++)
		{
			if (!checkedTable[k] && distancesMatrix[index][k] > 0)
				break;
		}

		min = distancesMatrix[index][k];
		tempIndex = k;

		for (int j = 0; j < distancesMatrix[index].size(); j++)
		{
			if (distancesMatrix[index][j] != 0)
			{
				if (checkedTable[j] == false)
					if (distancesMatrix[index][j] < min)
					{
						min = distancesMatrix[index][j];
						tempIndex = j;
					}
			}
		}
		index = tempIndex;

		ind = index;
		minimumPermutation.push_back(index);
		checkedTable[index] = true;
		i++;
	}

	cost = CalculateCost(minimumPermutation);
	minimumPermutation.push_back(0);
	cout << endl << endl << "Minimalny koszt: " << cost << endl;
	for (int i = 0; i < minimumPermutation.size(); i++)
	{
		cout << minimumPermutation[i] << " ";
	}
	cout << endl;
}

int TSM::CalculateCost(vector<int> x)
{
	int cost = 0;

	for (int i = 0; i < x.size() - 1; i++)
	{
		cost += distancesMatrix[x[i]][x[i + 1]];
	}
	cost += distancesMatrix[x[x.size() - 1]][0];

	return cost;
}

void TSM::ReadFromFile(string fileName)
{
	fstream file(fileName, ios_base::in);

	if (file.good())
	{
		file >> numberOfCities;

		distancesMatrix.resize(numberOfCities, vector<int>(numberOfCities, 0));

		for (int i = 0; i < numberOfCities; i++)
		{
			for (int j = 0; j < numberOfCities; j++)
			{
				file >> distancesMatrix[i][j];
			}			
		}
		file.close();
	}
}
