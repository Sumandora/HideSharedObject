#include "HideSharedObject.hpp"

#include <algorithm>
#include <cstring>
#include <vector>

static std::vector<std::string> hiddenSharedObjects;

static bool __attribute((used)) check(struct dl_phdr_info* info)
{
	return std::ranges::any_of(hiddenSharedObjects, [&info](std::string sharedObject) {
		return std::strstr(info->dlpi_name, sharedObject.c_str());
	});
}

static int __attribute__((naked)) passthrough(struct dl_phdr_info* rdi, size_t rsi, void* rdx)
{
	__asm volatile(
		"push %rdi;" // Save registers
		"push %rsi;"
		"push %rdx;"

		"call _ZL5checkP12dl_phdr_info;" // Should we hide this one?

		"pop %rdx;" // Reset registers
		"pop %rsi;"
		"pop %rdi;"

		"test %eax, %eax;" // Did the check succeed?
		"je call_orig;" // If no then ignore this one

		"xor %eax, %eax;" // If it did, request the next object
		"ret;"

		"call_orig:"
		"mov 0x8(%rdx), %rax;" // Unmarshall 'Data' structure
		"mov (%rdx), %rdx;"
		"jmp *%rax;" // Jump to target function
	);
}

void HideSharedObject::addHiddenSharedObject(const std::string& name)
{
	hiddenSharedObjects.push_back(name);
}

int HideSharedObject::hookFunc(int (*__callback)(struct dl_phdr_info*, size_t, void*), void* __data)
{
	struct Data {
		void* oldData;

		int (*oldCallback)(struct dl_phdr_info*, size_t, void*);
	} newData{};

	newData.oldData = __data;
	newData.oldCallback = __callback;

	return reinterpret_cast<int (*)(int (*)(struct dl_phdr_info*, size_t, void*), void*)>(proxy)(passthrough, &newData);
}