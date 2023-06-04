//
// Created by Maximo Chattas on 29/05/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "EasyPIO.h"

#define PASSWORD_LENGTH 5
#define port_out 0x208
#define port_in  0x209
//
void disp_binary (int);

void getPassword(char *password);
void menu();
void autoFantastico();
void choque();
void secuencia3();
void secuencia4();

struct termios modifyTerminalConfig(void);
void restoreTerminalConfig(struct termios);
bool escapeHit (void);
void pinSetup(void);
//

const unsigned char led[] = {14, 15, 18, 23, 24, 25, 8, 7};

int main (void)
{
//    pinSetup();
    char setPassword[5] = {'h', 'e', 'l', 'l', 'o'};
    char passwordInput[5];

    //Receive password and checks it
    //If it receives an incorrect password 3 times, it aborts
    for (int i = 0 ; i < 3 ; i++)
    {
        bool passwordFlag = true;
        getPassword(passwordInput);

        for(int j = 0 ; j < 5 ; j++)
        {
            if(setPassword[j] != passwordInput[j])
            {
                passwordFlag = false;
                break;
            }
        }

        if (passwordFlag)
        {
            printf("Bienvenido al sistema !\n\n");
            menu();
            printf("Hasta luego !\n");
            break;
        } else {
            printf("Clave incorrecta\n\n");
        }

    }
}

void disp_binary (int i)
{
    int t;
    for(t=128; t>0; t=t/2)
        if(i&t) printf("1 ");
        else printf("0 ");
    printf("\n");
}

void getPassword(char *password) {

    struct termios oldattr = modifyTerminalConfig();

    printf("Ingrese su clave: ");

    // Read the password
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        password[i] = getchar();
        printf("*"); // Print asterisk
        fflush(stdout);
    }

    restoreTerminalConfig(oldattr);

    printf("\n");
}

void menu() {
    int opcion;

    do {
        printf("Seleccione una opcion:\n");
        printf("1: Auto Fantastico\n");
        printf("2: El Choque\n");
        printf("3: Secuencia 3\n");
        printf("4: Secuencia 4\n");
        printf("0: Salir\n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                autoFantastico();
                break;
            case 2:
                choque();
                break;
            case 3:
                secuencia3(); //Race shift lights
                break;
            case 4:
                secuencia4();
                break;
            case 0:
                break;
            default:
                printf("Seleccione una opcion valida\n");
        }
    } while (opcion != 0);
}

void autoFantastico() {
    printf("Presione esc para finalizar la secuencia\n");

    unsigned char output;
    while(!escapeHit())
    {
        output = 0x80;
        for (int i = 0 ; i < 8 ; i++)
        {
            disp_binary(output);
            output = output >> 1;
            delayMillis(100);
        }
        output = 0x2;

        for (int i = 0 ; i < 6 ; i++)
        {
            disp_binary(output);
            output = output << 1;
            delayMillis(100);
        }

    }

}

void choque() {
    printf("Choque\n");

}

void secuencia3() {
    printf("Secuencia 3\n");

}

void secuencia4() {
    printf("Secuencia 4\n");

}

struct termios modifyTerminalConfig(void) {
    struct termios oldattr, newattr;

    // Get the current terminal attributes
    tcgetattr(STDIN_FILENO, &oldattr);

    // Copy the current attributes to the new attributes
    newattr = oldattr;

    // Disable canonical mode and echo
    newattr.c_lflag &= ~(ICANON | ECHO);

    // Apply the new attributes to the terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    return oldattr;
}

void restoreTerminalConfig(struct termios oldattr) {

    // Restore the original terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}

bool escapeHit (void) {

    struct termios oldattr = modifyTerminalConfig();
    int ch, oldf;

    // Set the file descriptor of the standard input to non-blocking mode
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Attempt to read a character from the standard input
    ch = getchar();

    restoreTerminalConfig(oldattr);

    // Restore the file descriptor mode
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // If esc key is hit, return 1
    if (ch == '\033') {
        ungetc(ch, stdin);
        return 1;
    }

    // Esc wasn't read, return 0
    return 0;
}

void pinSetup(void) {
    pioInit();

    for (int i = 0 ; i < 8 ; i++)
    {
        pinMode(led[i], OUTPUT);
    }

}
