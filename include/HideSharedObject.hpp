#ifndef HIDESHAREDOBJECT
#define HIDESHAREDOBJECT

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <link.h>

namespace HideSharedObject {
	void AddHiddenSharedObject(const char* name);

	int HookFunc(int (*)(struct dl_phdr_info *, size_t, void *), void *);
	extern void* proxy;
}

#endif