#ifndef Check_h
#define Check_h

#include <string>
#include <vector>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>


using namespace std;

class Check
{
private:

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& archive, const unsigned int version) {
		archive& BOOST_SERIALIZATION_NVP(amount);
		archive& BOOST_SERIALIZATION_NVP(date);
		archive& BOOST_SERIALIZATION_NVP(id);
	}

	double amount;
	string date;
	int id;

public:

	Check();
	Check(double, char*, int);

	double getAmount();
	void setAmount(double a);

	string getDate();
	void setDate(char*);

	void setId(int id);
	int getId();

};
#endif Check_h
