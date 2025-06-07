# Relatório Comparativo: Comunicação entre Processos vs. Threads

## Introdução

Neste trabalho, foram implementadas duas abordagens para comunicação entre componentes de um sistema em linguagem C:

- **Processos com IPC (arquivo e memória compartilhada)**
- **Threads com memória compartilhada (variáveis globais)**

Cada abordagem foi utilizada para dois cenários:

1. Comunicação via **arquivo**.
2. Comunicação via **memória compartilhada**.

#### Processos
```bash
gcc writer.c -o writer
gcc reader.c -o reader

gcc writer_mem.c -o writer_mem
gcc reader_mem.c -o reader_mem
```
---

## Parte 1: Comunicação via Arquivo

### Usando Processos

- Um processo escreve a mensagem em um arquivo (`comunicacao.txt`).
- Outro processo lê o conteúdo e renomeia o arquivo como sinalização de leitura concluída.
- Utiliza chamadas como `fopen`, `fread`, `rename`, e `access`.

#### Execução
![Imagem da execução via arquivo com processos](imagem.png)

---

### 🧵 Usando Threads

- A mensagem é escrita em uma variável global compartilhada.
- Um leitor em outra thread lê o conteúdo e sinaliza a leitura alterando um flag.
- Utiliza `pthread_mutex_t` e `pthread_cond_t` para sincronização.

#### Execução
![Imagem da execução via arquivo com threads](imagem-1.png)

---

## Parte 2: Comunicação via Memória Compartilhada

### Usando Processos

- Os processos usam a API System V: `shmget`, `shmat`, `shmdt`, `shmctl`.
- O escritor escreve na memória compartilhada e espera a sinalização (*).
- O leitor lê o conteúdo e altera o primeiro byte como sinal.


### Usando Threads

- A comunicação é feita com uma variável global em memória compartilhada entre threads.
- Sincronização com `pthread_mutex` e `pthread_cond`.
- Código mais simples e leve, sem necessidade de IPC.

## Conclusão

A abordagem com **threads** se mostrou mais eficiente e com menor complexidade de implementação, especialmente para comunicações simples. No entanto, **processos** ainda são importantes em casos onde o isolamento é essencial, como em ambientes multiprogramados ou aplicações independentes.

O uso de threads é recomendado quando há necessidade de comunicação leve e rápida dentro de um mesmo programa, enquanto processos são mais adequados para casos onde segurança e isolamento são prioritários.

---
