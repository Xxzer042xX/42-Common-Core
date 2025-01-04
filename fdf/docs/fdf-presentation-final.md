# Projet FDF (Fil de Fer) - Présentation Détaillée
*Durée: 45-60 minutes*

## 1. Introduction (5 minutes)

### 1.1 Présentation Personnelle
- Nom: [Votre Nom]
- Projet: FDF (Fil de Fer)
- Durée de développement: [X semaines/mois]

### 1.2 Vue d'Ensemble du Projet
**Objectif Principal:**
"FDF est un projet de visualisation 3D qui transforme une carte de points en une représentation wireframe interactive."

**DÉMONSTRATION RAPIDE:** [Montrer une carte simple en rotation]

### 1.3 Technologies Clés
```c
// Bibliothèques principales (fdf.h)
# include "../lib/minilibx-linux/mlx.h"      // Graphique
# include "../lib/libftprintf/libft/libft.h" // Utilitaires
# include <math.h>                           // Calculs 3D
```

## 2. Architecture du Projet (10 minutes)

### 2.1 Structure du Programme
[Montrer le diagramme du projet]

```plaintext
[Structure des dossiers avec explications]
fdf
├── src/
│   ├── controls/   → Gestion des entrées utilisateur
│   ├── core/       → Fonctions principales
│   ├── drawer/     → Rendu graphique
│   └── [autres dossiers...]
```

### 2.2 Points Techniques Essentiels
```c
// Structure principale de l'application (ft_structs.h)
typedef struct s_app {
    t_map map;          // Carte et points
    t_win win;          // Fenêtre MLX
    t_matrix matrix;    // Transformations
    t_sidebar sidebar;  // Interface
    e_app_state state; // État du programme
} t_app;
```

**DÉMO:** [Montrer l'initialisation du programme]

## 3. Fonctionnalités Principales (15 minutes)

### 3.1 Lecture et Parsing de Fichiers
```c
// Validation du fichier (fdf.c)
static int is_fdf_file(const char *filename)
{
    const char *ext;

    if (!filename || ft_strlen(filename) < 5)
        return (ERR_ARGS);
    ext = ft_strrchr(filename, '.');
    if (!ext || ft_strncmp(ext, ".fdf", 4))
        return (ERR_ARGS);
    return (SUCCESS);
}
```
**Points Clés:**
- Validation stricte des fichiers
- Gestion des erreurs
- Sécurité des données

### 3.2 Système de Rendu
```c
// Fonction de dessin (drawer.c)
void draw_line(t_app *app, t_point start, t_point end)
{
    // [Montrer l'algorithme de Bresenham]
}
```
**DÉMO:** [Montrer différents modes de rendu]

### 3.3 Gestion des Transformations
```c
// Configuration des transformations (matrix.h)
# define SCALE 0.1f
# define SCALE_STEP 20.0f
# define ISO_ANGLE 0.523599f // 30 degrés en radians
```
**DÉMO:** [Montrer les rotations et zoom]

## 4. Interface Utilisateur (10 minutes)

### 4.1 Contrôles Utilisateur
```c
// Gestion des événements (events.c)
int handle_key(int keycode, void *param)
{
    t_app *app;

    app = (t_app *)param;
    if (keycode == KEY_ESC)
        return (handle_exit(app));
    // [Autres contrôles...]
}
```

### 4.2 Barre Latérale et Informations
```c
// Structure de la barre latérale
typedef struct s_sidebar {
    t_control_pair *ctrl_pairs;
    t_rgba color;
    char *title;
    // [Autres paramètres...]
} t_sidebar;
```
**DÉMO:** [Montrer l'interface et les contrôles]

## 5. Optimisations (10 minutes)

### 5.1 Performance
```c
// Optimisation du rendu (drawer.c)
void put_pixel(t_app *app, int x, int y, int color)
{
    char *pixel;
    int i;

    if (x >= 0 && x < app->win.w_win && 
        y >= 0 && y < app->win.h_win)
    {
        i = y * app->win.line_len + x * (app->win.bbp / 8);
        pixel = app->win.addr + i;
        *(int *)pixel = color;
    }
}
```

### 5.2 Gestion de la Mémoire
```c
// Nettoyage des ressources (core.c)
void cleanup_app(t_app *app)
{
    // [Montrer la gestion de la mémoire]
}
```

## 6. Démonstration Finale (5 minutes)

### 6.1 Cas d'Utilisation Avancés
1. Cartes complexes
2. Changements de vue
3. Gestion des erreurs

## 7. Conclusion (5 minutes)

### 7.1 Points Forts du Projet
- Architecture modulaire
- Interface intuitive
- Performance optimisée
- Gestion robuste des erreurs

### 7.2 Questions et Réponses

## Notes pour la Soutenance

### Points à Accentuer
1. Choix techniques (pourquoi ces structures?)
2. Gestion des erreurs (montrer des exemples)
3. Optimisations (expliquer l'impact)
4. Interface utilisateur (facilité d'utilisation)

### Préparation
- Compiler le projet avant
- Avoir des fichiers tests prêts
- Terminal propre
- Environnement de démo préparé