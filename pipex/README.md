# 🚀 Pipex - Documentation Technique

## 📚 Table des matières
1. 🎯 [Vue d'ensemble](#vue-densemble)
2. ⚙️ [Spécifications techniques](#specifications-techniques)
3. 🏗️ [Architecture](#architecture)
4. 💻 [Implémentation](#implementation)
5. ⚡ [Gestion des processus](#gestion-des-processus)
6. 🔧 [Configurations avancées](#configurations-avancees)
7. 📎 [Guide redirections Shell](https://github.com/Xxzer042xX/42-Common-Core/blob/main/pipex/docs/shell-redirections-readme.md)
8. 📎 [Guide variables d'environnement et processus](https://github.com/Xxzer042xX/42-Common-Core/blob/main/pipex/docs/shell-var-env.md)
9. 📎[Ressources](#ressources)
## Vue d'ensemble

### 📋 Description
Pipex est une implémentation en C des mécanismes de redirection et de pipeline UNIX. Ce projet reproduit le comportement natif des pipes shell en utilisant les appels système de bas niveau.

### 🎯 Objectifs
- 🔄 Reproduction fidèle du comportement des pipes UNIX
- 💪 Gestion robuste des processus et de la mémoire
- 🔒 Implementation sécurisée des redirections d'entrée/sortie
- 📈 Extensibilité pour les fonctionnalités avancées

### 💡 Contexte d'utilisation
```bash
./pipex infile cmd1 cmd2 outfile
# Équivalence shell:
# < infile cmd1 | cmd2 > outfile
```

## Specifications techniques

### 🛠️ Environnement de développement
- 🐧 Système : Unix/Linux
- 🔨 Compilateur : GCC avec flags de compilation stricts
- 📋 Standard : C11
- ⚡ Makefile : Compilation optimisée et règles standards

### 📦 Dépendances requises
- 📚 Libc standard
- 🔄 Environnement POSIX compatible
- 🔑 Permissions d'accès aux appels système

### 🔧 API système utilisée
```c
// 📂 Gestion des fichiers
open()    // Ouverture des fichiers
close()   // Fermeture des descripteurs
read()    // Lecture de données
write()   // Écriture de données
access()  // Vérification des permissions
unlink()  // Suppression de fichiers

// 🔄 Gestion des processus
fork()    // Création de processus
execve()  // Exécution de programmes
wait()    // Attente de processus
waitpid() // Attente de processus spécifique

// 🔌 Gestion des descripteurs
pipe()    // Création de tube
dup()     // Duplication de descripteur
dup2()    // Duplication avec cible spécifique

// 💾 Gestion mémoire
malloc()  // Allocation dynamique
free()    // Libération mémoire
```

## Architecture

### 📁 Structure du projet
```
pipex/
├── include/          🔍
│   ├── pipex.h       # Définitions et prototypes
│   └── errors.h      # Gestion des erreurs
├── src/             💻
│   ├── main.c        # Point d'entrée
│   ├── init.c        # Initialisation
│   ├── process.c     # Gestion des processus
│   ├── exec.c        # Exécution des commandes
│   ├── utils.c       # Fonctions utilitaires
│   └── cleanup.c     # Nettoyage ressources
├── bonus/           ⭐
│   └── [fichiers bonus]
└── tests/           🧪
    └── [fichiers de test]
```

### 🔨 Modules fonctionnels
1. **Core** 🎯
   - Parsing des arguments
   - Validation des entrées
   - Gestion du flux principal

2. **Process Management** ⚡
   - Fork et création de processus
   - Synchronisation
   - Communication inter-processus

3. **File Operations** 📂
   - Gestion des descripteurs
   - Redirections E/S
   - Validation des accès

4. **Error Handling** ⚠️
   - Codes d'erreur personnalisés
   - Messages contextuels
   - Nettoyage en cas d'erreur

## Implementation

### 🚦 Initialisation
1. ✅ Validation des arguments
2. 🔒 Vérification des permissions
3. 🔧 Initialisation des structures de données
4. ⚙️ Configuration des descripteurs

### 🔄 Pipeline d'exécution
1. 🌟 Création du pipe de communication
2. 🔄 Fork des processus enfants
3. 🔌 Configuration des redirections
4. ▶️ Exécution des commandes
5. ⏳ Synchronisation et attente
6. 🧹 Nettoyage des ressources

### ⚠️ Gestion des erreurs
- 🔍 Validation extensive des entrées
- ✅ Vérification des valeurs de retour
- 🧹 Libération propre des ressources
- 📝 Messages d'erreur détaillés

## Gestion des processus

### 🔄 Process lifecycle
1. **Création** 🔨 : Fork et initialisation
2. **Configuration** ⚙️ : Redirection des descripteurs
3. **Exécution** ▶️ : Lancement des commandes
4. **Supervision** 👀 : Monitoring et synchronisation
5. **Terminaison** 🏁 : Nettoyage et codes de retour

### 🔄 Communication inter-processus
- 📡 Tubes anonymes pour le flux de données
- ⏳ Synchronisation par wait/waitpid
- 🔔 Gestion des signaux (optionnel)

## Configurations avancees

### 📝 Mode Here_doc
Implémentation du heredoc UNIX :
```bash
./pipex here_doc LIMITER cmd1 cmd2 outfile
```

### 🔗 Multi-pipes
Support de pipes multiples :
```bash
./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile
```

## 📚 Ressources
- [Pipes UNIX expliqués](https://www.rozmichelle.com/pipes-forks-dups/)
- [Fork en C](https://www.geeksforgeeks.org/fork-system-call/)
- [Appels système de Pipe](https://www.geeksforgeeks.org/pipe-system-call/)

