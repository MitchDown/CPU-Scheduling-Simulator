#include "SRTF.h"

//Implementation file for the "Shortest Remaining Time First" algorithm

SRTF::SRTF():Scheduler() 
{
	currentProcess = new PCB();
}

void SRTF::CheckForNewProcess()
{
	PCB holder;
	PCB initial;
	while(!inputQueue.empty())
	{
		holder = inputQueue.front();
		if(holder.arrivalTime == processorTime)
		{
			priorityReadyQueue.push(holder);
			inputQueue.pop();
			if(currentProcess != NULL)
			{
				if(holder.remainingTime < currentProcess->remainingTime)
				{
					ContextSwitch();
				}
			}
			if(processorTime == 0 && currentProcess == NULL)
			{	
				currentProcess = new PCB();
				*currentProcess = holder;
				priorityReadyQueue.pop();
			}
		}
		else
			break;
	}
	if(inputQueue.empty())
		moreInputs = false;
}

void SRTF::ContextSwitch()
{
	PCB holder;
	holder = *currentProcess;
	if(currentProcess->remainingTime != 0)
	{
		holder.lastExecutionTime = processorTime;
		priorityReadyQueue.push(holder);
		cout << "swapping out " << holder.PID << endl;
		delete currentProcess;
	}
	else
	{
		cout << "process " << holder.PID << " is finished......." << endl;
		cout << "<system time " << processorTime << "> ";
		holder.terminationTime = processorTime;
		terminationQueue.push(holder);
		delete currentProcess;
	}
	if(!priorityReadyQueue.empty())
	{
		holder = priorityReadyQueue.top();
		currentProcess = new PCB();
		*currentProcess = holder;
		priorityReadyQueue.pop();
		if(currentProcess->waitingTime == 0)
			currentProcess->responseTime = processorTime - currentProcess->arrivalTime;
		currentProcess->waitingTime += (processorTime - currentProcess->lastExecutionTime);
		
	}
	else
	{
		currentProcess = NULL;
		nonEmptyReadyQueue = false;
	}
}

void SRTF::Simulate()
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
}
