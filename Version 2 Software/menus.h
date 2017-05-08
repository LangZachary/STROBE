//*********************************************************************
//* Constants for the OLED Menu in the STROBE system.				  *
//*																	  *
//* Written by Zachary Lang                                           *
//* January 12, 2015                                               	  *
//*********************************************************************

unsigned char oled_menu = 0;

// Menus
#define		main_menu1		0
far rom char main_menu1_l1[] = "   Welcome to the   ";
far rom char main_menu1_l2[] = "       STROBE       ";
far rom char main_menu1_l3[] = "        xxxx        ";
far rom char main_menu1_l4[] = "        1234        ";


#define		select_menu1	10
far rom char select_menu1_l1[] = " Choose a mode:     ";
far rom char select_menu1_l2[] = "  > Motion Sensing  ";
far rom char select_menu1_l3[] = "    Manual          ";
far rom char select_menu1_l4[] = "    Strobe          ";

#define		select_menu2	11
far rom char select_menu2_l1[] = " Choose a mode:     ";
far rom char select_menu2_l2[] = "    Motion Sensing  ";
far rom char select_menu2_l3[] = "  > Manual          ";
far rom char select_menu2_l4[] = "    Strobe          ";

#define		select_menu3	12
far rom char select_menu3_l1[] = " Choose a mode:     ";
far rom char select_menu3_l2[] = "    Motion Sensing  ";
far rom char select_menu3_l3[] = "    Manual          ";
far rom char select_menu3_l4[] = "  > Strobe          ";

#define		select_menu4	13
far rom char select_menu4_l1[] = " Choose a mode:     ";
far rom char select_menu4_l2[] = "    Manual          ";
far rom char select_menu4_l3[] = "    Strobe          ";
far rom char select_menu4_l4[] = "  > Options         ";

#define		select_menu5	14
far rom char select_menu5_l1[] = " Choose a mode:     ";
far rom char select_menu5_l2[] = "    Manual          ";
far rom char select_menu5_l3[] = "  > Strobe          ";
far rom char select_menu5_l4[] = "    Options         ";

#define		select_menu6	15
far rom char select_menu6_l1[] = " Choose a mode:     ";
far rom char select_menu6_l2[] = "  > Manual          ";
far rom char select_menu6_l3[] = "    Strobe          ";
far rom char select_menu6_l4[] = "    Options         ";

#define		motion_screen1	20
far rom char motion_screen1_l1[] = "   Motion Sensors   ";
far rom char motion_screen1_l2[] = "        ON          ";
far rom char motion_screen1_l3[] = "                    ";
far rom char motion_screen1_l4[] = "                    ";

#define		manual_screen1	30
far rom char manual_screen1_l1[] = "    Manual Mode     ";
far rom char manual_screen1_l2[] = "                    ";
far rom char manual_screen1_l3[] = "  > New             ";
far rom char manual_screen1_l4[] = "    Load            ";

#define		manual_screen2	31
far rom char manual_screen2_l1[] = "    Manual Mode     ";
far rom char manual_screen2_l2[] = "                    ";
far rom char manual_screen2_l3[] = "    New             ";
far rom char manual_screen2_l4[] = "  > Load            ";

#define		manual_new1		40
far rom char manual_new1_l1[] = "      STAGE 1       ";
far rom char manual_new1_l2[] = " > Change Color     ";
far rom char manual_new1_l3[] = "   Change Delay     ";
far rom char manual_new1_l4[] = "             Next   ";

#define		manual_new2		41
far rom char manual_new2_l1[] = "      STAGE 2       ";
far rom char manual_new2_l2[] = " > Change Color     ";
far rom char manual_new2_l3[] = "   Change Delay     ";
far rom char manual_new2_l4[] = "   Back      Next   ";

#define		manual_new_color	42
far rom char manual_new_color_l1[] = " > Red              ";
far rom char manual_new_color_l2[] = "   Green            ";
far rom char manual_new_color_l3[] = "   Blue             ";
far rom char manual_new_color_l4[] = "   Save             ";

#define		manual_load1	60
far rom char manual_load1_l1[] = " > Profile 1        ";
far rom char manual_load1_l2[] = "   Profile 2        ";
far rom char manual_load1_l3[] = "   Profile 3        ";
far rom char manual_load1_l4[] = "   Profile 4        ";

#define		manual_load2	61
far rom char manual_load2_l1[] = "   Profile 1        ";
far rom char manual_load2_l2[] = " > Profile 2        ";
far rom char manual_load2_l3[] = "   Profile 3        ";
far rom char manual_load2_l4[] = "   Profile 4        ";

#define		manual_load3	62
far rom char manual_load3_l1[] = "   Profile 1        ";
far rom char manual_load3_l2[] = "   Profile 2        ";
far rom char manual_load3_l3[] = " > Profile 3        ";
far rom char manual_load3_l4[] = "   Profile 4        ";

#define		manual_load4	63
far rom char manual_load4_l1[] = "   Profile 1        ";
far rom char manual_load4_l2[] = "   Profile 2        ";
far rom char manual_load4_l3[] = "   Profile 3        ";
far rom char manual_load4_l4[] = " > Profile 4        ";




