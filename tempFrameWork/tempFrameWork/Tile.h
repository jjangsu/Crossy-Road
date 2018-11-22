#pragma once
#include "ParentObject.h"
class Tile:public ParentObject
{
public:
	Tile();
	~Tile();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

