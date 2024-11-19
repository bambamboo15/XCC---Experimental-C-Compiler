/**
 *    =====================================
 *        XCC - Experimental C Compiler  
 *    =====================================
 * 
 * Global variable that manages configurations.
 */
extern struct GlobalProperties {
	char* name;
	char* file;
	bool error;

	GlobalProperties(int argc, char** argv)
		: name(argv[0]), error(argc != 2) {
		if (error)
			file = argv[1];
	}
} globalProperties;