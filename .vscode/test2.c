#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <direct.h>
    #define hhh '\\' 
#else
    #include <unistd.h>
    #define hhh '/'
#endif
FILE *fl=NULL;
char key[100][100];
char value[100][100];
char (*pkey)[100];
char (*pvalue)[100];
char input[100];
char op;
int raw=0,kcolumn=0,vcolumn=0,keybool=1;
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
    char *cwd=getcwd(NULL,0);
    int len=strlen(cwd)+1+strlen("data.txt")+1;
    char *newcwd=(char *)malloc(len);
    snprintf(newcwd, len, "%s%cdata.txt", cwd, hhh);
    fl=fopen(newcwd,"r");
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
    free(cwd);
    free(newcwd);
}
void process(){
    do{
        printf("请输入：");
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