#pragma once
#include "Character.h"

class Car : public Character
{
private:
	VECTOR3 direction;

public:
	Car();
	Car(VECTOR3 vec);
	~Car();
};

