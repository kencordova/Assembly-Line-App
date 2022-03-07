

#include "Station.h"

Station::Station() {}

// the constructor uses an Utilities object (created local in the function) to extract each token from the record and populates the Station object accordingly.
Station::Station(const string& str) {

		Utilities tokenExtractor;

		bool more = true;
		size_t cur_pos = 0;

		m_id = ++id_generator;

		m_name = tokenExtractor.extractToken(str, cur_pos, more);

		m_serial = stoi(tokenExtractor.extractToken(str, cur_pos, more));

		m_stock = stoi(tokenExtractor.extractToken(str, cur_pos, more));

// once the constructor has extracted name, starting serial number, and quantity from the record, it updates Station::m_widthField to the maximum value of Station::m_widthField and Utilities::m_widthField.

		if (tokenExtractor.getFieldWidth() > m_widthField) 
            
        m_widthField = tokenExtractor.getFieldWidth();

		m_desc = tokenExtractor.extractToken(str, cur_pos, more);

	}

const string &Station::getItemName() const {
    return m_name;
}

unsigned int Station::getNextSerialNumber() {
    return m_serial++;
}

unsigned int Station::getQuantity() const {
    return m_stock;
}

void Station::updateQuantity() {
    if (m_stock == 1) {
        m_stock = 0;
    } else {
        m_stock -= 1;
    }
}

void Station::display(ostream &os, bool qty) const {
    os << "[" << right << setw(3) << setfill('0') << m_id << setfill(' ') << "]";
    os << " Item: " << left << setw(m_widthField) << getItemName() << " ";
    os << "[" << right << setw(6) << setfill('0') << m_serial << setfill(' ') << "]";
    if (qty) {
        os << " Quantity: " << setw(m_widthField) << left << m_stock << " Description: " << m_desc;
    }
    os << left << setfill(' ');
    os << endl;
}