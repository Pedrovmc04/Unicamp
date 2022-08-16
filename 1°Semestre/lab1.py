

mes = int(input())
semana = input()
valor = float(input())
ans = float(0)


if mes%7 == 0:
    ans = valor/2
elif semana == "sexta-feira":
    ans = valor - (valor/4)
else:
    ans = valor - mes

if(ans < 0):
    ans = 0

print("{0:.2f}".format(ans))

if(semana == "sábado" or semana == "domingo"):
    print("Agradecemos a preferência, tenha um ótimo fim de semana!")
elif(semana == "segunda-feira"):
    print("É um dia terrível, você não devia ter saído da cama.")
else:
    print("Agradecemos a preferência, tenha uma ótima {}!".format(semana))
