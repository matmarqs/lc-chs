char* decodeMessage(char* key, char* message) {
    char table[26] = { 0 };
    char letter = 'a';
    for (; *key != '\0'; key++) {
        if ('a' <= *key && *key <= 'z') {
            int c = *key - 'a';
            if (!table[c]) {
                table[c] = letter++;
            }
        }
    }

    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] != ' ') {
            message[i] = table[message[i] - 'a'];
        }
    }

    return message;
}
