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
    Data[0]=NULL;
    BCE = 0; }


void DataFrame::manageFrame(HANDLE &portCOM,char msg[],int tamanio){
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
		BCE = calculateBCE();
		sendFrameData(portCOM);
		}
	}

	L=(unsigned char) tam+1;
    Data[tam]='\n';
	Data[tam+1]='\0';
	BCE=calculateBCE();
	sendFrameData(portCOM);

}











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
char *DataFrame::getData() {
    return this->Data;
}

unsigned char DataFrame::getBCE() {
    return this->BCE;
}

unsigned char DataFrame::calculateBCE2() {
    unsigned char BCE = Data[0] ;
    for(int i=1 ; i< L-1; i++) {
        BCE = BCE ^ Data[i];
    }
    if(BCE ==255 || BCE == 0) {
        BCE = 1;
    }
    return BCE;
}
unsigned char DataFrame::calculateBCE(){
unsigned char bce = 0;
    for (int i = 0;i < L-1;i++){
        if(i == 0){
            bce = Data[i+1]^Data[i];
        }else{
            bce = bce ^ Data[i+1];
        }
    }
    if(bce == 255||bce == 0){
        bce = 1;
    }
    return bce;
    }

void DataFrame::showData(){
    for(int x=1;x<this->L-1;x++){
            printf("%c",Data[x]);
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
void DataFrame::setL(unsigned char value){
    this->L=value;
}
void DataFrame::insertData(int i,unsigned char value){
    this->Data[i]= value;
}
        void DataFrame::setBCE(unsigned char value){
        this->BCE = value;
        }
void DataFrame::setData(char msg[]){
    strcpy(Data,msg);

}
bool DataFrame::comprobar(){
    unsigned char bce = calculateBCE();
	if (bce == getBCE()) {
		return true;
	} else {
		return false;
	}

}

