#ifndef SICT_PERISHABLE_H
#define SICT_PERISHABLE_H
#include "Date.h"
#include "Product.h"
#include "NonPerishable.h"
namespace sict {
	class Perishable :public NonPerishable
	{
	private:
		Date expire_date;
	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;
	};
	Product* CreatePerishable();
}



#endif
