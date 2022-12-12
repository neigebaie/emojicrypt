/*
 * Emojicrypt
 * @author neigebaie
 */
 
#ifndef __EMOJISET_H__
#define __EMOJISET_H__

#include <string.h>
#include <stdint.h>
#include <stdio.h>

typedef char emoji[16];

int binary_search(int l, int r, const emoji e);

extern emoji emojiset[256];

#endif
