#pragma once
#include "Add.h"

class Substract : public Add //odejmowanie to to samo co dodawanie :). tylko dodajemy ujemna liczbe
{
public:
	Substract(Operation &lhm, Operation &rhm);
	virtual double Result() override;
};