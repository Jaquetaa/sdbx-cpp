#include <iostream>
#include <windows.h> // API do Windows para manipular a console

using namespace std;

// ?? Fun??o para mudar a cor do texto e do fundo
void setCorTexto(int corTexto, int corFundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, corFundo * 16 + corTexto);
}

// ?? Fun??o para pausar o processamento
void pausar() {
    system("pause");  // Pressione qualquer tecla para continuar...
}

// ?? Fun??o para mostrar cores dispon?veis
void mostrarCores() {

    for (int fundo = 0; fundo < 8; fundo++) {
        for (int texto = 0; texto < 16; texto++) {
            setCorTexto(texto, fundo);
            cout << "Texto " << texto << " Fundo " << fundo << "  ";
        }
        cout << endl;
    }

    // Restaurar para branco sobre preto
    setCorTexto(7, 0);
}

int main() {

    mostrarCores(); // Mostra todas as cores dispon?veis
pausar();
    return 0;
}

