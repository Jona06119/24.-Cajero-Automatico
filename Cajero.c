#include <stdio.h>

#define PIN_CORRECTO 1234
#define ARCHIVO "movimientos.txt"

static void registrar(const char *tipo, double cantidad, double saldo) {
    FILE *f = fopen(ARCHIVO, "a");
    if (f) {
        fprintf(f, "%s | Importe: %.2f | Saldo: %.2f\n", tipo, cantidad, saldo);
        fclose(f);
    } else {
        puts("Advertencia: no se pudo guardar el movimiento.");
    }
}

int main(void) {
    int pin, intentos = 0, opcion;
    double saldo = 5000.00, cantidad;

    puts("=== CAJERO AUTOMATICO | SIMULADOR ===");
    while (intentos < 3) {
        printf("Introduce tu PIN de prueba: ");
        if (scanf("%d", &pin) != 1) {
            puts("Entrada invalida."); return 1;
        }
        if (pin == PIN_CORRECTO) break;
        intentos++;
        printf("PIN incorrecto. Intentos restantes: %d\n", 3 - intentos);
    }
    if (intentos == 3) {
        puts("Acceso bloqueado por seguridad.");
        return 1;
    }

    do {
        puts("\n1. Consultar saldo");
        puts("2. Depositar");
        puts("3. Retirar");
        puts("4. Salir");
        printf("Opcion: ");
        if (scanf("%d", &opcion) != 1) {
            puts("Entrada invalida."); return 1;
        }

        switch (opcion) {
            case 1:
                printf("Saldo disponible: $%.2f\n", saldo);
                break;
            case 2:
                printf("Importe a depositar: $");
                if (scanf("%lf", &cantidad) != 1 || cantidad <= 0) {
                    puts("Importe invalido."); return 1;
                }
                saldo += cantidad;
                registrar("DEPOSITO", cantidad, saldo);
                printf("Deposito realizado. Nuevo saldo: $%.2f\n", saldo);
                break;
            case 3:
                printf("Importe a retirar: $");
                if (scanf("%lf", &cantidad) != 1 || cantidad <= 0) {
                    puts("Importe invalido."); return 1;
                }
                if (cantidad > saldo) {
                    puts("Fondos insuficientes.");
                } else {
                    saldo -= cantidad;
                    registrar("RETIRO", cantidad, saldo);
                    printf("Retiro realizado. Nuevo saldo: $%.2f\n", saldo);
                }
                break;
            case 4:
                puts("Gracias por utilizar el simulador.");
                break;
            default:
                puts("Opcion no valida.");
        }
    } while (opcion != 4);
    return 0;
}
