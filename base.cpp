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

float posx = 10.33; // posicao do PacMan
float posy = 3;

int main() {
    // cria a janela
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Minha janela");

    // cria um círculo de raio 50
    sf::CircleShape circ(50.f);
    // define a posição absoluta do círculo
    circ.setPosition({10.f, 50.f});
    // define a cor do círculo (verde)
    circ.setFillColor(sf::Color(100, 250, 50));

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
                      posx -= 0.2;   // left key: move o PacMan para esquerda
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                      posx += 0.2;   // right key: move o PacMan para direita
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                      posy -= 0.2;   // up key: move o PacMan para cima
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                      posy += 0.2;   // down key: move o PacMan para baixo
            }
        }

        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);

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
        sprite.setScale({0.7083, 0.7083});
        window.draw(sprite);

        //ruan boiola
        // termina e desenha o frame corrente
        window.display();
    }

    return 0;
}
