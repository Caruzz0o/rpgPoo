//=====================================================================    
//Projeto semana 3
//Felipe Caruzzo Rosini e José Vinicio Fernandes da Costa
//=====================================================================    

#include <iostream>
#include <string>

using namespace std;

class Jogador {
private:
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

    Jogador(string n) {
        nome = n;
        nivel = 1;
        hpMaximo = 100;
        hp = 100;
        xp = 0;
    }

    Jogador() {
        nome = "Sem nome";
        nivel = 1;
        hpMaximo = 100;
        hp = 100;
        xp = 0;
    }

    ~Jogador() {
        cout << "Jogador " << nome << " foi destruido!" << endl;
    }

    //========GETERS========
    string getNome() { 
        return nome; 
    }
    
    int getHpMaximo() { 
        return hpMaximo; 
    }
    
    int getNivel() { 
        return nivel; 
    }
    
    int getHp() { 
        return hp; 
    }

    int getXp(){
        return xp;
    }


    //========SETERS========
    void setNivel(int n) {
        if (n >= 0) {
            nivel = n;
        } else {
            cout << "Erro: Nivel nao pode ser negativo" << endl;
        }
    }

    void setHp(int h) {
        if (h < 0) {
            hp = 0;
        } else if (h > hpMaximo) {
            hp = hpMaximo;
        } else {
            hp = h;
        }
    }

    void setXp(int n){
        this->xp = n;
    }


    //=======MÉTODOS=========
    void exibirStatus() {
        cout << "Status do Jogador" << endl;
        cout << "Nome: " << nome << endl;
        cout << "Nivel: " << nivel << endl;
        cout << "Xp: " << xp << "/100" << endl;
        cout << "HP: " << hp << "/" << hpMaximo << endl;
        if (estaVivo()) {
            cout << "Vivo: Sim" << endl;
        } else {
            cout << "Vivo: Nao" << endl;
        }
    }

    bool estaVivo() {
        return hp > 0;
    }

    void receber_dano(int quantidade) {
        if (quantidade > 0) {
            setHp(hp - quantidade);
            cout << nome << " recebeu " << quantidade << " de dano! HP atual: " << hp << endl;
        } else {
            cout << "Dano invalido" << endl;
        }
    }

    void curar(int quantidade) {
        if (quantidade > 0) {
            if (estaVivo()) {
               setHp(hp + quantidade);
               cout << nome << " curou " << quantidade << " de HP atual: " << hp << endl;
            } else {
                cout << "Jogador morto, nao pode ser curado" << endl;
            }
        } else {
            cout << "Cura invalida" << endl;
        }
    }

    void subirNivel(){
        nivel = nivel + 1;
        xp = 0;
    }

    void experiencia (int quantidade) {
        xp = xp + quantidade;
        while (xp >= 100){
            nivel = nivel + 1;
            xp = xp - 100;
        }
    }
    //=========FIM MÉTODOS=========
};

class armas{
private:
    string nome;
    float desgate;

public:
    armas(string nome){
        this->nome = nome;
        this->desgate = 100;
    }

    void setNome(string Nome){
        this->nome = Nome;
    }
    
    void setDesgaste(float Desgaste){
        this->desgate = Desgaste;
    }

    string getNome(){
        return this->nome;
    }

    float getDesgaste(){
        return this->desgate;
    }

    ~armas(){
        cout << this->getNome() << " foi destruido!" << endl;
    }
};

/*
class armasBrancas : public armas{
private:

public:

};

class armasFogo : public armas{
private:

public:

};

/*
class Policial : public Jogador{
private:
    
public:

};
*/
int main() {
    //Policial heroi("Henry", 100);
    armas a("Pistola");
    cout << a.getNome() << "|" << a.getDesgaste() << endl;

    return 0;
}
