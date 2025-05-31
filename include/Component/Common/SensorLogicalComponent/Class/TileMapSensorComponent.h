#pragma once
#include "SensorLogicalComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ICollisionComponent.h"
#include "Component/Common/SensorLogicalComponent/Interface/ITileMapSensorComponent.h"
#pragma warning(push)
#pragma warning(disable:4250)
class TileMapSensorComponent : public SensorLogicalComponent, public ITileMapSensorComponent
{
protected:
	Inject<ICollisionComponent> collisionComponent_;

public:
	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	bool IsInsideWall(const Vector2f& _position) const override = 0;

protected:
	TileMapSensorComponent(bool _isActive, IMessenger* _messenger);

	explicit TileMapSensorComponent(IMessenger* _messenger);

	void Reset() override;

};
#pragma warning(pop)