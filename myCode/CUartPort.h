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

	/**
	 * \brief UART Port available for creation.
	 */
	enum port_t{
		ASCLIN1 = 1 ,	/**< \brief ASCLIN Port 1, per default mapped to USB bridge */   //!< ASCLIN1
		ASCLIN2, 		/**< \brief ASCLIN Port 2, can be mapped to PIN P12(0),PIN P12(2) *///!< ASCLIN2
		ASCLIN3, 		/**< \brief ASCLIN Port 3, can be mapped to PIN P12(3),PIN P12(4) *///!< ASCLIN3
		ASCLIN4, 		/**< \brief ASCLIN Port 4, can be mapped to PIN P12(1),PIN P12(5) *///!< ASCLIN4
		NONE,			/**< \brief default value no valid port */                             //!< NONE
	};

	/**
	 * \brief Type of Parity for the UART port
	 */
	enum parity_t{
		ODD, 			/**< \brief ODD parity, will detect single bit transmission errors */         //!< ODD
		EVEN, 			/**< \brief EVEN parity, will detect single bit transmission errors */       //!< EVEN
		NOPARITY,		/**< \brief NO parity check, only recommended for baudrates below 115200 *///!< NOPARITY
	};

	/**
	 * \brief Constructor - Will initialize the peripheral port and setup the RX and TX buffers
	 *
	 *  Constructor - Will initialize the peripheral port and setup the RX and TX buffers
	 *  Please check the hardware limitations to ensure proper configuration parameters
	 *
	 *  @param port : NONE port_t			: IN	The hardware port to be used
	 *  @param baudrate : 115200 uint16_t	: IN	The baudrate of the device. Check the hardware manual for valid values.
	 *  @param bits : 8 uint8_t				: IN	The number of data bits, typically 7 or 8
	 *  @param parity : NONE parity_t		: IN	Parity, ODD, EVEN or NONE
	 *  @param stopbits : 1 uint8_t			: IN	Number of Stopbits, 1 or 2
	 *  @param bufferSizeRx uint16_t        : CAN_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer
	 *  @param bufferSizeTx uint16_t        : CAN_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer
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
	 * \brief Get the size of a package for the peripheral
	 * @return package size in byte
	 */
	uint16_t getDriverPackageSize();

	/**
	 * \brief Destructor of the UART port
	 */
	~CUartPort();

private:

	/**
	 * \brief Sends one Package to the UART hardware
	 * @param data that has to be written to hardware
	 * @return RC_t:
	 * RC_SUCCESS - byte was transmitted via UART
	 */
	RC_t writePackage_hw(CRingBuffer& data);

	/**
	 * \brief Data to be read from hardware is populated in the
	 * 		  Ringbuffer passed as parameter.
	 * @param dataReadFromHw - Data to be read from hardware
	 * @return RC_SUCCESS - byte was received via UART
	 * 		   RC_NODATA - No data present to recieve
	 */
	RC_t readPackage_hw(CRingBuffer& dataReadFromHw);

};

#endif /* CUARTPORT_H */
