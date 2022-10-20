#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shorthand.h"

typedef enum {
    ELEM_U8, ELEM_S8, ELEM_U16, ELEM_S16,
    ELEM_U32, ELEM_S32, ELEM_U64, ELEM_S64,
} ElemSize;

void
write_array(FILE *file_in, FILE *file_out, char *arr_name, ElemSize elem_size) {
    char *arr_type;
    size_t n_elem = 0;
    switch (elem_size) {
        case ELEM_U8:
            arr_type = "u8";
            n_elem = 8;
            break;
        case ELEM_S8:
            arr_type = "s8";
            n_elem = 8;
            break;
        case ELEM_U16:
            arr_type = "u16";
            n_elem = 8;
            break;
        case ELEM_S16:
            arr_type = "s16";
            n_elem = 8;
            break;
        case ELEM_U32:
            arr_type = "u32";
            n_elem = 4;
            break;
        case ELEM_S32:
            arr_type = "s32";
            n_elem = 4;
            break;
        case ELEM_U64:
            arr_type = "u64";
            n_elem = 4;
            break;
        case ELEM_S64:
            arr_type = "s64";
            n_elem = 4;
            break;
        default:
            arr_type = "u8";
            n_elem = 8;
            break;
    }
    fprintf(file_out, "const %s %s[] = {\n", arr_type, arr_name);
    size_t n_read = 0;
    size_t counter = 0;
    do {
        if (counter == 0) {
            fprintf(file_out, "    ");
        }
        switch (elem_size) {
            case ELEM_U8:
            case ELEM_S8: {
                u8 elem;
                n_read = fread(&elem, sizeof(u8), 1, file_in);
                fprintf(file_out, "0x%02x,", elem);
                break;
            }
            case ELEM_U16:
            case ELEM_S16: {
                u16 elem;
                n_read = fread(&elem, sizeof(u16), 1, file_in);
                fprintf(file_out, "0x%04x,", elem);
                break;
            }
            case ELEM_U32:
            case ELEM_S32: {
                u32 elem;
                n_read = fread(&elem, sizeof(u32), 1, file_in);
                fprintf(file_out, "0x%08x,", elem);
                break;
            }
            case ELEM_U64:
            case ELEM_S64: {
                u64 elem;
                n_read = fread(&elem, sizeof(u64), 1, file_in);
                fprintf(file_out, "0x%016lx,", elem);
                break;
            }
        }

        if (counter == n_elem - 1) {
            fprintf(file_out, "\n");
            counter = 0;
        } else {
            fprintf(file_out, " ");
            counter++;
        }
    } while(n_read != 0);
    if (counter != 0) {
        fseek(file_out, -1, SEEK_CUR);
        fprintf(file_out, "\n");
    }
    fprintf(file_out, "};\n");
}

void
print_usage(void) {
    printf("Usage: %s [options] <filename>\n", BIN_NAME);
    printf("\n");
    printf("\t-e <u16>\tSize of array elements.\n");
    printf("\t-n <arr_name>\tName of the output array.\n");
    printf("\t-o <out_file.c>\tPath to the output file. If blank, stdout will be used.\n");
    printf("\n");
}

int
main(int argc, char *argv[]) {
    // Initialize default parameters.
    char *in_file_path = NULL;
    char *out_file_path = NULL;
    char arr_name[256] = {0};
    ElemSize elem_size = ELEM_U8;

    // Process options.
    int option;
    while ((option = getopt(argc, argv, "e:n:o:")) != -1) {
        switch (option) {
            case 'e': {
                // Element size.
                char *size = optarg;
                if (strcmp(size, "u8") == 0) {
                    elem_size = ELEM_U8;
                } else if (strcmp(size, "s8") == 0) {
                    elem_size = ELEM_S8;
                } else if (strcmp(size, "u16") == 0) {
                    elem_size = ELEM_U16;
                } else if (strcmp(size, "s16") == 0) {
                    elem_size = ELEM_S16;
                } else if (strcmp(size, "u32") == 0) {
                    elem_size = ELEM_U32;
                } else if (strcmp(size, "s32") == 0) {
                    elem_size = ELEM_S32;
                } else if (strcmp(size, "u64") == 0) {
                    elem_size = ELEM_U64;
                } else if (strcmp(size, "s64") == 0) {
                    elem_size = ELEM_S64;
                }
            } break;
            case 'n': {
                // Array name.
                char *ptr = optarg;
                size_t k = 0;
                while(*ptr) {
                    switch (*ptr) {
                        case '.':
                        case '/':
                        case '-':
                        case '\\':
                            ptr++;
                            break;
                        default: {
                            arr_name[k++] = *ptr++;
                        } break;
                    }
                }
            } break;
            case 'o': {
                // Output file.
                out_file_path = optarg;
            } break;
            default: {
                print_usage();
                return EXIT_FAILURE;
            } break;
        }
    }

    // Get the path to the file to be exported.
    if (optind != argc - 1) {
        fprintf(stderr, "%s: No input file given.\n", BIN_NAME);
        print_usage();
        return EXIT_FAILURE;
    }
    in_file_path = argv[optind];

    // Check if there is a default array name.
    if (arr_name[0] == '\0') {
        char *ptr = in_file_path;
        size_t k = 0;
        while(*ptr) {
            switch (*ptr) {
                case '.':
                case '/':
                case '-':
                case '\\':
                    ptr++;
                    break;
                default: {
                    arr_name[k++] = *ptr++;
                } break;
            }
        }
    }

    // Try to open input file.
    FILE *file_in = fopen(in_file_path, "r");
    if (file_in == NULL) {
        fprintf(stderr, "%s: can't open input file: %s\n", BIN_NAME,
        in_file_path);
        return EXIT_FAILURE;
    }

    // Write output to file.
    if (out_file_path == NULL) {
        write_array(file_in, stdout, arr_name, elem_size);
    } else {
        FILE *file_out = fopen(out_file_path, "w");
        if (!file_out) {
            fprintf(stderr, "%s: can't open output file: %s\n", BIN_NAME, out_file_path);
            fclose(file_in);
            return EXIT_FAILURE;
        }
        write_array(file_in, file_out, arr_name, elem_size);
        fclose(file_out);
    }

    // Cleanup.
    fclose(file_in);
    return EXIT_SUCCESS;
}
