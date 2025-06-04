#pragma once
#include "GameObject/DroppedObject/DroppedObject.h"

class DroppedObjectPool {
public:
	template <class T>
	void Init(int _poolSize) {
		for (int i = 0; i < _poolSize; i++)
		{

			DroppedObject* newDroppedObject = new T();

			newDroppedObject->Init();

			// 最初は非アクティブ
			newDroppedObject->Disable();
			// プールにアドレスを記録しておく
			pool_.push_back(newDroppedObject);
		}
	}

	void Term();

	DroppedObject* Alloc();

protected:
	std::vector<DroppedObject*> pool_;
};
