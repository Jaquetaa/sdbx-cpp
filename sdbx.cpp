#include <iostream>
#include <cstdlib>    // rand, srand
#include <ctime>      // time(0)
#include <cctype>     // toupper
#include <conio.h>    // _getch() (Windows)
#include <windows.h>  // Sleep(), GetStdHandle(), SetConsoleTextAttribute()
#include <locale>     // para suportar acentos
#include <string>

using namespace std;

//--------------------------------------------------------------------
// Cor, Cls, locale
void setColor(int corTexto, int corFundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, corFundo * 16 + corTexto);
}

void Cls() {
    system("cls");
}

//--------------------------------------------------------------------
// Função que converte uma tecla (W/A/S/D) numa palavra para exibir
string moveToWord(char mv) {
    switch(mv) {
        case 'W': return "Cima";
        case 'A': return "Esquerda";
        case 'S': return "Baixo";
        case 'D': return "Direita";
    }
    return "Desconhecido";
}

//--------------------------------------------------------------------
// Instruções do Pedra-Papel-Tesoura (RPS)
void showRpsInstructions() {
    Cls();
    setColor(1,0);
    setColor(1,0); cout << "=========================================================\n";
setColor(15,0); cout << "             Instruções: "; setColor(7,0); cout << "Pedra-Papel-Tesoura\n";
    setColor(1,0); cout << "=========================================================\n";
    setColor(15,0);
    cout << "\nÉ jogado Pedra-Papel-Tesoura para decidir quem têm o primeiro turno no shadow-box.\n";
    cout << "Quem ganhar, ataca primeiro no jogo!\n\n";
    cout << "Tens as seguintes opções:\n";
    setColor(3,0); cout << "1) "; setColor(15,0); cout << "Pedra\n";
    setColor(3,0); cout << "2) "; setColor(15,0); cout << "Papel\n";
    setColor(3,0); cout << "3) "; setColor(15,0); cout << "Tesoura\n";

    cout << "\nPrima "; setColor(9,0); cout << "qualquer tecla" ; setColor(15,0); cout << " para voltar...\n";
    _getch();
    Cls();
}

//--------------------------------------------------------------------
// Decide quem ataca primeiro via Pedra-Papel-Tesoura
// Se o jogador pressionar '?' em vez de 1/2/3, mostra as instruções
bool playRockPaperScissors() {
    while (true) {
    Cls();
    cout << "\n";
    setColor(1,0); cout << "=========================================================\n";
    setColor(15,0); cout << "                       Shadow-Box                       \n";
    setColor(7,0); cout << "                  Pedra-Papel-Tesoura                  \n";
    setColor(1,0); cout << "=========================================================\n";
    setColor(3,0); cout << "1) "; setColor(15,0); cout << "Pedra\n";
    setColor(3,0); cout << "2) "; setColor(15,0); cout << "Papel\n";
    setColor(3,0); cout << "3) "; setColor(15,0); cout << "Tesoura\n";
    setColor(9,0); cout << "---------------------------------------------------------\n";
    setColor(3,0); cout << "?) "; setColor(15,0); cout << "Como Jogar?\n";
        
        char ch = _getch();
        ch = toupper(ch);

        
        if (ch == '?') {
            showRpsInstructions();
            continue;
        }
        
        int playerChoice = ch - '0'; // converte '1','2','3' para 1,2,3
        if (playerChoice < 1 || playerChoice > 3) {
    cout << "\n\n\n";
    setColor(4,0); cout << "=========================================================\n";
    setColor(15,0); cout << "                    Escolha inválida                    \n";
    setColor(4,0); cout << "=========================================================\n";
    Sleep(2000);
            continue;
        }
        
    setColor(1,0); cout << "\n=========================================================";
        int computerChoice = (rand() % 3) + 1;
        setColor(15,0);
        cout << "\n                  O computador escolheu:\n";
        if (computerChoice == 1)      cout << "                          Pedra\n";
        else if (computerChoice == 2) cout << "                           Papel\n";
        else                          cout << "                          Tesoura\n";
    	setColor(9,0); 
        cout << "---------------------------------------------------------\n";
        
        if (playerChoice == computerChoice) {
        setColor(6,0);
        cout << "                          Empate\n";
    	setColor(1,0);
        cout << "=========================================================";
            Sleep(2000);
            continue;
        }
        // Pedra vence Tesoura, Tesoura vence Papel, Papel vence Pedra.
        bool playerWins = false;
        if ((playerChoice == 1 && computerChoice == 3) ||
            (playerChoice == 3 && computerChoice == 2) ||
            (playerChoice == 2 && computerChoice == 1)) {
            playerWins = true;
        }
        
        if (playerWins) {
        setColor(2,0);
        cout << "             Ganhaste "; setColor(15,0); cout << "o Pedra-Papel-Tesoura!            ";
    		setColor(1,0); cout << "\n=========================================================";
            Sleep(2000);
            setColor(15,0);
            return true;   // o jogador ataca primeiro
        } else {
        setColor(4,0);
        cout << "             Perdeste "; setColor(15,0); cout << "o Pedra-Papel-Tesoura!            ";
    		setColor(1,0); cout << "\n=========================================================";
            Sleep(2000);
            setColor(15,0);
            return false;  // o computador ataca primeiro
        }
    }
}

//--------------------------------------------------------------------
// Shadow Boxing
// Array fixo com os movimentos possíveis
static char allMoves[4] = {'W','A','S','D'};
// Array de booleanos para indicar quais movimentos estão disponíveis
static bool isAvailable[4] = {true, true, true, true};

// Mostra as instruções do Shadow Boxing (quando se prima '?')
void showShadowBoxInstructions(int round, bool playerIsAttacker) {
    Cls();
    setColor(1,0); cout << "=========================================================\n";
setColor(15,0); cout << "                Instruções: "; setColor(7,0); cout << "Shadow-Boxing\n";
    setColor(1,0); cout << "=========================================================\n";
    cout << "\n";
	setColor(9,0);
	cout << "Jogadores:\n";
	setColor(3,0); cout << "- "; setColor(15,0); cout << "Tu (Jogador)\n";
	setColor(3,0); cout << "- "; setColor(15,0); cout << "Computador (Inimigo)\n\n";
	setColor(9,0);
	cout << "Regras:\n";

	setColor(3,0); cout << "--> "; setColor(15,0); cout << "O jogo têm 3 rondas, quem ganhar a terceira ganha o jogo.\n";
	setColor(3,0); cout << "--> "; setColor(15,0); cout << "Apenas se pode jogar para cima, esquerda, direita ou abaixo.\n";
	setColor(3,0); cout << "--> "; setColor(15,0); cout << "Não se pode atacar nem defender em direções repetidas:\n";
	setColor(8,0); cout << "  -  (Exemplo: Se esquerda já foi jogado na rondas anteriores, não se pode atacar denovo ou desviar para a esquerda)\n";
	setColor(3,0); cout << "--> "; setColor(15,0); cout << "Quando o defensor desvia um ataque, o jogo volta á ronda 1 e todos os ataques voltam a estar disponíveis denovo.\n\n";
	setColor(9,0); cout << "Como Jogar?: "; setColor(4,0); cout << "(ATACAR)\n"; setColor(15,0);
    cout << "O objetivo é tentar prever e jogar na mesma direção do que o inimigo.\n";
    cout << "\n";
	setColor(9,0); cout << "Como Jogar?: "; setColor(11,0); cout << "(DEFENDER)\n"; setColor(15,0);
    cout << "O objetivo é tentar não jogar na mesma direção do inimigo, para o turno de atacar passar para ti.\n";

    cout << "\n\nPrima "; setColor(9,0); cout << "qualquer tecla" ; setColor(15,0); cout << " para voltar...\n";
    _getch();
    Cls();
    
    // Re-exibe o estado atual do jogo
    cout << "========================= Ronda " << round << " =========================\n";
    if (playerIsAttacker)
        cout << "Tu és o ATACANTE.\n";
    else
        cout << "O computador é o ATACANTE.\n";
    
    cout << "Movimentos disponíveis: ";
    for (int i = 0; i < 4; i++) {
        if (isAvailable[i])
            cout << moveToWord(allMoves[i]) << " (" << allMoves[i] << ")  ";
    }
    cout << "\n";
}

//--------------------------------------------------------------------
// Restaura todos os movimentos (marca-os como disponíveis)
void restoreAllMoves() {
    for (int i = 0; i < 4; i++) {
        isAvailable[i] = true;
    }
}

//--------------------------------------------------------------------
// Remove um movimento, marcando-o como indisponível
void removeMove(char mv) {
    for (int i = 0; i < 4; i++) {
        if (allMoves[i] == mv) {
            isAvailable[i] = false;
            return;
        }
    }
}

//--------------------------------------------------------------------
// Verifica se existe algum movimento disponível
bool anyMovesLeft() {
    for (int i = 0; i < 4; i++) {
        if (isAvailable[i])
            return true;
    }
    return false;
}

//--------------------------------------------------------------------
// Verifica se um movimento (W, A, S, D) é válido e está disponível
bool isValidAndAvailable(char mv) {
    mv = toupper(mv);
    for (int i = 0; i < 4; i++) {
        if (allMoves[i] == mv && isAvailable[i])
            return true;
    }
    return false;
}

//--------------------------------------------------------------------
// Lê o movimento do utilizador de forma imediata (W/A/S/D ou '?' para ajuda)
// Recebe o estado atual (ronda e se o jogador é o atacante) para poder restaurar esse estado
char getMoveFromUser(bool isAttacker, int round, bool playerIsAttacker) {
    while (true) {
        if (isAttacker)
            cout << "Prima W/A/S/D para ATACAR (ou '?' para ajuda): ";
        else
            cout << "Prima W/A/S/D para DEFENDER (ou '?' para ajuda): ";
        
        char c = _getch();
        c = toupper(c);
        cout << c << "\n";
        
        if (c == '?') {
            showShadowBoxInstructions(round, playerIsAttacker);
            continue; // re-prompt
        }
        
        if (isValidAndAvailable(c))
            return c;
        
        cout << "Movimento inválido ou não disponível. Tenta outra vez.\n";
    }
}

//--------------------------------------------------------------------
// Permite ao computador escolher um movimento aleatório dentre os disponíveis
char getRandomAvailableMoveForComputer() {
    int indices[4];
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (isAvailable[i]) {
            indices[count] = i;
            count++;
        }
    }
    int r = rand() % count;
    return allMoves[ indices[r] ];
}

//--------------------------------------------------------------------
// Jogo principal do Shadow Boxing (3 rondas)
// Retorna true se o jogador ganhar, false se o computador ganhar.
bool playThreeRoundGame() {
    bool playerIsAttacker = playRockPaperScissors();
    restoreAllMoves();
    Cls();
    
    int round = 1;
    while (true) {
        cout << "========================= Ronda " << round << " =========================\n";
        char attackerMove, defenderMove;
        
        if (playerIsAttacker) {
            cout << "Tu és o ATACANTE.\n";
            cout << "Movimentos disponíveis: ";
            for (int i = 0; i < 4; i++) {
                if (isAvailable[i])
                    cout << moveToWord(allMoves[i]) << " (" << allMoves[i] << ")  ";
            }
            cout << "\n";
            attackerMove = getMoveFromUser(true, round, playerIsAttacker);
            
            defenderMove = getRandomAvailableMoveForComputer();
            cout << "O computador (defensor) escolheu: " << moveToWord(defenderMove) << "\n";
        } else {
            cout << "O computador é o ATACANTE.\n";
            attackerMove = getRandomAvailableMoveForComputer();
            cout << "O computador (atacante) já escolheu um movimento (oculto).\n";
            
            cout << "Movimentos disponíveis: ";
            for (int i = 0; i < 4; i++) {
                if (isAvailable[i])
                    cout << moveToWord(allMoves[i]) << " (" << allMoves[i] << ")  ";
            }
            cout << "\n";
            defenderMove = getMoveFromUser(false, round, playerIsAttacker);
        }
        
        if (attackerMove == defenderMove) {
            cout << "Ataque bem-sucedido! Ambos escolheram " << moveToWord(attackerMove) << ".\n";
            removeMove(attackerMove);
            if (round == 3) {
                if (playerIsAttacker)
                    cout << "Conseguiste o ataque final na ronda 3! Ganhaste o jogo!\n";
                else
                    cout << "O computador conseguiu o ataque final na ronda 3! Perdes!\n";
                return playerIsAttacker;
            } else {
                round++;
                cout << "A passar para a ronda " << round << "...\n\n";
                if (!anyMovesLeft()) {
                    cout << "Não há movimentos disponíveis! Fim do jogo.\n";
                    return false;
                }
            }
        } else {
            cout << "Ataque falhado! (Esquiva)\n"
                 << "O atacante escolheu " << moveToWord(attackerMove)
                 << " enquanto o defensor escolheu " << moveToWord(defenderMove) << ".\n";
            cout << "Trocam de papéis, reiniciamos a ronda 1 com todos os movimentos disponíveis.\n\n";
            playerIsAttacker = !playerIsAttacker;
            round = 1;
            restoreAllMoves();
        }
    }
}

//--------------------------------------------------------------------
// Função principal: ciclo de jogo (RPS + Shadow Boxing) e reinicio
int main() {
    // Configurar locale para suportar acentos (Português de Portugal)
    setlocale(LC_ALL, "");
    
    srand(static_cast<unsigned int>(time(0)));
    
    while (true) {
        bool playerWon = playThreeRoundGame();
        
        cout << "\nResultado Final: ";
        if (playerWon)
            cout << "Parabéns, ganhaste o Shadow Boxing!\n";
        else
            cout << "O computador venceu o jogo.\n";
        
        cout << "\nPrima Y para recomeçar, ou N para sair: ";
        while (true) {
            char ans = _getch();
            ans = toupper(ans);
            cout << ans << "\n";
            if (ans == 'Y') {
                Cls();
                break;  // recomeça o ciclo
            } else if (ans == 'N') {
                cout << "Obrigado por jogares!\n";
                return 0;
            } else {
                cout << "Por favor, prima Y ou N.\n";
            }
        }
    }
}

