def rotacao(matriz,ini,fim):
    new = []
    
    for i in range(ini[1],fim[1]):            #percorro pelas colunas
        aux = []
        for j in range(fim[0]-1,ini[0]-1,-1):   #percorro pelas linhas
            aux.append(matriz[j][i])
            matriz[j][i] = '000'
        new.append(aux)
    
    for i in range(len(new)):
        for j in range(len(new[i])):
            matriz[i+ini[0]][j+ini[1]] = new[i][j]

def espelhamento_v(matriz,ini,fim):
    new = []
    
    for i in range(fim[0]-1,ini[0]-1,-1):
        aux = []
        for j in range(ini[1],fim[1]):
            aux.append(matriz[i][j])
        new.append(aux)
        
    for i in range(ini[0],fim[0]):
        for j in range(ini[1],fim[1]):
            matriz[i][j] = new[i-ini[0]][j-ini[1]]

def espelhamento_h(matriz,ini,fim):
    new = []
    
    for i in range(ini[0],fim[0]):
        aux = []
        for j in range(fim[1]-1,ini[1]-1,-1):
            aux.append(matriz[i][j])
        new.append(aux)
        
    for i in range(ini[0],fim[0]):
        for j in range(ini[1],fim[1]):
            matriz[i][j] = new[i-ini[0]][j-ini[1]] 
    
def recorte(matriz,ini,fim,x,y):
    new = []
    
    for i in range(ini[0],fim[0]):
        aux = []
        for j in range(ini[1],fim[1]):
            aux.append(matriz[i][j])
            matriz[i][j] = '000'
        new.append(aux)
    
    for i in range(y,y+len(new)):
        for j in range(x,x+len(new[i-y])):
            matriz[i][j] = new[i-y][j-x]

def copia(matriz,ini,fim,x,y):
    new = []
    
    for i in range(ini[0],fim[0]):
        aux = []
        for j in range(ini[1],fim[1]):
            aux.append(matriz[i][j])
        new.append(aux)
    
    for i in range(y,y+len(new)):
        for j in range(x,x+len(new[i-y])):
            matriz[i][j] = new[i-y][j-x]

if __name__ == "__main__":
    n,m = input().split()
    n = int(n)
    m = int(m)
    operacoes = int(input())

    matriz = []
    
    ini = [0,0]
    fim = [m,n] #linhas,colunas 
    
    for i in range(m):
        x = input().split()
        matriz.append(x)
    
    for i in range(operacoes):
        operacao = input().split()
        
        if operacao[0] == 'selecao':
            ini[1] = int(operacao[1])
            ini[0] = int(operacao[2])
            
            fim[1] = ini[1]+int(operacao[3])
            fim[0] = ini[0]+int(operacao[4])
            
            #print(ini,fim)
            
        elif(operacao[0] == 'rotacao'):
            rotacao(matriz,ini,fim)
        elif operacao[0] == 'espelhamento':
            if operacao[1] == 'v':espelhamento_v(matriz,ini,fim)
            if operacao[1] == 'h':espelhamento_h(matriz,ini,fim)
        elif operacao[0] == "recorte":
            recorte(matriz,ini,fim,int(operacao[1]),int(operacao[2]))
        elif operacao[0] == "copia":
            copia(matriz,ini,fim,int(operacao[1]),int(operacao[2]))
    
    for i in range(m):
        print(*matriz[i])
