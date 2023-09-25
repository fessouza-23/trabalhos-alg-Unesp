#ifndef CLIUTILS.H
#define CLIUTILS.H

#define esc 27
#define f1 59

typedef struct {
  int codigo;
  int existe;
  char nomeDoCliente[50];
  int codigoDoCliente;
  int dia;
  int mes;
  int ano;
  int hora;
  int minuto;
} Consulta;

typedef struct {
  int codigo;
  char nome[50];
  int idade;
  char endereco[50];
  char fone[21];
} Cliente;

FILE *abrirArquivo(const char nome_arquivo[20], const char op[5]);

int confirma();

void sobre();

void menu();

#endif