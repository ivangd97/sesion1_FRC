//============================================================================
//----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES ------------
//---------------------------- CURSO 2019/20 ---------------------------------
//--------Autores: Rub�n Costa Barriga e Iv�n Gonzalez Dominguez--------------
//============================================================================

#include "DataFrame.h"
#include <iostream>
#include <stdio.h>

char author[255];
int cont=0;

//Default constructor
DataFrame::DataFrame() {
    S  = 22;
    D  = 'T';
    C  = 02;
    NT = '0';
    L = 0;
    BCE = 0; }



//This procedure will send a control frame when the user press the F2 key
void DataFrame::sendDataFrame(HANDLE &portCOM) {
            EnviarCaracter(portCOM,S);
            EnviarCaracter(portCOM,D);
            EnviarCaracter(portCOM,C);
            EnviarCaracter(portCOM,NT);
            EnviarCaracter(portCOM,L);
            EnviarCadena(portCOM,Data,strlen(Data));
            EnviarCaracter(portCOM,BCE);

}

void DataFrame::sendDataFrame2(HANDLE &portCOM,char cadena[]){
    EnviarCaracter(portCOM, S);
	EnviarCaracter(portCOM, D);
	EnviarCaracter(portCOM, C);
	EnviarCaracter(portCOM, NT);
	EnviarCaracter(portCOM, L);
	EnviarCadena(portCOM, cadena, (int) L);
	EnviarCaracter(portCOM, BCE);
}

unsigned char DataFrame::getS() {
    return this->S; }

unsigned char DataFrame::getD() {
    return this->D; }

unsigned char DataFrame::getC() {
    return this->C; }

unsigned char DataFrame::getNT() {
    return this->NT; }

unsigned char DataFrame::getL() {
    return this->L; }

//Data vector size is undefined until the message is received
char *DataFrame::getData() {
    return this->Data;
}

unsigned char DataFrame::getBCE() {
    return this->BCE;
}

//After a given formula, we will calculate the bce associated to data.
unsigned char DataFrame::calculateBCE() {
    unsigned char BCE = Data[0] ;
    for(int i=1 ; i< L; i++) {
        BCE = (BCE ^ Data[i]);
    }
    if(BCE ==0 || BCE == 255) {
        BCE = 1;
    }

    return BCE;
}

//Second topic to calculate the bce of the frame
unsigned char DataFrame::calcularBCE_2(char cadena[]){
	unsigned char BCE = cadena[0];
		for (int i = 1; i < L; i++) {
			BCE = BCE ^ cadena[i];
		}
		if (BCE == 0 || BCE == 255) {
			BCE = 1;
		}
		return BCE;
}

//Show in terminal the message in the frame
void DataFrame::showData(HANDLE pantalla){
    pantalla = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (pantalla, 233);
    for(int x=0;x<this->L;x++){
            printf("%c",Data[x]);
        }
}

//Write data in the output file with a of stream
void DataFrame::writeFile(ofstream &of,HANDLE pantalla,bool log,ofstream &logStream,int &colouro,ofstream &pStream,int &line){

    if(cont!=0){
        SetConsoleTextAttribute (pantalla,colouro);
        printf("Recibiendo fichero de %s \n",author);
        pStream<<"Recibiendo fichero de "<< author<<"\n";
        if(log){logStream<<"Recibiendo fichero de "<< author<<"\n";}

    }

    if(calculateBCE() == BCE ){
        switch(line){
            case 0:
                strcpy(author,Data);
                line++;
                break;
            case 1:
                colouro = atoi(Data);
                pantalla = GetStdHandle(STD_OUTPUT_HANDLE);
                line++;
                break;

            case 2:
                of.open(Data,ios::trunc);
                line++;
                cont++;
                break;

            case 3:
                cont =0;
                of.write(Data,strlen(Data));
                break;

        }
    }else{
    printf("No se pudo escribir en el fichero.\n");
    }
}

//Set C attribute
void DataFrame::setC(unsigned char value)
{
    this->C = value;
}

//Set D attribute
void DataFrame::setD(unsigned char value)
{
    this->D = value;
}

//Set S attribute
void DataFrame::setS(unsigned char value)
{
    this->S = value;
}

//Set NT attribute
void DataFrame::setNT(unsigned char value)
{
    this->NT = value;
}
//Set L attribute
void DataFrame::setL(unsigned char value){
    this->L=value;
}

void DataFrame::insertData(unsigned char value){
    this->Data[this->L]= value;
}

void DataFrame::setBCE(unsigned char value){
    this->BCE = value;
}

//Sets char of a message
void DataFrame::setPartialData(int i, char msg) {
     this->Data[i] = msg;
}

//Sets data message
void DataFrame::setData(char msg[]){
    strcpy(Data,msg);
}



//master/slave procedure
void DataFrame::changeNT() {
	if (NT == '0') {
		NT = '1';
	} else {
		NT = '0';
	}
}


