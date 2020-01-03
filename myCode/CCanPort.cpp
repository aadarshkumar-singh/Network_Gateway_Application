
#include <iostream>
using namespace std;


#include "CCanPort.h"

CCanPort::CCanPort(port_t port, uint32_t baudrate, uint16_t bufferSizeRx, uint16_t bufferSizeTx) : CPort(bufferSizeTx, bufferSizeRx)
{
}
RC_t CCanPort::writeByte_hw(uint8_t data)
{
	cout << "Just wrote to CAN hardware: " << data << endl;
	return RC_SUCCESS;
}
RC_t CCanPort::readByte_hw(uint8_t &data)
{
	static uint8_t fakeData = 'A';
	static uint16_t counter = 0;

	counter++;

	if (counter >= 20) return RC_NODATA;

	data = fakeData++;

	cout << "Just read from CAN hardware: " << data << endl;

	return RC_SUCCESS;
}
