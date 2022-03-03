// Scott Kuhl

/* exec*() functions let you replace the existing process with a new
   process (see exec-variations.c) and will never return (except for
   error).

   popen() is different in several ways:

   First, it allows you to capture stdout (but not stderr!) or write
   information to stdin.

   Second, it returns when the program exits. I.e., popen() will call
   fork() and then exec for you, then wait for the program to complete.

   Third, the command is executed by the shell and not run
   directly. For example, your shell will take the command "ls r*" and
   expand the "r*" to be a list of files that begin with 'r'. However,
   exec*() functions don't do this for you.

   Fourth, you just list the program name and the parameters all in
   one string. The reason for this is because the program will be run
   in the shell program. The shell will parse out the actual
   parameters.
 */
#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>

char buf[1024];
char* getBatteryPercent(void)
{
	// Compare the output of this program to running "ps aux" on the
	// command line.
	FILE *in = popen("cat /sys/class/power_supply/BAT0/capacity", "r");
	if(in == NULL)
	{
		perror("popen:");
		exit(EXIT_FAILURE);
	}

	// Write the output of the command to the console.
	while(fgets(buf, sizeof(buf), in) != NULL)
		printf("%s", buf);


	printf("\n\n");
	
	int pcloseRetVal = pclose(in); // wait for process to finish.
	
	return buf;
}
int main()
{
    char *battery = getBatteryPercent();
    printf("Battery Value %s",battery);
    return 0;
}
