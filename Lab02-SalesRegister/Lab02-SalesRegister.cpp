#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

// Changed to current tax amounts:
const double MO_SALES_TAX = 0.04225;
const double KS_SALES_TAX = 0.0615;

double saleAmountCalc(int, double);
double salesTaxCalc(double, string);
void displaySaleData(string, double, double, string);

struct Customer
{
public :
	string name = "";
	string stateCode = "MO";
	int itemAmount = 0;
	double itemPrice = 0.0;
};

int main()
{
	fstream fileStream;

	fileStream.open("SalesRegister.txt");

	if (!fileStream)
	{
		cout << "Error: failed to open file.";
		system("pause");
		return -1;
	}

	// List of customers:
	vector<Customer> customers;
	int count = 0;
	
	// Prime read:
	Customer temp;
	fileStream >> temp.name;
	
	while (!fileStream.eof())
	{
		fileStream >> temp.stateCode >> temp.itemAmount >> temp.itemPrice;
		customers.insert(customers.begin() + count, temp);

		fileStream >> temp.name;

		count++;
	}

	for (int n = 0; n < count; n++)
	{
		double saleAmount = saleAmountCalc(customers[n].itemAmount, customers[n].itemPrice);
		double taxAmount = salesTaxCalc(saleAmount, customers[n].stateCode);

		displaySaleData(customers[n].name, saleAmount, taxAmount, customers[n].stateCode);
	}

	// Get totals:
	double salesAmountTotal = 0.0;
	double taxAmountTotalKS = 0.0;
	double taxAmountTotalMO = 0.0;

	for (int n = 0; n < count; n++)
	{
		double saleAmount = saleAmountCalc(customers[n].itemAmount, customers[n].itemPrice);
		salesAmountTotal += saleAmount;

		if (customers[n].stateCode == "KS")
		{
			taxAmountTotalKS += salesTaxCalc(saleAmount, customers[n].stateCode);
		}
		else
		{
			taxAmountTotalMO += salesTaxCalc(saleAmount, customers[n].stateCode);
		}
	}

	cout << endl << endl << setw(30) << '$' << "  " << salesAmountTotal << "  $" << taxAmountTotalKS + taxAmountTotalMO << "  Total" << endl;
	cout << endl << "Sales Tax: " << taxAmountTotalMO << "  MO" << endl;
	cout << endl << "           " << taxAmountTotalKS << "  KS" << endl;


	cout << endl << endl;
	system("pause");
    return 0;
}

double saleAmountCalc(int sold, double price)
{
	return sold * price;
}

double salesTaxCalc(double amount, string stateCode)
{
	if (stateCode == "KS")
		return amount * KS_SALES_TAX;
	
	return amount * MO_SALES_TAX;
}

void displaySaleData(string customerName, double salesAmount, double salesTax, string stateCode)
{
	static char dolSign = '$';

	cout << customerName << setw(30 - customerName.length()) << dolSign << setw(10) << setprecision(2) << fixed << salesAmount << setw(10) << dolSign << setw(10) << setprecision(2) << fixed << salesTax << setw(5) << stateCode << endl;
}