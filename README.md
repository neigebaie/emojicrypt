# Emojicrypt ✨
Petit algorithme permettant d'encrypter n'importe quel fichier en une **chaîne d'emojis**.

![main](https://cdn.discordapp.com/attachments/547909957711036429/1051988753557749861/demo.png)

## Compilation
```
gcc -o emojicrypt emojiset.c emojicrypt.c
```

## Utilisation
Encryption :
```
emojicrypt -e -i input -o output -k key
```

Decryption :
```
emojicrypt -d -i input -o output -k key
```

Toutes les options :
```
  -d      encryption mode
  -e      decryption mode
  -h      this help page
  -i file input file
  -k      the key used for encryption/decryption
  -o file output file
```

## Liste des fonctionnalités à ajouter
 - Mélange des colonnes du bloc
 - Adaptation en outil CLI (ligne de commande)
 - Support du mode CBC

