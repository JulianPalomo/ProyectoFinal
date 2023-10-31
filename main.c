#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 30
#define ANSI_ENTER "\r"

#include <string.h>

#define ARCHCUENTAS "cuentas.dat"
#define ESC 27

typedef struct Empleado
{
    int dni;
    char apellido_nombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
}Empleado;

void mostrarCuenta(Empleado muestra);
int crearCuentaAdmin(Empleado* cuentaNueva);
int adminLogin(Empleado* cuentaAdmin);


int main()
{
    Empleado empleadito;

    int num1 = crearCuentaAdmin(&empleadito);
    int num2 = adminLogin(&empleadito);

    mostrarCuenta(empleadito);
    return 0;
}


int crearCuentaAdmin(Empleado* cuentaNueva)
{
    Empleado nuevaCuenta;
    Empleado verificacion;

    int flag = 0;
    char control = 0;
    char password[MAX_PASSWORD_LENGTH + 1]; // +1 para el carácter nulo de terminación

    FILE* archivoAdmin = fopen(ARCHCUENTAS,"r+b");

///PIDE DATOS

    system("cls");

    int opcion = 0;

    int bandera = 0;

    while(bandera == 0)
    {

        printf("1_ Crear Perfil Administrativon/n 2_ Crear Perfil de Tecnico/n 3_ Crear Perfil de Bioquimico/n");
        scanf("%i",&opcion);

        switch(opcion)
        {
            case 1: strcpy(nuevaCuenta.perfil,"Administrativo");
            bandera = 1;
                break;

            case 2: strcpy(nuevaCuenta.perfil,"Tecnico");
            bandera = 1;
                break;

            case 3: strcpy(nuevaCuenta.perfil,"Bioquimico");
            bandera = 1;
            break;

            default : printf("Ha ingresado una opcion inexistente");
            break;
        }
    }

    printf("Ingrese el  Usuario: ");
    fflush(stdin);

    ///USUARIO = DNI

    gets(nuevaCuenta.usuario);

    printf("Ingrese la Contraseña: ");
    fflush(stdin);


    int i = 0;
    char c;
    int j = 70;
    do
    {

        c = getch();
        j++;
        if (c == 8 && i > 0)  // Verificar si se presionó la tecla de retroceso
        {
            j--;
            j--;

            printf(" ");
            if (i > 0)
            {
                i--;
            }
        }
        else
        {
            if (c != 13 && c != 10)  // Ignorar las teclas Enter
            {
                password[i++] = c;
                printf("*");
            }
        }
    }
    while (c != 13 && c != 10 && i < MAX_PASSWORD_LENGTH);

    password[i] = '\0'; // Agregar el carácter nulo de terminación al final de la cadena

    ///CONTRASEÑA
    strcpy(nuevaCuenta.contrasenia, password);

///TERMINA DE PEDIR DATOS

    if(archivoAdmin)
    {
        while(flag == 0 && fread(&verificacion,sizeof(Empleado),1,archivoAdmin) > 0)
        {
            ///HAY CUENTA ?
            if (strcmp(nuevaCuenta.usuario, verificacion.usuario) == 0)
            {
                ///si hay cuenta...error

                system("cls");

                printf("La cuenta ingresada ya existe.");
                sleep(3);

                flag = 1;

                return flag;
            }
        }


        ///Si no hay cuenta... la crea
        if(flag == 0)
        {
            fwrite(&nuevaCuenta,sizeof(Empleado),1,archivoAdmin);
            system("cls");

            printf("Cuenta creada Exitosamente !");
            sleep(3);
            mostrarCuenta(nuevaCuenta);
            sleep(3);

            *cuentaNueva = nuevaCuenta;

            control = 27;

            fclose(archivoAdmin);
            flag = 1;

            return flag;

        }
    }

    system("cls");

    fclose(archivoAdmin);

    return flag;
}



int adminLogin(Empleado* cuentaAdmin)
{
    Empleado loginAdmin;

    char nombreUsuario[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1]; // +1 para el carácter nulo de terminación

    char control = 0;
    int flag = 0;

    FILE* archivoCuentas = fopen(ARCHCUENTAS,"rb");

///PIDE DATOS

    if(archivoCuentas)
    {
        while (control != ESC)
        {
            system("cls");

            printf("USUARIO:");
            fflush(stdin);
            gets(nombreUsuario);


            printf("Contrasenia:");

            int i = 0;
            char c;
            int j = 70;
            do
            {

                c = getch();
                j++;
                if (c == 8 && i > 0)  // Verificar si se presionó la tecla de retroceso
                {
                    j--;
                    j--;

                    printf(" ");
                    if (i > 0)
                    {
                        i--;
                    }
                }
                else
                {
                    if (c != 13 && c != 10)  // Ignorar las teclas Enter
                    {
                        password[i++] = c;
                        printf("*");
                    }
                }
            }
            while (c != 13 && c != 10 && i < MAX_PASSWORD_LENGTH);

            password[i] = '\0'; // Agregar el carácter nulo de terminación al final de la cadena

///TERMINA DE PEDIR DATOS


            ///valida los datos.
            while(flag == 0 && fread(&loginAdmin,sizeof(Empleado),1,archivoCuentas) > 0)
            {
                ///Si son validos... ingresa.
                if (strcmpi(loginAdmin.usuario, nombreUsuario) == 0 && strcmpi(loginAdmin.contrasenia, password) == 0)
                {
                    system("cls");

                    printf("Bienvenido !");
                    sleep(1);

                    flag = 1;

                    *cuentaAdmin = loginAdmin;


                    fclose(archivoCuentas);

                    return flag;

                }
            }

            ///Si no son validos...vuelve a ingresar.
            if(flag == 0)
            {
                system("cls");

                printf("Ha ingresado un Usuario o Contrasenia invalidos.\n");

                printf("Cualquier tecla para volver a intentar,ESC para salir. \n");

                control = getch();
            }


        }

    }
    system("cls");

    fclose(archivoCuentas);

    return 0;
}



void mostrarCuenta(Empleado muestra)
{
    system("cls");

    printf("Usuario: %s ",muestra.usuario);

    printf("Contrasenia: %s ",muestra.contrasenia);

    if(strcmpi(muestra.perfil,"Administrativo") == 0)
    {

        printf("Cuenta: Administrativo. ");
    }
    else if(strcmpi(muestra.perfil,"Tecnico") == 0)
    {

        printf("Cuenta: Tecnico. ");
    }
    else
    {
        printf("Cuenta: Bioquimico. ");
    }

}
