#include "mem.h"
#include <TlHelp32.h>
Mem::Mem(const char* procname) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	while (Process32Next(snapshot, &entry)){
		if (!strcmp(procname, entry.szExeFile)) {
			this->pid = entry.th32ProcessID;
			this->proc = OpenProcess(PROCESS_ALL_ACCESS, false, this->pid);
			break;
		}
	}
}
Mem::~Mem() {
	if (this->proc)
		CloseHandle(this->proc);
}

DWORD Mem::getpid() {
	return this->pid;
}
HANDLE Mem::getprochandel() {
	return this->proc;
}

uintptr_t Mem::GetModuleBase(const char* modname) {
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);

	const auto modul = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->pid);

	uintptr_t result = 0;

	while (Module32Next(modul, &entry)) {
		if (!strcmp(modname, entry.szModule)) {
			result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			break;
		}
	}
	if (modul)
		CloseHandle(modul);
	return result;
}