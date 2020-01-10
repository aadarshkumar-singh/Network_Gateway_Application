/***************************************************************************
 ****************************************************************************
 * \file CSimulationTestGatewayApp.cpp
 * \author Aadarsh Kumar Singh <aadarsh.k.singh@stud.h-da.de>
 * \date 30.12.2019
 *
 * \brief CSimulationTestGatewayApp.cpp
 *
 * Source file that defines API to simulate all the test cases of the Gateway
 *
 ****************************************************************************/

#include "CSimulationTestGatewayApp.h"

/**
 * \brief enum for every simulation test case of the gatewat
 */
typedef enum simulationMenu_e
{
	UARTTOCAN = 1,          //!< UARTTOCAN  : Simulation of UART to CAN communication
	CANTOUART,              //!< CANTOUART  : Simulation of CAN to UART communication
	CANTOCAN,               //!< CANTOCAN   : Simulation of CAN to CAN communication
	UARTTOUART,             //!< UARTTOUART : Simulation of UART to UART communication
	INVALIDORNULLPOINTER,   //!< INVALIDORNULLPOINTER : Simulation of error while Invalid/NULL Port Pointer passed to gateway
	MAXIMUMPORTLIMITREACHED,//!< MAXIMUMPORTLIMITREACHED : Simulation of error while Maximum Port reached gateway
	REOPENINGOPENEDPORT,    //!< REOPENINGOPENEDPORT : Simulation of error while reopening the port previously used.
	EXITSIMULATIONMENU,     //!< EXITSIMULATIONMENU : Exit simulation

}simulationMenu_t;

CSimulationTestGatewayApp::CSimulationTestGatewayApp()
{

}

/*
 * \brief This class defines the API to simulate the testcases of the Gateway
 */
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
		//Simulation of UART to CAN communication
		case UARTTOCAN :
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}
		//Simulation of CAN to UART communication
		case CANTOUART :
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}
		//Simulation of CAN to CAN communication
		case CANTOCAN:
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}
		//Simulation of UART to UART communication
		case UARTTOUART:
		{
			CPort* portA = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;
		}
		// Simulation of error while Invalid/NULL Port Pointer passed to gateway
		case INVALIDORNULLPOINTER :
		{
			CPort* portA = NULL;
			CPort* portB = NULL;
			CGateway simpleGateway(portA,portB);
			simpleGateway.transmitFromAToB();
			break;

		}
		// Simulation of error while Maximum Port reached gateway
		case MAXIMUMPORTLIMITREACHED :
		{
			CPort* portA1 = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB1 = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway1(portA1,portB1);
			//simpleGateway1.transmitFromAToB();

			CPort* portA2 = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB2 = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway2(portA2,portB2);
			//simpleGateway2.transmitFromAToB();

			CPort* portA3 = CPortFactory::createPort(CPortFactory::CAN);
			CPort* portB3 = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway3(portA3,portB3);
			simpleGateway3.transmitFromAToB();

			break;
		}

		//Simulation of error while reopening the port previously used.
		case REOPENINGOPENEDPORT :
		{
			CPort* portA1 = CPortFactory::createPort(CPortFactory::UART);
			CPort* portB1 = CPortFactory::createPort(CPortFactory::CAN);
			CGateway simpleGateway1(portA1,portB1);
			//simpleGateway1.transmitFromAToB();
			CPort* portA2 = CPortFactory::createPort(CPortFactory::UART);
			CGateway simpleGateway2(portA2,portB1);
			simpleGateway2.transmitFromAToB();
			break;
		}

		//Exit simulation
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
