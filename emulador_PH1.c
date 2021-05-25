// gcc emulador_PH1.c -o emulador_PH1
// ./emulador_PH1 entrada01.txt 

/*
                  OPCODE

     BINÁRIO       HEXADECIMAL     INSTRUÇÃO
    0000 0000   =     0x00      =   NOP
    0001 0000   =     0x10      =   LDR
    0010 0000   =     0x20      =   STR
    0011 0000   =     0x30      =   ADD
    0100 0000   =     0x40      =   SUB
    0101 0000   =     0x50      =   MUL
    0110 0000   =     0x60      =   DIV
    0101 0000   =     0x70      =   NOT
    1000 0000   =     0x80      =   AND
    1001 0000   =     0x90      =   OR
    1010 0000   =     0xA0;     =   XOR
    1011 0000   =     0xB0      =   JMP
    1100 0000   =     0xC0      =   JEQ
    1101 0000   =     0xD0      =   JG
    1110 0000   =     0xE0      =   JL
    1111 0000   =     0xF0      =   HLT

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int mem [256]; //vetor onde serao armazenadas as infos do arquivo
    int pc = 0; //program counter
    int ac; //acumulador
    int ri; //registrador de instrucoes
    int rem; // reg. de endr. de memoria
    int rdm; //reg. de dados de memoris
    int execut = 0; // contador de instrucoes executadas
    int endr; //endereco de onde a info esta no vetor (primeira coluna do arquivo)
    int info; //informaçao contida no endr (segunda coluna do arquivo)
    int comp [256]; //vetor para comparar os dados da memoria no final
    int indice; //indice para usar na comparacao
	
    FILE *file;
	
    if(argc != 2){
	printf("Argumentos Invalidos\n");
	exit(1);
    }
	
    file = fopen(argv[1], "r"); //abre o arquivo para leitura

    if(file == NULL){ //Nao aponta em um end de memoria (o arq nao existe)
       printf("Arquivo nao pode ser aberto \n");
       getchar();
       exit(1);
    }
    printf("Input file: %s\n", argv[1]);
    printf("\n");

    do{ // guradando todas os dados contidos no arquivo no vetor mem
	    
        fscanf( file ,"%x %x", &endr, &info);
	mem[endr] = info;
	comp[endr] = info;
        indice = endr; //o ultimo endereco da memoria ficara aqui
	    
    }while(!feof(file)); //continua lendo o arquivo ate nao haver mais o que  ler
	
    fclose(file); //fecha o arquivo
	
    do{

        // Passando as informaçoes para os registradores
        rem = pc;
        rdm = mem[rem];
        ri = rdm;

        //Testando no conj. de instruçoes do PH1
        //NOP
        if(ri == 0x00){
            pc = pc + 1; //Regra sem exceçao, utiliza 1 Byte
	    printf("NOP;\n");
	    execut++;
	    continue;
	}
        //LDR
        if(ri == 0x10){
            pc = pc + 2; //Utiliza 2 Bytes
            rdm = mem[rem +1]; // para que pegue o dado (proximo indice do vetor)
            printf("LDR %x; ", rdm);
            printf("AC <- MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = rdm; // dado contido na no end de mem vai pro ac
            execut++;
            continue;

        }
        //STR
        if(ri == 0x20){
            pc=pc + 2;
            rdm = mem[rem +1];
            printf("STR %x; ", rdm);
            printf("MEM[%x] <- AC\n", rdm);
            rem = rdm;
            rdm = ac; //reg. de mem recebe o valor contido no ac
            mem[rem] = rdm;
            execut++;
            continue;
        }
        //ADD
        if(ri == 0x30){
            pc = pc + 2;
            rdm = mem[rem +1];
            printf("ADD %x; ", rdm);
            printf("AC <- AC + MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac + rdm;
            execut++;
            continue;
        }
        //SUB
        if(ri == 0x40){
            pc = pc + 2;
            rdm = mem[rem +1];
            printf("SUB %x; ", rdm);
            printf("AC <- AC - MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac - rdm;
            execut++;
            continue;
        }
        //MUL
        if(ri == 0x50){
            pc = pc + 2;
            rdm = mem[rem +1];
            printf("MUL %x; ", rdm);
            printf("AC <- AC * MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac= ac * rdm;
            execut++;
            continue;
        }
        //DIV
        if(ri == 0x60){
            pc = pc + 2;
            rdm = mem[rem +1];
            printf("DIV %x; ", rdm);
            printf("AC <- AC / MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac= ac / rdm;
            execut++;
            continue;
        }
        //NOT
        if(ri == 0x70){
            pc = pc + 1; //1 Byte
	    printf("NOT;");
	    printf("AC <- !AC\n");
            ac = !ac;
			execut++;
			continue;
        }
	//AND
        if(ri == 0x80){
            pc = pc + 2;
            rdm = mem[rem +1];
            printf("AND %x; ", rdm);
            printf("AC <- AC & MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac & rdm;
            execut++;
            continue;
        }
        //OR
        if (ri == 0x90){
            pc = pc + 2;
            rdm = mem[rem +1];
            printf("OR %x; ", rdm);
            printf("AC <- AC | MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac | rdm;
            execut++;
            continue;
        }
        //XOR
        if (ri == 0xA0){
            pc = pc + 2;
            rdm = mem[rem +1];
            printf("XOR %x; ", rdm);
            printf("AC <- AC ^ MEM[%x]\n", rdm);
            rem = rdm;
            rdm = mem[rem];
            ac = ac ^ rdm;
            execut++;
            continue;
        }
        //JMP
        if (ri == 0xB0){
            pc = pc + 2;
	    rdm = mem[rem +1];
            printf("JMP %02x; ", rdm);
            printf("PC <- %02x\n", rdm);
            pc = rdm;
            execut++;
            continue;
        }
        //JEQ
        if(ri == 0xC0){
		pc = pc + 2;
		execut++;
              if(ac == 0){
		rdm = mem[rem +1];
                printf("JEQ %02x; ", rdm);
                printf("PC <- %02x\n", rdm);
                pc = rdm;
               }
            continue;
        }
        //JG
        if(ri == 0xD0){
		pc = pc + 2;
		execut++;
              if(ac > 0){ 
		rdm = mem[rem +1];
                printf("JG %02x; ", rdm);
                printf("PC <- %02x\n", rdm);
                pc = rdm; 
              }
            continue;
        }
        //JL
        if(ri == 0xE0){
		execut++;
		pc = pc + 2;
              if(ac < 0){
		rdm = mem[rem +1];
                printf("JL %02x; ", rdm);
                printf("PC <- %02x\n", rdm);
                pc = rdm; 
              }
            continue;
        }
	//HLT
        if(ri == 0xF0){
            pc = pc + 1; //1 Byte
	    printf("HLT;\n");
	    execut++;
	    break;
        }
        
    }while(1); //loop infinito ate o HLT (break)

    printf("\n");
    printf("%d instructions executed \n",  execut);
    printf("\n");
    printf("Registers:\n");
    printf("AC %02x \n", ac);
    printf("PC %02x \n", pc);
    printf("\n");
    printf("Memory:\n");

    int i;
    for(i = 128; i < indice + 1; i++){ // 80 = 128 ate o fim do vetor
        if(mem[i] != comp[i]){
        	printf("%x %02x\n", i, mem[i]); //mostra aquele que foi modificado
        }
    }
    return 0;

}


