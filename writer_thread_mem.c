#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

char mensagem[1024];
int disponivel = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* escrever(void* arg) {
    pthread_mutex_lock(&mutex);
    strcpy(mensagem, "Olá, Memória Compartilhada via Threads!");
    disponivel = 1;
    printf("Escritor: Mensagem escrita na memória.\n");

    pthread_cond_signal(&cond);  // Notifica leitor
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t;

    pthread_create(&t, NULL, escrever, NULL);
    pthread_join(t, NULL);

    // Espera leitura
    while (1) {
        pthread_mutex_lock(&mutex);
        if (!disponivel) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    printf("Escritor: Mensagem foi lida. Finalizado.\n");
    return 0;
}
