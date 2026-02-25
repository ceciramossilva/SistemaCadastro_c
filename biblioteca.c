#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"


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


//+++++MENU EMPRESTIMOS+++++
void menuEmprestimos(Emprestimo **emprestimos, int *totalEmprestimos, Usuario *usuarios, int totalUsuarios, Livro *livros, int totalLivros)
{
    int opcao;
    do
    {
        printf("\n===== GERENCIAMENTO DE EMPRESTIMOS =====\n");
        printf("1 - Registrar Emprestimos\n");
        printf("2 - Listar Emprestimos\n");
        printf("3 - Buscar Emprestimos\n");
        printf("4 - Remover Emprestimos\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);


        switch (opcao)
        {
        case 1:
            RegistrarEmprestimo(emprestimos, totalEmprestimos, usuarios, totalUsuarios, livros, totalLivros);
            break;
        case 2:
            ListarEmprestimo(*emprestimos, (*totalEmprestimos));
            break;
        case 3:
            BuscarEmprestimo(*emprestimos, (*totalEmprestimos));
            break;
        case 4:
            RemoverEmprestimo(emprestimos, totalEmprestimos);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}


// DESAFIO: GRAVAR ORDENADO


//+++ORDENAR USUARIOS+++
void ordenarUsuariosPorNome(Usuario *usuarios, int totalUsuarios)
{
    if (totalUsuarios < 2)
        return;


    Usuario temp;


    for (int i = 0; i < totalUsuarios - 1; i++)
    {
        for (int j = 0; j < totalUsuarios - i - 1; j++)
        {
            if (strcmp(usuarios[j].nome, usuarios[j + 1].nome) > 0)
            {


                temp = usuarios[j];
                usuarios[j] = usuarios[j + 1];
                usuarios[j + 1] = temp;
            }
        }
    }
    printf("Usuarios ordenados A-Z\n");
}


//+++ORDENAR LIVROS+++
void ordenarLivrosPorNome(Livro *livros, int totalLivros)
{
    if (totalLivros < 2)
        return;


    Livro temp;


    for (int i = 0; i < totalLivros - 1; i++)
    {
        for (int j = 0; j < totalLivros - i - 1; j++)
        {
            if (strcmp(livros[j].nome, livros[j + 1].nome) > 0)
            {


                temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
    printf("Livros ordenados A-Z\n");
}


//====RELATORIO====
int gerarRelatorio(Livro *livros, int totalLivros, Usuario *usuarios, int totalUsuarios, Emprestimo *emprestimos, int totalEmprestimos, const char *relatorioTxt)
{
    FILE *f = fopen(relatorioTxt, "w");
    if (f == NULL)
        return 1;


    ordenarUsuariosPorNome(usuarios, totalUsuarios);
    ordenarLivrosPorNome(livros, totalLivros);
    fprintf(f, "=====RELATÓRIO COMPLETO====\n");
    fprintf(f, "Total de Usuarios: %d\n", totalUsuarios);
    fprintf(f, "Total de Livros: %d\n", totalLivros);
    fprintf(f, "Total de Emprestimos ativos: %d\n", totalEmprestimos);
    fprintf(f, "----------------------------------------\n");
    fprintf(f, "====USUARIOS====\n");


    if (totalUsuarios == 0)
    {
        fprintf(f, "Nenhum usuario ativo.\n");
    }
    else
    {
        for (int i = 0; i < totalUsuarios; i++)
        {
            fprintf(f, "Nome: %s\n", usuarios[i].nome);
            fprintf(f, "CPF: %d\n", usuarios[i].cpf);
            fprintf(f, "Idade: %d\n", usuarios[i].idade);
            fprintf(f, "-----------------------------\n");
        }
    }


    fprintf(f, "====LIVROS====\n");


    if (totalLivros == 0)
    {
        fprintf(f, "Nenhum livro ativo.\n");
    }
    else
    {
        for (int i = 0; i < totalLivros; i++)
        {
            fprintf(f, "ID: %d\n", livros[i].id);
            fprintf(f, "Título: %s\n", livros[i].nome);
            fprintf(f, "Autor: %s\n", livros[i].autor);
            fprintf(f, "Ano: %d\n", livros[i].ano);
            fprintf(f, "-----------------------------\n");
        }
    }


    fprintf(f, "====EMPRESTIMOS====\n");


    if (totalEmprestimos == 0)
    {
        fprintf(f, "Nenhum emprestimo ativo.\n");
    }
    else
    {
        for (int i = 0; i < totalEmprestimos; i++)
        {
            fprintf(f, "Emprestimo ID: %d\n", emprestimos[i].idEmprestimo);
            fprintf(f, "Usuario: %s (CPF: %d)\n", emprestimos[i].usuario.nome, emprestimos[i].usuario.cpf);
            fprintf(f, "Livros Emprestados:\n");
            for (int j = 0; j < 10; j++)
            {
                if (emprestimos[i].livros[j].id != 0)
                {
                    fprintf(f, "  > ID %d: %s (Autor: %s)\n",
                            emprestimos[i].livros[j].id,
                            emprestimos[i].livros[j].nome,
                            emprestimos[i].livros[j].autor);
                }
            }
            fprintf(f, "Total de livros ativos neste emp.: %d\n", ContarLivrosAtivos(emprestimos[i]));
            fprintf(f, "----------------------------------------\n");
        }
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


int carregarUsuarioBinario(Usuario **usuarios, int *totalUsuarios, const char *arqUsuarioBin)
{
    FILE *f = fopen(arqUsuarioBin, "rb");
    if (f == NULL)
    {
        *usuarios = NULL;
        *totalUsuarios = 0;
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long bytes = ftell(f);
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


int carregarLivroBinario(Livro **livros, int *totalLivros, const char *arqLivroBin)
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


//+++++BINARIO EMPRESTIMO++++
int salvarEmprestimoBinario(Emprestimo *emprestimos, int totalEmprestimo, const char *arqEmprestimoBin)
{
    FILE *f = fopen(arqEmprestimoBin, "wb");
    if (f == NULL)
        return 1;


    if (totalEmprestimo > 0)
    {
        size_t escritos = fwrite(
            emprestimos,
            sizeof(Emprestimo),
            (size_t)totalEmprestimo, f);


        if (escritos != (size_t)totalEmprestimo)
        {
            fprintf(stderr, "Erro: fwrite escreveu %zu de %d itens\n", escritos, totalEmprestimo);
            fclose(f);
            return 1;
        }
    }


    fclose(f);
    return 0;
}


int carregarEmprestimoBinario(Emprestimo **emprestimos, int *totalEmprestimo, const char *arqEmprestimoBin)
{
    FILE *f = fopen(arqEmprestimoBin, "rb");
    if (f == NULL)
    {
        *emprestimos = NULL;
        *totalEmprestimo = 0;
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long bytes = ftell(f);
    rewind(f);


    if (bytes <= 0)
    {
        fclose(f);
        *emprestimos = NULL;
        *totalEmprestimo = 0;
        return 1;
    }


    int qtd = (int)(bytes / sizeof(Emprestimo));
    Emprestimo *tmp = (Emprestimo *)malloc(qtd * sizeof(Emprestimo));


    if (tmp == NULL)
    {
        fclose(f);
        return 1;
    }


    size_t lidos = fread(tmp, sizeof(Emprestimo), (size_t)qtd, f);
    fclose(f);


    if (lidos != (size_t)qtd)
    {
        fprintf(stderr, "Erro: fread leu %zu de %d items\n", lidos, qtd);
        free(tmp);
        *emprestimos = NULL;
        *totalEmprestimo = 0;
        return 1;
    }


    *emprestimos = tmp;
    *totalEmprestimo = qtd;
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
    if (totalUsuarios <= 0 || usuarios == NULL)
    {
        printf("Nenhum usuario cadastrado");
        return 1;
    }


    int cpf, i;
    printf("======ATUALIZAR USUARIO======\n");
    printf("Informe o CPF do usuario a ser atualizado: ");
    scanf("%d", &cpf);


    int posicao = -1;
    for (i = 0; i < totalUsuarios; i++)
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
    printf("Usuario atualizado com sucesso!\n");


    salvarUsuarioBinario(usuarios, totalUsuarios, "dadosUsuario.bin");
    return 0;
}


//+++++BUSCAR USUARIO+++++//
int BuscarUsuario(Usuario *usuarios, int totalUsuarios)
{
    if (totalUsuarios <= 0 || usuarios == NULL)
    {
        printf("Nenhum usuario cadastrado");
        return 1;
    }


    int cpf, i;
    printf("======BUSCAR USUARIO======\n");
    printf("Informe o CPF do usuario a ser buscado: ");
    scanf("%d", &cpf);


    for (i = 0; i < totalUsuarios; i++)
    {
        if (usuarios[i].cpf == cpf)
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
    if (totalUsuarios <= 0 || usuarios == NULL)
    {
        printf("Nenhum usuario cadastrado");
    }


    printf("=====LISTA DE USUARIOS=====\n");
    for (int i = 0; i < totalUsuarios; i++)
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


//======CRUD EMPRESTIMO=======


//++++FUNCAO AUXILIAR++++
int ContarLivrosAtivos(Emprestimo cont)
{
    int contador = 0;


    for (int i = 0; i < 10; i++)
    {


        if (cont.livros[i].id != 0)
        {
            contador++;
        }
    }


    return contador;
}


//++++REGISTRAR EMPRESTIMO++++
int RegistrarEmprestimo(Emprestimo **emprestimos, int *totalEmprestimos, Usuario *usuarios, int totalUsuarios, Livro *livros, int totalLivros)
{
    printf("\n=====REGISTRAR EMPRESTIMO=====\n");


    if (totalUsuarios <= 0 || totalLivros <= 0)
    {
        printf("certifique-se de ter usuarios e livros cadastrados!\n");
        return 1;
    }


    int cpfTemp;
    printf("Informe CPF do usuario para o emprestimo: ");
    scanf("%d", &cpfTemp);


    int posicaoUsuario = -1;
    for (int i = 0; i < totalUsuarios; i++)
    {
        if (usuarios[i].cpf == cpfTemp)
        {
            posicaoUsuario = i;
            break;
        }
    }


    if (posicaoUsuario == -1)
    {
        printf("Usuario nao encontrado");
        return 1;
    }


    int qtdLivros;
    do
    {
        printf("Quantos livros deseja? (max.: 10): ");
        scanf("%d", &qtdLivros);
        if (qtdLivros <= 0 || qtdLivros > 10)
            printf("Quantidade invalida! Informe novamente\n");
    } while (qtdLivros <= 0 || qtdLivros > 10);


    Livro livrosSelecionados[10];
    int livrosEncontrados = 0;


    for (int i = 0; i < qtdLivros; i++)
    {
        int posicaoLivro = -1;
        int idTemp;


        printf("Informe o ID do livro %d: ", i + 1);
        scanf("%d", &idTemp);


        for (int j = 0; j < totalLivros; j++)
        {
            if (livros[j].id == idTemp)
            {
                posicaoLivro = j;
                break;
            }
        }


        if (posicaoLivro == -1)
        {
            printf("Livro com ID %d nao encontrado\n", idTemp);
            return 1;
        }


        int ocupado = 0;
        for (int k = 0; k < *totalEmprestimos; k++)
        {
            for (int l = 0; l < 10; l++)
            {
                if ((*emprestimos)[k].livros[l].id == idTemp)
                {
                    ocupado = 1;
                    break;
                }
            }
            if (ocupado)
            {
                break; // sai do loop k
            }
        }


        if (ocupado)
        {
            printf("ERRO: Livro com ID %d ja esta emprestado! Tente outro ID.\n", idTemp);
            return 1;
        }


        livrosSelecionados[livrosEncontrados] = livros[posicaoLivro];
        livrosEncontrados++;
    }


    (*totalEmprestimos)++;
    Emprestimo *tmp = realloc(*emprestimos, *totalEmprestimos * sizeof(Emprestimo));
    if (tmp == NULL)
    {
        printf("Erro!");
        (*totalEmprestimos)--;
        return 1;
    }
    else
    {
        *emprestimos = tmp;
        (*emprestimos)[(*totalEmprestimos) - 1].idEmprestimo = *totalEmprestimos;
        (*emprestimos)[(*totalEmprestimos) - 1].usuario = usuarios[posicaoUsuario];
        for (int i = 0; i < livrosEncontrados; i++)
        {
            (*emprestimos)[*totalEmprestimos - 1].livros[i] = livrosSelecionados[i];
        }


        for (int i = livrosEncontrados; i < 10; i++)
        {
            (*emprestimos)[*totalEmprestimos - 1].livros[i].id = 0;
        }
        printf("Emprestimo registrado com sucesso!\n");
    }


    salvarEmprestimoBinario(*emprestimos, *totalEmprestimos, "dadosEmprestimo.bin");
    return 0;
}


//++++REMOVER EMPRESTIMO++++
int RemoverEmprestimo(Emprestimo **emprestimos, int *totalEmprestimos)
{
    
        if (*totalEmprestimos <= 0 || *emprestimos == NULL)
        {
            printf("Nenhum emprestimo registrado.\n");
            return 1;
        }


        int idEmp, idLivro;
        printf("\n===== DEVOLUCAO DE LIVRO =====\n");
        printf("Informe o id do emprestimo: ");
        scanf("%d", &idEmp);


        int posEmp = -1;
        for (int i = 0; i < *totalEmprestimos; i++)
        {
            if ((*emprestimos)[i].idEmprestimo == idEmp)
            {
                posEmp = i;
                break;
            }
        }


        if (posEmp == -1)
        {
            printf("Emprestimo nao encontrado.\n");
            return 1;
        }


        Emprestimo *empTemp = &(*emprestimos)[posEmp];


        printf("Emprestimo de %s localizado.\n", empTemp->usuario.nome);
        printf("Livros emprestados atualmente: %d\n", ContarLivrosAtivos(*empTemp));


        printf("\nInforme o ID do livro a ser devolvido: ");
        scanf("%d", &idLivro);


        int posLivro = -1;
        for (int j = 0; j < 10; j++)
        {
            if (empTemp->livros[j].id == idLivro)
            {
                posLivro = j;
                break;
            }
        }


        if (posLivro == -1)
        {
            printf("Erro: Livro nao encontrado neste emprestimo.\n");
            return 1;
        }


        for (int j = posLivro; j < 9; j++)
        {
            empTemp->livros[j] = empTemp->livros[j + 1];
        }
        empTemp->livros[9].id = 0;


        printf("Livro devolvido com sucesso.\n");


        if (ContarLivrosAtivos(*empTemp) == 0)
        {


            printf("Todas as devolucoes foram concluidas! Emprestimo encerrado.\n");


            for (int i = posEmp; i < *totalEmprestimos - 1; i++)
            {
                (*emprestimos)[i] = (*emprestimos)[i + 1];
            }


            (*totalEmprestimos)--;


            if (*totalEmprestimos == 0)
            {
                free(*emprestimos);
                *emprestimos = NULL;
            }
            else
            {
                Emprestimo *tmp = realloc(*emprestimos, *totalEmprestimos * sizeof(Emprestimo));
                if (tmp != NULL)
                {
                    *emprestimos = tmp;
                }
            }
        }
        else
        {
            printf("O emprestimo continua ativo com %d livro(s).\n", ContarLivrosAtivos(*empTemp));
        }


    salvarEmprestimoBinario(*emprestimos, *totalEmprestimos, "dadosEmprestimo.bin");
    return 0;
}


//+++++BUSCAR EMPRESTIMO+++++//
int BuscarEmprestimo(Emprestimo *emprestimos, int totalEmprestimos)
{
    if (totalEmprestimos <= 0 || emprestimos == NULL)
    {
        printf("Nenhum emprestimo registrado");
        return 1;
    }


    int id, i, j;
    printf("======BUSCAR EMPRESTIMO======\n");
    printf("Informe o ID do emprestimo a ser buscado: ");
    scanf("%d", &id);


    for (i = 0; i < totalEmprestimos; i++)
    {
        if (emprestimos[i].idEmprestimo == id)
        {
            printf("------------------------------------------\n");
            printf("Emprestimo ID: %d\n", emprestimos[i].idEmprestimo);


            printf("---Usuário---");
            printf("Nome: %s", emprestimos[i].usuario.nome);
            printf("CPF: %d\n", emprestimos[i].usuario.cpf);


            printf("---Livros---");
            int livrosEncontrados = 0;
            for (j = 0; j < 10; j++)
            {
                if (emprestimos[i].livros[j].id != 0)
                {
                    printf("Livro %d:\n", livrosEncontrados + 1);
                    printf("ID: %d\n", emprestimos[i].livros[j].id);
                    printf("Titulo: %s\n", emprestimos[i].livros[j].nome);
                    printf("Autor: %s\n", emprestimos[i].livros[j].autor);
                    livrosEncontrados++;
                }
            }


            if (livrosEncontrados == 0)
            {
                printf("Nenhum livro ativo (todos devolvidos)");
            }


            printf("------------------------------------------\n");
            return 0;
        }
    }


    printf("Emprestimo nao encontrado!");
    return 1;
}


//+++++LISTAR EMPRESTIMO++++++//
void ListarEmprestimo(Emprestimo *emprestimos, int totalEmprestimos)
{
    if (totalEmprestimos <= 0 || emprestimos == NULL)
    {
        printf("Nenhum emprestimo registrado\n");
    }


    printf("=====LISTA DE EMPRESTIMOS=====\n");
    for (int i = 0; i < totalEmprestimos; i++)
    {
        printf("------------------------------------------\n");
        printf("EMPRESTIMO %d (ID: %d)\n", i + 1, emprestimos[i].idEmprestimo);


        printf("Usuario:\n");
        printf("Nome: %s\n", emprestimos[i].usuario.nome);
        printf("CPF: %d\n", emprestimos[i].usuario.cpf);


        printf("Livros:\n");
        int livrosEncontrados = 0;


        for (int j = 0; j < 10; j++)
        {
            if (emprestimos[i].livros[j].id != 0)
            {
                printf("Titulo: %s\n", emprestimos[i].livros[j].nome);
                printf("(ID: %d, Autor: %s)\n", emprestimos[i].livros[j].id, emprestimos[i].livros[j].autor);
                livrosEncontrados++;
            }
        }


        if (livrosEncontrados == 0)
        {
            printf("Nenhum livro ativo.\n");
        }
        else
        {
            printf("Total de livros ativos neste emprestimo: %d\n", livrosEncontrados);
        }
    }
}



