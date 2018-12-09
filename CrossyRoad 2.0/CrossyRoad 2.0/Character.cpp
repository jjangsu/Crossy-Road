#include "Character.h"


Character::Character()
{
}

Character::Character(VECTOR3 vec)
{
	position = vec;
}

Character::~Character()
{
}

void Character::jump(int key)
{
	switch (key)
	{
	case KEYLEFT:


		break;

	case KEYRIGHT:

		break;
	case KEYUP:

		break;
	case KEYDOWN:

		break;
	}
}
