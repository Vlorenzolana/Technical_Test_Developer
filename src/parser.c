#include "../inc/addnum.h"

int check_file(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".txt") != 0) {
        fprintf(stderr, "\033[1;31merror: config file extension must be .txt\033[0m\n");
        return -1;
    }
    fd = fopen(filename, "r");
    if (!fd) {
        fprintf(stderr, "\033[1;31merror: config file cannot be opened.\033[0m\n");
        return -1;
    }
    if (fclose(fd) != 0) {
        perror("\033[1;31mfclose error\033[0m\n");
        return -1;
    }
    fd = NULL;
    return 0;
}

int check_thread_max(int thread_num) {
    if (thread_num <= 0 || thread_num > THREAD_LIMIT) {
        fprintf(stderr, "\033[1;31merror: MAX thread number must be between 1 and %d.\033[0m\n", THREAD_LIMIT);
        return -1;
    }
    return 0;
}

int conf_parse(const char *filename, int *num_per_thread, int *thread_num) {
    fd = fopen(filename, "r");
    if (!fd) {
        fprintf(stderr, "\033[1;31merror: opening config file: %s\033[0m\n", strerror(errno));
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
            if (strstr(key, "Numbers_per_thread") != NULL)
            {
                *num_per_thread = atoi(value);
                if (*num_per_thread <= 0 || *num_per_thread > MAX_NUMBERS_PER_THREAD)
                {
                    fprintf(stderr, "\033[1;31merror: numbers_per_thread must be between 1 and %d.\033[0m\n", MAX_NUMBERS_PER_THREAD);
                    fclose(fd);
                    return -1;
                }
                found_nums = 1;
            }
            else if (strstr(key, "thread_num") != NULL)
            {
                *thread_num = atoi(value);
                found_threads = 1;
            }
        }
    }

    if (fclose(fd) != 0)
    {
        perror("\033[1;31mfclose error\033[0m\n");
        return -1;
    }
    fd = NULL;

    if (!found_nums || !found_threads)
    {
        fprintf(stderr, "\033[1;31merror: config file, key not found.\033[0m\n");
        return -1;
    }
    if (*num_per_thread <= 0 || *thread_num <= 0)
    {
        fprintf(stderr, "\033[1;31merror: config file, invalid values.\033[0m\n");
        return -1;
    }
    if (check_thread_max(*thread_num) != 0)
        return -1;

    return 0;
}
