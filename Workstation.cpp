

#include "Workstation.h"

Workstation::Workstation() :m_pNextStation{ nullptr } {}

Workstation::Workstation(const string& str) :Station(str) {
	m_pNextStation = nullptr;
}

void Workstation::runProcess(ostream& os) {
	if (!m_orders.empty()) m_orders.front().fillItem(*this, os);
}

// if the order at the front of the queue doesn't require service at the current station, move it to the next station on the assembly line and return true. Otherwise, do nothing and return false. If the queue is empty, return false
bool Workstation::moveOrder() {

	bool yes = false;

	if (!m_orders.empty() && m_orders.front().isItemFilled(getItemName()) && m_pNextStation) {
		yes = true;
		*m_pNextStation += move(m_orders.front());
		m_orders.pop_front();
	}

	return yes;

}

void Workstation::setNextStation(Station& station) {
	m_pNextStation = (Workstation*)&station;
}

const Workstation* Workstation::getNextStation() const {
	return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order) {

	bool yes = false;
		
	if (!m_orders.empty() && m_orders.front().isOrderFilled()) {

		yes = true;
		order = move(m_orders.front());
		m_orders.pop_front();

	}															

	return yes;

}

Workstation& Workstation::operator+=(CustomerOrder&& order) {
	m_orders.push_back(move(order));
	return *this;
}

void Workstation::display(ostream& os) {
	
	if (getNextStation()) os << getItemName() << " --> " << getNextStation()->getItemName() << endl;

	else os << getItemName() << " --> " << "END OF LINE" << endl;

}
