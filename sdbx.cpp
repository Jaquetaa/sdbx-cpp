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
// Cor, Cls
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
        case 'W': return "W";
        case 'A': return "A";
        case 'S': return "S";
        case 'D': return "D";
    }
    return "???";
}

//--------------------------------------------------------------------
// Instruções do Pedra-Papel-Tesoura (RPS)
void showRpsInstructions() {
    Cls();
    setColor(1,0);
    cout << "=========================================================\n";
    setColor(15,0);
    cout << "             Instruções: Pedra-Papel-Tesoura\n";
    setColor(1,0);
    cout << "=========================================================\n";
    setColor(15,0);
    cout << "\nÉ jogado Pedra-Papel-Tesoura para decidir quem têm o primeiro turno no shadow-box.\n";
    cout << "Quem ganhar, ataca primeiro no jogo!\n\n";
    cout << "Tens as seguintes opções:\n";
    setColor(3,0); cout << "1) "; setColor(15,0); cout << "Pedra\n";
    setColor(3,0); cout << "2) "; setColor(15,0); cout << "Papel\n";
    setColor(3,0); cout << "3) "; setColor(15,0); cout << "Tesoura\n";
    cout << "\nPrima "; setColor(9,0); cout << "qualquer tecla"; setColor(15,0); cout << " para voltar...\n";
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
            cout << "\n";
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
        if (computerChoice == 1)      cout << "                           Pedra\n";
        else if (computerChoice == 2) cout << "                           Papel\n";
        else                          cout << "                          Tesoura\n";
        setColor(9,0); 
        cout << "---------------------------------------------------------\n";
        
        if (playerChoice == computerChoice) {
            setColor(6,0);
            cout << "                          Empatou\n";
            setColor(1,0);
            cout << "=========================================================";
            Sleep(1500);
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

// Função para exibir as instruções do Shadow Boxing (quando se prima '?')
void showShadowBoxInstructions(int round, bool playerIsAttacker) {
    Cls();
    setColor(1,0); cout << "=========================================================\n";
    setColor(15,0); cout << "                Instruções: "; setColor(7,0); cout << "Shadow-Boxing\n";
    setColor(1,0); cout << "=========================================================\n";
    cout << "\n";
    setColor(9,0);
    cout << "Jogadores:\n";
    setColor(3,0); cout << "- "; setColor(15,0); cout << "Tu "; setColor(11,0); cout << "(Jogador)\n"; setColor(15,0);
    setColor(3,0); cout << "- "; setColor(15,0); cout << "Computador "; setColor(4,0); cout << "(Inimigo)\n\n"; setColor(15,0);
    setColor(9,0);
    cout << "Regras:\n";
    setColor(3,0); cout << "--> "; setColor(15,0); cout << "O jogo tem 3 rondas; quem ganhar a terceira ronda vence o jogo.\n";
    setColor(3,0); cout << "--> "; setColor(15,0); cout << "Só se pode jogar para cima, esquerda, direita ou abaixo.\n";
    setColor(3,0); cout << "--> "; setColor(15,0); cout << "Não se pode atacar nem defender em direções repetidas:\n";
    setColor(8,0); cout << "  -  (Exemplo: Se esquerda já foi jogado em rondas anteriores, não se pode jogar esquerda de novo.)\n";
    setColor(3,0); cout << "--> "; setColor(15,0); cout << "Quando o defensor esquiva um ataque, o jogo reinicia para a ronda 1 e todos os movimentos ficam disponíveis denovo.\n";
    cout << "\n";
    setColor(9,0); cout << "Teclas (WASD):\n";
    setColor(3,0); cout << "W) "; setColor(15,0); cout << "Cima\n";
    setColor(3,0); cout << "A) "; setColor(15,0); cout << "Esquerda\n";
    setColor(3,0); cout << "S) "; setColor(15,0); cout << "Baixo\n";
    setColor(3,0); cout << "D) "; setColor(15,0); cout << "Direita\n";
    setColor(8,0); cout << "-- Se a cor dos ataques disponíveis estiver mais escuro, significa que não está disponível.\n";
    cout << "\n";
    setColor(9,0); cout << "Como Jogar? (ATACAR): "; setColor(4,0); cout << "\n   - O objetivo é tentar prever e jogar na mesma direção que o inimigo.\n";
    setColor(9,0); cout << "Como Jogar? (DEFENDER): "; setColor(11,0); cout << "\n   - O objetivo é tentar não jogar na mesma direção que o inimigo, para assim ganhar o turno de atacar.\n"; setColor(15,0);
    cout << "\n\nPrima "; setColor(9,0); cout << "qualquer tecla"; setColor(15,0); cout << " para voltar...\n";
    _getch();
    Cls();
    
    // Re-exibe o estado atual do jogo:
    if (round == 1)
        setColor(2,0); // verde
    else if (round == 2)
        setColor(6,0); // amarelo
    else if (round == 3)
        setColor(4,0); // vermelho
    cout << "========================= Ronda " << round << " =========================\n";
    setColor(15,0);
    
if (playerIsAttacker) {
    setColor(3, 0);
    cout << "?) ";
    setColor(15, 0);
    cout << "Como Jogar?\n\n";
} else {
    setColor(3, 0);
    cout << "?) ";
    setColor(15, 0);
    cout << "";
}
    
    setColor(9,0);
    cout << "Ataques disponíveis: ";
        for (int i = 0; i < 4; i++) {
            if (isAvailable[i])
            setColor(3,0); cout << "\n- "; setColor(15,0); cout << moveToWord(allMoves[i]);
    	}
            cout << "\n";
        	setColor(9,0); cout << "\n?) "; setColor(15,0); cout << "Como Jogar?";
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
        if (isAttacker) {
            setColor(4,0);
            cout << "\nAtaque (Tu): "; setColor(15,0);
        } else {
            setColor(11,0);
            cout << "\nDefesa (Tu): "; setColor(15,0);
        }
        
        char c = _getch();
        c = toupper(c);
        cout << c << "\n";
        
        if (c == '?') {
            showShadowBoxInstructions(round, playerIsAttacker);
            continue; // re-prompt
        }
        
        if (isValidAndAvailable(c))
            return c;
        
        // Mensagem temporária de erro
        setColor(4,0);
        cout << "Ataque inválido.";
        setColor(15,0);
        Sleep(500);

        // Apagar a mensagem e voltar à linha anterior
        cout << "\r" << string(80, ' ') << "\r"; // limpa a linha
        cout << "\033[F";                        // sobe uma linha
        cout << "\033[F";
        cout << "\r" << string(80, ' ') << "\r"; // limpa essa também
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
        // Imprime a ronda com a cor correspondente
        if (round == 1)
            setColor(2,0); // verde
        else if (round == 2)
            setColor(6,0); // amarelo
        else if (round == 3)
            setColor(4,0); // vermelho
        cout << "========================= Ronda " << round << " =========================\n";
        setColor(15,0);
        
        char attackerMove, defenderMove;
        
        if (playerIsAttacker) {
        cout << "";
			setColor(9,0);
            cout << "Ataques disponíveis: ";
            for (int i = 0; i < 4; i++) {
                if (isAvailable[i])
             setColor(3,0); cout << "\n- "; setColor(15,0); cout << moveToWord(allMoves[i]);
            }
            cout << "\n";
        	setColor(9,0); cout << "\n?) "; setColor(15,0); cout << "Como Jogar?";
            cout << "\n";
            attackerMove = getMoveFromUser(true, round, playerIsAttacker);

            
            defenderMove = getRandomAvailableMoveForComputer();
            setColor(11,0); cout << "Defesa (Computador): "; setColor(15,0); cout << moveToWord(defenderMove) << "\n";
        } else {
        cout << "";
            setColor(9,0);
            cout << "Ataques disponíveis: ";
            for (int i = 0; i < 4; i++) {
                if (isAvailable[i])
            setColor(3,0); cout << "\n- "; setColor(15,0); cout << moveToWord(allMoves[i]);
            }
            cout << "\n";
        	setColor(9,0); cout << "\n?) "; setColor(15,0); cout << "Como Jogar?";
            cout << "\n";
            // Primeiro, o jogador defende
            defenderMove = getMoveFromUser(false, round, playerIsAttacker);
            // Depois, o computador escolhe o movimento de ataque
            attackerMove = getRandomAvailableMoveForComputer();

            setColor(4,0); cout << "Ataque (Computador): "; setColor(15,0); cout << moveToWord(attackerMove) << "\n";
        }
        
        if (attackerMove == defenderMove) {
            setColor(3,0);
            cout << "\n===========================================================\n";
            setColor(15,0);
			cout << "          Ataque acertado: Os dois escolheram: " << moveToWord(attackerMove) << "\n";
			setColor(3,0);
            cout << "===========================================================\n\n"; setColor(15,0);
            removeMove(attackerMove);
            if (round == 3) {
                if (playerIsAttacker)
                    cout << "";
                else
                    cout << "";
                return playerIsAttacker;
            } else {
                round++;
                if (!anyMovesLeft()) {
                    setColor(6,0); cout << "Erro (Sem mais ataques?): Reinicia o jogo totalmente.\n";
                    return false;
                }
            }
        } else {
            setColor(5,0); cout << "Ataque Esquivado! \n\n"; setColor(15,0);
            playerIsAttacker = !playerIsAttacker;
            round = 1;
            restoreAllMoves();
            Sleep(500);
            Cls();
        }
    }
}

//--------------------------------------------------------------------
// Função principal: ciclo de jogo (RPS + Shadow Boxing)
int main() {
    // Configurar locale para suportar acentos
    setlocale(LC_ALL, "");
    
    srand(static_cast<unsigned int>(time(0)));
    
while (true) {
    bool playerWon = playThreeRoundGame();
	
    cout << "\nResultado Final: \n";
    if (playerWon) {
        setColor(2,0);
        cout << "Ganhaste o shadow-box, bom jogo!\n";
        setColor(8,0);
        cout << "A recomeçar jogo...";
        Sleep(8000);
        setColor(15, 0);
    } else {
        setColor(4,0);
        cout << "O computador ganhou, bom jogo.\n";
        setColor(8,0);
        cout << "A recomeçar jogo...";
        Sleep(8000);
        setColor(15, 0);
    	}
	}	
}
