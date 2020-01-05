// Standard (system) header files
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
#include "CGateway.h"
#include "CPortFactory.h"
#include "CPort.h"
#include "CentralErrorHandler.h"

void terminateError()
{
	cerr << "Hard termination" << endl;
	terminate();
}

void terminateWarning()
{
	cerr << "No termination - program continues" << endl;
}

// Main program
int main (void)
{
	ErrorWriter errorConsole;
	CentralErrorHandler errorHandle(errorConsole,terminateError);

	CGateway simpleGateway(CPortFactory::UART, CPortFactory::CAN,errorHandle);
	simpleGateway.transmitFromAToB();

	CPort* portA = CPortFactory::createPort(CPortFactory::UART);
	CPort* portB = CPortFactory::createPort(CPortFactory::CAN);
	CGateway simpleGateway2(portA,portB,errorHandle);


	CPort* portA1 = CPortFactory::createPort(CPortFactory::UART);
	CPort* portB1 = CPortFactory::createPort(CPortFactory::CAN);
	CGateway simpleGateway3(portA1,portB1,errorHandle);

	return 0;
}
