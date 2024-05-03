#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <node_api.h>

const int ALPHABET_SYMBOLS_LEN = 26;
const int ALPHABET_SYMBOL_CODES_LEN = 97;
const int NUMBER_SHIFT = 3;
const int NUMBER_BASE_KEY = 'A';

int encryptFile(FILE *inputFile, FILE *outputFile, string key);
int decryptFile(FILE *inputFile, FILE *outputFile, string key);

char digit_to_char[] = {'g', 'R', 'n', 'i', 'a', 'b', 'c', 'd', 'e', 'f'};
int char_to_digit[128];

int app(string key, string modificator)
{
    if (strcmp(modificator, "--encrypt") != 0 && strcmp(modificator, "--decrypt") != 0)
    {
        printf("Modificator must be either --encrypt or --decrypt\n");
        return 1;
    }

    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

    if (strcmp(modificator, "--encrypt") == 0)
    {
        FILE *inputFile = fopen("env.json", "r");
        if (inputFile == NULL)
        {
            perror("Opening input file error");
            fclose(inputFile);
            return 1;
        }

        FILE *outputFile = fopen("env.enc.json", "w");
        if (outputFile == NULL)
        {
            perror("Opening output file error");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        if (encryptFile(inputFile, outputFile, key) != 0)
        {
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        fclose(inputFile);
        fclose(outputFile);
    }
    else
    {
        FILE *inputFile = fopen("env.enc.json", "r");
        if (inputFile == NULL)
        {
            perror("Opening input file error");
            fclose(inputFile);
            return 1;
        }

        FILE *outputFile = fopen("env.json", "w");
        if (outputFile == NULL)
        {
            perror("Opening output file error");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        if (decryptFile(inputFile, outputFile, key) != 0)
        {
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }

        fclose(inputFile);
        fclose(outputFile);
    }

    return 0;
}

int encryptFile(FILE *inputFile, FILE *outputFile, string key)
{
    char line[256];
    while (fgets(line, sizeof(line), inputFile))
    {
        for (int i = 0, j = 0, n = strlen(line), k = strlen(key); i < n; i++)
        {
            char pi = line[i];
            int kj = tolower(key[j]) - ALPHABET_SYMBOL_CODES_LEN;
            if (isalpha(pi))
            {
                char a = isupper(pi) ? 'A' : 'a';
                int code = pi - a;
                char ci = (code + kj) % ALPHABET_SYMBOLS_LEN + a;
                fprintf(outputFile, "%c", ci);
                j = (j + 1) % k;
            }
            else
            {
                fprintf(outputFile, "%c", pi);
            }
        }
    }

    return 0;
}

int decryptFile(FILE *inputFile, FILE *outputFile, string key)
{
    char line[256];
    while (fgets(line, sizeof(line), inputFile))
    {
        for (int i = 0, j = 0, n = strlen(line), k = strlen(key); i < n; i++)
        {
            char pi = line[i];
            int kj = tolower(key[j]) - ALPHABET_SYMBOL_CODES_LEN;
            if (isalpha(pi))
            {
                char a = isupper(pi) ? 'A' : 'a';
                int code = pi - a;
                char ci = (code - kj + ALPHABET_SYMBOLS_LEN) % ALPHABET_SYMBOLS_LEN + a;
                fprintf(outputFile, "%c", ci);
                j = (j + 1) % k;
            }
            else
            {
                fprintf(outputFile, "%c", pi);
            }
        }
    }

    return 0;
}

napi_value Main(napi_env env, napi_callback_info info)
{
    size_t argc = 3;
    napi_value args[3];
    napi_status status;

    status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
    if (status != napi_ok || argc != 2)
    {
        napi_throw_error(env, NULL, "Usage: <key> <modificator>\n");
        return NULL;
    }

    size_t key_len, mod_len;
    char key[1024], mod[1024];

    status = napi_get_value_string_utf8(env, args[0], key, sizeof(key), &key_len);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Invalid key");
        return NULL;
    }

    status = napi_get_value_string_utf8(env, args[1], mod, sizeof(mod), &mod_len);
    if (status != napi_ok)
    {
        napi_throw_error(env, NULL, "Invalid modificator");
        return NULL;
    }

    app(key, mod);
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_value fn;
    napi_create_function(env, NULL, 0, Main, NULL, &fn);
    napi_set_named_property(env, exports, "vigenereEncryption", fn);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)