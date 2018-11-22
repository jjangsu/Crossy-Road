#pragma once
class ParentObject
{
protected:
	int direction;
	float size;
	float cx, cy;
	float speed;

public:
	ParentObject();
	virtual ~ParentObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

