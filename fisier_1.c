#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main(){

    FILE *fp;
/*
    if((fp=fopen("fisier_1.txt","wt"))==NULL){
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }

    char sir[30];
*/
    //scriere in fisier cu totul (o singura scriere)
/*
    printf("introduceti sirul de carcatere: ");
    gets(sir);
    printf("\n");

    fputs(sir,fp);

    fprintf(fp,"\n");
*/
    
    //scriere in fisier caracter cu caracter
/*    
    printf("Introduceti sirul de caractere: ");
    gets(sir);
    char car;
    int i=0;
    do{
        car=*(sir+i);
        putc(car,fp);
        i++;
    }while(car!='\0');
*/

    //scriere in fisier cuvant cu cuvant pe o singura linie
/*    
    char *p;
    #define SPATIU " "
    printf("Introduceti sirul de caractere: ");
    gets(sir);
    char copy[30];
    strcpy(copy,sir);
    p=strtok(copy,SPATIU);
    while(p!=NULL){
        fputs(p,fp);
        fprintf(fp," "); //pentru afisare pe linii diferite se inlocuieste cu comanda fprintf(fp,"\n");
        p=strtok(NULL,SPATIU);
    }
*/

    if((fp=fopen("fisier_1.txt","rt"))==NULL){
        printf("fisierul nu a putut fi deschis!");
        exit(1);
    }

    //citire din fisier caracter cu caracter
/*
    char car;
    while(!feof(fp)){ //while(car!=EOF) ...
        car=fgetc(fp);
        printf("%c",car);
    }
*/

    //citire cuvant cu cuvant
/*
    char cuv[30];
    while(!feof(fp)){
        fscanf(fp,"%s",cuv);
        printf("%s",cuv);
    }
*/

    //citire intreaga linie
/*
    char cuv[30];
    char car;
    int lung;


    fseek(fp,0L,SEEK_END);
    lung=ftell(fp);
    fseek(fp,0L,SEEK_SET);
    fgets(cuv,lung,fp);
    printf("%s",cuv); 
*/
    //in cazul in care nu se foloseste \n sirul se afiseaza fara ultimul caracter!

    char sir1[10],sir2[10];
    char sir[100],new[100]="",temp[100]="";

    scanf("%s",sir1);
    getchar();
    scanf("%s",sir2);

    fseek(fp,1L,SEEK_END);
    int n=ftell(fp);
    fseek(fp,0L,SEEK_SET);
    fgets(sir,n,fp);

    fclose(fp);

    if((fp=fopen("fisier_1.txt","wt"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    printf("\n");
    puts(sir);
    printf("\n");
    /*
    char *p=strstr(str,sir1);
    while(p!=NULL){
        change++;
        strncpy(p,sir2,strlen(sir2));
        p[strlen(sir2)]= ' ';

        printf("Mofdificarea %d\n",change);
        printf("%s",str);
        fseek(fp,0L,SEEK_SET);
        fputs(str,fp);

        p=strstr(p+strlen(sir2),sir1);

    }


    if(change==0) fprintf(fp,"\nSirul nu a fost modificat!");
    */

    char *p;
    int change = 0;

    p = strtok(sir, " ");
    while(p != NULL){
        if(strcmp(p, sir1) == 0){
            strcat(new, sir2);
            strcpy(temp,new);
            strcat(temp,p+strlen(sir1));
            change++;
            printf("Modificarea %d: ",change);
            printf("%s\n",temp);
        }
        else strcat(new, p);
        strcat(new, " ");
        p = strtok(NULL, " ");
    }

    if(change == 0) printf("Nu exista cuvantul in fisier");
    else
    {
    fseek(fp,0L,SEEK_SET);
    fputs(new,fp);
    }

    fclose(fp);

    return 0;

}