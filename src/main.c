// Copyright (c) 2018-2019 Roland Bernard

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./program.h"
#include "./environment.h"
#include "./error.h"
#include "./langallocator.h"
#include "./string.h"
#include "./bool.h"
#include "./object.h"

#define LINE_BUFFER_SIZE 4096
#define HISTORY_BUFFER_SIZE 20

static bool_t error_flag = false;

void error_handler(const char* msg) {
    if(!empty_line) {
        fprintf(stdout, "\n");
        empty_line = true;
    }
    fprintf(stderr, "Error: %s\n", msg);
    error_flag = true;
}

void silent_error_handler(const char* msg) {
    error_flag = true;
}

int main(int argc, char** argv) {
    // Initialize error
    set_stack_start(&argc);
    set_error_handler(error_handler);

    // Initialize rand
    srand(time(NULL) + clock());

    // Create environment
    environment_t* env = environment_create();
    char* buffer;
    program_t* program;
    size_t file_size;
    error_flag = false;

    if (argc == 1) {
        while (1) {
            fprintf(stderr, ">>> ");
            string_t* input = string_create("");
            bool_t ready = false;

            do {
                error_flag = false;
                char line_buffer[LINE_BUFFER_SIZE];
                int buffer_index = 0;

                do {
                    int ch = getc(stdin);
                    if(ch == -1) {
                        string_free(input);
                        goto end;
                    }

                    line_buffer[buffer_index] = ch;
                    buffer_index++;
                } while (line_buffer[buffer_index-1] != '\n' && buffer_index < LINE_BUFFER_SIZE);

                string_t* tmp1 = string_create_full(line_buffer, buffer_index);
                string_t* tmp2 = string_concat(input, tmp1);
                string_free(input);
                string_free(tmp1);
                input = tmp2;

                set_error_handler(silent_error_handler);
                program = tokenize_and_parse_program(string_get_cstr(input));

                if(!error_flag) {
                    ready = true;
                }
                if(line_buffer[0] == '\n') {
                    ready = true;
                    set_error_handler(error_handler);
                    program = tokenize_and_parse_program(string_get_cstr(input));
                }
            } while (!ready);

            if(program != NULL) {
                set_error_handler(error_handler);
                object_t** ret = program_result(program, env);
                fflush(stdout);
                if (!empty_line) {
                    fprintf(stdout, "\n");
                    empty_line = true;
                }
                if(ret != NULL && ret != RET_ERROR && ret[0] != NULL) {
                    fprintf(stdout, "\e[36m");
                    for(int i = 0; ret[i] != NULL; i++) {
                        print_object(ret[i]);
                        if(ret[i+1] != NULL) {
                            fprintf(stdout, ", ");
                        }
                        object_dereference(ret[i]);
                    }
                    fprintf(stdout, "\e[m\n");
                    fflush(stdout);
                    empty_line = true;
                }
                _free(ret);
                program_free(program);
            }
            string_free(input);
        }
        
    end:
        fprintf(stdout, "\n");
    } else {
        for(int i = 1; !error_flag && i < argc; i++) {
            FILE* file = fopen(argv[i], "r");
            if(file == NULL) {
                printf("Couldn't open the file \"%s\".\n", argv[i]);
                exit(1);
            }

            fseek(file, 0, SEEK_END);
            file_size = ftell(file);
            fseek(file, 0, SEEK_SET);

            buffer = (char*)_alloc(sizeof(char)*(file_size+1));
            buffer[file_size] = '\0';
            fread(buffer, 1, file_size, file);

            program = tokenize_and_parse_program(buffer);
            program_exec(program, env);
            program_free(program);

            _free(buffer);
            fclose(file);
        }
    }
    environment_free(env);

    return error_flag;
}
