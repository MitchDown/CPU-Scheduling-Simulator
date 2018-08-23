#include "FCFS.h"

FCFS::FCFS():Scheduler() {}

void FCFS::Simulate()
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
			if(currentProcess->remainingTime == 0)
				ContextSwitch();
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
		}
		processorTime++;
	}
	cout << "<system time " << processorTime << "> ";
	cout << "All processes finished............" << endl;
	return;
}