
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CUARTPORT.CPP
* Author          : Aadarsh Kumar Singh
* Description     : Source file that has APIs to create UART port and
* 					defines packaging data to be transmitted and received
* 					via UART port.
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

RC_t CUartPort::writePackage_hw(CRingBuffer& data)
{
	cout << "Just wrote to UART hardware: " << data << endl;
	return RC_SUCCESS;
}

RC_t CUartPort::readPackage_hw(CRingBuffer& dataReadFromHw)
{
	static uint8_t fakeData = 'a';
	static uint16_t counter = 0;

	dataReadFromHw.clear();
	while(dataReadFromHw.write(fakeData) == RC_SUCCESS)
	{
		++fakeData;
		++counter;
		if (counter >= 20)
		{
			cout << "Just read from UART hardware: " << dataReadFromHw << endl;
			fakeData = 'a';
			counter = 0;
			return RC_NODATA;
		}
	}

	cout << "Just read from UART hardware: " << dataReadFromHw << endl;
	return RC_SUCCESS;

}

uint16_t CUartPort::getDriverPackageSize()
{
	return (UART_PACKETSIZE);
}

CUartPort::~CUartPort()
{
	//cout <<"Destroyed UART Port"<<endl;
}
