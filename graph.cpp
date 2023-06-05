//---------1 milhao de bibliotecas-----------//
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <list>
#include <queue>
//#include <functional> #Passar funcao por parametro



namespace graph{
    class digraph{
        //--------ESTRUTURAS UTILIZADAS--------//
        private:
        struct node{
            std::string email;
            std::string nome;
            std::string datanasc;
            std::string ntelefone;
            std::string cidade;
            std::vector<std::string> seguidores;
            std::vector<node*> links;
            bool flag = false;
        };
        std::unordered_map<std::string, node> nodes;
        std::unordered_set<node *> visited;
        //---------------- INICIO DAS FUNCOES ------------------//
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
                std::cout << "Seguindo: " << "(" << a->links.size() << ") ";
                int b = a->links.size();
                for(int i=0; i<b; i++){
                    std::cout << a->links[i]->email << ", ";
                }
                std::cout << std::endl;
                std::cout << "Seguidores: " << "(" << a->seguidores.size() << ")";
                for(int j=0; j<b; j++){
                    std::cout << a->seguidores[j] << ", ";
                }
                std::cout << std::endl;
        }
        void remove(const std::string &e){
            auto a = find(e);               //ENCONTRA O NODE A SER REMOVIDO
            int b = a->seguidores.size();   //PEGA O TAMANHO DO VECTOR DE SEGUIDORES
            for(int i=0; i<b; i++){                 
                auto c = find(a->seguidores[i]);    //ENCONTRA A PESSOA QUE SEGUE ELE
                int y = c->links.size();            //PEGA O TAMANHO DO VETOR DE SEGUIDORES DESSA PESSOA
                for(int j=0; j<y; j++){             //PERCORRE OS LINKS DESSA PESSOA
                    if(c->links[j]==a){             //TESTA SE O LINK É IGUAL AO REMOVIDO
                        c->links.erase(c->links.begin()+j); ///APAGA O LINK
                    }
                }
            }
            nodes.erase(e);                         //APAGA O NODE
            std::cout << "Usuario removido!" << std::endl;
        }
        int nusers(){
            int a = nodes.size();
            return a;
        }

        void finddistance(const std::string &e, const std::string &f){
            if(existe(e) && existe(f)){
            auto a = find(e);
            auto b = find(f);
            bool encontrou = false;
            int distance = 0;
            
        }
        }

        void saveuser(){
            std::ofstream arquivo("Usuarios.txt");
            if(arquivo.is_open()){
                for (const auto& item : nodes){
                    const struct node& pessoa = item.second;
                    arquivo << pessoa.email << ","
                    << pessoa.nome << ","
                    << pessoa.datanasc << ","
                    << pessoa.ntelefone << ","
                    << pessoa.cidade << std::endl;
                }
                arquivo.close();
                std::cout << "Dados gravados no arquivo com sucesso." << std::endl;
            }
            else {
                std::cout << "Erro ao abrir o arquivo." << std::endl;
            }
        }

        void savelinks(){
            std::ofstream arquivo2("Links.txt");
            if(arquivo2.is_open()){
                for(const auto& n : nodes){
                    const node& a = n.second;
                    const std::string& email = a.email;
                    for(node* link : a.links){
                        arquivo2 << email << "," << link->email << std::endl;
                    }
                }
                arquivo2.close();
                std::cout << "Links armazenados!" << std::endl;
            }
            else{
                std::cout << "Erro ao gravar links!" << std::endl;
            }
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

        void showdot() {
            std::string dotFilename = "/tmp/grafobonito.dot";
            std::string outputFilename = "/tmp/grafobonito";           
            save2dot(dotFilename);
            std::cout << "DIGITE 1 PARA SALVAR EM PDF" << std::endl;
            std::cout << "DIGITE 2 PARA SALVAR EM JPEG" << std::endl;
            std::cout << "DIGITE 3 PARA SALVAR EM PNG" << std::endl; 
            std::cout << "DIGITE 4 PARA MOSTRAR .DOT" << std::endl;
            int p;
            std::cin >> p;
            switch (p) {
                case 1:
                    {
                        std::string pdfCommand = "dot -Tpdf " + dotFilename + " -o " + outputFilename + ".pdf";
                        std::system(pdfCommand.c_str());
                        break;
                    }
                case 2:
                    {
                        std::string jpegCommand = "dot -Tjpeg " + dotFilename + " -o " + outputFilename + ".jpeg";
                        std::system(jpegCommand.c_str());
                        break;
                    }
                case 3:
                    {
                        std::string pngCommand = "dot -Tpng " + dotFilename + " -o " + outputFilename + ".png";
                        std::system(pngCommand.c_str());
                        break;
                    }
                case 4:
                    {
                        std::system("dot -Tx11 /tmp/grafobonito.dot");
                    }
                default:
                    std::cout << "Opção inválida" << std::endl;
                    break;
            }
    }


        int graumedioentrada(){
            int a=0;
            int b=0;
            for(auto n:nodes){
                a++;
                b+=n.second.seguidores.size();
            }
            return b/a;
        }
        int graumediosaida(){
            int a=0;
            int b=0;
            for(auto n:nodes){
                a++;
                b+=n.second.links.size();
            }
            return b/a;
        }
        node* morefollowers(){
            int maiorNumeroSeguidores = 0;
            node* usuarioMaiorSeguidores = nullptr;

            for (auto& pair : nodes) {
                node& usuario = pair.second;
                int numeroSeguidores = usuario.seguidores.size();

                if (numeroSeguidores > maiorNumeroSeguidores) {
                    usuarioMaiorSeguidores = &usuario;
                    maiorNumeroSeguidores = numeroSeguidores;
                }
            }
            return usuarioMaiorSeguidores;
        }
        int count =0;
        void visit_dfs_from(node *p){
            visited.insert(p);
            std::cout << p->email << std::endl;
            for(auto n: p->links){
                if(visited.count(n)==0){
                    visit_dfs_from(n);
                }
            }
        }
        void dfs_from(const std::string &from){
            auto p = find(from);
            if(!p) return;
            visit_dfs_from(p);
            std::cout << std::endl;
            visited.clear();
            }
            
        std::list<node*> bfs(const std::string &from, const std::string &to){
            std::list<node*> path; //lista que será retornada
            auto pfrom = find(from);
            if(!pfrom) return path;  //se from não existir, retorna lista vazia
            auto pto = find(to);
            if(!pto) return path;       //se to não existir, retorna lista vazia
            bool found = false;
            std::queue<node *> q;
            std::unordered_map<node*, node*> parent;
            q.push(pfrom);
            visited.clear();
            visited.insert(pfrom);
            parent[pfrom] = nullptr;
            while(!q.empty()){
                auto current = q.front();
                q.pop();
                if(current==pto){
                found = true;
                break;
                }
                for(auto n : current->links){
                if(visited.count(n)==0){
                    visited.insert(n);
                    parent[n] = current;
                    q.push(n);
                }
                }
            }
            if(found){
                auto p = pto;
                while(p){
                path.push_front(p);
                p = parent[p];
                }
            }
            return path;
        }

        int diameter() {
            int d_global = 0;
            for (const auto& pair : nodes) {
                int i = diameterbfs(pair.second.email);
                if (i > d_global) {
                    d_global = i;
                }
        }
        return d_global;
    }

int diameterbfs(const std::string& email) {
    std::list<node*> path2;
    auto pfrom = find(email);
    int globalbfs = 0;
    for (const auto& pair2 : nodes) {
        auto pto1 = pair2.second.email;
        auto pto = find(pto1);
        path2.clear();
        std::queue<node*> q2;
        std::unordered_set<node*> visited; // Corrigido: substituído "visited.clear()" por uma nova inicialização
        std::unordered_map<node*, node*> parent2;
        bool found = false;
        q2.push(pfrom);
        visited.insert(pfrom);
        parent2[pfrom] = nullptr;
        while (!q2.empty()) {
            auto current = q2.front();
            q2.pop();
            if (current == pto) {
                found = true;
                break;
            }
            for (auto n : current->links) {
                if (visited.count(n) == 0) {
                    visited.insert(n);
                    parent2[n] = current;
                    q2.push(n);
                }
            }
        }
        if (found) {
            auto temp = pto;
            while (temp != nullptr) {
                path2.push_front(temp);
                temp = parent2[temp];
            }
        }
        if (path2.size() > globalbfs) {
            globalbfs = path2.size();
        }
    }
    return globalbfs;
}






  //---------------FIM DAS FUNCOES-----------------------------//
    };
};
