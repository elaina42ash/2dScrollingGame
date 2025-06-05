#pragma once
#include "Component/Common/SensorLogicalComponent/Class/TileMapSensorComponent.h"
#include "GameObject/DroppedObject/IDroppedObjectView.h"

#pragma warning(push)
#pragma warning(disable:4250)
class AppleTileMapSensorComponent : public TileMapSensorComponent
{
private:
	Inject<IDroppedObjectView> droppedObjectView_;

public:
	AppleTileMapSensorComponent(bool _isActive, IMessenger* _messenger,
		IDroppedObjectView* _droppedObjectView);

	AppleTileMapSensorComponent(IMessenger* _messenger, IDroppedObjectView* _droppedObjectView);

	void Init() override;

	void Update() override;

	void Render() override;

	void Term() override;

	bool IsInsideWall(const Vector2f& _position) const override;

protected:
	void Reset() override;

};
#pragma warning(pop)
