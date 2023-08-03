# Emojicrypt ✨
Petit algorithme permettant d'encrypter n'importe quel fichier en une **chaîne d'emojis**.

![main](https://cdn.discordapp.com/attachments/547909957711036429/1136436643247689878/image.png)

## Installation
### Téléchargement
[Lien de téléchargement](https://github.com/neigebaie/emojicrypt/releases/latest)
### Compilation
1. clone this repo
2. run make command
```
make
```

## Utilisation
Encryption :
```
 🐯   | ./emojicrypt -e -i example.txt -o example.enc           
🔑 Enter your key:
```

Decryption :
```
 🐯   | ./emojicrypt -d -i example.enc -o example_out.txt           
🔑 Enter your key:
```

Toutes les options :
```
  -d        decryption mode
  -e        encryption mode
  -h        this help page
  -i file   input file
  -o file   output file
```

## Liste des fonctionnalités à ajouter
 - Mélange des colonnes du bloc
 - Support du mode CBC
 - Nom de fichier de sortie automatique si non fourni 

