/*
 * CSimulationTestGatewayApp.cpp
 *
 *  Created on: Jan 6, 2020
 *      Author: Aadarshxp
 */

#include "CSimulationTestGatewayApp.h"

typedef enum simulationMenu_e
{
	UARTTOCAN = 1,
	CANTOUART,
	CANTOCAN,
	UARTTOUART,
	INVALIDORNULLPOINTER,
	MAXIMUMPORTLIMITREACHED,
	REOPENINGOPENEDPORT,
	EXITSIMULATIONMENU,

}simulationMenu_t;

CSimulationTestGatewayApp::CSimulationTestGatewayApp()
{
	// TODO Auto-generated constructor stub

}

void CSimulationTestGatewayApp::simulateGateway()
{
	int choice ;

	while (1)
	{
		cout <<"Enter the choice from the list "<<endl;
		cout <<"1. Simulation of UART to CAN communication"<<endl;
		cout <<"2. Simulation of CAN to UART communication"<<endl;
		cout <<"3. Simulation of CAN to CAN communication"<<endl;
		cout <<"4. Simulation of UART to UART communication"<<endl;
		cout <<"5. Simulation when Invalid/NULL Pointer passed to gateway"<<endl;
		cout <<"6. Simulation of Maximum Port limit Reached"<<endl;
		cout <<"7.Simulation of reopening an already open port"<<endl;
		cout <<"8.Terminate the Simulation"<<endl;
		cin>>choice;

		switch(choice)
		{
		case UARTTOCAN :
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}
		case CANTOUART :
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}

		case CANTOCAN:
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}

		case UARTTOUART:
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}


		case INVALIDORNULLPOINTER :
		{
			CPort* portA = NULL;
			CPort* portB = NULL;
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;

		}

		case MAXIMUMPORTLIMITREACHED :
		{
			CPort* portA1 = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB1 = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway1(portA1,portB1);
			simpleGateway1.transmitFromAToB();

			CPort* portA2 = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB2 = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway2(portA2,portB2);
			simpleGateway2.transmitFromAToB();

			CPort* portA3 = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB3 = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway3(portA3,portB3);
			simpleGateway3.transmitFromAToB();

			break;
		}

		case REOPENINGOPENEDPORT :
		{
			CPort* portA1 = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB1 = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway1(portA1,portB1);
			simpleGateway1.transmitFromAToB();
			CPort* portA2 = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway2(portA2,portB1);
			simpleGateway2.transmitFromAToB();
			break;
		}

		case EXITSIMULATIONMENU :
		{
			std::cout <<"**User Asked to Quit the Simulation ** "<<endl;
			exit(0);
			break;
		}


		default :
		{
			std::cerr <<"** Invalid option ** "<<endl;
			errorHandler.report(CEH_INVALID_OPTION);
			break;
		}

		}

	}

}
