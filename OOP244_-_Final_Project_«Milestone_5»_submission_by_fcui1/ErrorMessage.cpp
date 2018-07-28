#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ErrorMessage.h"

namespace sict {
	

	void ErrorMessage::clear() {
		delete[] m_message;
		m_message = nullptr;
	}
	bool ErrorMessage::isClear() const {
		return (m_message != nullptr) ? false : true;

	}
	ErrorMessage::~ErrorMessage() {
		clear();
	}
	ErrorMessage::ErrorMessage(const char* errorMessage) {

		if (errorMessage != nullptr) {
			m_message = new char[strlen(errorMessage) + 1];
			strcpy(m_message, errorMessage);

		}
		else {
			
			m_message = nullptr;
		}
	}
	const  char* ErrorMessage::message()const {
		return m_message;

	}

	void ErrorMessage::message(const char* str)
	{
		clear();
		m_message = new char[strlen(str) + 1];
		strcpy(m_message, str);
	}
	std::ostream& operator<<(std::ostream& os, ErrorMessage& em) {
		if (!(em.isClear())) {
			os << em.message();
		}
		return os;
	}
}
	


