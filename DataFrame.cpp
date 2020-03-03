//============================================================================
//----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES ------------
//---------------------------- CURSO 2019/20 ---------------------------------
//--------Autores: Rub�n Costa Barriga e Iv�n Gonzalez Dominguez--------------
//============================================================================

#include "DataFrame.h"
#include <iostream>
#include <stdio.h>


//Default constructor
DataFrame::DataFrame() {
    S  = 22;
    D  = 'T';
    C  = 02;
    NT = '0';
    L = 0;
    BCE = 0; }


void DataFrame::manageFrame(HANDLE &portCOM,char msg[802],int tamanio){
    int tam=0;
	int corte = 0;
	while (tamanio > 0) {
		if (tamanio > 254) {
			tamanio -= 254;
			tam = 254;
		} else {
			tam = tamanio;
			tamanio = 0;
		}
		L = (unsigned char) tam;
		for (int j = 0; j < tam; j++) {
			Data[j] = msg[j + corte];
		}
		if(tamanio!=0){
		corte = corte + 254;
		Data[tam] = '\0';
		BCE = calculateBCE(tam,Data);
		sendFrameData(portCOM);
		}
	}

	L=(unsigned char) tam+1;
	Data[tam]='\n';
	Data[tam+1]='\0';
	BCE=calculateBCE(tam,Data);
	sendFrameData(portCOM);

}




//






//This procedure will send a control frame when the user press the F2 key
void DataFrame::sendFrameData(HANDLE &portCOM) {


            EnviarCaracter(portCOM,S);
            EnviarCaracter(portCOM,D);
            EnviarCaracter(portCOM,C);
            EnviarCaracter(portCOM,NT);
            EnviarCaracter(portCOM,L);
            EnviarCadena(portCOM,Data,strlen(Data));
            EnviarCaracter(portCOM,BCE);
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
char DataFrame::getData(int i) {
    return this->Data[i]; }
unsigned char DataFrame::getBCE() {


    return this->BCE; }

unsigned char DataFrame::calculateBCE(int x,char msg[]) {
    unsigned char BCE = msg[0] ^ msg[1];
    if(x ==1) {
        BCE = 1;

    }
    else {
        for(int i=2; i<x; i++) {
            BCE = BCE ^ msg[i];
        }
        if(BCE ==255 || BCE == 0) {
            BCE = 1; }
        }
    return BCE;

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
void DataFrame::setL(unsigned char value){
this->L=value;
}
