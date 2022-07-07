#include "Account.h"

Account::Account() {

	this->check = {};
	taxRate = 0;
	numOfChecks = 0;

}
Account::Account(double t) {
	numOfChecks = 0;
	taxRate = t;
}

int Account::getNumOfChecks() {
	return check.size();
}

void Account::listAll() {
	int count = 0;

	cout << setfill('-') << setw(64) << " " << setfill(' ') << endl;
	cout << left << setw(20) << "Check ID" 
		 << left << setw(20) << "Check Amount" 
		 << left << setw(20) << "Check Date of Entry" << endl;
	cout << setfill('-') << setw(64) << " " << setfill(' ') << endl;

	while (count < check.size()) {
		cout << setw(20) << check.at(count)->getId()
			 << setw(20) << check.at(count)->getAmount() 
			 << setw(20) << check.at(count)->getDate() << endl;
		count++;
	}
}
void Account::addCheck(Check* c) {
	check.push_back(c);
	numOfChecks++;
	cout << "\nCheck added successfully...\n" << endl;
}
void Account::removeCheck(int id) {
	for (int i = 0; i < check.size(); i++) {
		if (check.at(i)->getId() == id) {
			check.erase(check.begin()+i);
		}
	}
	for (int i = 0; i < check.size(); i++) {
		check.at(i)->setId(i + 1);
	}
}
void Account::clearAllChecks() {
	check.clear();
}

void Account::editCheckAmount(int id, double amount) {
	if (id > check.size() || id < 1) {
		return;
	}
	this->check.at(id - 1)->setAmount(amount);
}

void Account::setTaxRate(double t) {

	this->taxRate = t;
}

double Account::getTaxRate() {
	return this->taxRate;
}

double Account::getTaxesOwed() {
	double sum = 0;

	for (int i = 0; i < check.size(); i++) {
		sum += check.at(i)->getAmount();
	}

	return sum * (getTaxRate() / 100);
}

double Account::getTotalIncome() {
	double total = 0;
	for (int i = 0; i < check.size(); i++) {
		total += check.at(i)->getAmount();
	}
	return total;
}

		/*else if (check.at(i)->getId() > id) {
		check.at(i)->setId((check.at(i)->getId()) - 1);
		}
		if (check.size() == 1) {
			check.at(0)->setId(1);
			return;
		}
		if (check.size() == 0) {
			return;
		}*/