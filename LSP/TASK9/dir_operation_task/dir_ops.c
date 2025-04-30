#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <io.h>
#include <sys/stat.h>

int main() {
    DIR *d;
    struct dirent *dir;

    // List all files and directories in the current working directory
    d = opendir(".");
    if (d) {
        printf("Contents of current directory:\n");
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("opendir");
        return 1;
    }

    // Change directory to C:\tmp (use C:/tmp if it exists on your system)
    if (chdir("C:/Users/Public") != 0) {

        perror("chdir");
        return 1;
    }
    printf("Changed directory to C:/tmp\n");

    // Create new directory "testdir"
    if (mkdir("testdir") != 0) {
        perror("mkdir");
        return 1;
    }

    // Set directory permissions (read, write, execute for user)
    if (_chmod("testdir", _S_IREAD | _S_IWRITE | _S_IEXEC) != 0) {
        perror("_chmod");
        return 1;
    }

    printf("Created directory testdir with permissions (read, write, execute)\n");

    return 0;
}
