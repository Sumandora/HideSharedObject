#ifndef HIDESHAREDOBJECT
#define HIDESHAREDOBJECT

#include <link.h>
#include <string>

namespace HideSharedObject {
	void addHiddenSharedObject(const std::string& name);

	int hookFunc(int (*)(dl_phdr_info*, size_t, void*), void*);
	extern void* proxy;
}

#endif