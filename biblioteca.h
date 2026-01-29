#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

    typedef struct Usuario {
        int cpf;
        char nome[50];
        int idade;
    } Usuario;

    typedef struct Livro {
        int id;
        char nome[50];
        char autor[100];
        int ano;
    } Livro;

    typedef struct Emprestimo {
        int idEmprestimo;
        Usuario usuario;
        Livro livros[10]; 
    } Emprestimo;


    //====MENUS=====
    void menuUsuarios(Usuario **usuarios, int *totalUsuarios);
    void menuLivros(Livro **livros, int *totalLivros);

    //====RELATORIO====
    int gerarRelatorio(Livro *livros, int totalLivros, Usuario *usuarios, int totalUsuarios, const char *relatorioTxt);

    //====ARQUIVOS====
    int salvarUsuarioBinario(Usuario *usuarios, int totalUsuarios, const char *arqUsuarioBin);
    int carregarDadosUsuarioBinario(Usuario **usuarios, int *totalUsuarios, const char *arqUsuarioBin);
    int salvarLivroBinario(Livro *livros, int totalLivros, const char *arqLivroBin);
    int carregarDadosLivroBinario(Livro **livros, int *totalLivros, const char *arqLivroBin);

    //====CRUD====
    int RegistrarUsuario(Usuario **usuarios, int *totalUsuarios); 
    int RemoverUsuario(Usuario **usuarios, int *totalUsuarios); 
    int AtualizarUsuario(Usuario *usuarios, int totalUsuarios);
    void ListarUsuario(Usuario *usuarios, int totalUsuarios);
    int BuscarUsuario(Usuario *usuarios, int totalUsuarios);

    int RegistrarLivro(Livro **livros, int *totalLivros);
    int RemoverLivro(Livro **livros, int *totalLivros);
    int AtualizarLivro(Livro *livros, int totalLivros);
    void ListarLivro(Livro *livros, int totalLivros);
    int BuscarLivro(Livro *livros, int totalLivros);

    // int RegistrarEmprestimo(const char *arquivoEmprestimo, Emprestimo *emprestimo);
    // int RemoverEmprestimo(const char *arquivoEmprestimo, int id);
    // int AtualizaEmprestimo(const char *arquivoEmprestimo, int id, Emprestimo *novoEmprestimo);
    // void ListarEmprestimo(const char *arquivoEmprestimo);
    // int BuscarEmprestimo(const char *arquivoEmprestimo, int id);


#endif