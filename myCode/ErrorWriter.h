/*
 * ErrorWriter.h
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */

#ifndef ERRORWRITER_H_
#define ERRORWRITER_H_

#include <string>
#include <iostream>

class ErrorWriter
{
private:
	//Generic pointer to any kind of stream
	std::ostream& m_out;
public:

	/**
	 * FileIO
	 */
	ErrorWriter(std::ostream& stream = std::cerr);


	/**
	 * Functor for writing the data
	 * Could also be a specific function
	 * Real advantage comes with templated functions or classes, which will allow interchanging function pointers and functors
	 */
	void operator()(std::string message);

	~ErrorWriter();


};

#endif /* ERRORWRITER_H_ */
