#=====================================================================
#Projeto semana 3
#Felipe Caruzzo Rosini e José Vinicio Fernandes da Costa
#=====================================================================
class Jogador:
    def __init__(self, nome="Sem nome", hp_maximo=100):
        self.__nome = nome
        self.__hp_maximo = hp_maximo
        self.__hp = hp_maximo
        self.__nivel = 1
        self.__xp = 0

    def __del__(self):
        print("Jogador", self.__nome, "foi destruido!")

    def get_nome(self):
        return self.__nome

    def get_nivel(self):
        return self.__nivel

    def set_nivel(self, nivel):
        if nivel >= 0:
            self.__nivel = nivel
        else:
            print("Nivel nao pode ser negativo")

    def get_hp_maximo(self):
        return self.__hp_maximo

    def get_hp(self):
        return self.__hp

    def get_xp(self):
        return self.__xp

    def set_hp(self, hp):
        if hp < 0:
            self.__hp = 0
        elif hp > self.__hp_maximo:
            self.__hp = self.__hp_maximo
        else:
            self.__hp = hp

    def exibir_status(self):
        print("Status do Jogador")
        print("Nome:", self.__nome)
        print("Nivel:", self.__nivel)
        print("Xp:", self.__xp, "/100")
        print("HP:", self.__hp, "/", self.__hp_maximo)
        if self.esta_vivo():
            print("Vivo: Sim")
        else:
            print("Vivo: Nao")

    def esta_vivo(self):
        return self.__hp > 0

    def receber_dano(self, dano):
        if dano > 0:
            self.set_hp(self.__hp - dano)
            print(self.__nome, "recebeu", dano, "de dano! HP atual:", self.__hp)
        else:
            print("Dano invalido")

    def curar(self, cura):
        if cura > 0:
            if self.esta_vivo():
                self.set_hp(self.__hp + cura)
                print(self.__nome, "foi curado em", cura, "HP atual:", self.__hp)
            else:
                print("Jogador morto, nao pode curar")
        else:
            print("Cura invalida")

    def subir_nivel(self):
        self.__nivel += 1
        self.__xp = 0

    def experiencia(self, quantidade):
        self.__xp += quantidade
        while self.__xp >= 100:
            self.__nivel += 1
            self.__xp -= 100

def main():
    heroi = Jogador("Henry", 100)

    heroi.exibir_status()
    heroi.receber_dano(30)
    heroi.curar(20)
    heroi.receber_dano(10)
    heroi.experiencia(110)
    heroi.exibir_status()
    heroi.curar(50)

if __name__ == "__main__":
    main()
