class Mapa:
    def __init__(self,clone=0,item=None,rooms=None):
        
        self.clone = clone
        
        if item is None:
            self.item = []
        else:
            self.item = item

        if rooms is None:
            self.rooms = []
        else:
            self.rooms = rooms

    def __str__(self):
        text = ("Clone:" + str(self.clone)
                 +"\nItens:" + str(self.item)
                 +"\nSalas:" + str(self.rooms))
        return text 


n = int(input())    #Quantidade de Salas

rooms = []          #Salas do mapa

for i in range(n):  #Input das Salas
    auxiliar = input().split()
    for j in range(len(auxiliar)):auxiliar[j] = int(auxiliar[j])
    rooms.append(auxiliar[1:6])
    

m = int(input())    #Quantidade de Itens
itens = [None]*n    #Itens para cada sala[i]

for i in range(m):  #Input do item na sala[i]
    auxiliar = input().split(' ')
    auxiliar[0] = int(auxiliar[0])
    itens[auxiliar[0]] = auxiliar[1]

clone_position = int(input())   #Posição do bot
bot_position = int(input())     #Posição inicial
bot_inv = []                    #Inventario do bot
inv_limit = int(input())        #Limite do Inventario
moves = input().split()         #Lista de movimentos
for i in range(len(moves)):moves[i] = int(moves[i])#Transforma os movimentos em inteiros

mapa = Mapa(clone_position,itens,rooms)

print('''Bem-vindo as Aventuras de Sarah 2.0
Sarah acorda no saguão do antigo castelo de sua família,ela tem a oportunidade única de derrotar o seu clone maligno que se apoderou do reino.
Para isso ela deve encontrar o baú da sua família que contém a espada mágica que apenas a verdadeira herdeira pode utilizar.
Na sala onde está Sarah vê várias portas. Qual é a sua próxima ação?''')

print("DEBUG - O clone está na sala: {}".format(mapa.clone))

move = 0
has_sword = False
has_potion = False

while True:
    
    #Informar posição e pegar item
    if mapa.item[bot_position] is not None:
        
        print("Você está na sala de número {} ela contém um baú com {} e dela você pode ir para as salas {}".format(bot_position,mapa.item[bot_position],mapa.rooms[bot_position]))
        
        print("Pegar {}".format(mapa.item[bot_position]))
        
        if len(bot_inv) < inv_limit:
            
            if mapa.item[bot_position] == 'espada':has_sword=True
            if mapa.item[bot_position] == 'poção':has_potion=True
            
            bot_inv.append(mapa.item[bot_position])
            print("{} adicionado ao inventário".format(mapa.item[bot_position]))
            mapa.item[bot_position] = None
            
        else:
            print("Inventário cheio!")
    
    else:
        print("Você está na sala de número {} e dela você pode ir para as salas {}".format(bot_position,mapa.rooms[bot_position]))
    
    #Verifica a poção
    if has_potion:
        print("Você pegou a poção da morte e virou pó instantaneamente. Tente novamente...")
        break
    
    #Mover para proxima Sala
    print("Mover para sala {}".format(moves[move]))
    bot_position = moves[move]
    move += 1
    
    
    #Verifica a Vitoria
    if bot_position == mapa.clone:
        if has_sword:
            print("Você derrotou o clone maligno com a espada mágica! Com a Sarah no reino o mundo pode voltar ao equilíbrio.\nPARABÉNS!")
        else:
            print("Infelizmente você encontrou o clone sem a espada das fadas e foi derrotado. Tente novamente...")
        break
    
    