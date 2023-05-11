#include <iostream>
#include "graph.cpp"
#include <string>

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
        cout << "8 PARA EXPORTAR REDE" << endl;
        cout << "9 PARA INFORMAÇÕES SOBRE A REDE" << endl;
        int p;
        cin >> p;
        usuario u;
        switch(p){
            case 1:
                cout << "Informe o e-mail do usuario que deseja cadastrar: ";
                cin >> u.email;
                if(g.existe(u.email)){
                    cout << "E-mail ja ccleaadastrado!" << endl;
                    break;
                }
                cout << "Informe o nome: ";
                cin >> u.nome;
                cout << "Informe a data de nascimento, no formato dd/mm/yyyy: ";
                cin >> u.datadenascimento;
                cout << "Informe o numero de telefone: ";
                cin >> u.telefone;
                cout << "Informe a cidade onde reside: ";
                cin >> u.cidade;
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
                    cout << "Tem certeza que deseja excluir esse usuário? Y/N";
                    cin >> a;
                    if(a=='Y'){
                        g.remove(email);
                    }
                }
            break;
            case 7:

            break;
            case 8:

            break;
            case 9:

            break;
            default:
            cout << "Opcao invalida, tente novamente" << endl;
            break;
        }
    }
}
