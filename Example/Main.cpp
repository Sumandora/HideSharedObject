#include "HideSharedObject.hpp"

#include "DetourHooking.hpp"
#include "ldisasm.h"

#include <cassert>

int callback(struct dl_phdr_info* info, size_t size, void* data)
{
	printf("%s\n", info->dlpi_name);

	assert(size == sizeof(*info));
	assert(*(int*)data == 1337);

	return 0;
}

void* HideSharedObject::proxy;

void installHideSharedObject()
{
	HideSharedObject::addHiddenSharedObject("libc.so");

	void* functionPtr = (void*)dl_iterate_phdr;
	size_t stolenBytes = 0;
	while (stolenBytes <= DetourHooking::minLength) {
		stolenBytes += ldisasm(static_cast<char*>(functionPtr) + stolenBytes, true);
	}

	auto* hook = new DetourHooking::Hook(functionPtr, (void*)HideSharedObject::hookFunc, stolenBytes);
	hook->enable();

	HideSharedObject::proxy = hook->trampoline;
}

int main()
{
	int data = 1337;
	printf("Real:\n");
	dl_iterate_phdr(callback, &data);

	installHideSharedObject();

	printf("Fake:\n");
	dl_iterate_phdr(callback, &data);

	return 0;
}
