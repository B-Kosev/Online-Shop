#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <limits>
#include <string>
#include <vector>

#include "stock.h"
#include "account.h"
#include "Shop.h"


#undef max //input validation conflict

using namespace	std;

shop KoseBoseShop;

string toLower(string str)
{
	string res;
	for (int i = 0;i < str.size();i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + 32;
		}
	}
	res = str;
	return res;
}

void priceRangeInputValidation(double& lowerInput, double& upperInput, double lowerBound, double upperBound)
{
	double eps = 0.001;
	while (true)
	{
		cin >> lowerInput >> upperInput;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input.\n";
			continue;
		}
		if ((lowerInput < upperInput) && (lowerInput > lowerBound || abs(lowerInput - lowerBound) < eps) && (upperInput < upperBound || abs(upperInput - upperBound) < eps)) return;
		cout << "Invalid input.\n";
	}
}

void printMainMenu()
{
	system("CLS");
	cout << "Welcome " << KoseBoseShop.getUser()->getUsername() << " to KoseBose Online Shop.\n";
	cout << "\nCategories:";
	cout << "\n--------------------------------------------------------\n";
	cout << "\n1) Clothes\n2) Food\n3) Tech\n4) All categories\n\n5) Search by price range\n6) Search by keyword\n\n7) Create new product (ONLY FOR ADMIN)\n\n8) Log out\n\n";

	KoseBoseShop.getUser()->printShoppingCart();
}

void printCategory(int pick_Category, double lowerBoundPrice, double upperBoundPrice, string searchByText)
{
	system("CLS");
	cout << "Welcome " << KoseBoseShop.getUser()->getUsername() << " to KoseBose Online Shop.\n\n";

	switch (pick_Category)
	{
	case 1:
	{
		cout << "Clothes: \n\n";
		for (int i = 0;i < KoseBoseShop.getNumberStocks();i++)
		{
			if (KoseBoseShop.getProducts()[i]->getCategory_ID() == pick_Category && KoseBoseShop.getProducts()[i]->getAmount() > 0)
			{
				KoseBoseShop.getProducts()[i]->print();
				cout << endl;
			}
		}
		break;
	}
	case 2:
	{
		cout << "Food: \n\n";
		for (int i = 0;i < KoseBoseShop.getNumberStocks();i++)
		{
			if (KoseBoseShop.getProducts()[i]->getCategory_ID() == pick_Category && KoseBoseShop.getProducts()[i]->getAmount() > 0)
			{
				KoseBoseShop.getProducts()[i]->print();
				cout << endl;
			}
		}
		break;
	}
	case 3:
	{
		cout << "Tech:\n\n";
		for (int i = 0;i < KoseBoseShop.getNumberStocks();i++)
		{
			if (KoseBoseShop.getProducts()[i]->getCategory_ID() == pick_Category && KoseBoseShop.getProducts()[i]->getAmount() > 0)
			{
				KoseBoseShop.getProducts()[i]->print();
				cout << endl;
			}
		}
		break;
	}
	case 4:
	{
		cout << "All categories:\n";
		for (int i = 0;i < KoseBoseShop.getNumberStocks();i++)
		{
			if (KoseBoseShop.getProducts()[i]->getAmount() > 0) KoseBoseShop.getProducts()[i]->print();
			cout << endl;
		}
		break;
	}
	case 5:
	{
		cout << "All products between $" << lowerBoundPrice << " and $" << upperBoundPrice << ": \n";
		for (int i = 0;i < KoseBoseShop.getNumberStocks();i++)
		{
			if (KoseBoseShop.getProducts()[i]->getPrice() >= lowerBoundPrice && KoseBoseShop.getProducts()[i]->getPrice() <= upperBoundPrice && KoseBoseShop.getProducts()[i]->getAmount() > 0)
			{
				KoseBoseShop.getProducts()[i]->print();
				cout << endl;
			}
		}
		break;
	}
	case 6:
	{
		cout << "Results for \"" << searchByText << "\": \n";

		string nameAndDesc; //concatenate name and description

		for (int i = 0;i < KoseBoseShop.getNumberStocks();i++)
		{
			nameAndDesc.clear();
			nameAndDesc = KoseBoseShop.getProducts()[i]->getName() + KoseBoseShop.getProducts()[i]->getDescription();

			nameAndDesc = toLower(nameAndDesc);

			if (nameAndDesc.find(toLower(searchByText))>=0 && nameAndDesc.find(toLower(searchByText))<=nameAndDesc.size() && KoseBoseShop.getProducts()[i]->getAmount() > 0)
			{
				KoseBoseShop.getProducts()[i]->print();
				cout << endl;
			}
		}
		break;
	}
	}

	//print shopping cart
	KoseBoseShop.getUser()->printShoppingCart();
}



int main() 
{
	int pick_Category = 0;
	double lowerBoundPrice = 0.0, upperBoundPrice = 0.0;
	string searchByText = "";
	int itemVariable; //add or remove product or go to main menu

AUTH:
	//startup
	KoseBoseShop.auth();
	
PICK:
	printMainMenu();

	//pick category
	cout << "\n--------------------------------------------------------\n";
	cout << "Please pick category or enter 0 to to buy the items from your cart: ";
	pick_Category = KoseBoseShop.menuInputValidation(pick_Category, 0, 8);

	if (pick_Category == 5)
	{
		cout << "Enter lower and upper price values: ";
		priceRangeInputValidation(lowerBoundPrice, upperBoundPrice, 0.0, numeric_limits<double>::max());
	}

	if (pick_Category == 6)
	{
		cout << "Enter keyword: ";
		cin >> searchByText;
	}

	if (pick_Category == 7)
	{
		KoseBoseShop.createProduct();
		goto PICK;
	}

	if (pick_Category == 8) 
	{
		while (KoseBoseShop.getUser()->getShoppingCart().size() > 0)
		{
			KoseBoseShop.removeFromCart(KoseBoseShop.getUser()->getShoppingCart()[0]->getID());
		}
		delete KoseBoseShop.getUser();
		cout << "Logging out...\n";
		Sleep(2000);
		system("CLS");
		KoseBoseShop.setUser(new account);
		goto AUTH;
	}

	if (pick_Category == 0)
	{
		if(KoseBoseShop.getUser()->buy()) KoseBoseShop.updateDataToFile();
		Sleep(2000);
		goto PICK;

	}
	cout << endl;

	printCategory(pick_Category, lowerBoundPrice, upperBoundPrice, searchByText);

	do
	{
		cout << "\n--------------------------------------------------------\n";
		cout << "Enter the ID of the product you wish to add to the shopping cart,\nthe ID with - in front of it in order to remove from cart\nor 0 to go to main menu: ";
		cin >> itemVariable;
		system("CLS");

		if (itemVariable > 0) KoseBoseShop.addToCart(itemVariable);
		else if (itemVariable < 0) KoseBoseShop.removeFromCart(itemVariable * (-1));

		printCategory(pick_Category, lowerBoundPrice, upperBoundPrice, searchByText);
	} while (itemVariable != 0);

	if (itemVariable == 0) goto PICK;

	return 0;
}