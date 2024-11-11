#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cstdlib> 
#include <ctime> 

using namespace sf;
using namespace std;


class Enemigo {
public:
    //atributos para el enemigo
    Sprite sprite;
    FloatRect bounds;

    //constructor que recibe la textura para el sprite
    Enemigo(const Texture& texture) {
        //escalamos el sprite a 128x128
        sprite.setTexture(texture);
        sprite.setScale(128.0f / texture.getSize().x, 128.0f / texture.getSize().y);
        //generamos una posición aleatoria para el enemigo dentro de la ventana
        sprite.setPosition(rand() % 800 + 50, rand() % 600 + 50); //dentro de un rango de 800x600 píxeles

        bounds = sprite.getGlobalBounds();
    }

    //método para dibujar al enemigo
    void draw(RenderWindow& App) {
        App.draw(sprite);
    }

    //método para verificar si el clic está sobre el enemigo
    bool isClicked(int x, int y) {
        return bounds.contains(x, y);
    }
};

class Crosshair {
public:
    //atributos para la mira
    Sprite sprite;
    FloatRect bounds;

    //constructor que recibe la textura para el crosshair
    Crosshair(const Texture& texture) {
        sprite.setTexture(texture);
        sprite.setScale(32.0f / texture.getSize().x, 32.0f / texture.getSize().y);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); //centrado en el mouse
    }

    //método para mover el crosshair según la posición del ratón
    void updatePosition(int x, int y) {
        sprite.setPosition(x, y);
    }

    //método para dibujar el crosshair
    void draw(RenderWindow& App) {
        App.draw(sprite);
    }

    //método para obtener los límites del crosshair
    FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));  //inicializamos la semilla para números aleatorios

    //creamos la ventana del juego
    RenderWindow App(VideoMode(800, 600), "Crosshair Shooter");

    //cargamos las texturas
    Texture enemigoTexture, crosshairTexture;
    enemigoTexture.loadFromFile("../../AssetsU4/et.png");
    crosshairTexture.loadFromFile("../../AssetsU4/crosshair.png");

    //crear las clases Crosshair y Enemigo
    Crosshair crosshair(crosshairTexture);
    vector<Enemigo> enemies;

    //lógica del juego
    int enemiesDefeated = 0;

    //timer para generar enemigos cada cierto intervalo
    Clock enemySpawnClock;
    const float spawnInterval = 1.0f;  //intervalo en segundos entre generación de enemigos

    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                App.close();
                break;
            }

        //obtenemos la posición del mouse
        int mouseX = Mouse::getPosition(App).x;
        int mouseY = Mouse::getPosition(App).y;

        //actualizamos la posición del crosshair
        crosshair.updatePosition(mouseX, mouseY);

        //verificamos si el jugador hace clic en alguno de los enemigos
        if (Mouse::isButtonPressed(Mouse::Left)) {
            for (auto it = enemies.begin(); it != enemies.end(); ) {
                if (it->isClicked(mouseX, mouseY)) {
                    //si el clic está sobre el enemigo, eliminamos el enemigo
                    it = enemies.erase(it);
                    enemiesDefeated++;
                    break;  //detenemos la iteración ya que solo puede hacer clic en un enemigo
                }
                else {
                    ++it;
                }
            }
        }

        //si se derrotaron 5 enemigos, el juego termina
        if (enemiesDefeated == 5) {
           
            App.close();
        }

        //fenerar nuevos enemigos cada vez que eliminamos 1 cada cierto intervalo de segundos
        if (enemySpawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
            enemies.push_back(Enemigo(enemigoTexture));  //creamos un nuevo enemigo
            enemySpawnClock.restart();  //reiniciamos el cronómetro para el siguiente enemigo
        }

        //dibujamos todo
        App.clear();
        for (auto& enemy : enemies) {
            enemy.draw(App);
        }
        crosshair.draw(App);
        App.display();
    }

    return 0;
}
