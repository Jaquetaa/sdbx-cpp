#include <iostream>
#include <windows.h> // API do Windows para manipular a console

using namespace std;

// ?? Fun??o para mudar a cor do texto e do fundo
void setCorTexto(int corTexto, int corFundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, corFundo * 16 + corTexto);
}

// ?? Fun??o para limpar a tela
void limparTela() {
    system("cls");
}

// ?? Fun??o para pausar o processamento
void pausar() {
    system("pause");  // Pressione qualquer tecla para continuar...
}

// ?? Fun??o para mostrar cores dispon?veis
void mostrarCores() {
    limparTela();
    cout << "Exemplo de cores:\n\n";

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
    limparTela(); // Limpa a tela
    setCorTexto(10, 0); // Verde no fundo preto
    cout << "Texto verde no fundo preto\n";

    setCorTexto(4, 7); // Vermelho no fundo branco
    cout << "Texto vermelho no fundo branco\n";

    pausar(); // Pausa o processamento

    mostrarCores(); // Mostra todas as cores dispon?veis
pausar();
    return 0;
}

