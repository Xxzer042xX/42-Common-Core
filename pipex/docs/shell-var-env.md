# 📚 Aide-Mémoire Shell: Variables d'Environnement et Processus

## 🔍 Visualisation des Processus
```bash
# 1. Commandes de Base
ps                  # Processus du terminal actuel
ps aux             # TOUS les processus (détaillé)
ps -ef             # Format standard Unix
top                # Vue dynamique des processus
htop               # Version améliorée de top (si installé)

# 2. Visualisation Arborescente
ps --forest        # Arbre des processus
pstree             # Arbre élégant
pstree -p          # Avec PIDs
pstree -a          # Avec arguments complets

# 3. Informations Spécifiques
ps -f $$           # Info sur shell actuel
echo $$            # PID du shell actuel
echo $?            # Code retour dernière commande
ps -u $USER        # Vos processus
```

## 📊 Gestion des Tâches (Jobs)
```bash
# 1. Contrôle des Tâches
command &          # Lancer en arrière-plan
jobs               # Liste des tâches en cours
fg %1             # Mettre tâche 1 au premier plan
bg %1             # Mettre tâche 1 en arrière-plan
kill %1           # Terminer tâche 1

# 2. Raccourcis Clavier
Ctrl + Z          # Suspendre processus actuel
Ctrl + C          # Arrêter processus actuel
```

## 🌍 Variables d'Environnement
```bash
# 1. Affichage
env                # Liste toutes les variables
printenv           # Alternative à env
echo $VARIABLE     # Voir une variable spécifique
set               # Toutes les variables (incluant locales)

# 2. Création et Modification
export NOM="valeur"     # Créer variable exportée
NOM="valeur"           # Variable locale (non exportée)
export PATH="$PATH:/nouveau/chemin"  # Ajouter au PATH

# 3. Suppression
unset VARIABLE     # Supprimer une variable
env -i bash        # Shell avec env minimal

# 4. Variables Spéciales
echo $HOME         # Dossier personnel
echo $USER         # Nom utilisateur
echo $SHELL        # Shell actuel
echo $PWD          # Dossier actuel
echo $OLDPWD       # Dossier précédent
```

## 🔧 Commandes de Débogage
```bash
# 1. Debug Shell
set -x            # Active trace des commandes
set +x            # Désactive trace
set -e            # Sort si erreur
set -v            # Montre ligne avant exécution

# 2. Traçage
strace ./prog     # Trace appels système
ltrace ./prog     # Trace appels bibliothèque

# 3. Redirection Debug
command 2>debug.log     # Erreurs vers fichier
command 2>&1           # Erreurs vers sortie standard
```

## 📍 Navigation et Localisation
```bash
# 1. Navigation
pwd                # Dossier actuel
cd -               # Retour dossier précédent
pushd /chemin      # Empile et change dossier
popd               # Retour dossier empilé

# 2. Localisation Commandes
which cmd          # Chemin de la commande
whereis cmd        # Trouve binaires/sources/man
type cmd           # Type de commande (alias, built-in, etc.)

# 3. Chemins
echo $PATH         # Liste chemins de recherche
echo $PATH | tr ':' '\n'  # Format lisible
```

## 🛠️ Manipulation des Shells
```bash
# 1. Gestion des Shells
echo $SHELL        # Shell par défaut
bash              # Ouvrir nouveau bash
exit              # Quitter shell actuel
exec bash         # Remplacer shell actuel

# 2. Information Shell
echo $0           # Nom du shell
echo $BASH_VERSION # Version de bash
```

## 💡 Astuces Pratiques
```bash
# 1. Alias Utiles
alias ll='ls -la'
alias path='echo $PATH | tr ":" "\n"'
alias envs='env | sort'

# 2. Valeurs par Défaut
${VAR:-defaut}    # Utilise 'defaut' si VAR vide/non définie
${VAR:=defaut}    # Assigne 'defaut' si VAR vide/non définie

# 3. Test Variables
[ -z "$VAR" ]     # Vrai si VAR vide
[ -n "$VAR" ]     # Vrai si VAR non vide
```

## ⚠️ Bonnes Pratiques
1. Toujours encadrer les variables par guillemets : `"$VAR"`
2. Utiliser `export` uniquement quand nécessaire
3. Nettoyer les variables temporaires avec `unset`
4. Documenter les variables importantes
5. Préférer les variables locales quand possible

## 🎯 Exemples Pratiques
```bash
# 1. Créer variable temporaire
TEMP_VAR="test" ./script.sh

# 2. Voir processus par utilisateur
ps -u $USER --forest

# 3. Variables en lecture seule
declare -r CONSTANTE="valeur"

# 4. Debug script
bash -x ./script.sh

# 5. Environnement personnalisé
env -i HOME=$HOME PATH=$PATH bash
```