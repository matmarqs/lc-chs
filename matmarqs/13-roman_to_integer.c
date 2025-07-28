int romanToInt(char* s) {
    int sum = 0;
    for (; *s != '\0'; s++) {
        switch (*s) {
            case 'M':
                sum += 1000;
                break;
            case 'D':
                sum += 500;
                break;
            case 'C':
                if (*(s+1) == 'D' || *(s+1) == 'M') {
                    sum -= 100;
                }
                else {
                    sum += 100;
                }
                break;
            case 'L':
                sum += 50;
                break;
            case 'X':
                if (*(s+1) == 'L' || *(s+1) == 'C') {
                    sum -= 10;
                }
                else {
                    sum += 10;
                }
                break;
            case 'V':
                sum += 5;
                break;
            case 'I':
                if (*(s+1) == 'V' || *(s+1) == 'X') {
                    sum -= 1;
                }
                else {
                    sum += 1;
                }
                break;
        }
    }
    return sum;
}


/*
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/
