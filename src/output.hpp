/**
 *    =====================================
 *        XCC - Experimental C Compiler  
 *    =====================================
 * 
 * This file takes care of EVERYTHING output 
 * related, such as color macros or diagnostics.
 */
#include <iostream>
#include <cstdio>
#include <utility>

#define COLOR_WHITE		"\033[38;2;255;255;255m"
#define COLOR_YELLOW	"\033[38;2;255;255;100m"
#define COLOR_RED		"\033[38;2;255;75;75m"
#define COLOR_RST		"\033[0m"

template <typename... Args>
void diagnostic_fatal(const char* source, const char* msg, Args&&... args) {
	printf(COLOR_WHITE "%s: " COLOR_RED "fatal error: " COLOR_RST, source);
	printf(msg, std::forward<Args>(args)...);
}