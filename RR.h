#include "Scheduler.h"

class RR: public Scheduler
{
	private:
		int timeQuantum;
		int currentQuantum;
	public:
		RR(int quantum);
		void Simulate();
};