from pprint import pprint

def determinante(matriz):
    tam = len(matriz)
    
    if tam == 2:
        return (matriz[0][0]*matriz[1][1])-(matriz[0][1]*matriz[1][0])    
    else:
        det = 0
        
        for j in range(tam):
            sub_matriz = list()
            for i in range(1,tam):
                x = matriz[i].copy()
                x.pop(j)
                sub_matriz.append(x)

            if j%2 == 0:
                det += matriz[0][j]*determinante(sub_matriz)
            else:
                det -= matriz[0][j]*determinante(sub_matriz)
        
        return det

def main():
    m = int(input()) # Numero de Matrizes
    n = int(input()) # Tamanho das Matrizes NxN
    d = 1
    for _ in range(m):
        matriz = list()
        
        for _ in range(n):
            x = input().split()
            x = [int(i) for i in x]
            matriz.append(x)
            
        d *= determinante(matriz)
        
    print(f"Após as {m} transformações, o objeto {n}-dimensional teve o volume multiplicado no valor {d}.")
    
    
    
    return

if __name__ == '__main__':
    main()