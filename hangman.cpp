#include <iostream>
#include <string>
#include <vector>

// jogo da forca

void limpaTela() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");
        //std::cout << "\033[2J\033[H"; // Linux/macOS (códigos ANSI)
    #endif
}

bool foiDigitada(const std::vector<char>& tentativas,const char& tentativa){
    for (char iterator : tentativas){
            if (iterator == tentativa){
                return true;
                break;
            }
        }
        return false;
}

bool acertou(const std::string& palavra,std::string &progresso,const char& tentativa){
    bool letraEncontrada{false};
    for (size_t i=0; i < palavra.size(); i++){
        if (palavra[i] == tentativa){
            progresso[i] = tentativa;
            letraEncontrada=true;
            }
        }
    return letraEncontrada;
}

void imprimeVetor(const std::vector<char>& tentativas){
    std::cout << "Wrong letters already tried: ";
    for (char iterator : tentativas){
        std::cout << iterator << " ";
    }
}

void imprimeJogo(const int& erros){
    const std::string estagios [7] {
        "_________\n|\t|\n|\n|\n|\n|\n|\n",
        "_________\n|\t|\n|\tO\n|\n|\n|\n|\n",
        "_________\n|\t|\n|\tO\n|\t|\n|\n|\n|\n",
        "_________\n|\t|\n|\tO\n|      -|\n|\n|\n|\n",
        "_________\n|\t|\n|\tO\n|      -|-\n|\n|\n|\n",
        "_________\n|\t|\n|\tO\n|      -|-\n|      /\n|\n|\n",
        "_________\n|\t|\n|\tO\n|      -|-\n|      / \\ \n|\n|\n"
    };
    std::cout << estagios[erros];
}

void menu(){
    std::string palavra{};
    std::cout << "Insert one word/phrase: ";
    std::getline(std::cin, palavra);

    limpaTela();

    std::string progresso = palavra;
    for (char &c : progresso) {
        if (c != ' ') {
            c = '_';
        }
    }
    
    std::vector<char> tentativas;
    char tentativa;
    int erros{0};
    imprimeJogo(erros);

    while (progresso != palavra && erros < 6){
        std::cout << "\n";
        for (char c : progresso){
            std::cout << c << ' ';
        }
        std::cout << std::endl;

        std::cout << "Insert one letter:\n";
        std::cin >> tentativa;

        limpaTela();
        imprimeJogo(erros);

        if (!acertou(palavra, progresso, tentativa)){
            if (!foiDigitada(tentativas, tentativa)){
                limpaTela();
                tentativas.push_back(tentativa);
                erros++;
                imprimeJogo(erros);
                std::cout << "Incorrect letter '" << tentativa << "'\n";
            } else {
                std::cout << "Letter '" << tentativa << "' already tried!\n";
            }
        }
        imprimeVetor(tentativas);
    }
    if (progresso == palavra) {
        std::cout << "\nCongratulations! You've guessed the word: " << palavra << std::endl;
        } else {
        std::cout << "\nGamer Over! The word was: " << palavra << std::endl;
    }

    char continuar;
    std::cout << "\nDo you want to play again ? (y/n)\n";
    std::cin >> continuar;
    std::cin.ignore();
    if (continuar == 'y' || continuar == 'Y'){
        limpaTela();
        menu();
    }
}

int main (){
    std::cout << "Welcome to hangman.cpp!\n\n";
    menu();
    return 0;
}