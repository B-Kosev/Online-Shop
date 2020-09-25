#include "stock.h"
#include <cstring>
#include <iostream>

using namespace std;

stock::stock()
{
	category_ID = 0;
	ID = 0;
	amount = 0;
	amountInCart = 0;
	price = 0.0;
}

stock::stock(string name, string category,int category_ID,int ID, int amount, int amountInCart, double price, string description)
{
	this->name = name;
	this->category = category;

	this->category_ID = category_ID;
	this->ID = ID;
	this->amount = amount;
	this->amountInCart = amountInCart;
	this->price = price;

	this->description = description;
}

string stock::getName() const
{
	return name;
}

string stock::getCategory() const
{
	return category;
}

int stock::getCategory_ID() const
{
	return category_ID;
}

int stock::getID() const
{
	return ID;
}

int stock::getAmount() const
{
	return amount;
}

int stock::getAmountInCart() const
{
	return amountInCart;
}

double stock::getPrice() const
{
	return price;
}

string stock::getDescription() const
{
	return description;
}

void stock::setName(string name)
{
	this->name = name;
}

void stock::setCategory(string category)
{
	this->category = category;
}

void stock::setCategory_ID(int category_ID)
{
	this->category_ID = category_ID;
}

void stock::setID(int ID)
{
	this->ID = ID;
}

void stock::setAmount(int amount)
{
	this->amount = amount;
}

void stock::setAmountInCart(int amountInCart)
{
	this->amountInCart = amountInCart;
}

void stock::setPrice(double price)
{
	this->price = price;
}

void stock::setDescription(string description)
{
	this->description = description;
}

void stock::setProduct(string name, string category, string description, int categoryID, int ID, int amount, int amountInCart, double price)
{
	this->name = name;
	this->category = category;
	this->description = description;
	this->category_ID = categoryID;
	this->ID = ID;
	this->amount = amount;
	this->amountInCart = amountInCart;
	this->price = price;
}

void stock::print() const
{
	cout << "\nProduct ID: " << ID << endl << "Name: " << name << endl << "Category: " << category << endl << "Amount: " << amount << endl << "Price: $" << price << endl << "Description: " << description << endl;
}

void stock::printForCart() const
{
	cout <<"\nProduct ID: "<<ID<<endl<< "Name: " << name << endl << "Price: $" << price << endl << "Description: " << description << endl<<"Amount in cart: "<<amountInCart<<endl;
}



//stockTech:

void stockTech::setWarranty(int warranty)
{
	this->warranty = warranty;
}

void stockTech::setProduct(string name, string description, int ID, int amount, int amountInCart, double price,int warranty)
{
	stock::setProduct(name, "Tech", description, 3, ID, amount, amountInCart, price);
	this->warranty = warranty;
}

int stockTech::getExtraData() const
{
	return warranty;
}

void stockTech::print() const
{
	stock::print();
	cout << "Warranty: " << warranty << " monnths\n";
}

void stockTech::printForCart() const
{
	stock::printForCart();
	cout << "Warranty: " << warranty << " monnths\n";
}



//stockClothes:

void stockClothes::setSize(int size)
{
	this->size = size;
}

void stockClothes::setProduct(string name, string description, int ID, int amount, int amountInCart, double price, int size)
{
	stock::setProduct(name, "Clothes", description, 1, ID, amount, amountInCart, price);
	this->size = size;
}

int stockClothes::getExtraData() const
{
	return size;
}

void stockClothes::print() const
{
	stock::print();
	cout << "Size: " << size << endl;
}

void stockClothes::printForCart() const
{
	stock::printForCart();
	cout << "Size: " << size << endl;
}


//stockFood:

void stockFood::setPortions(int portions)
{
	this->portions = portions;
}

void stockFood::setProduct(string name, string description, int ID, int amount, int amountInCart, double price, int portions)
{
	stock::setProduct(name, "Food", description, 2, ID, amount, amountInCart, price);
	this->portions = portions;
}

int stockFood::getExtraData() const
{
	return portions;
}

void stockFood::print() const
{
	stock::print();
	cout << "Portions: " << portions << endl;
}

void stockFood::printForCart() const
{
	stock::printForCart();
	cout << "Portions: " << portions << endl;
}
