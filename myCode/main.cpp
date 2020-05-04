// Standard (system) header files
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
#include "CSimulationTestGatewayApp.h"
#include "CentralErrorHandler.h"

ErrorWriter errorConsole;
CentralErrorHandler errorHandler(errorConsole,CentralErrorHandler::terminateError);


// Main program
int main (void)
{
	CSimulationTestGatewayApp testGateway;
	testGateway.simulateGateway();

	return 0;
}
