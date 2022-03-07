

#ifndef _CUSTOMERORDER_H
#define _CUSTOMERORDER_H

#include <string>
#include "Station.h"

using namespace std;

struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;

	Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {

	std::string m_name{};
	std::string m_product{};
	unsigned int m_cntItem{};
	Item** m_lstItem{};
	static size_t m_widthField;

public:
	CustomerOrder();
	CustomerOrder(const string& str);
	CustomerOrder(const CustomerOrder& cst_ord);
	CustomerOrder& operator=(const CustomerOrder& cst_ord) = delete;
	CustomerOrder(CustomerOrder&& cst_ord) noexcept;
	CustomerOrder& operator=(CustomerOrder&& cst_ord) noexcept;
	~CustomerOrder();
	bool isOrderFilled() const;
	bool isItemFilled(const std::string& itemName) const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;


};



#endif