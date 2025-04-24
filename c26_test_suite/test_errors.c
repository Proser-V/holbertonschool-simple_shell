#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * run_test - Runs an automated test for a given command in the custom shell.
 *
 * @cmd: The command to execute in the shell (as a string).
 * @expected_output: A string that should appear in the shell standard output.
 * @expected_exit: The expected exit status after executing the command.
 *
 * Return: nothing (void)
 */

void run_test(const char *cmd, const char *expected_output, int expected_exit)
{
	char tmpfile[] = "/tmp/myshell_test_output_XXXXXX";
	int fd = mkstemp(tmpfile);
	char output[1024] = "";
	FILE *fp = fdopen(fd, "w+");
	char full_command[512];

	if (fd == -1)
	{
		perror("mkstemp");
		exit(1);
	}

	if (!fp)
	{
		perror("fdopen");
		exit(1);
	}

	/* Préparer la commande complète */
	snprintf(full_command, sizeof(full_command),
	"echo \"%s\" | ./hsh > %s 2>&1", cmd, tmpfile);

	/* Lancer le shell avec la commande simulée */
	int exit_status = system(full_command) / 256;

	/* Lire le contenu produit */
	fseek(fp, 0, SEEK_SET);

	fread(output, 1, sizeof(output) - 1, fp);
	fclose(fp);
	remove(tmpfile);

	/* Afficher le résultat du test */
	printf("Command: %s\n", cmd);
	printf("Expected exit: %d | Got: %d\n", expected_exit, exit_status);
	printf("Expected output (part): \"%s\"\n", expected_output);
	printf("Shell output:\n%s\n", output);
	printf("TEST %s\n\n", (strstr(output, expected_output)
	!= NULL && exit_status == expected_exit) ? "✅ PASSED" : "❌ FAILED");
}

/**
 * main - Entry point for the shell test runner.
 *
 * Return: Always 0.
 */

int main(void)
{
	/* Cas valides */
	run_test("ls", "", 0);
	run_test("echo hello", "hello", 0);
	/* Commande invalide */
	run_test("unknowcmd", "not found", 127);
	/* Commande avec argument invalide */
	run_test("ls /doesnotexist", "No such file or directory", 2);
	/* Test de `exit` sans argument */
	run_test("exit", "", 0);
	/* Test de `exit` avec valeur */
	run_test("exit 42", "", 42);
	/* Test de la commande `env` */
	run_test("env", "PATH", 0);
	/* Test de plusieurs commandes */
	run_test("echo 1\necho 2", "1", 0);

		/* --- TESTS SPÉCIFIQUES À EXIT --- */
	/* exit simple, sans argument -> doit retourner 0 */
	run_test("exit", "", 0);
	/* exit avec un code précis -> doit quitter avec ce code */
	run_test("exit 0", "", 0);
	run_test("exit 42", "", 42);
	run_test("exit 127", "", 127);
	/* exit avec une valeur négative */
	run_test("exit -1", "./hsh: 1: exit: Illegal number: -1", 2);
	/* exit avec trop d'arguments (ex: "exit 5 10") */
	run_test("exit 5 10", "", 5);
	/* exit avec espaces en trop (le shell devrait quand même fonctionner) */
	run_test("   exit    56   ", "", 56);
	/* commande invalide puis exit */
	run_test("badcmd\nexit 99", "not found", 99);
	return (0);
}
