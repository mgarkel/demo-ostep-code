#include <assert.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int a;
    int b;
} myarg_t;

myarg_t global_var = { 30, 40 };

void *routine1(void *arg) {
    myarg_t *args = (myarg_t *) arg;
	int t1_var1 = 1;
	int t1_var2 = 2;
    printf("Thread routine1:\n myarg: %d %d\n global_var: %d %d\n addr of local vars: %x %x\n", 
				args->a, args->b, 
				global_var.a, global_var.b,
				(unsigned int) &t1_var1, (unsigned int) &t1_var2);
    return NULL;
}

void *routine2(void *arg) {
    myarg_t *args = (myarg_t *) arg;
	int t2_var1 = 1;
	int t2_var2 = 2;
    printf("Thread routine2:\n myarg: %d %d\n global_var: %d %d\n addr of local vars: %x %x\n", 
				args->a, args->b, 
				global_var.a, global_var.b,
				(unsigned int) &t2_var1, (unsigned int) &t2_var2);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    myarg_t args = { 10, 20 };

    int rc = pthread_create(&p1, NULL, routine1, &args);
    assert(rc == 0);
    rc = pthread_create(&p2, NULL, routine2, &args);
    assert(rc == 0);
    (void) pthread_join(p1, NULL);
    (void) pthread_join(p2, NULL);
    printf("done\n");
    return 0;
}
