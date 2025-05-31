#pragma once
#include "GameObject/StaticObject.h"

class StaticObjectPool {
public:
	template <class T>
	void Init(int _poolSize) {
		for (int i = 0; i < _poolSize; i++)
		{
		
			StaticObject* newStaticObject = new T();
		
			newStaticObject->Init();

			// 最初は非アクティブ
			newStaticObject->Disable();
			// プールにアドレスを記録しておく
			pool_.push_back(newStaticObject);
		}
	}

	void Term();

	StaticObject* Alloc();

protected:
	std::vector<StaticObject*> pool_;
};
