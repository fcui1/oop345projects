#ifndef SICT_PRODUCT_H
#define SICT_PRODUCT_H
#include <fstream>
#include <iostream> 
namespace sict {
	class Product {


	       public:

		virtual std::fstream& store(std::fstream& file, bool addNewLine) const=0;
		virtual std::fstream& load(std::fstream& file)=0;
		virtual std::ostream& write(std::ostream& os, bool linear) const=0;
		virtual std::istream& read(std::istream& is)=0;
		virtual bool operator==(const char*) const=0;
		virtual double total_cost() const=0;
		virtual const char* name() const=0;
		virtual void quantity(int)=0;
		virtual int qtyNeeded() const=0;
		virtual int quantity() const=0;
		virtual int operator+=(int)=0;
		virtual bool operator>(const Product&) const=0;
		
	};
	std::ostream& operator<<(std::ostream& ostr, const Product& p);
	std::istream& operator >> (std::istream&is, Product& p);
	double operator+=(double&, const Product&);
	Product* CreateProduct();
}
#endif
