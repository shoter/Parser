#pragma once
#include <string>
#include "typedefs.h"


class ONP
{
public:
	ONP(const char *expression); //zwykly konstruktor, nie wiele robi, const po to by nie zmieniac expression ktore zostalo nam dane
	double Calculate(); //zwraca wynik expression (na przyklad "1 + 2" to zwroci nam 3)

	operator double();

	std::string onpExpression; //globalna zmienna, przechowuje expression zapisane w postaci odwrotnej notacji polskiej
	
private:
	void convertToONP(const std::string &expr, uint &position, std::string & out); //zmienia podanme expr na odwrotna notacje polska
	double calculateONP(const std::string &onp); //oblicza wynik z odwrotnej notacji polskiej
	std::string expression;
	
	
};