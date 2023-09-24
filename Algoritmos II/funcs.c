#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcs.h"

FILE *abrirArquivo(const char nome_arquivo[20], const char op[5]) {
  FILE *file;

  if ((file = fopen(nome_arquivo, op)) == NULL) {
    printf("Erro ao abrir o arquivo.\n\n");
    system("pause");
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

void cadastrarCliente() {
  system("cls");

  FILE *file;
  Cliente c;
  int cod_gen = 0;

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

  printf("Idade: ");
  scanf("%d", &c.idade);

  while (getchar() != '\n');

  printf("Endereco: ");
  fgets(c.endereco, sizeof(c.endereco), stdin);
  c.endereco[strlen(c.endereco) - 1] = '\0';

  printf("Telefone: ");
  fgets(c.fone, sizeof(c.fone), stdin);
  c.fone[strlen(c.fone) - 1] = '\0';

  // Gravação do Cliente no arquivo
  fwrite(&c, sizeof(Cliente), 1, file);
  fclose(file);
}

// Esta função não está dentro das necessárias, serve apenas para testar
void consultarCliente() {
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

void atualizarCliente() {
  system("cls");

  FILE *file;
  int codigo_ref; // Código de referência = código digitado para procurar o cliente
  Cliente c;
  int flag = 0;

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

        while (getchar() != '\n');

        printf("Novo Nome: ");
        gets(c.nome);

        printf("Nova Idade: ");
        scanf("%d", &c.idade);

        while (getchar() != '\n');

        printf("Novo Endereco: ");
        gets(c.endereco);

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
  system("pause");
}

void marcarConsulta() {
  system("cls");

  FILE *file;
  Consulta consulta;
  int cod_gen = 0;

  if ((file = fopen("consultas.dat", "r+b")) == NULL) {
    file = fopen("consultas.dat", "wb");
  } else {
    while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
      if (consulta.codigo >= cod_gen)
        cod_gen = consulta.codigo + 1;
    }
    fseek(file, 0, SEEK_END); // Vá para o final do arquivo
  }

  consulta.existe = 1;
  consulta.codigo = cod_gen; // Defina o código antes de coletar outros dados

  fflush(stdin);

  printf("Nome do paciente para consulta: ");
  fgets(consulta.nomeDoCliente, sizeof(consulta.nomeDoCliente), stdin);
  consulta.nomeDoCliente[strlen(consulta.nomeDoCliente) - 1] = '\0';

  printf("Data da consulta (DIA/MES/ANO): ");
  scanf("%d/%d/%d", &consulta.dia, &consulta.mes, &consulta.ano);

  while (getchar() != '\n');

  printf("Horario da consulta (HORA:MINUTO): ");
  scanf("%d:%d", &consulta.hora, &consulta.minuto);

  while (getchar() != '\n');

  fwrite(&consulta, sizeof(Consulta), 1, file);
  fclose(file);

  printf("\n");
  system("pause");
}

// Esta função não está dentro das necessárias, serve apenas para testar
void listarConsultas() {
  system("cls");

  FILE *file;
  Consulta consulta;
  int consultasEncontradas = 0; // Variável para rastrear se consultas foram encontradas

  file = abrirArquivo("consultas.dat", "rb");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  printf("================================= LISTA DE CONSULTAS "
         "==================================\n");
  printf("| %-8s | %-25s | %-10s | %-3s |\n", "Codigo", "Nome", "Data", "Horario");
  printf("---------------------------------------------------------------\n");

  while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
    if (consulta.existe) {
      printf("| %-8d | %-25s | %02d/%02d/%04d |  %02d:%02d  |\n",
             consulta.codigo, consulta.nomeDoCliente,
             consulta.dia, consulta.mes, consulta.ano,
             consulta.hora, consulta.minuto);
      consultasEncontradas = 1; // Consultas foram encontradas
    }
  }

  fclose(file);

  if (!consultasEncontradas) {
    printf("Nenhuma consulta encontrada.\n");
  }
  printf("\n");
  system("pause");
}

void desmarcarConsulta() {
  system("cls");

  FILE *file;
  Consulta consulta;
  int numero, flag = 0;

  printf("Digite o codigo da consulta que deseja desmarcar: ");
  scanf("%d", &numero);

  file = abrirArquivo("consultas.dat", "r+b");

  while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
    if (consulta.existe && consulta.codigo == numero) {
      system("cls");
      printf("Consulta encontrada de codigo %d\n", consulta.codigo);

      printf("Nome: %s\n", consulta.nomeDoCliente);
      printf("Data: %d/%d/%d", consulta.dia, consulta.mes, consulta.ano);

      printf("\nDeseja realmente desmarcar a consulta? (s/n): ");
      if (confirma()) {
        consulta.existe = 0;

        fseek(file, -sizeof(Consulta), SEEK_CUR);
        fwrite(&consulta, sizeof(Consulta), 1, file);
        fflush(file);
        printf("Consulta desmarcada com sucesso\n");

      } else {
        printf("Consulta de codigo %d nao pode ser removida", &consulta.codigo);
      }
      flag = 1;
      break;
    }
  }

  if (!flag) {
    printf("Nao existe consulta com esse codigo\n");
  }

  fclose(file);

  printf("\n");
  system("pause");
}

void desmarcarConsultaRemFis() {
  system("cls");

  FILE *file, *auxfile;
  Consulta consulta;

  file = abrirArquivo("consultas.dat", "rb");

  auxfile = fopen("NOME.BAK", "wb");

  while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
    if (consulta.existe)
      fwrite(&consulta, sizeof(Consulta), 1, auxfile);
  }

  fclose(file);
  fclose(auxfile);

  remove("consultas.dat");
  rename("NOME.BAK", "consultas.dat");

  printf("Remocao fisica realizada com sucesso\n");
  getch();
}

void listarConsultasCodCliente() {
  system("cls");

  FILE *file;
  Consulta consulta;
  Cliente c;
  int cod, cont = 0;
  char aux[50];

  printf("Digite o codigo do cliente: ");
  scanf("%d", &cod);

  file = abrirArquivo("clientes.dat", "rb");

  while (fread(&c, sizeof(Cliente), 1, file) == 1) {
    if (cod == c.codigo)
      strcpy(aux, c.nome);
  }

  fclose(file);

  file = abrirArquivo("consultas.dat", "rb");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
    if ((strcmp(aux, consulta.nomeDoCliente) == 0) && consulta.existe == 1) {
      printf("Codigo da consulta: %2d | Nome: %2s | Data: %2d/%d/%d | Horario: "
             "%2d:%d\n",
             consulta.codigo, consulta.nomeDoCliente, consulta.dia,
             consulta.mes, consulta.ano, consulta.hora, consulta.minuto);
      cont++;
    }
  }

  if (cont == 0)
    printf("\nNenhuma consulta marcada com esse cliente! Verifique o codigo "
           "digitado ou marque uma nova consulta.\n");

  fclose(file);
  getch();
}

void consultasHa6Meses() {
  FILE *arquivoConsultas, *arquivoClientes;
  Consulta consulta;
  Cliente cliente;
  int cont = 0;

  system("cls");

  arquivoConsultas = abrirArquivo("consultas.dat", "rb");
  arquivoClientes = abrirArquivo("clientes.dat", "rb");

  time_t horaAtual = time(NULL);
  struct tm seisMesesAtras;
  struct tm dataDaConsulta;

  // Subtrai 6 meses do tempo atual
  seisMesesAtras = *gmtime(&horaAtual);
  seisMesesAtras.tm_mon -= 6;

  while (fread(&consulta, sizeof(Consulta), 1, arquivoConsultas) == 1) {
    if (consulta.existe == 1) {
      dataDaConsulta.tm_year = consulta.ano - 1900;
      dataDaConsulta.tm_mon = consulta.mes - 1;
      dataDaConsulta.tm_mday = consulta.dia;
      dataDaConsulta.tm_hour = consulta.hora;
      dataDaConsulta.tm_min = consulta.minuto;
      dataDaConsulta.tm_sec = 0;

      // Calcula a diferença em segundos entre as datas
      double diferenca = difftime(horaAtual, mktime(&dataDaConsulta));

      // Verifica se a consulta ocorreu há mais de 6 meses
      if (diferenca > 15778800) {
        // Abre o arquivo de clientes e procura o cliente pelo código
        fseek(arquivoClientes, (consulta.codigo - 1) * sizeof(Cliente), SEEK_SET);
        fread(&cliente, sizeof(Cliente), 1, arquivoClientes);

        // Verifica a idade do cliente
        if (cliente.idade > 50) {
          printf("Nome do Cliente: %s | Telefone: %s\n", cliente.nome, cliente.fone);
          cont++;
        }
      }
    }
  }

  if (cont == 0)
    printf("\nNenhum cliente atende aos criterios especificados!\n");

  fclose(arquivoConsultas);
  fclose(arquivoClientes);
  getch();
}

void menu() {
  char op;
  Cliente c;
  Consulta consulta;

  do {
    system("cls");
    printf("\e[?25l"); // Oculta o cursor piscante
    printf("\n================================== MENU "
           "=====================================\n");
    printf(" 1 - Cadastrar Cliente\n");
    printf(" 2 - Listar Clientes\n");
    printf(" 3 - Atualizar Cliente\n");
    printf(" 4 - Marcar Consulta\n");
    printf(" 5 - Listar Consultas\n");
    printf(" 6 - Desmarcar Consulta\n");
    printf(" 7 - Listar Consultas por Cliente\n");
    printf(" 8 - Consultas de Clientes com mais de 50 anos\n");
    printf(" 9 - Sobre o Programa\n");
    printf(" 0 - Sair\n");
    printf("\nEscolha uma opcao: ");

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

      case '4':
        marcarConsulta();
        break;

      case '5':
        listarConsultas();
        break;

      case '6':
        desmarcarConsulta();
        break;

      case '7':
        listarConsultasCodCliente();
        break;

      case '8':
        consultasHa6Meses();
        break;

      case '9':
        sobre();
        break;

      case '0':
        system("cls");
        printf("\nSaindo do programa...\n\n");
        system("pause");
        break;

      default:
        printf("\nOpcao invalida! Tente novamente.\n");
        break;
    }
  } while (op != '0');
}