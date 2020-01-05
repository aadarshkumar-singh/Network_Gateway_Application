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
	CentralErrorHandler m_errorHandler ;
public:
	/**
	 * Constructor taking explicit port objects
	 */
	CGateway(CPort& portA, CPort& portB,CentralErrorHandler errorHandler);

	/**
	 * Contructor, using the default factory settings
	 */
	CGateway(CPortFactory::port_t portA,  CPortFactory::port_t portB,CentralErrorHandler errorHandler);

	CGateway(CPort *portA,  CPort* portB , CentralErrorHandler errorHandler);

	RC_t transmitFromAToB();

	virtual ~CGateway();
};

#endif /* CPARSER_H_ */
