#!/bin/bash
# Couleurs pour une meilleure lisibilité
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Fonction pour afficher les résultats
print_result() {
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ Test passé${NC}"
    else
        echo -e "${RED}✗ Test échoué${NC}"
    fi
    echo "----------------------------------------"
}

# Fonction pour afficher le contenu des fichiers
show_files() {
    echo -e "${YELLOW}Contenu de outfile_shell.txt:${NC}"
    cat outfile_shell.txt
    echo -e "\n${YELLOW}Contenu de outfile_pipex.txt:${NC}"
    cat outfile_pipex.txt
    echo "----------------------------------------"
}

# Nettoyage initial
rm -f infile.txt outfile_shell.txt outfile_pipex.txt

# Création d'un fichier de test avec des données tabulées
echo -e "Name\tAge\tCity" > infile.txt
echo -e "John\t25\tParis" >> infile.txt
echo -e "Alice\t30\tLyon" >> infile.txt
echo -e "Bob\t22\tNice" >> infile.txt
echo -e "Eve\t28\tParis" >> infile.txt

echo -e "${BLUE}=== Contenu du fichier d'entrée ====${NC}"
cat infile.txt
echo "----------------------------------------"

# Test 1: awk avec sélection de colonne simple
echo "=== Test 1: awk print première colonne ==="
echo "Shell command: < infile.txt awk '{print \$1}' | sort > outfile_shell.txt"
< infile.txt awk '{print $1}' | sort > outfile_shell.txt
./bin/pipex_bonus infile.txt 'awk "{print \$1}"' "sort" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage
rm -f outfile_shell.txt outfile_pipex.txt

# Test 2: awk avec condition
echo "=== Test 2: awk avec filtrage sur ville ==="
echo "Shell command: < infile.txt awk '\$3==\"Paris\" {print \$1,\$2}' | tr [:lower:] [:upper:] > outfile_shell.txt"
< infile.txt awk '$3=="Paris" {print $1,$2}' | tr '[:lower:]' '[:upper:]' > outfile_shell.txt
./bin/pipex_bonus infile.txt 'awk "\$3==\"Paris\" {print \$1,\$2}"' "tr [:lower:] [:upper:]" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage
rm -f outfile_shell.txt outfile_pipex.txt

# Test 3: awk avec calcul simple
echo "=== Test 3: awk avec somme ==="
echo "Shell command: < infile.txt awk '{sum+=\$2} END {print sum}' > outfile_shell.txt"
< infile.txt awk '{sum+=$2} END {print sum}' > outfile_shell.txt
./bin/pipex_bonus infile.txt 'awk "{sum+=\$2} END {print sum}"' "cat" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Test 4: cut et grep simple
echo "=== Test 4: cut et grep ==="
echo "Shell command: < infile.txt cut -f1 | grep 'e' > outfile_shell.txt"
< infile.txt cut -f1 | grep 'e' > outfile_shell.txt
./bin/pipex_bonus infile.txt "cut -f1" "grep e" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Test 5: here_doc avec commande simple
echo "=== Test 5: here_doc avec sort ==="
# Test shell
cat << LIMIT | sort > outfile_shell.txt
John
Alice
Bob
LIMIT

# Test pipex_bonus
./bin/pipex_bonus here_doc LIMIT "cat" "sort" outfile_pipex.txt << LIMIT
John
Alice
Bob
LIMIT

show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage final
echo -e "${BLUE}=== Nettoyage des fichiers de test ===${NC}"
rm -f infile.txt outfile_shell.txt outfile_pipex.txt