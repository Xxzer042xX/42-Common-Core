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

# Création des fichiers de test
echo "Bonjour le monde" > infile.txt
echo "Test 123" >> infile.txt
echo "Pipeline test" >> infile.txt
echo "HELLO WORLD" >> infile.txt
echo "test again" >> infile.txt

echo -e "${BLUE}=== Contenu du fichier d'entrée ====${NC}"
cat infile.txt
echo "----------------------------------------"

# Test 1: Triple pipe
echo "=== Test 1: Triple pipe (cat | grep | tr) ==="
echo "Shell command: < infile.txt cat | grep test | tr [:lower:] [:upper:] > outfile_shell.txt"
< infile.txt cat | grep test | tr '[:lower:]' '[:upper:]' > outfile_shell.txt
./bin/pipex_bonus infile.txt "cat" "grep test" "tr [:lower:] [:upper:]" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage avant le prochain test
rm -f outfile_shell.txt outfile_pipex.txt

# Test 2: Quadruple pipe
echo "=== Test 2: Quadruple pipe (cat | grep | sed | tr) ==="
echo "Shell command: < infile.txt cat | grep test | sed s/test/TEST/ | tr [:lower:] [:upper:] > outfile_shell.txt"
< infile.txt cat | grep test | sed 's/test/TEST/' | tr '[:lower:]' '[:upper:]' > outfile_shell.txt
./bin/pipex_bonus infile.txt "cat" "grep test" "sed s/test/TEST/" "tr [:lower:] [:upper:]" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage avant here_doc tests
rm -f outfile_shell.txt outfile_pipex.txt

# Test 3: Here_doc simple
echo "=== Test 3: Here_doc simple ==="
# Test shell
cat > expected_input.txt << EOL
hello world
test line
last line
EOL
cat expected_input.txt | tr '[:lower:]' '[:upper:]' > outfile_shell.txt

# Test pipex_bonus
./bin/pipex_bonus here_doc EOL "cat" "tr [:lower:] [:upper:]" outfile_pipex.txt << EOL
hello world
test line
last line
EOL

show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage
rm -f outfile_shell.txt outfile_pipex.txt

# Test 4: Here_doc avec grep
echo "=== Test 4: Here_doc avec grep et tr ==="
# Test shell
cat > expected_input.txt << LIMITER
first line
middle test
last line
test line
LIMITER
cat expected_input.txt | grep line | tr '[:lower:]' '[:upper:]' > outfile_shell.txt

# Test pipex_bonus
./bin/pipex_bonus here_doc LIMITER "grep line" "tr [:lower:] [:upper:]" outfile_pipex.txt << LIMITER
first line
middle test
last line
test line
LIMITER

show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage
rm -f outfile_shell.txt outfile_pipex.txt

# Test 5: Multiple pipes avec commandes complexes
echo "=== Test 5: Multiple pipes avec commandes complexes ==="
echo "Shell command: < infile.txt grep test | sed s/test/CHECK/ | tr [:lower:] [:upper:] | wc -l > outfile_shell.txt"
< infile.txt grep test | sed 's/test/CHECK/' | tr '[:lower:]' '[:upper:]' | wc -l > outfile_shell.txt
./bin/pipex_bonus infile.txt "grep test" "sed s/test/CHECK/" "tr [:lower:] [:upper:]" "wc -l" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Nettoyage
rm -f outfile_shell.txt outfile_pipex.txt

# Test 6: Here_doc avec commande invalide
echo "=== Test 6: Here_doc avec commande invalide ==="
# Test shell
cat > expected_input.txt << ENDING
test line
ENDING
(cat expected_input.txt | invalidcmd > outfile_shell.txt) 2>/dev/null
status_shell=$?

# Test pipex_bonus
./bin/pipex_bonus here_doc ENDING "invalidcmd" "cat" outfile_pipex.txt << ENDING
test line
ENDING
status_pipex=$?

show_files
echo -e "${YELLOW}Status de sortie shell: ${status_shell}${NC}"
echo -e "${YELLOW}Status de sortie pipex: ${status_pipex}${NC}"
if [ $status_pipex -ne 0 ]; then
    echo -e "${GREEN}✓ Test passé${NC}"
else
    echo -e "${RED}✗ Test échoué${NC}"
fi
echo "----------------------------------------"

# Nettoyage final
echo -e "${BLUE}=== Nettoyage des fichiers de test ===${NC}"
rm -f infile.txt outfile_shell.txt outfile_pipex.txt expected_input.txt