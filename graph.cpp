#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
namespace graph{
    class digraph{
        private:
        struct node{
            std::string email;
            std::string nome;
            std::string datanasc;
            std::string ntelefone;
            std::string cidade;
            std::vector<std::string> seguidores;
            std::vector<node*> links;
        };
        std::unordered_map<std::string, node> nodes;
        public:
        bool insert_node(std::string eemail, std::string name, std::string datana, std::string ntele, std::string city){
            if(nodes.count(eemail)>0) return false; //se a chave já existir
            node n;                 //cria um nodo
            n.email = eemail;
            n.nome = name;
            n.datanasc = datana;            //guarda valor
            n.ntelefone = ntele;
            n.cidade = city;
            nodes[eemail] =  n;             //insere no map
            return true;
        }
        size_t size(){
            return nodes.size();
        }
        bool existe(std::string a){
            if(nodes.count(a)>0){
                return true;
            }
            return false;
        }

        node *find(std::string s){
            //if(nodes.count(s)>0) return &nodes[s];
            auto it = nodes.find(s); //pesquisa no map
            return it==nodes.end() ? nullptr : &it->second;
        }
        bool linkexiste(const std::string &origem, const std::string &destino){
            auto teste = find(origem);
            auto teste2 = find(destino);
            int b = teste->links.size();
            for(int i=0; i<b; i++){
                if(teste->links[i]==teste2){
                    return true;
                }
            }
            return false;
        }
        bool insert_link(const std::string &src, const std::string &dest){
            auto psrc = find(src);
            if(!psrc) return false;
            auto pdest = find(dest);
            if(!pdest) return false;
            //NÃO INSERIR SE O LINK JÁ EXISTIR
            //...
            //...
            //...
            //A FAZER
            if(linkexiste(src, dest)){
                std::cout << "Link já existe!\n";
                return false;
            }
            psrc->links.push_back(pdest);
            pdest->seguidores.push_back(psrc->email);
            return true;
        }
        bool remove_link(const std::string &src, const std::string &dest){
            if(linkexiste(src, dest)){
                auto teste = find(src);
                auto teste2 = find(dest);
                int b = teste->links.size();
                for(int i=0; i<b; i++){
                    if(teste->links[i]==teste2){
                        teste->links.erase(teste->links.begin() + i);
                        return true;
                    }
                }
            }
            return false;
        }

        void show(){
            for(auto n:nodes){
                int b = n.second.links.size();
                std::cout << "Nome: " << n.second.nome << std::endl;
                std::cout << "E-mail: " << n.second.email << std::endl;
                std::cout << "Data de nascimento: " << n.second.datanasc << std::endl;
                std::cout << "Telefone: " << n.second.ntelefone << std::endl;
                std::cout << "Cidade: " << n.second.cidade << std::endl;
                std::cout << "Seguindo: ";
                for(int i=0; i<b; i++){
                    std::cout << n.second.links[i]->email << ", ";
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }

        void showuser(const std::string &chave){
            auto a = find(chave);
                std::cout << "Nome: " << a->nome << std::endl;
                std::cout << "E-mail: " << a->email << std::endl;
                std::cout << "Data de nascimento: " << a->datanasc << std::endl;
                std::cout << "Telefone: " << a->ntelefone << std::endl;
                std::cout << "Cidade: " << a->cidade << std::endl;
                std::cout << "Seguindo: ";
                int b = a->links.size();
                for(int i=0; i<b; i++){
                    std::cout << a->links[i]->email << ", ";
                }
                std::cout << std::endl;
                std::cout << std::endl;
        }
        void remove(const std::string &e){
            auto a = find(e);
            int b = a->seguidores.size();
            for(int i=0; i<b; i++){
                auto c = find(a->seguidores[i]);
                
            }
            nodes.erase(e);
        }

        void save2dot(const std::string &filename){
            std::ofstream dot(filename);
            dot << "digraph{\n";
            for(auto n:nodes){
                dot << '\t' << '"' << n.first << '"'; 
                if(!n.second.links.empty()){
                    dot << " -> { ";
                    for(auto link:n.second.links){
                        dot << '"' << link->email << "\" " ;
                    }
                    dot << "}";
                }
                dot << '\n';
            }
            dot << "}\n";
        }
        /*void show(){
            save2dot("/tmp/grafobonito.dot");
            std::system("dot -Tx11 /tmp/grafobonito.dot");
        }*/
    };
}
