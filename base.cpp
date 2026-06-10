#include <SFML/Graphics.hpp>
#include <iostream>

const int linha = 31;
const int coluna = 29;

char mapa[linha][coluna] = {
    "1111111111111111111111111111",
    "1000000000000110000000000001",
    "1011110111110110111110111101",
    "1011110111110110111110111101",
    "1011110111110110111110111101",
    "1000000000000000000000000001",
    "1011110110111111110110111101",
    "1011110110111111110110111101",
    "1000000110000110000110000001",
    "1111110111110110111110111111",
    "1111110111110110111110111111",
    "1111110110000000000110111111",
    "1111110110111001110110111111",
    "1111110110100000010110111111",
    "0000000000100000010000000000",
    "1111110110100000010110111111",
    "1111110110111111110110111111",
    "1111110110000000000110111111",
    "1111110110111111110110111111",
    "1111110110111111110110111111",
    "1000000000000110000000000001",
    "1011110111110110111110111101",
    "1011110111110110111110111101",
    "1000110000000000000000110001",
    "1110110110111111110110110111",
    "1110110110111111110110110111",
    "1000000110000110000110000001",
    "1011111111110110111111111101",
    "1011111111110110111111111101",
    "1000000000000000000000000001",
    "1111111111111111111111111111"
};

float posx = 10.365; // posicao do PacMan
float posy = 3;
int direction;

int main() {
    // cria a janela
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Minha janela", sf::State::Fullscreen);

    // cria um quadrado de tamanho 50 (a parede)
    sf::RectangleShape quad({34.f, 34.f});
    quad.setFillColor(sf::Color(0, 100, 200));

    // sprites do PacMan
    sf::Texture texture;
    if (!texture.loadFromFile("pacman.png")) {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    sf::Sprite sprite{texture};
    sf::Clock clock;
    sf::Time tempoPassado;
    sf::Time tempoDePasso = sf::seconds(0.05f);

    // executa o programa enquanto a janela está aberta
    while (window.isOpen()) {

        // verifica todos os eventos que foram acionados na janela desde a última iteração do loop
        while (const std::optional event = window.pollEvent()) {
            // evento "fechar" acionado: fecha a janela
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                  if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                      window.close();
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
                     direction=1;
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                     direction=2;   // right key: move o PacMan para direita
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                     direction=3;   // up key: move o PacMan para cima
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                     direction=4;   // down key: move o PacMan para baixo
            }
        }

        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);
        tempoPassado += clock.restart();
        if(tempoPassado>=tempoDePasso){
            if(direction==1){
                float proxX = posx - 0.1f; 
                if(mapa[static_cast<int>(posy)][static_cast<int>(proxX)]!='1' &&
                   mapa[static_cast<int>(posy+0.9f)][static_cast<int>(proxX)]!='1'){
                    posx = proxX;
                }
            }
            else if(direction==2){
                float proxX = posx + 0.1f;
                if(mapa[static_cast<int>(posy)][static_cast<int>(proxX + 0.9f)]!='1' &&
                   mapa[static_cast<int>(posy + 0.9f)][static_cast<int>(proxX + 0.9f)]!='1'){
                posx = proxX;
                }
            }
            else if(direction==3){
                float proxY = posy - 0.1f;
                if(mapa[static_cast<int>(proxY)][static_cast<int>(posx)]!='1' &&
                   mapa[static_cast<int>(proxY)][static_cast<int>(posx+0.9f)]!='1'){
                posy = proxY;
                }
            }
            else if(direction==4){
                float proxY = posy + 0.1f;
                if(mapa[static_cast<int>(proxY + 0.9f)][static_cast<int>(posx)]!='1' &&
                   mapa[static_cast<int>(proxY + 0.9f)][static_cast<int>(posx+0.9f)]!='1'){
                posy = proxY;
                }
            }
            tempoPassado = sf::Time::Zero;
        }
        

        // desenhar tudo aqui...

float primeiraColuna = 484.f; // Centraliza no eixo X
float tamanhoRetangulo = 34.f;

// desenha paredes
for(int i = 0; i < linha; i++) {
    for(int j = 0; j < coluna; j++) {
        // Ignora o caractere nulo '\0' no final de cada string
        if (mapa[i][j] == '1') {
            quad.setPosition({primeiraColuna + (j * tamanhoRetangulo), i * tamanhoRetangulo});
            window.draw(quad);
        }
    }
}

        // desenha PacMan
        sprite.setPosition({posx*50.f,posy*50.f});
        sprite.setScale({0.7, 0.7});
        window.draw(sprite);

        //ruan boiola
        // termina e desenha o frame corrente
        window.display();
    }

    return 0;
}
