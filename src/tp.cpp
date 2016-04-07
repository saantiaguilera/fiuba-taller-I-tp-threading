//============================================================================
// Name        : tp.cpp
// Author      : Santi Aguilera
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <list>
#include <map>

class Expression;

#include "ParserUtils.h"
#include "Expression.h"

int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!

	//arithmetic
	//std::string a = "(+ 2 3 (* 5 2) (- 2 (/ 6 3)))"; //Returns 15

	//logicals
	//std::string a = "(= (+ 5 7) (* 6 2) (- 24 10))"; //Returns ()
	//std::string a = "(= (+ 5 7) (* 6 2) (- 24 12))"; //Returns 1
	//std::string a = "(> (* 5 10000) (* 4 2))"; //< Returns () ; > Returns 1

	//lists
	//std::string a = "(list 5 2 3 4 (+ 1 2) (* 8 7))"; //Returns size 6
	//std::string a = "(car 5 2 3 4 (+ 1 2) (* 8 7))"; //Returns size 1
	//std::string a = "(cdr 5 2 3 4 (+ 1 2) (* 8 7))"; //Returns size 5
	//std::string a = "(append (list 50 12 43 84 (- 159 208)) (list 1 (* 2 5) 3 4))"; //Returns size 9
	//std::string a = "(append (car (list 1 (* 2 4) 3 4)) (cdr 4 5 (- 8 4)))"; //Return size 3

	//if
	//std::string a = "(if (list) 2 3)"; //Returns 3
	//std::string a = "(if (car 4 5 6 7) (* 5 (+ 1 3)) 5000)"; //Returns 20

	//print
	//std::string a = "(print \"HOLA VIEJA\" (* 5 2) (+ 4 (- 3 1)))"; //Returns "HOLA VIEJA 10 6"
	//std::string a = "(print 45 (if 1 46 47))"; //Returns "45 46"
	//std::string a = "(print \"HOLA\" (if 1 46 47))"; //Returns "HOLA 46"
	//std::string a = "(print \"HOLA\" (if 1 \"HOLA\" \"CHAU\"))"; //Returns "HOLA HOLA"

	//setq
	/* std::string a = "(setq var1 (+ (* 8 (/ 4 2)) 4))"; //Var1 = 20
	std::string b = "(/ var1 (+ (list 1 2 3 4)))"; //Returns 2 */
	/* std::string a = "(setq abcdef (/ 4 (car (list 2 3 4))))"; // abcdef = 2
	std::string b = "(print \"abcdef = \" abcdef)"; //Returns "abcdef = 2" */
	/*std::string a = "(setq variableName (if (list) 1 (+ (- 8 4 2) (/ 16 2))))"; //variableName = 10
	std::string b = "(- variableName 120)"; //Returns -110 */

	//defunc - Recursive is impossible with this design (and I thought about it and I think
	//Its still damn hard with most of designs. So no recursivness for defunc :(
	/*std::string a = "(defun pow2 (var) (* var var))";
	std::string b = "(pow2 4)"; //Return 16; */
	/*std::string a = "(defun op1 (lista) (+ (cdr lista)))";
	std::string b = "(setq valores (list 1 2 3 4 5 6 7 8 9))";
	std::string c = "(print (op1 valores))"; //Return 44; */
	std::string a = "(defun caar (ENV) (car (car ENV)))";
	std::string b = "(defun condicional (ENV) (if ENV (caar (list ENV 2 3 4 5)) 1234))";
	std::string c = "(print (condicional (list 1 2 3 4)))";

	std::cout << "Lets parse: " << a << std::endl;
	std::cout << "Lets parse: " << b << std::endl;
	std::cout << "Lets parse: " << c << std::endl;

	ParserUtils parser;
	parser.run(a);
	parser.run(b);
	parser.run(c);
	parser.run(c);

	return 0;
}
