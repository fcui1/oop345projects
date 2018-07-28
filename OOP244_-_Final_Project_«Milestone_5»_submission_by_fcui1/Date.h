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
#ifndef SICT_DATE_H
#define SICT_DATE_H
#include <iostream>
namespace sict {
	const int max_year = 2030;
	const int min_year = 2000;
	const int CIN_FAILED = 1;
	const int YEAR_ERROR = 2;
	const int MON_ERROR = 3;
	const int DAY_ERROR = 4;
	const int NO_ERROR = 0;

  class Date {
	  int m_year;
	  int m_month;
	  int m_day;
	  int value_comparator;
	  int errcode_read;
     int mdays(int, int)const;
	 void errCode(int errorCode);
  public:
	  void setEmpty();
	  Date();
	  Date(int year, int month, int day);
	  bool operator==(const Date& rhs) const;
	  bool operator!=(const Date& rhs) const;
	  bool operator<(const Date& rhs) const;
	  bool operator>(const Date& rhs) const;
	  bool operator<=(const Date& rhs) const;
	  bool operator>=(const Date& rhs) const;
	  int errCode() const;
	  bool bad() const;
	  std::istream& read(std::istream& istr);
	  std::ostream& write(std::ostream& ostr) const;
  };

  std::istream& operator >> (std::istream& istr, Date& date);    // std ---iostream 
  std::ostream& operator << (std::ostream& ostr, const Date& date); // helper function  global   access public memeber not private  
  //    friend function can access private  


}
#endif
