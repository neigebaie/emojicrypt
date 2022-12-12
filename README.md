# Emojicrypt ✨
Petit algorithme permettant d'encrypter une chaîne de caractère en une **chaîne d'emojis**.

![main](https://cdn.discordapp.com/attachments/547909957711036429/1051988753557749861/demo.png)

## Compilation
```
gcc -o emojicrypt emojiset.c emojicrypt.c
```
## Liste des fonctionnalités à ajouter :
 - Reconnaissance du padding (random bytes + padding length on last byte)
 - Décalage pour les lignes du bloc
 - Mélange des colonnes du bloc
