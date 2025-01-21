# 🚀 Guide Complet des Redirections Shell

> "Dans le shell, tout est fichier, et chaque problème a sa redirection !" 😉

## 📚 Table des matières
1. [Redirections d'entrée (`<`)](#-redirections-simples-dentrée-)
2. [Redirections de sortie (`>`)](#-redirections-simples-de-sortie-)
3. [Redirections avec ajout (`>>`)](#-redirections-avec-ajout-)
4. [Combinaisons avec pipes (`|`)](#-combinaisons-avec-pipes-)
5. [Here-documents (heredoc)](#-here-documents-)
6. [Here-strings (`<<<`)](#-here-strings-)
7. [Descripteurs de fichiers](#-descripteurs-de-fichiers-)
8. [Process Substitution](#-process-substitution-)
9. [Pipes nommés (FIFO)](#-pipes-nommés-fifo-)
10. [Pièges et Solutions](#-pièges-et-solutions-)
11. [Bonnes Pratiques](#-bonnes-pratiques-)

## 🎯 Redirections simples d'entrée (`<`)

Voici les différentes façons de dire "lis ça" à bash :
```bash
# Lecture de fichier (choisissez votre style !)
cat < input.txt         # Style classique
< input.txt cat         # Style ninja

# Recherche avec grep
grep "motif" < fichier.txt     # Fouille dans ce fichier
< fichier.txt grep "motif"     # Même chose, autre style

# Comptage de lignes
wc -l < données.txt            # Combien de lignes ? 🤔
```

## 💾 Redirections simples de sortie (`>`)

Pour sauvegarder nos précieux résultats :
```bash
# Sauvegarde (attention, ça écrase !)
echo "Mon super texte" > sortie.txt
> sortie.txt echo "Mon super texte"

# Listing de répertoire
ls -l > listing.txt

# Capture des erreurs
grep "erreur" logs.txt > erreurs.txt
```

## 📝 Redirections avec ajout (`>>`)

Pour les collectionneurs qui ne veulent rien perdre :
```bash
# Ajout sans écraser (votre ami contre les "oups")
echo "une ligne de plus" >> log.txt
>> log.txt echo "une ligne de plus"

# Journalisation
date >> journal.txt

# Ajout multi-lignes
cat >> notes.txt << EOF
Note importante
À ne pas oublier
EOF
```

## 🔄 Combinaisons avec pipes (`|`)

La magie des pipes, où les commandes collaborent :
```bash
# Pipeline classique
< entrée.txt grep "motif" | sort > sortie.txt
grep "motif" < entrée.txt | sort > sortie.txt

# Chaîne de traitement
cat fichier.txt | grep "motif" | sort | uniq > résultat.txt
< fichier.txt grep "motif" | sort | uniq > résultat.txt

# Comptage avec redirection
< logs.txt grep "ERROR" | wc -l > nombre_erreurs.txt
```

## 📜 Here-documents (heredoc) 

La puissance des documents intégrés :
```bash
# Here-document basique (avec expansion de variables)
cat << EOF > config.txt
Serveur: $hostname
Port: 8080
EOF

# Here-document protégé (pas d'expansion)
cat << 'EOF' > script.sh
#!/bin/bash
echo "$1"
EOF

# Here-document indenté (-EOF)
cat <<-EOF > fichier.txt
    ligne 1
    ligne 2
EOF

# Here-document avec sudo
sudo tee /etc/conf.d/app.conf << EOF > /dev/null
config1=valeur1
config2=valeur2
EOF
```

## 🎮 Here-strings (`<<<`)

Pour les entrées rapides et directes :
```bash
# Lecture directe
read -r var <<< "valeur"

# Recherche dans une chaîne
grep "motif" <<< "texte à chercher"

# Boucle sur une sortie
while read -r ligne; do
    echo "-> $ligne"
done <<< "$(ls -l)"
```

## 🔧 Descripteurs de fichiers

Manipulation avancée des flux :
```bash
# Redirection séparée de stdout et stderr
commande > sortie.txt 2> erreurs.txt

# Tout dans le même fichier
commande &> tout.log            # Bash 4+
commande > tout.log 2>&1       # POSIX

# Redirection globale du script
exec 1> tout.log              # Redirige stdout
exec 2> erreurs.log          # Redirige stderr

# Descripteurs personnalisés
exec 3> fichier.log          # Ouvre un nouveau descripteur
echo "log" >&3              # Écrit via le descripteur
exec 3>&-                   # Ferme le descripteur
```

## 🎭 Process Substitution

Pour les manipulations avancées :
```bash
# Comparaison de sorties
diff <(ls dir1) <(ls dir2)

# Traitement en parallèle
while read ligne; do
    echo "Traitement: $ligne"
done < <(find . -type f)

# Fusion de flux triés
paste <(sort file1) <(sort file2)
```

## 🚰 Pipes nommés (FIFO)

Communication inter-process élégante :
```bash
# Création du pipe
mkfifo mon_pipe

# Écriture (en arrière-plan)
echo "données" > mon_pipe &

# Lecture
cat < mon_pipe

# Nettoyage
rm mon_pipe
```

## 🎯 Pièges et Solutions

Évitez les erreurs classiques :
```bash
# ❌ Ne marche PAS comme prévu
grep "erreur" fichier.txt > resultats.txt | wc -l

# ✅ Solution correcte
grep "erreur" fichier.txt | tee resultats.txt | wc -l

# Redirection silencieuse
commande &> /dev/null     # Bash 4+
commande > /dev/null 2>&1 # POSIX

# Debug avec tee
commande 2>&1 | tee log.txt
```

## 🌟 Bonnes Pratiques

1. **Organisation** 📋
   - Un style cohérent dans tout le script
   - Documentation claire des redirections complexes
   - Tests sur petits fichiers d'abord

2. **Sécurité** 🛡️
   - Toujours vérifier les permissions
   - Faire des backups avant d'écraser
   - Utiliser `set -e` pour arrêter sur erreur

3. **Performance** ⚡
   - Éviter les pipes inutiles
   - Préférer `&>` quand possible (Bash 4+)
   - Utiliser process substitution plutôt que temp files

4. **Maintenance** 🔧
   - Commenter les redirections complexes
   - Fermer les descripteurs personnalisés
   - Documenter les dépendances de version

## 📝 Notes Techniques

- **Descripteurs standard** :
  - 0️⃣ : stdin (entrée)
  - 1️⃣ : stdout (sortie)
  - 2️⃣ : stderr (erreurs)

- **Compatibilité** :
  - `&>` : Bash 4+
  - Process substitution : Bash/Zsh
  - Here-strings : Non POSIX

- **Limitations** :
  - Nombre max de descripteurs système
  - Mémoire pour here-documents
  - Blocage des FIFO

## 🎓 Conseils d'Expert

1. **Pour le debug** :
   ```bash
   set -x  # Active le mode debug
   trap 'echo "$BASH_COMMAND" failed' ERR
   ```

2. **Pour la performance** :
   ```bash
   # Préférez
   < fichier grep pattern
   # À
   cat fichier | grep pattern
   ```

3. **Pour la maintenance** :
   ```bash
   # Nommez vos descripteurs
   exec {logfile}>log.txt
   echo "log" >&$logfile
   ```

> "Un bon script shell est comme une recette de cuisine : il faut les bons ingrédients et le bon ordre !" 👨‍🍳

## 🎉 Conclusion

Les redirections shell sont puissantes mais demandent de la pratique. N'hésitez pas à expérimenter dans un environnement de test, et rappelez-vous : la documentation (`man bash`) est votre meilleure amie ! 

Happy scripting! 🚀
