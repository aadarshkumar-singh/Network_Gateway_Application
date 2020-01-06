/*
 * CParser.cpp
 *
 *  Created on: 01.12.2019
 *      Author: Fromm
 */

#include "CGateway.h"

#include <string>
#include "CPort.h"
using namespace std;


CGateway::CGateway(CPortFactory::port_t portA, CPortFactory::port_t portB)
{
	m_portA = CPortFactory::createPort(portA);
	m_portB = CPortFactory::createPort(portB);

	if (m_portA == NULL || m_portB ==NULL)
	{
		errorHandler.report(CEH_INVALIDPOINTER);
	}
}

CGateway::CGateway(CPort *portA, CPort *portB)
{
	if (portA == NULL || portB == NULL)
	{
		errorHandler.report(CEH_INVALIDPOINTER);
	}

	m_portA = portA;
	m_portB = portB;
}

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


void CGateway::resetPorts()
{
	if (m_portA->getDriverPackageSize() == CAN_PACKETSIZE)
	{
		CPortFactory::decrementCountCanPort();
	}
	else
	{
		CPortFactory::decrementCountUartPort();
	}

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
	resetPorts();
	m_portA = 0;
	m_portB = 0;
}

