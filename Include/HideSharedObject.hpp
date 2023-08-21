#ifndef HIDESHAREDOBJECT
#define HIDESHAREDOBJECT

#include <cstdio>
#include <cstdlib>

#include <link.h>

#include <string>

namespace HideSharedObject {
	void addHiddenSharedObject(const std::string& name);

	int hookFunc(int (*)(struct dl_phdr_info*, size_t, void*), void*);
	extern void* proxy;
}

#endif