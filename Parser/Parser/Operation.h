#pragma once

class Operation
{
public :
	virtual ~Operation() {} //wirtualny destruktor. Dzieki niemu klasy dziedziczace potrafia sie odpowiednio zdestruktorowac XD.
	//czyli usunac swoja pamiec z pamieci. 
	virtual double Result() = 0; //to kazda operacja musi przeladowac. Zwraca wynik operacji. Dodawanie zwroci a + b, liczba zwroci samo a :)
	virtual operator double()
	{
		return Result(); //zeby mozna bylo dokonac niejawnej konwersji na double'a.
	}
};