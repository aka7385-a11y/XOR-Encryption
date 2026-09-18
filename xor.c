#include <stdio.h>
#include <string.h>

#define MAX_KEY_LENGTH 100

void xor_encrypt_decrypt(char *data, const char *key) {
    int key_len = strlen(key);
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] ^= key[i % key_len];
    }
}

int main() {
    char choice[10];
    printf("Enter 'encrypt' or 'decrypt': ");
    scanf("%s", choice);

    if (strcmp(choice, "encrypt") == 0) {
        char message[MAX_KEY_LENGTH];
        char filename[MAX_KEY_LENGTH];
        char key[MAX_KEY_LENGTH];

        printf("Enter the string to encrypt: ");
        fgets(message, MAX_KEY_LENGTH, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline

        printf("Enter the filename to save encrypted data: ");
        scanf("%s", filename);

        printf("Enter the key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        xor_encrypt_decrypt(message, key);
        fprintf(file, "%s", message);
        fclose(file);
    } else if (strcmp(choice, "decrypt") == 0) {
        char filename[MAX_KEY_LENGTH];
        char key[MAX_KEY_LENGTH];

        printf("Enter the filename to read encrypted data: ");
        scanf("%s", filename);

        printf("Enter the key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *encrypted_data = malloc(size + 1);
        if (encrypted_data == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return 1;
        }

        fread(encrypted_data, sizeof(char), size, file);
        encrypted_data[size] = '\0';
        fclose(file);

        xor_encrypt_decrypt(encrypted_data, key);
        printf("Decrypted data: %s\n", encrypted_data);

        free(encrypted_data);
    } else {
        printf("Invalid choice. Please enter 'encrypt' or 'decrypt'.\n");
    }

    return 0;
}