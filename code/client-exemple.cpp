/*  client side */
/* Ce client windows permet d'envoyer des donnée à une adresse ip */
#include <winsock2.h> //fonction socket windows
#include <stdlib.h>
#include <stdio.h>
#include <cstdio> //pour les Sprintf

WSADATA initialisation_win32;

int erreur;
int tempo;
int phrase = 0;
int numberChar;
char buffer[65535]; //tampon contenant les donnees recues ou envoyee

SOCKET socketId;
SOCKADDR_IN destInfo;


int main(int argc, char* argv[])
{
    printf("\n Bienvenue, vous etes du cote client \n");

    //Initialisation de Winsock

    erreur = WSAStartup(MAKEWORD(2,2), &initialisation_win32);
    if(erreur != 0)
        printf("\nWSAStartup : [FAIL] : Desole, ne peux pas initialiser Winsock2 : %d %d", erreur, WSAGetLastError());
    else
        printf("\nWSAStartup : [OK]");

    //Ouverture d'une Socket

    socketId = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketId == INVALID_SOCKET)
        printf("\nSocket : [FAIL] : Desole, ne peux pas creer la socket, erreur : %d", WSAGetLastError());
    else
        printf("\nSocket : [OK]");

    //Envois de donnees

    destInfo.sin_family = AF_INET; //IPV4
    destInfo.sin_addr.s_addr = inet_addr("172.16.1.52"); //adresse du serveur
    destInfo.sin_port = htons(888);

    while(true)
    {
        strcpy(buffer, "DONNEEESSSSSS!!!!\n");
        numberChar = sendto(socketId, buffer, strlen(buffer), 0, (struct sockaddr*)&destInfo, sizeof(destInfo));
        Sleep(10);
    }

    if(numberChar == SOCKET_ERROR)
        printf("\nSend : [FAIL] : Desole, ne peux pas envoyer les donnees du a l'erreur : %d", WSAGetLastError());
    else
        printf("\nSend : [OK]");

    //fermeture de la socket correspondant a la commande socket()

    erreur = closesocket(socketId);
    if(erreur != 0)
        printf("\nClosesocket : [FAIL] : Desole, ne peux pas liberer la socket du a l'erreur = %d %d", erreur, WSAGetLastError());
    else
        printf("\nClosesocket : [OK]");

    //quitte proprement le winsock ouvert avec la commande WSAStartup

    erreur = WSACleanup();

    if(erreur != 0)
        printf("\nWSACleanup : [FAIL] : Desole, ne peux pas liberer winsock du a l'erreur : %d %d", erreur, WSAGetLastError());
    else
        printf("\nWSACleanup : [OK]");
}
