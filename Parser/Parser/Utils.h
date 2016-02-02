#pragma once
#include <math.h>
#include "OperatorType.h"
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
extern double MIN_COMP; //to jest ta tolerancja bledu dla porwnywania liczb zmiennoprzecinkwoych
typedef unsigned int Priority;
//Liczby zmiennoprzecinkowe maja glupia ceche
//maja skonczona dokladnosc. Czesto (!!!) na przyklad 1 nie rowna sie 1 na doublach. Naprawde :)
//dlatego odejmujemy te 2 liczby od siebie, bierzemy z nich wartosc bezwgledna i sprawdzamy jak bardzo sie roznia miedzy soba.
//robimy taka tolerancje bledu tak jakby...
//glownie wykorzystywane do tego by sprawdzic czy liczba jest 0, nie wiem czy gdzie to jeszcze jest uzyte.
inline bool Compare(double x, double y)
{
	return fabs(x - y) < MIN_COMP;
}

//Priorytet wykonywania operacji (mnozenie wykonujemy po dodawaniu etc...)
//nawiasy tutaj musza byc ;-;
//ale maja priorytet najnizszy
inline Priority getOperatorPriority(OperatorType type)
{
	switch (type)
	{
	case OperatorType::LEFTBRACKET: case OperatorType::RIGHTBRACKET:
		return __COUNTER__; //<- to ci dalem aby profsor dal ci wiecej punktow za pomysl XD
		//o co chodzi z __COUNTER__?
		//__COUNTER__ z kazdym uzyciem zwieksza swoja wartosc o 1
		//czyli tutaj ma pewnie wartosc 0
	case OperatorType::ADD : case OperatorType::SUBSTRACT :
		return __COUNTER__; //tutaj 1
	case OperatorType::DIVIDE : case OperatorType::MULTIPLY : case OperatorType::MODULO:
		return __COUNTER__; //tutaj 2
	case OperatorType::POWER :
		return __COUNTER__; //tutaj 3
		//Proste, no nie :D?
	
	default :
		throw std::exception("getOperatorPriority wrong type"); //wywala wyjatek kiedy poda mu sie zly typ operator.
	}
}

//http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
//znalezione na stack overflow. Nie ma sensu wywazac otwartych drzwi
//nie rozumiem co te funkcje znacza XD ale gosc ktory to pisal pewnie rozumie XD
// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}