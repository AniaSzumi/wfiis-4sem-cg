// Calosc mozna dowolnie edytowac wedle uznania. 


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
// #include "/usr/local/Cellar/sfml/2.5.1_1/include/SFML/Window.hpp"
// #include "/usr/local/Cellar/sfml/2.5.1_1/include/SFML/Graphics.hpp"
#include "font.h"
#define abs(X) ((X)>0? (X):-(X))

class Menu : public sf::Drawable
{
 private:
  sf::Font font;
  sf::Text *text;
  sf::RectangleShape *rectangle;
  
  sf::Uint8 *colors_pixels;
  sf::Texture *colors_texture;
  sf::Sprite *colors_sprite;
  const unsigned int colors_size_x = 765;
  const unsigned int colors_size_y = 60;
  inline void draw_to_color_pixels(unsigned int x, unsigned int y,unsigned char r, unsigned char g, unsigned char b)
  {
   colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
   colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
   colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
   colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
  }

 public:
  friend int Main();
  Menu()
  {
   font.loadFromMemory(font_data, font_data_size);
   text = new sf::Text;
   text->setFont(font);
   text->setCharacterSize(12);
   text->setFillColor(sf::Color::White);

   rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
   rectangle->setFillColor(sf::Color::Transparent);
   rectangle->setOutlineColor(sf::Color::White);
   rectangle->setOutlineThickness(1.0f);
   rectangle->setPosition(2, 62);

   unsigned int x, y;
   colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
   for (x = 0; x<255; x++)
    for (y = 0; y < 30; y++)
     {
      draw_to_color_pixels(x, y, x, 255, 0);
      draw_to_color_pixels(x+255, y, 255, 255-x, 0);
      draw_to_color_pixels(x + 510, y, 255, 0, x);
      draw_to_color_pixels(254 - x, y+30, 0, 255, 255-x);
      draw_to_color_pixels(509 - x, y + 30, 0, x, 255 );
      draw_to_color_pixels(764 - x, y + 30, 255-x, 0, 255);
     }

   colors_texture = new sf::Texture();
   colors_texture->create(colors_size_x, colors_size_y);
   colors_texture->update(colors_pixels);

   colors_sprite = new sf::Sprite();
   colors_sprite->setTexture(*colors_texture);
   colors_sprite->setPosition(1, 1);
  }

  void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const
  {
   text->setPosition(x, y); 
   text->setString(str); 
   target.draw(*text);
  }

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
   outtextxy(target,5, 600, L"f - wybór koloru rysowania");
   outtextxy(target, 5, 615, L"b - wybór koloru wypełniania");
   outtextxy(target, 5, 630, L"l - rysowanie linii");

   outtextxy(target, 200, 600, L"r - rysowanie prostokąta");
   outtextxy(target, 200, 615, L"a - rysowanie wypełnionego prostokąta");
   outtextxy(target, 200, 630, L"c - rysowanie okręgu");

   outtextxy(target, 470, 600, L"w - zapis do pliku");
   outtextxy(target, 470, 615, L"o - odczyt z pliku");
   outtextxy(target, 470, 630, L"esc - wyjście");

   outtextxy(target, 650, 615, L"Aktualne:");

   target.draw(*rectangle);
   target.draw(*colors_sprite);
  }

  void setColor(sf::Color* c, int x, int y){
      *c = sf::Color(colors_pixels[4 * (y * colors_size_x + x) + 0],
                            colors_pixels[4 * (y * colors_size_x + x) + 1],
                            colors_pixels[4 * (y * colors_size_x + x) + 2],
                            colors_pixels[4 * (y * colors_size_x + x) + 3]);
  }
};

void setRec(sf::RectangleShape *rec, sf::Vector2f size, sf::Vector2f pos, sf::Color c, sf::Color outlinec, double lineth){
 rec->setSize(size);
 rec->setPosition(pos);
 rec->setFillColor(c);
 rec->setOutlineColor(outlinec);
 rec->setOutlineThickness(lineth);
}

int main(){
sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01",sf::Style::Titlebar | sf::Style::Close);
sf::Event event;
Menu menu;
sf::RectangleShape color_rec1;
sf::RectangleShape color_rec2;
sf::Color c1 = sf::Color::Green;
sf::Color c2 = sf::Color::Red;
setRec(&color_rec1, sf::Vector2f(30,30), sf::Vector2f(768,1), c1, sf::Color::Black, 1.0f);
setRec(&color_rec2, sf::Vector2f(30,30), sf::Vector2f(768,31), c2, sf::Color::Black, 1.0f);

sf::Text mode;
sf::Font font;
font.loadFromMemory(font_data, font_data_size);
mode.setFont(font);
mode.setCharacterSize(12);
mode.setFillColor(sf::Color::White);
mode.setPosition(720,615);

sf::Vector2f poczatek;
sf::Vector2f koniec;
int rysuj = 0;


sf::RenderTexture bg;
bg.create(750,530);
sf::Sprite bg_sp(bg.getTexture());
bg_sp.setPosition(2,65);

sf::VertexArray line(sf::LineStrip, 2);
sf::RectangleShape rectangle;
rectangle.setFillColor(sf::Color::Transparent);
rectangle.setOutlineThickness(2.0f);
sf::RectangleShape rectangle_fill;
rectangle_fill.setOutlineThickness(2.0f);
sf::CircleShape circle;
circle.setFillColor(sf::Color::Transparent);
circle.setOutlineThickness(2.0f);
sf::Vector2f p;

window.setFramerateLimit(60);


while (window.isOpen()){
    window.clear(sf::Color::Black);
   
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed) window.close();
        //Tu trzeba obsluzyc zdarzenia zwiazane z myszka oraz klawiatura. 
        if (event.type == sf::Event::KeyPressed){
            switch(event.key.code){
                case sf::Keyboard::F:
                    mode.setString('f');
                    break;
                case sf::Keyboard::B:
                    mode.setString('b');
                    break;
                case sf::Keyboard::L:
                    mode.setString('l');
                    break;
                case sf::Keyboard::R:
                    mode.setString('r');
                    break;
                case sf::Keyboard::A:
                    mode.setString('a');
                    break;
                case sf::Keyboard::C:
                    mode.setString('c');
                    break;
                case sf::Keyboard::W:
                    mode.setString('w');
                    break;
                case sf::Keyboard::O:
                    mode.setString('o');
                    break;
                default:
                    break;
                
            }
        }

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            if(mode.getString()=='f'){
                menu.setColor(&c1, event.mouseButton.x, event.mouseButton.y);
                color_rec1.setFillColor(c1);
            }
            if(mode.getString()=='b'){
                menu.setColor(&c2, event.mouseButton.x, event.mouseButton.y);
                color_rec2.setFillColor(c2);
            }
            if(mode.getString()=='l'){
                rysuj = 1;
                poczatek = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                line[0].position = poczatek;
                line[0].color = c1;
            }
            if(mode.getString()=='r'){
                rysuj = 1;
                poczatek = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                rectangle.setPosition(poczatek);
                rectangle.setOutlineColor(c1);
            }
            if(mode.getString()=='a'){
                rysuj = 1;
                poczatek = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                rectangle_fill.setPosition(poczatek);
                rectangle_fill.setOutlineColor(c1);
                rectangle_fill.setFillColor(c2);
            }
            if(mode.getString()=='c'){
                rysuj = 1;
                poczatek = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                circle.setPosition(poczatek);
                circle.setOutlineColor(c1);
            }
            
        }
        if(rysuj){
            if(event.type == sf::Event::MouseMoved){
                koniec = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                p = (koniec-poczatek);
            }
            if(mode.getString()=='l'){
                line[1].position = koniec;
                line[1].color = c2;
                window.draw(line);
            }
            if(mode.getString()=='r'){
                rectangle.setSize(p);
                window.draw(rectangle);
            }
            if(mode.getString()=='a'){
                rectangle_fill.setSize(p);
                window.draw(rectangle_fill);
            }
            if(mode.getString()=='c'){
                circle.setRadius(sqrt(p.x*p.x+p.y*p.y));
                window.draw(circle);
            }
        }
        if(event.type == sf::Event::MouseButtonReleased){
            rysuj = 0;
            if(mode.getString()=='l'){
                bg.draw(line);
            }
            if(mode.getString()=='r'){
                bg.draw(rectangle);
            }
            if(mode.getString()=='a'){
                bg.draw(rectangle_fill);
            }
            if(mode.getString()=='c'){
                bg.draw(circle);
            }

        }

    }
    //Draw BEGIN
    // Pomi�dzy "Draw BEGIN" a "Draw End" trzeba "cos" dopisac :-). Na pewno znajd� si� tam te dwie linijki:

    bg.display();
    window.draw(bg_sp);
    window.draw(color_rec1);
    window.draw(color_rec2);
    window.draw(menu);
    window.draw(mode);
    window.display();

    //Draw END
}
return 0;
}