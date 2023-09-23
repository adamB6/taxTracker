#ifndef Account_h
#define Account_h

#include "Check.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>


using namespace std;

class Account
{
private:

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& archive, const unsigned int version)
	{
		archive& BOOST_SERIALIZATION_NVP(check);
		archive& BOOST_SERIALIZATION_NVP(taxRate);
		archive& BOOST_SERIALIZATION_NVP(numOfChecks);

	}
	vector<Check*> check;
	double taxRate;
	int numOfChecks;

public:

	Account();
	Account(double t);
	int getNumOfChecks();
	void listAll();
	void addCheck(Check*);
	void editCheckAmount(int, double);
	void removeCheck(int);
	void clearAllChecks();
	void setTaxRate(double);
	double getTaxRate();
	double getTaxesOwed();
	double getTotalIncome();

};
#endif Account_h
