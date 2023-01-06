/*
 * Emojicrypt
 * @author neigebaie
 */

#include "emojicrypt.h"
#include "emojiset.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Nb 4

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
      state[Nb * i + j] ^= *key;
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

  uint8_t i, j;
  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      state[Nb * i + j] = in[Nb * i + j];
    }
  }

  add_round_key(state, key);

  sub_bytes(state);

  for (i = 0; i < Nb; i++) {
    for (j = 0; j < Nb; j++) {
      for (uint8_t k = 0; k < 16; k++) {
        out[Nb * i + j][k] = emojiset[state[Nb * i + j]][k];
      }
    }
  }
}

/*
 * Performs the Emojicrypt decipher operation (for a single block)
 */
void ec_inv_cipher(uint8_t *in, uint8_t *out, uint8_t *key) {

  uint8_t i, j;
  for (i = 0; i < Nb * Nb; i++) {
    for (int k = 0; k < 256; k++) {
      out[i] = in[i];
    }
  }

  inv_sub_bytes(out);

  add_round_key(out, key);
}

/*
 * Very slow !
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

int main() {
  clock_t clck_enc_start = clock();
  srand(time(NULL));

  FILE *f_in, *f_out;
  uint8_t i = 0, j, c;

  uint8_t buf[Nb * Nb];
  emoji out[Nb * Nb];
  uint8_t key[] = {0xa0, 0x0a, 0x11, 0xff};
  // uint8_t key[] = {0xaa, 0xaa, 0xaa, 0xaa};
  // uint8_t key[] = {0x00, 0x00, 0x00, 0x00};

  f_in = fopen("input.txt", "rb");
  f_out = fopen("file.enc", "wb");

  if (f_in == NULL) {
    fprintf(stderr, "Erreur d'ouverture du fichier d'entrée.\n");
    return EXIT_FAILURE;
  }

  if (f_out == NULL) {
    fprintf(stderr, "Erreur d'ouverture du fichier de sortie.\n");
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
        // fputs(" ", f_out);
      }
      fputs("\n", f_out);
      i = 0;
      if (feof(f_in))
        break;
    }
  }

  i--;
  printf("i=%d\n", i);

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
      // fputs(" ", f_out);
    }
    // fputs("\n", f_out);
  } else {
    printf("Pas de padding :)\n");
  }

  // fclose(f_in);
  fseek(f_in, 0L, SEEK_SET);
  fclose(f_out);

  printf("\nencryption completed!\n\n");

  // decryption

  printf("\ndecryption started!\n\n");


  FILE *f_enc, *f_clear;
  uint8_t emoji_count = 0;
  uint8_t in[Nb * Nb];
  uint8_t out_bin[Nb * Nb];
  char buf1[128];
  char buf2[128];
  int buf1_i = 0, buf2_i = 0, tmp = 0;
  f_enc = fopen("file.enc", "rb");
  f_clear = fopen("test3_out.dat", "wb");

  if (f_enc == NULL) {
    fprintf(stderr, "Erreur d'ouverture du fichier encrypté.\n");
    return EXIT_FAILURE;
  }

  if (f_clear == NULL) {
    fprintf(stderr, "Erreur d'ouverture du fichier decrypté.\n");
    return EXIT_FAILURE;
  }

  // clock_t clck_dec_start = clock();

  while (!feof(f_enc)) {
    buf2_i = 0;
    fget_emoji(buf1, buf2, &buf1_i, &buf2_i, f_enc);

    if (buf1_i <= 4) {
      buf1[buf1_i] = '\0';
      if ((tmp = binary_search(0, 255, buf1)) >= 0) {
        printf("%02x ", in[emoji_count]);
        in[emoji_count] = tmp;
        emoji_count++;
      } else {
        printf("v=%d : not found.\n", in[emoji_count]);
      }
      memcpy(buf1, buf2, buf2_i);
      buf1_i = buf2_i;
    } else {
      buf1[buf1_i] = '\0';
      buf1_i = 0;
      // printf("%s", buf1);
      // in[emoji_count] = 0;
      if ((tmp = binary_search(0, 255, buf1)) >= 0) {
        printf("%02x ", in[emoji_count]);
        in[emoji_count] = tmp;
        emoji_count++;
      } else {
        printf("v=%d : not found.\n", in[emoji_count]);
      }
    }

    if (emoji_count == Nb * Nb) {
      int padding_len = 0;
      ec_inv_cipher(in, out_bin, key);
      if (feof(f_enc)) {
        printf("last block.\n");
        padding_len = out_bin[(Nb * Nb) - 1];
      }
      printf("\n");
      print_block(out_bin);
      fwrite((char *)out_bin, sizeof(uint8_t), (size_t)(Nb * Nb - padding_len), f_clear);
      emoji_count = 0;
    }
  }

  // clock_t clck_dec_end = clock();

  // printf("encryption time : %.2lfms (%.2lfmbps)\n", 1000 * (double)(clck_dec_start - clck_enc_start) / CLOCKS_PER_SEC, ((double)sz/(1000*1000)) / ((double)(clck_dec_start - clck_enc_start) / CLOCKS_PER_SEC));
  // printf("decryption time : %.2lfms\n", 1000 * (double)(clck_dec_end - clck_dec_start) / CLOCKS_PER_SEC); // ((double)sz/(1000*1000)) / ((double)(clck_dec_end - clck_dec_start) / CLOCKS_PER_SEC)
  fclose(f_enc);
  fclose(f_clear);

  return EXIT_SUCCESS;
}

// TODO:
// - padding (with random bytes + padding length on last byte)
// - add shift rows
// - add mix columns ?