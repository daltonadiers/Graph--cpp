#include <iostream>
#include "graph.cpp"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
struct usuario{
    string email;
    string nome;
    string cidade;
    string telefone;
    string datadenascimento;
};

int main(){
    graph::digraph g;
    ifstream arquivo("Usuarios.txt");
    string linha;

    if (arquivo.is_open()) {
        while(getline(arquivo, linha)){
            istringstream iss(linha);
            string nome, email, telefone, cidade, datadenascimento;
            getline(iss, email, ',');
            getline(iss, nome, ',');
            getline(iss, datadenascimento, ',');
            getline(iss, telefone, ',');
            getline(iss, cidade);
            g.insert_node(email, nome, datadenascimento, telefone, cidade);
        }
        arquivo.close();
    }
    ifstream arquivo2("Links.txt");
    string linha2;
    if (arquivo2.is_open()) {
        while(getline(arquivo2, linha2)){
            istringstream iss2(linha2);
            string email1, email2;
            getline(iss2, email1, ',');
            getline(iss2, email2);
                if(g.insert_link(email1, email2)){
                    cout << "link inserido" << endl;
                    continue;
                }
        }
        arquivo2.close();
    }


    while(true){
        cout << "Ola, seja bem vindo ao modo administrador FriendZone, sua rede social de amizades!" << endl;
        cout << "\tPara iniciar, o que deseja fazer?" << endl;
        cout << endl;
        cout << "1 PARA CADASTRAR NOVO USUÁRIO" << endl;
        cout << "2 PARA SEGUIR ALGUEM" << endl;
        cout << "3 PARA DEIXAR DE SEGUIR ALGUEM" << endl;
        cout << "4 PARA LISTAR USUARIOS" << endl;
        cout << "5 PARA CONSULTAR DADOS DE UM USUARIO" << endl;
        cout << "6 PARA EXCLUIR USUARIO" << endl;
        cout << "7 PARA VERIFICAR CAMINHO ENTRE USUARIOS" << endl;
        cout << "8 PARA EXPORTAR REDE PARA ARQUIVO DOT" << endl;
        cout << "9 PARA INFORMAÇÕES SOBRE A REDE" << endl;
        cout << "0 PARA SAIR" << endl;
        int p;
        cin >> p;
        usuario u;
        switch(p){
            case 1:
                cout << "Informe o e-mail do usuario que deseja cadastrar: ";
                cin >> u.email;
                cin.ignore();
                if(g.existe(u.email)){
                    cout << "E-mail ja cadastrado!" << endl;
                    break;
                }
                cout << "Informe o nome: ";
                getline(cin, u.nome);
                cout << "Informe a data de nascimento, no formato dd/mm/yyyy: ";
                getline(cin, u.datadenascimento);
                cout << "Informe o numero de telefone: ";
                getline(cin, u.telefone);
                cout << "Informe a cidade onde reside: ";
                getline(cin, u.cidade);
                if(g.insert_node(u.email, u.nome, u.datadenascimento, u.telefone, u.cidade)){
                    cout << "Usuario inserido!" << endl;
                }
            break;
            case 2:
            {
                string email1, email2;
                cout << "Informe o primeiro e-mail: ";
                cin >> email1;
                if(!g.existe(email1)){
                    cout << "E-mail nao cadastrado!" << endl;
                    break;
                }
                cout << "Informe o segundo e-mail: ";
                cin >> email2;
                if(!g.existe(email2)){
                    cout << "E-mail nao cadastrado!" << endl;
                    break;
                }
                if(g.insert_link(email1, email2)){
                    cout << "Link adicionado!" << endl;
                }

            }
            break;
            case 3:
                {
                string email1, email2;
                cout << "Informe o primeiro e-mail: ";
                cin >> email1;
                if(!g.existe(email1)){
                    cout << "E-mail nao cadastrado!" << endl;
                    break;
                }
                cout << "Informe o segundo e-mail: ";
                cin >> email2;
                if(!g.existe(email2)){
                    cout << "E-mail nao cadastrado!" << endl;
                    break;
                }
                if(g.remove_link(email1, email2)){
                    cout << "Link excluido!" << endl;
                }
            }
            break;
            case 4:
                g.show();
            break;
            case 5:
                {
                    string email;
                    cout << "Digite o e-mail do usuário que deseja visitar: ";
                    cin >> email;
                    g.showuser(email);
                }
            break;
            case 6:
                {
                    string email;
                    char a;
                    cout << "Digite o e-mail do usuário que deseja excluir: ";
                    cin >> email;
                    g.showuser(email);
                    cout << "Tem certeza que deseja excluir esse usuário? Y/N ";
                    cin >> a;
                    if(a=='Y' || a=='y'){
                        g.remove(email);
                    }
                    else{
                        cout << "Operacao cancelada!" << endl;
                    }
                }
            break;
            case 7:
            {
                string email, email2;
                cout << "Digite o email do primeiro usuário: ";
                cin >> email;
                if(!g.existe(email)){
                    cout << "Email não cadastrado!" << endl;
                }else{
                    cout << "Digite o email do segundo usuário: ";
                    cin >> email2;
                    if(!g.existe(email2)){
                        cout << "Email não cadastrado!" << endl;
                    }else{
                        auto path = g.bfs(email, email2);
                        cout << "Tamanho do caminho: " << path.size() << endl;
                        cout << "Voce deseja imprimir esse caminho? Y OR N ";
                        char v;
                        cin >> v;
                        if(v=='Y' || v=='y'){
                            for(auto n: path){
                                cout << "->" << n->email;
                            }
                            cout << endl;
                        }
                    }
                }
            }
            break;
            case 8:
                g.showdot();
            break;
            case 9:
                cout << "Quantidade de usuarios cadastrados: " << g.nusers() << endl;
                cout << "Grau medio de entrada: " << g.graumedioentrada() << endl;
                cout << "Grau medio de saida: " << g.graumediosaida() << endl;
                cout << "Diâmetro do grafo: " << g.diameter() << endl;
                cout << "Usuario com maior numero de seguidores: " << g.morefollowers()->nome << " (" << g.morefollowers()->email << ")" << endl;
                cout << "Numero de seguidores: " << g.morefollowers()->seguidores.size() << endl;
            break;
            case 0:
                cout << "Salvando..." << endl;
                g.saveuser();
                g.savelinks();
                return 0;
            break;
            default:
            cout << "Opcao invalida, tente novamente" << endl;
            break;
        }
        cout << "Pressione Enter para continuar...";
        cin.ignore();
        cin.get();
    }
}
