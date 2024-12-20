#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;


    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    printf("Contents of directory: %s\n", path);
    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }


        if (S_ISDIR(file_stat.st_mode)) {
            printf("[Directory] %s\n", entry->d_name);
        } else if (S_ISREG(file_stat.st_mode)) {
            printf("[File] %s\n", entry->d_name);
        } else {
            printf("[Other] %s\n", entry->d_name);
        }
    }
    closedir(dir);
}

int main() {
    char path[1024];


    printf("Enter a directory path: ");
    fgets(path, sizeof(path), stdin);


    path[strcspn(path, "\n")] = 0;


    list_directory(path);

    return 0;
}
