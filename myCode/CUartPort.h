/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CUARTPORT.H
* Author          : Aadarsh Kumar Singh
* Description     : Header file that has APIs to create UART port and
* 					defines packaging data to be transmitted and received
* 					via UART port.
*
****************************************************************************/

#ifndef CUARTPORT_H
#define CUARTPORT_H

#include "global.h"
#include "CPort.h"
#include "CRingbuffer.h"

/**
 * \brief Default Buffer Size defined for UART Communication in bytes
 */
#define UART_DEFAULTBUFFERSIZE 20
/**
 * \brief Maximum number of UART ports that can be created
 */
#define PORT_ASCLINMAX 4
/**
 * \brief Maximum size of UART packets in bytes.
 */
#define UART_PACKETSIZE 1

/**
 * \brief Class which has APIs to create UART port and defines packaging data
 *  	  format for transmitting and receiving via UART port.
 */
class CUartPort : public CPort {

public:

    enum port_t{
    	ASCLIN1 = 1 ,	/**< \brief ASCLIN Port 1, per default mapped to USB bridge */
		ASCLIN2, 		/**< \brief ASCLIN Port 2, can be mapped to PIN P12(0),PIN P12(2) */
		ASCLIN3, 		/**< \brief ASCLIN Port 3, can be mapped to PIN P12(3),PIN P12(4) */
		ASCLIN4, 		/**< \brief ASCLIN Port 4, can be mapped to PIN P12(1),PIN P12(5) */
		NONE,			/**< \brief default value no valid port */
    };

    enum parity_t{
    	ODD, 			/**< \brief ODD parity, will detect single bit transmission errors */
		EVEN, 			/**< \brief EVEN parity, will detect single bit transmission errors */
		NOPARITY,		/**< \brief NO parity check, only recommended for baudrates below 115200 */
    };

    /**
     * \brief Constructor - Will initialize the peripheral port and setup the RX and TX buffers
     *
     *  Constructor - Will initialize the peripheral port and setup the RX and TX buffers
     *  Please check the hardware limitations to ensure proper configuration parameters
     *
     *  \param port_t port : NONE			: IN	The hardware port to be used
     *  \param uint16_t baudrate : 115200	: IN	The baudrate of the device. Check the hardware manual for valid values.
     *  \param uint8_t bits : 8				: IN	The number of data bits, typically 7 or 8
     *  \param parity_t parity :NONE		: IN	Parity, ODD, EVEN or NONE
     *  \param uint8_t stopbits : 1			: IN	Number of Stopbits, 1 or 2
     *  \param uint16_t bufferSizeRx 		: UART_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer
     *  \param uint16_t bufferSizeTx  		: UART_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer
     */
    CUartPort(port_t port = NONE,
             uint32_t baudrate = 115200,
             uint8_t bits = 8,
             parity_t parity = NOPARITY,
             uint8_t stopbits = 1,
			 uint16_t bufferSizeRx = UART_DEFAULTBUFFERSIZE,
			 uint16_t bufferSizeTx = UART_DEFAULTBUFFERSIZE
			 );

	/**
	 * Get the size of a package for the peripheral
	 * \return packagesize in byte
	 */
	uint16_t getDriverPackageSize();

	~CUartPort();

private:

	/**
	 * \brief Sends one Package to the UART hardware
	 *
	 * \return RC_t:
	 * RC_SUCCESS - byte was transmitted
	 */
	RC_t writePackage_hw(CRingBuffer& data);

	/**
	 * \brief Receive one Package from the UART hardware
	 *
	 * RC_SUCCESS - byte was received
	 * RC_NODATA  - When no data available for reception
	 */
	RC_t readPackage_hw(CRingBuffer& dataReadFromHw);

};

#endif /* CUARTPORT_H */
