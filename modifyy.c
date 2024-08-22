#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 


void print_html_header() {
    
    printf("<html>\n<head>\n<title>Modifier Inscription</title>\n");
    printf("<style>\n");
    printf("body { font-family: Arial, sans-serif; background-color: #ffe4e1; padding: 20px; }\n");
    printf("form { max-width: 500px; margin: auto; padding: 10px; background: white; border-radius: 5px; }\n");
    printf("input[type=\"text\"] { width: 100%%; padding: 10px; margin: 5px 0 10px 0; border: 1px solid #ccc; border-radius: 4px; }\n");
    printf("input[type=\"submit\"] { background-color: #4CAF50; color: white; padding: 10px 15px; border: none; border-radius: 4px; cursor: pointer; }\n");
    printf("input[type=\"submit\"]:hover { background-color: #45a049; }\n");
    printf("</style>\n</head>\n<body>\n");
}

void print_html_footer() {
    printf("</body>\n</html>\n");
}

void display_modify_form(char *nom, char *prenom, char *genre) {
    printf("<h2>Modifier Inscription</h2>\n");
    printf("<form action=\"modifyy.cgi\" method=\"GET\">\n");
    printf("<label for=\"nom\">Nom :</label>\n");
    printf("<input type=\"text\" id=\"nom\" name=\"nom\" value=\"%s\" required><br>\n", nom);
    printf("<label for=\"prenom\">Prenom :</label>\n");
    printf("<input type=\"text\" id=\"prenom\" name=\"prenom\" value=\"%s\" required><br>\n", prenom);
    printf("<label for=\"genre\">Genre :</label>\n");
    printf("<input type=\"text\" id=\"genre\" name=\"genre\" value=\"%s\" required><br>\n", genre);
    printf("<input type=\"hidden\" name=\"old_nom\" value=\"%s\">\n", nom);
    printf("<input type=\"hidden\" name=\"old_prenom\" value=\"%s\">\n", prenom);
    printf("<input type=\"submit\" value=\"Modifier\">\n");
    printf("</form>\n");
}

void modify_inscription(char *old_nom, char *old_prenom, char *new_nom, char *new_prenom, char *new_genre) {
    FILE *file = fopen("inscription.html", "r");
    FILE *temp = fopen( "temp.html", "w");
    char buffer[1000];

    if (file == NULL || temp == NULL) {
        printf("<p>Erreur d'ouverture du fichier.</p>\n");
        return;
    }

    // Copier les lignes du fichier original au fichier temporaire, en modifiant la ligne sélectionnée
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, old_nom) != NULL && strstr(buffer, old_prenom) != NULL) {
            fprintf(temp, "<tr><td>%s</td><td>%s</td><td>%s</td><td><a href=\"modifyy.cgi?nom=%s&prenom=%s&genre=%s\"><button>ec-modifier</button></a></td>\n",
                    new_nom, new_prenom, new_genre, new_nom, new_prenom, new_genre);
        } else {
            fputs(buffer, temp);
        }
    }

    fclose(file);
    fclose(temp);

   if (remove("inscription.html") != 0) {
    perror("Erreur lors de la suppression du fichier original");
}

if (rename("temp.html", "inscription.html") != 0) {
    perror("Erreur lors du renommage du fichier temporaire");
}
    printf("<p><b>Inscription modifiee avec succes.<b></p>\n");
    printf("<a href=\"inscription.html\"><button>Retour a la liste des inscriptions</button></a>\n");
}

int main(void) {
    char *data;
    char nom[50], prenom[50], genre[50], old_nom[50], old_prenom[50];
    int modify_mode = 0;

    printf("content-type: text/html\n\n");

    data = getenv("QUERY_STRING");
    if (data == NULL) {
        printf("<p>Erreur : aucune donnee reçue.</p>\n");
        printf("</body></html>\n");
        return 1;
    }

   /// printf("<p>Data received: %s</p>\n", data);

    // Vérifier si nous sommes en mode modification ou soumission
    if (sscanf(data, "nom=%49[^&]&prenom=%49[^&]&genre=%49[^&]&old_nom=%49[^&]&old_prenom=%49s", nom, prenom, genre, old_nom, old_prenom) == 5) {
        modify_mode = 1;
    } else if (sscanf(data, "nom=%49[^&]&prenom=%49[^&]&genre=%49s", nom, prenom, genre) == 3) {
        modify_mode = 0;
    } else {
        printf("<p>Erreur de format des donnees reçues.</p>\n");
        printf("</body></html>\n");
        return 1;
    }

    print_html_header();

    if (modify_mode) {
        modify_inscription(old_nom, old_prenom, nom, prenom, genre);
    } else {
        display_modify_form(nom, prenom, genre);
    }

    print_html_footer();

    return 0;
}
