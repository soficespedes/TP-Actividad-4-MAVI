#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;
//para esta consigna, debido a que no debe hacer un límite de circulos para dibujar en la ventana, conviene utilizar
//vectores, estos nos ayudarán a gestionar mejor la memoria y nos permite agregar el numero indefinido de circulos que nos pide la consigna
Texture texture1, texture2;
vector<Sprite> sprites1; //vector para el sprite1 (círculo rojo)
vector<Sprite> sprites2; //vector para el sprite2 (círculo azul)
vector<Vector2f> positions1; //vector para las posiciones del sprite1
vector<Vector2f> positions2; //vector para las posiciones del sprite2

int main() {
    //cargamos las texturas
    texture1.loadFromFile("..\\..\\AssetsU4\\rcircle.png");
    texture2.loadFromFile("..\\..\\AssetsU4\\rcircleb.png");

    //creamos la ventana
    RenderWindow App(VideoMode(800, 600, 32), "Ventana de aplicación");

    //bucle principal
    while (App.isOpen()) {
        Event event;
        while (App.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                App.close();
                break;
            //evento que nos permitirá utilizar los botones del mouse)
            case Event::MouseButtonPressed:
                if (event.mouseButton.button == Mouse::Left) {
                    //agregamos el sprite (circulo rojo) cuando pulsamos el clic izquierdo
                    positions1.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    sprites1.push_back(Sprite(texture1));
                    sprites1.back().setPosition(positions1.back());
                }
                else if (event.mouseButton.button == Mouse::Right) {
                    //agregamos el sprite (circulo azul) cuando pulsamos del clic derecho
                    positions2.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    sprites2.push_back(Sprite(texture2));
                    sprites2.back().setPosition(positions2.back());
                }
                break;
            }
        }
        //momento de mostrarlo en pantalla
        //limpiamos la ventana
        App.clear();

        //dibujamos todos los sprites de clic izquierdo (círculos rojos) con un for,
        //este nos permite recorrer el arreglo dinamico del vector correspondiente al circulo rojo
        for (size_t i = 0; i < sprites1.size(); ++i) {
            App.draw(sprites1[i]);
        }
        //hacemos lo mismo con todos los sprites de clic derecho (círculos azules)
        for (size_t i = 0; i < sprites2.size(); ++i) {
            App.draw(sprites2[i]);
        }

        //mostramos la ventana
        App.display();
    }

    return 0;
}
