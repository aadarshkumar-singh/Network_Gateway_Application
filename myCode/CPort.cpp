
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORT.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
using namespace std;


//Own Include Files
#include "CPort.h"


//Method Implementations



CPort::CPort(uint16_t txSize, uint16_t rxSize) : m_ringBufferTx(txSize), m_ringBufferRx(rxSize)
{
}



RC_t CPort::writeByteStream(string const& data)
{
	RC_t result = RC_ERROR;

	for (uint16_t i = 0; i < data.length(); i++)
	{
		result = m_ringBufferTx.write(data[i]);

		if (RC_SUCCESS != result) return RC_ERROR;
	}

	//Fire TX interrupt
	portTx_isr();

	return result;


}

RC_t CPort::readByteStream(string &data)
{
	string dataFromDriver="";

	RC_t result = RC_ERROR;
	do
	{
		uint8_t ldata = 0;
		result = m_ringBufferRx.read(ldata);
		if (RC_SUCCESS == result)
		{
			dataFromDriver += (char)ldata;
		}
	} while (RC_SUCCESS == result);

	data = dataFromDriver;

	return RC_SUCCESS;
}

RC_t CPort::portTx_isr()
{
	RC_t result = RC_ERROR;
	uint16_t packageSize = getDriverPackageSize();
	CRingBuffer dataWriteToHw(packageSize);
	//uint16_t packageFillLevel = 0;
	do
	{
		uint8_t data = 0;
		result = m_ringBufferTx.read(data);
		if (RC_SUCCESS == result)
		{
			dataWriteToHw.write(data);
			if (dataWriteToHw.getFillLevelOfBuffer()== packageSize)
			{
				writePackage_hw(dataWriteToHw);
				dataWriteToHw.clear();
			}
		}
		else
		{
			if(dataWriteToHw.getFillLevelOfBuffer()>0)
				writePackage_hw(dataWriteToHw);
		}
	} while (RC_SUCCESS == result);



	//Todo: real error handling to be added later
	return RC_SUCCESS;
}

RC_t CPort::portRx_isr()
{
	//Todo: real error handling to be added later
	RC_t result = RC_ERROR;
	uint8_t data = 0;
	CRingBuffer dataReadFromHw(getDriverPackageSize());
	uint16_t packageFillLevel = 0;
	do
	{
		result = readPackage_hw(dataReadFromHw);
		packageFillLevel = dataReadFromHw.getFillLevelOfBuffer();

		if (RC_SUCCESS == result)
		{
			for (uint16_t index = 0; index<packageFillLevel;index++)
			{
				dataReadFromHw.read(data);
				m_ringBufferRx.write(data);
			}
		}

	} while (RC_SUCCESS == result);

	return RC_SUCCESS;

}
