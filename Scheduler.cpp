#include "Scheduler.h"
#include <iomanip>

Scheduler::Scheduler()
{
	processorTime = 0;
	idleTime = 0;
	currentProcess = NULL;
	moreInputs = true;
	nonEmptyReadyQueue = true;
	numProcesses = 0;
	
}


void Scheduler::ReadInputFile(char* filename)
{
	ifstream reader(filename);
	int ID,arrival,burst;
	PCB holder;
	while(reader >> ID >> arrival >> burst)
	{
		PCB* newPCB = new PCB();
		newPCB->PID = ID;
		newPCB->arrivalTime = arrival;
		newPCB->burstTime = burst;
		newPCB->remainingTime = burst;
		newPCB->waitingTime = 0;
		newPCB->responseTime = 0;
		newPCB->lastExecutionTime = 0;
		newPCB->terminationTime = 0;
		holder = *newPCB;
		inputQueue.push(holder);
		numProcesses++;
	}
	reader.close();
	CheckForNewProcess();
}

void Scheduler::CheckForNewProcess()
{
	PCB holder;
	bool traversal = true;
	while(!inputQueue.empty())
	{
		holder = inputQueue.front();
		if(holder.arrivalTime == processorTime)
		{
			readyQueue.push(holder);
			nonEmptyReadyQueue = true;
			inputQueue.pop();
		}	
		else
			break;
		if(currentProcess == NULL)
		{
			currentProcess = &readyQueue.front();
			readyQueue.pop();
		}
	}
	if(inputQueue.empty())
		moreInputs = false;
}

void Scheduler::ContextSwitch()
{
	PCB holder;
	holder = *currentProcess;
	if(currentProcess->remainingTime != 0)
	{
		holder.lastExecutionTime = processorTime;
		readyQueue.push(holder);
	}
	else
	{
		cout << "process " << holder.PID << " is finished......." << endl;
		cout << "<system time " << processorTime << "> ";
		holder.terminationTime = processorTime;
		terminationQueue.push(holder);
		currentProcess = NULL;
	}
	if(!readyQueue.empty())
	{
		currentProcess = &readyQueue.front();
		readyQueue.pop();
		if(currentProcess->waitingTime == 0)
			currentProcess->responseTime = processorTime - currentProcess->arrivalTime;
		currentProcess->waitingTime += (processorTime - currentProcess->lastExecutionTime);
		
	}
	else
		nonEmptyReadyQueue = false;
}

void Scheduler::EndOfProgramStatistics()
{
	double totalWaitingTime = 0.00;
	double totalResponseTime = 0.00;
	double totalTurnaroundTime = 0.00;
	PCB holder;
	while(!terminationQueue.empty())
	{
		holder = terminationQueue.front();
		terminationQueue.pop();
		totalResponseTime += holder.responseTime;
		totalWaitingTime += holder.waitingTime;
		totalTurnaroundTime += (holder.terminationTime - holder.responseTime);
	}
	for(int i = 0; i < 80; i++)
		cout << "=";
	cout << endl << endl;
	double processorUsage = 1.0000;
	if(idleTime != 0)
		processorUsage = idleTime /	processorTime;
	cout << "CPU Usage: " << processorUsage * 100 << "%" << endl;
	cout << "Average waiting time: " << totalWaitingTime/(numProcesses) << endl;
	cout << "Average response time: " << totalResponseTime/((double)(numProcesses)) << endl;
	cout << "Average turnaround time: " << totalTurnaroundTime/((double)(numProcesses)) << endl;

	for(int i = 0; i < 80; i++)
		cout << "=";
	cout << endl;
}

void Scheduler::Simulate() {}