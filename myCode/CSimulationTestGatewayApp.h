/*
 * CSimulationTestGatewayApp.h
 *
 *  Created on: Jan 6, 2020
 *      Author: Aadarshxp
 */

#ifndef CSIMULATIONTESTGATEWAYAPP_H_
#define CSIMULATIONTESTGATEWAYAPP_H_
#include <iostream>
#include <stdlib.h>

#include "CGateway.h"
#include "CPortFactory.h"
#include "CPort.h"
#include "CentralErrorHandler.h"

using namespace std;

class CSimulationTestGatewayApp
{
public:
	CSimulationTestGatewayApp();
	void simulateGateway();
};

#endif /* CSIMULATIONTESTGATEWAYAPP_H_ */
