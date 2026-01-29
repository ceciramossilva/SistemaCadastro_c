#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

int main()
{

    Usuario *usuarios = NULL;
    int totalUsuarios = 0;
    Livro *livros = NULL;
    int totalLivros = 0;
    int op;
    carregarDadosUsuarioBinario(&usuarios, &totalUsuarios, "dadosUsuario.bin");
    carregarDadosLivroBinario(&livros, &totalLivros, "dadosLivro.bin");

    //====MENU====

    do
    {
        printf("\n===== SISTEMA DE CADASTRO =====\n");
        printf("1 - Gerenciar Usuarios\n");
        printf("2 - Gerenciar Livros\n");
        printf("3 - Gerenciar Emprestimo\n");
        printf("4 - Gerar Relatorio (texto)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            menuUsuarios(&usuarios, &totalUsuarios);
            break;
        case 2:
            menuLivros(&livros, &totalLivros);
            break;
        case 3:
            // menuEmprestimos();
            break;
        case 4:
            gerarRelatorio(livros, totalLivros, usuarios, totalUsuarios, "relatorio.txt");
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (op != 0);

    salvarUsuarioBinario(usuarios, totalUsuarios, "dadosUsuario.bin");
    salvarLivroBinario(livros, totalLivros, "dadosLivro.bin");
    free(usuarios);
    free(livros);
    return 0;
}
