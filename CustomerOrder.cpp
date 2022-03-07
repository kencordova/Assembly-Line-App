

#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {}

// a custom constructor that takes as a parameter a reference to a string containing a single record from the input file
CustomerOrder::CustomerOrder(const string& str) {

	Utilities extractor;
	string temp;
	bool more = true;
	size_t cur_pos = 0;

	m_name = extractor.extractToken(str, cur_pos, more);
	m_product = extractor.extractToken(str, cur_pos, more);

	size_t sec_pos = cur_pos;

	while (more) {
		temp = extractor.extractToken(str, cur_pos, more);
		m_cntItem++;
	}

	m_lstItem = new Item * [m_cntItem] {};

	for (auto i = 0u; i < m_cntItem; i++) {
		temp = extractor.extractToken(str, sec_pos, more);
		m_lstItem[i] = new Item(temp);
	}

	if (extractor.getFieldWidth() > m_widthField)
		m_widthField = extractor.getFieldWidth();
}

CustomerOrder::CustomerOrder(const CustomerOrder& cst_ord) {
	throw string("Copy operations for CustomerOrder is ILLEGAL");
}

// move assignment operator. This operator should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the prototype.
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cst_ord) noexcept {
	if (this != &cst_ord) {
		if (m_lstItem) {
			for (auto i = 0u; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}

		m_name = cst_ord.m_name;
		m_product = cst_ord.m_product;
		m_lstItem = cst_ord.m_lstItem;
		m_cntItem = cst_ord.m_cntItem;


		cst_ord.m_name = "";
		cst_ord.m_product = "";
		cst_ord.m_lstItem = nullptr;
		cst_ord.m_cntItem = 0u;
	}

	return *this;
}

// move constructor. This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the prototype.
CustomerOrder::CustomerOrder(CustomerOrder&& cst_ord) noexcept {
	*this = std::move(cst_ord);
}


void CustomerOrder::fillItem(Station& station, std::ostream& os) {

	for (auto i = 0u; i < m_cntItem; i++) {

		if (m_lstItem[i]->m_itemName == station.getItemName()) {

			if (station.getQuantity() > 0) {
				station.updateQuantity();
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;

				os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
			}

			else os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << std::endl;
		}
	}
}

bool CustomerOrder::isOrderFilled() const {

	bool yes = true;

	for (auto i = 0u; i < m_cntItem; i++) {
		if(m_lstItem[i]->m_isFilled == false) yes = false;
	}

	return yes;

}

bool CustomerOrder::isItemFilled(const std::string& itemName) const {

	bool yes = true;

	for (auto i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == itemName) yes = m_lstItem[i]->m_isFilled;
	}
	
	return yes;
}

CustomerOrder::~CustomerOrder() {

	for (auto i = 0u; i < m_cntItem; i++) {
		delete m_lstItem[i];
	}

	delete[] m_lstItem;

	m_lstItem = nullptr;

}

void CustomerOrder::display(std::ostream& os) const {

	os << m_name << " - " << m_product << std::endl;

	for (auto i = 0u; i < m_cntItem; i++) {

		os << right << "["; 
		os << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << std::setfill(' ');
		os << "] ";
		os << left << std::setw(m_widthField) << m_lstItem[i]->m_itemName;
		os << " - ";
		os << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING");
		os << std::endl;

	}

}

