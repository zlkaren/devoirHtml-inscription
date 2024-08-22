#include <stdio.h>
#include <stdlib.h>

int main()
{
		FILE * file = NULL;
		 printf("Content-type: text/html\n\n");
		file = fopen ("inscription.html" ,"a+");
		if(file == NULL)
		{
				printf("<html>\n <head><title> fin </title></head>\n<body ><p> error ouveture!! </p></body> \n</html>");
				exit(1);
			}
		if (file != NULL){
			fprintf(file , "</table>\n </body> \n</html>");
			fprintf(file ,"<html> ");
			fprintf(file , "<head><title>Les Inscriptions</title></head>");
			fprintf(file , "<body  bgcolor = \"#ffe4e1\">");
			fprintf(file, "<table border = \"1\">");
			
			}
			fclose(file);
			printf("<html>\n <head><title> fin </title></head>\n<body  bgcolor = \"#ffe4e1\"><p>Good Bye </p></body> \n</html>");
			printf("<a href=\"inscription.html\">la liste des inscriptions</a>\n");
		return (0);
	
}
