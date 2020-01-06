/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORTFACTORY.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files


//Own Include Files
#include "CPortFactory.h"


//Method Implementations

uint8_t CPortFactory::countUartPort = 0;
uint8_t CPortFactory::countCanPort = 0;


CPort* CPortFactory::createCanPort(CCanPort::port_t port,
		uint32_t baudrate, uint16_t bufferSizeRx, uint16_t bufferSizeTx)
{
	if (countCanPort < PORT_CANNMAX)
	{
		countCanPort++;
		return new CCanPort(port, baudrate,bufferSizeRx, bufferSizeTx);

	}
	else
	{
		errorHandler.report(CEH_MAXIMUMLIMITOFPORTREACHED);
		return NULL;
	}
}

CPort* CPortFactory::createUartPort(CUartPort::port_t port,
		uint32_t baudrate, uint8_t bits, CUartPort::parity_t parity,
		uint8_t stopbits, uint16_t bufferSizeRx, uint16_t bufferSizeTx)
{
	if (countUartPort < PORT_CANNMAX)
	{
		countUartPort++;
		return new CUartPort(port, baudrate, bits, parity,stopbits, bufferSizeRx, bufferSizeTx);
	}
	else
	{
		errorHandler.report(CEH_MAXIMUMLIMITOFPORTREACHED);
		return NULL;
	}

}

CPort* CPortFactory::createPort(port_t port)
{
	switch (port)
	{
	case UART: return createUartPort();
	case CAN: return createCanPort();
	default: /* Some error handling */ break;
	}

	return 0;
}

void CPortFactory::decrementCountCanPort()
{
	countCanPort--;
}

void CPortFactory::decrementCountUartPort()
{
	countUartPort--;
}
