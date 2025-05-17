#pragma once
#include "SensorLogicalComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ITileMapSensorComponent.h"
#include "GameObjectMng/IEnvironmentQuery.h"
#pragma warning(push)
#pragma warning(disable:4250)
class TileMapSensorComponent : public SensorLogicalComponent, public ITileMapSensorComponent
{
protected:
	Inject<ICollisionComponent> collisionComponent_;
	Inject<IEnvironmentQuery> environmentQuery_;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	float GetTileSize() const override;

	Vector2f GetMapSize() const override;

	bool IsInsideWall(const Vector2f& _position) const override;

	void InjectEnvironmentQuery(IEnvironmentQuery* _environmentQuery);

protected:
	TileMapSensorComponent(bool _isActive, IMessenger* _messenger);

	explicit TileMapSensorComponent(IMessenger* _messenger);

	void Reset() override;


};
#pragma warning(pop)