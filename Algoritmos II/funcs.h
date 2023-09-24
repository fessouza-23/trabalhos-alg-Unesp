#ifndef FUNCS_H
#define FUNCS_H

#define esc 27
#define f1 59

typedef struct {
  int codigo;
  char nome[50];
  int idade;
  char endereco[50];
  char fone[21];
} Cliente;

typedef struct {
  int codigo;
  int existe;
  char nomeDoCliente[50];
  int dia;
  int mes;
  int ano;
  int hora;
  int minuto;
} Consulta;

FILE *abrirArquivo(const char nome_arquivo[20], const char op[5]);

int confirma();

void sobre();

void cadastrarCliente();

void consultarCliente();

void atualizarCliente();

void marcarConsulta();

void desmarcarConsulta();

void listarConsultas();

void desmarcarConsultaRemFis();

void listarConsultasCodCliente();

void consultaHaMaisDe6Meses();

void menu();

#endif