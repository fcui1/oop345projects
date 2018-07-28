#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Perishable.h"
#include "Product.h"

namespace sict {

	Perishable::Perishable():NonPerishable('P'){

		expire_date.setEmpty();
	}

	Product* CreatePerishable(){
		Product*product = nullptr;
		product = new Perishable();
		return product;
    }

	std::fstream & Perishable::store(std::fstream & file, bool newLine) const
	{
		NonPerishable::store(file, false);

		file << "," << expire_date;

		if (newLine == true) {
			file << '\n';
		}
		return file;
	}

	std::fstream & Perishable::load(std::fstream & file)
	{
		NonPerishable::load(file);
	
		file >> expire_date;

		return file;
	}

	std::ostream & Perishable::write(std::ostream & os, bool linear) const
	{
		NonPerishable::write(os, linear);
       if(this->name() != nullptr && this->isClear()){

			if (linear == false) {
               os << '\n' << "Expiry date: " << expire_date;
			
			}
			else {
				os << expire_date;
			}

	   }
		
		return os;
	}

	std::istream & Perishable::read(std::istream & is)
	{
		Date D;
		NonPerishable::read(is);
		if (!is.fail()) {
			std::cout << "Expiry date (YYYY/MM/DD): ";
			is >> D;

			if (D.errCode() == 1) {
				message("Invalid Date Entry");
				is.setstate(std::ios::failbit);
			}
			else if (D.errCode() == 2) {
				message("Invalid Year in Date Entry");
				is.setstate(std::ios::failbit);
			}
			else if (D.errCode() == 3) {
				message("Invalid Month in Date Entry");
				is.setstate(std::ios::failbit);
			}
			else if (D.errCode() == 4) {
				message("Invalid Day in Date Entry");
				is.setstate(std::ios::failbit);
			}
			else {
				expire_date = D;
			}
		}
		return is;
	}

	const Date & Perishable::expiry() const
	{
		return expire_date;
	}
}
