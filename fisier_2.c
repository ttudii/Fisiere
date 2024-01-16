#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){

    FILE *fp;

    if((fp=fopen("fisier_2.txt","wt"))==NULL){
        printf("fisierul nu a putu fi deschis");
        exit(1);
    }

    char car;
    int out=0;

    do{
        char sir[100];
        gets(sir);
        //getchar();
        fputs(sir,fp);
        fprintf(fp,"\n");

        do{
            printf("mai introduci?(y sau n)");
            scanf("%c",&car);
            getchar();
        }while(tolower(car)!='y' && tolower(car)!='n');

        if(tolower(car)=='n') out=1;
    }while(!out);

    fclose(fp);

    printf("\nContinutul fisierului este:\n\n");

    if((fp=fopen("fisier_2.txt","rt"))==NULL){
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    
    char c;
    char str[100];

    fseek(fp,1L,SEEK_END);
    int n=ftell(fp);
    fseek(fp,0L,SEEK_SET);

    while(!feof(fp)){
        fgets(str,n,fp);
        if(feof(fp)) break;
        puts(str);
    }

    //cerinta b) cautare cuvant

    /*

    fseek(fp,0L,SEEK_SET);
    char text[1000];
    int line=0;
    int found[100];
    int i=0;
    char cuv[20];

    printf("Cuvantul cautat: ");
    scanf("%s",cuv);
    getchar();
    printf("\n\n");

    while(fgets(text,1000,fp)!=NULL){
        line++;
        char copy[1000];
        strcpy(copy,text);
        char *p;
        p=strstr(copy,cuv);
        if(p!=NULL){
            found[i]=line;
            i++;
        }
    }

    printf("Cuvantul a fost gasit pe liniile:\n");

    for(int k=0;k<i;k++) 
    {
    printf("%d ",found[k]);
    }

    */

   //cerinta c) numar cuvinte si caractere

   char text[1000];
   int nr_cuv=0,nr_car=0;
   char DELIM[]=" .,";

   fseek(fp,0L,SEEK_SET);

   while(fgets(text,1000,fp)){
    char copy[1000];
    strcpy(copy,text);
    char *p;
    p=strtok(copy,DELIM);
    while(p!=NULL){
        nr_cuv++;
        p=strtok(NULL,DELIM);
    }
   }

    char x;

    fseek(fp,0L,SEEK_SET);

    while((x=getc(fp))!=EOF){
        nr_car++;
    }

    printf("\nFisierul are %d cuvinte si %d caractere.\n",nr_cuv,nr_car);

    //cerinta d) linia de lungime maxima

    fseek(fp,0L,SEEK_SET);
    int length[10];
    int j=0;
    while(fgets(text,1000,fp)){
    char copy[1000];
    strcpy(copy,text);
    int i=0;
    while(*(copy+i)!='\n' && *(copy+i)!=EOF)
    {
        i++;
    }
    length[j]=i;
    j++;
   }

   int max=length[0];
   int indice=0;

   for(int i=1;i<j;i++){
        if(length[i]>max) {
            max=length[i];
            indice=i+1;
        }
   }

   printf("\nLinia de lungime maxima este: %d",indice);


    fclose(fp);


    return 0;
}