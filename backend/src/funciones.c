#include "../include/header.h"

// Funcion para pushear nuevos elementos a la pila

void push(long element){
    if (top >= SIZE){
        printf("NO se puede agregar más elementos. \n");
        return;
    }
    top++; // Incrementar
    stack[top] = element; // Pushear
    printf("Datos pusheados OK. \n");
}

// Funcion pop

int pop(){
    if (top < 0){
        printf("Pila vacia.\n");
        return INT_MIN;
    }
    return stack[top--];
}

// Declaracion de funcion para realizar push-pop

void push(long element);
int  pop();