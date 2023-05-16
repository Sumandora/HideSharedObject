# HideSharedObject
HideSharedObject is a C++ library that makes it easy to hide a shared object in `dl_iterate_phdr` by hooking the function and allowing you to hide a shared object with a simple function call.

## Introduction
The `dl_iterate_phdr` function is used in Linux to iterate over the loaded shared objects in a process. It is commonly used by various tools and libraries for introspection and dynamic analysis. However, in some scenarios, you may want to hide a specific shared object from being detected or accessed by such tools.

HideSharedObject provides a straightforward way to achieve this by hooking the `dl_iterate_phdr` function and intercepting the shared object information.

## Usage
```c++
#include "HideSharedObject.hpp"

void* HideSharedObject::proxy;

void InstallHideSharedObject() {
	HideSharedObject::AddHiddenSharedObject("libc.so"); // This may be a substring of your shared objects name
    
	void* trampoline = CreateHook((void*) dl_iterate_phdr, (void*) HideSharedObject::HookFunc);
	HideSharedObject::proxy = trampoline;
}
```
The only requirement is a hooking library, capable of redirecting execution flow to the HookFunc inside HideSharedObject.
It is intentional to not provide a hooking library in this repository since it is your task to hook the function.

If this confuses you, you can take a look at `Example/Main.cpp`. This file houses an example with a hooking library.
You are not forced to use this hooking library, you may use another one.
