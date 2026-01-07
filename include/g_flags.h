#ifndef G_FLAGS_H
#define G_FLAGS_H

// !! 'gGlobalFlags' array is in 'g_data.c' file !!

#define G_FLAG_PENDING_DARK_HOUR    2565 // idx 80 (1 << 5). When activated and the time is passing, trigger dark hour and tp hero to tartarus
#define G_FLAG_DAY_IS_MONDAY        2568 // idx 80 (1 << 8)
#define G_FLAG_DAY_IS_TUESDAY       2569 // idx 80 (1 << 9)
#define G_FLAG_DAY_IS_WEDNESDAY     2570 // idx 80 (1 << 10)
#define G_FLAG_DAY_IS_THURSDAY      2571 // idx 80 (1 << 11)
#define G_FLAG_DAY_IS_FRIDAY        2572 // idx 80 (1 << 12)
#define G_FLAG_DAY_IS_SATURDAY      2573 // idx 80 (1 << 13)
#define G_FLAG_DAY_IS_SUNDAY        2574 // idx 80 (1 << 14). DAYOFF flag is also activated when it's sunday
#define G_FLAG_DAY_IS_DAYOFF        2575 // idx 80 (1 << 15). Holiday or sunday
#define G_FLAG_ROOM_HELP_SEEN       3086 // idx 96 (1 << 14). "If you go back into your room, it will become midnight"
#define G_FLAG_HERO_HANDS_IN_POCKET 3125 // idx 98 (1 << 21)

#endif