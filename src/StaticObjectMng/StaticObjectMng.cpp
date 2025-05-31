#include "StaticObjectMng/StaticObjectMng.h"

#include "GameObject/StaticObject/IronSpike.h"

void StaticObjectMng::Init() {

	activeStaticObject_.clear();
}

void StaticObjectMng::Term() {
	
	activeStaticObject_.clear();
	
	DestroyPoolAll();
}

void StaticObjectMng::Update() {
	for (int i = 0; i < activeStaticObject_.size(); i++)
	{
		activeStaticObject_[i]->Update();
	}

	for (int i = 0; i < activeStaticObject_.size();)
	{
		if (activeStaticObject_[i]->IsActive())
		{
			++i;
		}
		else
		{
			activeStaticObject_.erase(activeStaticObject_.begin() + i);

		}
	}
}

void StaticObjectMng::Render() {
	for (int i = 0; i < activeStaticObject_.size(); i++)
	{
		activeStaticObject_[i]->Render();
	}
}


void StaticObjectMng::GeneratePool(const char* _staticObjectName, int _poolSize) {
	if (strcmp(_staticObjectName,"IronSpike")==0)
	{
		staticObjectPools_[_staticObjectName].Init<IronSpike>(_poolSize);
	}
}

void StaticObjectMng::DestroyPool(const char* _staticObjectName)
{
	if (staticObjectPools_.count(_staticObjectName) > 0)
	{
		staticObjectPools_[_staticObjectName].Term();
		staticObjectPools_.erase(_staticObjectName);
	}

}

StaticObject* StaticObjectMng::CreateStaticObject(const char* _staticObjectName, Lib::Math::Vector2f _position)
{
	StaticObject* staticObject = nullptr;

	if (staticObjectPools_.count(_staticObjectName) > 0)
	{
		staticObject = staticObjectPools_[_staticObjectName].Alloc();
	}

	if (staticObject == nullptr)
	{
		return nullptr;
	}


	ITransformComponent* transformComponent = staticObject->GetComponent<ITransformComponent>();
	if (transformComponent)
		transformComponent->MoveTo(_position);

	activeStaticObject_.push_back(staticObject);

	return staticObject;
}

void StaticObjectMng::CreateStaticObjects(CSVData* _csvData, int _tileSize)
{
	if (_csvData == nullptr)
		return;

	int staticObjectNum = _csvData->GetElementCount() / 3;

	for (int i = 0; i < staticObjectNum; i++)
	{
		int index = i * 3;
		std::string staticObjectName;
		_csvData->GetString(index, &staticObjectName);

		float gridX = _csvData->GetFloat(index + 1);
		float gridY = _csvData->GetFloat(index + 2);

		Vector2f position;
		position.x = gridX * _tileSize;
		position.y = -gridY * _tileSize;

		// 敵を生成
		CreateStaticObject(staticObjectName.c_str(), position);
	}
}

int StaticObjectMng::GetStaticObjectCount()
{
	return static_cast<int>(activeStaticObject_.size());
}


void StaticObjectMng::DestroyPoolAll() {
	DestroyPool("IronSpike");
}


