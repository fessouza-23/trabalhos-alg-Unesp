
/*
Trabalho de Algoritmos II - Gerenciamento de Clinica
a partir de manipulação de arquivos binarios
realizado por:
 - João Victor Fernandes Souza
 - Eduardo Teixeira
 - Gabriel Rasi
 - Guilherme Silva
*/
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define esc 27
#define f1 59
typedef struct {
  int codigo;
  char nome[50];
  int idade;
  char endereco[50];
  char fone[21];
} Cliente;

int cod_gen = 0; // Variável para gerar código para cadastro de clientes

/* Função para abrir arquivo e evitar repetição de código,
 funciona criando variavel do tipo FILE e usando: arquivo = abrirArquivo(nome_arquivo, op); 
 op é a forma que deseja abrir o arquivo (rb, wb, ab)*/
FILE *abrirArquivo(const char nome_arquivo[20], const char op[5]) {
  FILE *file;
  if ((file = fopen(nome_arquivo, op)) == NULL) {
    printf("Erro ao abrir o arquivo.\n\n");
    exit(1);
  }
  return file;
}

int confirma() {
  char resp;
  do {
    resp = toupper(getch());
  } while (resp != 'S' && resp != 'N');

  return (resp == 'S') ? 1 : 0;
}

void sobre() {
  system("cls");
  printf("================================  SOBRE O PROGRAMA  "
         "=======================================\n");
  printf("Programa desenvolvido por Eduardo R. Teixeira, Joao V. F. Souza, "
         "Gabriel Rasi e Guilherme S.\n"
         "Disciplina de Algoritmos II do curso de BSI\n");
  printf("Criado em 2023\n");
  printf("\nPressione qualquer tecla para voltar ao menu.\n");
  getch();
}

void cadastrarCliente() {
  FILE *file;
  Cliente c;

  system("cls");
  printf("CADASTRO DE NOVO CLIENTE\n");
  c.codigo = cod_gen++;
  fflush(stdin);
  printf("Nome: ");
  fgets(c.nome, sizeof(c.nome), stdin);
  c.nome[strlen(c.nome) - 1] = '\0';
  printf("Idade: ");
  scanf("%d", &c.idade);
  fflush(stdin);
  printf("Endereco: ");
  fgets(c.endereco, sizeof(c.endereco), stdin);
  c.endereco[strlen(c.endereco) - 1] = '\0';
  printf("Telefone: ");
  fgets(c.fone, sizeof(c.fone), stdin);
  c.fone[strlen(c.fone) - 1] = '\0';

  // Gravação do Cliente no arquivo
  file = abrirArquivo("clientes.dat", "ab");
  fwrite(&c, sizeof(Cliente), 1, file);
  fclose(file);
}

/* Esta função não está dentro das necessárias,
 serve apenas para testar se o codigo esta funcionando corretamente */
void consultarCliente() {
  FILE *file;
  Cliente c;

  system("cls");
  file = abrirArquivo("clientes.dat", "rb");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (fread(&c, sizeof(Cliente), 1, file) == 1) {
    printf("%d %s %d %s %s\n", c.codigo, c.nome, c.idade, c.endereco, c.fone);
  }

  fclose(file);
  getch();
}

void atualizarCliente() {
  FILE *file;
  int codigo_ref; // Código de referência = código digitado para procurar o
                  // cliente
  Cliente c;
  int achou = 0;

  system("cls");
  printf("Digite o codigo do cliente: ");
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
        fflush(stdin);
        printf("Novo Nome: ");
        gets(c.nome);
        printf("Nova Idade: ");
        scanf("%d", &c.idade);
        fflush(stdin);
        printf("Novo Endereco: ");
        gets(c.endereco);
        printf("Novo Telefone: ");
        gets(c.fone);
        fseek(file, -sizeof(Cliente), SEEK_CUR);
        fwrite(&c, sizeof(Cliente), 1, file);
        fclose(file);
        achou = 1;
      } else {
        achou = 2;
        break;
      }
    }
  }
  if (!achou) {
    printf("Cliente nao encontrado!\n");
  } else if (achou == 2) {
    printf("Cliente nao alterado!\n");
  } else {
    printf("Cliente alterado com sucesso!\n");
  }
  printf("\nPressione qualquer tecla para voltar ao menu.\n");
  getch();
}

void menu() {
  char op;

  do {
    system("cls");
    printf("================================  MENU  "
           "=======================================\n");
    printf("|ESC - Sair | F1 - Sobre o Programa|\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Listar clientes\n");
    printf("3 - Atualizar cliente\n");
    op = getch();

    switch (op) {
    case '1':
      cadastrarCliente();
      break;

    case '2':
      consultarCliente();
      break;

    case '3':
      atualizarCliente();
      break;

    case f1:
      sobre();
      break;
    }
  } while (op != esc);
}

int main() {
  Cliente c;
  menu();
  return 0;
}
