/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORT.H
* Author          : Aadarsh Kumar Singh
* Description     : Header file that defines APIs to store the transmission
* 					and reception data in a ring buffer when establishing
* 					communication between ports via Gateway.
*
****************************************************************************/

#ifndef CPORT_H
#define CPORT_H

#include "global.h"
#include "CRingBuffer.h"
#include <string>

/**
 * \brief Base class which defines API to store the transmission
* 		  and reception data in a ring buffer when establishing
* 		  communication between ports via Gateway
*/
class CPort
{
protected:
    /**
     * \brief Ring buffer to store Transmission data
     */
    CRingBuffer m_ringBufferTx;


    /**
     * \brief Ring buffer to store Reception data
     */
    CRingBuffer m_ringBufferRx;
public:

    /**
     * \brief Creates Transmission and reception buffer of given size
     * @param txSize Transmit Buffer size
     * @param rxSize Receive Buffer Size
     */
    CPort(uint16_t txSize = 10, uint16_t rxSize = 10);


    /**
     * \brief Sends one Byte to the buffer
     *
     * \param data string	: IN	Byte to be transmitted
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted
     * 		 RC_BUFFEROVERFLOW - in case of full buffer
     */
    RC_t writeByteStream(std::string const& data);

    /**
     * \brief Receive one Byte from the buffer
     *
     * @param data string&	: OUT	Byte received
     * @return RC_t:
     * 		 RC_SUCCESS - byte was received
     * 		 RC_BUFFERUNDERFLOW - in case of empty buffer
     */
    RC_t readByteStream(std::string& data);

    /**
     * \brief Will transmit all data from TX buffer to hardware
     * @return RC_t
     * 		RC_SUCCESS - all ok
     * 		Specific error code in case of error
     */
    RC_t portTx_isr();

    /**
     * \brief Will transmit all data from RX hardware to buffer
     * @return
     * 		RC_SUCCESS - all ok
     * 		Specific error code in case of error
     */
    RC_t portRx_isr();

    /**
     * \brief Destructor of the Port
     */
    virtual ~CPort();

	/**
	 * \brief Get the size of a package for the peripheral
	 * @return package size in byte
	 */
    virtual uint16_t getDriverPackageSize() = 0;

private:

	/**
	 * \brief Sends one Package to the  hardware
	 * @param data that has to be written to hardware
	 * @return RC_t:
	 * RC_SUCCESS - byte was transmitted
	 */
    virtual RC_t writePackage_hw(CRingBuffer& data) = 0;

    /**
	 * \brief Data to be read from hardware is populated in the
	 * 		  Ringbuffer passed as parameter.
	 * @param data - Data to be read from hardware
	 * @return RC_SUCCESS - byte was received
	 * 		   RC_NODATA - No data present to recieve
	 */
    virtual RC_t readPackage_hw(CRingBuffer& data) = 0;

};
/********************
**  CLASS END
*********************/
#endif /* CPORT_H */
