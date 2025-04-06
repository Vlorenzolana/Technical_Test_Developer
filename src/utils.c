#include "../inc/addnum.h"

void free_list(t_list *list)
{
    if (list->numbers) free(list->numbers);
    pthread_rwlock_destroy(&list->lock);
}

void exit_error(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void init_list(t_list *list, int load_size)
{
    list->numbers = malloc(load_size * sizeof(int));
    if (!list->numbers)
        exit_error("memory allocation error");
    list->load_size = load_size;
    list->count = 0;
    if (pthread_rwlock_init(&list->lock, NULL) != 0)
        exit_error("read-write lock init error.");
}

void print_list(const char *title, t_list *list)
{
    printf("%s:\n", title);
    int i = 0;
    while (i < list->count) {
        printf("position %d: %d\n", i, list->numbers[i]);
        i++;
    }
}
