# Push_swap - École 42
> "Parce que Swap_push, c'est moins naturel" 

## 📋 Table des Matières
- [Vue d'ensemble](#vue-densemble)
- [Règles du Projet](#règles-du-projet)
- [Instructions Disponibles](#instructions-disponibles)
- [Algorithmes et Complexité](#algorithmes-et-complexité)
- [Bonus - Programme Checker](#bonus---programme-checker)
- [Installation et Utilisation](#installation-et-utilisation)

## Vue d'ensemble

Push_swap est un projet d'algorithmie qui consiste à trier une pile de nombres avec un set d'instructions limité, en utilisant deux piles (a et b). L'objectif est de développer un programme qui calcule et affiche la plus petite suite d'opérations permettant de trier la pile a.

### 🎯 Objectifs du Projet
- Apprendre et implémenter différents algorithmes de tri
- Comprendre la notion de complexité algorithmique
- Optimiser les solutions pour minimiser le nombre d'opérations
- Pratiquer la manipulation de structures de données (piles)

## Règles du Projet

### Configuration Initiale
- **Pile a** : Contient une quantité aléatoire de nombres (positifs et/ou négatifs)
- **Pile b** : Vide au départ
- **Contrainte** : Pas de doublons autorisés

### Conditions de Réussite
- Tous les nombres doivent être triés dans la pile a
- La pile b doit être vide
- Utiliser le minimum d'opérations possible

### Gestion des Erreurs
Le programme doit afficher "Error\n" sur la sortie d'erreur dans les cas suivants :
- Arguments non numériques
- Nombres ne tenant pas dans un int
- Présence de doublons

## Instructions Disponibles

### Opérations sur une Pile
```c
sa : swap a - Inverse les 2 premiers éléments de la pile a
sb : swap b - Inverse les 2 premiers éléments de la pile b
ss : sa et sb simultanément

pa : push a - Place le premier élément de b au sommet de a
pb : push b - Place le premier élément de a au sommet de b

ra : rotate a - Décale tous les éléments de a vers le haut
rb : rotate b - Décale tous les éléments de b vers le haut
rr : ra et rb simultanément

rra : reverse rotate a - Décale tous les éléments de a vers le bas
rrb : reverse rotate b - Décale tous les éléments de b vers le bas
rrr : rra et rrb simultanément
```

### Exemple de Manipulation
```plaintext
État Initial :
Pile a: 2 1 3 6 5 8
Pile b: (vide)

Après 'sa' :
Pile a: 1 2 3 6 5 8
Pile b: (vide)

Après 'pb pb pb' :
Pile a: 6 5 8
Pile b: 3 2 1
```

## Algorithmes et Complexité

### Stratégies de Tri
1. **Tri pour 3 nombres** : Algorithme spécifique optimisé
2. **Tri pour 5 nombres** : Utilisation stratégique de la pile b
3. **Tri pour de grandes listes** : Algorithme avancé (chunking, quicksort adapté, etc.)

### Objectifs de Performance
| Taille | Opérations Maximum |
|--------|-------------------|
| 3      | 2-3              |
| 5      | 12               |
| 100    | 700              |
| 500    | 5500             |

## Bonus - Programme Checker

Le bonus consiste à créer un programme "checker" qui vérifie si une série d'instructions trie correctement la pile.

### Fonctionnalités
- Lit les instructions depuis l'entrée standard
- Exécute les instructions sur la pile
- Affiche "OK" si la pile est triée, "KO" sinon
- Gère les erreurs de la même manière que push_swap

### Exemple d'Utilisation
```bash
$> ./checker 3 2 1 0
rra
pb
sa
rra
pa
OK
```

## Installation et Utilisation

### Compilation
```bash
make        # Compile push_swap
make bonus  # Compile checker (bonus)
make clean  # Nettoie les fichiers objets
make fclean # Nettoie tout
make re     # Recompile tout
```

### Utilisation
```bash
# Test simple
./push_swap 2 1 3 6 5 8

# Test avec vérification
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_OS $ARG
```

### Scripts de Test Recommandés
```bash
# Test avec 100 nombres
ARG=$(seq 1 100 | shuf); ./push_swap $ARG | wc -l

# Vérification du tri
ARG=$(seq 1 100 | shuf); ./push_swap $ARG | ./checker $ARG
```

---

## ⚠️ Notes Importantes

- Suivre la Norme de code de 42
- Aucune fuite mémoire n'est tolérée
- Les variables globales sont interdites
- Le Makefile doit inclure les règles standard
- La libft est autorisée

---