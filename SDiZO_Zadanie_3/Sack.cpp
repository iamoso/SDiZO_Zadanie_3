#include "Sack.h"

Sack::Sack()
{
	string name;
	cout << "Wprowadz nazwe pliku: ";
	cin >> name;
	ReadFromFile(name);
	cout << endl << endl << "Ilosc przedmiotow: " << itemsQuantity << endl;
	cout << "Pojemnosc plecaka: " << bagCapacity << endl << endl;

	cout << "Indeks | Waga | Wartosc" << endl;
	for (int i = 0; i < itemsQuantity; i++)
	{
		cout << setw(6) << i << " | " << setw(4) << weights[i] << " | " << setw(7) << values[i] << endl;
	}

	cout << endl << "Algorytm zupelny" << endl << endl;
	RunBruteForce();
	cout << endl << "Alogrytm zachlanny wartosci" << endl << endl;
	RunGreedyValue();
	cout << endl << "Algorytm zachlanny stosunek wartosci i rozmiaru" << endl << endl;
	RunGreedyValueRatio();
}

Sack::~Sack()
{
}

void Sack::RunBruteForce()
{
	int tempWeight;
	int tempValue;
	int maxCombinationValue = 0;
	int sumOfValues = 0;
	int sumOfWeights = 0;
	long long k = pow(2, itemsQuantity) - 1;
	vector<bool> tempMax(itemsQuantity);
	bruteForceTable.resize(itemsQuantity, false);

	for (int i = 0; i < k; i++)
	{
		tempValue = 0;
		tempWeight = 0;
		
		AddOne(0);

		for (int j = 0; j < itemsQuantity; j++)
		{
			if (bruteForceTable[j])
			{
				tempValue += values[j];
				tempWeight += weights[j];
			}
		}

		if (tempWeight <= bagCapacity && tempValue > maxCombinationValue)
		{
			maxCombinationValue = tempValue;
			for (int j = 0; j < itemsQuantity; j++)
			{
				tempMax[j] = bruteForceTable[j];
			}
		}
	}

	copy(tempMax.begin(), tempMax.end(), bruteForceTable.begin());

	cout << "Indeks | Waga | Wartosc" << endl;
	for (int i = 0; i < itemsQuantity; i++)
	{
		if (bruteForceTable[i])
		{
			cout << setw(6) << i << " | " << setw(4) << weights[i] << " | " << setw(7) << values[i] << endl;
			sumOfWeights += weights[i];
			sumOfValues += values[i];
		}
	}
	cout << endl << "Rozmiar w sumie: " << sumOfWeights << "\nWartosc w sumie: " << sumOfValues << endl;
}

void Sack::RunGreedyValue()
{
	int sumOfWeights = 0;
	int sumOfValues = 0;
	vector<int> tempValues(itemsQuantity);
	vector<int> tempWeights(itemsQuantity);

	copy(values.begin(), values.end(), tempValues.begin());
	copy(weights.begin(), weights.end(), tempWeights.begin());

	int k = 0;
	int l = itemsQuantity;

	for (int i = 0; i < itemsQuantity; i++)
	{
		k = 0;
		for (int j = 0; j < l - 1; j++)
		{
			if (tempValues[j] < tempValues[j + 1])
			{
				swap(tempValues[j], tempValues[j + 1]);
				swap(tempWeights[j], tempWeights[j + 1]);
				k++;
			}
		}
		l--;
		if (k == 0)
			break;
	}

	cout << "Indeks | Waga | Wartosc" << endl;
	for (int i = 0; i < itemsQuantity; i++)
	{
		if (sumOfWeights + tempWeights[i] <= bagCapacity)
		{
			sumOfWeights += tempWeights[i];
			sumOfValues += tempValues[i];
			cout << setw(6) << i << " | " << setw(4) << tempWeights[i] << " | " << setw(7) << tempValues[i] << endl;
		}
	}
	cout << endl << "Rozmiar w sumie: " << sumOfWeights << "\nWartosc w sumie: " << sumOfValues << endl;

}

void Sack::RunGreedyValueRatio()
{
	int sumOfWeights = 0;
	int sumOfValues = 0;
	vector<float> temp(itemsQuantity);
	vector<int> tempValues(itemsQuantity);
	vector<int> tempWeights(itemsQuantity);

	copy(values.begin(), values.end(), tempValues.begin());
	copy(weights.begin(), weights.end(), tempWeights.begin());
	for (int i = 0; i < itemsQuantity; i++)
	{
		temp[i] = (1.0 * tempValues[i]) / (1.0 *tempWeights[i]);
	}

	int k = 0;
	int l = itemsQuantity;

	for (int i = 0; i < itemsQuantity; i++)
	{
		k = 0;
		for (int j = 0; j < l - 1; j++)
		{
			if (temp[j] < temp[j + 1])
			{
				swap(temp[j], temp[j + 1]);
				swap(tempValues[j], tempValues[j + 1]);
				swap(tempWeights[j], tempWeights[j + 1]);
				k++;
			}
		}
		l--;
		if (k == 0)
			break;
	}

	cout << "Indeks | Waga | Wartosc" << endl;
	for (int i = 0; i < itemsQuantity; i++)
	{
		if (sumOfWeights + tempWeights[i] <= bagCapacity)
		{
			sumOfWeights += tempWeights[i];
			sumOfValues += tempValues[i];
			cout << setw(6) << i << " | " << setw(4) << tempWeights[i] << " | " << setw(7) << tempValues[i] << endl;
		}
	}
	cout << endl << "Rozmiar w sumie: " << sumOfWeights << "\nWartosc w sumie: " << sumOfValues << endl;
}

void Sack::AddOne(int place)
{
	if (bruteForceTable[place])
	{
		bruteForceTable[place] = false;
		AddOne(place + 1);
	}
	else
	{
		bruteForceTable[place] = true;
	}
}

void Sack::ReadFromFile(string fileName)
{
	fstream file(fileName, ios_base::in);

	if (file.good())
	{
		int value;
		int weight;

		file >> bagCapacity;
		file >> itemsQuantity;

		for (int i = 0; i < itemsQuantity; i++)
		{
			file >> weight;
			file >> value;
			weights.push_back(weight);
			values.push_back(value);
		}
		file.close();
	}
}
