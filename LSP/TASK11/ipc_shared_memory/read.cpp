#include <windows.h>
#include <iostream>

#define SHM_SIZE 1024
const char* shm_name = "SharedMemoryExample";
  // Same name

int main() {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, shm_name);

    if (hMapFile == NULL) {
        std::cerr << "Could not open file mapping object. Error: " << GetLastError() << std::endl;
        return 1;
    }

    char* pBuf = (char*)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, SHM_SIZE);

    if (pBuf == NULL) {
        std::cerr << "Could not map view of file. Error: " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

    std::cout << "Reader: Message from shared memory: " << pBuf << std::endl;

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}
