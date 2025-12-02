/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Luan
 *
 * Created on 17 de Junho de 2018, 17:54
 */

#include <stdio.h>
#include <stdlib.h>
#define qtd_livros 100
#define qtd_clientes 100

struct Cliente 
{
    int codigo_cliente;
    char nome[100];
    char cpf[20];
    char rg[20];
};
typedef struct Cliente Cliente;

struct Livro 
{
    int codigo;
    char titulo[100];
    char autor[100];
    int isbn;
    int ano;
    struct Cliente *cliente;
};
typedef struct Livro Livro;

void cadastroLivro(Livro *livro, int codigo)
{
    livro->codigo = codigo;
    setbuf(stdin,NULL);
    printf("\nDigite o título: ");
    scanf("%[^\n]s", livro->titulo);
    setbuf(stdin,NULL);
    printf("\nDigite o autor: ");
    scanf("%[^\n]s", livro->autor);
    setbuf(stdin,NULL);
    printf("\nDigite o ISBN: ");
    scanf("%d", &livro->isbn);
    printf("\nDigite o ano: ");
    scanf("%d", &livro->ano);
    printf("Digite o código do cliente que deseja emprestar: ");
}

void listaLivro(Livro *livro)
{
    printf("\nTítulo : %s", livro->titulo);
    printf("\nAutor : %s", livro->autor);
    printf("\nISBN : %d", livro->isbn);
    printf("\nAno : %d", livro->ano);
}

void listaLivroArquivo(Livro *livro)
{
    FILE *fp = fopen("livros","r");
    Livro livros[qtd_livros];
    int numLivros = qtd_livros;
    //Leitura do arquivo
    fread(&numLivros, sizeof(int),1,fp);
    fread(livros, sizeof(Livro), numLivros, fp);
    printf("-------------------------------------------------------\n");
    
    //Imprime os dados do livro contido no arquivo
    for(int i = 0; i < numLivros ; i++)
    {
        printf("Título: %s", livros[i].titulo);
        printf("\nAutor: %s", livros[i].autor);		
        printf("\nISBN: %d", livros[i].isbn);
        printf("\nANO: %d", livros[i].ano);
        printf("\n-------------------------------------------------------\n");
    }
	
    fclose(fp);
}

void inicializaBiblioteca(Livro *biblioteca)
{
    for(int i=0; i < qtd_livros; i++)
    {
        biblioteca[i].codigo = -1;
    }
}

void inicializaCliente(Cliente *cliente)
{
    for(int i = 0; i < qtd_clientes; i++)
    {
        cliente[i].codigo_cliente = -1;
    }
}  

void cadastrarNovoLivro(Livro *biblioteca, int codigo)
{
    for(int i=0; i < qtd_livros; i++)
    {
        if(biblioteca[i].codigo == -1)
        {
            cadastroLivro(&biblioteca[i], codigo);
            break;
	}
    }
}

void cadastrarNovoCliente(Cliente *cliente, int codigo)
{
    for(int i=0; i < qtd_clientes; i++)
    {
        if(cliente[i].codigo_cliente == -1)
        {
            cadastroCliente(&cliente[i], codigo);
            break;
	}
    }
}

void cadastroCliente(Cliente *cliente, int codigo_cliente)
{
    cliente->codigo_cliente = codigo_cliente;
    setbuf(stdin,NULL);
    printf("\nDigite o nome do cliente: ");
    scanf("%[^\n]s", cliente->nome);
    setbuf(stdin,NULL);
    printf("\nDigite o CPF do cliente: ");
    scanf("%[^\n]s", cliente->cpf);
    setbuf(stdin,NULL);
    printf("\nDigite o RG do cliente: ");
    scanf("%[^\n]s", cliente->rg);
}

void listaCliente(Cliente *cliente)
{
    printf("\nNome: %s", cliente->nome);
    printf("\nCPF: %s", cliente->cpf);
    printf("\nRG: %s", cliente->rg);
}

void listaClienteArquivo(Cliente *cliente)
{
    FILE *fpc = fopen("clientes","rb");
    Cliente clientes[qtd_clientes];
    int numClientes;
    //Leitura do arquivo
    fread(&numClientes, sizeof(int),1,fpc);
    fread(clientes, sizeof(Cliente), numClientes, fpc);
    
    //Lista os dados do cliente contido no arquivo
    for(int i =0; i < numClientes; i++)
    {
        printf("Nome: %s", clientes[i].nome);
        printf("\nCPF: %s", clientes[i].cpf);		
        printf("\nRG: %s", clientes[i].rg);
        printf("\n-------------------------------------------------------\n");
    }
	
    fclose(fpc);
}

/*
 * 
 */


int main(int argc, char** argv) {
    int comando;    //Variável de controle das operações da biblioteca.
    Livro livros[qtd_livros];
    Cliente clientes[qtd_clientes];
    printf("Digite 0 para sair!\n");
    printf("Digite 1 para cadastrar um novo livro e 2 para visualizá-lo!\n");
    printf("Digite 3 para cadastrar um novo cliente e 4 para visualizá-lo!\n");
    scanf("%d", &comando);
    while(comando!=0)
    {
        if(comando==1)
        {
            FILE *fp = fopen("livros","a");
            if (fp == NULL)
            {
                printf("erro ao abrir arquivo");
                return -1;
            }
            int codigo;
            inicializaBiblioteca(livros);

            printf("\nDigite o código do livro: ");
            scanf("%d", &codigo);
			
			//Insere os dados do livro até parar quando o código for -1
            while(codigo != -1)
            {
                printf("\nInsira um livro ");
                cadastrarNovoLivro(livros,codigo);				
                printf("\nDigite o código do livro: ");
                scanf("%d", &codigo);	
            }

            printf("\nDados inseridos:");
            for(int i =0; i < qtd_livros; i++)
            {
                   if(livros[i].codigo != -1)
                       listaLivro(&livros[i]);
            }
            printf("\n");
            //Armazena um vetor da struct Livro no arquivo
            int numLivros = qtd_livros;
            fwrite(&numLivros, sizeof(int), 1, fp);
            fwrite(livros, sizeof(Livro),qtd_livros, fp);
            fclose(fp);
        }

        if(comando==2)
            listaLivroArquivo(&livros);

        if(comando==3)
        {
            FILE *fpc = fopen("clientes","a");
            if (fpc == NULL)
            {
                printf("erro ao abrir arquivo");
                return -1;
            }
            int codigo_cliente;
            inicializaCliente(clientes);

            printf("\nDigite o código do cliente: ");
            scanf("%d", &codigo_cliente);
			
			//Insere os dados do cliente até parar quando o código for -1
            while(codigo_cliente != -1)
            {
                printf("\nInsira um cliente ");
                cadastroCliente(clientes, codigo_cliente);				
                printf("\nDigite o código do cliente: ");
                scanf("%d", &codigo_cliente);	
            }

            printf("\nDados inseridos:");
            for(int i =0; i < qtd_clientes; i++)
            {
                   if(livros[i].codigo != -1)
                       listaCliente(&clientes[i]);
            }
            printf("\n");
            //Armazena um vetor da struct Cliente num arquivo
            int numClientes = qtd_clientes;
            fwrite(&numClientes, sizeof(int), 1, fpc);
            fwrite(clientes, sizeof(Cliente),qtd_clientes, fpc);
            fclose(fpc);
        }
    
        if(comando==4)
            listaClienteArquivo(&clientes);
        
        printf("Digite 0 para sair!\n");
        printf("Digite 1 para cadastrar um novo livro e 2 para visualizá-lo!\n");
        printf("Digite 3 para cadastrar um novo cliente e 4 para visualizá-lo!\n");
        scanf("%d", &comando);
    }
    return (EXIT_SUCCESS);
}

