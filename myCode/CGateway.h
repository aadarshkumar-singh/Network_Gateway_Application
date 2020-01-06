/*
 * CParser.h
 *
 *  Created on: 01.12.2019
 *      Author: Fromm
 */

#ifndef CPARSER_H_
#define CPARSER_H_

#include "global.h"
#include "CPort.h"
#include "CPortFactory.h"
#include "CentralErrorHandler.h"

class CGateway
{
private:
	CPort* m_portA;
	CPort* m_portB;

	void resetPorts();

public:
	/**
	 * Contructor, using the default factory settings
	 */
	CGateway(CPortFactory::port_t portA,  CPortFactory::port_t portB);

	CGateway(CPort *portA,  CPort* portB);

	RC_t transmitFromAToB();

	virtual ~CGateway();
};

#endif /* CPARSER_H_ */
