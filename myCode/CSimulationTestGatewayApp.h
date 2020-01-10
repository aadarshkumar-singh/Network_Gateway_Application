/***************************************************************************
 ****************************************************************************
 * \file CSimulationTestGatewayApp.h
 * \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
 * \date 30.12.2019
 *
 * \brief CSimulationTestGatewayApp.h
 *
 * Header file that declares API to simulate all the test cases of the Gateway
 *
 ****************************************************************************/

#ifndef CSIMULATIONTESTGATEWAYAPP_H_
#define CSIMULATIONTESTGATEWAYAPP_H_
#include <iostream>
#include <stdlib.h>

#include "CGateway.h"
#include "CPortFactory.h"
#include "CPort.h"
#include "CentralErrorHandler.h"

using namespace std;

/**
 * \brief This class defines the API to simulate the testcases of the Gateway
 */
class CSimulationTestGatewayApp
{

public:

	/**
	 * \brief Default Constructor
	 */
	CSimulationTestGatewayApp();

	/**
	 * \brief API to Simulate the gateway
	 */
	void simulateGateway();
};

#endif /* CSIMULATIONTESTGATEWAYAPP_H_ */
