# Protocole PolyLink
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/iElsha/Protocole-PolyLink/CI)
![GitHub](https://img.shields.io/github/license/iElsha/Protocole-PolyLink)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/iElsha/Protocole-PolyLink)
[![GitHub issues](https://img.shields.io/github/issues/iElsha/Protocole-PolyLink)](https://github.com/iElsha/Protocole-PolyLink/issues)
[![GitHub forks](https://img.shields.io/github/forks/iElsha/Protocole-PolyLink)](https://github.com/iElsha/Protocole-PolyLink/network)
[![GitHub stars](https://img.shields.io/github/stars/iElsha/Protocole-PolyLink)](https://github.com/iElsha/Protocole-PolyLink/stargazers)

## Install
1. Create the executable
```
cd cmake-build-debug
make
```
2. run it with the corresponding computer Id
```
./Protocole_PolyLink <ComputerId>
```
Examples with 3 terminal:
```
Terminal 1: ./Protocole_PolyLink 1
Terminal 2: ./Protocole_PolyLink 2
Terminal 3: ./Protocole_PolyLink 3
```

## Features (In French)
- Communication sur un réseau en anneau
    - Protocole **TCP**
- **Fairplay**
    - Une seule personne ne peut parler à la fois
    - Un message par tour
- Gestion des :
    - **Acquittement** lors de la réception du paquet
    - **Erreurs** = renvois du ou des message(s) erronés.
- **Multiplexage** :
    - Plusieurs messages peuvent circuler dans le même paquet
    - Les headers ont une taille fixe    
    - Le contenu des **message a une taille dynamique** (=variable)
        - Utilisation d'offset pour se repérer dans le paquet
- Gestion des adresses
    - **Attribution automatique des ports**
        - Il est possible de modifier le port dans le fichier de config ci-dessous.
    - attribution manuel des adresses IP dans le fichier `src/config/configIps.c`
    
## Config
Open the file in `src/config/configIps.c` then edit lines 
```C
const int NUMBER_OF_PC = XXX; // for example 3

// Put as many address there than the number of PC
const char *ADRESSES_EMETTEUR[] = {"192.168.43.178", "192.168.43.51", "192.168.43.131"};
const char *ADRESSES_RECEPTEUR[] = {"192.168.43.131", "192.168.43.178", "192.168.43.51"};
```

## Commands
When you're asked to send a message or not, you can type `h` to get the help.
Otherwise it's acting like a basic UNIX command.

## Contributors
- Etienne Lécrivain
- Erwan Launay
- Maxence Dominici

## Context
This project has been done in a network computer science class during our studies.
