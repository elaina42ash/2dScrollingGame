#pragma once

enum class ObjectPossessionState
{
    NONE = -1,

    FIRST = 0,

    WORLD_DROPPED = FIRST,
    EQUIPPED,
    IN_INVENTORY,
    CONSUMED,
    IN_USE,

    COUNT
};