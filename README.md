# Emojicrypt ✨

<img alt="language" src="https://img.shields.io/badge/Lang-C-blue.svg"> <img alt="version" src="https://img.shields.io/badge/Version-1.0.3-green.svg">

Fun algorithm allowing to encrypt any file into a **string of emojis**. 

[![asciicast](https://asciinema.org/a/620762.svg)](https://asciinema.org/a/620762)

## Installation
### Download
[Download link](https://github.com/neigebaie/emojicrypt/releases/latest)
### Compilation
1. clone this repo
2. run make command
```
make
```

## Usage
Encryption:
```
 🐯   | ./emojicrypt -e -i example.txt -o example.enc           
🔑 Enter your key:
```

Decryption:
```
 🐯   | ./emojicrypt -d -i example.enc -o example_out.txt           
🔑 Enter your key:
```

Available flags:
```
  -d        decryption mode
  -e        encryption mode
  -h        this help page
  -i file   input file
  -o file   output file
```

## List of features to add
- Mixing the columns of the block
- CBC mode support
- Automatic output filename if not provided

