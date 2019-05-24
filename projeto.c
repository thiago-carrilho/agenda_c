#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 100
struct sContato{
    char nome[30];
    char telefone[11];
    int idade;
}typedef contato;

void tela_inicial();
int menu();
int adicionar(contato *,int);
int excluir();
void listar(contato *,int);
int sair();

int semTelaInicial=0;

contato lista[ARRAYSIZE]={0};

int main()
{
    if(semTelaInicial==0){
        tela_inicial();    
        contato lista[ARRAYSIZE]={0};
    }
    if(semTelaInicial==1){
        int retorno=0, qrSair = 0,tamanhoLista=0;
        while(qrSair==0){
            retorno = menu();
            switch(retorno){
                case 1://Novo Contato
                    system("cls||clear");
                    if(tamanhoLista!=(ARRAYSIZE-1)){
                        tamanhoLista=adicionar(lista,tamanhoLista);
                    }
                    break;
                case 2://Excluir Contato
                    break;
                case 3://Editar Contato
                    //editar();
                    break;
                case 4:
                    system("cls||clear");
                    listar(lista,tamanhoLista);
                    break;
                case 6:
                    system("cls||clear");
                    qrSair = sair();
                    break;
                default:
                    printf("Opção inválida.");
                    break;
            }
        }            
    }
    return 0;
}

int adicionar(contato *vLista,int tLista){
    printf("Digite o nome: ");
    scanf("%s",vLista[tLista].nome);
    printf("Digite o telefone: ");
    scanf("%s",vLista[tLista].telefone);
    printf("Digite a idade: ");
    scanf("%d",&vLista[tLista].idade);
    system("cls||clear");
    return tLista+1;
}

int excluir(){
    return 0;
}

void listar(contato *vLista,int tLista){
    char continuar;
    int contador;
    if(tLista==0){
        printf("Nenhum Cadastro na Agenda.");
    }
    else{
        printf("Nome | Telefone | Idade");
        for(contador=0;contador<tLista;contador++){
            printf("%s | %s | %d\n",vLista[contador].nome,vLista[contador].telefone,vLista[contador].idade);
        }
    }
    printf("Pressione ENTER para voltar.");
    scanf("%c", &continuar);
    getchar();
    system("cls||clear");
    return;
    
}

void tela_inicial(){
    char continuar;
    printf("\n\n\n\n\n%105s\n%105s\n%105s\n%105s\n%105s\n%105s\n%105s\n\n\n\n\n%70s",
            "      .o.         .oooooo.    oooooooooooo ooooo      ooo oooooooooo.         .o.       ",
            "     .888.       d8P'  `Y8b   `888'     `8 `888b.     `8' `888'   `Y8b       .888.      ",
            "    .8\"888.     888            888          8 `88b.    8   888      888     .8\"888.     ",
            "   .8' `888.    888            888oooo8     8   `88b.  8   888      888    .8' `888.    ",
            "  .88ooo8888.   888     ooooo  888    \"     8     `88b.8   888      888   .88ooo8888.   ",
            " .8'     `888.  `88.    .88'   888       o  8       `888   888     d88'  .8'     `888.  ",
            "o88o     o8888o  `Y8bood8P'   o888ooooood8 o8o        `8  o888bood8P'   o88o     o8888o ",
            "Para continuar pressione ENTER");
    scanf("%c", &continuar);
    if(continuar!=0){
        system("cls||clear");
        semTelaInicial=1;
        return;
    }
}

int menu(){
    printf("Digite a opcao desejada:\n1 - Novo Contato\n2 - Excluir Contato\n3 - Editar Contato\n4 - Listar Contato\n6 - Sair\n\n");
    int entrada = 0;
    scanf("%d",&entrada);
    return entrada;
}

int sair(){
    int continuar;
    printf("Deseja sair? (digite 1 para sair)\n");
    scanf("%d", &continuar);
    if(continuar==1){
        return 1;
    }
    else{
        system("cls||clear");
        return 0;
    }
}