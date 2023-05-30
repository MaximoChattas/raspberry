//
// Created by Maximo Chattas on 29/05/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#define PASSWORD_LENGTH 5
#define port_out 0x208
#define port_in  0x209
//
void disp_binary (int);
void delay (int);

int getch(void);
void getPassword(char *password);
void menu();
void autoFantastico(int time);
void choque(int time);
void secuencia3(int time);
void secuencia4(int time);
//

int main (void)
{
    unsigned char output;
    char t;
    int on_time;  /* set holding time */
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
            if(setPassword[i] != passwordInput[i])
            {
                passwordFlag = false;
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
void delay(int time)
{
    int i;
    unsigned int j;
    for(i=time; i>0; --i) /* repeat specified number of times */
        for(j=0; j<65535; ++j);
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
    struct termios oldattr, newattr;

    // Get the current terminal attributes
    tcgetattr(STDIN_FILENO, &oldattr);

    // Copy the current attributes to the new attributes
    newattr = oldattr;

    // Disable canonical mode and echo
    newattr.c_lflag &= ~(ICANON | ECHO);

    // Apply the new attributes to the terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    printf("Ingrese su clave: ");

    // Read the password
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        password[i] = getchar();
        printf("*"); // Print asterisk
        fflush(stdout);
    }

    // Restore the original terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

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
                autoFantastico(1000);
                break;
            case 2:
                choque(1000);
                break;
            case 3:
                secuencia3(1000);
                break;
            case 4:
                secuencia4(1000);
                break;
            case 0:
                break;
            default:
                printf("Seleccione una opcion valida\n");
        }
    } while (opcion != 0);
}

void autoFantastico(int time) {
    printf("Auto Fantastico\n");

}

void choque(int time) {
    printf("Choque\n");

}

void secuencia3(int time) {
    printf("Secuencia 3\n");

}

void secuencia4(int time) {
    printf("Secuencia 4\n");

}
