#!/bin/bash

# ========== CONFIGURATION ==========
SHELL_EXEC="./hsh"  # Nom de ton shell compilé
TMPDIR="./test_tmp"
mkdir -p "$TMPDIR"

# ========== VÉRIFICATION ==========
if [ ! -x "$SHELL_EXEC" ]; then
    echo -e "\033[0;31m❌ Shell not found or not executable: $SHELL_EXEC\033[0m"
    exit 1
fi

# ========== COULEURS ==========
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# ========== STATISTIQUES ==========
total=0
passed=0

echo "Running tests on shell: $SHELL_EXEC"
echo

# ========== FONCTION DE TEST ==========
run_test() {
    ((total++))
    test_name="$1"
    shift
    bash -c "$@" > "$TMPDIR/out.log" 2>&1
    result=$?
    if [ "$result" -eq 0 ]; then
        echo -e "${GREEN}✅ $test_name${NC}"
        ((passed++))
    else
        echo -e "${RED}❌ $test_name${NC}"
        echo "--- Output ---"
        cat "$TMPDIR/out.log"
        echo "--------------"
    fi
}

# ========== TESTS ==========

run_test "Multiple ls with temporary file" "
tmp_file=\"checker_tmp_file_\$RANDOM\"
output_file=\"$TMPDIR/output.txt\"
touch \"\$tmp_file\"

command=\"ls \$tmp_file
ls \$tmp_file
ls \$tmp_file
ls \$tmp_file
ls \$tmp_file\"

echo \"\$command\" | $SHELL_EXEC > \"\$output_file\" 2>/dev/null
nmatch=\$(grep -c \"\$tmp_file\" \"\$output_file\")
rm -f \"\$tmp_file\" \"\$output_file\"
[ \"\$nmatch\" -eq 5 ]
"

run_test "Invalid command returns error" "
echo \"thiscommanddoesnotexist\" | $SHELL_EXEC > \"$TMPDIR/out\" 2>&1
grep -qi \"not found\" \"$TMPDIR/out\"
"

run_test "exit 42 returns correct exit code" "
echo \"exit 42\" | $SHELL_EXEC > /dev/null 2>&1
[ \$? -eq 42 ]
"

run_test "Chained echo commands" "
echo -e \"echo Hello\\necho World\" | $SHELL_EXEC > \"$TMPDIR/out\" 2>&1
grep -q \"Hello\" \"$TMPDIR/out\" && grep -q \"World\" \"$TMPDIR/out\"
"

run_test "env command includes PATH" "
echo \"env\" | $SHELL_EXEC > \"$TMPDIR/out\" 2>/dev/null
grep -q \"^PATH=\" \"$TMPDIR/out\"
"

# ========== RÉSUMÉ FINAL ==========

echo
echo "========= TEST SUMMARY ========="
echo -e "Passed: ${GREEN}$passed${NC}/$total | Failed: ${RED}$((total - passed))${NC}/$total"
echo "================================"

# Nettoyage
rm -rf "$TMPDIR"

# Code de retour global
[ "$passed" -eq "$total" ]
exit $?