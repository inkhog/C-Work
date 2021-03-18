#include "stdio.h"
#include "stdlib.h"
#include "string.h"
char path[100];
int p=0;
void append(char c){path[p++]=c;}
struct kk{
    int x=0;
    int y=0;
    int p0=0;
    kk* last=NULL;
};
kk* pos=new kk;
void push(int y0,int x0,int p0){
    kk* np=new kk;
    np->x=x0;
    np->y=y0;
    np->p0=p;
    if(pos->last!=NULL)np->last=pos->last;
    pos->last=np;
}
void pop(int* y0,int* x0){
    pos=pos->last;
    *y0=pos->y;
    *x0=pos->x;
    p=pos->p0;
}
int main(int argc,char* argv[]) {
    if(argc!=2){printf("You must put one argument!");system("pause");return -1;}
    FILE *f=fopen(argv[1],"r");
    if(!f){printf("No such file or it's empty!");system("pause");return -1;}
    char a[43960];
    fscanf(f,"%*[^\n]\n%[^$]",a);strcat(a,"$\n");
    fclose(f);
    int line=0,column=1;
    for(int i=1;a[i]!='\n';i++,column++);
    for(int i=0;a[i]!='\0';i++)if(a[i]=='\n')line++;
    int x,y;
    x=column-2;y=line;
    bool maze[y][x];
    for(int i=0;i<y;i++)for(int j=0;j<x;j++)maze[i][j]=0;
    for(int i=0;i<y;i++)for(int j=0;j<x;j++)if(a[(column+1)*i+1+j]=='#')maze[i][j]=1;
    for(int x0=0,y0=0;;){
        if(x0==x-1&&y0==y-1)break;
        int count=0,cond=0;
        if(y0!=y-1&&maze[y0+1][x0]==0){cond+=1;count++;}//s
        if(y0!=0&&maze[y0-1][x0]==0){cond+=2;count++;}//w
        if(x0!=x-1&&maze[y0][x0+1]==0){cond+=4;count++;}//d
        if(x0!=0&&maze[y0][x0-1]==0){cond+=8;count++;}//a
        if(count==0){pop(&y0,&x0);continue;}
        if(count>1)push(y0,x0,p);
        if(cond==1||cond==3||cond==5||cond==7||cond==9||cond==11||cond==13||cond==15){
            maze[++y0][x0]=1;
            append('s');
            continue;
        }
        if(cond==2||cond==6||cond==10||cond==14){maze[--y0][x0]=1;append('w');continue;}
        if(cond==4||cond==12){maze[y0][++x0]=1;append('d');continue;}
        if(cond==8){maze[y0][--x0]=1;append('a');continue;}
    }
    for(int i=0;i<p;i++)printf("%c",path[i]);
    return 0;
}

/* sample 1
#####################
#*          #       #
########### ####### #
#   #   #   #     # #
### ### # # # ### # #
#     # # # # # #   #
##### # ### ### ### #
#       # #   #     #
####### # ### ##### #
#                  $#
#####################
*/
/* sample 2
#########################################
#*# #   #     #   #     # # # # # #     #
# # ### ### ##### ##### # # # # # ### ###
#   #         #   #       # # # #       #
### ######### # ####### ### # # ##### ###
# #           # #   # #   #   # # #   # #
# # ######### # ### # ### # ### # ### # #
#   #           # # # # # # #   #   # # #
# # ### ####### # # # # # # ### ### # # #
# # #   #   # # # # #       # #   # #   #
# ######### # # # # ####### # ### # # ###
#     #         # #   # # # #     # #   #
############### # ### # # # ##### # # ###
#   #   # #     #     #   # # #       # #
# # ### # ### # ##### ### # # ####### # #
# # #       # #     #   # #   #     #   #
### ####### ### ### # ### ### ### # # # #
# # #             #       # #     #   # #
# # ####### ### ### ##### # ####### # # #
#           #   #   #               # #$#
#########################################
 */