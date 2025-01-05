# 📝 Pipex - Projet 42

## 📋 Table des matières
1. [Introduction](#introduction)
2. [Aperçu du projet](#aperçu-du-projet)
3. [Prérequis](#prérequis)
4. [Installation et utilisation](#installation-et-utilisation)
5. [Détails d'implémentation](#détails-dimplémentation)
6. [Bonus](#bonus)
7. [Exemples](#exemples)
8. [Structure du projet](#structure-du-projet)
9. [Gestion des erreurs](#gestion-des-erreurs)
10. [Ressources](#ressources)

## 🔎 Introduction
Pipex est un projet qui vise à approfondir la compréhension des mécanismes UNIX en recréant la fonctionnalité des pipes (`|`) en C. Le programme reproduit le comportement des pipelines de commandes shell, en gérant spécifiquement l'entrée/sortie de fichiers et l'exécution des commandes via des tubes.

## 🚀 Aperçu du projet
L'objectif principal est de créer un programme qui se comporte exactement comme la commande shell :
```bash
< fichier1 cmd1 | cmd2 > fichier2
```
en l'implémentant comme :
```bash
./pipex fichier1 cmd1 cmd2 fichier2
```

### Fonctionnalités principales
- Gestion des fichiers d'entrée/sortie
- Exécution des commandes
- Communication entre processus via pipes
- Gestion des erreurs
- Prévention des fuites mémoire

## ⚙️ Prérequis
- Compilateur GCC
- Make
- Système d'exploitation UNIX
- Connaissances de base des commandes shell

### Fonctions autorisées
```c
- open, close, read, write
- malloc, free
- perror, strerror
- access
- dup, dup2
- execve
- exit
- fork
- pipe
- unlink
- wait, waitpid
```

## 📥 Installation et utilisation

### Installation
```bash
git clone https://github.com/votre_nom/pipex.git
cd pipex
make
```

### Utilisation de base
```bash
./pipex fichier_entree "cmd1" "cmd2" fichier_sortie
```

### Exemples
```bash
./pipex infile "ls -l" "wc -l" outfile
# Équivalent à : < infile ls -l | wc -l > outfile

./pipex infile "grep bonjour" "wc -w" outfile
# Équivalent à : < infile grep bonjour | wc -w > outfile
```

## 🔧 Détails d'implémentation

### Fonctionnalités principales
1. **Traitement des arguments**
   - Validation des arguments d'entrée
   - Vérification des permissions des fichiers
   - Analyse des commandes et leurs paramètres

2. **Création du pipe**
   - Création du tube de communication entre processus
   - Gestion appropriée des descripteurs de fichiers

3. **Gestion des processus**
   - Création des processus fils avec fork
   - Gestion de l'exécution et synchronisation des processus
   - Traitement de l'exécution des commandes avec execve

4. **Opérations sur les fichiers**
   - Gestion de l'ouverture et lecture du fichier d'entrée
   - Gestion de la création et écriture du fichier de sortie
   - Implémentation des redirections de descripteurs de fichiers

### Gestion de la mémoire
- Allocation et libération soigneuse des ressources
- Prévention des fuites mémoire
- Fermeture appropriée des descripteurs de fichiers

## ⭐ Bonus

### Pipes multiples
Gestion de plusieurs commandes en séquence :
```bash
./pipex fichier1 cmd1 cmd2 cmd3 ... cmdn fichier2
# Équivalent à : < fichier1 cmd1 | cmd2 | cmd3 ... | cmdn > fichier2
```

### Support here_doc
Gestion de la méthode d'entrée here_doc :
```bash
./pipex here_doc LIMITEUR cmd cmd1 fichier
# Équivalent à : cmd << LIMITEUR | cmd1 >> fichier
```

## 📁 Structure du projet
```
.
├── Makefile
├── README.md
├── include/
│   └── pipex.h
├── src/
│   ├── main.c
│   ├── process.c
│   ├── utils.c
│   └── error.c
└── bonus/
    └── pipex_bonus.c
```

## ⚠️ Gestion des erreurs
Le programme gère différents cas d'erreur :
- Nombre invalide d'arguments
- Erreurs de permission d'accès aux fichiers
- Échecs d'exécution des commandes
- Échecs d'allocation mémoire
- Erreurs de création de pipe

Chaque erreur est gérée proprement avec des messages appropriés et un nettoyage correct.

## 📚 Ressources
- [Pipes UNIX expliqués](https://www.rozmichelle.com/pipes-forks-dups/)
- [Fork en C](https://www.geeksforgeeks.org/fork-system-call/)
- [Appels système de Pipe](https://www.geeksforgeeks.org/pipe-system-call/)

## 📝 Note
Ce projet fait partie du cursus de l'école 42 et vise à enseigner :
- La création et gestion des processus
- La manipulation des descripteurs de fichiers
- La communication inter-processus
- La gestion des erreurs en C
- La gestion de la mémoire

## 👤 Auteur
Votre Nom (@votre_login)

## 📄 Licence
Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.