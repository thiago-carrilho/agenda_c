#include <stdio.h>
#include <stdlib.h>

struct sContato
{
    char nome[30];
    char telefone[30];
    int idade;
} typedef contato;

void tela_inicial();
int menu();
void adicionar(contato *, int);
void excluir(contato *, int);
void editar(contato *, int);
void listar(contato *, int);
void procurar(contato *, int, int[]);
int sair();
int strLen(char[]);
int strBuscar(char[], char[]);
int arqExiste();
void procurarMenu(contato *, int);
void removerdoArray(contato *, int, int);
int selecaoId(contato *, int, int);
void salvarAlteracoes(contato *, int);

int semTelaInicial = 0;

int main()
{
    if (semTelaInicial == 0)
    {
        tela_inicial();
    }
    if (semTelaInicial == 1)
    {
        int retorno = 0, qrSair = 0, tamanhoLista = 0, existe = arqExiste();
        contato *lista;
        if (existe == 0)
        {
            tamanhoLista = 1;
            lista = malloc(1 * sizeof(contato));
        }
        else
        {
            FILE *arqContador = fopen("contador.txt", "r");
            int contador = 0;
            fscanf(arqContador, "%d", &contador);
            fclose(arqContador);
            lista = malloc(contador * sizeof(contato));
            FILE *arq = fopen("contatos.dat", "rb");
            if (arq == NULL)
            {
                printf("Erro.");
                exit(1);
            }
            while (fread(&lista[tamanhoLista], sizeof(contato), 1, arq) == 1)
            {
                tamanhoLista += 1;
            }
            fclose(arq);
        }
        while (qrSair == 0)
        {
            retorno = menu();
            switch (retorno)
            {
            case 1: //Novo Contato
                if (existe != 0)
                {
                    tamanhoLista += 1;
                    lista = realloc(lista, tamanhoLista * sizeof(contato));
                }
                adicionar(lista, tamanhoLista);
                if (existe == 0)
                    existe = 1;
                printf("Contato adicionado\n");
                salvarAlteracoes(lista, tamanhoLista);
                break;
            case 2: //Excluir Contato
                system("cls||clear");
                if (tamanhoLista == 0)
                {
                    printf("Nenhum Cadastro na Agenda.\n");
                    break;
                }
                else
                {
                    excluir(lista, tamanhoLista);
                    tamanhoLista -= 1;
                    lista = realloc(lista, tamanhoLista * sizeof(contato));
                    system("cls||clear");
                    salvarAlteracoes(lista, tamanhoLista);
                    printf("Contato deletado\n");
                }
                break;
            case 3: //Editar Contato
                system("cls||clear");
                if (tamanhoLista == 0)
                {
                    printf("Nenhum Cadastro na Agenda.\n");
                    break;
                }
                else
                {
                    editar(lista, tamanhoLista);
                    salvarAlteracoes(lista, tamanhoLista);
                    printf("Contato editado\n");
                    system("cls||clear");
                }
                break;
            case 4: //listar
                system("cls||clear");
                listar(lista, tamanhoLista);
                system("cls||clear");
                break;
            case 5: //procurar
                system("cls||clear");
                if (tamanhoLista == 0)
                {
                    printf("Nenhum Cadastro na Agenda.\n");
                    break;
                }
                else
                {
                    procurarMenu(lista, tamanhoLista);
                    system("cls||clear");
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

void salvarAlteracoes(contato *vLista, int tLista)
{
    int contador;
    FILE *arqExcluir = fopen("contatos.dat", "wb");
    fclose(arqExcluir);
    FILE *arq = fopen("contatos.dat", "ab");
    FILE *arqContador = fopen("contador.txt", "w");
    fprintf(arqContador, "%d", tLista);
    fclose(arqContador);
    for (contador = 0; contador < tLista; contador++)
    {
        fwrite(&vLista[contador], sizeof(contato), 1, arq);
    }
    fclose(arq);
}

void editar(contato *vLista, int tLista)
{
    int id = selecaoId(vLista, tLista, 1), escolha = 0, valida = 1, novaIdade = 0;
    char novoNome[30], novoTelefone[30];
    while (valida == 1)
    {
        valida = 0;
        printf("\nDigite 1 para editar o nome\nDigite 2 para editar o telefone\nDigite 3 para editar a idade\n\n");
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1: //nome
            printf("\nDigite o novo nome: ");
            scanf("%s", vLista[id - 1].nome);
            break;
        case 2: //telefone
            printf("\nDigite o novo telefone: ");
            scanf("%s", vLista[id - 1].telefone);
            break;
        case 3: //idade
            printf("\nDigite a nova idade: ");
            scanf("%s", &vLista[id - 1].idade);
            break;
        default:
            system("cls||clear");
            printf("Digite uma opcao valida!!\n");
            valida = 1;
            break;
        }
    }
}

void procurarMenu(contato *vLista, int tLista)
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
        for (contadorLista = 0; contadorLista < tLista; contadorLista++)
        {
            resultado = strBuscar(subString, vLista[contadorLista].nome);
            if (resultado == 1)
            {
                indicesIgual[contadordeResultado] = contadorLista;
                contadordeResultado += 1;
            }
        }
        if (indicesIgual[0] != -1)
        {
            procurar(vLista, contadordeResultado, indicesIgual);
        }
        else
        {
            printf("Nenhum Cadastro na Agenda com esse nome.\n");
        }
        break;
    case 2:
        printf("Digite o telefone: ");
        scanf(" %s", subString);
        for (contadorLista = 0; contadorLista < tLista; contadorLista++)
        {

            resultado = strBuscar(subString, vLista[contadorLista].telefone);
            if (resultado == 1)
            {
                indicesIgual[contadordeResultado] = contadorLista;
                contadordeResultado += 1;
            }
        }
        if (indicesIgual[0] != -1)
        {
            procurar(vLista, contadordeResultado, indicesIgual);
        }
        else
        {
            printf("Nenhum Cadastro na Agenda com esse telefone.\n");
        }
        break;
    default:
        printf("Digite uma opcao valida!");
        break;
    }
}

void adicionar(contato *vLista, int tLista)
{
    system("cls||clear");
    printf("Digite o %d nome: ", tLista);
    scanf(" %s", vLista[tLista - 1].nome);
    printf("Digite o telefone: ");
    scanf(" %s", vLista[tLista - 1].telefone);
    printf("Digite a idade: ");
    scanf("%d", &vLista[tLista - 1].idade);
    system("cls||clear");
}

int arqExiste()
{
    FILE *arq;
    if (arq = fopen("test2e22.dat", "rb"))
    {
        return 1;
    }
    return 0;
}

int selecaoId(contato *vLista, int tLista, int opcao)
{
    int escolha = 0, id = -1, escolhaProcura = 0, loopValido = 1;
    while (loopValido != 0)
    {
        if (opcao == 0)
        {
            printf("Para excluir um contato e necessario saber o ID\nCaso ja saiba digite 1, caso nao digite 2: ");
        }
        else if (opcao)
        {
            printf("Para editar um contato e necessario saber o ID\nCaso ja saiba digite 1, caso nao digite 2: ");
        }
        scanf(" %d", &escolha);
        loopValido = 0;
        switch (escolha)
        {
        case 1:
            printf("\nDigite o ID: ");
            scanf(" %d", &id);
            break;
        case 2:
            printf("\nDigite 1 para listar todos contatos\nDigite 2 para procurar um contato\n\n");
            scanf(" %d", &escolhaProcura);
            switch (escolhaProcura)
            {
            case 1:
                listar(vLista, tLista);
                printf("\nDigite o ID: ");
                scanf(" %d", &id);
                break;
            case 2:
                printf("\n\n");
                procurarMenu(vLista, tLista);
                printf("\nDigite o ID: ");
                scanf(" %d", &id);
                break;
            default:
                system("cls||clear");
                printf("Digite uma opcao valida!!\n");
                loopValido = 1;
                break;
            }
            break;
        default:
            system("cls||clear");
            printf("Digite uma opcao valida!!\n");
            loopValido = 1;
            break;
        }
        if (id > tLista)
        {
            printf("Digite um ID entre 1 e %d!!\n", tLista);
            loopValido = 1;
        }
    }
    return id;
}

void removerdoArray(contato *vLista, int idRemover, int tLista)
{
    int contador;
    for (contador = (idRemover - 1); contador < tLista - 1; contador++)
    {
        vLista[contador] = vLista[contador + 1];
    }
}

void excluir(contato *vLista, int tLista)
{
    int id = selecaoId(vLista, tLista, 0);
    removerdoArray(vLista, id, tLista);
}

void procurar(contato *vLista, int tLista, int resultados[100])
{
    int contador = 0;
    char continuar;
    printf("\nResultados da Pesquisa\nID | Nome | Telefone | Idade\n");
    for (contador = 0; contador < tLista; contador++)
    {
        printf("%d | %s | %s | %d\n", resultados[contador] + 1, vLista[resultados[contador]].nome, vLista[resultados[contador]].telefone, vLista[resultados[contador]].idade);
    }
    printf("Pressione ENTER para voltar.");
    scanf("%c", &continuar);
    getchar();
}

void listar(contato *vLista, int tLista)
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
        printf("ID | Nome | Telefone | Idade\n");
        for (contador = 0; contador < tLista; contador++)
        {
            printf("%d | %s | %s | %d\n", (contador + 1), vLista[contador].nome, vLista[contador].telefone, vLista[contador].idade);
        }
    }
    printf("Pressione ENTER para voltar.");
    scanf("%c", &continuar);
    getchar();
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
    scanf(" %d", &entrada);
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

int strBuscar(char subString[30], char strCompleta[30])
{
    int tamanhoCompleto = strLen(strCompleta), tamanhoSub = strLen(subString);
    int contadorStrCompleta = 0, contadorSubStr = 0, contadorLista, diferente = 0, temp = 0;
    while (diferente == 0)
    {
        if (strCompleta[contadorStrCompleta] == '\0')
        {
            diferente = 1;
        }
        else if (strCompleta[contadorStrCompleta] == subString[contadorSubStr])
        {
            temp = contadorStrCompleta;
            while (diferente == 0)
            {
                if (strCompleta[temp] != subString[contadorSubStr])
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
        contadorStrCompleta += 1;
    }
    return 0;
}