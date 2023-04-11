def pseudo_random(last_random):
    new_random = (7 * last_random + 111) % 1024
    print("MENSAGEM DEBUG - número gerado:",new_random)
    return new_random

def soco(atacante,oponente,random1,dano=0):
    random1 = random1%3
    dano = (atacante-oponente)*random1

    if dano < 0: dano = 0

    return dano

def arremesso_de_facas(atacante,random1,dano = 0):
    random1 = random1%6

    for i in range(1,random1+1):
        dano += atacante//(3**i)
    
    return dano


def invocacao_de_fada(turno,random1,random2):
    global hp_sarah
    global hp_clone
    global atk_sarah
    global atk_clone
    global def_sarah
    global def_clone

    global defeat_fada

    random1 = random1%100

    if turno == 1:
        hp_sarah += random1
        print("Sarah ganhou {} pontos de vida!".format(random1))

        if random2 < 100 and random2%2 == 1:
            atk_sarah += random2
            print("Sarah ganhou {} pontos de ataque!".format(random2))
        elif random2 < 100 and random2%2 == 0 and random2 != 0:
            def_sarah += random2
            print("Sarah ganhou {} pontos de defesa!".format(random2))
        elif random2 >= 1019:
            hp_clone = 0
            defeat_fada = True

    elif turno == 0:
        hp_clone += random1
        print("O clone ganhou {} pontos de vida!".format(random1))

        if random2 < 100 and random2%2 == 1:
            atk_clone += random2
            print("O clone ganhou {} pontos de ataque!".format(random2))

        elif random2 < 100 and random2%2 == 0 and random2 != 0:
            def_clone += random2
            print("O clone ganhou {} pontos de defesa!".format(random2))

        elif random2 >= 1019:
            hp_sarah = 0
            defeat_fada = True

def verify_defeat():
    if hp_clone <= 0:
        if defeat_fada == False:
            print("O clone foi derrotado! Sarah venceu!")
            print("FIM - PARABENS")
        else:
            print("O quê? A fada trouxe um monstro gigante com ela!")
            print("O Clone e o castelo foram destruídos,")
            print("e Sarah agora tem um novo pet.")
            print("FINAL SECRETO - PARABENS???")
    elif hp_sarah <= 0:
        if defeat_fada == False:
            print("Sarah foi derrotada...")
        else:
            print("O quê? A fada trouxe um monstro gigante com ela!")
            print("Sarah foi derrotada...")

    if hp_sarah <= 0 or hp_clone <=0:return True


sarah = input().split(' ')
clone = input().split(' ')
random = int(input())

turno = 0
dano = 0
action = ""
defeat_fada = False

hp_sarah = int(sarah[0])
atk_sarah = int(sarah[1])
def_sarah = int(sarah[2])

hp_clone = int(clone[0])
atk_clone = int(clone[1])
def_clone = int(clone[2])

while True:
    turno = (turno+1)%2

    if(turno%2 == 1): #Turno da Sarah
        action = input()

        if(action == "soco"):
            random = pseudo_random(random)
            dano = soco(atk_sarah, def_clone,random)

            hp_clone -= dano

            print("O clone sofreu {} pontos de dano!".format(dano))

        elif(action == "facas"):
            random = pseudo_random(random)
            dano = arremesso_de_facas(atk_sarah,random)

            hp_clone -= dano

            print("O clone sofreu {} pontos de dano!".format(dano))

        else:
            auxiliar = pseudo_random(random)
            random = pseudo_random(auxiliar)
            invocacao_de_fada(turno,auxiliar,random)

    else: #Turno do clone
        action = input()

        if(action == "soco"):
            random = pseudo_random(random)
            dano = soco(atk_clone,def_sarah,random)

            hp_sarah -= dano

            print("Sarah sofreu {} pontos de dano!".format(dano))

        elif(action == "facas"):
            random = pseudo_random(random)
            dano = arremesso_de_facas(atk_clone,random)

            hp_sarah -= dano

            print("Sarah sofreu {} pontos de dano!".format(dano))

        else:
            auxiliar = pseudo_random(random)
            random = pseudo_random(auxiliar)
            invocacao_de_fada(turno,auxiliar,random)
        
    if(verify_defeat()):break