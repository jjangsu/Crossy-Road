#pragma once
class ParentObject
{
public:
	ParentObject();
	virtual ~ParentObject();

	void Initialize();
	void Update();
	void Render();
	void Release();
};

