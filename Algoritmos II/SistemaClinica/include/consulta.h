#ifndef CONSULTA_H
#define CONSULTA_H

#define esc 27
#define f1 59

void marcarConsulta();

void desmarcarConsulta();

void listarConsultas();

void desmarcarConsultaRemFis();

void listarConsultasCodCliente();

Consulta funcConsultaRecente(const Cliente *cliente);

void consultasHa6Meses();

#endif