#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "NonPerishable.h"
#include "Product.h"
namespace sict {

	void NonPerishable::setEmpty() {

		m_sku[0] = '\0';
		m_unit[0] = '\0';
		t_type = '\0';
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
		//m_name = nullptr;
		if (sku[0] != '\0' &&name_product != nullptr) {
			strncpy(this->m_sku, sku, max_sku_length + 1);
			name(name_product);
			strncpy(this->m_unit, unit, max_unit + 1);
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

			if (other.m_name != nullptr) {
				delete[] m_name;
			t_type =other.t_type;
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
		file << t_type << ';';
		file << m_sku << ',';
		file << name() << ',';
		file << m_unit << ',';
		file << quantity_current << ',';
		file << quantity_need << ',';
		file << m_taxed << ',';
		file << price_before << ',';

		if (newLine) {
			file << "\n";
		}
		return file;
	}

	std::fstream & NonPerishable::load(std::fstream & file)
	{
		char SKU[2048];
		char NAME[2048];
		char tax_no[1];



		file.getline(SKU, 2048, ',');
		file.getline(NAME, 2048, ',');
		file.ignore();

		file.getline(tax_no, 2048, ',');
		file >> this->quantity_current;
		file.ignore();
		file >> this->quantity_need;
		file.ignore();

		strcpy(this->m_sku, SKU);
		name(NAME);

		return file;
	}


	std::ostream & NonPerishable::write(std::ostream & os, bool linear) const
	{
		if (linear) {

			os.width(max_sku_length);
			os << m_sku << "|";
			os.width(20);
			os << m_name << "|";
			os.width(7);
			os << price_before << "|";
			os.width(4);
			os << quantity_current << "|";
			os.width(10);
			os << m_unit << "|";
			os.width(4);
			os << quantity_need << "|";

		}
		else {

			os << "Sku:" << "\n";
			os << "Name:" << "\n";
			os << "Price:" << "\n";
			if (m_taxed) {
				os << "Price after tax: " << "\n";

			}
			else {

				os << "N/A" << "\n";
			}

			os << "Quantity On Hand:" << "\n";
			os << "Quantity Needed" << "\n";

		}

		return os;
	}

	std::istream & NonPerishable::read(std::istream & is)
	{
		is >> m_sku;
		is >> m_name;
		is >> m_unit;
		is >> m_taxed;
		is.setstate(std::ios::failbit);
		if (is.fail()) {
			error.message("Only (Y)es or (N)o are acceptable");
			return is;
		}
		is >> quantity_need;

		if (is.fail()) {
			error.message("Invalid Quantity Needed Entry");
			return is;
		}
		is >> quantity_current;

		if (is.fail()) {
			error.message("Invalid Quantity Entry");
			return is;

		}

		is >> price_before;

		if (is.fail()) {
			error.message("Invalid Price Entry");
			return is;

		}

		return is;
	}



	void NonPerishable::name(const char* n) {
		m_name = nullptr;
		if (n != nullptr) {
			m_name = new  char[strlen(n) + 1];
			strcpy(m_name, n);

		}


	}
	const char* NonPerishable::name() const {
		if (m_name == nullptr || m_name[0] == '\0') {

			return nullptr;
		}
		else {
			return this->m_name;

		}


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
	bool  NonPerishable::isEmpty() const {

		bool valid;

		if (this->m_name == nullptr&&m_sku[0]=='\0' && quantity_current == 0&&quantity_need==0&&price_before==0) {
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