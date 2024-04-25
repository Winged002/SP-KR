#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>


wchar_t *apply_rule1(const wchar_t *text) {
    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len; ++i) {
        wchar_t current_char = text[i];
        wchar_t next_char = (i + 1 < text_len) ? text[i + 1] : L'\0';

        if (current_char == L' ' && next_char == L'.' &&
            (i + 2 < text_len) && text[i + 2] == L'.' &&
            (i + 3 < text_len) && text[i + 3] == L'.') {
            // Skip the space before "..."
            continue;
        }

        output[output_len++] = current_char;
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    //free(output);

    return output;
}

wchar_t *apply_rule2(const wchar_t *text) {
    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;
    int dot_count = 0;

    for (size_t i = 0; i < text_len; ++i) {
        wchar_t current_char = text[i];

        if (current_char == L'.') {
            dot_count++;

            if (dot_count <= 3) {
                output[output_len++] = current_char;
            }
        } else {
            dot_count = 0;
            output[output_len++] = current_char;
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule3(const wchar_t *text) {
    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;
    bool new_line = false;

    for (size_t i = 0; i < text_len; ++i) {
        wchar_t current_char = text[i];
        wchar_t next_char = (i + 1 < text_len) ? text[i + 1] : L'\0';
        wchar_t next_next_char = (i + 2 < text_len) ? text[i + 2] : L'\0';

        if (new_line && (current_char == L' ' || current_char == L'-')) {
            // If new line and there is space or '-' after the comma, skip
            continue;
        } else if (current_char == L',' && (next_char == L' ' || next_char == L'\n') && (next_next_char == L' ' || next_next_char == L'-')) {
            // If there is comma followed by space or new line and then space or '-', append comma and '-' to output
            output[output_len++] = current_char;
            output[output_len++] = L'-';
            new_line = false;
        } else {
            output[output_len++] = current_char;
            new_line = current_char == L'\n';
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    //free(output);

    return output;
}

wchar_t *apply_rule4(const wchar_t *text) {
    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;
    bool last_was_punctuation = false;

    for (size_t i = 0; i < text_len; ++i) {
        wchar_t current_char = text[i];
        bool is_punctuation = wcschr(L",:.!?", current_char) != NULL;

        if (last_was_punctuation && (current_char == L' ' || is_punctuation)) {
            // If the last character was punctuation and the current character is space or punctuation, skip
            continue;
        } else {
            output[output_len++] = current_char;
            last_was_punctuation = is_punctuation;
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule5(const wchar_t *text) {
    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;
    bool last_was_space = false;

    for (size_t i = 0; i < text_len; ++i) {
        wchar_t current_char = text[i];
        bool is_punctuation = wcschr(L",:.!?", current_char) != NULL;

        if (last_was_space && is_punctuation) {
            // If the last character was a space and the current character is punctuation, remove the space
            output_len--;
        }

        output[output_len++] = current_char;
        last_was_space = current_char == L' ';
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule6(const wchar_t *text) {
    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;
    bool last_was_punctuation = false;
    bool last_was_comma = false;

    for (size_t i = 0; i < text_len; ++i) {
        wchar_t current_char = text[i];
        bool is_punctuation = wcschr(L",:.!?", current_char) != NULL;
        bool is_comma = current_char == L',';

        if ((last_was_punctuation || last_was_comma) && (is_punctuation || is_comma || current_char == L' ')) {
            // If the last character was punctuation or a comma and the current character is punctuation, a comma, or space, skip
            continue;
        } else {
            output[output_len++] = current_char;
            last_was_punctuation = is_punctuation;
            last_was_comma = is_comma;
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule7(const wchar_t *text) {
    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len * 2 + 1) * sizeof(wchar_t)); // Allocate extra space for potential added spaces
    size_t output_len = 0;

    for (size_t i = 0; i < text_len; ++i) {
        wchar_t current_char = text[i];
        output[output_len++] = current_char;

        if (current_char == L',' && i + 1 < text_len && text[i + 1] != L' ') {
            // If the current character is a comma and the next character is not a space, add a space
            output[output_len++] = L' ';
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule8(const wchar_t *text) {
    const wchar_t *words[] = {L"Например", L"Всъщност", L"Според мен", L"Наистина", L"Следователно", L"Действително", L"Реално", L"Практически", L"Така", L"Може би", 
    L"Значи", L"Вероятно", L"Очевидно", L"Навярно", L"По всяка вероятност", L"В действителност", L"В края на краищата"};
    size_t num_words = sizeof(words) / sizeof(words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        size_t j;
        for (j = 0; j < num_words; ++j) {
            size_t word_len = wcslen(words[j]);
            if (wcsncmp(text + i, words[j], word_len) == 0) {
                // If the current substring matches one of the words
                if (i + word_len < text_len && text[i + word_len] == L',') {
                    // If there is a comma after the word, remove it
                    wcsncpy(output + output_len, text + i, word_len);
                    output_len += word_len;
                    i += word_len + 1; // Skip the word and the comma
                } else if (i + word_len < text_len && text[i + word_len] != L' ') {
                    // If there is no space after the word, add one
                    wcsncpy(output + output_len, text + i, word_len);
                    output_len += word_len;
                    output[output_len++] = L' ';
                    i += word_len;
                } else {
                    wcsncpy(output + output_len, text + i, word_len);
                    output_len += word_len;
                    i += word_len;
                }
                break;
            }
        }

        if (j == num_words) {
            // If the current substring doesn't match any of the words, copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule9(const wchar_t *text) {
    const wchar_t *words[] = {L"Казват", L"Напротив", L"Разбира се", L"Изглежда", L"Струва ми се", L"Види се", L"Общо взето", L"Тъй да се каже", L"Между нас казано", 
    L"Както казват", L"Първо", L"Второ", L"Трето", L"Естествено"};
    size_t num_words = sizeof(words) / sizeof(words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len * 2 + 1) * sizeof(wchar_t)); // Allocate extra space for potential added commas
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        size_t j;
        for (j = 0; j < num_words; ++j) {
            size_t word_len = wcslen(words[j]);
            if (wcsncmp(text + i, words[j], word_len) == 0) {
                // If the current substring matches one of the words
                wcsncpy(output + output_len, text + i, word_len);
                output_len += word_len;
                i += word_len;

                if (i < text_len && text[i] != L',') {
                    // If there is no comma after the word, add one
                    output[output_len++] = L',';
                }
                break;
            }
        }

        if (j == num_words) {
            // If the current substring doesn't match any of the words, copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule10(const wchar_t *text) {
    const wchar_t *words[] = {L"казват", L"напротив", L"разбира се", L"изглежда", L"струва ми се", L"види се", L"общо взето", L"тъй да се каже", L"между нас казано", L"както казват"};
    size_t num_words = sizeof(words) / sizeof(words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len * 4 + 1) * sizeof(wchar_t)); // Allocate extra space for potential added commas and spaces
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        size_t j;
        int found = 0;
        for (j = 0; j < num_words; ++j) {
            size_t word_len = wcslen(words[j]);
            if (wcsncmp(text + i, words[j], word_len) == 0 && (i == 0 || text[i - 1] != L',')) {
                // If the current substring matches one of the words and there is no comma before the word
                output[output_len++] = L',';
                output[output_len++] = L' ';
                i += word_len;
                found = 1;
                break;
            }
        }
        if (!found) {
            // Copy the current character
            output[output_len++] = text[i++];
        }

        // Add a comma and space after the matching word, if needed
        for (j = 0; j < num_words; ++j) {
            size_t word_len = wcslen(words[j]);
            if (wcsncmp(text + i, words[j], word_len) == 0 && (i == text_len || text[i] != L',')) {
                output[output_len++] = L',';
                output[output_len++] = L' ';
                i += word_len;
                break;
            }
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule11(const wchar_t *text) {
    const wchar_t *words[] = {L"а", L"но", L"че", L"и", L"не", L"или", L"дори", L"само", L"именно", L"едва", L"особено", L"поне", L"тъкмо", L"под", L"много", L"малко", 
    L"даже", L"чак", L"щом", L"тъй", L"след", L"освен", L"чак", L"единствено", L"именно", L"тъкмо"};
    size_t num_words = sizeof(words) / sizeof(words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        size_t j;
        int found = 0;
        for (j = 0; j < num_words; ++j) {
            size_t word_len = wcslen(words[j]);
            if (wcsncmp(text + i, words[j], word_len) == 0 && (i == 0 || text[i - 1] != L' ')) {
                // If the current substring matches one of the words and there is no space before the word
                output[output_len++] = L' ';
                i += word_len;
                found = 1;
                break;
            }
        }
        if (!found) {
            // Copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule12(const wchar_t *text) {
    const wchar_t *first_words[] = {L"за", L"в", L"с", L"заради", L"от", L"по", L"поради", L"вследствие на", L"благодарение на"};
    const wchar_t *second_words[] = {L"който", L"която", L"което", L"които", L"чийто", L"чиято", L"чието", L"чиито"};
    size_t num_first_words = sizeof(first_words) / sizeof(first_words[0]);
    size_t num_second_words = sizeof(second_words) / sizeof(second_words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        size_t j, k;
        for (j = 0; j < num_first_words; ++j) {
            size_t first_word_len = wcslen(first_words[j]);
            if (wcsncmp(text + i, first_words[j], first_word_len) == 0) {
                // If the current substring matches one of the first_words
                wcsncpy(output + output_len, first_words[j], first_word_len);
                output_len += first_word_len;
                i += first_word_len;

                if (i < text_len && text[i] == L' ') {
                    // If there is a space after the first word, skip it
                    i++;
                }

                for (k = 0; k < num_second_words; ++k) {
                    size_t second_word_len = wcslen(second_words[k]);
                    if (wcsncmp(text + i, second_words[k], second_word_len) == 0) {
                        // If the current substring matches one of the second_words
                        output[output_len++] = L',';
                        output[output_len++] = L' ';

                        wcsncpy(output + output_len, second_words[k], second_word_len);
                        output_len += second_word_len;
                        i += second_word_len;
                        break;
                    }
                }
                break;
            }
        }

        if (j == num_first_words) {
            // If no matching word was found, copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule13(const wchar_t *text) {
    const wchar_t *first_words[] = {L"дори", L"само", L"именно", L"едва", L"особено", L"поне", L"тъкмо", L"под", L"много", L"малко", L"даже", L"чак", L"щом", L"тъй", 
    L"след", L"освен", L"чак", L"единствено", L"именно", L"тъкмо", L"не"};
    const wchar_t *second_word = L"защото";
    size_t num_first_words = sizeof(first_words) / sizeof(first_words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        size_t j;
        for (j = 0; j < num_first_words; ++j) {
            size_t first_word_len = wcslen(first_words[j]);
            if (wcsncmp(text + i, first_words[j], first_word_len) == 0) {
                // If the current substring matches one of the first_words
                wcsncpy(output + output_len, first_words[j], first_word_len);
                output_len += first_word_len;
                i += first_word_len;

                if (i < text_len && text[i] == L' ') {
                    // If there is a space after the first word, skip it
                    i++;
                }

                size_t second_word_len = wcslen(second_word);
                if (wcsncmp(text + i, second_word, second_word_len) == 0) {
                    // If the current substring matches the second_word
                    output[output_len++] = L' ';

                    wcsncpy(output + output_len, second_word, second_word_len);
                    output_len += second_word_len;
                    i += second_word_len;
                }
                break;
            }
        }

        if (j == num_first_words) {
            // If no matching word was found, copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule14(const wchar_t *text) {
    const wchar_t *starting_word = L"За съжаление";
    size_t starting_word_len = wcslen(starting_word);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        if (wcsncmp(text + i, starting_word, starting_word_len) == 0) {
            // If the current substring matches the starting_word
            wcsncpy(output + output_len, starting_word, starting_word_len);
            output_len += starting_word_len;
            i += starting_word_len;

            if (i < text_len && text[i] == L' ') {
                // If there is a space after the starting_word, skip it
                i++;
            }

            // Add a comma and a space
            output[output_len++] = L',';
            output[output_len++] = L' ';
        } else {
            // If no match is found, copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule15(const wchar_t *text) {
    const wchar_t *target_word = L"за съжаление";
    size_t target_word_len = wcslen(target_word);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 2) * sizeof(wchar_t)); // +2 for potential added comma and null terminator
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        if (wcsncmp(text + i, target_word, target_word_len) == 0) {
            bool add_comma_before = (output_len > 0 && output[output_len - 1] != L',');
            bool add_comma_after = (i + target_word_len < text_len && text[i + target_word_len] != L',');

            // Add comma before target_word if necessary
            if (add_comma_before) {
                output[output_len++] = L',';
            }

            // Copy the target_word
            wcsncpy(output + output_len, target_word, target_word_len);
            output_len += target_word_len;
            i += target_word_len;

            // Add comma after target_word if necessary
            if (add_comma_after) {
                output[output_len++] = L',';
            }
        } else {
            // If no match is found, copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

bool is_first_word(const wchar_t *word, const wchar_t *text) {
    size_t word_len = wcslen(word);
    return wcsncmp(text, word, word_len) == 0 && (text[word_len] == L' ' || text[word_len] == L'\0');
}

wchar_t *apply_rule16(const wchar_t *text) {
    const wchar_t *first_words[] = {L"само", L"дори", L"едва", L"чак", L"даже", L"единствено", L"именно", L"тъкмо", L"много", L"малко", L"не", L"и", L"макар", L"въпреки", 
    L"така", L"само", L"при положение", L"в случай", L"по причина", L"при условие", L"при все", L"сякаш", L"освен", L"независимо", L"Въпреки", L"Така", L"Само", 
    L"При положение че", L"Макар", L"В случай че", L"При условие", L"При все", L"Освен", L"Независимо"};
    size_t first_words_count = sizeof(first_words) / sizeof(first_words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        bool matched_first_word = false;
        for (size_t j = 0; j < first_words_count; j++) {
            if (is_first_word(first_words[j], text + i)) {
                // If the current substring matches one of the first_words
                size_t first_word_len = wcslen(first_words[j]);
                wcsncpy(output + output_len, first_words[j], first_word_len);
                output_len += first_word_len;
                i += first_word_len;

                // Skip spaces and comma if present
                while (i < text_len && (text[i] == L' ' || text[i] == L',')) {
                    i++;
                }

                // Add a space
                output[output_len++] = L' ';

                matched_first_word = true;
                break;
            }
        }

        if (!matched_first_word) {
            // If no match is found, copy the current character
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

bool starts_with(const wchar_t *word, const wchar_t *text) {
    size_t word_len = wcslen(word);
    return wcsncmp(text, word, word_len) == 0;
}

wchar_t *apply_rule17(const wchar_t *text) {
    const wchar_t *first_word = L"че";
    const wchar_t *second_words[] = {L"за да"};
    size_t second_words_count = sizeof(second_words) / sizeof(second_words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        if (starts_with(first_word, text + i)) {
            size_t first_word_len = wcslen(first_word);
            wcsncpy(output + output_len, first_word, first_word_len);
            output_len += first_word_len;
            i += first_word_len;

            // Skip spaces and comma if present
            while (i < text_len && (text[i] == L' ' || text[i] == L',')) {
                i++;
            }

            bool matched_second_word = false;
            for (size_t j = 0; j < second_words_count; j++) {
                if (starts_with(second_words[j], text + i)) {
                    size_t second_word_len = wcslen(second_words[j]);
                    wcsncpy(output + output_len, second_words[j], second_word_len);
                    output_len += second_word_len;
                    i += second_word_len;

                    // Add a space
                    output[output_len++] = L' ';
                    matched_second_word = true;
                    break;
                }
            }

            if (!matched_second_word) {
                output[output_len++] = text[i++];
            }
        } else {
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule18(const wchar_t *text) {
    const wchar_t *first_words[] = {L"щом", L"тъй", L"след", L"освен"};
    size_t first_words_count = sizeof(first_words) / sizeof(first_words[0]);
    const wchar_t *second_word = L"като";

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        bool matched_first_word = false;
        for (size_t j = 0; j < first_words_count; j++) {
            if (starts_with(first_words[j], text + i)) {
                size_t first_word_len = wcslen(first_words[j]);
                wcsncpy(output + output_len, first_words[j], first_word_len);
                output_len += first_word_len;
                i += first_word_len;

                // Skip spaces if present
                while (i < text_len && text[i] == L' ') {
                    i++;
                }

                if (starts_with(second_word, text + i)) {
                    // Add a comma and a space
                    output[output_len++] = L',';
                    output[output_len++] = L' ';
                }
                matched_first_word = true;
                break;
            }
        }

        if (!matched_first_word) {
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule19(const wchar_t *text) {
    const wchar_t *words[] = {L"както следва", L"вместо да", L"за разлика от"};
    size_t words_count = sizeof(words) / sizeof(words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        bool matched_word = false;
        for (size_t j = 0; j < words_count; j++) {
            if (starts_with(words[j], text + i)) {
                size_t word_len = wcslen(words[j]);
                wcsncpy(output + output_len, words[j], word_len);
                output_len += word_len;
                i += word_len;

                // Skip spaces if present
                while (i < text_len && text[i] == L' ') {
                    i++;
                }

                // Add a comma before the next word
                output[output_len++] = L',';
                output[output_len++] = L' ';

                matched_word = true;
                break;
            }
        }

        if (!matched_word) {
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule20(const wchar_t *text) {
    const wchar_t *words[] = {L"както следва", L"вместо да", L"за разлика от"};
    const wchar_t *target_word = L"естествено";
    size_t words_count = sizeof(words) / sizeof(words[0]);

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        bool matched_word = false;
        for (size_t j = 0; j < words_count; j++) {
            if (starts_with(words[j], text + i)) {
                size_t word_len = wcslen(words[j]);
                wcsncpy(output + output_len, words[j], word_len);
                output_len += word_len;
                i += word_len;

                // Skip spaces and commas if present
                while (i < text_len && (text[i] == L' ' || text[i] == L',')) {
                    i++;
                }

                // Check if the target word follows the matched word
                if (starts_with(target_word, text + i)) {
                    size_t target_word_len = wcslen(target_word);
                    wcsncpy(output + output_len, target_word, target_word_len);
                    output_len += target_word_len;
                    i += target_word_len;
                }

                // Add a single space
                output[output_len++] = L' ';

                matched_word = true;
                break;
            }
        }

        if (!matched_word) {
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule21(const wchar_t *text) {
    const wchar_t *target_word = L"в";
    const wchar_t *replacement_word = L"във";
    const wchar_t *following_letters = L"вф";

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        if (starts_with(target_word, text + i) &&
            i + 1 < text_len &&
            wcschr(following_letters, text[i + 1]) != NULL) {

            size_t replacement_len = wcslen(replacement_word);
            wcsncpy(output + output_len, replacement_word, replacement_len);
            output_len += replacement_len;
            i += wcslen(target_word);
        } else {
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);

    return output;
}

wchar_t *apply_rule22(const wchar_t *text) {
    const wchar_t *target_word = L"с";
    const wchar_t *replacement_word = L"със";
    const wchar_t *following_letters = L"сз";

    size_t text_len = wcslen(text);
    wchar_t *output = malloc((text_len + 1) * sizeof(wchar_t));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        if (starts_with(target_word, text + i) &&
            i + 1 < text_len &&
            wcschr(following_letters, text[i + 1]) != NULL) {

            size_t replacement_len = wcslen(replacement_word);
            wcsncpy(output + output_len, replacement_word, replacement_len);
            output_len += replacement_len;
            i += wcslen(target_word);
        } else {
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';
    free(output);
    return output;
}

wchar_t *apply_rule23(const wchar_t *text) {
    const wchar_t *target_words[] = {
        L"а", L"ала", L"но", L"макар и", L"ако и", L"та", L"ама", L"пък", L"що", L"дето",
        L"обаче", L"ами", L"защото", L"отколкото", L"без да", L"докато", L"като"
    };
    size_t target_words_count = sizeof(target_words) / sizeof(target_words[0]);

    size_t text_len = wcslen(text);
    // Allocate more memory to accommodate added commas and the null-terminating character
    wchar_t *output = malloc((text_len * 2 + 1) * sizeof(text[0]));
    size_t output_len = 0;

    for (size_t i = 0; i < text_len;) {
        size_t matched_word_len = 0;

        for (size_t j = 0; j < target_words_count; j++) {
            if (starts_with(target_words[j], text + i)) {
                matched_word_len = wcslen(target_words[j]);
                break;
            }
        }

        if (matched_word_len > 0 && i + matched_word_len < text_len && text[i + matched_word_len] != L',') {
            output[output_len++] = text[i++];
            output[output_len++] = L',';
            while (i < text_len && iswspace(text[i])) {
                i++;
            }
        } else {
            output[output_len++] = text[i++];
        }
    }

    // Null-terminate the output string
    output[output_len] = L'\0';

    free(output);
    return output;
}

// Function to correct the text based on the given rules
wchar_t *correct_text(const wchar_t *input_text) {
    size_t input_len = wcslen(input_text);
    wchar_t *corrected_text = malloc((input_len + 1) * sizeof(wchar_t));
    wcscpy(corrected_text, input_text);

    apply_rule1(corrected_text);
    apply_rule2(corrected_text);
    apply_rule3(corrected_text);
    apply_rule4(corrected_text);
    apply_rule5(corrected_text);
    apply_rule6(corrected_text);
    apply_rule7(corrected_text);
    apply_rule8(corrected_text);
    apply_rule9(corrected_text);
    apply_rule10(corrected_text);
    apply_rule11(corrected_text);
    apply_rule12(corrected_text);
    apply_rule13(corrected_text);
    apply_rule14(corrected_text);
    apply_rule15(corrected_text);
    apply_rule16(corrected_text);
    apply_rule17(corrected_text);
    apply_rule18(corrected_text);
    apply_rule19(corrected_text);
    apply_rule20(corrected_text);
    apply_rule21(corrected_text);
    apply_rule22(corrected_text);
    apply_rule23(corrected_text);

    return corrected_text;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    // Set the locale to support wide characters
    setlocale(LC_ALL, "");

    // Read the input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Read the input file into a wide string
    fseek(input_file, 0, SEEK_END);
    long input_file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    char *input_file_contents = malloc(input_file_size + 1);
    fread(input_file_contents, 1, input_file_size, input_file);
    fclose(input_file);
    input_file_contents[input_file_size] = '\0';

    // Convert the input file contents to a wide string
    size_t input_wide_len = mbstowcs(NULL, input_file_contents, 0) + 1;
    wchar_t *input_wide = malloc(input_wide_len * sizeof(wchar_t));
    mbstowcs(input_wide, input_file_contents, input_wide_len);
    free(input_file_contents);

    // Correct the text
    wchar_t *corrected_text = correct_text(input_wide);
    free(input_wide);

    // Convert the corrected text to a multibyte string
    size_t corrected_text_mb_len = wcstombs(NULL, corrected_text, 0) + 1;
    char *corrected_text_mb = malloc(corrected_text_mb_len * sizeof(char));
    wcstombs(corrected_text_mb, corrected_text, corrected_text_mb_len);
    free(corrected_text);

    // Write the corrected text to the output file
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        free(corrected_text_mb);
        return 1;
    }

    fwrite(corrected_text_mb, 1, strlen(corrected_text_mb), output_file);
    fclose(output_file);
    free(corrected_text_mb);

    return 0;
}


