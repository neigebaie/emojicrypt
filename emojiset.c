/*
 * Emojicrypt
 * @author neigebaie
 */

#include "emojiset.h"

int binary_search(int l, int r, const emoji e) {
    if (l > r) return -1;

    int mid = l + (r - l) / 2;
    // printf("%d %d %d\n", mid, r, l);
    int cmp = strcmp(e, emojiset[mid]);

    if (!cmp) {
        // printf("res = %d\n", mid);
        return mid;
    }
    else if (cmp > 0)
        return binary_search(mid + 1, r, e);
    else
        return binary_search(l, mid - 1, e);
}

emoji emojiset[] = { // sorted for binary search
    "☄️", "☕", "⚰️", "✨", "❤️", "⭐", "🌊", "🌭", "🌮", "🌯", "🌰", "🌱", "🌳", "🌴", "🌵", "🌶️", 
    "🌷", "🌸", "🌹", "🌺", "🌻", "🌼", "🌽", "🌾", "🌿", "🍄", "🍅", "🍆", "🍇", "🍈", "🍉", "🍊", 
    "🍋", "🍌", "🍍", "🍎", "🍏", "🍐", "🍑", "🍒", "🍓", "🍔", "🍕", "🍖", "🍗", "🍘", "🍙", "🍚", 
    "🍛", "🍜", "🍝", "🍞", "🍟", "🍠", "🍡", "🍢", "🍣", "🍤", "🍥", "🍦", "🍧", "🍨", "🍩", "🍪", 
    "🍫", "🍬", "🍭", "🍮", "🍯", "🍰", "🍱", "🍲", "🍳", "🍵", "🍶", "🍷", "🍹", "🍼", "🍾", "🍿", 
    "🎂", "🎊", "🎋", "🏵️", "🐀", "🐁", "🐂", "🐃", "🐄", "🐅", "🐆", "🐇", "🐈", "🐉", "🐊", "🐋", 
    "🐌", "🐍", "🐎", "🐏", "🐐", "🐑", "🐒", "🐓", "🐔", "🐕", "🐖", "🐗", "🐘", "🐙", "🐚", "🐛", 
    "🐜", "🐝", "🐞", "🐟", "🐠", "🐡", "🐢", "🐣", "🐤", "🐥", "🐦", "🐧", "🐨", "🐩", "🐪", "🐫", 
    "🐬", "🐭", "🐮", "🐯", "🐰", "🐱", "🐲", "🐳", "🐴", "🐵", "🐶", "🐸", "🐹", "🐺", "🐻", "🐻‍❄️", 
    "🐼", "🐾", "🐿️", "💦", "💧", "💫", "💮", "🔥", "🕊️", "🕷️", "🥀", "🥃", "🥄", "🥐", "🥑", "🥒", 
    "🥓", "🥔", "🥕", "🥖", "🥗", "🥘", "🥙", "🥚", "🥛", "🥜", "🥝", "🥞", "🥟", "🥠", "🥡", "🥢", 
    "🥣", "🥤", "🥥", "🥦", "🥧", "🥨", "🥩", "🥪", "🥫", "🥬", "🥭", "🥮", "🥯", "🦀", "🦁", "🦂", 
    "🦃", "🦄", "🦅", "🦆", "🦇", "🦈", "🦉", "🦊", "🦋", "🦌", "🦍", "🦎", "🦏", "🦐", "🦑", "🦒", 
    "🦓", "🦔", "🦕", "🦖", "🦗", "🦘", "🦙", "🦚", "🦛", "🦜", "🦝", "🦞", "🦟", "🦠", "🦡", "🦢", 
    "🦣", "🦤", "🦥", "🦦", "🦧", "🦨", "🦩", "🦪", "🦫", "🦬", "🦭", "🦮", "🧀", "🧁", "🧂", "🧃", 
    "🧄", "🧅", "🧆", "🧇", "🧈", "🧉", "🧊", "🧋", "🪶", "🪷", "🪸", "🪹", "🪺", "🫘", "🫙", "🫧"};
