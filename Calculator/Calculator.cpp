#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main()
{
    char v[20];
    int sign, n, i,nr,c;
    float result,aux;
    while (1)
    {
        cout << "insert the expression:" << endl;
        scanf("%s", v);
        n = strlen(v);
        result = 0, nr = 0, aux = 0, c = 0;
        sign = 1, n, i = 0;
        while (i<n)//loops only once through the array
        {
            while (v[i] >= '0'&&v[i] <= '9')//builds the number
            {
                nr = nr * 10 + (v[i] - '0');
                i++;
            }
            switch (v[i])//identifies the operations
            {
            case '+': {

                if (!(v[i - 1] == '*') && !(v[i - 1] == '/'))//if a*-b or a/-b occurs it does nothing
                {
                    if (c == 1)// * was found before: 2*2+1
                    {
                        result += aux*nr*sign;// updates the end result
                        aux = 0;//aux is reseted
                    }
                    else if (c == 2)// / was found before: 2/2+1
                    {
                        if(nr==0){ // 2/0
                            goto ERROR;
                        }
                        result += aux / nr*sign;
                        aux = 0;
                    }
                    else// there is no * or / befor +
                    {
                        result += nr*sign;
                    }
                    nr = 0;
                    c = 0;
                }

                sign = 1;

                break;
            }
            case '-': {
                if (!(v[i - 1] == '*') && !(v[i - 1] == '/')) //if a*-b or a/-b occurs it does nothing
                {
                    if (c == 1)// * was found before: 2*2-1
                    {
                        result += aux*nr*sign;// updates the end result
                        aux = 0;//aux is reseted
                    }
                    else if (c == 2)// / was found before: 2/2/1
                    {
                        if(nr==0){
                            goto ERROR;
                        }
                        result += aux / nr*sign;
                        aux = 0;
                    }
                    else // there is no * or / befor -
                    {
                        result += nr*sign;
                    }
                    c = 0;
                    nr = 0;
                }
                sign = -1;
                break;
            }
            case '*': {
                if (!aux)//aux==0
                {
                    aux = nr*sign; // aux hold the result from * and / operations
                }
                else if (c == 2)
                {
                    if(nr==0){
                        goto ERROR;
                    }
                    aux /= nr*sign;
                }
                else
                {
                    aux *= nr*sign;
                }
                c = 1;
                nr = 0;
                sign = 1;
                break;
            }
            case '/': {
                if (!aux)
                {
                    aux = nr * sign;
                }
                else if (c == 1)
                {
                    aux *= nr*sign;
                }
                else
                {
                    if(nr==0){
                        goto ERROR;
                    }
                    aux /= nr*sign;
                }
                c = 2;
                nr = 0;
                sign = 1;
                break;
            }
            case '!': {
                for(int k = nr - 1 ; k>=1 ; k--){ // nr = 4, for loop will start from 3
                    nr=nr*k; // nr = 4*3*...
                }
                break;
            }
            case '^': {
                i++;// to get the power (2^3) -> 3
                int m = v[i] - '0'; //convert from char to int
                m--;// (2^3) -> we should mul 2 in another two 2 -> 2* (2*2)
                int k = nr;
                while(m--){
                    nr = nr *k;//first itration : nr = 2*2 -> nr=4, second itration : nr = 4*2 -> nr=8 
                }
                break;
            }
            
            default:;
            }
            if (i >= (n - 1))// updates the result because there is no + or - at the end of the string.
            {
                if (c == 1)
                {
                    result += aux*nr*sign;
                }
                else if (c == 2)
                {
                    if(nr==0){
                        goto ERROR;
                    }
                    result += aux / nr*sign;
                }
                else
                {
                    result += nr*sign;
                }
            }
            i++;
        }
        cout << "=" << result << endl;
        ERROR :cout << "ERROR" << endl;

    }

}
