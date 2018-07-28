#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring> 
#include <iomanip>
#include <fstream> 
#include "NonPerishable.h"
#include "Product.h"
using namespace std;

namespace sict {

	void NonPerishable::setEmpty() {

		m_sku[0] = '\0';
		m_unit[0] = '\0';
		//t_type = '\0';
		m_name = nullptr;
		quantity_current = 0;
		quantity_need = 0;
		price_before = 0.0;
		m_taxed = 1;
	}

	NonPerishable::NonPerishable(const char type) {

		t_type = type;
		setEmpty();
	}
	NonPerishable::~NonPerishable() {

		delete[]this->m_name;
		this->m_name = nullptr;

	}
	NonPerishable::NonPerishable(const char*sku, const char*name_product, const char*unit, int Quantity_current, bool Taxed, double Price, int Quantity_need) {

		if (sku != nullptr&&name_product != nullptr&&unit != nullptr) {

			strncpy(this->m_sku, sku, max_sku_length + 1);
			name(name_product);
			strcpy(this->m_unit, unit);
			this->quantity_current = Quantity_current;
			this->quantity_need = Quantity_need;
			this->price_before = Price;
			this->m_taxed = Taxed;
		}


	}
	NonPerishable::NonPerishable(const NonPerishable& other) {
		m_name = nullptr;
		*this = other;

	}
	NonPerishable& NonPerishable::operator=(const NonPerishable& other) {

		if (this != &other) {
			delete[] m_name;
			t_type = other.t_type;
			if (other.m_name != nullptr) {

				strncpy(m_sku, other.m_sku, max_sku_length + 1);
				name(other.m_name);
				strncpy(m_unit, other.m_unit, max_unit + 1);
				quantity_current = other.quantity_current;
				quantity_need = other.quantity_need;
				price_before = other.price_before;
				m_taxed = other.m_taxed;
			}
			else {

				setEmpty();
			}
		}
		return *this;
	}
	std::fstream & NonPerishable::store(std::fstream & file, bool newLine) const
	{
		file << t_type << ',' << m_sku << ',' << name() << ',' << price_before << ',' << taxed() << ',' << quantity_current << ',' << m_unit << ',' << quantity_need;

		if (newLine) {
			file << "\n";
		}
		return file;
	}

	std::fstream & NonPerishable::load(std::fstream & file)
	{
		NonPerishable temp('N');
		char name[50];

		file.getline(temp.m_sku, max_sku_length, ',');
		//	file >> temp.m_sku;

		file.getline(name, max_name_length, ',');
		temp.name(name);

		file >> temp.price_before;
		file.ignore(1, ',');

		file >> temp.m_taxed;
		file.ignore(1, ',');

		file >> temp.quantity_current;
		file.ignore(1, ',');

		file.getline(temp.m_unit, max_unit, ',');
		
		file >> temp.quantity_need;
		file.ignore(1, ',');

		*this = temp;

		return file;

	}

	std::ostream & NonPerishable::write(std::ostream & os, bool linear) const
	{
		// TODO: print the content only if the object is valid
		// isVald means the object is not empty is not in error
		// if the object is in error, print the error message


		if (!isClear()) {

			os << error.message();

		}
		else {

			if (linear) {

				os << std::left << std::setw(max_sku_length) << m_sku << "|";
				os << std::left << std::setw(20) << m_name << "|";
				os << std::right << std::setw(7) << std::fixed << setprecision(2) << cost() << "|";
				os << std::right << std::setw(4) << quantity_current << "|";
				os << std::left << std::setw(10) << m_unit << "|";
				os << std::right << ::setw(4) << quantity_need << "|";

			}
			else {
				os.setf(std::ios::fixed);
				os.precision(2);
				os << "Sku: " << m_sku << "\n";
				os << "Name: " << name() << "\n";
				os << "Price: " << price_before << "\n";
				if (this->m_taxed)
				{
					os << "Price after tax: " << cost() << std::endl;
				}
				else
				{
					os << "Price after tax:" << " N/A" << std::endl;
				}
				os << "Quantity On Hand: " << quantity_current << std::setprecision(2) << ' ' << m_unit<< "\n";
				os << "Quantity Needed: " << quantity_need ;

			}

		}


		return os;
	}


	std::istream & NonPerishable::read(std::istream & is)
	{
		this->error.clear();

		char temp_sku[max_sku_length + 1];
		char tempName[max_name_length + 1];
		char temp_unit[max_unit + 1];

		char tax_t;
		double t_price;
		int quantity_t;
		int quantity_n;
		std::cout << " Sku: ";
		is >> temp_sku;


		std::cout << " Name: ";
		is >> tempName;


		std::cout << " Unit: ";
		is >> temp_unit;



		if (!is.fail()) {
			cout << " Taxed? (y/n): ";
			is >> tax_t;
			if (tax_t == 'y' || tax_t == 'Y') {

				this->m_taxed = true;

			}
			else if ((tax_t == 'n' || tax_t == 'N')) {

				this->m_taxed = false;
			}
			else
			{
				error.message("Only (Y)es or (N)o are acceptable");
				is.setstate(ios::failbit);

			}
		}

		if (!is.fail()) {

			std::cout << " Price: ";
			is >> t_price;
			if (is.fail()) {
				error.message("Invalid Price Entry");
			}
		}

		if (!is.fail()) {
			std::cout << "Quantity On hand: ";
			is >> quantity_t;

			if (quantity_t <= 0) {
				error.message("Invalid Quantity Entry");
			}

		}

		if (!is.fail()) {
			std::cout << "Quantity Needed: ";
			is >> quantity_n;

			if (quantity_n <= 0) {

				error.message("Invalid Quantity Needed Entry");
			}
		}

		if (!is.fail()) {
			strcpy(m_sku, temp_sku);
			this->name(tempName);
			strcpy(m_unit, temp_unit);
			price_before = t_price;
			quantity_current = quantity_t;
			quantity_need = quantity_n;
		}

		return is;
	}


	void NonPerishable::name(const char* n) {

		if (n != nullptr) {
			m_name = new  char[strlen(n) + 1];
			strcpy(m_name, n);
		}

	}
	const char* NonPerishable::name() const {

		return this->m_name;
	}

	double NonPerishable::cost()const {
		double cost = price_before;

		if (m_taxed) {

			cost = price_before + price_before*tax;
		}
		return cost;
	}


	void NonPerishable::message(const char* error_message) {

		error.message(error_message);

	}
	bool NonPerishable::isClear() const {

		return error.isClear();

	}

	double NonPerishable::total_cost() const {
		double totalcost;
		if (m_taxed) {

			totalcost = cost()* quantity();
		}
		else {

			totalcost = quantity_current*price_before;
		}

		return  totalcost;

	}
	int NonPerishable::quantity() const {

		return quantity_current;

	}
	int  NonPerishable::qtyNeeded() const {


		return quantity_need;

	}
	void NonPerishable::quantity(int q_qunantity) {

		quantity_current = q_qunantity;


	}
	const char* NonPerishable::sku() const {
		return m_sku;
	}

	double NonPerishable::price() const {
		return price_before;
	}

	int NonPerishable::taxed() const {
		return m_taxed;
	}
	const char* NonPerishable::unit() const {

		return m_unit;
	}
	bool  NonPerishable::isEmpty() const {

		bool valid;

		if (this->m_name == nullptr) {

			valid = true;
		}
		else {
			valid = false;
		}
		return valid;
	}
	bool NonPerishable::operator==(const char* sku) const {
		bool valid;
		if (strcmp(m_sku, sku) == 0) {

			//string is identical to the sku of the current object; false otherwise.

			valid = true;

		}
		else {
			valid = false;
		}
		return valid;
	}

	bool  NonPerishable ::operator > (const char* sku) const {
		bool valid;
		if (strcmp(sku, this->m_sku) > 0) {

			valid = true;
		}
		else {
			valid = false;
		}
		return valid;
	}


	int NonPerishable ::operator+=(int unit) {
		if (unit > 0) {

			quantity_current += unit;

		}

		return quantity_current;
	}

	bool NonPerishable ::operator>(const Product& other) const {
		bool valid;
		if (strcmp(this->m_name, other.name()) > 0) {

			valid = true;
		}
		else {
			valid = false;
		}
		return valid;

	}
	std::ostream& operator<<(std::ostream& ostr, const Product& p) {


		p.write(ostr, true);
		return ostr;



	}
	std::istream& operator >> (std::istream& is, Product& p) {

		p.read(is);
		return is;


	}
	double operator+=(double & total, const Product & p)
	{
		total += p.total_cost();
		return total;
	}

	Product* CreateProduct() {

		Product*p = nullptr;
		p = new NonPerishable();
		return p;
	}
}
