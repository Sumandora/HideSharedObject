#include "HideSharedObject.hpp"

#include <vector>
#include <algorithm>

static std::vector<const char*> hiddenSharedObjects;

static bool __attribute((used)) Check(struct dl_phdr_info* info) {
	return std::ranges::any_of(hiddenSharedObjects, [&info](const char* sharedObject) {
		return std::strstr(info->dlpi_name, sharedObject);
	});
}

static int __attribute__((naked)) Passthrough(struct dl_phdr_info* rdi, size_t rsi, void* rdx) {
	__asm volatile(
			"push %rdi;" // Save registers
			"push %rsi;"
			"push %rdx;"

			"call _ZL5CheckP12dl_phdr_info;" // Should we hide this one?

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

void HideSharedObject::AddHiddenSharedObject(const char* name) {
	hiddenSharedObjects.push_back(name);
}

int HideSharedObject::HookFunc(int (* __callback)(struct dl_phdr_info*,
												  size_t, void*),
							   void* __data) {
	struct Data {
		void* oldData;

		int (* oldCallback)(struct dl_phdr_info*, size_t, void*);
	} newData{};

	newData.oldData = __data;
	newData.oldCallback = __callback;

	return reinterpret_cast<int (*)(int (*)(struct dl_phdr_info*, size_t, void*), void*)>(proxy)(Passthrough, &newData);
}