/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H

#include "global.h"
#include <iostream>
using namespace std;

class CRingBuffer {
private:
	uint8_t* m_pBuffer;
	uint16_t m_size;
	uint16_t m_readIdx;
	uint16_t m_writeIdx;
	uint16_t m_fillLevel;
public:

    CRingBuffer(uint16_t size = 10);
    CRingBuffer(const CRingBuffer &copyRingBuffer);
    ~CRingBuffer();
    friend ostream& operator <<(ostream &lhs , const CRingBuffer& rhs);
    RC_t read(uint8_t& data);
    uint16_t getFillLevelOfBuffer();
    RC_t write(uint8_t data);
    RC_t clear();

};

ostream& operator <<(ostream &lhs , const CRingBuffer& rhs);

/********************
**  CLASS END
*********************/
#endif /* CRINGBUFFER_H */
