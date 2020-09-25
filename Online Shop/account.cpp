#include "account.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

account::account()
{
	isAdmin = false;
}

account::account(string username, string password)
{
	this->username = username;
	this->password = password;
	isAdmin = false;
}

string account::getUsername() const
{
	return username;
}

string account::getPassword() const
{
	return password;
}

bool account::getIsAdmin() const
{
	return isAdmin;
}

vector<stock*>& account::getShoppingCart()
{
	return shoppingCart;
}

void account::setUsername(string username)
{
	this->username = username;
}

void account::setPassword(string password)
{
	this->password = password;
}

void account::setIsAdmin(bool isAdmin)
{
	this->isAdmin = isAdmin;
}

void account::setShoppingCart(vector<stock*> shoppingCart)
{
	this->shoppingCart = shoppingCart;
}

void account::printUser() const
{
	cout << "Username: " << username << endl << "Password: " << password << endl<<"Is Admin? " <<isAdmin<<endl;
}

void account::printShoppingCart() const
{
	double priceSum = 0.0;
	cout << "\n--------------------------------------------------------\n";
	cout << "\nShopping cart: \n\n";
	if (shoppingCart.size()==0)
	{
		cout << "Empty.\n";
	}
	else
	{
		for (int i = 0;i < shoppingCart.size();i++)
		{
			shoppingCart[i]->printForCart();
			cout << endl;
			priceSum += shoppingCart[i]->getAmountInCart() * shoppingCart[i]->getPrice();
		}
	}
	cout << "\nTotal: " << priceSum << endl;
}

bool account::buy() 
{
	//if there are no items in cart
	if (shoppingCart.size() ==0)
	{
		cout << "You don't have any items in the cart.\n";
		return false;
	}

	//restrict access to admin only
	if (!isAdmin)
	{
		cout << "You don't have access to this feature yet. Only admin can buy items.\n";
		return false;
	}
	
	//remove all items from the cart
	shoppingCart.clear();

	cout << "Purchase completed!\n";

	return true;
}