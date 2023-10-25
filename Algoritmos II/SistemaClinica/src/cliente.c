#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cliutils.h"
#include "../include/cliente.h"

//Escreve as informacoes de um cliente e as escreve num arquivo clientes.dat
void cadastrarCliente() {
  system("cls");

  FILE *file;
  Cliente c;
  int cod_gen = 0;

  printf("Deseja cadastrar um novo cliente (S\\N)?\n");
  if (!confirma()) {
    return;
  }

  system("cls");
  printf("\e[?25h");

  if ((file = fopen("clientes.dat", "r+b")) == NULL) {
    file = fopen("clientes.dat", "wb");
    c.codigo = 0;
  } else {
    while (fread(&c, sizeof(Cliente), 1, file) == 1) {
      if (c.codigo == cod_gen)
        cod_gen++;
      if (c.codigo != cod_gen)
        c.codigo = cod_gen;
    }
  }

  printf("CADASTRO DE NOVO CLIENTE\n");

  fflush(stdin);

  printf("Nome: ");
  fgets(c.nome, sizeof(c.nome), stdin);
  c.nome[strlen(c.nome) - 1] = '\0';

  for (int i = 0; c.nome[i]; i++) {
    c.nome[i] = toupper(c.nome[i]);
  }

  printf("Idade: ");
  scanf("%d", &c.idade);

  while (getchar() != '\n');

  printf("Endereco: ");
  fgets(c.endereco, sizeof(c.endereco), stdin);
  c.endereco[strlen(c.endereco) - 1] = '\0';

  for (int i = 0; c.endereco[i]; i++) {
    c.endereco[i] = toupper(c.endereco[i]);
  }

  printf("Telefone: ");
  fgets(c.fone, sizeof(c.fone), stdin);
  c.fone[strlen(c.fone) - 1] = '\0';

  // Gravação do Cliente no arquivo
  fwrite(&c, sizeof(Cliente), 1, file);
  fclose(file);
}

//Lista todos os clientes armazenados no arquivo clientes.dat
void listarClientes() {
  system("cls");

  FILE *file;
  Cliente c;

  file = abrirArquivo("clientes.dat", "rb");

  if(file != NULL) {
    printf("==================================== LISTA DE CLIENTES "
           "======================================\n");
    printf("| %-8s | %-25s | %-5s | %-25s | %-15s |\n", "Codigo", "Nome", "Idade", "Endereco", "Telefone");
    printf("----------------------------------------------------------------------------------------------\n");

    while (fread(&c, sizeof(Cliente), 1, file) == 1) {
      printf("| %-8d | %-25s | %-5d | %-25s | %-15s |\n",
             c.codigo, c.nome, c.idade, c.endereco, c.fone);
    }
  }
  fclose(file);
  getch();
}

//Altera as informacoes de um cliente a partir de seu codigo, reescrevendo
//no arquivo clientes.dat
void atualizarCliente() {
  system("cls");

  FILE *file;
  int codigo_ref; // Código de referência = código digitado para procurar o cliente
  Cliente c;
  int flag = 0;

  printf("Deseja atualizar um cliente (S\\N)?\n");
  if (!confirma()) {
    return;
  }

  system("cls");
  printf("\e[?25h");

  printf("Codigo do cliente: ");
  scanf("%d", &codigo_ref);

  file = abrirArquivo("clientes.dat", "r+b");

  while (fread(&c, sizeof(Cliente), 1, file) == 1) {
    if (c.codigo == codigo_ref) {
      system("cls");
      printf("Cliente encontrado de codigo %d\n", codigo_ref);

      printf("Nome: %s\n", c.nome);
      printf("Idade: %d\n", c.idade);
      printf("Endereco: %s\n", c.endereco);
      printf("Telefone: %s\n", c.fone);

      printf("\nDeseja realmente alterar o cliente? (s/n): ");
      if (confirma()) {
        system("cls");

        while (getchar() != '\n');

        printf("Novo Nome: ");
        gets(c.nome);

        for (int i = 0; c.nome[i]; i++) {
          c.nome[i] = toupper(c.nome[i]);
        }

        printf("Nova Idade: ");
        scanf("%d", &c.idade);

        while (getchar() != '\n');

        printf("Novo Endereco: ");
        gets(c.endereco); 

        for (int i = 0; c.endereco[i]; i++) {
          c.endereco[i] = toupper(c.endereco[i]);
        }

        printf("Novo Telefone: ");
        gets(c.fone);


        fseek(file, -sizeof(Cliente), SEEK_CUR);
        fwrite(&c, sizeof(Cliente), 1, file);
        fclose(file);
        flag = 1;
      } else {
        flag = 2;
      }
    }
  }

  if (!flag) {
    printf("\nCliente nao encontrado!\n");
  } else if (flag == 2) {
    printf("\nCliente nao alterado!\n");
  } else {
    printf("\nCliente atualizado com sucesso!\n");
  }
  printf("\n");

  while (getchar() != '\n');

  system("pause");
}