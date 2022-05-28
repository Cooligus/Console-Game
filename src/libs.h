//===check is any curses library avaible and if is include and define variable telling about that
//ncursesw.h
//#elif __has_include(<ncursesw.h>)
#	include <ncurses.h>
#	define CURSES_AVAILABLE
//#endif
//add support for pdcurses