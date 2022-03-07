
#ifndef _LINEMANAGER_H
#define _LINEMANAGER_H
#include "Workstation.h"
#include "Utilities.h"
#include <vector>

using namespace std;

class LineManager {
	std::vector<Workstation*> m_AssemblyLine;
	std::vector<Workstation*> m_AssemblyLineSorted;
	std::deque<CustomerOrder> m_ToBeFilled;
	std::deque<CustomerOrder> m_Completed;
	unsigned int m_cntCustomerOrder;
	static size_t count;

public:

	LineManager();
	LineManager(const string& str, vector<Workstation*>& station, vector<CustomerOrder>& order);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;

};



#endif