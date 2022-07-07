#include "Account.h"
#include "Check.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include <chrono>
#include <ctime>
#include <limits>

#pragma warning(disable : 4996)

using namespace std;

void intro();
int mainMenu(Account&);
void addCheck(Account&);
void editCheck(Account&);
void load(Account&);
void save(Account&);

int main() {

	Account account;
	load(account);
	intro();

	//repeating switch case for menu navigation
	int choice = 0;
	do {
		choice = mainMenu(account);
		switch (choice) {

		case 1: //add check and save
			addCheck(account);
			save(account);
			break;

		case 2: //edit or remove check and save
			editCheck(account);
			save(account);
			break;

		case 3: //lists all checks
			account.listAll();
			break;

		case 4: //clears all checks after asking a second time. 
			char choice;
			cout << "\nAre you sure that you wish to clear all checks (Y/N)? ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y') {
				account.clearAllChecks();
				break;
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
			}
			save(account);
			break;

		case 5: //changes the tax rate
			double tax;
			cout << "\nPlease enter your desired tax rate (ie. 10 for 10%): ";
			cin >> tax;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nInvalid input." << endl;
				cout << "Please enter a numerical value excluding the percentage sign: ";
				cin >> tax;
			}
			account.setTaxRate(tax);
			save(account);
			break;

		case 6: //exits the program
			save(account);
			cout << "\nSaving information..." << endl;
			cout << "\nThanks for using Tax Tracker." << endl;
			break;
		}
	} while (choice != 6);

	return 0;
}


void intro() {
	//intro message
	cout << "Welcome to Tax Tracker. \n\nTax Tracker is a tool to help you "
		<< "keep track of your total income and the taxes owed on your income." << endl;
	cout << "\nAll information is stored locally.\n" << endl;
}

// menu for making a selection.
int mainMenu(Account& account) {
	int choice;

	cout << setfill('-') << setw(64) << " " << setfill(' ') << endl;
	cout << fixed << setprecision(2) << left
		<< "Total Income: $" << setw(20) << account.getTotalIncome()
		<< "Taxes Owed: $" << account.getTaxesOwed() << endl;
	cout << setfill('-') << setw(64) << " " << setfill(' ') << endl;
	cout << "\nPlease make a choice from the following menu: " << endl;
	cout << "\n1. Add entry\n"
		<< "2. Edit entry\n"
		<< "3. View entries\n"
		<< "4. Clear all entries\n"
		<< "5. Change tax rate\n"
		<< "6. Exit\n" << endl;
	cout << "Selection: ";
	cin >> choice;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid input." << endl;
		cout << "Please enter a numerical value between 1 and 5: ";
		cin >> choice;
	}
	return choice;
}

//adds a Check to Account along with a timestamp
void addCheck(Account& account) {
	double amount;

	cout << "\nPlease enter the amount of the check: ";
	cin >> amount;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid input." << endl;
		cout << "Please enter a numerical value: ";
		cin >> amount;
	}

	std::time_t now = time(0);
	char* dt = ctime(&now);

	account.addCheck(new Check(amount, dt, account.getNumOfChecks() + 1));
}

//edit Check ... still needs date editing and exception handling in case of editing a non existing entry
void editCheck(Account& account) {
	int entryChoice;
	int editChoice;
	double amount;

	account.listAll();

	cout << "\nPlease enter the ID number of the entry that you would like to edit: ";
	cin >> entryChoice;

	cout << "\nWhat would you like to do?" << endl;
	cout << "\n1. Edit the amount" << endl;
	cout << "\n2. Remove the entry" << endl;
	cout << "\n3. Back to main menu" << endl;
	cout << "\nSelection: ";
	cin >> editChoice;

	if (editChoice == 1) {
		cout << "\nNew amount: ";
		cin >> amount;
		account.editCheckAmount(entryChoice, amount);
	}
	else if (editChoice == 2) {
		account.removeCheck(entryChoice);
	}
}

//boost instream (load data)
void load(Account& account) {
	ifstream in("data.xml");
	try {
		in.open("data.xml");
		boost::archive::binary_iarchive input_archive(in);
		input_archive& BOOST_SERIALIZATION_NVP(account);
		in.close();
	}
	catch (ifstream::failure e) {
		cout << "Creating new account...\n" << endl;
	}
	catch (boost::archive::archive_exception e) {
		cout << "Creating new account...\n" << endl;

	}

}

//boost outstream (save data)
void save(Account& account) {
	ofstream out("\data\data.xml");
	boost::archive::binary_oarchive output_archive(out);
	output_archive& BOOST_SERIALIZATION_NVP(account);
}
//@author Adam Botens