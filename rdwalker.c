/*
 * =====================================================================================
 *
 *       Filename:  rdwalker.c
 *
 *    Description: recursive directory walker 
 *
 *        Version:  1.0
 *        Created:  09.01.2026 04:07:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (freemorger), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

bool is_dir(char* path);
void walk(char* path, int foldlvl); 

int main(int argc, char** argv) {
    if (argc < 2) {
        char* path = "./";
        walk(path, 0);
        return 0;
    }
    char* path = argv[1];

    walk(path, 0);
    return 0;
}

bool is_dir(char* path) {
    struct stat fstat;

    if (stat(path, &fstat) != 0) {
        fprintf(stderr, "stat: can't get stat for %s\n", path);
        exit(1);
    } 

    if (S_ISDIR(fstat.st_mode)) {
        return true;
    } else {
        return false;
    }
}

void print_fname(char* path, int foldlvl) {
    char* start = strrchr(path, '/');
    if (start == NULL) {
        printf("%s\n", path);
        return;
    }
    start += 1;
    size_t len = strlen(start);

    char* sep_path = malloc(sizeof(char) * (len + 1));
    strncpy(sep_path, start, len);
    sep_path[len] = '\0'; 

    int need_size = foldlvl + strlen(start) + 1;
    
    char* res = malloc(sizeof(char) * need_size);
    char* res_og = res;
    for (int i = 0; i < foldlvl; i++) {
        *(res) = '-';
        res++;
    }
    stpcpy(res, sep_path);

    if (is_dir(path)) {
        printf("%s/\n", res_og);
    } else {
        printf("%s\n", res_og);
    }

    free(res_og);
    free(sep_path);
}

void walk(char* path, int foldlvl) {
    if (!is_dir(path)) {
        print_fname(path, foldlvl);
        return;
    }

    DIR* _dir = opendir(path);
    if (_dir == NULL) {
    fprintf(stderr, "dir %s is null\n", path);
        exit(1);
    }

    struct dirent* entry;
    while ((entry = readdir(_dir)) != NULL) {
        char* entry_name = entry->d_name;
        if (!strcmp(entry_name, ".") || !strcmp(entry_name, "..")) continue;

        size_t need_size = strlen(path) + strlen(entry_name) + 2; // 1 for slash, 1 for term
        char* full = malloc(sizeof(char) * need_size);
        char* sec = stpcpy(full, path);
        char* end = stpcpy(sec, entry_name);

        if (is_dir(full)) {
            print_fname(full, foldlvl);
            *end = '/';
            *(end + 1) = '\0';
            walk(full, foldlvl + 1);
        } else {
            walk(full, foldlvl);
        }

        free(full);
    }
}
