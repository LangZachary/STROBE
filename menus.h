//*********************************************************************
//* Constants for the OLED Menu in the STROBE system.				  *
//*																	  *
//* Written by Zachary Lang                                           *
//* January 12, 2015                                               	  *
//*********************************************************************


// Menus //

#pragma romdata menus=0x11500

// Used by multiple menus

// Change Color
far rom char change_color_l1[21] = "   Zone     All     ";
far rom char change_color_l2[21] = "   Red  |          |";
far rom char change_color_l3[21] = "   Green|          |";
far rom char change_color_l4[21] = "   Blue |          |";

// Memory Slot
far rom char memory_slot_l1[21] = "   1.               ";
far rom char memory_slot_l2[21] = "   2.               ";
far rom char memory_slot_l3[21] = "   3.               ";
far rom char memory_slot_l4[21] = "   4.               ";


// Welcome Screen
far rom char welcome_screen1_l1[21] = "   Loading ...   0% ";
far rom char welcome_screen1_l2[21] = "                    ";
far rom char welcome_screen1_l3[21] = "                    ";
far rom char welcome_screen1_l4[21] = "    |          |    ";

far rom char welcome_load1_l1[21] = "       Waking       ";
far rom char welcome_load1_l2[21] = "         Up         ";     
far rom char welcome_load2_l1[21] = "       Hitting      ";
far rom char welcome_load2_l2[21] = "       Snooze       ";
far rom char welcome_load3_l1[21] = "      Actually      ";
far rom char welcome_load3_l2[21] = "     Waking  Up     ";
far rom char welcome_load4_l1[21] = "     Getting On     ";
far rom char welcome_load4_l2[21] = "    Hamster Wheel   ";
far rom char welcome_load5_l1[21] = "       Steady       ";
far rom char welcome_load5_l2[21] = "        Jog         ";
far rom char welcome_load6_l1[21] = "       Running      ";
far rom char welcome_load6_l2[21] = "        Fast        ";
far rom char welcome_load7_l1[21] = "       Out Of       ";
far rom char welcome_load7_l2[21] = "       Control      ";
far rom char welcome_load8_l1[21] = "       Crashed      ";
far rom char welcome_load8_l2[21] = "     The System     ";
far rom char welcome_load9_l1[21] = "      Rebooting     ";
far rom char welcome_load9_l2[21] = "                    ";
far rom char welcome_load10_l1[21] = "    Streamlining    ";
far rom char welcome_load10_l2[21] = "      System        ";
far rom char welcome_load11_l1[21] = "     Pretending     ";
far rom char welcome_load11_l2[21] = "      To Work       ";
far rom char welcome_load12_l1[21] = "      Raising       ";
far rom char welcome_load12_l2[21] = "      Curtain       ";
far rom char welcome_load13_l1[21] = "     Taking  A      ";
far rom char welcome_load13_l2[21] = "        Bow         ";

// Welcome Screen 2
far rom char welcome_screen2_l1[21] = "   Welcome to the   ";
far rom char welcome_screen2_l2[21] = "                    ";
far rom char welcome_screen2_l3[21] = "       STROBE       ";
far rom char welcome_screen2_l4[21] = "                    ";

// Welcome Screen definitions.
#define		welcome_screen1		0


// Select Menu 1
far rom char select_menu1_l1[21] = "    Motion Sensing  ";
far rom char select_menu1_l2[21] = "    Manual          ";
far rom char select_menu1_l3[21] = "    STROBE          ";
far rom char select_menu1_l4[21] = "                    ";

// Select Menu 1 definitions.
#define		select_menu1a		10		// Motion Sensing.
#define		select_menu1b		11		// Manual.
#define		select_menu1c		12		// STROBE.

// Motion Sensing Menu 1
far rom char motion_menu1_l1[21] = "    Start           ";
far rom char motion_menu1_l2[21] = "    Options         ";
far rom char motion_menu1_l3[21] = "    Tracking OFF    ";
far rom char motion_menu1_l4[21] = "  Status:    OFF    ";
// MS OFF
far rom char motion_menu1a_off_l1[21] = "    Start           ";
far rom char motion_menu1a_off_l4[21] = "  Status:    OFF    ";
// MS ON
far rom char motion_menu1a_on_l1[21] = 	"    Stop            ";
far rom char motion_menu1a_on_l4[21] = 	"  Status:    ON     ";
// TRACKING OFF
far rom char motion_menu1c_off_l3[21] = "    Tracking OFF    ";
// TRACKING ON
far rom char motion_menu1c_on_l3[21] = "    Tracking ON     ";

// Motion Sensing Menu 1 definitions.
#define		motion_menu1		103		// Initial
#define		motion_menu1a_off	20		// Start
#define		motion_menu1a_on	21		// Stop
#define		motion_menu1b		22		// Options
#define		motion_menu1c_off	101		// Tracking OFF
#define		motion_menu1c_on	102		// Tracking ON


// Motion Sensing Menu 2
far rom char motion_menu2_l1[21] = " Timeout Delay: 0.1s";
far rom char motion_menu2_l2[21] = "    |          |    ";
far rom char motion_menu2_l3[21] = "    Light Spread    ";
far rom char motion_menu2_l4[21] = "    |          |    ";

// Motion Sensing Menu 2 definitions.
#define		motion_menu2a		23

// Manual Menu 1
far rom char manual_menu1_l1[21] = "        Manual      ";
far rom char manual_menu1_l2[21] = "   New              ";
far rom char manual_menu1_l3[21] = "   Load             ";
far rom char manual_menu1_l4[21] = "                    ";

#define		manual_menu1a		30		// New	
#define		manual_menu1b		31		// Load

// Manual Menu 2
// Uses Change Color
#define		manual_menu2		40		// Initial
#define		manual_menu2a		41		// Zone
#define		manual_menu2a_zone	42		// Zone Select
#define		manual_menu2b		43		// Red
#define		manual_menu2b_red	44		// Red Select
#define		manual_menu2c		45		// Green
#define		manual_menu2c_green	46		// Green Select
#define		manual_menu2d		47		// Blue
#define		manual_menu2d_blue	48		// Blue Select

// Manual Menu 3
// Uses Memory Slot
#define		manual_menu3		49		// Load Menu
#define		manual_menu3a		50		// Slot 1
#define		manual_menu3b		51		// Slot 2
#define		manual_menu3c		52		// Slot 3
#define		manual_menu3d		53		// Slot 4

// Manual Save 1
far rom char manual_save1_l1[21] = "   Do you wish to   ";
far rom char manual_save1_l2[21] = "        save?       ";
far rom char manual_save1_l3[21] = "         Yes        ";
far rom char manual_save1_l4[21] = "         No         ";

#define		manual_save1a		54		// Yes
#define		manual_save1b		55		// No

// Manual Save 2
// Uses Memory Slot
#define		manual_save2		56
#define		manual_save2a		57		// Slot 1
#define		manual_save2b		58		// Slot 2
#define		manual_save2c		59		// Slot 3
#define		manual_save2d		60		// Slot 4

// Manual Save Name
#define		manual_save_name1	61
#define		manual_save_name2	62
#define		manual_save_name3	63
#define		manual_save_name4	64

// STROBE Menu 1
far rom char strobe_menu1_l1[21] = "       STROBE       ";
far rom char strobe_menu1_l2[21] = "   Short Show       ";
far rom char strobe_menu1_l3[21] = "   Long Show        ";
far rom char strobe_menu1_l4[21] = "   Strobe Light     ";

// STROBE Menu 1
#define		strobe_menu1a		70		// Short
#define		strobe_menu1b		71		// Long
#define		strobe_menu1c		105		// Strobe

// STROBE Short Menu 1
far rom char strobe_short1_l1[21] = "     Short Show     ";
far rom char strobe_short1_l2[21] = "   New              ";
far rom char strobe_short1_l3[21] = "   Load             ";
far rom char strobe_short1_l4[21] = "                    ";

// STROBE Short Menu 1
#define		strobe_short1a		72		// New
#define		strobe_short1b		73		// Load

// STROBE Short New 1
// Uses Memory Slot
#define		strobe_short_new1	74
#define		strobe_short_new1a	75		// Slot 1
#define		strobe_short_new1b	76		// Slot 2
#define		strobe_short_new1c	77		// Slot 3
#define		strobe_short_new1d	78		// Slot 4

// STROBE Short New 2
far rom char strobe_short_new2_l1[21] = "   Stage    /32     ";
far rom char strobe_short_new2_l2[21] = "   Change Colors    ";
far rom char strobe_short_new2_l3[21] = "   Change Timing    ";
far rom char strobe_short_new2_l4[21] = "  Next   Back   Done";

#define		strobe_short_new2	140		// Initial
#define		strobe_short_new2a	79		// Change Colors
#define		strobe_short_new2b	80		// Change Timing
#define		strobe_short_new2c	81		// Next
#define		strobe_short_new2d	82		// Back
#define		strobe_short_new2e	141		// Done

// STROBE Short New 3
// Uses Change Color Menu
#define		strobe_short_new3			83		// Initial
#define		strobe_short_new3a			84		// Zone
#define		strobe_short_new3a_zone		85		// Zone Select
#define		strobe_short_new3b			86		// Red
#define		strobe_short_new3b_red		87		// Red Select
#define		strobe_short_new3c			88		// Green
#define		strobe_short_new3c_green	89		// Green Select
#define		strobe_short_new3d			90		// Blue
#define		strobe_short_new3d_blue		91		// Blue Select

// STROBE Short New 4
far rom char strobe_short_new4_l1[21] = " Hold Time:        s";
far rom char strobe_short_new4_l2[21] = "    |          |    ";
far rom char strobe_short_new4_l3[21] = " Fade Time:        s";
far rom char strobe_short_new4_l4[21] = "    |          |    ";

#define		strobe_short_new4	92		// Initial

// Strobe Save Name
#define		strobe_short_save_name	142		// Short Save Name
#define		strobe_long_save_name	143		// Long Save Name

// Strobe Exit 1
far rom char strobe_exit_l1[21] = "    Exit without    ";
far rom char strobe_exit_l2[21] = "       saving?      ";
far rom char strobe_exit_l3[21] = "         Yes        ";
far rom char strobe_exit_l4[21] = "         No         ";

#define		strobe_short_exit1a		144		// Yes
#define		strobe_short_exit1b		145		// No

#define		strobe_long_exit1a		146		// Yes
#define		strobe_long_exit1b		147		// No


// STROBE Short Load 1
// Uses Memory Slot
#define		strobe_short_load1	93
#define		strobe_short_load1a	94		// Slot 1
#define		strobe_short_load1b	95		// Slot 2
#define		strobe_short_load1c	96		// Slot 3
#define		strobe_short_load1d	97		// Slot 4

// STROBE Short Load 2
far rom char strobe_short_load2_l1[21] = "    Show Loaded:    ";
far rom char strobe_short_load2_l2[21] = "                    ";
far rom char strobe_short_load2_l3[21] = "   Start            ";
far rom char strobe_short_load2_l4[21] = "   Edit             ";

#define		strobe_short_load2		104		// Initial
#define		strobe_short_load2a_off	98		// Start
#define		strobe_short_load2a_on  99		// Stop
#define		strobe_short_load2b		100		// Edit

#define		strobe_short_load3		108

// STROBE Long Menu 1
far rom char strobe_long1_l1[21] = "     Long Show      ";
far rom char strobe_long1_l2[21] = "   New              ";
far rom char strobe_long1_l3[21] = "   Load             ";
far rom char strobe_long1_l4[21] = "                    ";

// STROBE Long Menu 1
#define		strobe_long1a		109		// New
#define		strobe_long1b		110		// Load

// STROBE Long New 1
// Uses Memory Slot
#define		strobe_long_new1	111
#define		strobe_long_new1a	112		// Slot 1
#define		strobe_long_new1b	113		// Slot 2
#define		strobe_long_new1c	114		// Slot 3
#define		strobe_long_new1d	115		// Slot 4

// STROBE Long New 2
far rom char strobe_long_new2_l1[21] = "   Stage    /192    ";
far rom char strobe_long_new2_l2[21] = "   Change Colors    ";
far rom char strobe_long_new2_l3[21] = "   Change Timing    ";
far rom char strobe_long_new2_l4[21] = "  Next   Back   Done";

#define		strobe_long_new2	116		// Initial
#define		strobe_long_new2a	117		// Change Colors
#define		strobe_long_new2b	118		// Change Timing
#define		strobe_long_new2c	119		// Next
#define		strobe_long_new2d	148		// Back
#define		strobe_long_new2e	149		// Done

// STROBE Long New 3
// Uses Change Color Menu
#define		strobe_long_new3			120		// Initial
#define		strobe_long_new3a			121		// Zone
#define		strobe_long_new3a_zone		122		// Zone Select
#define		strobe_long_new3b			123		// Red
#define		strobe_long_new3b_red		124		// Red Select
#define		strobe_long_new3c			125		// Green
#define		strobe_long_new3c_green		126		// Green Select
#define		strobe_long_new3d			127		// Blue
#define		strobe_long_new3d_blue		128		// Blue Select

// STROBE Long New 4
far rom char strobe_long_new4_l1[21] = " Hold Time:        s";
far rom char strobe_long_new4_l2[21] = "    |          |    ";
far rom char strobe_long_new4_l3[21] = " Fade Time:        s";
far rom char strobe_long_new4_l4[21] = "    |          |    ";

#define		strobe_long_new4	129		// Initial

// STROBE Long Load 1
// Uses Memory Slot
#define		strobe_long_load1	130
#define		strobe_long_load1a	131		// Slot 1
#define		strobe_long_load1b	132		// Slot 2
#define		strobe_long_load1c	133		// Slot 3
#define		strobe_long_load1d	134		// Slot 4

// STROBE Long Load 2
far rom char strobe_long_load2_l1[21] = "    Show Loaded:    ";
far rom char strobe_long_load2_l2[21] = "                    ";
far rom char strobe_long_load2_l3[21] = "   Start            ";
far rom char strobe_long_load2_l4[21] = "   Edit             ";

#define		strobe_long_load2		135		// Initial
#define		strobe_long_load2a_off	136		// Start
#define		strobe_long_load2a_on  	137		// Stop
#define		strobe_long_load2b		138		// Edit

#define		strobe_long_load3		139


// STROBE Strobe Light 1
// STROBE Long Load 2
far rom char strobe_strobe1_l1[21] = "    STROBE LIGHT    ";
far rom char strobe_strobe1_l2[21] = "                    ";
far rom char strobe_strobe1_l3[21] = "Time ON |          |";
far rom char strobe_strobe1_l4[21] = "Time OFF|          |";


#define		strobe_strobe1a			107


#pragma code beginning

