/**
 *    =====================================
 *        XCC - Experimental C Compiler  
 *    =====================================
 * 
 * Fully preprocess, compile, assemble, and link 
 * a program, from start to end.
 */
#include "output.hpp"
#include "mmap.hpp"
#include <limits>

void compiler(const char* file) {
	// Memory map the whole file, throw a fatal error if unsuccessful.
	size_t length;
	const char* const data = mmap_file(file, &length);

	if (data == NULL)
		return diagnostic_fatal(file, "failed opening file '%s'\n", file);
	
	// If total file size exceeds the capacity of an `unsigned long long`
	// throw a fatal error. We tag each character with an `unsigned long long`
	// value that determines the original index of the character it came from.
	if (const auto max = std::numeric_limits<unsigned long long>::max(); length > 0)
		return diagnostic_fatal(file, "file size of %s%llu%s exceeds maximum capacity of %s%llu%s bytes\n",
			COLOR_YELLOW, length, COLOR_RST, COLOR_YELLOW, max, COLOR_RST);
	
	
}