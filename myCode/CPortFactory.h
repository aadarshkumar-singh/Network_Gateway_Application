/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPORTFACTORY.H
 * Author          : Aadarsh Kumar Singh
 * Description     : Header file that defines API to create all types of
 * 					 ports for communication via the Gateway.
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
	 * @param bits : 8 uint8_t				: IN	The number of data bits, typically 7 or 8
	 * @param parity : NONE parity_t		: IN	Parity, ODD, EVEN or NONE
	 * @param stopbits : 1 uint8_t			: IN	Number of Stopbits, 1 or 2
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
	 * @param port : UART : To create UART port
	 * 					 CAN  : To create CAN port
	 * @return CPort* address of the port that has been created.
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
