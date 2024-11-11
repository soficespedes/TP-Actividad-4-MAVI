#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

int main() {
    //creamos la ventana inicial
    RenderWindow App(VideoMode(500, 500), "Redimensión de Ventana");

    //límite de tamaño para la ventana
    const int minWidth = 100;
    const int minHeight = 100;
    const int maxWidth = 1000;
    const int maxHeight = 1000;

    bool resizing = false; //indica si se está en el proceso de redimensionar la ventana
    Vector2i initialMousePos; //guarda la posición inicial del mouse cuando se comienza a redimensionar.

    while (App.isOpen()) {
        Event event;
        //procesamos los eventos
        while (App.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                App.close();
                break;
                //evento para el mouse (presionando boton izq)
            case Event::MouseButtonPressed:
                if (event.mouseButton.button == Mouse::Left) {
                    initialMousePos = Mouse::getPosition(App);
                    resizing = true;
                }
                break;
                //evento para el mouse (dejamos de presionar)
            case Event::MouseButtonReleased:
                if (event.mouseButton.button == Mouse::Left) {
                    resizing = false;
                }
                break;
                //evento para el mouse (movemos)
            case Event::MouseMoved:
                if (resizing) {
                    //obtenermos la posición actual del mouse
                    Vector2i currentMousePos = Mouse::getPosition(App);

                    //calcularmos el cambio en el tamaño de la ventana
                    int deltaX = currentMousePos.x - initialMousePos.x;
                    int deltaY = currentMousePos.y - initialMousePos.y;

                    //obtenemos el tamaño actual de la ventana
                   Vector2u currentSize = App.getSize();

                    //calculamos el nuevo tamaño de la ventana
                    int newWidth = currentSize.x + deltaX;
                    int newHeight = currentSize.y + deltaY;

                    //nos aseguramos de que el nuevo tamaño esté dentro de los límites
                    if (newWidth < minWidth) newWidth = minWidth;
                    if (newWidth > maxWidth) newWidth = maxWidth;
                    if (newHeight < minHeight) newHeight = minHeight;
                    if (newHeight > maxHeight) newHeight = maxHeight;

                    //verificamos si hemos llegado a los límites
                    if (newWidth == minWidth || newWidth == maxWidth || newHeight == minHeight || newHeight == maxHeight) {
                        //detenemos el redimensionamiento si hemos llegado al límite
                        resizing = false;
                    }

                    //redimensionamos la ventana solo si el tamaño es válido
                    App.setSize(Vector2u(newWidth, newHeight));

                    //actualizamos la posición inicial del mouse para el siguiente movimiento
                    initialMousePos = currentMousePos;
                }
                break;
            }
        }

        //limpiamos la ventana
        App.clear();

        //mostramos la ventana
        App.display();
    }

    return 0;
}
