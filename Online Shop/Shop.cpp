#include "Shop.h"
#include <fstream>
#include <iostream>
#include <windows.h>

#undef max

using namespace std;

shop::shop()
{
	number_Stocks = getFileLines();
	user = new account;
	fillStocksArr();

}

shop::shop(const shop& obj)
{
	number_Stocks = obj.number_Stocks;
	user = new account;
	user->setIsAdmin(obj.getUser()->getIsAdmin());
	user->setPassword(obj.getUser()->getPassword());
	user->setUsername(obj.getUser()->getUsername());
	user->setShoppingCart(obj.getUser()->getShoppingCart());
	for (int i = 0;i < number_Stocks;i++)
	{
		products[i] = obj.products[i];
	}
}

shop::~shop()
{
	delete user;
}

int shop::getFileLines() const
{
	int fileLines = 0;
	string tempRead;
	ifstream inFile;

	inFile.open("stocks.txt", ios::in);
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			getline(inFile, tempRead);
			fileLines++;
		}
	}
	inFile.close();

	fileLines--;

	return fileLines;
}

int shop::getNumberStocks() const
{
	return number_Stocks;
}

vector<stock*> shop::getProducts()
{
	return products;
}

account* shop::getUser() const
{
	return user;
}

void shop::setUser(account*obj)
{
	user = obj;
}

shop& shop::operator=(const shop& obj)
{
	if (this != &obj)
	{
		delete this->user;
		number_Stocks = obj.number_Stocks;
		user = new account;
		user->setIsAdmin(obj.getUser()->getIsAdmin());
		user->setPassword(obj.getUser()->getPassword());
		user->setUsername(obj.getUser()->getUsername());
		user->setShoppingCart(obj.getUser()->getShoppingCart());
		for (int i = 0;i < number_Stocks;i++)
		{
			products[i] = obj.products[i];
		}
	}
	return *this;
}

void shop::auth()
{
START:
	cout << "Welcome to KoseBose Online Shop!";
	cout << "\n--------------------------------------------------------\n";
	cout << "\n1) Register\n";
	cout << "2) Login\n";
	cout << "\n--------------------------------------------------------\n";

	//variable for menu
	int logreg = 0;
	logreg = menuInputValidation(logreg, 1, 2);

	//file
	fstream authList;

	//register
	if (logreg == 1)
	{
		string username;
		string password;
		bool isAdmin = false;

		cout << "Enter username: ";
		cin >> username;

		string read_Username;
		string read_Password;

		bool registered = false;

		//open file for reading, check if username is already registered
		authList.open("auth.txt", ios::in);
		if (authList.is_open())
		{
			while (!authList.eof())
			{
				authList >> read_Username >> read_Password;
				if (username==read_Username)
				{
					registered = true;
					break;
				}
			}

			if (registered)
			{
				cout << "User already registered!";
				Sleep(2000);
				system("CLS");
				authList.close();
				goto START;

			}
		}
		//else closes the file and opens it for writing and stores the data for the new user
		authList.close();
		authList.open("auth.txt", ios::app);
		authList << username << ' ';

		cout << "Enter password: ";
		cin >> password;

		authList << password << ' ' << isAdmin << endl;
		authList.close();
		cout << "Successfully registered!\n";
		cout << "\n--------------------------------------------------------\n";

		user->setUsername(username);
		user->setPassword(password);
		user->setIsAdmin(isAdmin);
		goto LOGIN;
	}

	//login new
	if (logreg == 2)
	{
	LOGIN:
		//input variables
		string attempt_Username;
		string attempt_Password;

		//stored variables in database
		string read_Username;
		string read_Password;
		bool read_IsAdmin;

		//check if correct
		bool correct_Username = false;

		//open file for reading
		authList.open("auth.txt", ios::in);

		//check if entered username exists in database
		cout << "\nLogin:\n";
		cout << "Enter username: ";
		cin >> attempt_Username;
		if (authList.is_open())
		{
			while (!authList.eof())
			{
				read_Username.clear();
				read_Password.clear();
				authList >> read_Username >> read_Password;
				authList>> read_IsAdmin;
				correct_Username = false;

				//check if correct username
				if (read_Username==attempt_Username)
				{
					correct_Username = true;
					cout << "Enter password: ";
					cin >> attempt_Password;

					//check if correct passowrd
					if (read_Password==attempt_Password)
					{
						cout << "\nSuccessfully logged in!\n\n";
						user->setUsername(attempt_Username);
						user->setPassword(attempt_Password);
						user->setIsAdmin(read_IsAdmin);
						cout << "\n--------------------------------------------------------\n";
						authList.close();
						break;
					}
					else
					{
						cout << "Incorrect password!\n";
						authList.close();
						Sleep(2000);
						goto LOGIN;
					}
				}
			}
			//if not correct username
			if (!correct_Username)
			{
				cout << "Incorrect username!\n";
				authList.close();
				Sleep(2000);
				goto LOGIN;
			}
		}
	}
}

void shop::fillStocksArr()
{
	ifstream stock_fill;
	stock_fill.open("stocks.txt", ios::in);

	//temp variables
	string read_Name, read_Description;
	int read_Amount, read_Category_ID, read_ID, read_AmountInCart, inherit_Variable;
	double read_Price;

	//fill array
	for (int i = 0;i < number_Stocks;i++)
	{
		if (stock_fill.is_open())
		{
			//read from file and fill data into object
			stock_fill >> read_Category_ID >> read_Name >> read_ID >> read_Amount >> read_AmountInCart >> read_Price>>inherit_Variable;
			getline(stock_fill, read_Description);

			switch (read_Category_ID)
			{
				case 1:
				{
					stockClothes* newClothes=new stockClothes;
					newClothes->setProduct(read_Name, read_Description, read_ID, read_Amount, read_AmountInCart, read_Price, inherit_Variable);
					products.push_back(newClothes);
					break;
				}
				case 2:
				{
					stockFood* newFood=new stockFood;
					newFood->setProduct(read_Name, read_Description, read_ID, read_Amount, read_AmountInCart, read_Price, inherit_Variable);
					products.push_back(newFood);
					break;
				}
				case 3:
				{
					stockTech* newTech=new stockTech;
					newTech->setProduct(read_Name, read_Description, read_ID, read_Amount, read_AmountInCart, read_Price, inherit_Variable);
					products.push_back(newTech);
					break;
				}
			default:
				break;
			}

			read_Name.clear();
			read_Category_ID = -1;
			read_ID = 0;
			read_Amount = -1;
			read_AmountInCart = -1;
			read_Price = -1.0;
			read_Description.clear();
			inherit_Variable = -1;
		}
	}
	stock_fill.close();
}

int shop::menuInputValidation(int input, int lowerBound, int upperBound)
{
	while (true)
	{
		cin >> input;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input.\n";
			continue;
		}
		if (input >= lowerBound && input <= upperBound) break;
		cout << "Invalid input.\n";
	}
	return input;
}

void shop::addToCart(int addByID)
{
	if (addByID == 0) return;

	int addToCart = -1; //the index of the element in the array of products

	//find index of product in array by comparing with ID
	for (int i = 0;i < number_Stocks;i++)
	{
		if (addByID == products[i]->getID())
		{
			addToCart = i;
			break;
		}
	}
	if (addToCart == -1)
	{
		cout << "There is no item with that ID.\n";
		Sleep(2000);
		return;
	}
	bool isInCart = false;

	//if size>0
	if (user->getShoppingCart().size()>0)
	{
		//if product already in cart
		for (int i = 0;i < user->getShoppingCart().size();i++)
		{
			if (user->getShoppingCart()[i]->getID() == products[addToCart]->getID())
			{
				user->getShoppingCart()[i]->setAmountInCart(user->getShoppingCart()[i]->getAmountInCart() + 1);
				products[addToCart]->setAmount(products[addToCart]->getAmount() - 1);
				isInCart = true;
				break;
			}
		}
		if (isInCart) return;

		//add new product
		user->getShoppingCart().push_back(products[addToCart]);
		user->getShoppingCart()[user->getShoppingCart().size()-1]->setAmountInCart(1);
		products[addToCart]->setAmount(products[addToCart]->getAmount() - 1);
	}
	else
	{
		//lower the amount of the product
		products[addToCart]->setAmount(products[addToCart]->getAmount() - 1);

		//add new product
		user->getShoppingCart().push_back(products[addToCart]);
		user->getShoppingCart()[user->getShoppingCart().size()-1]->setAmountInCart(1);
		
	}
}

void shop::removeFromCart(int removeByID)
{
	int removeFromCart = -1; //index in array of item to be removed

	//find the index in the array of shopping cart of the item to be removed
	for (int i = 0;i < user->getShoppingCart().size();i++)
	{
		if (removeByID == user->getShoppingCart()[i]->getID())
		{
			removeFromCart = i;
			break;
		}
	}
	if (removeFromCart == -1)
	{
		cout << "There is no item in cart with that ID.\n";
		Sleep(2000);
		return;
	}

	//if there is only 1 item in cart with amount == 1
	if (user->getShoppingCart().size() == 1 && user->getShoppingCart()[0]->getAmountInCart() == 1)
	{
		//find the index of the element in the array of stocks and increase its amount by 1
		for (int i = 0;i < number_Stocks;i++)
		{
			if (user->getShoppingCart()[0]->getID() == products[i]->getID())
			{
				products[i]->setAmount(products[i]->getAmount() + 1);
				break;
			}
		}

		user->getShoppingCart().clear();
		return;
	}

	//if amount in cart is > 1 then lower it
	if (user->getShoppingCart()[removeFromCart]->getAmountInCart() > 1)
	{
		user->getShoppingCart()[removeFromCart]->setAmountInCart(user->getShoppingCart()[removeFromCart]->getAmountInCart() - 1);

		//find the index of the element in the array of stocks and increase its amount by 1
		for (int i = 0;i < number_Stocks;i++)
		{
			if (user->getShoppingCart()[removeFromCart]->getID() == products[i]->getID())
			{
				products[i]->setAmount(products[i]->getAmount() + 1);
				break;
			}
		}

		return;
	}
	else if (user->getShoppingCart()[removeFromCart]->getAmountInCart() == 1) //(amount==1) make new array with size -=1 and copy everything except the item to be removed
	{
		//find the index of the element in the array of stocks and increase its amount by 1
		for (int i = 0;i < number_Stocks;i++)
		{
			if (user->getShoppingCart()[removeFromCart]->getID() == products[i]->getID())
			{
				products[i]->setAmount(products[i]->getAmount() + 1);
				break;
			}
		}

		//remove product from shopping cart
		user->getShoppingCart().erase(user->getShoppingCart().begin()+removeFromCart);
	}
}

void shop::createProduct()
{
	//if user not admin - exit
	if (!user->getIsAdmin())
	{
		cout << "Restricted Access!\n";
		Sleep(2000);
		return;
	}

	system("CLS");
	cout << "Now creating a new product...\n\n";

	//temp variables for input
	string name, category, description;
	int category_ID;
	int ID;
	int amount;
	int inheritVariable;
	double price;

	//input variables
	cout << "Input name: ";
	cin >> name;
	cout << "Input category ID => 1=Clothes, 2=Food, 3=Tech: ";
	cin >> category_ID;
	cout << "Input ID of product: ";
	cin >> ID;
	cout << "Input amount: ";
	cin >> amount;
	cout << "Input price: ";
	cin >> price;

	//create new stock and push it to array with products
	switch (category_ID)
	{
	case 1:
	{
		cout << "Input size: ";
		cin >> inheritVariable;
		cout << "Input description: ";
		cin.ignore();
		getline(cin, description);
		stockClothes newClothes;
		newClothes.setProduct(name, description, ID, amount, 0, price, inheritVariable);
		products.push_back(&newClothes);
		break;
	}
	case 2:
	{
		cout << "Input portions: ";
		cin >> inheritVariable;
		cout << "Input description: ";
		cin.ignore();
		getline(cin, description);
		stockFood newFood;
		newFood.setProduct(name, description, ID, amount, 0, price, inheritVariable);
		products.push_back(&newFood);
		break;
	}
	case 3:
	{
		cout << "Input warranty: ";
		cin >> inheritVariable;
		cout << "Input description: ";
		cin.ignore();
		getline(cin, description);
		stockTech newTech;
		newTech.setProduct(name, description, ID, amount, 0, price, inheritVariable);
		products.push_back(&newTech);
		break;
	}
	default:
		break;
	}

	//increase size
	number_Stocks++;

	//add product to database
	ofstream addProduct;
	addProduct.open("stocks.txt", ios::app);
	addProduct <<category_ID<<' '<< name << ' ' << ID << ' ' << amount << ' ' << 0 << ' ' << price << ' ' <<inheritVariable<<' '<< description << endl;
	addProduct.close();

	products.clear();
	fillStocksArr();
}

void shop::updateDataToFile()
{
	ofstream updateData;
	updateData.open("stocks.txt", ios::out | ios::trunc);
	for (int i = 0;i < getNumberStocks();i++)
	{
		updateData <<getProducts()[i]->getCategory_ID()<< ' ' << getProducts()[i]->getName() <<  ' '
			<< getProducts()[i]->getID() << ' '
			<< getProducts()[i]->getAmount() << ' ' << getProducts()[i]->getAmountInCart() << ' '
			<< getProducts()[i]->getPrice() << ' ' <<getProducts()[i]->getExtraData()<< ' '
			<< getProducts()[i]->getDescription() << endl;
	}
	updateData.close();
}