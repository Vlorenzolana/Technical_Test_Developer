#include "../inc/addnum.h"

int add_num(t_list *list, int number)
{
    if (list->count >= list->load_size)
        return -1;
    list->numbers[list->count++] = number;
    return 0;
}

void* threadFunc(void *arg)
{
    t_threadData *data = (t_threadData*) arg;
    int n = data->num_per_thread;
    int *generated = (int *)malloc(n * sizeof(int));
    if (!generated)
    {
        perror("error: malloc");
        pthread_exit(NULL);
    }

    int count = 0;
    while (count < n)
    {
        int num = rand();
        int duplicate = 0;
        int i = 0;
        while (i < count)
        {
            if (generated[i] == num)
            {
                duplicate = 1;
                break;
            }
            i++;
        }
        if (duplicate)
            continue;

        generated[count++] = num;
        if (num % 2 == 0) {
            pthread_rwlock_wrlock(&add_even.lock);
            add_num(&add_even, num);
            pthread_rwlock_unlock(&add_even.lock);
        } else {
            pthread_rwlock_wrlock(&add_odd.lock);
            add_num(&add_odd, num);
            pthread_rwlock_unlock(&add_odd.lock);
        }
    }

    free(generated);
    pthread_exit(NULL);
}
