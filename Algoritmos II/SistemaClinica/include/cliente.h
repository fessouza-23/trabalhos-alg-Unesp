#ifndef CLIENTE_H
#define CLIENTE_H

#define esc 27
#define f1 59

void cadastrarCliente();

void listarClientes();

void atualizarCliente();

int nomeClienteExiste(const char *nome);

int codigoClienteExiste(int codigo);

#endif