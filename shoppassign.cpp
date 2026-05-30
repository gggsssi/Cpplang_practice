#include <iostream>
using namespace std;

class ShopItem {
	string name;
	int price;
	static int itemCount;
	
	ShopItem () {
		name = "Item";
		price = 0;
		itemCount++;
		cout << "Item " << name << " created" << endl;
	}
	
	ShopItem (string n, int p) {
		name = n;
		price = p;
		itemCount++;
		cout << "Item " << name << " created" << endl;
	}
	
	void show () {
		cout << "Item: " << name << endl;
		cout << "Price: " << price << endl;
	}
	
	~ShopItem () {
		cout << "Item " << name << " removed" << endl;
		itemCount--;
	}
};

int ShopItem::itemCount;

int main () {
	
}
