#include "RR.h"

RR::RR(int quantum):Scheduler()
{
	timeQuantum = quantum;
	currentQuantum = 0;
}

void RR::Simulate()
{
	while((nonEmptyReadyQueue || moreInputs) || currentProcess != NULL)
	{
		cout << "<system time " << processorTime << "> ";
		if(!inputQueue.empty())
			CheckForNewProcess();
		if(currentProcess == NULL)
		{
			cout << "no process is running" << endl;
			idleTime++;
		}
		else
		{
			if(currentProcess->remainingTime == 0 || currentQuantum == timeQuantum)
			{
				ContextSwitch();
				currentQuantum = 0;
			}
			if(!nonEmptyReadyQueue && currentProcess == NULL)
			{
				if(moreInputs)
				{
					cout << "no process is running" << endl;
				}
			}
			else
			{
				cout << "process " << currentProcess->PID << " is running" << endl;
				currentProcess->remainingTime--;
			}
			currentQuantum++;
		}
		processorTime++;
		
	}
	cout << "All processes finished............" << endl;
}