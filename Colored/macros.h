/*
	source file: main.cpp

	Copyright (c) 2022 TheCryStal, All rights reserved.

	MIT License
*/
#ifndef MACROS_H
#define MACROS_H

#define ESC "\x1B"
#define CSI ESC "["
#define OSC ESC "]"
#define SP "\x20"

#define _W(x) L##x
#define W(x) _W(x)

// TF = text formatting
#define TF_END "m"
#define TF_FMT(n) CSI n TF_END
#define TF_DEFAULT "0"
#define TF_BOLD "1"
#define TF_BRIGHT TF_BOLD
#define TF_NO_BOLD "22"
#define TF_NO_BRIGHT TF_NO_BOLD
#define TF_UNDERLINE "4"
#define TF_NO_UNDERLINE "24"
#define TF_NEGATIVE "7"
#define TF_POSITIVE "27"
#define TF_NO_NEGATIVE TF_POSITIVE
#define TF_FOREGROUND "3"
#define TF_FG TF_FOREGROUND
#define TF_BACKGROUND "4"
#define TF_BG TF_BACKGROUND
#define TF_BRIGHT_FOREGROUND "9"
#define TF_BFG TF_BRIGHT_FOREGROUND
#define TF_BRIGHT_BACKGROUND "10"
#define TF_BBG TF_BRIGHT_BACKGROUND

#define TF_BLACK "0"
#define TF_RED "1"
#define TF_GREEN "2"
#define TF_YELLOW "3"
#define TF_BLUE "4"
#define TF_MAGENTA "5"
#define TF_CYAN "6"
#define TF_WHITE "7"

// FG = foreground
#define TF_FG_BLACK		TF_FG TF_BLACK
#define TF_FG_GREEN		TF_FG TF_GREEN
#define TF_FG_RED		TF_FG TF_RED
#define TF_FG_YELLOW	TF_FG TF_YELLOW
#define TF_FG_BLUE		TF_FG TF_BLUE
#define TF_FG_MAGENTA	TF_FG TF_MAGENTA
#define TF_FG_CYAN		TF_FG TF_CYAN
#define TF_FG_WHITE		TF_FG TF_WHITE
#define TF_FG_EXTENDED	TF_FG "8"
#define TF_FG_DEFAULT	TF_FG "9"

// BFG = bright foreground
#define TF_BFG_BLACK	TF_BFG TF_BLACK
#define TF_BFG_GREEN	TF_BFG TF_GREEN
#define TF_BFG_RED		TF_BFG TF_RED
#define TF_BFG_YELLOW	TF_BFG TF_YELLOW
#define TF_BFG_BLUE		TF_BFG TF_BLUE
#define TF_BFG_MAGENTA	TF_BFG TF_MAGENTA
#define TF_BFG_CYAN		TF_BFG TF_CYAN
#define TF_BFG_WHITE	TF_BFG TF_WHITE

// BG = bakckground
#define TF_BG_BLACK		TF_BG TF_BLACK
#define TF_BG_GREEN		TF_BG TF_GREEN
#define TF_BG_RED		TF_BG TF_RED
#define TF_BG_YELLOW	TF_BG TF_YELLOW
#define TF_BG_BLUE		TF_BG TF_BLUE
#define TF_BG_MAGENTA	TF_BG TF_MAGENTA
#define TF_BG_CYAN		TF_BG TF_CYAN
#define TF_BG_WHITE		TF_BG TF_WHITE
#define TF_BG_EXTENDED	TF_BG "8"
#define TF_BG_DEFAULT	TF_BG "9"

// BBG = bright background
#define TF_BBG_BLACK	TF_BBG TF_BLACK
#define TF_BBG_GREEN	TF_BBG TF_GREEN
#define TF_BBG_RED		TF_BBG TF_RED
#define TF_BBG_YELLOW	TF_BBG TF_YELLOW
#define TF_BBG_BLUE		TF_BBG TF_BLUE
#define TF_BBG_MAGENTA	TF_BBG TF_MAGENTA
#define TF_BBG_CYAN		TF_BBG TF_CYAN
#define TF_BBG_WHITE	TF_BBG TF_WHITE

#define TF_FG_EXT_RGB_COLOR   TF_FG_EXTENDED ";2;" 
#define TF_BG_EXT_RGB_COLOR   TF_BG_EXTENDED ";2;"
#define TF_FG_EXT_INDEX_COLOR TF_FG_EXTENDED ";5;" 
#define TF_BG_EXT_INDEX_COLOR TF_BG_EXTENDED ";5;"

#define TF_FG_EXT_RGB_SEQ(R, G, B)	TF_FMT( TF_FG_EXT_RGB_COLOR		R##";"##G##";"##B) 
#define TF_BG_EXT_RGB_SEQ(R, G, B)	TF_FMT( TF_BG_EXT_RGB_COLOR		R##";"##G##";"##B) 
#define TF_FG_EXT_INDEX_SEQ(S)		TF_FMT( TF_FG_EXT_INDEX_COLOR	S			 	 )
#define TF_BG_EXT_INDEX_SEQ(S)		TF_FMT( TF_BG_EXT_INDEX_COLOR	S				 )

#endif // !MACROS_H