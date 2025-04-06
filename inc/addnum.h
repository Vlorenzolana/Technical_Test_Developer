#ifndef ADDNUM_H
#define ADDNUM_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>

#define MAX_LINE 128
#define THREAD_LIMIT 100

typedef struct s_list {
    int *numbers;
    int load_size;
    int count;
    pthread_rwlock_t lock;
} t_list;

typedef struct s_threadData {
    int thread_id;
    int num_per_thread;
} t_threadData;

extern t_list add_even;
extern t_list add_odd;

extern pthread_t *threads;
extern int thread_count;
extern int threads_created;

#endif