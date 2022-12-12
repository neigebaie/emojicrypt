/*
 * Emojicrypt
 * @author neigebaie
 */
 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "emojiset.h"
#include "AES/aes.h"

uint8_t *aes_init(size_t key_size);

void aes_key_expansion(uint8_t *key, uint8_t *w);

void aes_inv_cipher(uint8_t *in, uint8_t *out, uint8_t *w);

void aes_cipher(uint8_t *in, uint8_t *out, uint8_t *w);
