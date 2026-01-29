#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

// DESAFIO: GRAVAR ORDENADO

//===SUB-MENU====
//+++++MENU USUARIOS++++
void menuUsuarios(Usuario **usuarios, int *totalUsuarios)
{
    int opcao;
    do
    {
        printf("\n===== GERENCIAMENTO DE USUARIOS =====\n");
        printf("1 - Registrar Usuarios\n");
        printf("2 - Listar Usuarios\n");
        printf("3 - Buscar Usuarios\n");
        printf("4 - Remover Usuarios\n");
        printf("5 - Atualizar Usuarios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Informe total de usuarios que deseja cadastrar: ");
            int n;
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                RegistrarUsuario(usuarios, totalUsuarios);
            }
            break;
        case 2:
            ListarUsuario(*usuarios, (*totalUsuarios));
            break;
        case 3:
            BuscarUsuario(*usuarios, (*totalUsuarios));
            break;
        case 4:
            RemoverUsuario(usuarios, totalUsuarios);
            break;
        case 5:
            AtualizarUsuario(*usuarios, (*totalUsuarios)); //(*totalUsuarios) --> desrreferencio para pegar o conteudo
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

//+++++MENU LIVROS+++++
void menuLivros(Livro **livros, int *totalLivros)
{
    int opcao;
    do
    {
        printf("\n===== GERENCIAMENTO DE LIVROS =====\n");
        printf("1 - Registrar Livros\n");
        printf("2 - Listar Livros\n");
        printf("3 - Buscar Livros\n");
        printf("4 - Remover Livros\n");
        printf("5 - Atualizar Livros\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:

            printf("Informe total de livros que deseja cadastrar: ");
            int n;
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                RegistrarLivro(livros, totalLivros);
            }
            break;
        case 2:
            ListarLivro(*livros, (*totalLivros));
            break;
        case 3:
            BuscarLivro(*livros, (*totalLivros));
            break;
        case 4:
            RemoverLivro(livros, totalLivros);
            break;
        case 5:
            AtualizarLivro(*livros, (*totalLivros));
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

//====RELATORIO====
int gerarRelatorio(Livro *livros, int totalLivros, Usuario *usuarios, int totalUsuarios, const char *relatorioTxt)
{
    FILE *f = fopen(relatorioTxt, "w");
    if (f == NULL)
        return 1;

    fprintf(f, "=====RELATÓRIO COMPLETO====\n");
    fprintf(f, "Total de Usuarios: %d\n", totalUsuarios);
    fprintf(f, "Total de Livros: %d\n", totalLivros);
    fprintf(f, "----------------------------------------\n");
    fprintf(f, "====USUARIOS====\n");

    for (int i = 0; i < totalUsuarios; i++)
    {
        fprintf(f, "Nome: %s\n", usuarios[i].nome);   // string
        fprintf(f, "CPF: %d\n", usuarios[i].cpf);     // inteiro
        fprintf(f, "Idade: %d\n", usuarios[i].idade); // inteiro
        fprintf(f, "-----------------------------\n");
    }

    fprintf(f, "====LIVROS====\n");

    for (int i = 0; i < totalLivros; i++)
    {
        fprintf(f, "ID: %d\n", livros[i].id);
        fprintf(f, "Título: %s\n", livros[i].nome);
        fprintf(f, "Autor: %s\n", livros[i].autor);
        fprintf(f, "Ano: %d\n", livros[i].ano);
        fprintf(f, "-----------------------------\n");
    }

    fclose(f);
    return 0;
}


//=====BINARIO=====
//++++++USUARIO BINARIO+++++
int salvarUsuarioBinario(Usuario *usuarios, int totalUsuarios, const char *arqUsuarioBin)
{
    FILE *f = fopen(arqUsuarioBin, "wb");
    if (f == NULL)
        return 1;

    if (totalUsuarios > 0)
    {

        size_t escritos = fwrite(
            usuarios,
            sizeof(Usuario),
            (size_t)totalUsuarios,
            f);

        if (escritos != (size_t)totalUsuarios)
        {
            fprintf(stderr,
                    "Erro: fwrite escreveu %zu de %d itens\n",
                    escritos,
                    totalUsuarios);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int carregarDadosUsuarioBinario(Usuario **usuarios, int *totalUsuarios, const char *arqUsuarioBin)
{
    FILE *f = fopen(arqUsuarioBin, "rb");
    if (f == NULL)
    {
        *usuarios = NULL;
        *totalUsuarios = 0;
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long bytes = ftell(f); // minha variavel bytes recebe o resultado de ftell
    rewind(f);

    if (bytes <= 0)
    {
        fclose(f);
        *usuarios = NULL;
        *totalUsuarios = 0;
        return 1;
    }

    int qtd = (int)(bytes / sizeof(Usuario));
    Usuario *tmp = malloc(qtd * sizeof(Usuario));

    if (tmp == NULL)
    {
        fclose(f);
        return 1;
    }

    size_t lidos = fread(tmp, sizeof(Usuario), (size_t)qtd, f);
    fclose(f);
    if (lidos != (size_t)qtd)
    {
        fprintf(stderr, "Erro: fread leu %zu de %d items\n", lidos, qtd);
        free(tmp);
        *usuarios = NULL;
        *totalUsuarios = 0;
        return 1;
    }

    fclose(f);
    *usuarios = tmp;
    *totalUsuarios = qtd;
    return 0;
}

//+++++BINARIO LIVROS+++++
int salvarLivroBinario(Livro *livros, int totalLivros, const char *arqLivroBin)
{
    FILE *f = fopen(arqLivroBin, "wb");
    if (f == NULL)
        return 1;

    if (totalLivros > 0)
    {

        size_t escritos = fwrite(
            livros,
            sizeof(Livro),
            (size_t)totalLivros,
            f);

        if (escritos != (size_t)totalLivros)
        {
            fprintf(stderr,
                    "Erro: fwrite escreveu %zu de %d itens\n",
                    escritos,
                    totalLivros);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int carregarDadosLivroBinario(Livro **livros, int *totalLivros, const char *arqLivroBin)
{
    FILE *f = fopen(arqLivroBin, "rb");
    if (f == NULL)
    {
        *livros = NULL;
        *totalLivros = 0;
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long bytes = ftell(f);
    rewind(f);

    if (bytes <= 0)
    {
        fclose(f);
        *livros = NULL;
        *totalLivros = 0;
        return 1;
    }

    int qtd = (int)(bytes / sizeof(Livro));
    Livro *tmp = malloc(qtd * sizeof(Livro));

    if (tmp == NULL)
    {
        fclose(f);
        return 1;
    }

    size_t lidos = fread(tmp, sizeof(Livro), (size_t)qtd, f);
    fclose(f);
    if (lidos != (size_t)qtd)
    {
        fprintf(stderr, "Erro: fread leu %zu de %d items\n", lidos, qtd);
        free(tmp);
        *livros = NULL;
        *totalLivros = 0;
        return 1;
    }

    fclose(f);
    *livros = tmp;
    *totalLivros = qtd;
    return 0;
}

//====CRUD USUARIO=====

//+++++REGISTRAR USUARIO+++++
int RegistrarUsuario(Usuario **usuarios, int *totalUsuarios)
{
    int cpfTemp;
    printf("=====REGISTRAR USUARIO=====\n");
    printf("Informe CPF: ");
    scanf("%d", &cpfTemp);

    for (int i = 0; i < *totalUsuarios; i++)
    {
        if ((*usuarios)[i].cpf == cpfTemp)
        {
            printf("Erro: Usuario ja cadastrado!");
            return 1;
        }
    }

    (*totalUsuarios)++;
    Usuario *tmp = realloc(*usuarios, *totalUsuarios * sizeof(Usuario));
    if (tmp == NULL)
    {
        printf("Erro!");
        (*totalUsuarios)--;
        return 1;
    }
    else
    {
        *usuarios = tmp;
        (*usuarios)[(*totalUsuarios) - 1].cpf = cpfTemp;
        printf("Informe nome: ");
        scanf(" %49[^\n]", (*usuarios)[(*totalUsuarios) - 1].nome);
        printf("Informe idade: ");
        scanf("%d", &(*usuarios)[(*totalUsuarios) - 1].idade);
        printf("Usuario cadastrado com sucesso!\n");
    }

    salvarUsuarioBinario(*usuarios, *totalUsuarios, "dadosUsuario.bin");
    return 0;
}

//++++REMOVER USUARIO++++
int RemoverUsuario(Usuario **usuarios, int *totalUsuarios)
{
    if (*totalUsuarios <= 0 || *usuarios == NULL)
    {
        printf("Nenhum usuario cadastrado");
        return 1;
    }

    int cpf, i;
    printf("======REMOVER USUARIO======\n");
    printf("Informe o CPF do usuario a ser removido: ");
    scanf("%d", &cpf);

    int posicao = -1;
    for (i = 0; i < *totalUsuarios; i++)
    {
        if ((*usuarios)[i].cpf == cpf)
        {
            posicao = i;
            break;
        }
    }

    if (posicao == -1)
    {
        printf("Usuario nao encontrado!");
        return 1;
    }

    for (i = posicao; i < *totalUsuarios - 1; i++)
    {
        (*usuarios)[i] = (*usuarios)[i + 1];
    }

    (*totalUsuarios)--;

    if (*totalUsuarios == 0)
    {
        free(*usuarios);
        *usuarios = NULL;
        printf("Usuario removido com sucesso!\n");
        printf("Ultimo usuario removido. Vetor apagado.");
        return 0;
    }

    Usuario *tmp = realloc(*usuarios, *totalUsuarios * sizeof(Usuario));
    if (tmp != NULL)
    {
        *usuarios = tmp;
    }
    else
    {
        printf("Erro!");
    }

    printf("Usuario removido com sucesso!");

    salvarUsuarioBinario(*usuarios, *totalUsuarios, "dadosUsuario.bin");
    return 0;
}

//++++ATUALIZAR USUARIO++++//
int AtualizarUsuario(Usuario *usuarios, int totalUsuarios)
{
    if (totalUsuarios <= 0 || usuarios == NULL) // verifica se tem usuario cadastrado
    {
        printf("Nenhum usuario cadastrado");
        return 1;
    }

    int cpf, i;
    printf("======ATUALIZAR USUARIO======\n");
    printf("Informe o CPF do usuario a ser atualizado: ");
    scanf("%d", &cpf);

    int posicao = -1;
    for (i = 0; i < totalUsuarios; i++) // percorre o vetor de usuarios
    {
        if (usuarios[i].cpf == cpf)
        {
            posicao = i;
            break;
        }
    }

    if (posicao == -1)
    {
        printf("Usuario nao encontrado!");
        return 1;
    }

    printf("Informe novo nome: ");
    scanf(" %49[^\n]", usuarios[posicao].nome);
    printf("Informe novo idade: ");
    scanf("%d", &usuarios[posicao].idade);
    printf("Informe novo CPF: ");
    scanf("%d", &usuarios[posicao].cpf);
    printf("Usuario atualizado com sucesso!\n");

    salvarUsuarioBinario(usuarios, totalUsuarios, "dadosUsuario.bin");
    return 0;
}

//+++++BUSCAR USUARIO+++++//
int BuscarUsuario(Usuario *usuarios, int totalUsuarios)
{
    if (totalUsuarios <= 0 || usuarios == NULL) // verifica se tem usuario cadastrado
    {
        printf("Nenhum usuario cadastrado");
        return 1;
    }

    int cpf, i;
    printf("======BUSCAR USUARIO======\n");
    printf("Informe o CPF do usuario a ser buscado: ");
    scanf("%d", &cpf);

    for (i = 0; i < totalUsuarios; i++) // percorre o vetor de usuarios
    {
        if (usuarios[i].cpf == cpf) // compara o cpf informado com o cpf do usuario
        {
            printf("Usuario encontrado:\n");
            printf("Nome: %s\n", usuarios[i].nome);
            printf("CPF: %d\n", usuarios[i].cpf);
            printf("Idade: %d\n", usuarios[i].idade);
            return 0;
        }
    }

    printf("Usuario nao encontrado!");
    return 1;
}

//+++++LISTAR USUARIO++++++//
void ListarUsuario(Usuario *usuarios, int totalUsuarios)
{
    if (totalUsuarios <= 0 || usuarios == NULL) // verifica se tem usuario cadastrado
    {
        printf("Nenhum usuario cadastrado");
    }

    printf("=====LISTA DE USUARIOS=====\n");
    for (int i = 0; i < totalUsuarios; i++) // percorre o vetor de usuarios
    {
        printf("Usuario %d:\n", i + 1);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("CPF: %d\n", usuarios[i].cpf);
        printf("Idade: %d\n", usuarios[i].idade);
        printf("----------------------------\n");
    }
}

//====CRUD LIVROS=====

//+++++REGISTRAR LIVRO+++++
int RegistrarLivro(Livro **livros, int *totalLivros)
{
    int idTemp;
    printf("=====REGISTRAR LIVROS=====\n");
    printf("Informe ID: ");
    scanf("%d", &idTemp);

    for (int i = 0; i < *totalLivros; i++)
    {
        if ((*livros)[i].id == idTemp)
        {
            printf("Erro: Livro ja cadastrado!");
            return 1;
        }
    }

    (*totalLivros)++;
    Livro *tmp = realloc(*livros, *totalLivros * sizeof(Livro));
    if (tmp == NULL)
    {
        printf("Erro!");
        (*totalLivros)--;
        return 1;
    }
    else
    {
        *livros = tmp;
        (*livros)[(*totalLivros) - 1].id = idTemp;
        printf("Informe nome: ");
        scanf(" %49[^\n]", (*livros)[(*totalLivros) - 1].nome);
        printf("Informe ano: ");
        scanf("%d", &(*livros)[(*totalLivros) - 1].ano);
        printf("Informe autor: ");
        scanf(" %49[^\n]", (*livros)[(*totalLivros) - 1].autor);
        printf("Livro cadastrado com sucesso!\n");
    }

    salvarLivroBinario(*livros, *totalLivros, "dadosLivro.bin");
    return 0;
}

//++++REMOVER LIVRO++++
int RemoverLivro(Livro **livros, int *totalLivros)
{
    if (*totalLivros <= 0 || *livros == NULL)
    {
        printf("Nenhum livro cadastrado");
        return 1;
    }

    int id, i;
    printf("======REMOVER LIVROS======\n");
    printf("Informe o ID do livro a ser removido: ");
    scanf("%d", &id);

    int posicao = -1;
    for (i = 0; i < *totalLivros; i++)
    {
        if ((*livros)[i].id == id)
        {
            posicao = i;
            break;
        }
    }

    if (posicao == -1)
    {
        printf("Livro nao encontrado!");
        return 1;
    }

    for (i = posicao; i < *totalLivros - 1; i++)
    {
        (*livros)[i] = (*livros)[i + 1];
    }

    (*totalLivros)--;

    if (*totalLivros == 0)
    {
        free(*livros);
        *livros = NULL;
        printf("Livro removido com sucesso!\n");
        printf("Ultimo livro removido. Vetor apagado.");
        return 0;
    }

    Livro *tmp = realloc(*livros, *totalLivros * sizeof(Livro));
    if (tmp != NULL)
    {
        *livros = tmp;
    }
    else
    {
        printf("Erro!");
    }

    printf("Livro removido com sucesso!");

    salvarLivroBinario(*livros, *totalLivros, "dadosLivro.bin");
    return 0;
}

//++++ATUALIZAR LIVRO++++//
int AtualizarLivro(Livro *livros, int totalLivros)
{
    if (totalLivros <= 0 || livros == NULL)
    {
        printf("Nenhum livro cadastrado");
        return 1;
    }

    int id, i;
    printf("======ATUALIZAR LIVRO======\n");
    printf("Informe o ID do livro a ser atualizado: ");
    scanf("%d", &id);

    int posicao = -1;
    for (i = 0; i < totalLivros; i++)
    {
        if (livros[i].id == id)
        {
            posicao = i;
            break;
        }
    }

    if (posicao == -1)
    {
        printf("Livro nao encontrado!");
        return 1;
    }

    printf("Informe novo nome: ");
    scanf(" %49[^\n]", livros[posicao].nome);
    printf("Informe novo ano: ");
    scanf("%d", &livros[posicao].ano);
    printf("Informe novo autor: ");
    scanf(" %49[^\n]", livros[posicao].autor);
    printf("Informe novo ID: ");
    scanf("%d", &livros[posicao].id);
    printf("Livro atualizado com sucesso!\n");

    salvarLivroBinario(livros, totalLivros, "dadosLivro.bin");
    return 0;
}

//+++++BUSCAR LIVRO+++++//
int BuscarLivro(Livro *livros, int totalLivros)
{
    if (totalLivros <= 0 || livros == NULL)
    {
        printf("Nenhum livro cadastrado");
        return 1;
    }

    int id, i;
    printf("======BUSCAR LIVRO======\n");
    printf("Informe o ID do livro a ser buscado: ");
    scanf("%d", &id);

    for (i = 0; i < totalLivros; i++)
    {
        if (livros[i].id == id)
        {
            printf("Livro encontrado:\n");
            printf("Nome: %s\n", livros[i].nome);
            printf("ID: %d\n", livros[i].id);
            printf("Ano: %d\n", livros[i].ano);
            printf("Autor: %s\n", livros[i].autor);
            return 0;
        }
    }

    printf("Livro nao encontrado!");
    return 1;
}

//+++++LISTAR LIVRO++++++//
void ListarLivro(Livro *livros, int totalLivros)
{
    if (totalLivros <= 0 || livros == NULL)
    {
        printf("Nenhum livro cadastrado\n");
    }

    printf("=====LISTA DE LIVROS=====\n");
    for (int i = 0; i < totalLivros; i++)
    {
        printf("Livro %d:\n", i + 1);
        printf("Nome: %s\n", livros[i].nome);
        printf("ID: %d\n", livros[i].id);
        printf("Ano: %d\n", livros[i].ano);
        printf("Autor: %s\n", livros[i].autor);
        printf("----------------------------\n");
    }
}
