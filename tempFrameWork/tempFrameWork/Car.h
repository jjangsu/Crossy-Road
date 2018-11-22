#pragma once
#include "ParentObject.h"
class Car: public ParentObject
{
public:
	Car();
	virtual ~Car();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

