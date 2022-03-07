

#ifndef _WORKSTATION_H
#define _WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"

class Workstation : public Station {

	deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation{nullptr};

public:

	Workstation();
	//a custom constructor -- upon instantiation, a Workstation object receives a reference to an unmodifiable std::string. This string contains a single record (one line) that has been retrieved from the input file specified by the user to be used for Station instantiation.
	Workstation(const string& str);
	Workstation(Workstation&) = delete;
	Workstation& operator=(Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(Workstation&&) = delete;
    void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os = cout);
    Workstation& operator+=(CustomerOrder&& order);

};



#endif