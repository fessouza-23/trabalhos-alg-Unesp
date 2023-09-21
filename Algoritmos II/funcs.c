#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.h"

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
    system("cls");

    FILE *file;
    Cliente c;
    int cod_gen = 0;
    
    file = abrirArquivo("clientes.dat", "r+t");

    printf("CADASTRO DE NOVO CLIENTE\n");

    while (fread(&c, sizeof(Cliente), 1, file) == 1) {
        if(c.codigo == cod_gen)
            cod_gen++;
        if(c.codigo != cod_gen)
            c.codigo = cod_gen;
    }
    fflush(stdin); // limpa o buffer

    // Usado para limpar o buffer, nao apagar
    // while (getchar() != '\n');

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
        printf("Cliente nao encontrado!\n");
    } else if(flag == 2) {
        printf("Cliente nao alterado!\n");
    } else {
        printf("Cliente atualizado com sucesso!\n");
    }
    
    printf("\nPressione qualquer tecla para voltar ao menu.\n");
    getch();
}

void marcarConsulta() {
    system("cls");

    FILE *file;

    Consulta consulta;

    file = abrirArquivo("consultas.dat", "ab");

    consulta.existe = 1;
    printf("Digite o codigo da consulta: ");
    scanf("%d", &consulta.codigo);

    while (getchar() != '\n');

    printf("Digite o nome do paciente que esta agendando a consulta: ");
    fgets(consulta.nomeDoCliente, sizeof(consulta.nomeDoCliente), stdin);
    consulta.nomeDoCliente[strlen(consulta.nomeDoCliente) - 1] = '\0';

    printf("Digite a data da consulta (DIA/MES/ANO): \n");
    scanf("%d/%d/%d", &consulta.dia, &consulta.mes, &consulta.ano);

    while (getchar() != '\n');

    printf("Digite o horario da consulta (HORA:MINUTO): \n");
    scanf("%d:%d", &consulta.hora, &consulta.minuto);

    while (getchar() != '\n');

    fwrite(&consulta, sizeof(Consulta), 1, file);
    fclose(file);

    printf("\nPressione qualquer tecla para voltar ao menu.\n");
    getch();
}

// Esta função não está dentro das necessárias, serve apenas para testar
void listarConsultas() {
    system("cls");

    FILE *file;
    Consulta consulta;

    file = abrirArquivo("consultas.dat", "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
        if (consulta.existe)
            printf("Codigo: %2d | Nome: %15s | Data: %2d/%d/%d | Horario: %2d:%d\n", consulta.codigo, consulta.nomeDoCliente, consulta.dia, consulta.mes, consulta.ano, consulta.hora, consulta.minuto);
    }

    fclose(file);
    getch();
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

    printf("\nPressione qualquer tecla para voltar ao menu.\n");
    getch();
}

void desmarcarConsultaRemFis() {
    system("cls");

    FILE *file, *auxfile;
    Consulta consulta;

    file = abrirArquivo("consultas.dat", "rb");

    auxfile = fopen("NOME.BAK", "wb");

    while (fread(&consulta, sizeof(Consulta), 1, file) == 1) 
    {
        if (consulta.existe)
            fwrite(&consulta, sizeof(Consulta), 1, auxfile);
    }

    fclose(file);
    fclose(auxfile);

    remove("consultas.dat");
    rename ("NOME.BAK", "consultas.dat");

    printf("Remocao fisica realizada com sucesso\n");
    getch();
}

void datasConsulta(){
    system("cls");

    FILE *file;
    Consulta consulta;
    Cliente c;
    int cod, cont = 0;
    char aux[50];
    
    printf("Digite o codigo do cliente:\n");
    scanf("%d",&cod);

    file = abrirArquivo("clientes.dat", "rb");

    while (fread(&c, sizeof(Cliente), 1, file) == 1) {
        if(cod == c.codigo)
        strcpy(aux, c.nome);
    }

    fclose(file);

    file = abrirArquivo("consultas.dat", "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&consulta, sizeof(Consulta), 1, file) == 1) {
        if (strcmp(aux, consulta.nomeDoCliente)==0){
            printf("Codigo: %2d | Nome: %15s | Data: %2d/%d/%d | Horario: %2d:%d\n", consulta.codigo, consulta.nomeDoCliente, consulta.dia, consulta.mes, consulta.ano, consulta.hora, consulta.minuto);
            cont++;
        }
    }

    if(cont == 0)
    printf("\nNenhuma consulta marcada com esse cliente! Verifique o codigo digitado ou marque uma nova consulta.\n");

    fclose(file);
    getch();
}

void menu() {
    char op;
    Cliente c;
    Consulta consulta;

    do {
        system("cls");
        printf("\e[?25l");
        printf("================================  MENU  "
            "=======================================\n");
        printf("|ESC - Sair | F1 - Sobre o Programa|\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Atualizar cliente\n");
        printf("4 - Marcar consulta\n");
        printf("5 - Listar consultas\n");
        printf("6 - Desmarcar consultas\n");
        printf("8 - Listar consulta por cliente\n");
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
                desmarcarConsultaRemFis();
                break;

            case '8':
                datasConsulta();
                break;

            case f1:
                sobre();
                break;
        }

    } while (op != esc);
}