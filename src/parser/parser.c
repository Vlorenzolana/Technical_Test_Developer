#include "../../inc/addnum.h"

int conf_parse(const char *filename, int *num_per_thread, int *thread_num) {
    FILE *fd = fopen(filename, "r");
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
