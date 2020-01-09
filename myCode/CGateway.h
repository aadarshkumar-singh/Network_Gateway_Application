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
#include <vector>
#include <algorithm>
class CGateway
{
private:

	/**
	 * \brief Generic Communication port A to establish Gateway communication.
	 */
	CPort* m_portA;
	/**
	 * \brief Generic Communication port B to establish Gateway communication.
	 */
	CPort* m_portB;
	/**
	 * \brief Vector that stores the address of ports that are opened
	 * 		  for establishing gateway communication.
	 */
	static std::vector <CPort*> m_OpenedPorts;

	/**
	 * \brief API to decrement the count of the communication ports
	 * 		  When the port is not used by the gateway object
	 *
	 * @param None
	 */
	void resetPorts();

	/**
	 * \brief API which checks if a valid port is opened for establishing
	 * 		  communication via Gateway Object.
	 * 		  It checks if the port is already opened and if it is already
	 * 		  used by gateway object
	 *
	 * @param  port : Pointer to the communication port like CAN/UART
	 * @return true : If the port is not used by any other gateway object
	 * 				  and can be used for establishing communication.
	 * 		   false : If the port is already opened and is already
	 * 		  			used by gateway object
	 */
	bool checkIfOpeningValidPort(CPort* port);

public:
	/**
	 * Contructor, using the default factory settings
	 */
	CGateway(CPortFactory::port_t portA,  CPortFactory::port_t portB);

	/**
	 * \brief Constructor that accepts the pointer arguments
	 * 		  and creates a gateway object if ports are valid.
	 *
	 * @param portA : Pointer to first communication port
	 * @param portB : Pointer to second communication port
	 *
	 * \note : In case the ports are invalid:
	 * 			Null/Invalid : error message of Invalid pointer is printed and program is terminated.
	 * 			Invalid Port : error message of Invalid port is printed and program is terminated.
	 */
	CGateway(CPort *portA,  CPort* portB);

	/**
	 * Transmits the data from communication port A to Communication port B.
	 *
	 * @return error code : RC_ERROR : if error in transmitting data
	 * 						RC_SUCCESS : if transmission is successfull.
	 */
	RC_t transmitFromAToB();

	virtual ~CGateway();
};

#endif /* CPARSER_H_ */
