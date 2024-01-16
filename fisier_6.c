#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct PERSOANA{
    char nume[30];
    char prenume[30];
    float varsta;
};

struct INDEX{
    int indice;
    float ani;
};

int main(){

    FILE *fp;

    struct PERSOANA persoana[5];
    int i,j;

    for(i=0;i<5;i++){
        printf("Persoana %d\n\n",i+1);
        printf("Numele persoanei: ");
        scanf("%s",persoana[i].nume);
        getchar();
        printf("Prenumele persoanei: ");
        scanf("%s",persoana[i].prenume);
        printf("Varsta persoanei: ");
        scanf("%f",&persoana[i].varsta);
        printf("\n\n");
    }

    if((fp=fopen("fisier_6.txt","wt"))==NULL){
        printf("Fisierul nu a putut fi deschis");
        exit(1);
    }

    for(i=0;i<5;i++){
        fprintf(fp,"%s ",persoana[i].nume);
        fprintf(fp,"%s ",persoana[i].prenume);
        fprintf(fp,"%3.2f",persoana[i].varsta);
        fprintf(fp,"\n");
    }

    fclose(fp);

    if((fp=fopen("fisier_6.txt","rt"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    struct PERSOANA temp[5];

    for(i=0;i<5;i++){
        fscanf(fp,"%s",temp[i].nume);
        fscanf(fp,"%s",temp[i].prenume);
        fscanf(fp,"%f",&temp[i].varsta);
    }

    fclose(fp);

    printf("Afisarea continutului fisierului text:\n\n");

    for(i=0;i<5;i++){
        printf("%s ",temp[i].nume);
        printf("%s ",temp[i].prenume);
        printf("%3.2f",temp[i].varsta);
        printf("\n");
    }

    struct PERSOANA extra;

    printf("\n\n");

    printf("Persoana noua:\n\n");

    printf("Introduceti numele persoanei: ");
    scanf("%s",extra.nume);
    getchar();
    printf("Introduceti prenumele persoanei: ");
    scanf("%s",extra.prenume);
    printf("Introduceti varsta persoanei: ");
    scanf("%f",&extra.varsta);

    int out=0;

    for(i=0;i<5;i++){
        if(strcmp(extra.nume,temp[i].nume)==0 && strcmp(extra.prenume,temp[i].prenume)==0 && extra.varsta==temp[i].varsta)
        {
            out=1;
            break;
        }
    }

    printf("\n\n");

    if(out==0){
    
    printf("Persoana nu exista in fisier si va fi introdusa");

    if((fp=fopen("fisier_6.txt","at"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    fseek(fp,0L,SEEK_END);

    fprintf(fp,"%s ",extra.nume);
    fprintf(fp,"%s ",extra.prenume);
    fprintf(fp,"%3.2f",extra.varsta);
    fprintf(fp,"\n");

    fclose(fp);
    }
    else
    printf("Persoana introdusa exista deja in fisier!");

    printf("\n");

    int nr_pers;

    if(out==1) nr_pers=5;
    else
    nr_pers=6;

    printf("Vom afisa media aritmetica a varstelor persoanelor din fisier.");

    float medie=0;

    for(i=0;i<nr_pers;i++){
        medie+=temp[i].varsta;
    }

    medie=medie/(float)nr_pers;

    printf("\nMedia persoanelor din fisier este: %3.2f",medie);

    printf("\n\n");

    struct INDEX *index,copy;
    struct PERSOANA *modified;
    int t;

    if(nr_pers==5){
        modified=(struct PERSOANA*)malloc(sizeof(struct PERSOANA)*5);
        index=(struct INDEX*)malloc(sizeof(struct INDEX)*5);
        for(t=0;t<5;t++) modified[t]=temp[t];
    }
    else
    {
    modified=(struct PERSOANA*)malloc(sizeof(struct PERSOANA)*6);
    index=(struct INDEX*)malloc(sizeof(struct INDEX)*6);
    for(t=0;t<5;t++) modified[t]=temp[t];
    modified[t]=extra;
    }

    printf("\n\n");
    printf("Modified:\n\n");

    for(i=0;i<nr_pers;i++){
        printf("Nume: %s ",modified[i].nume);
        printf("Prenume: %s ",modified[i].prenume);
        printf("Varsta: %f",modified[i].varsta);
        printf("\n");
    }

    for(i=0;i<nr_pers;i++) {
        index[i].indice=i;
        index[i].ani=modified[i].varsta;
    }

    int aux;

    for(i=0;i<nr_pers;i++){
        for(j=i+1;j<nr_pers;j++){
            if(index[i].ani>index[j].ani){
                copy=index[i];
                index[i]=index[j];
                index[j]=copy;
            }
        }
    }

    printf("\n\n");

    for(i=0;i<nr_pers;i++) printf("%d ",index[i].indice);

    //in fisierul de indici se vor scrie persoanele sortate

    if((fp=fopen("index_6.txt","wt"))==NULL){
        printf("fisierul nu a putut fi deschis!");
        exit(1);
    }

    for(i=0;i<nr_pers;i++){
        fprintf(fp,"%s ",modified[index[i].indice].nume);
        fprintf(fp,"%s ",modified[index[i].indice].prenume);
        fprintf(fp,"%3.2f",modified[index[i].indice].varsta);
        fprintf(fp,"\n");
    }

    fclose(fp);

    //eliminarea unui element din fisier

    char eliminat_nume[30],eliminat_prenume[30];

    //se pot face verificari pentru a introduce doar nume existente in fisier

    printf("\n");
    printf("Introduceti numele de eliminat: ");
    scanf("%s",eliminat_nume);
    getchar();
    printf("Introduceti prenumele de eliminat: ");
    scanf("%s",eliminat_prenume);
    getchar();

    printf("\n\n");

    if((fp=fopen("eliminat_6.txt","wt"))==NULL){
        printf("fisierul nu a putut fi deschis!");
        exit(1);
    }  


    for(i=0;i<nr_pers;i++){
        if(!(strcmp(eliminat_nume,modified[i].nume)==0 && strcmp(eliminat_prenume,modified[i].prenume)==0)){
            fprintf(fp,"%s ",modified[i].nume);
            fprintf(fp,"%s ",modified[i].prenume);
            fprintf(fp,"%3.2f",modified[i].varsta);
            fprintf(fp,"\n");
        }
    }

    fclose(fp);

    //modificare a treia persoana din lista

    if((fp=fopen("modificat.txt","wt"))==NULL){
        printf("fisierul nu a putut fi deschis!");
        exit(1);
    }

    printf("\n\n");
    
    char car;
    char new_nume[30],new_prenume[30];

    do{
    printf("Vrei sa modifici numele celei de a treia persoane?");
    scanf("%c",&car);
    getchar();
    }while(tolower(car)!='d' && tolower(car)!='n');

    if(tolower(car)=='d'){
        printf("Nume nou: ");
        scanf("%s",new_nume);
        printf("Prenume nou: ");
        scanf("%s",new_prenume);
    }
    else
    printf("Fisierul nu va fi modificat!");

    strcpy(modified[2].nume,new_nume);
    strcpy(modified[2].prenume,new_prenume);

    for(i=0;i<nr_pers;i++){
        fprintf(fp,"%s ",modified[i].nume);
        fprintf(fp,"%s ",modified[i].prenume);
        fprintf(fp,"%3.2f",modified[i].varsta);
        fprintf(fp,"\n");
    }

    fclose(fp);

    return 0;

}