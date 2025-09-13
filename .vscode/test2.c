#include <stdio.h>
#include <string.h>
FILE *fl=NULL;
char (*pkey)[100]=NULL;
char (*pvalue)[100]=NULL;
char key[100][100];
char value[100][100];
char input[100];
int keybool=1,raw=0,kcolumn=0,vcolumn=0;
char op;
void rfl();
void process();
int main() {
    pkey=key;
    pvalue=value;
    rfl();
    process();
    return 0;
}
void rfl(){
    fl=fopen("data.txt","r");
    while((op=fgetc(fl))!=EOF){
        if(op=='\n'){
            pkey[raw][kcolumn]='\0';
            pvalue[raw][vcolumn]='\0';
            keybool=1;
            raw++;
            kcolumn=0,vcolumn=0;
            continue;
        }else if(op==':'){
            keybool=0;
            continue;
        }
        switch(keybool){
            case 1:
                pkey[raw][kcolumn++]=op;
                break;        
            case 0:
                pvalue[raw][vcolumn++]=op;
                break;
        }
    }
    fclose(fl);
}
void process(){
    do{
        scanf("%s",input);
        if(strcmp(input,"Quit")==0)
            break;
        for(int i=0;i<=raw;i++){
            if(strcmp(input,pkey[i])==0){
                printf("%s\n",pvalue[i]);
                break;
            }else if(i==raw){
                printf("Error\n");
                break;
            }
        }
    }while(1);
}