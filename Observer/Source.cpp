#include <iostream>
#include <vector>
using namespace std;

class Observer abstract
{
public:
	virtual void Update() abstract;
};

class Subject abstract
{
	vector<Observer*> observers;
public:
	void Attach(Observer* observer) {
		observers.push_back(observer);
	}
	void Detach(Observer* observer) {
		auto iter = find(observers.begin(), observers.end(), observer);
		if (iter != observers.end())
			observers.erase(iter);
	}
	void Notify() {
		for (Observer* o : observers)
		{
			o->Update();
		}
	}
};


class Shop : public Subject {
private:
	bool is_available_phone;
public:
	Shop(bool is) {
		is_available_phone = is;
	}
	void SetAvailable(bool is) {
		is_available_phone = is;
	}
	bool GetAvailable() {
		return is_available_phone;
	}
};

class Buyer : public Observer
{
	Shop* shop;
	string name;

public:
	Buyer(Shop* shop, string name) {
		this->shop = shop;
		this->name = name;
	};
	void Update() override {
		cout << name << " - phone available: " << shop->GetAvailable() << endl;
	}
	Shop* GetShop() {
		return this->shop;
	}
	void SetShop(Shop* shop) {
		this->shop = shop;
	}
};



int main()
{
	Shop* shop = new Shop(false);

	Observer* o1 = new Buyer(shop, "Observer #1");
	Observer* o2 = new Buyer(shop, "Observer #2");
	Observer* o3 = new Buyer(shop, "Observer #3");

	shop->Attach(o1);
	shop->Attach(o2);
	shop->Attach(o3);

	shop->Notify();

	shop->SetAvailable(true);

	shop->Notify();

	shop->Detach(o2);

	shop->Detach(o1);
	shop->Notify();

	delete shop;
	delete o1;
	delete o2;
	delete o3;

	system("pause");
	return 0;
}