#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>

#define SHM_SIZE 1024
const char* shm_name = "SharedMemoryExample";  // No Global\\

int main() {
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        SHM_SIZE,
        shm_name);

    if (hMapFile == NULL) {
        std::cerr << "Could not create file mapping object. Error: " << GetLastError() << std::endl;
        return 1;
    }

    char* pBuf = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, SHM_SIZE);

    if (pBuf == NULL) {
        std::cerr << "Could not map view of file. Error: " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

    std::cout << "Writer: Enter a message to store in shared memory: ";
    std::string message;
    std::getline(std::cin, message);

    strncpy(pBuf, message.c_str(), SHM_SIZE - 1);
    pBuf[SHM_SIZE - 1] = '\0';  // Make sure it's null-terminated

    std::cout << "Writer: Message written. Press Enter to exit..." << std::endl;
    std::cin.get();

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}
