
#include <iostream>
using namespace std;


#include "CCanPort.h"

#define CAN_PACKETSIZE 8

CCanPort::CCanPort(port_t port, uint32_t baudrate, uint16_t bufferSizeRx, uint16_t bufferSizeTx) : CPort(bufferSizeTx, bufferSizeRx)
{
}

RC_t CCanPort::writePackage_hw(CRingBuffer data)
{
	cout << "Just wrote to CAN hardware: " << data << endl;
	return RC_SUCCESS;
}


RC_t CCanPort::readPackage_hw(CRingBuffer& dataReadFromHw)
{
	static uint8_t fakeData = 'a';
	static uint16_t counter = 0;
	RC_t errCode = RC_SUCCESS;



	if (counter >= CAN_DEFAULTBUFFERSIZE)
		return RC_NODATA;

	do
	{
		errCode = dataReadFromHw.write(fakeData++);
		counter++;
	}while(errCode == RC_SUCCESS );

	cout << "Just read from CAN hardware: " << dataReadFromHw << endl;

	return RC_SUCCESS;

}

uint16_t CCanPort::getDriverPackageSize()
{
	return (CAN_PACKETSIZE);
}
