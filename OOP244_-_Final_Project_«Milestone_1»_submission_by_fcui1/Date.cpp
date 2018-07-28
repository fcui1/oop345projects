// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include "Date.h"

namespace sict {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}


	void Date::errCode(int errorCode) {
		errcode_read = errorCode;
}


	Date::Date() {
		m_year = 0;
		m_month = 0;
		m_day = 0;
		errcode_read = NO_ERROR;
		value_comparator = 0;
	}


	Date::Date(int year, int month, int day) {
		if ((year >= min_year &&year <= max_year) && (month < 13 && month >= 1) && (day>0&&day<=mdays(month,year))) {
			m_year = year;
			m_month = month;
			m_day = day;
			value_comparator = this->m_year * 372 + month * 13 + day;
			errcode_read = NO_ERROR;

		}
		else {
			*this = Date();
		}


	}

	bool Date::operator==(const Date& rhs) const {

       if(value_comparator ==0 ||rhs.value_comparator ==0){
		   return false;
	   }else{
           	return this->value_comparator == rhs.value_comparator;

	   }
	}
	bool Date::operator!=(const Date& rhs) const {
		if(value_comparator ==0 ||rhs.value_comparator ==0){
		   return false;
	   }else{
           	return this->value_comparator != rhs.value_comparator;
     	}
	}

	bool Date::operator<(const Date& rhs) const {
		if(value_comparator ==0 ||rhs.value_comparator ==0){
		   return false;
	   }else{
           	return this->value_comparator < rhs.value_comparator;

	  }
	}

	bool Date::operator>(const Date& rhs) const {
		if(value_comparator ==0 ||rhs.value_comparator ==0){
		   return false;
	   }else{
           	return this->value_comparator > rhs.value_comparator;

	   }
	}

	bool Date:: operator<= (const Date& rhs) const {
		if(value_comparator ==0 ||rhs.value_comparator ==0){
		   return false;
	   }else{
           	return this->value_comparator <= rhs.value_comparator;

	   }
	}
	bool Date::operator>=(const Date& rhs) const {

		if(value_comparator ==0 ||rhs.value_comparator ==0){
		   return false;
	   }else{
           	return this->value_comparator >= rhs.value_comparator;
	   }
	}

	int Date::errCode() const {

		return errcode_read;
	}



	bool Date::bad() const {
		if (errCode() != NO_ERROR) {

			return true;
		}
		else {
			return false;
		}
	}
	std::istream&Date:: read(std::istream& istr) {

		istr >> m_year;

		if (!istr.fail()){
			istr.ignore();
			istr >> m_month;

			if (!istr.fail()){
				istr.ignore();
				istr >> m_day;

				if (!istr.fail()){

					if (m_month < 1 || m_month>12){
						errcode_read = MON_ERROR;
						m_year = 0;
						m_day = 0;
						m_month = 0;

					}
					else if (m_day<0 || m_day>mdays(m_month, m_year)){
						errcode_read = DAY_ERROR;
						m_year = 0;
						m_day = 0;
						m_month = 0;
					}
					else if (m_year > max_year || m_year < min_year){
						errcode_read = YEAR_ERROR;
						m_year = 0;
						m_day = 0;
						m_month = 0;
					}
					else  {
						errCode(NO_ERROR);
					}
				}
				else{
					errCode(CIN_FAILED);
				}
			}
			else{
				errCode(CIN_FAILED);
			}
		}
		else {

			errCode(CIN_FAILED);
		}
			
		return istr;
	}

	std::ostream&Date:: write(std::ostream& ostr) const{
		ostr << m_year << "/";
		ostr.width(2);
		ostr.fill('0');
		ostr << m_month << "/";
		ostr.width(2);
		ostr << m_day;
		return ostr;
	}

	std::istream& operator >> (std::istream& istr, Date& date) {
       
		date.read(istr);
		return istr;

	}
	std::ostream& operator << (std::ostream& ostr, const Date& date) {
		date.write(ostr);
		return ostr;
	}

}

