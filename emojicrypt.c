/*
 * Emojicrypt
 * @author neigebaie
 */

#include "emojicrypt.h"
#include "emojiset.h"
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define Nb 4
#define ROUNDS 16

#define MAX_KEYSTR_LENGTH 64

/* global cmd flags: */
static uint8_t o_enc = 0;
static uint8_t o_dec = 0;
char *o_in  = NULL;
char *o_out = NULL;

const char vsel16[] = {0xef, 0xb8, 0x8f, 0x00};
const char zwjoin[] = {0xe2, 0x80, 0x8d, 0x00};

uint8_t s_box[256] = { // generated by s_box_gen.py
    // 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
    0xe8, 0x81, 0x41, 0x32, 0xbc, 0x16, 0x03, 0x15, 0x34, 0x71, 0xca, 0x1f, 0x9f, 0x38, 0x0c, 0x63, // 0
    0x33, 0xb3, 0xba, 0xdf, 0xc5, 0xe6, 0xad, 0x47, 0xf4, 0x9a, 0x89, 0xa2, 0x66, 0xb7, 0x77, 0xfc, // 1
    0x53, 0xae, 0x36, 0xf6, 0x99, 0xa1, 0x37, 0x7b, 0x5f, 0x5e, 0x86, 0x09, 0xc3, 0x91, 0xe4, 0xa0, // 2
    0x2e, 0x0f, 0xb6, 0x0d, 0x2d, 0xf0, 0x2a, 0xf9, 0x4d, 0x4a, 0x54, 0x49, 0xe5, 0x70, 0xc4, 0x35, // 3
    0x9e, 0xfa, 0x6a, 0xa8, 0x4b, 0x8b, 0x08, 0x1c, 0x9c, 0x0a, 0x1d, 0xda, 0x78, 0xee, 0x65, 0xa5, // 4
    0xcf, 0x04, 0xec, 0x67, 0xac, 0x7a, 0xe9, 0xb9, 0xfe, 0x21, 0x14, 0xea, 0x01, 0x3c, 0xbd, 0x2c, // 5
    0xc8, 0x6c, 0x94, 0xf8, 0x79, 0x5c, 0x52, 0x05, 0xed, 0xf3, 0x1a, 0x60, 0x68, 0x40, 0xd7, 0xfd, // 6
    0xcc, 0x28, 0xe3, 0x20, 0xc1, 0xff, 0x39, 0x10, 0x64, 0xab, 0xe2, 0x7c, 0x13, 0xf5, 0xbb, 0x85, // 7
    0xa4, 0x73, 0x87, 0x90, 0x9b, 0x07, 0x4c, 0xdc, 0x1b, 0x76, 0x12, 0x4e, 0x51, 0x23, 0x80, 0xd9, // 8
    0x97, 0x17, 0x5d, 0x50, 0x29, 0x3a, 0xcd, 0x42, 0x45, 0x7f, 0x3b, 0x24, 0x00, 0x92, 0xaf, 0xb8, // 9
    0x44, 0x82, 0x98, 0xd8, 0xc2, 0xb1, 0x72, 0x18, 0x11, 0xdd, 0xef, 0x69, 0x8a, 0x0e, 0x46, 0x6d, // a
    0x88, 0x22, 0x84, 0x7d, 0xd1, 0xd0, 0xb2, 0x02, 0x19, 0xc0, 0x25, 0xe1, 0xc7, 0x95, 0x75, 0x7e, // b
    0xf1, 0x2f, 0x4f, 0x9d, 0x30, 0x83, 0xb0, 0x8e, 0xc6, 0x57, 0xa6, 0xb5, 0xa3, 0x56, 0x0b, 0xa7, // c
    0xaa, 0xd3, 0x06, 0x3e, 0xdb, 0x48, 0xfb, 0x62, 0x6e, 0x8d, 0xbf, 0x59, 0x6b, 0xd4, 0x8f, 0xa9, // d
    0x5a, 0xcb, 0x1e, 0x5b, 0x2b, 0x27, 0x96, 0xf7, 0xb4, 0xce, 0x58, 0x55, 0x8c, 0xd2, 0x43, 0xf2, // e
    0xd6, 0xe0, 0xbe, 0xd5, 0x26, 0x93, 0xde, 0x3f, 0x3d, 0x74, 0xe7, 0x61, 0x6f, 0x31, 0xc9, 0xeb};// f

uint8_t inv_s_box[256] = { // generated by s_box_gen.py
    // 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
    0x9c, 0x5c, 0xb7, 0x06, 0x51, 0x67, 0xd2, 0x85, 0x46, 0x2b, 0x49, 0xce, 0x0e, 0x33, 0xad, 0x31, // 0
    0x77, 0xa8, 0x8a, 0x7c, 0x5a, 0x07, 0x05, 0x91, 0xa7, 0xb8, 0x6a, 0x88, 0x47, 0x4a, 0xe2, 0x0b, // 1
    0x73, 0x59, 0xb1, 0x8d, 0x9b, 0xba, 0xf4, 0xe5, 0x71, 0x94, 0x36, 0xe4, 0x5f, 0x34, 0x30, 0xc1, // 2
    0xc4, 0xfd, 0x03, 0x10, 0x08, 0x3f, 0x22, 0x26, 0x0d, 0x76, 0x95, 0x9a, 0x5d, 0xf8, 0xd3, 0xf7, // 3
    0x6d, 0x02, 0x97, 0xee, 0xa0, 0x98, 0xae, 0x17, 0xd5, 0x3b, 0x39, 0x44, 0x86, 0x38, 0x8b, 0xc2, // 4
    0x93, 0x8c, 0x66, 0x20, 0x3a, 0xeb, 0xcd, 0xc9, 0xea, 0xdb, 0xe0, 0xe3, 0x65, 0x92, 0x29, 0x28, // 5
    0x6b, 0xfb, 0xd7, 0x0f, 0x78, 0x4e, 0x1c, 0x53, 0x6c, 0xab, 0x42, 0xdc, 0x61, 0xaf, 0xd8, 0xfc, // 6
    0x3d, 0x09, 0xa6, 0x81, 0xf9, 0xbe, 0x89, 0x1e, 0x4c, 0x64, 0x55, 0x27, 0x7b, 0xb3, 0xbf, 0x99, // 7
    0x8e, 0x01, 0xa1, 0xc5, 0xb2, 0x7f, 0x2a, 0x82, 0xb0, 0x1a, 0xac, 0x45, 0xec, 0xd9, 0xc7, 0xde, // 8
    0x83, 0x2d, 0x9d, 0xf5, 0x62, 0xbd, 0xe6, 0x90, 0xa2, 0x24, 0x19, 0x84, 0x48, 0xc3, 0x40, 0x0c, // 9
    0x2f, 0x25, 0x1b, 0xcc, 0x80, 0x4f, 0xca, 0xcf, 0x43, 0xdf, 0xd0, 0x79, 0x54, 0x16, 0x21, 0x9e, // a
    0xc6, 0xa5, 0xb6, 0x11, 0xe8, 0xcb, 0x32, 0x1d, 0x9f, 0x57, 0x12, 0x7e, 0x04, 0x5e, 0xf2, 0xda, // b
    0xb9, 0x74, 0xa4, 0x2c, 0x3e, 0x14, 0xc8, 0xbc, 0x60, 0xfe, 0x0a, 0xe1, 0x70, 0x96, 0xe9, 0x50, // c
    0xb5, 0xb4, 0xed, 0xd1, 0xdd, 0xf3, 0xf0, 0x6e, 0xa3, 0x8f, 0x4b, 0xd4, 0x87, 0xa9, 0xf6, 0x13, // d
    0xf1, 0xbb, 0x7a, 0x72, 0x2e, 0x3c, 0x15, 0xfa, 0x00, 0x56, 0x5b, 0xff, 0x52, 0x68, 0x4d, 0xaa, // e
    0x35, 0xc0, 0xef, 0x69, 0x18, 0x7d, 0x23, 0xe7, 0x63, 0x37, 0x41, 0xd6, 0x1f, 0x6f, 0x58, 0x75};// f

/*
 * Adds the encryption key to the block
 */
void add_round_key(uint8_t *state, uint8_t *key) {
  uint8_t i, j;
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      state[Nb * i + j] ^= key[Nb * i + j];
    }
  }
}

/*
 * Performs sub bytes operation
 */
void sub_bytes(uint8_t *state) {
  uint8_t i, j;
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      state[Nb * i + j] = s_box[state[Nb * i + j]];
    }
  }
}

/*
 * Performs inverse sub bytes operation
 */
void inv_sub_bytes(uint8_t *state) {
  uint8_t i, j;
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      state[Nb * i + j] = inv_s_box[state[Nb * i + j]];
    }
  }
}

/*
 * Shifts rows (to the left)
 */
void shift_rows(uint8_t *block) {
    uint8_t i, s, k, tmp;

    for (i = 1; i < Nb; i++) {
        for (s = 0; s < i; s++) {
            tmp = block[Nb * i]; // first element of row i

            for (k = 0; k < Nb - 1; k++) {
                block[Nb * i + k] = block[Nb * i + k + 1];
            }
            
            block[Nb * i + Nb - 1] = tmp;
        }
    }
}

/*
 * Shifts rows (to the right)
 */
void inv_shift_rows(uint8_t *block) {
    uint8_t i, s, k, tmp;

    for (i = 1; i < Nb; i++) {
        for (s = 0; s < i; s++) {
            tmp = block[Nb * i + Nb - 1]; // last element of row i

            for (k = Nb - 1; k > 0; k--) {
                block[Nb * i + k] = block[Nb * i + k - 1];
            }
            
            block[Nb * i] = tmp;
        }
    }
}

/*
 * Returns utf8 char's length (in bytes)
 */
uint8_t wchar_len(uint8_t byte) {
    if (byte < 0xC0)
        return 1;
    if (byte < 0xe0)
        return 2;
    if (byte < 0xf0)
        return 3;
    return 4;
}

/*
 * Used for debugging, prints the current block (hex)
 */
void print_block(uint8_t *block) {
  uint8_t i, j;
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      printf("%02x ", block[i * Nb + j]);
    }
    printf("\n");
  }
  printf("\n");
}

/*
 * Used for debugging, prints the current block as emojis
 */
void print_emoji_block(emoji *block) {
  uint8_t i, j;
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      printf("%s ", block[i * Nb + j]);
    }
    printf("\n");
  }
  printf("\n");
}

/*
 * Used for debugging, prints the current block as text
 */
void print_text_block(uint8_t *block) {
  printf("%s\n", block);
  uint8_t i, j;
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      printf("%02x ", block[i * Nb + j]);
    }
    printf("\n");
  }
  printf("\n");
}

/*
 * Used for debugging, prints the key (hex)
 */
void print_key(uint8_t *key) {
  // printf("keystr=");
  // for (int i = 0; i < Nb*Nb; i++) {
  //   printf("%c", key[i]);
  // }
  // printf("\n");

  printf("key=");
  for (int i = 0; i < Nb*Nb; i++) {
    printf("%02x ", key[i]);
  }
  printf("\n");
}
/*
 * Reads an utf8 character from the file's stream (between 1 and 4 bytes)
 */
int fget_utf8(char *buf, int *start_i, int max, FILE* file) {
    int i;
    if (feof(file)) return -1;
    buf[*start_i] = fgetc(file);
    if (!buf[*start_i]) {
        printf("invalid wclen\n");
        return -1;
    }
    for (i = *start_i + 1; i < wchar_len(buf[*start_i]) + *start_i && i < max; i++) {
        buf[i] = fgetc(file);
    }
    *start_i = i;
    buf[i] = 0;
    return 0;
}

/*
 * Reads an emoji from the file's stream, one emoji can be constituted of multiple utf8 characters
 */
void fget_emoji(char *buf1, char *buf2, int *buf1_i, int *buf2_i, FILE *file) {
    if (strcmp(buf2, zwjoin) && *buf2_i) {
        *buf2_i = 0;
        return;
    }
    if (!(*buf1_i) || *buf1_i > 4) {
        if (fget_utf8(buf1, buf1_i, 128, file)) return;
    }
    *buf2_i = 0;
    if(fget_utf8(buf2, buf2_i, 128, file)) return;
    if (!strcmp(buf2, vsel16) || !strcmp(buf2, zwjoin)) {
        for (int i = *buf1_i; i < (*buf1_i + *buf2_i); i++) {
            buf1[i] = buf2[i - *buf1_i];
        }
        *buf1_i = *buf1_i + *buf2_i;
        fget_emoji(buf1, buf2, buf1_i, buf2_i, file);
    }
}

/*
 * Performs the Emojicrypt cipher operation (for a single block)
 * (https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Electronic_codebook_(ECB))
 */
void ec_cipher(uint8_t *in, emoji *out, uint8_t *key) {
  uint8_t state[Nb * Nb]; // tableau de 4 x 4

  uint8_t i, j, k;
  // Copies input on state
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      state[Nb * i + j] = in[Nb * i + j];
    }
  }

  for (k = 0; k < ROUNDS; k++) {
    add_round_key(state, key);

    sub_bytes(state);

    shift_rows(state);
  }

  // Converts state to corresponding emojis
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      char *src = emojiset[state[Nb * i + j]];
      size_t size = strlen(src) + 1; // include null terminator
      memcpy(out[Nb * i + j], src, size);
    }
  }
}

/*
 * Performs the Emojicrypt decipher operation (for a single block)
 */
void ec_inv_cipher(uint8_t *in, uint8_t *out, uint8_t *key) {

  uint8_t i, k;
  for (i = 0; i < Nb * Nb; i++) {
    for (int k = 0; k < 256; k++) {
      out[i] = in[i];
    }
  }

  for (k = 0; k < ROUNDS; k++) {
    inv_shift_rows(out);

    inv_sub_bytes(out);

    add_round_key(out, key);
  }
}

/*
 * Very slow ! Not used
 * Finds the emoji's corresponding value
 */
uint8_t emoji_to_int(char *buf) {
  for (int j = 0; j < 256; j++) {
    if (!strcmp(buf, emojiset[j])) { // emojicmp(buf, emojiset[j])
      return j;
    }
  }
  return -1;
}

int encrypt_file(char *f_in_path, char *f_out_path, uint8_t *key) {
  FILE *f_in, *f_out;
  uint8_t i = 0, j;

  uint8_t buf[Nb * Nb];
  emoji out[Nb * Nb];

  clock_t clck_enc_start = clock();

  f_in = fopen(f_in_path, "rb");
  f_out = fopen(f_out_path, "wb");

  if (f_in == NULL) {
    fprintf(stderr, "🚧 Failed to open input file : %s\n", f_in_path);
    return EXIT_FAILURE;
  }

  if (f_out == NULL) {
    fprintf(stderr, "🚧 Failed to open output file : %s\n", f_out_path);
    return EXIT_FAILURE;
  }

  fseek(f_in, 0L, SEEK_END);
  long sz = ftell(f_in);
  fseek(f_in, 0L, SEEK_SET);
  printf("size = %ld\n", sz);
  // fprintf(f_out, "EMOJICRYPT : %ld\n", sz); // FILE HEADER

  while (!feof(f_in)) {
    buf[i] = getc(f_in);
    i++;
    if (i % (Nb * Nb) == 0) {
      ec_cipher(buf, out, key);
      for (j = 0; j < Nb * Nb; j++) {
        fputs(out[j], f_out);
      }
      fputs("\n", f_out);
      i = 0;
      if (feof(f_in))
        break;
    }
  }

  i--;
  // printf("i=%d\n", i);

  if (i != 0) {
    int padding_len = 0;
    while (i % (Nb * Nb)) {
      buf[i] = rand() % 256;
      i++;
      padding_len++;
    }
    buf[(Nb * Nb) - 1] = padding_len;

    ec_cipher(buf, out, key);
    for (j = 0; j < Nb * Nb; j++) {
      fputs(out[j], f_out);
    }
  } else {
    // printf("Pas de padding :)\n");
  }

  fclose(f_in);
  // fseek(f_in, 0L, SEEK_SET);
  fclose(f_out);

  clock_t clck_enc_end = clock();
  printf("encryption time : %.2lfms (%.2lfmbps)\n", 1000 * (double)(clck_enc_end - clck_enc_start) / CLOCKS_PER_SEC, ((double)sz/(1000*1000)) / ((double)(clck_enc_end - clck_enc_start) / CLOCKS_PER_SEC));

  return EXIT_SUCCESS;
}

int decrypt_file(char *f_in_path, char *f_out_path, uint8_t *key) {
  FILE *f_in, *f_out;
  uint8_t emoji_count = 0;
  uint8_t in[Nb * Nb];
  uint8_t out_bin[Nb * Nb];
  char buf1[128];
  char buf2[128];
  int buf1_i = 0, buf2_i = 0, tmp = 0;

  clock_t clck_dec_start = clock();

  f_in = fopen(f_in_path, "rb");
  f_out = fopen(f_out_path, "wb");

  if (f_in == NULL) {
    fprintf(stderr, "🚧 Failed to open input file : %s\n", f_in_path);
    return EXIT_FAILURE;
  }

  if (f_out == NULL) {
    fprintf(stderr, "🚧 Failed to open output file : %s\n", f_out_path);
    return EXIT_FAILURE;
  }

  while (!feof(f_in)) {
    buf2_i = 0;
    fget_emoji(buf1, buf2, &buf1_i, &buf2_i, f_in);

    if (buf1_i <= 4) {
      buf1[buf1_i] = '\0';
      if ((tmp = binary_search(0, 255, buf1)) >= 0) {
        // printf("%02x ", in[emoji_count]);
        in[emoji_count] = tmp;
        emoji_count++;
      } else { // unknown emoji or \n
        // printf("v1=%d : not found.\n", in[emoji_count]);
      }
      memcpy(buf1, buf2, buf2_i);
      buf1_i = buf2_i;
    } else {
      buf1[buf1_i] = '\0';
      buf1_i = 0;
      // printf("%s", buf1);
      // in[emoji_count] = 0;
      if ((tmp = binary_search(0, 255, buf1)) >= 0) {
        // printf("%02x ", in[emoji_count]);
        in[emoji_count] = tmp;
        emoji_count++;
      } else { // unknown emoji or \n
        // printf("v2=%d : not found.\n", in[emoji_count]);
      }
    }

    if (emoji_count == Nb * Nb) {
      int padding_len = 0;
      ec_inv_cipher(in, out_bin, key);
      if (feof(f_in)) {
        padding_len = out_bin[(Nb * Nb) - 1];
        // printf("last block. padding_len=%d\n", padding_len);
      }
      // printf("\n");
      // print_block(out_bin);
      fwrite((char *)out_bin, sizeof(uint8_t), (size_t)(Nb * Nb - padding_len), f_out);
      emoji_count = 0;
    }
  }

  fclose(f_in);
  fclose(f_out);

  clock_t clck_dec_end = clock();
  printf("decryption time : %.2lfms\n", 1000 * (double)(clck_dec_end - clck_dec_start) / CLOCKS_PER_SEC); // ((double)sz/(1000*1000)) / ((double)(clck_dec_end - clck_dec_start) / CLOCKS_PER_SEC)

  return EXIT_SUCCESS;
}

/*
 * Converts keytext given in the command line to key bytes
 * Not very strong tho
 */
int keytext_to_key(char *keytext, uint8_t *key) {

  for (int i = 0; i < Nb*Nb; i++) {
    key[i] = keytext[i % strlen(keytext)] + i;
  }

  for (int i = 0; i < strlen(keytext); i++) {
    key[i % (Nb*Nb)] += (uint8_t)keytext[i];
  }
  
  return 0;
}

int main(int argc, char *argv[]) {
  int opt;

  while ((opt = getopt(argc, argv, "dehk:i:o:")) != EOF) {
    switch (opt) {
      case 'e': /* encryption mode */
        o_enc++;
        break;
      case 'd': /* decryption mode */
        o_dec++;
        break;
      case 'i': /* input file */
        o_in = optarg;
        break;
      case 'o': /* output file */
        o_out = optarg;
        break;
      case 'h': /* help */
        helpme(argv[0]);
        return EXIT_SUCCESS;
        break;
      default:
        fprintf(stderr, "Usage: %s [-e] [-d] -i input -o output -k key\n", argv[0]);
        return 1;
    }
  }

  if (o_enc && o_dec) {
    fprintf(stderr, "🚧 Encryption (-e) and decryption (-d) flags are incompatible.\n");
    return EXIT_FAILURE;
  }

  if (!o_in) {
    fprintf(stderr, "🚧 An input file (-i) is required.\n");
    return EXIT_FAILURE;
  }

  if (!o_enc && !o_dec) {
    fprintf(stderr, "🚧 Encryption (-e) or decryption (-d) flag is required.\n");
    return EXIT_FAILURE;
  }

  char keystr[MAX_KEYSTR_LENGTH];
  uint8_t key[Nb*Nb];

  if ((o_enc || o_dec)) {
    char *input = getpass("🔑 Enter your key: ");

    if (strlen(input) >= MAX_KEYSTR_LENGTH - 1) {
      fprintf(stderr, "🚧 The key is too long, the max size is %d.\n", MAX_KEYSTR_LENGTH - 1);
      return EXIT_FAILURE;
    }

    strncpy(keystr, input, sizeof(keystr));
    
    // Clear the original input from memory for security
    memset(input, 0, strlen(input));
  }

  srand(time(NULL));

  keytext_to_key(keystr, key);
  // print_key(key);

  if (o_enc && o_in && o_out) {
    if (!encrypt_file(o_in, o_out, key))
      printf("File successfully encrypted! : %s -> 🔒%s\n", o_in, o_out);
    else
      fprintf(stderr, "🚧 An error occured during encryption!\n");
  } else if (o_dec && o_in && o_out) {
    if (!decrypt_file(o_in, o_out, key)) {
      printf("Success! : 🔒%s -> %s\n", o_in, o_out);
      return EXIT_SUCCESS;
    } else {
      fprintf(stderr, "🚧 An error occured during decryption!\n");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

static int helpme(char *argv_0)
{
  printf("Emojicrypt https://github.com/neigebaie/emojicrypt\n\n\
encrypt a file:	%s -e -i input -o output -k key\n\
decrypt a file:	%s -d -i input -o output -k key\n\n\
options:", argv_0, argv_0);
  printf("\n\
  -d      decryption mode\n\
  -e      encryption mode\n\
  -h      this help page\n\
  -i file input file\n\
  -o file output file\n");

  return 0;
}