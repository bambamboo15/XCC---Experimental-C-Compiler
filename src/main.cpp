/**
 *    =====================================
 *        XCC - Experimental C Compiler  
 *    =====================================
 * 
 * This file is the main entry point for the program.
 */
#include "compiler.hpp"

int main(int argc, char** argv) {
	if (argc == 2) {
		compiler(argv[1]);
		return 0;
	} else if (argc == 1) {
		diagnostic_fatal(argv[0],
			"you either entered nothing, or gave me the wrong arguments :(\n"
			"Did you mean '%s [file]'?\n",
			argv[0]);
		return -1;
	}
}