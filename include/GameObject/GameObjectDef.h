#pragma once

enum class DetachableObjectState
{
    NONE = -1,

    FIRST = 0,

    WORLD_DROPPED = FIRST,
    HELD,
    IN_INVENTORY,
    CONSUMED,
    IN_USE,

    COUNT
};