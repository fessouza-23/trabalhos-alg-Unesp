#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/cliutils.h"

//Checa se houve erros na abertura do arquivo
FILE *abrirArquivo(const char nome_arquivo[20], const char op[5]) {
  FILE *file;

  if ((file = fopen(nome_arquivo, op)) == NULL) {
    printf("Erro ao abrir o arquivo.\n\n");
    system("pause");
  }

  return file;
}

//Utilizada para confirmar uma acao
int confirma() {
  char resp;

  do {
    resp = toupper(getch());
  } while (resp != 'S' && resp != 'N');

  return (resp == 'S') ? 1 : 0;
}

//Menu sobre
void sobre() {
  system("cls");
  printf("================================  SOBRE O PROGRAMA  "
         "=======================================\n");
  printf("Programa desenvolvido por Eduardo R. Teixeira, Joao V. F. Souza, "
         "Gabriel Rasi e Guilherme S.\n"
         "Disciplina de Algoritmos II do curso de BSI\n");
  printf("Criado em 2023\n\n");
  printf("Versao: 1.0\n");
  printf("Descricao: Este programa eh um sistema de gerenciamento de clinica que \n"
  "permite cadastrar clientes, marcar consultas e realizar outras operacoes relacionadas.\n");
  printf("Funcionalidades: \n");
  printf("- Cadastrar cliente\n");
  printf("- Listar clientes\n");
  printf("- Atualizar cliente\n");
  printf("- Marcar consulta\n");
  printf("- Listar consultas\n");
  printf("- Desmarcar consulta\n");
  printf("- Listar consultas por codigo de cliente\n");
  printf("- Listar consultas que ocorreram ha mais de 6 meses de clientes com mais de 50 anos\n");
  printf("- Sobre o programa\n");
  printf("- Sair\n");
  printf("\n");
  system("pause");
}

void debugMenu() {
  char op;

  do {
    system("cls");
    printf("\e[?25l");
    printf("================================  MENU  "
           "=======================================\n");
    printf("|ESC - Voltar ao menu principal |\n");
    printf("1 - Listar clientes\n");
    printf("2 - Listar consultas\n");
    op = getch();

    switch (op) {
      case '1':
        listarClientes();
        break;

      case '2':
        listarConsultas();
        break;

      case 27: // Tecla ESC para sair
        break;

      default:
        break;
    }
  } while (op != 27); // Continue até que a tecla ESC seja pressionada
}

//Cria o contexto do menu inicial
void menu() {
  char op;

  do {
    system("cls");
    printf("\e[?25l");
    printf("================================  MENU  "
           "=======================================\n");
    printf("|ESC - Sair | F1 - Sobre o Programa|\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Alterar dados do cliente\n");
    printf("3 - Marcar consulta\n");
    printf("4 - Desmarcar consulta\n");
    printf("5 - Mapa de horarios para um determinado dia\n");
    printf("6 - Listar consulta por paciente\n");
    printf("7 - Consultas de clientes com mais de 50 anos que ocorreram ha mais de 6 meses\n");
    printf("8 - DEBUG - Funcoes de teste\n");
    op = getch();

    switch (op) {
      case '1':
        cadastrarCliente();
        break;

      case '2':
        atualizarCliente();
        break;

      case '3':
        marcarConsulta();
        break;

      case '4':
        desmarcarConsulta();
        break;
        
      case '5':
    	  mapaHorarios();
        break;

      case '6':
        listarConsultasCodCliente();
        break;

      case '7':
        consultasHa6Meses();
        break;

      case '8':
        debugMenu();
        break;

      case 27: // Tecla ESC para sair
        system("cls");
        printf("\nSaindo do programa...\n\n");
        system("pause");
        break;

      case 0: // Tecla F1 para Sobre o Programa
        sobre();
        break;

      default:
        break;
    }
  } while (op != 27); // Continue até que a tecla ESC seja pressionada
  desmarcarConsultaRemFis();
}
