// pblaunch.cpp : Defines the entry point for the console application.
//

#include "stdio.h"

#include "pbapi.h"

char processName[] = "FULLTILTPOKER.EXE";
char dllName[] = "PBFT.DLL";
char dirName[]=".";

int main(int argc, char* argv[])
{
	return pbStart(processName, argc>1?argv[1]:".", dllName, 1);	
}

