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

int posx = 13; // posicao do PacMan
int posy = 17;
float posxf = 13.0f; // Nova variável
float posyf = 17.0f; // Nova variável
int score=0;
bool isLeft = false;
bool isRight = false;
bool isUp = false;
bool isDown = false;

int main() {
    // cria a janela
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Minha janela", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    // cria um quadrado de tamanho 50 (a parede)
    sf::RectangleShape quad({34.f, 34.f});
    sf::CircleShape bolinha({8.f});
    bolinha.setFillColor(sf::Color(255, 255, 255));
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

    sprite.setOrigin({texture.getSize().x / 2.0f, texture.getSize().y / 2.0f});
    sprite.setScale({34.f/texture.getSize().x, 34.f/texture.getSize().y});
    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
    {
      std::cout << "Erro lendo fonte arial\n";
      return 0;
    }
    sf::Text text(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition({0, 0});
    // executa o programa enquanto a janela está aberta
    sf::Clock relogioMovimento;
    while (window.isOpen()) {
        // verifica todos os eventos que foram acionados na janela desde a última iteração do loop
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                  if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                      window.close();
                      
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Left){
                      sprite.setRotation(sf::degrees(180));
                      isLeft = true;
                      isRight = false; 
                      isUp = false;
                      isDown = false;
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Right){
                      sprite.setRotation(sf::degrees(0));
                      isLeft = false;
                      isRight = true;
                      isUp = false;
                      isDown = false;
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Up){
                      sprite.setRotation(sf::degrees(270));
                      isLeft = false;
                      isRight = false;
                      isUp = true;
                      isDown = false;
                  }     
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Down){
                      sprite.setRotation(sf::degrees(90));
                      isLeft = false;
                      isRight = false;
                      isUp = false;
                      isDown = true;
                  }            
            }
        }
         posxf += (posx - posxf ) * 0.2f;
         posyf += (posy - posyf) * 0.2f;

        if (relogioMovimento.getElapsedTime().asSeconds() > 0.15f) {
            
            if (isLeft && mapa[posy][posx - 1] != '1') {
                posx--;
                
            }
            else if (isRight && mapa[posy][posx + 1] != '1') {
                posx++;
               
            }
            else if (isUp && mapa[posy - 1][posx] != '1') {
                posy--;
                
            }
            else if (isDown && mapa[posy + 1][posx] != '1') {
                posy++;
                
            }
            if(mapa[posy][posx]=='0'){
                mapa[posy][posx]='2';
                score+=10;
            }
            if (posx >= 27) {
            posx = 0;
            posxf = 0; // Teleporta o visual junto
        }
            if (posx <= 0) {
            posx = 27;
            posxf = 27; // Teleporta o visual junto
        }
        
            // Após mover, zera o cronômetro para começar a contar até 0.15s de novo
            relogioMovimento.restart(); 
        }


        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);

        // desenhar tudo aqui...

        // desenha paredes
        for(int i=0;i<31;i++)
            for(int j=0;j<29;j++){
                if (mapa[i][j]=='1') {
                    quad.setPosition({484.f + (j*34.f), 13.f + (i*34.f)});
                    window.draw(quad);
                }
                if(mapa[i][j]=='0'){
                    bolinha.setPosition({492.f + (j*34.f), 22.f + (i*34.f)});
                    window.draw(bolinha);
                }
            }

        // desenha PacMan
        sprite.setPosition({484.f + (posxf * 34.f) + 17.f, 13.f + (posyf * 34.f) + 17.f});
        window.draw(sprite);
        // desenha o Score
        text.setString("SCORE: " + std::to_string(score));
        window.draw(text);

        // termina e desenha o frame corrente
        window.display();
    }

    return 0;
}
