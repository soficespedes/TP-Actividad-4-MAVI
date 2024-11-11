#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

//variables
Texture texture_cuad, texture_cir;
Sprite sprite_cuad, sprite_cir;
float escalaX;
float escalaY;
float height_cuad;
float width_cuad;
float height_cir;
float width_cir;
Vector2u windowSize;

//entrada de la aplicación
int main() {
    //cargamos texturas
    texture_cuad.loadFromFile("../../AssetsU4/cuad_yellow.png");
    texture_cir.loadFromFile("../../AssetsU4/rcircleg.png");
    //colocamos las texturas al sprite
    sprite_cuad.setTexture(texture_cuad);
    sprite_cir.setTexture(texture_cir);

    //escalamos el sprite del cuadrado según el sprite del circulo
    width_cuad = (float)texture_cuad.getSize().x;
    height_cuad = (float)texture_cuad.getSize().y;
    width_cir = (float)texture_cir.getSize().x;
    height_cir = (float)texture_cir.getSize().y;
   
    escalaX = width_cir / width_cuad;
    escalaY = height_cir / height_cuad;
    sprite_cuad.setScale(escalaX, escalaY);
   
    //creamos la ventana
    RenderWindow App(VideoMode(800, 600, 32), "Ventana de Aplicación");
    float velocidad = 1.0f; //nos permitirá colocarle la velocidad de movimiento a los sprites
    bool mostrarCirculo = false; //nos permitirá comenzar el programa sin que aparezca el circulo
    sprite_cuad.setOrigin(texture_cuad.getSize().x / 2, texture_cuad.getSize().y / 2); //establecemos el origen en el centro del cuadrado
    sprite_cuad.setPosition(App.getSize().x / 2, App.getSize().y / 2); //posicionamos el sprite en el centro de la ventana
    sprite_cir.setOrigin(texture_cir.getSize().x / 2, texture_cir.getSize().y / 2); //establecemos el origen en el centro del circulo
    sprite_cir.setPosition(App.getSize().x / 2, App.getSize().y / 2); //posicionamos el sprite en el centro de la ventana

    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            //procesamos los eventos
            switch (event.type) { //si cerramos la ventana
            case Event::Closed:
                App.close();
                break;
            case Event::Resized:
                windowSize = App.getSize();  //actualizamos el tamaño de la ventana para limitar el movimiento de los sprites
                break;
            }
            //creamos un evento para la tecla [ESPACIO]
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                mostrarCirculo = !mostrarCirculo;  //alterna el estado
                if (mostrarCirculo) {
                    //si se muestra el círculo, le damos la misma posición que el cuadrado
                    sprite_cir.setPosition(sprite_cuad.getPosition());
                }
                else {
                    //si se muestra el cuadrado, le damos la misma posicion que tenia el circulo
                } sprite_cuad.setPosition(sprite_cir.getPosition());
            }
        }
        if (mostrarCirculo) {  //solo se mueve el círculo si está visible
            //arriba 
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if (sprite_cir.getPosition().y > 64) { //verificamos si el sprite está dentro de la ventana en Y
                    sprite_cir.move(0, -velocidad);
                }
            }
            //abajo 
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                if (sprite_cir.getPosition().y + sprite_cir.getGlobalBounds().height < App.getSize().y + 64) {  //comprobamos el borde inferior
                    sprite_cir.move(0, velocidad);
                }
            }
            //izquierda 
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (sprite_cir.getPosition().x > 64) {  //verificamos si el sprite está dentro de la ventana en X
                    sprite_cir.move(-velocidad, 0);
                }
            }
            //derecha 
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (sprite_cir.getPosition().x + sprite_cir.getGlobalBounds().width < App.getSize().x + 64) {  //comprobamos el borde derecho
                    sprite_cir.move(velocidad, 0);
                }
            }
        }
        else {  //si no está visible, movemos el cuadrado (la misma lógica)
            //arriba 
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if (sprite_cuad.getPosition().y > 64) { 
                    sprite_cuad.move(0, -velocidad);
                }
            }
            //abajo 
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                if (sprite_cuad.getPosition().y + sprite_cuad.getGlobalBounds().height < App.getSize().y + 64) {  
                    sprite_cuad.move(0, velocidad);
                }
            }
            //izquierda 
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (sprite_cuad.getPosition().x > 64) {  
                    sprite_cuad.move(-velocidad, 0);
                }
            }
            //derecha 
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (sprite_cuad.getPosition().x + sprite_cuad.getGlobalBounds().width < App.getSize().x + 64) {  
                    sprite_cuad.move(velocidad, 0);
                }
            }
        }
        
        //limpiamos la ventana 
        App.clear();
        //dibujamos la escena
        if (mostrarCirculo) {
            App.draw(sprite_cir);  //si mostrarCirculo es true, dibuja el sprite del círculo
        }
        else {
            App.draw(sprite_cuad);  //sino, dibuja el sprite del cuadrado
        }

        //mostramos la ventana 
        App.display();
    }
    return 0;
}