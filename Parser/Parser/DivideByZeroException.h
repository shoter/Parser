#pragma once
#include <exception>
#include <string>

//Blad gdy dzielimy przez zero
//wystepuje w Modulo i Divide (klasie)
class DivideByZeroException : public std::exception
{
public:
	DivideByZeroException(const char * message = "You cannot divide by zero!");
};