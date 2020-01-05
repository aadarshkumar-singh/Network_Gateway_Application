/*
 * CentralErrorHandler.h
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */

#ifndef CENTRALERRORHANDLER_H_
#define CENTRALERRORHANDLER_H_

#include <string>

#include "global.h"
#include "ErrorWriter.h"
#include "CentraErrorHandler_cfg.h"

class CentralErrorHandler
{
public:
	/**
	 *  Type definitions for the function pointers
	 */
	typedef void (*fct_out_t) (std::string errMsg);
	typedef void (*fct_terminate_t) ();


private:

	ErrorWriter& m_outFct;
	fct_terminate_t m_terminateFct;

public:

	/**
	 * Constructor, taking two configuration parameters identifying the functions which will be called in error case
	 */
	CentralErrorHandler(ErrorWriter& errorFct, fct_terminate_t terminateFct = 0);

	/**
	 * Report function
	 * Enum values for the argument are defined in the configuration file
	 */
	RC_t report(CEH_source_t err);

	void operator=(CentralErrorHandler &handler);

};

#endif /* CENTRALERRORHANDLER_H_ */
