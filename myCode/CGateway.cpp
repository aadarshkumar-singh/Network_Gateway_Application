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

CGateway::CGateway(CPort *portA, CPort *portB)
{
	bool flagForValidPorts = false ;

	if (portA == NULL || portB == NULL)
	{
		errorHandler.report(CEH_INVALIDPOINTER);
	}

	try
	{
		flagForValidPorts = (checkIfOpeningValidPort(portA) && checkIfOpeningValidPort(portB));
		if(flagForValidPorts)
		{
			m_portA = portA;
			m_portB = portB;
		}
		else
		{
			throw flagForValidPorts ;
		}
	}
	catch(bool& flagForValidPorts)
	{
		cout<<" Gateway trying to use ports that are already opened ::> "<<endl;
		errorHandler.report(CEH_INVALIDPORT);
	}

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

	m_OpenedPorts.clear();
}

bool CGateway::checkIfOpeningValidPort(CPort *port)
{
	bool flag = false ;

	if (m_OpenedPorts.empty())
	{
		m_OpenedPorts.push_back(port);
		flag = true;
	}
	else
	{
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
