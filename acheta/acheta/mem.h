#include <windows.h>
#include <iostream>

class Mem {
private:
	DWORD pid = 0;
	HANDLE proc = NULL;
public:
	Mem(const char* procname);
	~Mem();

	DWORD getpid();
	HANDLE getprochandel();

	uintptr_t GetModuleBase(const char* modname);

	template <typename T>
	T Read(uintptr_t address) {
		T value;
		ReadProcessMemory(this->proc, (LPCVOID)address, &value, sizeof(T), NULL);
		return value;
	}
	template <typename T>
	BOOL Write(uintptr_t address, T value) {
		return WriteProcessMemory(this->proc, (LPCVOID)address, &value, sizeof(T), NULL);
	}

};