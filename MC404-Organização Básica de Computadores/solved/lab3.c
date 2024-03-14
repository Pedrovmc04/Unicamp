int read(int __fd, const void *__buf, int __n){
    int ret_val;
  __asm__ __volatile__(
    "mv a0, %1           # file descriptor\n"
    "mv a1, %2           # buffer \n"
    "mv a2, %3           # size \n"
    "li a7, 63           # syscall write code (63) \n"
    "ecall               # invoke syscall \n"
    "mv %0, a0           # move return value to ret_val\n"
    : "=r"(ret_val)  // Output list
    : "r"(__fd), "r"(__buf), "r"(__n)    // Input list
    : "a0", "a1", "a2", "a7"
  );
  return ret_val;
}

void write(int __fd, const void *__buf, int __n)
{
  __asm__ __volatile__(
    "mv a0, %0           # file descriptor\n"
    "mv a1, %1           # buffer \n"
    "mv a2, %2           # size \n"
    "li a7, 64           # syscall write (64) \n"
    "ecall"
    :   // Output list
    :"r"(__fd), "r"(__buf), "r"(__n)    // Input list
    : "a0", "a1", "a2", "a7"
  );
}

void exit(int code)
{
    __asm__ __volatile__(
        "mv a0, %0           # return code\n"
        "li a7, 93           # syscall exit (64) \n"
        "ecall"
        :   // Output list
        :"r"(code)    // Input list
        : "a0", "a7"
    );
}

#define STDIN_FD  0
#define STDOUT_FD 1

unsigned int to_int(char str[],int n,int *isNegative){
    int number = 0;

    if(str[1] == 'x'){
        if(n == 11 && str[2] >'7')*isNegative = 1;
        for(int i = 2 ; i < n-1 ; i++){
            number = number * 16;
            int digit = (str[i] >= '0' && str[i] <= '9') ? str[i]-'0' : str[i]-'a'+10;
            number += digit;
        }
    }else{
        for(int i = 0 ; i < n-1 ; i++){
            if(str[i] == '-'){
                *isNegative = 1;
                continue;
            }
            number = number * 10;
            number += str[i]-'0';
        }
    }

    if(number < 0)return -number;
    return number;
}

void decimal_print(unsigned int number,int isNegative){
    char decimal[40];
    int sz = 0;

    while(number > 0){
        int digit = number % 10;
        number /= 10;
        decimal[sz++] = digit + '0';
    }

    if(isNegative)decimal[sz++] = '-';

    for(int i = 0 ; i < sz/2 ; i++){
        char temp = decimal[i];
        decimal[i] = decimal[sz-i-1];
        decimal[sz-i-1] = temp;
    }


    decimal[sz++] = '\n';

    write(STDOUT_FD,decimal,sz);
}

void binary_print(unsigned int number,int isNegative){
    char binary[40];
    int sz = 0;

    while(number > 0){
        int digit = number % 2;
        number /= 2;
        binary[sz++] = digit + '0';
    }

    if(isNegative == 1 && sz < 32){
        while(sz < 32)binary[sz++] = '0';

        for(int i = 0 ; i < 32 ; i++){
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }

        for(int i = 0 ; i < 32 ; i++){
            if(binary[i] == '1'){
                binary[i] = '0';
            }else{
                binary[i] = '1';
                break;
            }
        }
    }

    binary[sz++] = 'b';
    binary[sz++] = '0';

    for(int i = 0 ; i < sz/2 ; i++){
        char temp = binary[i];
        binary[i] = binary[sz-i-1];
        binary[sz-i-1] = temp;
    }

    binary[sz++] = '\n';

    write(STDOUT_FD,binary,sz);
}

int hexa_print(unsigned int number,int isNegative,char hexa[]){
    int sz = 0;
    while(number > 0){
        int digit = number%16;
        number /= 16;
        hexa[sz++] = (digit >= 0 && digit <= 9) ? digit+'0' : digit+'a'-10;
    }

    if(isNegative == 1){
        if(sz < 8)while(sz < 8)hexa[sz++] = '0';

        if(hexa[7] <= '8'){
            int buffer = 1;
            for(int i = 0 ; i < sz ; ++i){
                int digit = (hexa[i] >= '0' && hexa[i] <= '9') ? hexa[i]-'0' : hexa[i]-'a'+10;
                digit = (digit < 8) ? 15-digit : -(digit-15);

                if(digit == 15 && buffer == 1){
                    digit = 0;
                }else{
                    digit += buffer;
                    buffer = 0;
                }

                hexa[i] = (digit >= 0 && digit <= 9) ? digit+'0' : digit+'a'-10;
            }
        }
    }

    hexa[sz++] = 'x';
    hexa[sz++] = '0';

    for(int i = 0 ; i < sz/2 ; i++){
        char temp = hexa[i];
        hexa[i] = hexa[sz-i-1];
        hexa[sz-i-1] = temp;
    }

    hexa[sz++] = '\n';
    
    write(STDOUT_FD, hexa,sz);

    return sz;
}

void endian_swap(char hexa[],int size){
    char swap[40];
    int sz = 0;

    for(int i = size-3 ; i > 1; i-=2){
        swap[sz++] = hexa[i];
        swap[sz++] = hexa[i+1];
    }

    if(size%2 == 0){
        swap[sz++] = '0';
        swap[sz++] = hexa[2];
    }

    while(sz < 8)swap[sz++] = '0';

    unsigned int number = 0;
    int isNegative = (swap[0] >= '8') ? 1 : 0;
    
    for(int i = 0 ; i < sz ; i++){
        number = number * 16;
        int digit = (swap[i] >= '0' && swap[i] <= '9') ? swap[i]-'0' : swap[i]-'a'+10;
        number += digit;
    }

    decimal_print(number,0);
}

int main()
{
    char str[40];
    int n = read(STDIN_FD, str, 40);
    char hexa[40];
    int sz = 0;

    int isNegative = 0;
    unsigned int number = to_int(str,n,&isNegative);

    binary_print(number,isNegative);
    decimal_print(number,isNegative);
    sz = hexa_print(number,isNegative,hexa);
    endian_swap(hexa,sz);

    return 0;
}

void _start()
{
  int ret_code = main();
  exit(ret_code);
}