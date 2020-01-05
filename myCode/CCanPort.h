/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CCANPORT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CCANPORT_H
#define CCANPORT_H

#include "global.h"
#include "CPort.h"
#include "CRingbuffer.h"
#include "CUartPort.h"
class CRingBuffer;

#define CAN_DEFAULTBUFFERSIZE 64
#define PORT_CANNMAX 2

class CCanPort : public CPort {

public:

    enum port_t{
    	CAN1,		/**< \brief CAN Port 1 */
		CAN2, 		/**< \brief CAN Port 2 */
		NONE,		/**< \brief default value no valid port */
    };


    /**
     * \brief Constructor - Will initialize the peripheral port and setup the RX and TX buffers
     *
     *  Constructor - Will initialize the peripheral port and setup the RX and TX buffers
     *  Please check the hardware limitations to ensure proper configuration parameters
     *
     *  \param port_t port = NONE			: IN	The hardware port to be used
     *  \param uint16_t baudrate = 115200	: IN	The baudrate of the device. Check the hardware manual for valid values.
     *  \param uint8_t bits = 8				: IN	The number of data bits, typically 7 or 8
     *  \param parity_t parity = NONE		: IN	Parity, ODD, EVEN or NONE
     *  \param uint8_t stopbits = 1			: IN	Number of Stopbits, 1 or 2
     *  \param uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer
     *  \param uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer
     */
    CCanPort(port_t port = NONE,
             uint32_t baudrate = 1000000,
			 uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE,
			 uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE
			 );

private:

	/**
	 * \brief Sends one Package to the hardware
	 *
	 * \return RC_t:
	 * RC_SUCCESS - byte was transmitted
	 * Device specific ErrorCode - in case of error
	 */
	RC_t writePackage_hw(CRingBuffer data);

	/**
	 * \brief Receive one Package from the hardware
	 *
	 * RC_SUCCESS - byte was received
	 * Device specific ErrorCode - in case of error
	 */
	RC_t readPackage_hw(CRingBuffer& dataReadFromHw);

	/**
	 * Get the size of a package for the peripheral
	 * \return packagesize in byte
	 */
	uint16_t getDriverPackageSize();
};

#endif /* CCANPORT_H */
