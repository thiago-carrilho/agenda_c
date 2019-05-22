#include <stdio.h>
#include <stdlib.h>

void tela_inicial();
int menu();
int adicionar();
int excluir();
void listar();
void sair();

int semTelaInicial=0;

struct sContato{
    char nome[30];
    char telefone[30];
    int idade;
}typedef contato;

int main()
{
    if(semTelaInicial==0){
        tela_inicial();    
    }
    else{
        contato lista[100];
        int retorno = menu();
        switch(retorno){
            case 1://Novo Contato
                printf("\nNovo Contato");
                //adiconar();
                break;
            case 2://Excluir Contato
                printf("\nExcluir Contato");
                //excluir();
                break;
            case 3://Editar Contato
                printf("\nEditar Contato");
                //editar();
                break;
            case 4:
                printf("\nListar Contatos");
                //listar();
                break;
            case 6:
                system("cls||clear");
                sair();
                break;
        }
    }
    return 0;
}

int adicionar(){
    return 0;
}

int excluir(){
    return 0;
}

void listar(){

}

void tela_inicial(){
    char continuar;
    printf("%57s\n%73s","AGENDA","Para continuar aperte qualquer tecla\n");
    scanf("%c", &continuar);
    if(continuar!=0){
        system("cls||clear");
        semTelaInicial=1;
        main();
    }
}

int menu(){
    printf("Digite a opcao desejada:\n1 - Novo Contato\n2 - Excluir Contato\n3 - Editar Contato\n4 - Listar Contato\n6 - Sair\n");
    int entrada = 0;
    scanf("%d",&entrada);
    return entrada;
}

void sair(){
    int continuar;
    printf("Deseja sair? (digite 1 para sair)\n");
    scanf("%d", &continuar);
    if(continuar==1){
        exit(0);
    }
    else{
        system("cls||clear");
        main();
    }
}