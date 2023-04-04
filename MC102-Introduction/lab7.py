def frequency(lista):
    
    last = lista[0]
    count = 1
    maximum = 0
    answer = ""
    
    for i in range(1,len(lista)):
        if lista[i] != last:
            
            if maximum < count:
                maximum = count
                answer = last
            
            last = lista[i]
            count = 1
        else:
            count += 1
       
    if maximum < count:
        maximum = count
        last = lista[-1]
    
    return answer + " " + str(maximum)


def elements(lista):
    new = lista.copy()
    new.sort()
    
    last = new[0]
    count = 1
    
    for i in range(1,len(new)):
        if new[i] != last:
            last = new[i]
            count += 1

    return count

def deleter(lista):
    new = []
    for i in range(len(lista)):
        if lista[i] == remove: continue
        flag = True
        for j in range(i):
            if lista[i] == lista[j]: flag = False
        
        if flag:
            new.append(lista[i])

    return new

def formatter(lista):
    global ha
    global cr
    global cc
    
    for i in range(len(lista)):
        lista[i] = lista[i].lower()
        lista[i] = lista[i].replace(' ','-')
        
        if(lista[i][0:2] == 'ha'):
            lista[i] = 'HA' + lista[i][2:]
            ha.append(lista[i])
        
        if(lista[i][0:2] == 'cr'):
            lista[i] = 'CR' + lista[i][2:]
            cr.append(lista[i])
        
        if(lista[i][0:2] == 'cc'):
            lista[i] = 'CC' + lista[i][2:]
            cc.append(lista[i])


if __name__=="__main__":
    ha = [] #Homen Aranha
    cr = [] #Criminoso
    cc = [] #Cena do crime
    
    lista = input().split(', ')

    lista[-1],remove = lista[-1].split('/ ')
    
    print(frequency(lista)) #Printo a ocorrencia mais repetida
    
    print(elements(lista))  #Printo quantos elementos diferentes tem
    
    lista = deleter(lista)  #Deleto os que se repetem e o que o input quer
    
    formatter(lista)        #Formato a string e categorizo elas
        
    print(ha)
    print(cr)
    print(cc)