/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPORTFACTORY.H
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

#ifndef CPORTFACTORY_H
#define CPORTFACTORY_H

#include "CPort.h"
#include "CUartPort.h"
#include "CCanPort.h"
#include "CentralErrorHandler.h"

class CPortFactory {
private:
	/**
	 * \brief Count Number of UART ports open during program Execution
	 */
	static uint8_t countUartPort;

	/**
	 * \brief Count Number of Can ports open during program Execution
	 */
	static uint8_t countCanPort;

public:

	/**
	 * \brief ENUM that defines flag to define ports which are supported
	 *
	 */
	enum port_t
	{
		UART, //!< UART : port for UART communication
		CAN,  //!< CAN  : port for CAN communication
		NONE, //!< NONE : No port
	};

	/**
	 * \brief Create CAN port
	 * @param port : The type of CAN port
	 * @param baudrate : The baudrate of the device. Check the hardware manual for valid values.
	 * @param bufferSizeRx : Size of the Receive Buffer
	 * @param bufferSizeTx : Size of the Transmit buffer
	 * @return CPort * : Returns a pointer of UART communication
	 */
	static CPort* createCanPort(
			CCanPort::port_t port = CCanPort::NONE,
			uint32_t baudrate = 1000000,
			uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE,
			uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE);

	/**
	 * \brief Create UART port
	 * @param port : The type of UART port
	 * @param baudrate : The baudrate of the device. Check the hardware manual for valid values.
	 * @param bufferSizeRx : Size of the Receive Buffer
	 * @param bufferSizeTx : Size of the Transmit buffer
	 * @return CPort * : Returns a pointer of UART communication
	 */
	static CPort* createUartPort(
			CUartPort::port_t port = CUartPort::NONE,
			uint32_t baudrate = 115200,
			uint8_t bits = 8,
			CUartPort::parity_t parity = CUartPort::NOPARITY,
			uint8_t stopbits = 1,
			uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE,
			uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE);

	/**
	 * \brief Will create a port using the default configuration of the port (i.e. the default parameters set above)
	 * \param : port_t : UART : To create UART port
	 * 					 CAN  : To create CAN port
	 */
	static CPort* createPort(port_t port);

	/**
	 * \brief Decrement Count of number of CAN Port that are opened.
	 */
	static void decrementCountCanPort();

	/**
	 * \brief Decrement Count of number of UART Port that are opened.
	 */
	static void decrementCountUartPort();


};
/********************
 **  CLASS END
 *********************/
#endif /* CPORTFACTORY_H */
