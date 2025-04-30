#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char buffer[100];

    // Open or create the file
    file = fopen("data.txt", "w+");  // "w+" creates the file if it doesn't exist
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Write to the file
    fprintf(file, "Hello, File Handling in C!");

    // Move pointer to the beginning
    rewind(file);

    // Read contents
    fgets(buffer, sizeof(buffer), file);

    // Print the contents
    printf("Read from file: %s\n", buffer);

    // Close the file
    fclose(file);

    return 0;
}
