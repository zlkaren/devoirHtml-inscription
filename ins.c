#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void get();
void inscrit();
void erreur();
void start();

int main() 
{
	get();
	return (0);
}
void get()
{
    char *query_string = getenv("QUERY_STRING");
    char nom[100] = {0};
    char prenom[100] = {0};
    char genre[15] = {0};
    char chainetmp[200];
    int in = 0;
    FILE* file = NULL;

    printf("Content-type: text/html\n\n");

    if (query_string == NULL) {
        printf("<html>\n");
        printf("<head><title>Erreur</title></head>\n");
        printf("<body>Erreur de stockage</body>\n");
        printf("</html>\n");
        exit( 1);
    }

    sscanf(query_string, "nom=%100[^&]&prenom=%100[^&]&genre=%15s", nom, prenom, genre);
    
	
	file = fopen( "inscription.html", "r");
    if (file != NULL) {
        
        
        while (fgets(chainetmp, sizeof(chainetmp), file) != NULL) {
            if (strstr(chainetmp, nom) != NULL && strstr(chainetmp, prenom) != NULL ) {
                in = 1;
                break;
            }
        }
        fclose(file);
    }

    if (in == 1) {
        printf("<html>\n");
        printf("<head><title>inscrit</title></head>\n");
        printf("<body bgcolor = \"#ffe4e1\"> <center><font color = \"gris\"> <b>Vous etes deja inscrit ! </b> </font> <center>\n");
        /*printf("<a href= \"formulaire.html\"> <button>Continuer l'inscription </button></a>");
        printf("<a href= \"bye.html\"> <button>Terminer l'inscription </button></a>");*/
        printf("</center></body>");
        printf("</html>\n");
        exit(1);
    }

    file = fopen( "inscription.html", "a+");
    if (file == NULL) {
       erreur();
        exit(1);
    }
	start();
	///int i = 0;
	/*while(prenom[i])
	{
			if(prenom[i] == '+')
			{
					prenom[i] = ' ';
			}
	}
	while(nom[i] != '\0')
	{
			nom[i] = toupper(nom[i]);
			i++;
	}
	while(prenom[0] != '\0')
	{
			prenom[0] = toupper(prenom[0]);
	}*/
	
    fprintf(file, "<tr> <td>%s </td> <td>%s </td> <td>%s </td>", nom, prenom, genre);
									
									
									
								
	fprintf(file ,"<td>\n\
											<form action = \"modifyy.cgi\" method = \"get\">\n\
											<input type = \"hidden\" name = \"nom\" value = \"%s\">\n\
											<input type = \"hidden\" name = \"prenom\" value = \"%s\">\n\
											<input type = \"hidden\" name = \"genre\" value = \"%s\">\n\
											<input type = \"submit\" value = \"Modifier\">\n\
											</form>\n\
									</td>\n", nom, prenom, genre);
	fprintf(file ,"<td>\n\
											<form action = \"delete.cgi\" method = \"get\">\n\
											<input type = \"hidden\" name = \"nom\" value = \"%s\">\n\
											<input type = \"hidden\" name = \"prenom\" value = \"%s\">\n\
											<input type = \"hidden\" name = \"genre\" value = \"%s\">\n\
											<input type = \"submit\" value = \"DELETE\">\n\
											</form>\n\
									</td></tr>\n", nom, prenom, genre);
    
    fclose(file);
	inscrit();
    
}

void inscrit()
{
	printf("<html>\n");
    printf("<head><title>Inscription</title></head>\n");
    printf("<body bgcolor = \"#ffe4e1\"> <center><font color = \"gris\"><b>Vous etes inscrit ! <b></font></center>\n");
    printf("<a href= \"formulaire.html\"><center><button>click pour continuer l'inscription</button><center><a>");
    printf("<a href= \"bye.cgi\"><center><button>click pour finir l'inscription</button><center><a>");
    printf("</body>");
    printf("</html>\n");	
	
}
void erreur()
{
		 printf("<html>\n");
        printf("<head><title>Erreur</title></head>\n");
        printf("<body>Erreur d'ouverture du fichier</body>\n");
        printf("</html>\n");
}
void start()
{
		
		printf("<html> ");
        printf("<head><title>Les Inscriptions</title></head>");
        printf("<body>");
         printf("<table border = \"1\">");

}
