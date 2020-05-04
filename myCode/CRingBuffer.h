/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.H
* Author          : Aadarsh Kumar Singh
* Description     : Header file that declares API to create Ringbuffer of
* 					given size.
*
****************************************************************************/

#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H

#include "global.h"
#include <iostream>
using namespace std;

/**
 * \brief Class that Defines APIs to create Ring buffer of given size.
 */
class CRingBuffer {
private:

	/**
	 * \brief Pointer that stores the address of buffer of given size
	 */
	uint8_t* m_pBuffer;

	/**
	 * \brief Size of the buffer
	 */

	uint16_t m_size;
	/**
	 * \brief Index that indicates the buffer index untill which
	 * 		  Buffer is read.
	 */
	uint16_t m_readIdx;

	/**
	 * \brief Index that indicates the buffer index untill which
	 * 		  Buffer is written.
	 */
	uint16_t m_writeIdx;

	/**
	 * \brief Index that indicates the buffer index untill which
	 * 		  Buffer is filled.
	 */
	uint16_t m_fillLevel;
public:


	/**
	 * \brief Creates a ring buffer of given size
	 * @param size size of the ringbuffer
	 */
    CRingBuffer(uint16_t size = 10);

    /**
	 * \brief Copy Constructor to provide deep copies
	 * @param copyRingBuffer Ringbuffer from which data is copied.
	 */
    CRingBuffer(const CRingBuffer &copyRingBuffer);

    /**
     * Destructor of the ring buffer
     */
    ~CRingBuffer();

    /**
     * \brief Operator Overloading to enable ostream object to print
     * 		  ringbuffer
     * @param lhs ostream object to output the Ringbuffer data
     * @param rhs Ringbuffer to be displayed
     * @return ostream of Ringbuffer Data
     */
    friend ostream& operator <<(ostream &lhs , const CRingBuffer& rhs);

    /**
     * \brief API to read the data from the ringbuffer
     * @param data Data which is read from the buffer is copied into
     * 			   the parameter
     * @return RC_SUCCESS : When the data is read successfully.
     * 		   RC_BUFFERUNDERFLOW : when the data read has failed.
     */
    RC_t read(uint8_t& data);

    /**
     * \brief To know the index of the buffer untill which the ringbuffer is
     * 		  Filled.
     * @return Fill Level of the buffer
     */
    uint16_t getFillLevelOfBuffer();

    /**
     * \brief API to write the data in the ringbuffer.
     * @param data Data to be written in the ringbuffer
     * @return ErrorCode : RC_SUCCESS : When Data written successfully.
     * 					   RC_BUFFERUNDERFLOW : when the data written is failed.
     */
    RC_t write(uint8_t data);

    /**
     * \brief API to clear the Ringbuffer
     * @return Error Code : RC_SUCCESS : When Cleared the Buffer successfully.
     */
    RC_t clear();

};

ostream& operator <<(ostream &lhs , const CRingBuffer& rhs);

/********************
**  CLASS END
*********************/
#endif /* CRINGBUFFER_H */
