#include "../inc/addnum.h"

void sig_handler(int sig) {
    printf("\nreceived signal %d, cleaned up & exit\n", sig);

    int i = 0;
    while (i < threads_created && threads[i]) {
        pthread_join(threads[i], NULL);
        i++;
    }

    if (fd)
        fclose(fd);

    free_list(&add_even);
    free_list(&add_odd);
    free(threads);

    exit(EXIT_SUCCESS);
}

void handler_sig(void) {
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
}
