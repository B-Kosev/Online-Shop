#pragma once
#pragma warning(disable:4996)
#include <string>
#include <vector>

using namespace std;

class stock 
{
	string name;
	string category;
	string description;
	int category_ID;
	int ID;
	int amount;
	int amountInCart;
	double price;
public:
	//constructors
	stock();
	stock(string, string, int, int, int, int, double, string);

	//getters
	string getName() const;
	string getCategory() const;
	string getDescription() const;
	int getCategory_ID() const;
	int getID() const;
	int getAmount() const;
	int getAmountInCart() const;
	double getPrice() const;
	virtual int getExtraData() const = 0; //abstract class

	//setters
	void setName(string);
	void setCategory(string);
	void setCategory_ID(int);
	void setID(int);
	void setAmount(int);
	void setAmountInCart(int);
	void setPrice(double);
	void setDescription(string);
	virtual void setProduct(string, string, string, int, int, int, int, double);

	//other
	virtual void print() const;
	virtual void printForCart() const;
};



class stockTech : public stock
{
	int warranty; //in months
public:
	stockTech() : warranty(0) {}
	stockTech(string name, int ID, int amount, int amountInCart, double price, string description, int warranty) :
		stock(name, "Tech", 3, ID, amount, amountInCart, price, description), warranty(warranty) {}

	void setWarranty(int warranty);
	void setProduct(string name, string description, int ID, int amount, int amountInCart, double price, int warranty);
	int getExtraData() const;

	void print() const;
	void printForCart() const;
};


class stockClothes : public stock
{
	int size;
public:
	stockClothes() : size(0) {}
	stockClothes(string name, int ID, int amount, int amountInCart, double price, string description, int size) :
		stock(name, "Clothes", 1, ID, amount, amountInCart, price, description), size(size) {}

	void setSize(int size);
	void setProduct(string name, string description, int ID, int amount, int amountInCart, double price, int size);
	int getExtraData() const;

	void print() const;
	void printForCart() const;
};



class stockFood : public stock
{
	int portions;
public:
	stockFood() : portions(0) {}
	stockFood(string name, int ID, int amount, int amountInCart, double price, string description, int portions) :
		stock(name, "Food", 2, ID, amount, amountInCart, price, description), portions(portions) {}

	void setPortions(int portions);
	void setProduct(string name, string description, int ID, int amount, int amountInCart, double price, int portions);
	int getExtraData() const;

	void print() const;
	void printForCart() const;
};