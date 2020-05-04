/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.CPP
* Author          : Aadarsh Kumar Singh
* Description     : Source file that defines API to create Ringbuffer of
* 					given size.
****************************************************************************/


//System Include Files
#include <iostream>
#include <ostream>
using namespace std;

//Own Include Files
#include "CRingBuffer.h"

//Method Implementations

/*
 * \brief Creates a ring buffer of given size
 * @param size size of the ringbuffer
 */
CRingBuffer::CRingBuffer(uint16_t size)
{
	cout << "just created buffer having size " << size << endl;

	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	//Todo: check range
	m_size = size;

	m_pBuffer = new uint8_t[size];
}

/*
 * Destructor of the ring buffer
 */
CRingBuffer::~CRingBuffer()
{
	delete[] m_pBuffer;
}

/*
 * \brief API to read the data from the ringbuffer
 * @param data Data which is read from the buffer is copied into
 * 			   the parameter
 * @return RC_SUCCESS : When the data is read successfully.
 * 		   RC_BUFFERUNDERFLOW : when the data read has failed.
 */
RC_t CRingBuffer::read(uint8_t& data)
{
	if (m_fillLevel > 0)
	{
		data = m_pBuffer[m_readIdx++];

		m_readIdx %= m_size;
		m_fillLevel--;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}

}

/*
 * \brief API to write the data in the ringbuffer.
 * @param data Data to be written in the ringbuffer
 * @return ErrorCode : RC_SUCCESS : When Data written successfully.
 * 					   RC_BUFFERUNDERFLOW : when the data written is failed.
 */
RC_t CRingBuffer::write(uint8_t data)
{
	if (m_fillLevel < m_size)
	{
		m_pBuffer[m_writeIdx++] = data;

		m_writeIdx %= m_size;
		m_fillLevel++;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}
}

/*
 * \brief Operator Overloading to enable ostream object to print
 * 		  ringbuffer
 * @param lhs ostream object to output the Ringbuffer data
 * @param rhs Ringbuffer to be displayed
 * @return ostream of Ringbuffer Data
 */
ostream& operator <<(ostream &lhs, const CRingBuffer &rhs)
{
	for (uint16_t index =0 ; index < rhs.m_size; index++)
	{
		lhs << rhs.m_pBuffer[index];
	}
	return lhs;
}

/*
 * \brief API to clear the Ringbuffer
 * @return Error Code : RC_SUCCESS : When Cleared the Buffer successfully.
 */
RC_t CRingBuffer::clear()
{
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	for(int i =0;i<m_size;i++)
		m_pBuffer[i]='\0';

	return RC_SUCCESS;
}

/*
 * \brief To know the index of the buffer untill which the ringbuffer is
 * 		  Filled.
 * @return Fill Level of the buffer
 */
uint16_t CRingBuffer::getFillLevelOfBuffer()
{
	return m_fillLevel ;
}

/*
 * \brief Copy Constructor to provide deep copies
 * @param copyRingBuffer Ringbuffer from which data is copied.
 */
CRingBuffer::CRingBuffer(const CRingBuffer &copyRingBuffer)
{
	this->m_fillLevel =copyRingBuffer.m_fillLevel;
	this->m_pBuffer =copyRingBuffer.m_pBuffer;
	this->m_readIdx =copyRingBuffer.m_readIdx;
	this->m_size =copyRingBuffer.m_size;
	this->m_writeIdx =copyRingBuffer.m_writeIdx;
}
