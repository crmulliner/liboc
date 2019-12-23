/*
 * (c) Collin Mulliner <collin AT mulliner.org>
 *
 * license: GPLv2
 */


#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

typedef int (*real_open)(const char *pathname, int flags, mode_t mode);

static int open_count;

static void init() __attribute__((constructor));
void init(void)
{
	char *cnt = getenv("OC_OPEN_COUNT");
	if (cnt != 0) {
		open_count = atoi(cnt);
	} else {
		open_count = -1;
	}
}

int open(const char *pathname, int flags, ...)
{
	real_open open_call;

	va_list args;
	va_start(args, flags);
	int mode = va_arg(args, int);
	va_end(args);
	
	open_call = dlsym(RTLD_NEXT, "open");
	//printf("->%s\n", pathname);

	if (open_count) {
		open_count--; 
		return open_call(pathname, flags, mode);
	} else if (open_count == -1) {
		return open_call(pathname, flags, mode);
	}

	errno = EACCES;
	return -1;
}
