
#include <iostream>
using namespace std;


#include "CCanPort.h"


CCanPort::CCanPort(port_t port, uint32_t baudrate, uint16_t bufferSizeRx, uint16_t bufferSizeTx) : CPort(bufferSizeTx, bufferSizeRx)
{
}

RC_t CCanPort::writePackage_hw(CRingBuffer& data)
{
	cout << "Just wrote to CAN hardware: " << data << endl;
	return RC_SUCCESS;
}

CCanPort::~CCanPort()
{
	//cout <<"Destroy the Can Port"<<endl;
}

RC_t CCanPort::readPackage_hw(CRingBuffer& dataReadFromHw)
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
			cout << "Just read from CAN hardware: " << dataReadFromHw << endl;
			fakeData = 'a';
			counter = 0;
			return RC_NODATA;
		}
	}

	cout << "Just read from CAN hardware: " << dataReadFromHw << endl;

	return RC_SUCCESS;

}

uint16_t CCanPort::getDriverPackageSize()
{
	return (CAN_PACKETSIZE);
}
