#include <iostream>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

void opcoes(){
    cout << "===============================" << endl;
    cout << "Este é o menu da biblioteca." << endl;
    cout << " 1 . Cadastro." << endl;
    cout << " 2 . Alteração." << endl;
    cout << " 3 . Exclusão." << endl;
    cout << " 4 . Emprestimo." << endl;
    cout << " 5 . Devolução." << endl;
    cout << " 6 . Consulta de livro." << endl;
    cout << " 7 . Livros disponiveis." << endl;
    cout << " 8 . Listagem geral de livros." << endl;
    cout << " 9 . Sair." << endl;
    cout << "===============================" << endl;
}

int main(){

    struct infoUsuario {
         char nome[50];
         char dataEmpr[50];
         char dataDevo[50];
    };

    struct livros{
        int codigo, nPag;
        char area[30], titulo[100], autor[12], editora[15];
        bool disponivel = true;
        int qtdLivros = 0;
        struct infoUsuario usuario;
    };

    struct livros liv;
    int opcao, i, codigoE, campo;
    string nomeUsu, saber;
    char opc;

    opcoes();
    FILE *livroscadastrados;
    FILE *livroscadastradosAux;
    

    cout << "Digite qual opção você deseja!" << endl;
    cin >> opcao;
    

    while(opcao != 9){
        system("cls");
        
        switch(opcao){

            case 1:
                livroscadastrados = fopen("livros_cadastrados.dat", "ab+");
                if(livroscadastrados == NULL){
                    cout << "Arquivo Não foi aberto";
                }else{
                    cout << "Deseja cadastrar outro livro? use 'S' para sim e 'N' para não!" << endl;
                    cin >> opc;
                    
                    while(opc == 'S'){                        
                        cout << "Faça o cadastro do livro." << endl;
                        cout << "Qual codigo de catalogo do livro?" << endl;
                        cin >> liv.codigo;
                        cin.ignore();

                        cout << "Qual a area desse livro? (Ciencias exatas, Ciencias humanas e Ciencias da saude)" << endl;
                        cin.get(liv.area, 29);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                        cout << "Qual o titulo deste livro?" << endl;
                        cin.get(liv.titulo,99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Quem é o autor deste livro?" << endl;
                        cin.get(liv.autor,11);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Qual a editora deste livro?" << endl;
                        cin.get(liv.editora,14);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Quantas paginas esse livro possui?" << endl;
                        cin >> liv.nPag;

                        liv.qtdLivros++;
                        system("cls");
                        if(fwrite(&liv, sizeof(struct livros), 1, livroscadastrados) == 1){
                            cout << "Registro gravado com sucesso!" << endl;
                            cin.get();
                        }else{
                            cout << "Erro ao gravar registro";
                            cin.get();
                        }
                        cout << "Deseja cadastrar um Livro? use 'S' para sim e 'N para não!" << endl;
                        cin >> opc;
                        
                    }
                    fclose(livroscadastrados);
                }
                break;
            case 2:
                cout << "Digite o codigo do livro que você deseja alterar." << endl;
                cin >> codigoE;
                livroscadastrados = fopen("livros_cadastrados.dat", "rb+");
                while(!feof(livroscadastrados)){
                    fread(&liv, sizeof(struct livros), 1 ,livroscadastrados);
                    if(codigoE == liv.codigo){
                        fseek(livroscadastrados, -sizeof(struct livros), SEEK_CUR);
                        cout << "Digite qual campo você deseja alterar" << endl;
                        cout << "1 - area, 2 - titulo, 3 - autor, 4 - editora, 5 - numeroPaginas" << endl;
                        cin >> campo;
                        switch (campo) {
                            case 1:
                                cout << "novo valor de area: ";
                                cin >> liv.area;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                fwrite(&liv, sizeof(struct livros), 1, livroscadastrados);
                                cout << "Nova area alterada com sucesso" << endl;
                                cin.get();
                                fclose(livroscadastrados);
                                break;
                            case 2:
                                cout << "Novo valor de titulo: ";
                                cin >> liv.titulo;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                fwrite(&liv, sizeof(struct livros), 1, livroscadastrados);
                                cout << "Nova area alterada com sucesso" << endl;
                                cin.get();
                                fclose(livroscadastrados);
                                break;
                            case 3:
                                cout << "Novo valor de autor: ";
                                cin >> liv.autor;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                fwrite(&liv, sizeof(struct livros), 1, livroscadastrados);
                                cout << "Nova area alterada com sucesso" << endl;
                                cin.get();
                                fclose(livroscadastrados);
                                break;
                            case 4:
                                cout << "Novo valor de editora: ";
                                cin >> liv.editora;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                fwrite(&liv, sizeof(struct livros), 1, livroscadastrados);
                                cout << "Nova area alterada com sucesso" << endl;
                                cin.get();
                                fclose(livroscadastrados);
                                break;
                            case 5:
                                cout << "Novo valor de Paginas: ";
                                cin >> liv.nPag;
                                fwrite(&liv, sizeof(struct livros), 1, livroscadastrados);
                                cout << "Nova area alterada com sucesso" << endl;
                                cin.get();
                                fclose(livroscadastrados);
                                break;
                            default:
                                cout << "Valor incorreto";
                                fclose(livroscadastrados);
                                break;
                                
                        }break;
                    }
                }
                break;
            case 3:
                cout << "Deseja excluir todo o arquivo? S para sim e N para nao" << endl;
                cin >> opc;
                if(opc == 'S'){
                    livroscadastrados = fopen("livros_cadastrados.dat", "wb");
                    fclose(livroscadastrados);
                    cout << "Registros excluidos" << endl;
                    cin.get();
                }else if(opc == 'N'){
                    cout << "Deseja excluir um registro especifico? S para sim e N para não" << endl;
                    cin >> opc;
                    if(opc == 'S'){
                        cout << "Digite o codigo do livro para exclusão" << endl;
                        cin >> codigoE;
                        livroscadastradosAux = fopen("livros_cadastrados.aux", "wb");
                        livroscadastrados = fopen("livros_cadastrados.dat", "rb+");
                        fread(&liv, sizeof(struct livros), 1 ,livroscadastrados);
                        while(!feof(livroscadastrados)){
                            if(codigoE != liv.codigo){
                                fwrite(&liv, sizeof(struct livros), 1 , livroscadastradosAux);
                            }
                            fread(&liv, sizeof(struct livros), 1 ,livroscadastrados);
                        }
                        fclose(livroscadastrados);
                        fclose(livroscadastradosAux);
                        remove("livros_cadastrados.dat");
                        rename("livros_cadastrados.aux", "livros_cadastrados.dat");
                        cout << "Registro excluido com sucesso" << endl;
                        cin.get();
                    }break;
                }
                break;
            case 4:
                cout << "Deseja pegar emprestado algum livro? use 'S' para sim e 'N' para não!" << endl;
                cin >> opc;
                while(opc == 'S'){
                    
                    cout << "Digite o codigo do livro que você deseja pegar emprestado" << endl;
                    cin >> codigoE;
                    livroscadastrados = fopen("livros_cadastrados.dat", "rb+");
                    while(fread(&liv, sizeof(struct livros), 1, livroscadastrados) == 1){
                        if(codigoE == liv.codigo){
                            fseek(livroscadastrados, -sizeof(struct livros), SEEK_CUR); 
                            cout << "Digite o nome do usuario que esta pegando o livro" << endl;
                            cin >> liv.usuario.nome;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Digite a data que o livro foi entregue" << endl;
                            cin >> liv.usuario.dataEmpr;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            liv.disponivel = false;
                            if(fwrite(&liv, sizeof(struct livros), 1, livroscadastrados) == 1){
                                cout << "livro anexado ao usuario com sucesso" << endl;
                                cin.get();
                                break;
                            }else{
                                cout << "Erro ao anexar arquivo" << endl;
                            }
                            
                        }
                    }fclose(livroscadastrados);
                    cout << "Deseja pegar emprestado outro livro? use 'S' para sim e 'N' para não!" << endl;
                    cin >> opc;
                }
                break;
            case 5:
                cout << "Deseja devolver algum livro? use 'S' para sim e 'N' para não!" << endl;
                cin >> opc;
                while(opc == 'S'){
                    cout << "Digite o codigo do livro que você deseja devolver" << endl;
                    cin >> codigoE;
                    livroscadastrados = fopen("livros_cadastrados.dat", "rb+");
                    bool livroEncontrado = false;
                    while(fread(&liv, sizeof(struct livros), 1, livroscadastrados) == 1){
                        if(codigoE == liv.codigo){
                            cout << liv.usuario.nome << " responsavel pela devolução" << endl;
                            cin.get();
                            
                            cout << "digite a data que o livro foi devolvido" << endl;
                            cin >> liv.usuario.dataDevo;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            strcpy(liv.usuario.dataEmpr, " ");
                            strcpy(liv.usuario.nome, " ");
                            liv.disponivel = true;

                            fseek(livroscadastrados, -sizeof(struct livros), SEEK_CUR);
                            fwrite(&liv, sizeof(struct livros), 1 ,livroscadastrados);

                            cout << "livro devolvido com sucesso!" << endl;
                            livroEncontrado = true;
                            break;
                        }
                    }fclose(livroscadastrados);

                    if(!livroEncontrado){
                        cout << "livro não encontrado" << endl;
                    }
                    cout << "Deseja devolver outro livro? use 'S' para sim e 'N' para não!" << endl;
                    cin >> opc;
                }
                break;  
            case 6:

                cout << "Deseja consultar algum livro? use 'S' para sim e 'N' para não!" << endl;
                cin >> opc;
                while((opc == 'S') && (opc != 'N')){
                    cout << endl << "Consulta de livro " << endl << endl;
                    cout << "Digite o codigo de catalago do livro que você deseja consultar" << endl;
                    cin >> codigoE;

                    livroscadastrados = fopen("livros_cadastrados.dat", "rb");
                    
                    while(!feof(livroscadastrados)){
                        fread(&liv, sizeof(struct livros), 1, livroscadastrados);
                        if(codigoE == liv.codigo){
                            saber = (liv.disponivel) ? " esta disponivel" : "não esta disponivel";
                            cout << "Os dados do livro consultado são:" << endl;
                            cout << "Codigo de catalacao: " << liv.codigo << " Area: " << liv.area << endl;
                            cout << "Titulo: " << liv.titulo << endl;
                            cout << "Autor: " << liv.autor << endl;
                            cout << "Editora: " << liv.editora << " n De pag: " << liv.nPag << endl;
                            cout << "Este livro " << saber << endl;
                            cout << "----------------------------------" << endl;
                            cin.get();
                            fclose(livroscadastrados);
                            break;
                        }
                    }
                    cout << endl << endl << "Deseja consultar outro livro? use 'S' para sim e 'N' para não!" << endl;
                    cin >> opc;
                }
                break;
            case 7:
                cout << "Esta é a lista de todos livros disponiveis." << endl;
                livroscadastrados = fopen("livros_cadastrados.dat", "rb");
                while(fread(&liv, sizeof(struct livros), 1 ,livroscadastrados) == 1){
                    if(liv.disponivel == true){
                        cout << "Codigo de catalacao: " << liv.codigo << " Area: " << liv.area << endl;
                        cout << "Titulo: " << liv.titulo << endl;
                        cout << "Autor: " << liv.autor << endl;
                        cout << "Editora: " << liv.editora << " n De pag: " << liv.nPag << endl;
                        cout << "Este livro esta disponivel " << endl;
                        cout << "----------------------------------" << endl;
                    }
                }
                cin.get();
                fclose(livroscadastrados);
                break;  
            case 8:
                cout <<endl << endl << "Listagem de livros" << endl << endl;
                livroscadastrados = fopen("livros_cadastrados.dat", "rb");
                while(fread(&liv, sizeof(struct livros), 1, livroscadastrados) == 1){
                    saber = (liv.disponivel) ? " esta disponivel" : "não esta disponivel";
                    cout << "Codigo de catalacao: " << liv.codigo << " Area: " << liv.area << endl;
                    cout << "Titulo: " << liv.titulo << endl;
                    cout << "Autor: " << liv.autor << endl;
                    cout << "Editora: " << liv.editora << " n De pag: " << liv.nPag << endl;
                    cout << "Este livro " << saber << endl;
                    cout << "----------------------------------" << endl;

                   // fread(&liv, sizeof(struct livros), 1, livroscadastrados);
                   // fread lê bloco por bloco, então sempre que o arquivo retornar 1 , ele leu mais um bloco, dessa forma n é necessario o feof;
                }
                cin.get();
                
                fclose(livroscadastrados);
                cin.get();
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
    }
       opcoes();

       cout << "Digite a opção desejada." << endl;
       cin >> opcao;
    }

}