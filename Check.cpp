#include "Check.h"
#include <iostream>
#include <fstream>

Check::Check() {
	amount = 0;
	date = "null";
	id = 0;
}
Check::Check(double a, char* date, int id) {
	this->amount = a;
	this->date = date;
	this->id = id;
}

double Check::getAmount() {
	return amount;
}


void Check::setAmount(double a) {
	this->amount = a;
}

string Check::getDate() {
	return date;
}
void Check::setDate(char* dt) {
	this->date = dt;
}

void Check::setId(int id) {
	this->id = id;
}

int Check::getId() {
	return this->id;
}