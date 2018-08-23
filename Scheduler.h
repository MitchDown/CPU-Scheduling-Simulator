#include <iostream>
#include <fstream>
#include <queue>

#ifndef SCHEDULER_H
#define SCHEDULER_H

using namespace std;

class Scheduler
{
	private:

	protected:
		int processorTime;
		int idleTime;
		bool moreInputs;
		bool nonEmptyReadyQueue;
		int numProcesses;
		struct PCB
		{
			unsigned int PID;
			unsigned int arrivalTime;
			unsigned int burstTime;
			unsigned int remainingTime;
			unsigned int waitingTime;
			unsigned int responseTime;
			unsigned int lastExecutionTime;
			unsigned int terminationTime;
			bool operator<(const PCB& right) const
			{
				return remainingTime > right.remainingTime;
			}
		};
		queue<PCB> inputQueue;
		queue<PCB> readyQueue;
		queue<PCB> terminationQueue;
		PCB* currentProcess;
	public:
		Scheduler();
		void ReadInputFile(char* filename);
		virtual void ContextSwitch();
		virtual void CheckForNewProcess();
		virtual void Simulate();
		void EndOfProgramStatistics();
};
#endif