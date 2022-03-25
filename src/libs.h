//===check is any curses library avaible and if is include and define variable telling about that
//curses.h
#if __has_include(<curses.h>)
#	include <curses.h>
#	define CURSES_AVAILABLE
//ncursesw.h
#elif __has_include(<ncursesw.h>)
#	include <ncursesw.h>
#	define CURSES_AVAILABLE
//stdio.h
#else
#	include <stdio.h>
#endif

