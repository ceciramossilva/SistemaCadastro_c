#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H


typedef struct Usuario
{
    int cpf;
    char nome[50];
    int idade;
} Usuario;


typedef struct Livro
{
    int id;
    char nome[50];
    char autor[100];
    int ano;
} Livro;


typedef struct Emprestimo
{
    int idEmprestimo;
    Usuario usuario;
    Livro livros[10];
} Emprestimo;


//====MENUS=====
void menuUsuarios(Usuario **usuarios, int *totalUsuarios);
void menuLivros(Livro **livros, int *totalLivros);
void menuEmprestimos(Emprestimo **emprestimos, int *totalEmprestimos, Usuario *usuarios, int totalUsuarios, Livro *livros, int totalLivros);


//====RELATORIO====
int gerarRelatorio(Livro *livros, int totalLivros, Usuario *usuarios, int totalUsuarios, Emprestimo *emprestimos, int totalEmprestimos, const char *relatorioTxt);


//====ARQUIVOS====
int salvarUsuarioBinario(Usuario *usuarios, int totalUsuarios, const char *arqUsuarioBin);
int carregarUsuarioBinario(Usuario **usuarios, int *totalUsuarios, const char *arqUsuarioBin);
int salvarLivroBinario(Livro *livros, int totalLivros, const char *arqLivroBin);
int carregarLivroBinario(Livro **livros, int *totalLivros, const char *arqLivroBin);
int salvarEmprestimoBinario(Emprestimo *emprestimos, int totalEmprestimo, const char *arqEmprestimoBin);
int carregarEmprestimoBinario(Emprestimo **emprestimos, int *totalEmprestimo, const char *arqEmprestimoBin);


//====AUXILIAR====
int ContarLivrosAtivos(Emprestimo cont);


//====ORDENAÇÃO====
void ordenarUsuariosPorNome(Usuario *usuarios, int totalUsuarios);
void ordenarLivrosPorNome(Livro *livros, int totalLivros);


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


int RegistrarEmprestimo(Emprestimo **emprestimos, int *totalEmprestimos, Usuario *usuarios, int totalUsuarios, Livro *livros, int totalLivros);
int RemoverEmprestimo(Emprestimo **emprestimos, int *totalEmprestimo);
void ListarEmprestimo(Emprestimo *emprestimos, int totalEmprestimos);
int BuscarEmprestimo(Emprestimo *emprestimos, int totalEmprestimos);


#endif

