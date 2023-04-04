print("*Que página de meme do Instagram você é?*")
print("Qual a sua idade?")
idade = int(input())
print(idade)

if idade < 25 and idade >= 0:
    print("Quantos segundos são necessários para saber se um vídeo é bom?")
    tempo = int(input())
    print(tempo)

    if tempo <= 5 and tempo >= 0:
        print("RESULTADO")
        print("Você deveria estar no TikTok")
    elif tempo > 5:
        print("RESULTADO")
        print("Sua página de memes é: @meltmemes")
    else:
        print("Erro: entrada inválida")

elif idade >= 25 and idade <= 40:
    print("Qual banda você gosta mais?")
    banda = input()

    if banda == "A": print("A) Matanza")
    if banda == "B": print("B) Iron Maiden")
    if banda == "C": print("C) Imagine Dragons")
    if banda == "D": print("D) BlackPink")

    if banda == "A" or banda == "B":
        print("RESULTADO")
        print("Sua página de memes é: @badrockistamemes")
    else:
        print("São as capivaras os melhores animais da Terra?")
        x = input()

        if x == "Sim":
            print("Sim")
            print("RESULTADO")
            print("Sua página de memes é: @genteboamemes")
        elif x == "Não":
            print("Não")
            print("RESULTADO")
            print("Sua página de memes é: @wrongchoicememes")
        else:
            print(x)
            print("Erro: entrada inválida")


elif idade > 40 and idade <= 125:    
    print("Que imagem de bom dia você manda no grupo da família?")
    imagem = input()

    if imagem == "A":
        print("A) Bebê em roupa de flor")
        print("RESULTADO")
        print("Sua página de memes é: @bomdiabebe")
    elif imagem == "B":
        print("B) Gato")
        print("RESULTADO")
        print("Sua página de memes é: @kittykatmsgs")
    elif imagem == "C":
        print("C) Coração e rosas")
        print("RESULTADO")
        print("Sua página de memes é: @bomdiaflordodia")
    else:
        print(imagem)
        print("Erro: entrada inválida")

else:
    print("Erro: entrada inválida")
