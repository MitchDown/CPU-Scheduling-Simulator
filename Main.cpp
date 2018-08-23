#include "Scheduler.h"
#include "FCFS.h"
#include "RR.h"
#include "SRTF.h"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		cout << "Usage: " << argv[0] << " input_file  [FCFS | RR | SRTF]  [quantum]" << endl;
		return -1;
	}
	string algoType = (string)argv[2];
	Scheduler* schedAlgo;
	if(algoType == "FCFS")
		schedAlgo = new FCFS();
	if(algoType == "SRTF")
		schedAlgo = new SRTF();
	if(algoType == "RR")
		schedAlgo = new RR(atoi(argv[3]));
	schedAlgo->ReadInputFile(argv[1]);
	schedAlgo->Simulate();
	schedAlgo->EndOfProgramStatistics();
}