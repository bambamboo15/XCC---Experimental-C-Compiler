/**
 *    =====================================
 *        XCC - Experimental C Compiler  
 *    =====================================
 * 
 * This file takes care of EVERYTHING output 
 * related, such as color macros or diagnostics.
 */
#include <cstdio>

template <typename... Args>
void diagnostic_fatal(const char* source, const char* msg, Args&&... args) {
	printf("\033[38;2;255;255;255m%s: \033[38;2;255;75;75mfatal error: \033[0m", source);
	printf(msg, args...);
}