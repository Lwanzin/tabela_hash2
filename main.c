#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// LUAN PINHEIRO MARQUETTI GRR20230959
// foi utilizado um compilador de C online (https://www.onlinegdb.com/online_c_compiler)

typedef struct Contato
{
    char nome[50];
    char numero[20];
    struct Contato *next;
} Contato;

Contato *hash_table[TABLE_SIZE];

unsigned int hash(const char *nome)
{
    unsigned int hash = 0;
    while (*nome)
    {
        hash += *nome++;
    }
    return hash % TABLE_SIZE;
}

void add_contact(const char *nome, const char *numero)
{
    unsigned int index = hash(nome);
    Contato *new_contact = malloc(sizeof(Contato));
    strcpy(new_contact->nome, nome);
    strcpy(new_contact->numero, numero);
    new_contact->next = hash_table[index];
    hash_table[index] = new_contact;
    printf("Contato %s adicionado com sucesso!\n", nome);
}

void search_contact(const char *nome)
{
    unsigned int index = hash(nome);
    Contato *current = hash_table[index];
    while (current)
    {
        if (strcmp(current->nome, nome) == 0)
        {
            printf("Encontrado: %s - %s\n", current->nome, current->numero);
            return;
        }
        current = current->next;
    }
    printf("Contato %s não encontrado.\n", nome);
}

void remove_contact(const char *nome)
{
    unsigned int index = hash(nome);
    Contato *current = hash_table[index];
    Contato *prev = NULL;
    while (current)
    {
        if (strcmp(current->nome, nome) == 0)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                hash_table[index] = current->next;
            }
            free(current);
            printf("Contato %s removido com sucesso!\n", nome);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contato %s não encontrado.\n", nome);
}

void list_contacts()
{
    printf("Lista de contatos:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Contato *current = hash_table[i];
        while (current)
        {
            printf("%s - %s\n", current->nome, current->numero);
            current = current->next;
        }
    }
}

int main()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    add_contact("Lucas", "1234-5678");
    add_contact("Ana", "9876-5432");
    search_contact("Lucas");
    remove_contact("Lucas");
    search_contact("Lucas");
    list_contacts();

    return 0;
}
