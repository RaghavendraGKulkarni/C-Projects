#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Table
{
    char* name;
    unsigned int addr;
};
typedef struct Table table;
void tokenize(char line[100],char label[10],char opcode[10],char operand[10])
{
    char cpy[100],*token;
    int count=0;
    strcpy(cpy,line);
    token=strtok(line," \t");
    while(token)
    {
        count++;
        token=strtok(NULL," \t");
    }
    strcpy(line,cpy);
    switch(count)
    {
        case 1:strcpy(label,"\t");
                label[8]='\0';
                token=strtok(line," \t");
                strcpy(opcode,token);
                opcode[strlen(token)]='\0';
                operand[8]='\0';
                strcpy(operand,"\t");
                break;
        case 2:strcpy(label,"\t");
                label[8]='\0';
                token=strtok(line," \t");
                strcpy(opcode,token);
                opcode[strlen(token)]='\0';
                token=strtok(NULL," \t");
                strcpy(operand,token);
                operand[strlen(token)]='\0';
                break;
        case 3:token=strtok(line," \t");
                strcpy(label,token);
                label[strlen(token)]='\0';
                token=strtok(NULL," \t");
                strcpy(opcode,token);
                opcode[strlen(token)]='\0';
                token=strtok(NULL," \t");
                strcpy(operand,token);
                operand[strlen(token)]='\0';
                break;
        default:
                break;
    }
    return;
}
int search(table *TAB,int size,char word[10])
{
    int i;
    for(i=0;i<size;i++)
        if(strcmp(TAB[i].name,word)==0)
            return TAB[i].addr;
    return -1;
}
int main()
{
    int opcodes=0,symbols=0,i=0,j,codes;
    unsigned int LOCCTR,SA=0,programLength,TA;
    char line[100],*token,label[10],opcode[10],operand[10],objectCode[6],**objectCodeList;
    FILE *optab,*sic,*intermediateFile,*objectFile;
    table *OPTAB,*SYMTAB;
    optab=fopen("Optab.txt","r");
    if(!optab)
    {
        printf("Unable to read Optab!!\n");
        exit(0);
    }
    OPTAB=(table*)malloc(sizeof(table));
    while(!feof(optab))
    {
        fgets(line,sizeof(line),optab);
        if(line[strlen(line)-1]=='\n')
            line[strlen(line)-1]='\0';
        if(strlen(line))
        {
            token=strtok(line," \t");
            OPTAB=(table*)realloc(OPTAB,(opcodes+1)*sizeof(table));
            OPTAB[opcodes].name=(char*)malloc(sizeof(token));
            strcpy(OPTAB[opcodes].name,token);
            token=strtok(NULL," \t");
            OPTAB[opcodes].addr=(unsigned int)strtoul(token,NULL,16);
            opcodes++;
        }
    }
    fclose(optab);
    sic=fopen("sic.txt","r");
    if(!sic)
    {
        printf("Unable to read the SIC Program!!\n");
        exit(0);
    }
    intermediateFile=fopen("Intermediate File.txt","w");
    if(!intermediateFile)
    {
        printf("Unable to write to the Intermediate File!!\n");
        exit(0);
    }
    fgets(line,sizeof(line),sic);
    if(line[strlen(line)-1]=='\n')
        line[strlen(line)-1]='\0';
    tokenize(line,label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        SA=(unsigned int)strtoul(operand,NULL,16);
        LOCCTR=SA;
        fprintf(intermediateFile,"%X %s %s %s\n",LOCCTR,label,opcode,operand);
        fgets(line,sizeof(line),sic);
        if(line[strlen(line)-1]=='\n')
            line[strlen(line)-1]='\0';
        tokenize(line,label,opcode,operand);
    }
    else
        LOCCTR=0;
    SYMTAB=(table*)malloc(sizeof(table));
    while(strcmp(opcode,"END")!=0)
    {
        fprintf(intermediateFile,"%X ",LOCCTR);
        if(line[0]!=';')
        {
            if(strcmp(label,"\t")!=0)
            {
                if(search(SYMTAB,symbols,label)!=-1)
                {
                    printf("Duplicate symbol found at %s %s %s\n",label,opcode,operand);
                }
                else
                {
                    SYMTAB=(table*)realloc(SYMTAB,(symbols+1)*sizeof(table));
                    SYMTAB[symbols].name=(char*)malloc(sizeof(label));
                    strcpy(SYMTAB[symbols].name,label);
                    SYMTAB[symbols].addr=LOCCTR;
                    symbols++;
                }
            }
            if(search(OPTAB,opcodes,opcode)!=-1)
            {
                if(opcode[0]=='+')
                    LOCCTR+=4;
                else
                    LOCCTR+=3;
            }
            else if(strcmp(opcode,"WORD")==0)
                LOCCTR+=3;
            else if(strcmp(opcode,"RESW")==0)
                LOCCTR+=(3*((unsigned int)(strtoul(operand,NULL,16))));
            else if(strcmp(opcode,"RESB")==0)
                LOCCTR+=((unsigned int)(strtoul(operand,NULL,16)));
            else if(strcmp(opcode,"BYTE")==0)
                LOCCTR+=((unsigned int)((strrchr(operand,(int)'\''))-(strchr(operand,(int)'\''))-1));
            else
            {
                printf("Invalid opcode at %s %s %s\n",label,opcode,operand);
            }
        }
        fprintf(intermediateFile,"%s %s %s\n",label,opcode,operand);
        fgets(line,sizeof(line),sic);
        if(line[strlen(line)-1]=='\n')
            line[strlen(line)-1]='\0';
        tokenize(line,label,opcode,operand);
    }
    fprintf(intermediateFile,"%X %s %s %s",LOCCTR,label,opcode,operand);
    fclose(intermediateFile);
    fclose(sic);
    programLength=LOCCTR-SA;
    printf("Pass 1 successfully completed\n\n");
    intermediateFile=fopen("Intermediate File.txt","r");
    if(!intermediateFile)
    {
        printf("Unable to read the Intermediate File!!\n");
        exit(0);
    }
    objectFile=fopen("Object Code File.txt","w");
    if(!objectFile)
    {
        printf("Unable to write to the Object Code File!!\n");
        exit(0);
    }
    fscanf(intermediateFile,"%X",&LOCCTR);
    fgets(line,sizeof(line),intermediateFile);
    if(line[strlen(line)-1]=='\n')
        line[strlen(line)-1]='\0';
    tokenize(line,label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        fprintf(objectFile,"H^%s",label);
        i=6-strlen(label);
        while(i--)
            fprintf(objectFile," ");
        fprintf(objectFile,"^%06X^%06X\n",SA,programLength);
        fscanf(intermediateFile,"%X",&LOCCTR);
        fgets(line,sizeof(line),intermediateFile);
        if(line[strlen(line)-1]=='\n')
            line[strlen(line)-1]='\0';
        tokenize(line,label,opcode,operand);
    }
    objectCodeList=(char**)malloc(sizeof(char*));
    codes=0;
    while(strcmp(opcode,"END")!=0)
    {
        if(line[0]!=';')
        {
            strcpy(objectCode,"");
            i=search(OPTAB,opcodes,opcode);
            if(i!=-1)
            {
                if(strcmp(operand,"\t")!=0)
                {
                    for(j=0;operand[j]!='\0';j++)
                        if(operand[j]==',')
                            break;
                    if(operand[j]==',' && operand[j+1]=='X')
                        operand[j]='\0';
                    else if(operand[j]==',' && operand[j+1]!='X')
                    {
                        printf("Invalid Addressing Mode at %s\t%s\t%s\n",label,opcode,operand);
                        j=-1;
                    }
                    if(j!=-1)
                        j=search(SYMTAB,symbols,operand);
                    if(j==-1)
                    {
                        printf("Undefined symbol at %s\t%s\t%s\n",label,opcode,operand);
                        j=0;
                    }
                }
                else
                    j=0;
                sprintf(objectCode,"%02X%04X",i,j);
            }
            else if(strcmp(opcode,"WORD")==0)
                sprintf(objectCode,"%06X",(unsigned int)strtoul(operand,NULL,16));
            else if(strcmp(opcode,"BYTE")==0)
            {
                i=0;
                while(operand[i]!='\'')
                    i++;
                i++;
                while(operand[i]!='\'')
                {
                    sprintf(token,"%02X",operand[i]);
                    strcat(objectCode,token);
                    i++;
                }
            }
            if(strlen(objectCode))
            {
                objectCodeList=(char**)realloc(objectCodeList,(codes+1)*(sizeof(char*)));
                objectCodeList[codes]=(char*)malloc(sizeof(objectCode));
                strcpy(objectCodeList[codes],objectCode);
                codes++;
            }
            if(codes==1)
                TA=LOCCTR;
            if(codes==10)
            {
                fprintf(objectFile,"T^%06X^%02X",TA,codes*3);
                for(i=0;i<codes;i++)
                    fprintf(objectFile,"^%06s",objectCodeList[i]);
                fprintf(objectFile,"\n");
                codes=0;
            }
        }
        fscanf(intermediateFile,"%X",&LOCCTR);
        fgets(line,sizeof(line),intermediateFile);
        if(line[strlen(line)-1]=='\n')
            line[strlen(line)-1]='\0';
        tokenize(line,label,opcode,operand);
    }
    if(codes>0)
    {
        fprintf(objectFile,"T^%06X^%02X",TA,codes*3);
        for(i=0;i<codes;i++)
            fprintf(objectFile,"^%06s",objectCodeList[i]);
        fprintf(objectFile,"\n");
    }
    fprintf(objectFile,"E^%06X",SA);
    fclose(intermediateFile);
    free(OPTAB);
    free(SYMTAB);
    free(objectCodeList);
    fclose(objectFile);
    printf("Pass 2 successfully completed.\n\nLength of the program = %d bytes.\n",programLength);
    return 0;
}
