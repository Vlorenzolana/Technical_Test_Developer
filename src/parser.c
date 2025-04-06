#include "../inc/addnum.h"

int check_file(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".txt") != 0) {
        fprintf(stderr, "error: config file extension must be .txt\n");
        return -1;
    }
    fd = fopen(filename, "r");
    if (!fd) {
        fprintf(stderr, "error: config file cannot be opened.\n");
        return -1;
    }
    if (fclose(fd) != 0) {
        perror("fclose error");
        return -1;
    }
    fd = NULL;
    return 0;
}

int check_thread_max(int thread_num) {
    if (thread_num <= 0 || thread_num > THREAD_LIMIT) {
        fprintf(stderr, "error: MAX thread number must be between 1 and %d.\n", THREAD_LIMIT);
        return -1;
    }
    return 0;
}

int conf_parse(const char *filename, int *num_per_thread, int *thread_num) {
    fd = fopen(filename, "r");
    if (!fd) {
        fprintf(stderr, "error: opening config file: %s\n", strerror(errno));
        return -1;
    }

    char line[MAX_LINE];
    int found_nums = 0, found_threads = 0;
    while (fgets(line, sizeof(line), fd))
    {
        char *ptr = line;
        while (isspace(*ptr))
            ptr++;
        if (*ptr == '#' || *ptr == '\0' || *ptr == '\n')
            continue;
        char key[64];
        char value[64];
        if (sscanf(ptr, " %63[^=]= %63s", key, value) == 2)
        {
            if (strstr(key, "Numbers per thread") != NULL)
            {
                *num_per_thread = atoi(value);
                found_nums = 1;
            } else if (strstr(key, "Thread num") != NULL)
            {
                *thread_num = atoi(value);
                found_threads = 1;
            }
        }
    }

    if (fclose(fd) != 0)
    {
        perror("fclose error");
        return -1;
    }
    fd = NULL;

    if (!found_nums || !found_threads)
    {
        fprintf(stderr, "error: config file, key not found.\n");
        return -1;
    }
    if (*num_per_thread <= 0 || *thread_num <= 0)
    {
        fprintf(stderr, "error: config file, invalid values.\n");
        return -1;
    }
    if (check_thread_max(*thread_num) != 0)
        return -1;

    return 0;
}
