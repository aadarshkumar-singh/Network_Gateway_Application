/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CGATEWAY.CPP
 * Author          : Aadarsh Kumar Singh
 * Description     : Source file that defines API to establish communication
 * 					 between two ports.
 *
 ****************************************************************************/


#include "CGateway.h"

#include <string>
#include "CPort.h"
using namespace std;

/*
 * \brief Vector that stores the address of ports that are opened
 * 		  for establishing gateway communication.
 */
std::vector<CPort*> CGateway::m_OpenedPorts ;

CGateway::CGateway(CPortFactory::port_t portA, CPortFactory::port_t portB)
{
	m_portA = CPortFactory::createPort(portA);
	m_portB = CPortFactory::createPort(portB);

	if (m_portA == NULL || m_portB ==NULL)
	{
		errorHandler.report(CEH_INVALIDPOINTER);
	}
}

/*
 * \brief Constructor that accepts the pointer arguments
 * 		  and creates a gateway object if ports are valid.
 *
 * @param portA : Pointer to first communication port
 * @param portB : Pointer to second communication port
 *
 * \note : In case the ports are invalid:
 * 			Null/Invalid : error message of Invalid pointer is printed and program is terminated.
 * 			Invalid Port : error message of Invalid port is printed and program is terminated.
 */
CGateway::CGateway(CPort *portA, CPort *portB)
{
	bool flagForValidPorts = false ;

	if (portA == NULL || portB == NULL)
	{
		cout <<"NULL Address of port found Cannot create Gateway Object"<<endl;
		errorHandler.report(CEH_INVALIDPOINTER);
	}

	try
	{
		flagForValidPorts = (checkIfOpeningValidPort(portA) && checkIfOpeningValidPort(portB));
		if(flagForValidPorts)
		{
			m_portA = portA;
			m_portB = portB;
			cout <<"Gateway Object Created Successfully"<<endl;
		}
		else
		{
			cout<<"Gateway Object Creation Failed"<<endl;
			throw flagForValidPorts ;
		}
	}
	catch(bool& flagForValidPorts)
	{
		cout<<" Gateway trying to use ports that are already opened ::> "<<endl;
		errorHandler.report(CEH_INVALIDPORT);
	}

}
/*
 * Transmits the data from communication port A to Communication port B.
 *
 * @return error code : RC_ERROR : if error in transmitting data
 * 						RC_SUCCESS : if transmission is successfull.
 */
RC_t CGateway::transmitFromAToB()
{
	//Simulate reception of data
	m_portA->portRx_isr();

	if (0 == m_portA || 0 == m_portB)
	{
		return RC_ERROR;
	}

	RC_t result = RC_ERROR;
	//Transmit from A to B
	string data;

	//Read the data
	result = m_portA->readByteStream(data);

	//Do something with the data

	//Write the data
	result = m_portB->writeByteStream(data);

	return result;
}

/*
 * \brief API to decrement the count of the communication ports
 * 		  When the port is not used by the gateway object
 *
 * @param None
 */
void CGateway::resetPorts()
{
	// Check if The port is CAN/ UART , decrement the count of Port accordingly
	if (m_portA->getDriverPackageSize() == CAN_PACKETSIZE)
	{
		CPortFactory::decrementCountCanPort();
	}
	else
	{
		CPortFactory::decrementCountUartPort();
	}

	// Check if The port is CAN/ UART , decrement the count of Port accordingly
	if(m_portB->getDriverPackageSize() == CAN_PACKETSIZE)
	{
		CPortFactory::decrementCountCanPort();
	}
	else
	{
		CPortFactory::decrementCountUartPort();
	}
}

CGateway::~CGateway()
{
	//Decrement the count of UART/CAN depending on the port opened.
	resetPorts();
	m_portA = 0;
	m_portB = 0;
	// Clear the vector that stores the address of all the ports that are already in use.
	m_OpenedPorts.clear();
}

/*
 * \brief API which checks if a valid port is opened for establishing
 * 		  communication via Gateway Object.
 * 		  It checks if the port is already opened and if it is already
 * 		  used by gateway object
 *
 * @param  port : Pointer to the communication port like CAN/UART
 * @return true : If the port is not used by any other gateway object
 * 				  and can be used for establishing communication.
 * 		   false : If the port is already opened and is already
 * 		  			used by gateway object
 */
bool CGateway::checkIfOpeningValidPort(CPort *port)
{
	bool flag = false ;

	// If vector to store port address empty , directly push the port address
	if (m_OpenedPorts.empty())
	{
		m_OpenedPorts.push_back(port);
		flag = true;
	}
	else
	{
		// Check if the port passed in parameter present in the vector
		if ( std::find(m_OpenedPorts.begin(), m_OpenedPorts.end(), port) != m_OpenedPorts.end() )
		{
			flag = false;
		}
		else
		{
			flag = true;
			m_OpenedPorts.push_back(port);
		}
	}
	return flag;
}
