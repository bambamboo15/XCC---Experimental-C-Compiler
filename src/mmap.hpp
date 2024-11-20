/**
 *    =====================================
 *        XCC - Experimental C Compiler  
 *    =====================================
 * 
 * This is an altered version of Benjamin Kramer's 
 * portable memory-mapped file implementation.
 */
#pragma once 
#include <stddef.h>

#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__MACH__)
#	include <unistd.h>
#	if _POSIX_VERSION >= 199506L
#		define HAVE_MMAP 1
#	endif 
#endif

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#elif HAVE_MMAP
#	include <fcntl.h>
#	include <sys/types.h>
#	include <sys/mman.h>
#else 
#	include <stdlib.h>
#	include <stdio.h>
#endif 

char* mmap_file(const char* path, size_t* length) {
	char* data = NULL;
	size_t size = 0;

#ifdef _WIN32 
	HANDLE hMap;
	HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,
							   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	size = GetFileSize(hFile, NULL);
	if (size == INVALID_FILE_SIZE || size == 0)
		goto fail;

	hMap = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, size, NULL);
	if (!hMap)
		goto fail;

	data = (char*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, size);

	CloseHandle(hMap);
fail:
	CloseHandle(hFile);

#elif HAVE_MMAP 
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return NULL;

	size = lseek(fd, 0, SEEK_END);
	if (size <= 0)
		goto fail;

	data = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED)
		data = NULL;
fail:
	close(fd);

#else 
	FILE *fd = fopen(path, "rb");
	if (!fd)
		return NULL;

	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	if (size <= 0)
		goto fail;

	rewind(fd);
	data = (char*)malloc(size);
	if (!data)
		goto fail;

	if (fread(data, size, 1, fd) != 1) {
		free(data);
		data = NULL;
	}
fail:
	fclose(fd);

#endif 
	if (length)
		*length = size;
	return data;
}

void unmap_file(char *data, [[maybe_unused]] size_t length) {
#ifdef _WIN32
	UnmapViewOfFile(data);
#elif HAVE_MMAP
	munmap(data, length);
#else 
	free(data);
#endif 
}