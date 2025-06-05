#include "DroppedObjectMng/DroppedObjectPool.h"
#include "Fwk/Framework.h"

// 後片付け
void DroppedObjectPool::Term()
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
DroppedObject* DroppedObjectPool::Alloc()
{

	DroppedObject* pResult = nullptr;

	for (int i = 0; i < pool_.size(); i++)
	{
		if (pool_[i]->IsActive() == false)
		{
			pResult = pool_[i];
			pResult->Enable();
			ICollisionComponent* collisionComponent = pResult->GetComponent<ICollisionComponent>();
			if (collisionComponent)
				collisionComponent->EnableCollider();

			break;
		}
	}
	return pResult;
}
