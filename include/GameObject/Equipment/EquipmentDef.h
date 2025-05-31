#pragma once

enum class EquipmentSlotType
{
	NONE = -1,
	FIRST = 0,
	WEAPON_1 = FIRST,
	WEAPON_2,

	COUNT
};

enum class EquipmentType
{
	NONE = -1,
	FIRST = 0,
    SWORD = FIRST,
	KATANA,

	COUNT
};

enum class EquipmentStatus
{
	NONE = -1,
	FIRST = 0,

	EQUIPPED = FIRST,
	IN_INVENTORY,
	DROPPED,
	IN_STORAGE,
	DESTROYED,

	COUNT,
};
