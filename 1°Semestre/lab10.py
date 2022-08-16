from pprint import pprint

def mutations(mutacoes,caracteristicas,primitiva):
    for x in caracteristicas:   # Ordeno as mutações
        for i in range(len(caracteristicas[x][0])):
            dna = caracteristicas[primitiva][0][i] + caracteristicas[primitiva][1][i]
            dnaa = caracteristicas[x][0][i] + caracteristicas[x][1][i]
            if(dna < dnaa):mutacoes[x] += 1

def main():
    caracteristicas = dict()
    mutacoes = dict()

    n = int(input())

    especies = [input().split(" | ") for _ in range(n)]
    mark = [0 for _ in range(n)]
    
    for i in range(len(especies)):
        especies[i][1] = especies[i][1].split()
    
    n = int(input())

    for i in range(n):
        aux = input()
        caracteristicas[aux] = [input() for _ in range(2)]
        mutacoes[aux] = 0
        if i == 0: primitiva = aux

    mutations(mutacoes,caracteristicas,primitiva)

    sorted_keys = sorted(mutacoes, key=mutacoes.get)

    for i in sorted_keys:
        print(f"CARACTERÍSTICA: {i}")
        
        for j in range(len(especies)):
            if mark[j] :continue
            flag = True
            for k in especies[j][1]:
                if mutacoes[k] > mutacoes[i]:flag = False
            if flag :
                print(especies[j][0])
                mark[j] = 1
            

if __name__ == '__main__':
    main()