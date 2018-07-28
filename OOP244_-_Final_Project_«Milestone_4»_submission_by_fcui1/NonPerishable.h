#ifndef SICT_NONPERISHABLE_H
#define SICT_NONPERISHABLE_H
#include "Product.h"
#include "ErrorMessage.h"

namespace sict {


	const int max_sku_length = 7;
	const int max_unit = 10;
	const char max_name_length = 75;
	const double tax = 0.13;

	class NonPerishable : public Product {
		char t_type;
		char m_sku[max_sku_length +1];
		char m_unit[max_unit+1];
		char*m_name;
		int quantity_current;
		int quantity_need;
		double price_before;
		bool m_taxed;
		ErrorMessage error;
	protected:
		void name(const char* name);
		const char*name() const;
		double cost()const;
		void message(const char*);
		bool isClear() const;

	public:
		void setEmpty();
		NonPerishable(const char type = '\0');
		NonPerishable(const char*sku, const char*name_product, const char*unit, int Quantity_current = 0, bool Taxed = true, double Price = 0, int Quantity_need = 0);
		NonPerishable(const NonPerishable& other);
		NonPerishable& operator=(const NonPerishable& other);
		~NonPerishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char* sku) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		int operator+=(int);
		bool operator>(const Product&) const;

	};
	std::ostream& operator<<(std::ostream& ostr, const Product& p);
	std::istream& operator >> (std::istream&is, Product& p);
	double operator+=(double&, const Product&);
	Product* CreateProduct();

}
#endif

