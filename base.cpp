#include <SFML/Graphics.hpp>
#include <iostream>

char mapa[31][29] = {    // Mapa do jogo
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

int posx = 15; // posicao do PacMan
int posy = 14;

int main() {
    // cria a janela
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Minha janela", sf::State::Fullscreen);

    // cria um quadrado de tamanho 50 (a parede)
    sf::RectangleShape quad({34.f, 34.f});
    quad.setFillColor(sf::Color(0, 150, 255, 100));
    quad.setOutlineColor(sf::Color(0, 50, 255));
    quad.setOutlineThickness(-2.f);

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
                      
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Left){
                  if (mapa[posy][posx - 1] != '1')
                      posx--;   // left key: move o PacMan para esquerda
                  }
                    
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Right){
                    if (mapa[posy][posx + 1] != '1')
                      posx++;   // right key: move o PacMan para direita
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Up){
                    if (mapa[posy - 1][posx] != '1')
                      posy--;   // up key: move o PacMan para cima
                  }     
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Down){
                    if (mapa[posy + 1][posx] != '1')
                      posy++;   // down key: move o PacMan para baixo
                  }   
                           
            }
        }

        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);

        // desenhar tudo aqui...

        // desenha paredes
        for(int i=0;i<31;i++)
            for(int j=0;j<29;j++)
                if (mapa[i][j]=='1') {
                    quad.setPosition({484.f + (j*34.f), 13.f + (i*34.f)});
                    window.draw(quad);
                }

        // desenha PacMan
        sprite.setPosition({484.f + (posx * 34.f), 13.f + (posy * 34.f)});
        sprite.setScale({34.f/texture.getSize().x, 34.f/texture.getSize().y});
        window.draw(sprite);

        // termina e desenha o frame corrente
        window.display();
    }

    return 0;
}
