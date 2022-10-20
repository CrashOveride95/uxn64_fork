#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "types.h"
#include "bootdata.c"

#define CHECKSUM_START  0x00001000
#define CHECKSUM_LENGTH 0x00100000

#define MAX(A,B) (A) < (B) ? (B) : (A)

typedef struct Bytes {
    u8 *data;
    size_t len;
} Bytes;

typedef struct Checksum {
    union {
        u64 crc;
        u8 data[8];
    };
} Checksum;

Bytes
read_file(FILE *file) {
    Bytes bytes = {0};

    // Get file length.
    fseek(file, 0, SEEK_END);
    bytes.len = ftell(file);
    bytes.len = MAX(bytes.len, CHECKSUM_START + CHECKSUM_LENGTH);

    // Allocate memory, ensuring we have a minimum size for checksum purposes.
    bytes.data = calloc(1, bytes.len);

    // Copy file contents to memory.
    fseek(file, 0, SEEK_SET);
    fread(bytes.data, 1, bytes.len, file);
    return bytes;
}

u32
read_big_endian(u8 *data) {
    return (data[3] <<  0) |
           (data[2] <<  8) |
           (data[1] << 16) |
           (data[0] << 24);
}

u32
rol(u32 x, u32 n) {
    return (x << n) | (x >> (32 - n));
}

Checksum
calculate_crc(Bytes bytes) {
    Checksum checksum = {0};
    u32 t1 = 0xF8CA4DDC;
    u32 t2 = 0xF8CA4DDC;
    u32 t3 = 0xF8CA4DDC;
    u32 t4 = 0xF8CA4DDC;
    u32 t5 = 0xF8CA4DDC;
    u32 t6 = 0xF8CA4DDC;
    for (size_t i = CHECKSUM_START; i < (CHECKSUM_START + CHECKSUM_LENGTH); i += 4) {
        u32 num = read_big_endian(&bytes.data[i]);
		if ((t6 + num) < t6) {
			t4++;
		}
		t6 += num;
		t3 ^= num;
		u32 r = rol(num, (num & 0x1F));
		t5 += r;
		if (t2 > num) {
			t2 ^= r;
		} else {
			t2 ^= t6 ^ num;
		}
        t1 += t5 ^ num;
    }
    u64 upper = t5 ^ t2 ^ t1;
    u64 lower = t6 ^ t4 ^ t3;
    upper = read_big_endian((u8*)&upper);
    lower = read_big_endian((u8*)&lower);
    checksum.crc = upper << 32 | lower;
    return checksum;
}

void
print_usage(void) {
    printf("Usage: %s [options] <filename>\n", BIN_NAME);
    printf("\n");
    printf("\t-o <out_file.c> Path to the output file. If blank, stdout will be used.\n");
    printf("\t-v              Verbose.\n");
    printf("\t-h              Prints usage.\n");
    printf("\n");
}

int main(int argc, char *argv[]) {
    FILE *in_file  = stdin;
    FILE *out_file = stdout;
    char *in_file_path  = NULL;
    char *out_file_path = NULL;
    bool verbose = false;

    // Handle arguments and flags.
    int option;
    while ((option = getopt(argc, argv, "hvo:")) != -1) {
        switch (option) {
            case 'h': {
                print_usage();
                return EXIT_SUCCESS;
            } break;
            case 'o': {
                out_file_path = optarg;
            } break;
            case 'v': {
                verbose = true;
            } break;
            default: {
                print_usage();
                return EXIT_FAILURE;
            } break;
        }
    }
    in_file_path = argv[optind];

    // Open source file.
    if (in_file_path == NULL) {
        in_file = stdin;
    } else {
        in_file = fopen(in_file_path, "rb");
        if (in_file == NULL) {
            fprintf(stderr, "%s: can't open input file: %s\n",
                    BIN_NAME, in_file_path);
            return EXIT_FAILURE;
        }
    }

    // Open destination file.
    if (out_file_path == NULL) {
        out_file = stdout;
    } else {
        out_file = fopen(out_file_path, "wb");
        if (out_file == NULL) {
            fprintf(stderr, "%s: can't open output file: %s\n",
                    BIN_NAME, out_file_path);
            return EXIT_FAILURE;
        }
    }

    // Read source file into memory.
    Bytes bytes = read_file(in_file);

    // Write bootdata at offset 0x40 of dst file.
    memcpy(bytes.data + 0x40, bootdata, sizeof(bootdata));

    // Calculate CRC after bootdata was added on the dst file.
    Checksum checksum = calculate_crc(bytes);
    if (verbose) {
        printf("Checksum: 0x%02X%02X%02X%02X%02X%02X%02X%02X\n",
                checksum.data[0],
                checksum.data[1],
                checksum.data[2],
                checksum.data[3],
                checksum.data[4],
                checksum.data[5],
                checksum.data[6],
                checksum.data[7]);
    }

    // Write crc bytes at 0x10 offset on the dst file.
    memcpy(bytes.data + 0x10, checksum.data, 8 * sizeof(u8));

    // Save the output file.
    fwrite(bytes.data, 1, bytes.len, out_file);

    // Cleanup.
    if (in_file != stdin) {
        fclose(in_file);
    }
    if (out_file != stdout) {
        fclose(out_file);
    }
    return EXIT_SUCCESS;
}
