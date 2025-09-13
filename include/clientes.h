#ifndef clientes_h
#define clientes_h



typedef struct {
    int id;
    char nome[50];
    char preferencia[50];
    int paciencia;
    int MoedasDisponiveis;
}tp_cliente;

void CriarCliente(tp_cliente *cliente, int id, const char *nome, const char *preferencia, int paciencia, int moedas);
/*
void GetnomeCliente(tp_cliente *cliente, char *nome);
  
void GetprefCliente(tp_cliente *cliente, char *preferencia);

void GetpaciCliente(tp_cliente *cliente, int *paciencia);

void dimPaciencia(tp_cliente *cliente);
*/
#endif