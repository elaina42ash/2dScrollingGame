#include "StaticObjectMng/StaticObjectPool.h"
#include "Fwk/Framework.h"

// 後片付け
void StaticObjectPool::Term()
{
	for (int i = 0; i < pool_.size(); i++)
	{
		if (!pool_[i])
			continue;
		pool_[i]->Term();
		SAFE_DELETE(pool_[i]);

	}
	// プールを破棄
	pool_.clear();
}

// オブジェクトを一つ活性化して戻す
StaticObject* StaticObjectPool::Alloc()
{

	StaticObject* pResult = nullptr;

	for (int i = 0; i < pool_.size(); i++)
	{
		if (pool_[i]->IsActive() == false)
		{
			pResult = pool_[i];
			pResult->Enable();
			break;
		}
	}
	return pResult;
}
