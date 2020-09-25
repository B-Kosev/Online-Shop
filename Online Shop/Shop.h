#pragma once
#include "stock.h"
#include "account.h"
#include "Shop.h"
#include <string>
#include <vector>

using namespace std;

class shop
{
	int number_Stocks; //number of stocks in the file
	vector<stock*> products; //array with products
	account* user; //pointer to one user - not array - dynamic!!!
	
public:
	//constructors
	shop();
	shop(const shop& obj);
	~shop();
	
	//getters
	int getFileLines() const;
	int getNumberStocks() const;
	vector<stock*> getProducts();
	account* getUser() const;

	//setters
	void setUser(account*);

	//other
	shop& operator=(const shop& obj);
	void auth();
	void fillStocksArr();
	int menuInputValidation(int input, int lowerBound, int upperBound);
	void addToCart(int addByID);
	void removeFromCart(int removeByID);
	void createProduct();
	void updateDataToFile();
};