#!/bin/bash

SHELL_PROG="./hsh"
RESULTS="results.log"
CMD_COUNT=1

echo "---- TEST Simple Shell ----" > "$RESULTS"

run_test() {
	cmd="$1"
	expected="$2"
	msg="$3"

	output=$(echo "$cmd" | $SHELL_PROG 2>&1)
	status=$?

	echo "[$CMD_COUNT] $cmd" >> "$RESULTS"
	echo "$output" >> "$RESULTS"
	echo "Exit: $status" >> "$RESULTS"
	echo >> "$RESULTS"

	if [ "$status" -eq "$expected" ]; then
		echo "✅ [$CMD_COUNT] $msg"
	else
		echo "❌ [$CMD_COUNT] $msg (got $status, expected $expected)"
	fi
	CMD_COUNT=$((CMD_COUNT + 1))
    
}

### TESTS ###

# 1. Command found via PATH
run_test "/bin/ls" 0 "Command /bin/ls should work (found, executable)"

# 2. Relative path (executable exists)
echo -e '#!/bin/sh\necho hello' > ./mytest
chmod +x ./mytest
run_test "./mytest" 0 "Relative path ./mytest (executable)"

# 3. Relative path (file exists but no exec permission)
chmod -x ./mytest
run_test "./mytest" 126 "Relative path ./mytest (permission denied)"

# 4. Relative path (file does not exist)
rm -f ./mytest
run_test "./mytest" 127 "Relative path ./mytest (not found)"

# 5. Command not found in PATH
run_test "thisdoesnotexist" 127 "Nonexistent command in PATH"

# 6. Command in PATH but not executable
mkdir -p testbin
echo 'echo fake' > testbin/fakecmd
chmod -rwx testbin/fakecmd
export PATH="$PWD/testbin:$PATH"
run_test "fakecmd" 126 "Command in PATH but not executable"

# 7. Valid PATH command
echo -e '#!/bin/sh\necho okay' > testbin/okcmd
chmod +x testbin/okcmd
run_test "okcmd" 0 "Valid PATH command (executable, found)"

echo "===> Test: PATH is unset"
unset PATH
./hsh << EOF
ls
EOF
echo "Exit status: $?"

echo "===> Test: PATH is empty"
PATH=""
./hsh << EOF
ls
EOF
echo "Exit status: $?"

# Cleanup
rm -rf testbin mytest

echo "---- DONE ----" >> "$RESULTS"
echo "Voir le fichier $RESULTS pour les détails."