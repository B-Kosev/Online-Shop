#pragma once
#pragma warning(disable:4996)
#include "stock.h"
#include <string>
#include <vector>

using namespace std;

class account 
{
	string username;
	string password;
	bool isAdmin;
	vector<stock*> shoppingCart; 
public:
	//constructors
	account();
	account(string, string);

	//getters
	string getUsername() const;
	string getPassword() const;
	bool getIsAdmin() const;
	vector<stock*>& getShoppingCart();

	//setters
	void setUsername(string);
	void setPassword(string);
	void setIsAdmin(bool);
	void setShoppingCart(vector<stock*>);

	//other
	void printUser() const;
	void printShoppingCart() const;
	bool buy(); //return true if a purchase is completed
	
};