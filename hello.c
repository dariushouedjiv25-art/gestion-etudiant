#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTURE D'ETUDIANT

typedef struct etudiant{
    char nom[30];
    float *notes;
    float moyenne;
}se;

 se *etudiants = NULL;

//VARIABLE GLOBALE
int MAX;
int nbnote;
int nb_etudiant=0;
int faconmoyen;
char nomfichier[100]="";

//--------- fontion est nombre------

int ESTNOMBRE(const char s[])
{
    int np=0;
    int len = strlen(s);
    if (len==0)
    {
        return 1;
    }
    for(int i=0;i<len;i++)
    {
        if (s[i]=='-')
        {
            if (i!=0)
            {
                return 1;
            }
        }
        else if ((s[i]=='.')||(s[i]==','))
        {
            np += 1;
            if ((np>1)||(i==len)||(i==0))
            {
                return 1;
            }
        }
        else
        {
            if ((s[i]<'0')||(s[i]>'9'))
            {
                return 1;
            }
        }
    }
    return 0;
}
 // FONCTION DE CALCULE DE LA MOYENNE

float CalculMoyenne(float notes[]){
    float somme=0,moyenne=0;
        if(faconmoyen==1){
            for(int j=0;j<nbnote;j++){
                somme += notes[j];
            }
            moyenne = somme/nbnote;
        }
        else if(faconmoyen==2){
            if(nbnote==2){
                moyenne =((notes[0]*0.4)+(notes[1]*0.6));
            }
            else{
                printf("ne peut etre fait qu'avec deux notes\n");
            }
        }
    return moyenne;
}

// FONCTION AJOUTER ETUDIANT

void ajouter_etudiant(){
    char saisie[30];
    int N;
    if(nb_etudiant==MAX){
        printf("capacité maximal atteinte\n");
        return;
    }
    do{
        printf("combien d'etudiant vous voulez ajouter ?\n");
        scanf("%s",saisie);
    }while(ESTNOMBRE(saisie));
    N = atoi(saisie);
    if(N+nb_etudiant>MAX){
        printf("capacite maximale atteinte, impossible d'ajouter %d etudiant\n",N);
        return;
    }
    for(int i=0;i<N;i++){
        printf("\nNom de l'etudiant %d\n",i+1);
        scanf("%s",etudiants[nb_etudiant].nom);
        etudiants[nb_etudiant].notes = malloc(nbnote * sizeof(float));
        if(etudiants[nb_etudiant].notes == NULL){
            printf("Erreur allocation\n");
            exit(1);
        }
        for(int j=0;j<nbnote;j++){
            do{
                printf("note %d de %s\n",j+1,etudiants[nb_etudiant].nom);
                scanf("%s",saisie);
                if(ESTNOMBRE(saisie)==1){
                    printf("veuillez n'entrer que des nombres\n");
                }
                else{
                    etudiants[nb_etudiant].notes[j]=atof(saisie);
                }
            }while((ESTNOMBRE(saisie)==1)||(etudiants[nb_etudiant].notes[j]<0)||(etudiants[nb_etudiant].notes[j]>20));
        }
        etudiants[nb_etudiant].moyenne =CalculMoyenne(etudiants[nb_etudiant].notes);
        nb_etudiant++;
    }
    printf("%d etudiant ajouter avec succes\n",N);
}

// FONCTION RECHERCHE ETUDIANT

void recherche_etudiant(){
    int index = 0;
    char recherche[30];
    int T[10];
    if(nb_etudiant==0){
        printf("aucun etudiant enregistre\n");
        return;
    }
    printf("entrer le nom de l'etudiant que vous voulez rechercher\n");
    scanf("%s",recherche);
    for(int i=0;i<nb_etudiant;i++){
        if(strcmp(recherche,etudiants[i].nom)==0){
            T[i]=i;
            index += 1;
        }
    }
    if(index==0){
        printf("aucun etudiant trouve a ce nom\n");
    }
    else{
        printf("%d etudiant trouve :\n",index);
        for(int i=0;i<index;i++){
            printf("\nNom : %s\n",etudiants[T[i]].nom);
            printf("moyenne : %.2f\n",etudiants[T[i]].moyenne);
        }
    }
}

// FONCTION AFFICHER TOUT LES ETUDIANTS

void afficher_etudiant(){
    if(nb_etudiant==0){
        printf("aucun etudiant enregistre\n");
        return;
    }
    for(int i=0;i<nb_etudiant;i++){
        printf("\nNom : %s\n",etudiants[i].nom);
        for(int j=0;j<nbnote;j++){
            printf("note %d : %.2f\n",j+1,etudiants[i].notes[j]);
        }
        printf("moyenne : %.2f\n",etudiants[i].moyenne);
    }
}

// FONCTION AFFICHER LE MEILLEUR ETUDIANT
void meilleur_etudiant(){
    if (nb_etudiant == 0) {
        printf("Aucun etudiant.\n");
        return;
    }
    int index = 0;
    for(int i=1;i<nb_etudiant;i++){
        if(etudiants[i].moyenne>etudiants[index].moyenne){
            index = i;
        }
    }
    printf("le meilleur etudiant est: %s\n",etudiants[index].nom);
    printf("moyenne : %.2f\n",etudiants[index].moyenne);
}

// FONTION SUPPRIMER UN ETUDIANT
void supprimer_etudiant(){
    char supprimer[30];
    int index = -1;
    if(nb_etudiant==0){
        printf("aucun etudiant enregistre\n");
        return;
    }
    printf("entrer le nom de l'etudiant que vous voulez supprimer\n");
    scanf("%s",supprimer);
    for(int i=0;i<nb_etudiant;i++){
        if(strcmp(supprimer,etudiants[i].nom)==0){
            index=i;
        }
    }
    if(index== -1){
        printf("aucun etudiant trouver\n");
        return;
    }
    else{
        free(etudiants[index].notes);
        for(int i=index;i<nb_etudiant-1;i++){
            etudiants[i] = etudiants[i+1];
        }
        nb_etudiant--;
    }
}

// FONCTION TRIE DU TABLEAU

void trie_tableau(){
    if(nb_etudiant==0){
        printf("aucun etudiant enregistre\n");
        return;
    }
    else if(nb_etudiant==1){
        printf("un seul etudiant enregistre\n");
        return;
    }
    int indmin;
    se temp;
    for(int i=0;i<nb_etudiant;i++){
        indmin = i;
        for(int j=i+1;j<nb_etudiant;j++){
            if(etudiants[j].moyenne<etudiants[indmin].moyenne){
                indmin = j;
            }
        }
        temp = etudiants[i];
        etudiants[i] = etudiants[indmin];
        etudiants[indmin] = temp;
    }
}

// MODIFIER LES INFOS D'UN ETUDIANT
void modifier_etudiant(){
    char modifier[30];
    char saisie[30];
    int N;
    int index =-1;
    int choix=3;
    if(nb_etudiant==0){
        printf("aucun etudiant enregistre\n");
        return;
    }
    do{
        printf("entrer le nom de l'etudiant\n");
        scanf("%s",modifier);
        for(int i=0;i<nb_etudiant;i++){
            if(strcmp(modifier,etudiants[i].nom)==0){
                index =i;
            }
        }
        if(index ==-1){
            printf("aucun etudiant trouve\n");
            return;
        }
        printf("\nNom : %s\n",etudiants[index].nom);
        for(int j=0;j<nbnote;j++){
            printf("note %d : %.2f\n",j+1,etudiants[index].notes[j]);
        }
        printf("moyenne : %.2f\n",etudiants[index].moyenne);
        printf("           \n");
        printf("que voulez vous faire ?\n");
        printf("1-modifier le nom\n");
        printf("2-modifier les notes\n");
        scanf("%d",&choix);
        switch(choix){
            case 1:{
                printf("entrer le nouveau nom:\n");
                scanf("%s",etudiants[index].nom);
                break;
            }
            case 2:{
                do{
                    printf("quelle note vous souhaitez modifier ? (1 pour note 1)\n");
                    scanf("%s",saisie);
                    if(ESTNOMBRE(saisie)==0){
                        N = atoi(saisie);
                        if((N<0)||(N>nbnote)){
                        printf("note incorrespondante\n");
                        }
                        else{
                        printf("entrer la nouvelle note %d\n",N);
                        scanf("%f",&etudiants[index].notes[N-1]);
                        }
                    }
                    else{
                        printf("veuillez n'entrer que des nombres\n");
                    }
                }
                while((ESTNOMBRE(saisie)==1)||((N<0)||(N>nbnote)));
                etudiants[index].moyenne = CalculMoyenne(etudiants[index].notes);
                break;
            }
        default : printf("choix invalide\n");
        }
    }while((index==-1)||((choix!=1)&&(choix!=2)));
}

// CHARGEMENT D'UN FICHIER

void charger_fichier(char nom_fichier[]){
    FILE *f;
    f = fopen(nom_fichier,"r");
    if(!f){
        printf("Aucun fichier existant, démarrage avec une base vide.\n");
        return;
    }
    while(fscanf(f,"%s",etudiants[nb_etudiant].nom)==1){
        etudiants[nb_etudiant].notes = malloc(nbnote * sizeof(float));
        if(etudiants[nb_etudiant].notes == NULL){
            printf("Erreur allocation\n");
            exit(1);
        }
        for(int j=0;j<nbnote;j++){
            fscanf(f,"%f",&etudiants[nb_etudiant].notes[j]);
        }
        fscanf(f,"%f",&etudiants[nb_etudiant].moyenne);
        nb_etudiant++;
    }
    fclose(f);
    printf("fichier charger avec succès\n");
}

// SAUVEGARDE RAPIDE

void sauvegarde_rapide(){
    if(strcmp(nomfichier,"")==0){
        printf("aucun fichier charger\n");
        return;
    }
    FILE *f = fopen(nomfichier,"w");
    if(!f){
        printf("erreur lors de la sauvegarde\n");
        exit(1);
    }
    for(int i=0;i<nb_etudiant;i++){
        fprintf(f,"%s\n",etudiants[i].nom);
        for(int j=0;j<nbnote;j++){
            fprintf(f,"note %d : %.2f\n",j+1,etudiants[i].notes[j]);
        }
        fprintf(f,"moyenne : %.2f\n",etudiants[i].moyenne);
        fprintf(f,"----------------------\n");
    }
    fclose(f);
    printf("fichier sauvegarder avec succes\n");
}

// SAUVEGARGE DANS UN AUTRE FICHIER

void sauvegarde(){
    int choix=2;
    printf("entrer le nom du fichier (avec l'extention .txt)\n");
    scanf("%s",nomfichier);
    FILE *test = fopen(nomfichier,"r");
    if(test==NULL){
        sauvegarde_rapide();
        return;
    }
    else if(test != NULL){
        fclose(test);
        do{
            printf("Le fichier existe. Voulez-vous ecraser ? (1=oui / 0=non)");
            scanf("%d",&choix);
            switch(choix){
                case 1: sauvegarde_rapide();break;
                case 0:{
                    FILE *f = fopen(nomfichier,"a");
                    if(!f){
                        printf("erreur lors de la sauvegarde\n");
                        exit(1);
                    }
                    for(int i=0;i<nb_etudiant;i++){
                        fprintf(f,"%s\n",etudiants[i].nom);
                        for(int j=0;j<nbnote;j++){
                            fprintf(f,"note %d : %.2f\n",j+1,etudiants[i].notes[j]);
                        }
                        fprintf(f,"moyenne : %.2f\n",etudiants[i].moyenne);
                        fprintf(f,"----------------------\n");
                    }
                    fclose(f);
                    break;
                }
                default : printf("choix invalide\n");
            }
        }while((choix!=1)&&(choix!=0));
        printf("fichier sauvegarder avec succes\n");
    }
}


// CORPS DU PROGRAMME
int main()
{
    char saisie[30];
    int choix;
    do{
        printf("combien d'etudiant vous voulez gerer en tout ?\n");
        scanf("%s",saisie);
    }while(ESTNOMBRE(saisie));
    MAX = atoi(saisie);
    etudiants = (se *)malloc(MAX * sizeof(se));
    if(etudiants==NULL){
        printf("erreur lors de l'allocation de la memoire");
        return 1;
    }

    do{
        printf("combien de note par etudiant ?\n");
        scanf("%s",saisie);
    }while(ESTNOMBRE(saisie));
    nbnote = atoi(saisie);

    do{
        printf("comment souhaitez vous calculer la moyenne ?\n");
        printf("1-moyenne classique\n");
        printf("2-moyenne 40-60\n");
        scanf("%d",&faconmoyen);
    }while((faconmoyen!=1)&&(faconmoyen!=2));

    do {
        printf("\n===== MENU =====\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher les etudiants\n");
        printf("3. Rechercher un etudiant\n");
        printf("4. Meilleur etudiant\n");
        printf("5. Trier par moyenne\n");
        printf("6. modifier les infos d'un etudiant\n");
        printf("7. supprimer un etudiant\n");
        printf("8. charger un fichier\n");
        printf("9. sauvergarde rapide dans le fichier charger\n");
        printf("10. sauvergarder dans un fichier\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouter_etudiant(); break;
            case 2: afficher_etudiant(); break;
            case 3: recherche_etudiant(); break;
            case 4: meilleur_etudiant(); break;
            case 5: trie_tableau(); break;
            case 6: modifier_etudiant();break;
            case 7: supprimer_etudiant();break;
            case 8: {
                    printf("entrer le nom du fichier que vous voullez charger\n");
                    scanf("%s",nomfichier);
                    charger_fichier(nomfichier);break;
            }
            case 9: sauvegarde_rapide();break;
            case 10: sauvegarde();break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 0);
}
