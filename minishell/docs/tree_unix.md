# Guide Complet de l'Arborescence Linux

## Introduction pour Débutants
Avant de plonger dans les détails, comprendre quelques concepts de base :

1. Tout est fichier sous Linux
2. L'arborescence commence à la racine (/)
3. La casse est importante (sensitive)
4. Les points (.) sont importants :
   - `.` : Répertoire courant
   - `..` : Répertoire parent
   - Les fichiers commençant par `.` sont cachés

## Comprendre les Liens Symboliques
- Un lien symbolique est comme un raccourci
- Notation: `dossier -> destination`
- Exemple: `/bin -> /usr/bin`
- Commande pour créer: `ln -s destination nom_du_lien`

## Structure Visuelle de Base
```
/ (racine)
├── bin/ → /usr/bin
├── boot/
├── dev/
├── etc/
├── home/
│   ├── user1/
│   └── user2/
├── lib/ → /usr/lib
├── media/
├── mnt/
├── opt/
├── proc/
├── root/
├── run/
├── sbin/ → /usr/sbin
├── tmp/
├── usr/
└── var/
```

## Commandes Essentielles pour Explorer
```bash
pwd                     # Voir où vous êtes
ls -la                  # Lister tout avec détails
cd /chemin             # Changer de répertoire
du -sh /*              # Voir taille des dossiers
df -h                  # Voir espace disque
tree -L 1 /           # Voir arborescence niveau 1
stat fichier          # Voir détails d'un fichier
lsblk                 # Voir les disques
mount                 # Voir les montages
```

# Détail des Répertoires

## / (Root Directory)
Permission standard: `drwxr-xr-x` (755)
Le répertoire racine du système.

**Points Importants pour Débutants:**
- Tout commence ici
- Nécessite des droits root pour modifier
- Contient tous les autres répertoires

**Commandes Utiles:**
```bash
ls -la /              # Voir contenu racine
sudo ls -la /         # Si certains accès sont refusés
df -h /              # Voir espace disque racine
```

[Suite du document précédent avec ajouts similaires pour chaque section...]

## Guide des Permissions Détaillé

### Comprendre les Permissions
```
d rwx r-x r-x
│ │   │   └── Autres (others)
│ │   └────── Groupe (group)
│ └────────── Propriétaire (user)
└──────────── Type (d=directory, -=fichier, l=lien)
```

### Valeurs Numériques
```
r (read)    = 4
w (write)   = 2
x (execute) = 1

Exemples:
7 = rwx (4+2+1)
6 = rw- (4+2)
5 = r-x (4+1)
4 = r-- (4)
```

### Commandes de Gestion des Permissions
```bash
chmod 755 fichier     # Changer permissions (numérique)
chmod u+x fichier     # Ajouter exécution pour user
chown user:group fichier  # Changer propriétaire
stat fichier         # Voir toutes les permissions
```

## FAQ pour Débutants

### Q: Pourquoi je ne peux pas modifier certains fichiers ?
R: Les fichiers système nécessitent des droits administrateur (sudo) pour être modifiés. C'est une mesure de sécurité.

### Q: Quelle différence entre /bin et /sbin ?
R: /bin contient les commandes essentielles pour tous les utilisateurs, /sbin contient les commandes système pour l'administrateur.

### Q: Où installer mes programmes ?
R: 
- Programmes personnels: /home/user/bin
- Programmes système: via gestionnaire de paquets
- Programmes compilés manuellement: généralement /usr/local

### Q: Où sont mes fichiers personnels ?
R: Dans /home/votre_username/

## Bonnes Pratiques

1. **Sécurité**
   - Ne jamais donner 777 aux permissions
   - Faire attention aux fichiers sensibles dans /etc
   - Toujours faire des sauvegardes avant modifications

2. **Organisation**
   - Garder les fichiers personnels dans /home
   - Utiliser /tmp pour les fichiers temporaires
   - Respecter les conventions de nommage

3. **Maintenance**
   - Surveiller l'espace disque régulièrement
   - Nettoyer /tmp et /var/log périodiquement
   - Faire des backups réguliers

## Points de Vigilance

### À ne pas modifier sans précaution :
- /etc/passwd
- /etc/shadow
- /boot/*
- Les fichiers de configuration système

### Répertoires à surveiller :
- /var/log (logs qui grandissent)
- /tmp (fichiers temporaires)
- /home (espace utilisateur)

## Ressources Additionnelles
- man hier : Manuel de la hiérarchie
- man file : Types de fichiers
- man chmod : Gestion des permissions
- man chown : Gestion des propriétaires























# Arborescence Standard Linux

## / (Root Directory)
Permission standard: `drwxr-xr-x` (755)
Le répertoire racine du système. Contient tous les autres répertoires.

### /bin
Permission standard: `drwxr-xr-x` (755)
- Contient les exécutables essentiels du système
- Commandes basiques utilisables par tous les utilisateurs
- Exemples: ls, cp, mv, rm, cat, chmod
- Souvent un lien symbolique vers /usr/bin sur les systèmes modernes

### /boot
Permission standard: `drwxr-xr-x` (755)
- Fichiers nécessaires au démarrage du système
- Noyau Linux (vmlinuz)
- Initial RAM disk (initrd)
- Configuration du bootloader (GRUB)
- Ne doit pas être modifié sans précaution

### /dev
Permission standard: `drwxr-xr-x` (755)
- Fichiers spéciaux représentant les périphériques
- Géré automatiquement par udev
- Contenu important:
  - /dev/sda, /dev/sdb : Disques durs
  - /dev/random, /dev/urandom : Générateurs de nombres aléatoires
  - /dev/null : "Trou noir" système
  - /dev/zero : Source de zéros
  - /dev/tty : Terminaux

### /etc
Permission standard: `drwxr-xr-x` (755)
- Fichiers de configuration système
- Contenu important:
  - /etc/passwd : Base de données des utilisateurs
  - /etc/shadow : Mots de passe cryptés
  - /etc/fstab : Configuration du montage des systèmes de fichiers
  - /etc/hosts : Résolution de noms d'hôtes
  - /etc/ssh : Configuration SSH
  - /etc/network : Configuration réseau

### /home
Permission standard: `drwxr-xr-x` (755)
Répertoires personnels des utilisateurs
- Chaque utilisateur a son propre dossier: /home/username
- Permission standard des dossiers utilisateurs: `drwxr-xr-x` (755)
- Contient les fichiers de configuration personnels (.bashrc, .profile)

### /lib, /lib32, et /lib64
Permission standard: `drwxr-xr-x` (755)
- Bibliothèques partagées essentielles
- Modules du noyau dans /lib/modules
- Support multiarchitecture
- /lib -> /usr/lib : Bibliothèques 32 bits sur systèmes 32 bits ou bibliothèques 64 bits sur systèmes 64 bits
- /lib32 -> /usr/lib32 : Bibliothèques 32 bits sur systèmes 64 bits
- /lib64 -> /usr/lib64 : Bibliothèques 64 bits

### /lost+found
Permission standard: `drwx------` (700)
- Utilisé par fsck pour stocker les fichiers récupérés
- Un répertoire par système de fichiers
- Normalement vide sauf après une récupération

### /snap
Permission standard: `drwxr-xr-x` (755)
- Utilisé par le système de paquets Snap
- Contient les applications installées via Snap
- Spécifique aux distributions utilisant Snap (comme Ubuntu)

Le fichier swapfile :
- Permission standard: `-rw-------` (600)
- Utilisé comme mémoire virtuelle
- Généralement situé à la racine
- Taille variable selon la configuration système

### /media
Permission standard: `drwxr-xr-x` (755)
- Point de montage pour les périphériques amovibles
- Clés USB, CD-ROM, disques externes
- Géré automatiquement par le système

### /mnt
Permission standard: `drwxr-xr-x` (755)
- Point de montage temporaire
- Utilisé pour le montage manuel de systèmes de fichiers

### /opt
Permission standard: `drwxr-xr-x` (755)
- Logiciels optionnels
- Applications tierces complètes
- Chaque application dans son propre sous-répertoire

### /proc
Permission standard: `dr-xr-xr-x` (555)
- Système de fichiers virtuel
- Informations sur les processus et le système
- Contenu important:
  - /proc/cpuinfo : Information sur le CPU
  - /proc/meminfo : État de la mémoire
  - /proc/version : Version du noyau
  - /proc/[PID] : Information sur les processus

### /root
Permission standard: `drwx------` (700)
- Répertoire personnel de l'administrateur (root)
- Très restrictif en termes de permissions

### /run
Permission standard: `drwxr-xr-x` (755)
- Données d'exécution temporaires
- Vidé au redémarrage
- PID files, locks, etc.

### /sbin
Permission standard: `drwxr-xr-x` (755)
- Commandes système essentielles
- Utilisé principalement par l'administrateur
- Souvent un lien symbolique vers /usr/sbin

### /srv
Permission standard: `drwxr-xr-x` (755)
- Données des services hébergés
- Sites web, FTP, etc.

### /sys
Permission standard: `drwxr-xr-x` (755)
- Système de fichiers virtuel sysfs
- Interface avec le noyau
- Information sur le matériel

### /tmp
Permission standard: `drwxrwxrwt` (1777)
- Fichiers temporaires
- Vidé au redémarrage
- Accessible en écriture par tous les utilisateurs

### /usr
Permission standard: `drwxr-xr-x` (755)
- Hiérarchie secondaire
- Contenu important:
  - /usr/bin : Commandes utilisateurs
  - /usr/sbin : Commandes système
  - /usr/lib : Bibliothèques
  - /usr/share : Données partagées
  - /usr/local : Logiciels installés localement
  - /usr/include : Headers C

### /var
Permission standard: `drwxr-xr-x` (755)
- Données variables
- Contenu important:
  - /var/log : Logs système
  - /var/mail : Boîtes mail
  - /var/spool : Files d'attente
  - /var/www : Fichiers web
  - /var/cache : Données de cache

## Notes sur les Permissions

Les permissions sont représentées sous deux formats:
1. Symbolique: `drwxr-xr-x`
   - d : type (directory)
   - rwx : droits utilisateur (read/write/execute)
   - r-x : droits groupe
   - r-x : droits autres

2. Numérique: 755
   - 7 (rwx) : droits utilisateur
   - 5 (r-x) : droits groupe
   - 5 (r-x) : droits autres

Les permissions spéciales:
- SUID (4000): Exécution avec les droits du propriétaire
- SGID (2000): Exécution avec les droits du groupe
- Sticky bit (1000): Protection des fichiers dans les répertoires partagés