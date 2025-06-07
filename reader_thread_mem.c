#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

extern char mensagem[1024];
extern int disponivel;

extern pthread_mutex_t mutex;
extern pthread_cond_t cond;

void* ler(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!disponivel) {
        pthread_cond_wait(&cond, &mutex);
    }

    printf("Leitor: Mensagem lida: \"%s\"\n", mensagem);
    disponivel = 0;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t;

    pthread_create(&t, NULL, ler, NULL);
    pthread_join(t, NULL);

    printf("Leitor: Finalizado.\n");
    return 0;
}
