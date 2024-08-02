#include <stdint.h>
#include "libc/string.h"


void strcat(char *first_string, char *second_string) {

    uint16_t len_strings = strlen(first_string);
    uint16_t len_second_strings = strlen(second_string);

    for (uint16_t i = len_strings; i < len_strings + len_second_strings; i++) {
        first_string[i] = second_string[i];
    }
}

void chareplace(char *string, char character, char character_to_replace) {

    for (uint16_t i = 0; i < strlen(string); i++) {
        if (string[i] == character) {
            string[i] = character_to_replace;
        }
    }
}

void strcpy(char *source, char *destination) {

    for (uint16_t i = 0; i < strlen(source); i++) {
        destination[i] = source[i];
    }
}

uint16_t strcmp(const char *first_string, const char *second_string) {
    
    uint16_t result = 0;
    uint16_t len_first_string = strlen(first_string), len_second_string = strlen(second_string), len = 0;

    if (len_first_string > len_second_string) {
        len = len_first_string;
    } else {
        len = len_second_string;
    }

    for (uint16_t i = 0; i < len; i++) {
        if (first_string[i] != second_string[i]) {
            result++;
            break;
        }
    }

    return result;
}

uint16_t strchr(char *string, char *research) {

    uint16_t string_len = strlen(string);
    uint16_t research_len = strlen(research);
    uint16_t result = 0;

    for (uint16_t i = 0; i < string_len; i++) {
        for (uint16_t j = 0; j < research_len; j++) {
            if (string[i] == research[j]) {
                result++;
            }
        }
    }

    if (result == research_len) {
        return 1;
    } else {
        return 0;
    }
}

uint16_t strlen(const char *string) {
    uint16_t len = 0;
    while (string[len]) {
        len++;
    }

    return len;
}