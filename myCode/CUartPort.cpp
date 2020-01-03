
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CUARTPORT.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;

//Own Include Files
#include "CUartPort.h"
#include "CRingBuffer.h"

//Method Implementations



CUartPort::CUartPort(port_t port, uint32_t baudrate, uint8_t bits,
		parity_t parity, uint8_t stopbits, uint16_t bufferSizeRx,
		uint16_t bufferSizeTx) : CPort(bufferSizeTx, bufferSizeRx)
{
}

RC_t CUartPort::writeByte_hw(uint8_t data)
{
	cout << "Just wrote to UART hardware: " << data << endl;
	return RC_SUCCESS;
}

RC_t CUartPort::readByte_hw(uint8_t &data)
{
	static uint8_t fakeData = 'a';
	static uint16_t counter = 0;

	counter++;

	if (counter >= 20) return RC_NODATA;

	data = fakeData++;

	cout << "Just read from UART hardware: " << data << endl;

	return RC_SUCCESS;
}
