/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CCANPORT.H
* Author          : Aadarsh Kumar Singh
* Description     : Header file that has APIs to create CAN port and
* 					defines packaging data to be transmitted and received
* 					via CAN port.
****************************************************************************/

#ifndef CCANPORT_H
#define CCANPORT_H

#include "global.h"
#include "CPort.h"
#include "CRingbuffer.h"
#include "CUartPort.h"

/**
 * \brief Default Buffer Size defined for CAN Communication in bytes
 */
#define CAN_DEFAULTBUFFERSIZE 64
/**
 * \brief Maximum number of CAN ports that can be created
 */
#define PORT_CANNMAX 2
/**
 * \brief Maximum size of CAN packets in bytes.
 */
#define CAN_PACKETSIZE 8

/**
 * \brief Class which has APIs to create CAN port and defines packaging data
 *  	  format for transmitting and receiving via CAN port.
 */

class CCanPort : public CPort {

public:

	/**
	 * \brief CAN Port available for creation.
	 */
    enum port_t{
    	CAN1,		/**< \brief CAN Port 1 */              //!< CAN1
		CAN2, 		/**< \brief CAN Port 2 */                //!< CAN2
		NONE,		/**< \brief default value no valid port *///!< NONE
    };


    /**
     * \brief Constructor - Will initialize the peripheral port and setup the RX and TX buffers
     *
     *  Constructor - Will initialize the peripheral port and setup the RX and TX buffers
     *  Please check the hardware limitations to ensure proper configuration parameters
     *
     *  @param port : NONE port_t			: IN	The hardware port to be used
     *  @param baudrate : 115200 uint16_t	: IN	The baudrate of the device. Check the hardware manual for valid values.
     *  @param bufferSizeRx uint16_t        : CAN_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer
     *  @param bufferSizeTx uint16_t        : CAN_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer
     */
    CCanPort(port_t port = NONE,
             uint32_t baudrate = 1000000,
			 uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE,
			 uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE
			 );

	/**
	 * \brief Get the size of a package for the peripheral
	 * @return package size in byte
	 */
	uint16_t getDriverPackageSize();

	~CCanPort();


private:

	/**
	 * \brief Sends one Package to the CAN hardware
	 * @param data that has to be written to hardware
	 * @return RC_t:
	 * RC_SUCCESS - byte was transmitted via CAN
	 */
	RC_t writePackage_hw(CRingBuffer& data);

	/**
	 * \brief Data to be read from hardware is populated in the
	 * 		  Ringbuffer passed as parameter.
	 * @param dataReadFromHw - Data to be read from hardware
	 * @return RC_SUCCESS - byte was received via CAN
	 * 		   RC_NODATA - No data present to recieve
	 */
	RC_t readPackage_hw(CRingBuffer& dataReadFromHw);

};

#endif /* CCANPORT_H */
