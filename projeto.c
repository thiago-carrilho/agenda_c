#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 100
struct sContato
{
    char nome[30];
    char telefone[11];
    int idade;
} typedef contato;

void tela_inicial();
int menu();
int adicionar(contato *, int);
int excluir();
void listar(contato *, int, int[]);
int sair();
int strLen(char[]);
int strBuscar(char[], char[]);

int semTelaInicial = 0;

contato lista[ARRAYSIZE];

int main()
{
    if (semTelaInicial == 0)
    {
        tela_inicial();
    }
    if (semTelaInicial == 1)
    {
        int retorno = 0, qrSair = 0, tamanhoLista = 0;
        while (qrSair == 0)
        {
            retorno = menu();
            switch (retorno)
            {
            case 1: //Novo Contato
                if (tamanhoLista != (ARRAYSIZE - 1))
                {
                    tamanhoLista = adicionar(lista, tamanhoLista);
                }
                break;
            case 2: //Excluir Contato
                break;
            case 3: //Editar Contato
                //editar();
                break;
            case 4:
                system("cls||clear");
                int temp[100] = {-1};
                listar(lista, tamanhoLista, temp);
                break;
            case 5: //procurar
                //se esse case não tiver chaves não pode declarar variaveis dentro. dá erro.
                system("cls||clear");
                if (tamanhoLista == 0)
                {
                    printf("Nenhum Cadastro na Agenda.\n");
                    break;
                }
                else
                {
                    int escolha = 0, contadorLista, contadordeResultado = 0, resultado = 0, indicesIgual[100] = {[0 ... 99] = -1};
                    char subString[30];
                    printf("Digite 1 para pesquisar uma parte do nome\nDigite 2 para pesquisar uma parte do telefone\n\n");
                    scanf("%d", &escolha);
                    switch (escolha)
                    {
                    case 1:
                        printf("Digite o nome: ");
                        scanf(" %s", subString);
                        for (contadorLista = 0; contadorLista < ARRAYSIZE; contadorLista++)
                        {
                            if (*lista[contadorLista].nome != '\000')
                            {
                                resultado = strBuscar(subString, lista[contadorLista].nome);
                                if (resultado == 1)
                                {
                                    if (contadorLista == 0)
                                    {
                                        indicesIgual[contadordeResultado] = 0;
                                    }
                                    else
                                    {
                                        contadordeResultado += 1;
                                        indicesIgual[contadordeResultado] = contadorLista;
                                    }
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        if (indicesIgual[0] != -1)
                        {
                            listar(lista, contadordeResultado + 1, indicesIgual);
                        }
                        break;
                    case 2:
                        printf("Digite o telefone: ");
                        scanf(" %s", subString);
                        for (contadorLista = 0; contadorLista < ARRAYSIZE; contadorLista++)
                        {
                            if (*lista[contadorLista].telefone != '\000')
                            {
                                resultado = strBuscar(subString, lista[contadorLista].telefone);
                                if (resultado == 1)
                                {
                                    if (contadorLista == 0)
                                    {
                                        indicesIgual[contadordeResultado] = 0;
                                    }
                                    else
                                    {
                                        contadordeResultado += 1;
                                        indicesIgual[contadordeResultado] = contadorLista;
                                    }
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        if (indicesIgual[0] != -1)
                        {
                            listar(lista, contadordeResultado + 1, indicesIgual);
                        }
                        break;
                    default:
                        printf("Digite uma opcao valida!");
                        break;
                    }
                    break;
                }
            case 6:
                qrSair = sair();
                break;
            default:
                system("cls||clear");
                printf("Opcao invalida!\n");
                break;
            }
        }
    }
    return 0;
}

int adicionar(contato *vLista, int tLista)
{
    system("cls||clear");
    printf("Digite o nome: ");
    scanf(" %[^\n]s", vLista[tLista].nome);
    printf("Digite o telefone: ");
    scanf("%s", vLista[tLista].telefone);
    printf("Digite a idade: ");
    scanf("%d", &vLista[tLista].idade);
    system("cls||clear");
    return tLista + 1;
}

int excluir()
{
    return 0;
}

void listar(contato *vLista, int tLista, int resultados[100])
{
    char continuar;
    int contador;
    system("cls||clear");
    if (tLista == 0)
    {
        printf("Nenhum Cadastro na Agenda.\n");
    }
    else
    {
        if (resultados[0] != -1)
        {
            printf("Resultados da Pesquisa\n");
        }
        printf("ID | Nome | Telefone | Idade\n");
        for (contador = 0; contador < tLista; contador++)
        {
            if (resultados[0] != -1)
            {
                printf("%d | %s | %s | %d\n", (contador + 1), vLista[resultados[contador]].nome, vLista[resultados[contador]].telefone, vLista[resultados[contador]].idade);
            }
            else
            {
                printf("%d | %s | %s | %d\n", (contador + 1), vLista[contador].nome, vLista[contador].telefone, vLista[contador].idade);
            }
        }
    }
    printf("Pressione ENTER para voltar.");
    scanf("%c", &continuar);
    getchar();
    system("cls||clear");
    return;
}

void tela_inicial()
{
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
    if (continuar != 0)
    {
        system("cls||clear");
        semTelaInicial = 1;
        return;
    }
}

int menu()
{
    printf("Digite a opcao desejada:\n1 - Novo Contato\n2 - Excluir Contato\n3 - Editar Contato\n4 - Listar Contatos\n5 - Procurar Contato\n6 - Sair\n\n");
    int entrada = 0;
    scanf("%d", &entrada);
    return entrada;
}

int sair()
{
    int continuar;
    system("cls||clear");
    printf("Deseja sair? (digite 1 para sair)\n");
    scanf("%d", &continuar);
    if (continuar == 1)
    {
        return 1;
    }
    else
    {
        system("cls||clear");
        return 0;
    }
}

int strLen(char string[])
{
    int tamanho = 0;
    while (string[tamanho] != '\0')
    {
        tamanho += 1;
    }
    return tamanho;
}

int strBuscar(char subString[30], char strCompleto[30])
{
    int tamanhoCompleto = strLen(strCompleto), tamanhoSub = strLen(subString);
    int contadorStrCompleta=0, contadorSubStr = 0, contadorLista, diferente = 0, temp = 0;
    while(diferente==0)
    {   
        if(strCompleto[contadorStrCompleta]=='\0'){
            diferente=1;
        }
        else if (strCompleto[contadorStrCompleta] == subString[contadorSubStr])
        {
            temp = contadorStrCompleta;
            while (diferente == 0)
            {
                if (strCompleto[temp] != subString[contadorSubStr])
                {
                    diferente = 1;
                }
                if (subString[contadorSubStr] == '\0')
                {
                    return 1;
                }
                temp += 1;
                contadorSubStr += 1;
            }
        }
    contadorStrCompleta+=1;
    }
    return 0;
}