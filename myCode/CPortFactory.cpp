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

/**
 * \brief Count Number of UART ports open during program Execution
 */
uint8_t CPortFactory::countUartPort = 0;

/**
 * \brief Count Number of Can ports open during program Execution
 */
uint8_t CPortFactory::countCanPort = 0;

/*
	 * \brief Create CAN port
	 * @param port : The type of CAN port
	 * @param baudrate : The baudrate of the device. Check the hardware manual for valid values.
	 * @param bufferSizeRx : Size of the Receive Buffer
	 * @param bufferSizeTx : Size of the Transmit buffer
	 * @return CPort * : Returns a pointer of UART communication
*/
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

/*
 * \brief Create UART port
 * @param port : The type of UART port
 * @param baudrate : The baudrate of the device. Check the hardware manual for valid values.
 * @param bufferSizeRx : Size of the Receive Buffer
 * @param bufferSizeTx : Size of the Transmit buffer
 * @return CPort * : Returns a pointer of UART communication
 */
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

/*
 * \brief Will create a port using the default configuration of the port (i.e. the default parameters set above)
 * \param : port_t : UART : To create UART port
 * 					 CAN  : To create CAN port
 */
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

/*
 * \brief Decrement Count of number of CAN Port that are opened.
 */
void CPortFactory::decrementCountCanPort()
{
	countCanPort--;
}

/*
 * \brief Decrement Count of number of UART Port that are opened.
 */
void CPortFactory::decrementCountUartPort()
{
	countUartPort--;
}
