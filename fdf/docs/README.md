# MinilibX - Aide Mémoire

## 🚀 Installation des dépendances (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

## 📚 Principales Fonctions

### 1. Initialisation
```c
void    *mlx_ptr;
void    *win_ptr;

// Initialise la connexion X-Window
mlx_ptr = mlx_init();

// Crée une nouvelle fenêtre
win_ptr = mlx_new_window(mlx_ptr, width, height, "Titre");
```

### 2. Gestion des Images
```c
void    *img_ptr;
char    *addr;
int     bits_per_pixel;
int     line_length;
int     endian;

// Crée une nouvelle image
img_ptr = mlx_new_image(mlx_ptr, width, height);

// Récupère l'adresse de l'image pour manipulation directe
addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &line_length, &endian);

// Calcul de la position d'un pixel dans l'image
int pos = (y * line_length + x * (bits_per_pixel / 8));
```

### 3. Dessin
```c
// Dessine un pixel dans une fenêtre (lent)
mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);

// Met un pixel dans une image (rapide)
*(unsigned int *)(addr + pos) = color;

// Affiche l'image dans la fenêtre
mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, x, y);
```

### 4. Gestion des Événements
```c
// Gestion générique d'événements
mlx_hook(win_ptr, event_type, mask, function_ptr, param);

// Événements courants
#define X_EVENT_KEY_PRESS     2
#define X_EVENT_KEY_RELEASE   3
#define X_EVENT_MOUSE_PRESS   4
#define X_EVENT_MOUSE_RELEASE 5
#define X_EVENT_MOUSE_MOVE    6
#define X_EVENT_EXIT          17

// Exemple de fonction pour les touches
int key_hook(int keycode, void *param)
{
    if (keycode == 65307)  // ESC
        mlx_destroy_window(mlx_ptr, win_ptr);
    return (0);
}

// Lancement de la boucle d'événements
mlx_loop(mlx_ptr);
```

### 5. Codes des Touches Courantes
```c
#define KEY_ESC    65307
#define KEY_W      119
#define KEY_A      97
#define KEY_S      115
#define KEY_D      100
#define KEY_UP     65362
#define KEY_LEFT   65361
#define KEY_DOWN   65364
#define KEY_RIGHT  65363
#define KEY_PLUS   65451
#define KEY_MINUS  65453
```

## 🎨 Gestion des Couleurs
```c
// Création d'une couleur RGB
int color = (r << 16) | (g << 8) | b;

// Transparence (si supportée)
int color_with_alpha = (t << 24) | (r << 16) | (g << 8) | b;
```

## 🧹 Nettoyage
```c
// Destruction des ressources
mlx_destroy_image(mlx_ptr, img_ptr);
mlx_destroy_window(mlx_ptr, win_ptr);
```

## 💡 Bonnes Pratiques

1. **Performance**
   - Préférer l'utilisation d'images plutôt que `mlx_pixel_put`
   - Dessiner dans une image puis l'afficher d'un coup
   - Éviter de recréer/détruire des images fréquemment

2. **Mémoire**
   - Toujours libérer les ressources (images, fenêtres)
   - Vérifier les retours des fonctions mlx

3. **Organisation**
   - Utiliser une structure pour regrouper les pointeurs mlx
   - Gérer proprement les erreurs d'initialisation

## 🔍 Structure Recommandée
```c
typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    // Autres variables nécessaires
} t_data;
```

## ⚠️ Points d'Attention
1. La MinilibX n'est pas thread-safe
2. Les coordonnées (0,0) sont en haut à gauche
3. Les images sont plus rapides que pixel_put
4. Toujours vérifier les valeurs de retour des fonctions

### Pour compiler un test :
```bash
gcc test.c -I[chemin_vers_mlx] -L[chemin_vers_mlx] -lmlx -lXext -lX11
```
### lexique fonctions :
Je vais grouper et expliquer les principales fonctions de la MinilibX par catégories :

1. **Initialisation et Fenêtres** :
```c
mlx_init.c         // Initialise la connexion avec le serveur X
mlx_new_window.c   // Crée une nouvelle fenêtre
mlx_destroy_window.c // Ferme une fenêtre
mlx_clear_window.c   // Efface le contenu d'une fenêtre
```

2. **Gestion des Images** :
```c
mlx_new_image.c      // Crée une nouvelle image en mémoire
mlx_put_image_to_window.c // Affiche une image dans une fenêtre
mlx_destroy_image.c  // Libère la mémoire d'une image
mlx_get_data_addr.c  // Récupère l'adresse des données de l'image
```

3. **Gestion des Événements** :
```c
mlx_hook.c          // Gère les hooks (callbacks) pour les événements
mlx_mouse_hook.c    // Gère spécifiquement les événements souris
mlx_key_hook.c      // Gère spécifiquement les événements clavier
mlx_expose_hook.c   // Gère les événements d'exposition (redessiner)
mlx_loop_hook.c     // Fonction appelée en boucle (animation)
mlx_loop.c          // Boucle principale des événements
```

4. **Dessin et Couleurs** :
```c
mlx_pixel_put.c     // Dessine un pixel dans une fenêtre
mlx_string_put.c    // Affiche du texte dans une fenêtre
mlx_get_color_value.c // Convertit une couleur RGB
mlx_rgb.c           // Gestion des couleurs RGB
```

5. **Fonctions Internes** :
```c
mlx_int.h           // Header pour les fonctions internes
mlx_int_anti_resize_win.c // Gestion du redimensionnement
mlx_int_get_visual.c     // Gestion du visuel X11
mlx_int_param_event.c    // Gestion interne des événements
mlx_int_set_win_event_mask.c // Configuration des masques d'événements
mlx_int_str_to_wordtab.c // Utilitaire de parsing
mlx_int_wait_first_expose.c // Attente du premier affichage
```

6. **Fonctions Système X11** :
```c
mlx_xpm.c          // Gestion des images XPM
mlx_ext_randr.c    // Extension RandR pour X11
mlx_flush_event.c  // Vide la file d'événements
```

Les fonctions les plus importantes pour FDF sont :

1. **Pour commencer** :
```c
void *mlx_ptr = mlx_init();  // Initialisation
void *win_ptr = mlx_new_window(mlx_ptr, width, height, "FDF");  // Création fenêtre
```

2. **Pour dessiner** :
```c
void *img = mlx_new_image(mlx_ptr, width, height);  // Créer image
char *addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);  // Accès pixels
mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);  // Dessiner pixel
```

3. **Pour les événements** :
```c
mlx_hook(win_ptr, X_EVENT, X_MASK, fct, param);  // Gérer événements
mlx_loop(mlx_ptr);  // Lancer la boucle principale
```
Voici les principaux événements X11 avec leurs numéros et masques correspondants :

CLAVIER :
```c
2 = KeyPress       Masque: 1L<<0  // Touche pressée
3 = KeyRelease     Masque: 1L<<1  // Touche relâchée
```

SOURIS :
```c
4 = ButtonPress    Masque: 1L<<2  // Clic pressé
5 = ButtonRelease  Masque: 1L<<3  // Clic relâché
6 = MotionNotify   Masque: 1L<<6  // Mouvement souris
```

FENÊTRE :
```c
17 = DestroyNotify Masque: 1L<<17 // Fermeture fenêtre
12 = Expose        Masque: 1L<<15 // Fenêtre nécessite redessiner
```

Exemple d'utilisation dans FdF :
```c
// Gestion des touches pour rotation/zoom
mlx_hook(win, 2, 1L<<0, handle_key, &app);

// Gestion souris pour déplacement/zoom
mlx_hook(win, 4, 1L<<2, handle_mouse, &app);
mlx_hook(win, 6, 1L<<6, handle_mouse_move, &app);

// Gestion fermeture fenêtre
mlx_hook(win, 17, 1L<<17, handle_close, &app);

// Gestion du redessin
mlx_hook(win, 12, 1L<<15, handle_expose, &app);
```
## Project Structure

```mermaid
classDiagram
   class e_error {
       <<enumeration>>
       SUCCESS
       ERR_ARGS
       ERR_MALLOC
       ERR_DATA
       ERR_FILE
       ERR_FORMAT
       ERR_MLX
       DEBUG
   }

   class e_app_state {
       <<enumeration>>
       STATE_KILL
       STATE_INIT
       STATE_RUNNING
   }

   class u_color {
       <<union>>
       +int ref
       +unsigned char b
       +unsigned char g
       +unsigned char r
       +unsigned char a
       +set_color(r, g, b, a)
       +get_hex()
       +interpolate(color1, color2, factor)
   }

   class u_coord {
       <<union>>
       +int x
       +int y
       +int z
       +int coords[3]
       +set_coord(x, y, z)
       +normalize()
       +distance_to(coord)
   }

   class s_point {
       +t_coord original_pos
       +t_coord pos
       +t_color color
       +float elevation
       +update_elevation(z)
       +calculate_color()
       +reset_position()
       +transform(matrix)
   }

   class s_win {
       +void* mlx
       +void* win
       +void* img
       +void* addr
       +int w_scr
       +int h_scr
       +int w_win
       +int h_win
       +int bbp
       +int line_len
       +int endian
       +int mouse_x
       +int mouse_y
       +int mouse_pressed
       +init_window()
       +clear_window()
       +put_pixel(x, y, color)
       +draw_line(p1, p2)
       +handle_mouse_event()
       +handle_keyboard_event()
       +refresh_display()
   }

   class s_map {
       +t_point** points
       +float z_min
       +float z_max
       +float z_range
       +float z_scale
       +float center_x
       +float center_y
       +int color_mode
       +int is_iso
       +int w_map
       +int h_map
       +load_map(filename)
       +calculate_bounds()
       +normalize_heights()
       +apply_color_scheme()
       +draw_map()
       +cleanup_map()
   }

   class s_transform {
       +float angle_x
       +float angle_y
       +float angle_z
       +float scale
       +float shift_x
       +float shift_y
       +float zoom
       +float spacing
       +float iso_angle
       +int auto_rot
       +rotate_x(angle)
       +rotate_y(angle)
       +rotate_z(angle)
       +scale_points(factor)
       +translate(x, y)
       +toggle_auto_rotation()
       +update_transform()
   }

   class s_app {
       +t_map map
       +t_win win
       +t_transform transform
       +e_app_state state
       +int projection_mode
       +float altitude_factor
       +init_app()
       +run_app()
       +cleanup_app()
       +handle_events()
       +update_display()
       +toggle_projection()
   }

   s_app *-- s_map
   s_app *-- s_win
   s_app *-- s_transform
   s_app *-- e_app_state
   s_map *-- s_point
   s_point *-- u_coord
   s_point *-- u_color

   note for s_app "Hook points:
   - Custom event handlers
   - Additional rendering modes
   - New projection types"

   note for s_map "Hook points:
   - Custom file formats
   - New color schemes
   - Height modifiers"

   note for s_transform "Hook points:
   - New transformation types
   - Custom animations
   - Matrix operations"
   ```