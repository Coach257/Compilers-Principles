#include<stdio.h>
#include<string.h>
FILE *inputfile;
char CHAR;
char TOKEN[105];
int num;
int len;
int isEOF=0;
char GETCHAR(){
	CHAR=fgetc(inputfile);
	if(CHAR==EOF)isEOF=1;
	return CHAR;
}
void clearToken(){
	memset(TOKEN,0,sizeof(TOKEN));
	TOKEN[0]='\0';
	len=0;
	return ;
}
int isSpace(){
	if(CHAR==' ')return 1;
	return 0;
}
int isNewline(){
	if(CHAR=='\r'||CHAR=='\n')return 1;
	return 0;
}
int isTab(){
	if(CHAR=='\t')return 1;
	return 0;
}
int isLetter(){
	if((CHAR>='A'&&CHAR<='Z')||(CHAR>='a'&&CHAR<='z'))return 1;
	return 0;
}
int isDigit(){
	if(CHAR>='0'&&CHAR<='9')return 1;
	return 0;
}
int isColon(){
	if(CHAR==':')return 1;
	return 0;
}
int isComma(){
	if(CHAR==',')return 1;
	return 0;
}
int isSemi(){
	if(CHAR==';')return 1;
	return 0;
}
int isEqu(){
	if(CHAR=='=')return 1;
	return 0;
}
int isPlus(){
	if(CHAR=='+')return 1;
	return 0;
}
int isStar(){
	if(CHAR=='*')return 1;
	return 0;
}
int isLpar(){
	if(CHAR=='(')return 1;
	return 0;
}
int isRpar(){
	if(CHAR==')')return 1;
	return 0;
}
void catToken(){
	TOKEN[len]=CHAR;
	len++;
	return ;
}
void retract(){
	int stat=fseek(inputfile,-1,1);
	if(stat==-1)printf("move filepoint error\n");
	return ;
}
void reserver(){
	if(strcmp(TOKEN,"BEGIN")==0)printf("Begin\n");
	else if(strcmp(TOKEN,"END")==0)printf("End\n");
	else if(strcmp(TOKEN,"FOR")==0)printf("For\n");
	else if(strcmp(TOKEN,"IF")==0)printf("If\n");
	else if(strcmp(TOKEN,"THEN")==0)printf("Then\n");
	else if(strcmp(TOKEN,"ELSE")==0)printf("Else\n");
	else printf("Ident(%s)\n",TOKEN);
}
int transNum(){
	int res=0;
	int i=0;
	for(;i<len;i++){
		res=res*10+TOKEN[i]-'0';
	}
	return res;
}
void error(){
	printf("Unknown\n");
	exit(0);
}
void getsym(){
	clearToken();
	while(isSpace()||isNewline()||isTab())GETCHAR();
	if(isEOF)exit(0); 
	if(isLetter()){
		while(isLetter()||isDigit()){
			catToken();
			GETCHAR();
		}
		if(!isEOF)retract();
		reserver();
	}
	else if(isDigit()){
		while(isDigit()){
			catToken();
			GETCHAR();
		}
		retract();
		printf("Int(%d)\n",transNum());
	}
	else if(isColon()){
		GETCHAR();
		if(isEqu())printf("Assign\n");
		else {
			retract();
			printf("Colon\n");
		}
	}
	else if(isPlus())printf("Plus\n");
	else if(isStar())printf("Star\n");
	else if(isComma())printf("Comma\n");
	else if(isLpar())printf("LParenthesis\n");
	else if(isRpar())printf("RParenthesis\n");
	else error();
	return ;
}
int main(int argc,char *argv[]){
	inputfile=fopen(argv[1],"r");
	if(inputfile==NULL){
		printf("open file error\n");
		return 0;
	}
	while(GETCHAR()!=EOF){
		getsym();	
	}
	return 0;
}
