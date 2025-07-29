int sumDigits(int num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int addDigitsNormal(int num) {
    int sum = sumDigits(num);
    while (sum % 10 != sum) {
        sum = sumDigits(sum);
    }
    return sum;
}

/* Digital Root */
int addDigits(int num) {
    if (num == 0)
        return 0;
    return 1 + (num - 1) % 9;
}
