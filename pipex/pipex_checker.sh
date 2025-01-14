#!/bin/bash
# Couleurs pour une meilleure lisibilité
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Création des fichiers de test
echo "Bonjour le monde" > infile.txt
echo "Test 123" >> infile.txt
echo "Pipeline test" >> infile.txt

echo -e "${BLUE}=== Contenu du fichier d'entrée ====${NC}"
cat infile.txt
echo "----------------------------------------"

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

# Tests basiques (pipex)
echo "=== Test 1: cat et grep ==="
echo "Shell command: < infile.txt cat | grep le > outfile_shell.txt"
< infile.txt cat | grep "le" > outfile_shell.txt
./bin/pipex infile.txt "cat" "grep le" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

echo "=== Test 2: cat et wc ==="
echo "Shell command: < infile.txt cat | wc -l > outfile_shell.txt"
< infile.txt cat | wc -l > outfile_shell.txt
./bin/pipex infile.txt "cat" "wc -l" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

echo "=== Test 3: grep et wc ==="
echo "Shell command: < infile.txt grep test | wc -w > outfile_shell.txt"
< infile.txt grep "test" | wc -w > outfile_shell.txt
./bin/pipex infile.txt "grep test" "wc -w" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Tests avec des commandes plus complexes
echo "=== Test 4: sed et tr ==="
echo "Shell command: < infile.txt sed s/test/TEST/ | tr [:lower:] [:upper:] > outfile_shell.txt"
< infile.txt sed "s/test/TEST/" | tr "[:lower:]" "[:upper:]" > outfile_shell.txt
./bin/pipex infile.txt "sed s/test/TEST/" "tr [:lower:] [:upper:]" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Tests avec des cas d'erreur (redirection des erreurs vers /dev/null)
echo "=== Test d'erreur 1: Commande invalide ==="
echo "Shell command: < infile.txt invalidcmd | wc -l > outfile_shell.txt"
(< infile.txt invalidcmd 2>/dev/null | wc -l > outfile_shell.txt) 2>/dev/null
status_shell=$?
./bin/pipex infile.txt "invalidcmd" "wc -l" outfile_pipex.txt 2>/dev/null
status_pipex=$?
show_files
echo -e "${YELLOW}Status de sortie shell: ${status_shell}${NC}"
echo -e "${YELLOW}Status de sortie pipex: ${status_pipex}${NC}"
echo "Test de gestion d'erreur effectué"
[ $status_shell -ne 0 ] && [ $status_pipex -ne 0 ]
print_result

echo "=== Test d'erreur 2: Fichier d'entrée inexistant ==="
echo "Shell command: < nonexistent.txt cat | wc -l > outfile_shell.txt"
(< nonexistent.txt cat 2>/dev/null | wc -l > outfile_shell.txt) 2>/dev/null
status_shell=$?
./bin/pipex nonexistent.txt "cat" "wc -l" outfile_pipex.txt 2>/dev/null
status_pipex=$?
show_files
echo -e "${YELLOW}Status de sortie shell: ${status_shell}${NC}"
echo -e "${YELLOW}Status de sortie pipex: ${status_pipex}${NC}"
echo "Test de gestion d'erreur effectué"
[ $status_shell -ne 0 ] && [ $status_pipex -ne 0 ]
print_result

# Tests supplémentaires
echo "=== Test 5: head et tail ==="
echo "Shell command: < infile.txt head -n 2 | tail -n 1 > outfile_shell.txt"
< infile.txt head -n 2 | tail -n 1 > outfile_shell.txt
./bin/pipex infile.txt "head -n 2" "tail -n 1" outfile_pipex.txt
show_files
diff outfile_shell.txt outfile_pipex.txt
print_result

# Test bonus si disponible
if [ -f "./bin/pipex_bonus" ]; then
    echo "=== Test Bonus: Multiple Pipes ==="
    echo "Shell command: < infile.txt cat | grep test | tr [:lower:] [:upper:] > outfile_shell.txt"
    < infile.txt cat | grep "test" | tr "[:lower:]" "[:upper:]" > outfile_shell.txt
    ./bin/pipex_bonus infile.txt "cat" "grep test" "tr [:lower:] [:upper:]" outfile_pipex.txt
    show_files
    diff outfile_shell.txt outfile_pipex.txt
    print_result
fi

# Nettoyage
echo -e "${BLUE}=== Nettoyage des fichiers de test ===${NC}"
rm -f infile.txt outfile_shell.txt outfile_pipex.txt
