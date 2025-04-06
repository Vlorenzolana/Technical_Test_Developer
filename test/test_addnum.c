#include "../inc/addnum.h"

t_list test_list;

t_list add_even;
t_list add_odd;
pthread_t *threads = NULL;
int thread_count = 0;
int threads_created = 0;
FILE *fd = NULL;

void test_add_and_print_list()
{
    init_list(&test_list, 5);

    assert(add_num(&test_list, 2) == 0);
    assert(add_num(&test_list, 4) == 0);
    assert(add_num(&test_list, 6) == 0);
    assert(test_list.count == 3);
    assert(test_list.numbers[0] == 2);
    assert(test_list.numbers[1] == 4);

    printf("test_add_and_print_list passed\n");

    free_list(&test_list);
}

void test_check_thread_max()
{
    assert(check_thread_max(10) == 0);
    assert(check_thread_max(THREAD_LIMIT + 1) == -1);

    printf("test_check_thread_max passed\n");
}

void test_init_list()
{
    init_list(&test_list, 3);
    assert(test_list.count == 0);
    assert(test_list.load_size == 3);
    assert(test_list.numbers != NULL);

    printf("test_init_list passed\n");

    free_list(&test_list);
}

int main(void)
{
    printf("Running unit tests\n\n");

    test_init_list();
    test_check_thread_max();
    test_add_and_print_list();

    printf("\nAll tests passed successfully!\n");
    return 0;
}
