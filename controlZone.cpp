#include <iostream>
#include "graph.cpp"
#include <string>
#include <fstream>
#include <sstream>

struct usuario{
    std::string email;
    std::string nome;
    std::string cidade;
    std::string telefone;
    std::string datadenascimento;
};

namespace controlZone{
    class cZone{
        public:
        void inicia(){
            graph::digraph g;
            std::ifstream arquivo("Usuarios.txt");
            std::string linha;

            if (arquivo.is_open()) {
                while(getline(arquivo, linha)){
                    std::istringstream iss(linha);
                    std::string nome, email, telefone, cidade, datadenascimento;
                    getline(iss, email, ',');
                    getline(iss, nome, ',');
                    getline(iss, datadenascimento, ',');
                    getline(iss, telefone, ',');
                    getline(iss, cidade);
                    g.insert_node(email, nome, datadenascimento, telefone, cidade);
                }
                arquivo.close();
            }
            std::ifstream arquivo2("Links.txt");
            std::string linha2;
            if (arquivo2.is_open()) {
                while(getline(arquivo2, linha2)){
                    std::istringstream iss2(linha2);
                    std::string email1, email2;
                    getline(iss2, email1, ',');
                    getline(iss2, email2);
                        if(g.insert_link(email1, email2)){
                            std::cout << "link inserido" << std::endl;
                            continue;
                        }
                }
                arquivo2.close();
            }


            while(true){
                std::cout << "Ola, seja bem vindo ao modo administrador FriendZone, sua rede social de amizades!" << std::endl;
                std::cout << "\tPara iniciar, o que deseja fazer?" << std::endl;
                std::cout << std::endl;
                std::cout << "1 PARA CADASTRAR NOVO USUÁRIO" << std::endl;
                std::cout << "2 PARA SEGUIR ALGUEM" << std::endl;
                std::cout << "3 PARA DEIXAR DE SEGUIR ALGUEM" << std::endl;
                std::cout << "4 PARA LISTAR USUARIOS" << std::endl;
                std::cout << "5 PARA CONSULTAR DADOS DE UM USUARIO" << std::endl;
                std::cout << "6 PARA EXCLUIR USUARIO" << std::endl;
                std::cout << "7 PARA VERIFICAR CAMINHO ENTRE USUARIOS" << std::endl;
                std::cout << "8 PARA EXPORTAR REDE PARA ARQUIVO DOT" << std::endl;
                std::cout << "9 PARA INFORMAÇÕES SOBRE A REDE" << std::endl;
                std::cout << "0 PARA SAIR" << std::endl;
                int p;
                std::cin >> p;
                usuario u;
                switch(p){
                    case 1:
                        std::cout << "Informe o e-mail do usuario que deseja cadastrar: ";
                        std::cin >> u.email;
                        std::cin.ignore();
                        if(g.existe(u.email)){
                            std::cout << "E-mail ja cadastrado!" << std::endl;
                            break;
                        }
                        std::cout << "Informe o nome: ";
                        getline(std::cin, u.nome);
                        std::cout << "Informe a data de nascimento, no formato dd/mm/yyyy: ";
                        getline(std::cin, u.datadenascimento);
                        std::cout << "Informe o numero de telefone: ";
                        getline(std::cin, u.telefone);
                        std::cout << "Informe a cidade onde reside: ";
                        getline(std::cin, u.cidade);
                        if(g.insert_node(u.email, u.nome, u.datadenascimento, u.telefone, u.cidade)){
                            std::cout << "Usuario inserido!" << std::endl;
                        }
                        g.saveuser();
                    break;
                    case 2:
                    {
                        std::string email1, email2;
                        std::cout << "Informe o primeiro e-mail: ";
                        std::cin >> email1;
                        if(!g.existe(email1)){
                            std::cout << "E-mail nao cadastrado!" << std::endl;
                            break;
                        }
                        std::cout << "Informe o segundo e-mail: ";
                        std::cin >> email2;
                        if(!g.existe(email2)){
                            std::cout << "E-mail nao cadastrado!" << std::endl;
                            break;
                        }
                        if(g.insert_link(email1, email2)){
                            std::cout << "Link adicionado!" << std::endl;
                        }
                        g.savelinks();
                    }
                    break;
                    case 3:
                        {
                        std::string email1, email2;
                        std::cout << "Informe o primeiro e-mail: ";
                        std::cin >> email1;
                        if(!g.existe(email1)){
                            std::cout << "E-mail nao cadastrado!" << std::endl;
                            break;
                        }
                        std::cout << "Informe o segundo e-mail: ";
                        std::cin >> email2;
                        if(!g.existe(email2)){
                            std::cout << "E-mail nao cadastrado!" << std::endl;
                            break;
                        }
                        if(g.remove_link(email1, email2)){
                            std::cout << "Link excluido!" << std::endl;
                        }
                        g.savelinks();
                    }
                    break;
                    case 4:
                        g.show();
                    break;
                    case 5:
                        {
                            std::string email;
                            std::cout << "Digite o e-mail do usuário que deseja visitar: ";
                            std::cin >> email;
                            g.showuser(email);
                        }
                    break;
                    case 6:
                        {
                            std::string email;
                            char a;
                            std::cout << "Digite o e-mail do usuário que deseja excluir: ";
                            std::cin >> email;
                            if(g.existe(email)){
                                g.showuser(email);
                                std::cout << "Tem certeza que deseja excluir esse usuário? Y/N ";
                                std::cin >> a;
                                if(a=='Y' || a=='y'){
                                    g.remove(email);
                                }
                                else{
                                    std::cout << "Operacao cancelada!" << std::endl;
                                }
                            }else{
                                std::cout << "Usuario inexistente!" << std::endl;
                            }
                            g.saveuser();
                            g.savelinks();
                        }
                    break;
                    case 7:
                    {
                        std::string email, email2;
                        std::cout << "Digite o email do primeiro usuário: ";
                        std::cin >> email;
                        if(!g.existe(email)){
                            std::cout << "Email não cadastrado!" << std::endl;
                        }else{
                            std::cout << "Digite o email do segundo usuário: ";
                            std::cin >> email2;
                            if(!g.existe(email2)){
                                std::cout << "Email não cadastrado!" << std::endl;
                            }else{
                                auto path = g.bfs(email, email2);
                                std::cout << "Tamanho do caminho: " << path.size()-1 << std::endl;
                                std::cout << "Voce deseja imprimir esse caminho? Y OR N ";
                                char v;
                                std::cin >> v;
                                if(v=='Y' || v=='y'){
                                    for(auto n: path){
                                        std::cout << "->" << n->email;
                                    }
                                    std::cout << std::endl;
                                }
                            }
                        }
                    }
                    break;
                    case 8:
                        g.showdot();
                    break;
                    case 9:
                    {
                        std::cout << "Quantidade de usuarios cadastrados: " << g.nusers() << std::endl;
                        std::cout << "Grau medio de entrada: " << g.graumedioentrada() << std::endl;
                        std::cout << "Grau medio de saida: " << g.graumediosaida() << std::endl;
                        auto aux = g.diameter();
                        std::cout << "Diâmetro do grafo: " << aux.size()-1 << std::endl;
                        std::cout << "Usuario com maior numero de seguidores: " << g.morefollowers()->nome << " (" << g.morefollowers()->email << ")" << std::endl;
                        std::cout << "Numero de seguidores: " << g.morefollowers()->seguidores.size() << std::endl;
                        std::cout << "Deseja visualizar o diâmetro do grafo? Y OR N ";
                        char a;
                        std::cin >> a;
                        if(a=='Y' || a=='y'){
                            for(auto n : aux){
                                    std:: cout << n->email << std::endl;
                            }
                        }
                    }
                    break;
                    case 0:
                        std::cout << "Salvando..." << std::endl;
                        g.saveuser();
                        g.savelinks();
                        return;
                    break;
                    default:
                    std::cout << "Opcao invalida, tente novamente" << std::endl;
                    break;
                }
                std::cout << "Pressione Enter para continuar...";
                std::cin.ignore();
                std::cin.get();
            }
        }
    };
};

