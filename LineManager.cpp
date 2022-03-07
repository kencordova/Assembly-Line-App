

#include "LineManager.h"
#include <fstream>
#include <algorithm>

size_t LineManager::count = 1u;

LineManager::LineManager() :m_cntCustomerOrder{0} {}

LineManager::LineManager(const string& str, vector<Workstation*>& station, vector<CustomerOrder>& order) {
	
	string line;
	string itemCurrent;
	string itemNext;
	fstream file(str);

	Utilities extractor;
	size_t cur_pos = 0;
	

	while (file) {

		bool more = true;

		while (getline(file, line)) {
			
			itemCurrent = extractor.extractToken(line, cur_pos, more);

			for (auto i : station) {
				if (itemCurrent == i->getItemName()) {
					if (more) {
						itemNext = extractor.extractToken(line, cur_pos, more);
						for (auto j : station)
							if (itemNext == j->getItemName()) i->setNextStation(*j);
					}
					m_AssemblyLineSorted.push_back(i);
				}
			}

		}

	}

	m_AssemblyLine = station;

	m_cntCustomerOrder = order.size();
	m_ToBeFilled = deque<CustomerOrder>(m_cntCustomerOrder);
	for (auto i = 0u; i < m_cntCustomerOrder; i++) {
		m_ToBeFilled[i] = move(order[i]);
	}
}

bool LineManager::run(std::ostream& os) {

	CustomerOrder temp;

	os << "Line Manager Iteration: " << count << endl;
	if (m_ToBeFilled.size() > 0)
	{
		*m_AssemblyLineSorted.at(0) += move(m_ToBeFilled.front());
		m_ToBeFilled.pop_front();
	}

	for (auto i : m_AssemblyLine) {
		i->runProcess(os);
	}

	for (auto i : m_AssemblyLine) {
		i->moveOrder();

		if (i->getIfCompleted(temp)) {
			m_Completed.push_back(move(temp));
		}

	}
	count++;

	return m_Completed.size() == m_cntCustomerOrder;
}

void LineManager::displayCompletedOrders(std::ostream& os) const {

	for (auto i = m_Completed.begin(); i != m_Completed.end(); i++) {
		(*i).display(cout);
	}
}

void LineManager::displayStations() const{
	for (auto i : m_AssemblyLine) {
		i->display(cout);
	}
}

void LineManager::displayStationsSorted() const {

	for (auto i : m_AssemblyLineSorted) {
	    i->display(cout);
	}

}