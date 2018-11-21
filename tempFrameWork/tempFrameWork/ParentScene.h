#pragma once
class ParentScene
{
public:
	ParentScene();
	virtual ~ParentScene();

	void Initialize();
	void Update();
	void Render();
	void Release();
};

