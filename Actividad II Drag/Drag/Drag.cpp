#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

// Variables. Luego de haber concluido la U3, averigué cómo podía "limpiar" el codigo u organizarlo mejor
//para una lectura un poco más sencilla. Por eso habrán leves modificaciones en la parte de las variables.
Texture texture_point;
Sprite sprite[4];
Sprite* active_sprite = nullptr; //sirve para almacenar el sprite que se está usando como cursor en el momento
Vector2i offset; //nos permitirá calcular la distancia del mouse al sprite
bool isMoving = false; //para saber si el sprite está en movimiento

//punto de entrada a la aplicación
int main() {
    //cargamos la textura del archivo que utilizaremos
    texture_point.loadFromFile("..\\..\\AssetsU4\\rcircle.png");
    //cargamos la textura a cada sprite
    sprite[0].setTexture(texture_point);
    sprite[1].setTexture(texture_point);
    sprite[2].setTexture(texture_point);
    sprite[3].setTexture(texture_point);

    //movemos el sprite
    sprite[0].setPosition(0, 0);
    sprite[1].setPosition(0, 470);
    sprite[2].setPosition(670, 0);
    sprite[3].setPosition(670, 470);

    //creamos la ventana
    RenderWindow App(VideoMode(800, 600, 32), "Ventana de aplicación");

    //loop principal
    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                App.close();
                break;
            }
            //detectamos el clic del mouse
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    //comprobamos si se hace clic en alguno de los sprites
                    if (sprite[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        if (active_sprite == &sprite[0] && isMoving) {
                            //si el mismo sprite se ha clicado, se queda en la posición donde estaba en el momento
                            active_sprite = nullptr;
                            isMoving = false;
                        }
                        else {
                            active_sprite = &sprite[0];
                            isMoving = true;
                        }
                    } //hacemos lo mismo para cada sprite (no encontré forma de optimizarlo mejor, agradezco sugerencias)
                    else if (sprite[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        if (active_sprite == &sprite[1] && isMoving) {
                            active_sprite = nullptr;
                            isMoving = false;
                        }
                        else {
                            active_sprite = &sprite[1];
                            isMoving = true;
                        }
                    }
                    else if (sprite[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        if (active_sprite == &sprite[2] && isMoving) {
                            active_sprite = nullptr;
                            isMoving = false;
                        }
                        else {
                            active_sprite = &sprite[2];
                            isMoving = true;
                        }
                    }
                    else if (sprite[3].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        if (active_sprite == &sprite[3] && isMoving) {
                            active_sprite = nullptr;
                            isMoving = false;
                        }
                        else {
                            active_sprite = &sprite[3];
                            isMoving = true;
                        }
                    }
                    //calculamos el offset si se ha seleccionado un sprite
                    if (active_sprite) {
                        offset.x = event.mouseButton.x - active_sprite->getPosition().x;
                        offset.y = event.mouseButton.y - active_sprite->getPosition().y;
                    }
                }
            }
        }

        //y movemos el sprite activo
        if (active_sprite && isMoving) {
            Vector2i mousePos = Mouse::getPosition(App);
            active_sprite->setPosition(mousePos.x - offset.x, mousePos.y - offset.y);
        }
//ahora si, momento de mostrarlo en pantalla
        //limpiamos la ventana
        App.clear();

        //dibujamos la escena
        App.draw(sprite[0]);
        App.draw(sprite[1]);
        App.draw(sprite[2]);
        App.draw(sprite[3]);

        //mostramos la ventana
        App.display();
    }
    return 0;
}
