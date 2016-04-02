/*
 * LispParser.h
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#ifndef LISPPARSER_H_
#define LISPPARSER_H_

class LispParser {
private:
	FILE *inputFile;

public:
	LispParser(std::string fileName);
	virtual ~LispParser();
	void parseLine();
};



#endif /* LISPPARSER_H_ */
