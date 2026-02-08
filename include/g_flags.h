#ifndef G_FLAGS_H
#define G_FLAGS_H

// !! 'gGlobalFlags' array is in 'g_data.c' file !!

#define G_FLAG_PENDING_DUNGEON      2565 // idx 80  (1 << 5). When activated and time is dark hour, tp to tartarus 1F
#define G_FLAG_DAY_IS_MONDAY        2568 // idx 80  (1 << 8)
#define G_FLAG_DAY_IS_TUESDAY       2569 // idx 80  (1 << 9)
#define G_FLAG_DAY_IS_WEDNESDAY     2570 // idx 80  (1 << 10)
#define G_FLAG_DAY_IS_THURSDAY      2571 // idx 80  (1 << 11)
#define G_FLAG_DAY_IS_FRIDAY        2572 // idx 80  (1 << 12)
#define G_FLAG_DAY_IS_SATURDAY      2573 // idx 80  (1 << 13)
#define G_FLAG_DAY_IS_SUNDAY        2574 // idx 80  (1 << 14). DAYOFF flag is also activated when it's sunday
#define G_FLAG_DAY_IS_DAYOFF        2575 // idx 80  (1 << 15). Holiday or sunday
#define G_FLAG_MAP_STUD_HELP_SEEN   2680 // idx 83  (1 << 24). "When you speak to this student, the Town Map will be displayed."
#define G_FLAG_TIME_IS_EARLY_MORN   2688 // idx 84  (1 << 0). Early morning
#define G_FLAG_TIME_IS_MORNING      2689 // idx 84  (1 << 1)
#define G_FLAG_TIME_IS_LUNCH        2690 // idx 84  (1 << 2)
#define G_FLAG_TIME_IS_AFTERNOON    2691 // idx 84  (1 << 3)
#define G_FLAG_TIME_IS_AFTER_SCHOOL 2692 // idx 84  (1 << 4)
#define G_FLAG_TIME_IS_EVENING      2693 // idx 84  (1 << 5)
#define G_FLAG_TIME_IS_LATE_NIGHT   2694 // idx 84  (1 << 6)
#define G_FLAG_TIME_IS_DARK_HOUR    2695 // idx 84  (1 << 7)
#define G_FLAG_ROOM_HELP_SEEN       3086 // idx 96  (1 << 14). "If you go back into your room, it will become midnight"
#define G_FLAG_HERO_HANDS_IN_POCKET 3125 // idx 98  (1 << 21)
#define G_FLAG_BATTLE               5127 // idx 160 (1 << 7)

#endif