//============================================================================
// Name        : tp.cpp
// Author      : Santi Aguilera
//============================================================================

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <stdexcept>

class Expression;

#include "threading/Mutex.h"

#include "ParserUtils.h"
#include "Expression.h"

#define ERROR_TYPE_ARGUMENTS "argumentos"
#define ERROR_GENERIC "ERROR: "

#define STATE_SUCCESS 0
#define STATE_WRONG_ARGS 1
#define STATE_BAD_FUNCTION 2

int main(int argc, char *argv[]) {
	ParserUtils parser;
	std::string line;

	//Check if the user send args. If so prompt error
	if (argc > 1) {
		std::cout << ERROR_GENERIC << ERROR_TYPE_ARGUMENTS << std::endl;
		return STATE_WRONG_ARGS;
	}

	/**
	 * Iterate through the file that was input
	 * and for each line run the parser.
	 *
	 * In case an exception is thrown while running
	 * the parser, act on it.
	 */
	while (std::getline(std::cin, line)) {
		try {
			parser.run(line);
		} catch (const std::logic_error &exception) {
			//If the exception was of a malformed func. Print it
			if (exception.what() == EXCEPTION_BAD_FUNCTION) {
				std::cout << ERROR_GENERIC << line << std::endl;
				return STATE_BAD_FUNCTION;
			}
		}
	}

	return STATE_SUCCESS;
}
