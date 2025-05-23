#include "../inc/addnum.h"

t_list add_even;
t_list add_odd;
int thread_count;

pthread_t *threads = NULL;
int threads_created = 0;

FILE *fd = NULL;

int main(int argc, char **argv) {
    thread_count = 0;

    if (argc < 2) {
        fprintf(stderr, "\033[1;31merror: invalid argument number.\033[0m\n");
        fprintf(stderr, "use: %s -h|--help or %s -f|--file configfile/cfg.txt\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("usage: %s -f|--file configfile/cfg.txt\n", argv[0]);
        printf("file extension must be .txt and contain:\n");
        printf("file extension must be .txt and contain:\n");
        printf("Numbers per thread = <value>\nThread num = <value>\n");
        return EXIT_SUCCESS;
    }
    else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0)
    {
        if (argc < 3) {
            fprintf(stderr, "\033[1;31mpath to the config file is missing.\033[0m\n");
            return EXIT_FAILURE;
        }

        if (check_file(argv[2]) != 0)
            return EXIT_FAILURE;

        handler_sig();

        int num_per_thread;
        if (conf_parse(argv[2], &num_per_thread, &thread_count) != 0)
            return EXIT_FAILURE;

        threads = malloc(thread_count * sizeof(pthread_t));
        if (!threads)
            exit_error("\033[1;31merror: malloc threads\033[0m\n");

        t_threadData data[thread_count];

        init_list(&add_even, num_per_thread * thread_count);
        init_list(&add_odd, num_per_thread * thread_count);

        srand(time(NULL));
        usleep(100000);
        int i = 0;
        threads_created = 0;
        while (i < thread_count)
        {
            data[i].thread_id = i;
            data[i].num_per_thread = num_per_thread;
            if (pthread_create(&threads[i], NULL, threadFunc, &data[i]) != 0)
            {
                perror("\033[1;31mpthread_create failed\033[0m\n");
                i++;
                continue;
            }
            threads_created++;
            i++;
        }

        i = 0;
        while (i < thread_count)
        {
            pthread_join(threads[i], NULL);
            i++;
        }

        print_list("even num list", &add_even);
        print_list("odd num list", &add_odd);

        free_list(&add_even);
        free_list(&add_odd);
        free(threads);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "\033[1;31minvalid parameter.\033[0m\n");
        return EXIT_FAILURE;
    }
}
