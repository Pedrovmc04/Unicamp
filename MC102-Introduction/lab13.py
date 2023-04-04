def solve(arquivo):
    if(pais[arquivo] == arquivo):
        return ''
    else:
        return solve(pais[arquivo])+pais[arquivo]+'_'

def main():
    
    raiz,n = input().split()
    n = int(n)
    
    pais[raiz] = raiz

    for _ in range(n):
        filho,pai = input().split()
        pais[filho] = pai
        print(solve(filho)+filho)

if __name__ == '__main__':
    pais = dict()
    main()