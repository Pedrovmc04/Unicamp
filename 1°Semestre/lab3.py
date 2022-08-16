q = int(input())
t = float(input())
c = int(input())
n = int(input())

m = n
soma = 0
contador = 0

for i in range(1,q+1):
    soma += (t*i)+(t*c) 
    print("{} {:.2f} {:.2f}".format(i, (t*i)+(t*c) , soma))

print("{:.2f}".format(soma))

while(m <= soma):
    contador += 1
    print(m)
    m += n

print(contador)
print("BATERIA DE TESTES TERMINADA")