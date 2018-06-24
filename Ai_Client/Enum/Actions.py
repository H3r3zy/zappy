from enum import IntEnum


class Actions(IntEnum):
    LOOK = 0,
    CHECK_FOOD = 1,
    FIND_FOOD = 2,
    FIND_CRYSTALS = 3,
    FORWARD = 4,
    CHECK_LVL_UP = 5,
    TAKE_ALL = 6,
    LVL_UP = 7,
    CHECK_PLAYER = 8,
    NEED_PEOPLE = 9,
    DROP = 10,
    WAIT_LVL_UP = 11,
    GO_TO_BROADCASTER = 12,
    FIND_IF_BROADCASTER = 13,
    SYNCHRO = 14,
    MAKE_FOOD_STOCK = 15,
    FIND_FOOD_STOCK = 16,
    FORWARD_STOCK = 17,
    SYNCHRO_INVENTORY = 18,
    AM_I_FIRST = 19,
    SYNCHRO_BROADCAST = 20
