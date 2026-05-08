//=====================================================================    
//Projeto semana 3
//Felipe Caruzzo Rosini e José Vinicio Fernandes da Costa
//=====================================================================    

#include <iostream>
#include <string>
#include <stdexcept> // Para as Excecoes (runtime_error)
#include <cstdlib>
#include <ctime>

using namespace std;

//================================================
// CLASSE ALVO (Para o Sistema de Ataque)
//================================================
class Zumbi {
private:
    int hp;
public:
    Zumbi(int h) { hp = h; }
    
    void receberDano(int dano) {
        hp -= dano;
        if (hp < 0) hp = 0;
        cout << "-> Zumbi recebeu " << dano << " de dano! (HP restante: " << hp << ")" << endl;
    }
    
    bool estaVivo() { return hp > 0; }
};


//================================================
// CLASSES DE ARMAS (Herança + Polimorfismo)
//================================================
class armas {
protected: // Mudamos para protected para as filhas poderem acessar
    string nome;
    float durabilidade;
    int danoBase;

public:
    armas(string n, int dano) {
        nome = n;
        danoBase = dano;
    }

    string getNome() { return nome; }
    float getDurabilidade() { return durabilidade; }
    void setDurabilidade(float d) { durabilidade = d; }

    // POLIMORFISMO: Método puramente virtual
    // Cada arma filha vai calcular o dano de um jeito!
    virtual int calcularDano() = 0; 

    virtual ~armas() {
        cout << nome << " foi destruido!" << endl;
    }
};

class armasBrancas : public armas {
public:
    armasBrancas(string nome, int dano) : armas(nome, dano) {
        float durabilidadeRandom = (rand() % 86) + 15; // 15 a 100
        setDurabilidade(durabilidadeRandom);
    }

    // Sobrescrevendo o método (Polimorfismo)
    int calcularDano() override {
        // EXCEÇÃO: Tentar atacar com arma quebrada
        if (durabilidade <= 0) {
            throw runtime_error("A arma branca quebrou e nao pode ser usada!");
        }
        
        durabilidade -= 10.0f; // Gasta durabilidade ao atacar
        cout << "[Arma Branca] " << nome << " usada! Durabilidade caiu para " << durabilidade << "%" << endl;
        return danoBase; // Dano fixo
    }
};

class armasFogo : public armas {
public:
    armasFogo(string nome, int dano) : armas(nome, dano) {
        float durabilidadeRandom = (rand() % 61) + 40; // 40 a 100
        setDurabilidade(durabilidadeRandom);
    }

    // Sobrescrevendo o método (Polimorfismo)
    int calcularDano() override {
        // EXCEÇÃO: Tentar atirar com arma emperrada/quebrada
        if (durabilidade <= 0) {
            throw runtime_error("A arma de fogo travou por falta de manutencao!");
        }
        
        durabilidade -= 20.0f; // Armas de fogo desgastam mais rápido neste exemplo
        
        // Dano crítico aleatório
        int danoFinal = danoBase;
        if (rand() % 100 > 70) { // 30% de chance de crítico
            danoFinal *= 2;
            cout << "[Tiro CRITICO!] ";
        }
        cout << nome << " disparada! Durabilidade: " << durabilidade << "%" << endl;
        return danoFinal;
    }
};


//================================================
// CLASSES DE PERSONAGENS PRINCIPAIS
//================================================
class Jogador {
protected: // Protected para as classes filhas acessarem
    string nome;
    int nivel;
    int hp;
    int hpMaximo;
    int xp;
    
public:
    Jogador(string n, int hpm) {
        nome = n;
        nivel = 1;
        hpMaximo = hpm;
        hp = hpm;
        xp = 0;
    }

    virtual ~Jogador() {
        cout << "Jogador " << nome << " foi destruido!" << endl;
    }

    string getNome() { return nome; }
    
    // POLIMORFISMO: Cada classe terá uma habilidade especial
    virtual void usarHabilidade() = 0; 

    // SISTEMA DE ATAQUE + TRATAMENTO DE EXCEÇÃO
    void atacar(Zumbi& alvo, armas* armaEquipada) {
        if (!alvo.estaVivo()) {
            cout << "O zumbi ja esta morto!" << endl;
            return;
        }

        cout << "\n" << nome << " esta atacando o Zumbi com " << armaEquipada->getNome() << "!" << endl;
        
        // BLOCO TRY-CATCH para capturar a exceção da arma quebrada
        try {
            int danoCausado = armaEquipada->calcularDano(); 
            alvo.receberDano(danoCausado);
        } 
        catch (const exception& erro) {
            // Se o throw runtime_error for acionado na arma, o código cai aqui!
            cout << "FALHA NO ATAQUE: " << erro.what() << endl;
        }
    }
};

// HERANÇA 1: Policial
class Policial : public Jogador {
public:
    Policial(string nome) : Jogador(nome, 120) {} // Começa com mais vida

    void usarHabilidade() override {
        cout << getNome() << " usou [Tiro de Precisao]! (Habilidade de Policial)" << endl;
    }
};

// HERANÇA 2: Medico
class Medico : public Jogador {
public:
    Medico(string nome) : Jogador(nome, 90) {} // Começa com menos vida, mas pode curar

    void usarHabilidade() override {
        cout << getNome() << " usou [Primeiros Socorros]! Curou 30 HP. (Habilidade de Medico)" << endl;
        hp += 30;
        if (hp > hpMaximo) hp = hpMaximo;
    }
};


//================================================
// MAIN - TESTANDO TUDO
//================================================
int main() {
    srand(time(0));

    cout << "=== INICIANDO JOGO ===" << endl;

    // Criando Personagens (Classes principais / Herança)
    Policial policial("Henry");
    Medico medico("Alice");

    // Criando Inimigo
    Zumbi zumbiMutante(100);

    // Criando Armas
    armasBrancas faca("Faca de Sobrevivencia", 15);
    armasFogo escopeta("Escopeta Calibre 12", 40);

    // Testando o Polimorfismo nas habilidades
    policial.usarHabilidade();
    medico.usarHabilidade();

    // Forçando a durabilidade da faca ser baixa para testar a EXCEÇÃO
    faca.setDurabilidade(5.0f); 

    // Testando o Sistema de Ataque
    policial.atacar(zumbiMutante, &escopeta);
    
    // Esse ataque vai funcionar (durabilidade vai de 5 para -5)
    medico.atacar(zumbiMutante, &faca); 
    
    // Esse ataque vai DAR ERRO (Exceção), pois a durabilidade ficou negativa no ataque anterior
    medico.atacar(zumbiMutante, &faca); 

    cout << "\n=== FIM DE JOGO ===" << endl;
    return 0;
}