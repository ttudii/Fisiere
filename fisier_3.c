#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){

    int nr;
    float *vec;

    printf("Numarul de elemente ale vectorului: ");
    scanf("%d",&nr);

    vec=(float*)malloc(sizeof(float)*nr);

    for(int i=0;i<nr;i++) scanf("%f",vec+i);

    FILE *txt;

    if((txt=fopen("text_3.txt","wt"))==NULL){
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    fwrite(vec,sizeof(float),nr,txt);

    fclose(txt);

    FILE *bin;

    if((bin=fopen("binar_3.bin","wb"))==NULL){ //extensie fisier binar
        printf("Fisierul nu a putut fi deschis!");
        exit(1);
    }

    fwrite(vec,sizeof(float),nr,bin);

    fclose(bin);


    //afisarea continutului fisierelor pe ecran

    float *new,*aux;

    new=(float*)malloc(sizeof(float)*nr);
    aux=(float*)malloc(sizeof(float)*nr);

    if((txt=fopen("text_3.txt","rt"))==NULL){
        printf("Fisierul text nu a putut fi deschis pentru citire!");
        exit(1);
    }

    fread(new,sizeof(float),nr,txt);

    printf("Vectorul din fisierul text este:\n");

    for(int i=0;i<nr;i++) printf("%3.5f ",*(new+i));

    fclose(txt);

    printf("\n");

    if((bin=fopen("binar_3.bin","rb"))==NULL){
        printf("Fisierul binar nu a putut fi deschis pentru citire!");
        exit(1);
    }

    fread(aux,sizeof(float),nr,bin);

    printf("Vectorul din fisierul binar este:\n");

    for(int i=0;i<nr;i++) printf("%3.5f ",*(aux+i));

    fclose(bin);

    return 0;
}