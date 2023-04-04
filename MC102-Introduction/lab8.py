from datetime import datetime, timedelta

class Produto:
    def __init__(self,nome,quantidade,categoria,preco,vencimento):
        self.nome = nome
        self.quantidade = quantidade
        self.categoria = categoria
        self.preco = preco
        self.vencimento = vencimento

    def remove(self,quantidade):    #Funcao para remover os produtos
        if self.quantidade < quantidade:
            print("ERROR")
        else:
            self.quantidade = self.quantidade-quantidade
            print("SUCCESS")
        
    def vender(self,quantidade):    #Funcao para vender os produtos
        self.quantidade = self.quantidade - quantidade
        return self.preco*quantidade
    
    def __str__(self):
        texto = ("Quantidade: " + str(self.quantidade) + "\n" +
                "Categoria: " + str(self.categoria) + "\n" +
                "Preço : " + str(self.preco) + "\n" +
                "Vencimento" + str(self.vencimento) + "\n")
        return texto
                  

def estoque(produtos):  #Printa o que tem no estoque
    conjuntos = dict()
    
    for produto in produtos.values():
        if produto.quantidade == 0: continue    #Verifica se tem o produto no estoque
        
        categoria = produto.categoria
        nome = produto.nome
        
        if categoria in conjuntos:  #   Divide por categoria em conjuntos
            conjuntos[categoria].add(nome)
        else:
            conjuntos[categoria] = set([nome])
    
    print("* ESTOQUE")
    
    for chave in sorted(conjuntos):
        print("- {}".format(chave))
        
        for produto in sorted(conjuntos[chave]):
            print("{} {}".format(produto,produtos[produto].quantidade))


def reposicao(produtos):
    new = []
    
    for produto in produtos.values():   #Vejo qual produto esta faltando
        if produto.quantidade == 0:
            new.append(produto.nome)
    
    if len(new) == 0:return

    print("* REPOSICAO")
    
    for produto in new:
        print(produto)

def promocao(produtos,data):
    new = []
    
    for produto in produtos.values():
        date = produto.vencimento
        date = datetime(int(date[4:8]),int(date[2:4]),int(date[0:2]))
        duration = int((date-data).total_seconds())
        duration = duration//86400  #transformo o tempo de segundos para dias
        
        if duration <= 7 and produto.quantidade != 0:
            new.append(produto.nome)
    
    if len(new) == 0:return
    
    print("* PROMOCAO")
    
    for produto in new:
        print(produto)
       
if __name__ == "__main__":
    produtos = dict()
    saldo = 0

    while True:
        
        t = int(input())
        
        if t == 0: break
        
        n = int(input())    #Numero de operações
        
        if t == 1:
            
            for i in range(n,0,-1):
                
                operation = input().split()
                
                if operation[0] == '1':
                    if operation[1] in produtos.keys():
                        produtos[operation[1]].remove(int(operation[2]))
                    else:
                        print("ERROR")
                elif operation[0] == '0':
                    produtos[operation[1]] = Produto(operation[1],int(operation[2]),operation[3],float(operation[4]),operation[5])         
        else:
            
            for i in range(n,0,-1):
                operation = input().split()
                saldo += produtos[operation[0]].vender(int(operation[1]))
    
    data = input()
    dia = int(data[0:2])
    mes = int(data[2:4])
    ano = int(data[4:8])
    data = datetime(ano,mes,dia)
    
    estoque(produtos)
    
    print("* SALDO {:.2f}".format(saldo))
    
    reposicao(produtos)
    
    promocao(produtos,data)