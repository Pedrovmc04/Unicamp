x = 0
y = 0

while True:
    n = input().split(' ')
    if(n[0] == '0'):break

    x = int(n[1])
    y = int(n[2])

    if n[0] == '+':
        print(x+y)
    elif n[0] == '-':
        print(x-y)
    elif n[0] == '*':
        print(x*y)
    elif n[0] == '/':
        print(x//y , x % y)
    else:
        if(x == y):print(0)
        else:
            if(x < y): x,y = y,x

            for i in range(1,x-y):
                if((x-y)%i == 0):print(i ,end=' ')
            print(x-y)