#include "show_binary.h"

void ShowCharInBinary(char mask)
    {
    unsigned temp = mask;
    int s[8] = {};
    for(int i = 0; i < 8; i++)
        {
        s[i] = temp % 2;
        temp /= 2;
        //printf ("%d", s[i]);
        }

    for (int i =0; i<8;i++)
        printf("%d", s[7-i]);
    
    printf("\n");
    }