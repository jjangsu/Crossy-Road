#pragma once
#include "ParentObject.h"
class Character:public ParentObject
{
public:
	Character();
	virtual ~Character();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

