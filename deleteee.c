#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void supprimer_ligne_tableau(char *filename, char *search_nom, char *search_prenom);
void vider_fichier( char *filename);


int main() {
    char *filename = "inscription.html";
    char *data;
    char search_nom[50], search_prenom[50], genre[15];

    printf("content-type: text/html\n\n");
    printf("<html>\n<head>\n<title>Supprimer Inscription</title>\n</head>\n<body bgcolor = \"#ffe4e1\">\n");

    data = getenv("QUERY_STRING");
    if (data == NULL) {
        printf("<p>Erreur : aucune donnée reçue.</p>\n");
        printf("</body></html>\n");
        return 1;
    }

    ///printf("<p>Donnees reçues : %s</p>\n", data); ///afficher les données reçues en cas d'erreur
    if (sscanf(data, "nom=%49[^&]&prenom=%49[^&]&genre=%14s", search_nom, search_prenom, genre) != 3) {
        printf("<p>Erreur de format des donnees reçues.</p>\n");
        printf("</body></html>\n");
        return 1;
    }

    supprimer_ligne_tableau(filename, search_nom, search_prenom);
    char tmp[2000];
    FILE *tmp_file = fopen ("temp.html", "r");
	FILE *file = fopen ("inscription.html", "w+");
    
		while(fgets(tmp, sizeof(tmp),tmp_file) != NULL)
		{
				fputs(tmp, file);
		} 
		
		
   
    
	printf("<a href=\"inscription.html\"><button>Retour a la liste des inscriptions</button></a>\n");
    printf("</body>\n</html>\n");
    return 0;
}
void supprimer_ligne_tableau(char *filename, char *search_nom, char *search_prenom) {
    FILE *file = fopen(filename, "r");
    FILE *temp_file = fopen("temp.html", "w");
    char buffer[1000];
    char ligne_tableau[4000];
    int found = 0;

    if (file == NULL || temp_file == NULL) {
        printf("<p>Erreur d'ouverture des fichiers.</p>\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        /// Vérifier si la ligne contient une entrée du tableau avec le nom et prénom recherchés
        if (strstr(buffer, "<tr>") != NULL) {
            strcpy(ligne_tableau, buffer);  ///Commencer une nouvelle ligne de tableau
            while (fgets(buffer, sizeof(buffer), file) != NULL && strstr(buffer, "</tr>") == NULL) 
            {
                strcat(ligne_tableau, buffer);  /// Ajouter à la ligne de tableau
            }
            strcat(ligne_tableau, buffer);  ///Ajouter la ligne de fermeture </tr>

            if (strstr(ligne_tableau, search_nom) != NULL && strstr(ligne_tableau, search_prenom) != NULL) {
                printf("<p><b>Ligne supprimee.</b></p>\n");
                found = 1;
                continue; /// Passer cette ligne pour la "supprimer"
            }

            fprintf(temp_file, "%s", ligne_tableau);  /// Écrire la ligne non supprimée
        } else {
            fprintf(temp_file, "%s", buffer);  /// Écrire les autres lignes
        }
    }

    if (!found) {
        printf("<p>Aucune correspondance trouvee pour %s %s.</p>\n", search_nom, search_prenom);
    }

    fclose(file);
    fclose(temp_file);

    /// Remplacer le fichier original par le fichier temporaire
 
    
}
void vider_fichier( char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fclose(file);
    }
}
