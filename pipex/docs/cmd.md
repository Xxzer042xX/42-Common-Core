Voici d'autres commandes bash utiles, certaines plus spécialisées :

**Gestion de fichiers avancée :**
- `xxd` : Affichage/manipulation hexadécimale
  ```bash
  xxd fichier.bin            # affiche en hexa
  xxd -b fichier            # affiche en binaire
  xxd -p fichier            # format hexadécimal pur
  ```

- `od` : Dump octal ou autres formats
  ```bash
  od -x fichier             # affichage hexadécimal
  od -c fichier            # affichage caractères
  ```

- `hexdump` : Autre outil d'affichage hexa
  ```bash
  hexdump -C fichier       # affiche hexa + ASCII
  ```

**Traitement de données :**
- `column` : Formater en colonnes
  ```bash
  column -t fichier.txt    # aligne en colonnes
  column -s";" -t data.csv # spécifie séparateur
  ```

- `comm` : Compare fichiers triés
  ```bash
  comm file1 file2         # compare ligne par ligne
  comm -12 file1 file2     # lignes uniques
  ```

**Manipulation de texte avancée :**
- `expand` / `unexpand` : Gestion des tabulations
  ```bash
  expand fichier.txt       # convertit tabs en espaces
  unexpand -a fichier.txt  # espaces en tabs
  ```

- `fmt` : Formater du texte
  ```bash
  fmt -w 60 fichier.txt    # limite largeur à 60 caractères
  fmt -u fichier.txt       # unifie les espaces
  ```

**Utilitaires système :**
- `timeout` : Limite temps d'exécution
  ```bash
  timeout 5s commande      # arrête après 5 secondes
  ```

- `time` : Mesure temps d'exécution
  ```bash
  time commande            # statistiques de temps
  ```

- `yes` : Répète une chaîne
  ```bash
  yes "message"           # répète indéfiniment
  yes "y" | commande     # automatise les confirmations
  ```

**Analyse de données :**
- `tsort` : Tri topologique
  ```bash
  tsort fichier           # tri les dépendances
  ```

- `nl` : Numérotation des lignes
  ```bash
  nl fichier.txt          # numérote les lignes
  nl -ba fichier.txt      # numérote même lignes vides
  ```

**Sécurité :**
- `sha256sum`, `md5sum`, etc : Hachage
  ```bash
  sha256sum fichier       # calcule hash SHA256
  md5sum fichier          # calcule hash MD5
  ```

**Divers :**
- `rev` : Inverse les caractères
  ```bash
  echo "Hello" | rev      # affiche "olleH"
  ```

- `look` : Recherche mots commençant par
  ```bash
  look pre               # mots commençant par "pre"
  ```

- `fold` : Wrapper de texte
  ```bash
  fold -w 80 fichier     # limite largeur à 80 caractères
  ```

Ces commandes sont moins connues mais peuvent être très utiles dans des situations spécifiques. Elles sont particulièrement puissantes quand on les combine avec les commandes plus classiques via des pipes.
