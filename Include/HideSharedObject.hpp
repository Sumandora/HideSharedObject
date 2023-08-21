#ifndef HIDESHAREDOBJECT
#define HIDESHAREDOBJECT

#include <cstdio>
#include <cstdlib>

#include <link.h>

#include <string>

namespace HideSharedObject {
	void AddHiddenSharedObject(const std::string& name);

	int HookFunc(int (*)(struct dl_phdr_info*, size_t, void*), void*);
	extern void* proxy;
}

#endif