#include "DroppedObjectMng/DroppedObjectMng.h"

#include "GameObject/DroppedObject/DroppedKatana.h"
#include "GameObject/DroppedObject/DroppedSword.h"


void DroppedObjectMng::Init() {

	activeDroppedObject_.clear();
}

void DroppedObjectMng::Term() {

	activeDroppedObject_.clear();

	DestroyPoolAll();
}

void DroppedObjectMng::Update() {
	for (int i = 0; i < activeDroppedObject_.size(); i++)
	{
		activeDroppedObject_[i]->Update();
	}

	for (int i = 0; i < activeDroppedObject_.size();)
	{
		if (activeDroppedObject_[i]->IsActive())
		{
			++i;
		}
		else
		{
			activeDroppedObject_.erase(activeDroppedObject_.begin() + i);

		}
	}
}

void DroppedObjectMng::Render() {
	for (int i = 0; i < activeDroppedObject_.size(); i++)
	{
		activeDroppedObject_[i]->Render();
	}
}


void DroppedObjectMng::GeneratePool(const char* _droppedObjectName, int _poolSize) {
	if (strcmp(_droppedObjectName, "Sword") == 0)
	{
		droppedObjectPools_[_droppedObjectName].Init<DroppedSword>(_poolSize);
	}

	if (strcmp(_droppedObjectName, "Katana") == 0)
	{
		droppedObjectPools_[_droppedObjectName].Init<DroppedKatana>(_poolSize);
	}
}

void DroppedObjectMng::DestroyPool(const char* _droppedObjectName)
{
	if (droppedObjectPools_.count(_droppedObjectName) > 0)
	{
		droppedObjectPools_[_droppedObjectName].Term();
		droppedObjectPools_.erase(_droppedObjectName);
	}

}

DroppedObject* DroppedObjectMng::CreateDroppedObject(const char* _droppedObjectName, Lib::Math::Vector2f _position, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI)
{
	DroppedObject* droppedObject = nullptr;

	if (droppedObjectPools_.count(_droppedObjectName) > 0)
	{
		droppedObject = droppedObjectPools_[_droppedObjectName].Alloc();
	}

	if (droppedObject == nullptr)
	{
		return nullptr;
	}

	droppedObject->BindSceneGameplayAPI(_sceneGameplayAPI);

	droppedObject->BindSceneContext(_sceneContext);

	ITransformComponent* transformComponent = droppedObject->GetComponent<ITransformComponent>();
	if (transformComponent)
		transformComponent->MoveTo(_position);

	activeDroppedObject_.push_back(droppedObject);

	return droppedObject;
}

void DroppedObjectMng::CreateDroppedObjects(CSVData* _csvData, int _tileSize, ISceneContext* _sceneContext, ISceneGameplayAPI* _sceneGameplayAPI)
{
	if (_csvData == nullptr)
		return;

	int droppedObjectNum = _csvData->GetElementCount() / 3;

	for (int i = 0; i < droppedObjectNum; i++)
	{
		int index = i * 3;
		std::string droppedObjectName;
		_csvData->GetString(index, &droppedObjectName);

		float gridX = _csvData->GetFloat(index + 1);
		float gridY = _csvData->GetFloat(index + 2);

		Vector2f position;
		position.x = gridX * _tileSize;
		position.y = -gridY * _tileSize;

		CreateDroppedObject(droppedObjectName.c_str(), position, _sceneContext, _sceneGameplayAPI);
	}
}

int DroppedObjectMng::GetDroppedObjectCount()
{
	return static_cast<int>(activeDroppedObject_.size());
}


void DroppedObjectMng::DestroyPoolAll() {
	DestroyPool("Sword");
	DestroyPool("Katana");
}


