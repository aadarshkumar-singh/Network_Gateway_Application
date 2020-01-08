

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
#include <ostream>
using namespace std;

//Own Include Files
#include "CRingBuffer.h"

//Method Implementations

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


CRingBuffer::~CRingBuffer()
{
	delete[] m_pBuffer;
}

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

ostream& operator <<(ostream &lhs, const CRingBuffer &rhs)
{
	for (uint16_t index =0 ; index < rhs.m_size; index++)
	{
		lhs << rhs.m_pBuffer[index];
	}
	return lhs;
}

RC_t CRingBuffer::clear()
{
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	for(int i =0;i<m_size;i++)
		m_pBuffer[i]='\0';

	return RC_SUCCESS;
}

uint16_t CRingBuffer::getFillLevelOfBuffer()
{
	return m_fillLevel ;
}

CRingBuffer::CRingBuffer(const CRingBuffer &copyRingBuffer)
{
	this->m_fillLevel =copyRingBuffer.m_fillLevel;
	this->m_pBuffer =copyRingBuffer.m_pBuffer;
	this->m_readIdx =copyRingBuffer.m_readIdx;
	this->m_size =copyRingBuffer.m_size;
	this->m_writeIdx =copyRingBuffer.m_writeIdx;
}
