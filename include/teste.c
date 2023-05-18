#include <string.h>

void main () {
        int d1 = 1;
        int d2 = 3;
        char c1 = (char) ('0' + d1);
        char c2 = (char) ('0' + d2);
        char s[24] = "You picked up ";
        s[14] = '0' + d1;
        s[15] = '0' + d2;
        s[16] = ' ';
        s[17] = 'g';
        s[18] = 'o';
        s[19] = 'l';
        s[20] = 'd';
        s[21] = '.';
    }