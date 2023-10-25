#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/cliutils.h"
#include "../include/consulta.h"

//Verifica se o nome do cliente existe no arquivo clientes.dat
int codigoClienteExiste(int codigo) {
  Cliente cliente;
  
  FILE *file = fopen("clientes.dat", "rb");
  if (file == NULL) {
    return 0; // Se o arquivo não puder ser aberto, consideramos que o nome não existe
  }

  while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
    if (cliente.codigo == codigo) { // Codigo encontrado no arquivo
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  return 0; // Codigo não encontrado no arquivo
}

//Verifica se o nome do cliente existe no arquivo clientes.dat
int nomeClienteExiste(const char *nome) {
  FILE *file = fopen("clientes.dat", "rb");
  if (file == NULL) {
    return 0; // Se o arquivo não puder ser aberto, consideramos que o nome não existe
  }

  Cliente cliente;
  while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
    if (strcmp(cliente.nome, nome) == 0) {
      fclose(file);
      return 1; // Nome encontrado no arquivo
    }
  }

  fclose(file);
  return 0; // Nome não encontrado no arquivo
}

//Marca uma consulta de um cliente ja existente a partir de seu codigo
//utilizando a funcao codigoClienteExiste()
void marcarConsulta() {
  system("cls");

  FILE *file;
  Consulta consulta;
  int cod_gen = 0;

  printf("Deseja marcar uma consulta (S\\N)?\n");
  if (!confirma()) {
    return;
  }

  system("cls");
  printf("\e[?25h");

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

  printf("Codigo do paciente para consulta: ");
  scanf("%d", &consulta.codigoDoCliente);

  /*
  //Verifique se o codigo do cliente existe no arquivo
  if (!codigoClienteExiste(consulta.codigoDoCliente)) {
    printf("O codigo do cliente nao foi encontrado no arquivo clientes.dat.\n");
    fclose(file);
    printf("\n");
    system("pause");
    return;
  }*/

  while (getchar() != '\n');
  
  printf("Nome do paciente para consulta: ");
  fgets(consulta.nomeDoCliente, sizeof(consulta.nomeDoCliente), stdin);
  consulta.nomeDoCliente[strlen(consulta.nomeDoCliente) - 1] = '\0';

  for (int i = 0; consulta.nomeDoCliente[i]; i++) {
    consulta.nomeDoCliente[i] = toupper(consulta.nomeDoCliente[i]);
  }

  // Verifique se o nome do cliente existe no arquivo
  if (!nomeClienteExiste(consulta.nomeDoCliente)) {
    printf("O nome do cliente nao foi encontrado no arquivo clientes.dat.\n");
    fclose(file);
    printf("\n");
    system("pause");
    return;
  }

  // Validação da data
  do {
    printf("Data da consulta (DIA/MES/ANO): ");
    if (scanf("%d/%d/%d", &consulta.dia, &consulta.mes, &consulta.ano) != 3) {
      printf("Formato de data invalido. Use o formato DIA/MES/ANO.\n");
      while (getchar() != '\n');
    }
  } while (consulta.dia < 1 || consulta.mes < 1 || consulta.mes > 12 || consulta.ano < 1900 ||
           (consulta.dia > 31 || (consulta.mes == 2 && consulta.dia > 29) ||
            ((consulta.mes == 4 || consulta.mes == 6 || consulta.mes == 9 || consulta.mes == 11) && consulta.dia > 30)));

  // Validação do horário
  do {
    printf("Horario da consulta (HORA:MINUTO): ");
    if (scanf("%d:%d", &consulta.hora, &consulta.minuto) != 2) {
      printf("Formato de horário invalido. Use o formato HORA:MINUTO.\n");
      while (getchar() != '\n');
    }
  } while (consulta.hora < 0 || consulta.hora > 23 || consulta.minuto < 0 || consulta.minuto > 59);

  while (getchar() != '\n');

  fwrite(&consulta, sizeof(Consulta), 1, file);
  fclose(file);

  printf("\n");
  system("pause");
}

//Lista todas as consultas que estao no arquivo consultas.dat
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

//Desmarca uma consulta a partir do seu codigo
//Remove os dados apenas virtualmente por meio de uma flag
void desmarcarConsulta() {
  system("cls");

  FILE *file;
  Consulta consulta;
  int numero, flag = 0;

  printf("Deseja desmarcar uma consulta (S\\N)?\n");
  if (!confirma()) {
    return;
  }

  system("cls");
  printf("\e[?25h");

  printf("Codigo da consulta que deseja desmarcar: ");
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
  while (getchar() != '\n');
  system("pause");
}

//Remove fisicamente o arquivo consulta.dat
//So eh chamado no fim do programa
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
}

//Lista todas as consultas de um cliente a partir de seu codigo
void listarConsultasCodCliente() {
  system("cls");

  FILE *file;
  Consulta consulta;
  Cliente c;
  int cod, cont = 0, clienteAchou = 0;
  char aux[50];

  printf("Deseja listar as consultas do cliente (S\\N)?\n");
  if (!confirma()) {
    return;
  }

  printf("Codigo do cliente: ");
  scanf("%d", &cod);

  system("cls");

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

  printf("================================= LISTA DE CONSULTAS "
         "==================================\n");
  printf("| %-8s | %-25s | %-10s | %-3s |\n", "Codigo", "Nome", "Data", "Horario");
  printf("---------------------------------------------------------------\n");

  while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
    if ((strcmp(aux, consulta.nomeDoCliente) == 0) && consulta.existe == 1) {
      printf("| %-8d | %-25s | %02d/%02d/%04d |  %02d:%02d  |\n",
             consulta.codigo, consulta.nomeDoCliente,
             consulta.dia, consulta.mes, consulta.ano,
             consulta.hora, consulta.minuto);
      cont++;
    }
  }

  if (cont == 0)
    printf("\nNenhuma consulta marcada com esse cliente! Verifique o codigo "
           "digitado ou marque uma nova consulta.\n");

  fclose(file);
  system("pause");
  while (getchar() != '\n');
}

/*
 as duas funções abaixo possuem função de achar os clientes com mais de 50 anos
 em que suas consultas foram realizadas há mais de 6 meses, a primeira faz
 realiza a verificação da consulta mais atual do cliente, e a segunda verifica
 se está já ocorreu há mais de 6 meses ou não
*/
Consulta funcConsultaRecente(const Cliente *cliente) {
  FILE *arquivoConsultas;
  Consulta consulta;
  Consulta consultaMaisRecente;
  consultaMaisRecente.ano = 0;
  consultaMaisRecente.mes = 0;
  consultaMaisRecente.dia = 0;
  consultaMaisRecente.hora = 0;
  consultaMaisRecente.minuto = 0;

  arquivoConsultas = abrirArquivo("consultas.dat", "rb");

  while (fread(&consulta, sizeof(Consulta), 1, arquivoConsultas) == 1)
  {
    if (consulta.existe == 1 && strcmp(consulta.nomeDoCliente, cliente->nome) == 0)
    {
      consultaMaisRecente = consulta;
    }
  }

  fclose(arquivoConsultas);
  return consultaMaisRecente;
}

Consulta consultaMaisRecente;

void consultasHa6Meses() {
  FILE *arquivoClientes;
  Cliente cliente;
  int cont;

  arquivoClientes = abrirArquivo("clientes.dat", "rb");

  system("cls");

  time_t horaAtual = time(NULL);
  struct tm seisMesesAtras;
  struct tm dataDaConsulta;

  // Subtrai 6 meses do tempo atual
  seisMesesAtras = *gmtime(&horaAtual);
  seisMesesAtras.tm_mon -= 6;

  printf("Consultas que ocorreram ha mais de 6 meses de cliente com mais de 50 anos:\n\n");
  printf("================================= LISTA DE CONSULTAS "
         "==================================\n");
  printf("| %-25s | %-15s |\n", "Nome do Cliente", "Telefone");
  printf("-----------------------------------------------\n");

  while (fread(&cliente, sizeof(Cliente), 1, arquivoClientes))
  {
    if (cliente.idade > 50)
    {
      consultaMaisRecente = funcConsultaRecente(&cliente);
      dataDaConsulta.tm_year = consultaMaisRecente.ano - 1900;
      dataDaConsulta.tm_mon = consultaMaisRecente.mes - 1;
      dataDaConsulta.tm_mday = consultaMaisRecente.dia;
      dataDaConsulta.tm_hour = consultaMaisRecente.hora;
      dataDaConsulta.tm_min = consultaMaisRecente.minuto;
      dataDaConsulta.tm_sec = 0;

      double diferenca = difftime(horaAtual, mktime(&dataDaConsulta));

      if (diferenca > 15778800)
      {
        printf("| %-25s | %-15s |\n", consultaMaisRecente.nomeDoCliente, cliente.fone);
        cont++;
      }
    }
  }

  fclose(arquivoClientes);
  getch();
}

void mapaHorarios() {
	system("cls");
  int dia = 0, mes = 0;
  int achouConsulta = 0; 

  printf("Deseja listar o mapa de horarios (S\\N)?\n");
  if (!confirma()) {
    return;
  }
  
  system("cls");
  printf("Digite o dia: ");
  scanf("%d", &dia);

  printf("Digite o mes (NUMERO DO MES): ");
  scanf("%d", &mes);
  	
  FILE *file;
  Consulta consulta;

  file = abrirArquivo("consultas.dat", "rb");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  printf("================================= LISTA DE CONSULTAS PARA O DIA %d"
         "==================================\n", dia);
  printf("| %-8s | %-25s | %-10s | %-3s |\n", "Codigo", "Nome", "Data", "Horario");
  printf("---------------------------------------------------------------\n");

  while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
  	
    if (consulta.existe && consulta.dia == dia && consulta.mes == mes) {
      printf("| %-8d | %-25s | %02d/%02d/%04d |  %02d:%02d  |\n",
             consulta.codigo, consulta.nomeDoCliente,
             consulta.dia, consulta.mes, consulta.ano,
             consulta.hora, consulta.minuto);
      achouConsulta = 1;
    }
    
  }

  fclose(file);

  if (!achouConsulta) {
  	
    printf("Nenhuma consulta foi encontrada neste dia.\n");
  }
  
  printf("\n");
  system("pause");
}
