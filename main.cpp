#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
using namespace std;
void generare_mapa( int w, int grid[][12], int sgrid[][12]){

     for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
        {
        sgrid[i][j]=10;
        if (rand()%5==0)
            grid[i][j]=9;
        else grid[i][j]=0;
        }

    for (int i=1;i<=10;i++)
        for (int j=1;j<=10;j++)
        {
            int n=0;
            if (grid[i][j]==9) continue;
            if (grid[i+1][j]==9) n++;
            if (grid[i][j+1]==9) n++;
            if (grid[i-1][j]==9) n++;
            if (grid[i][j-1]==9) n++;
            if (grid[i+1][j+1]==9) n++;
            if (grid[i-1][j-1]==9) n++;
            if (grid[i-1][j+1]==9) n++;
            if (grid[i+1][j-1]==9) n++;
            grid[i][j]=n;
      }
}

void gameover(Time elapsed){
    string scor;
    scor="Scorul dumneavoastra este: \t "+ to_string(elapsed.asSeconds())+"\n Pentru a reincepe, apsati pe bombe";
    RenderWindow over(VideoMode(400, 200), "Game Over!");
    Text text;
    Font font;
    if (!font.loadFromFile("font/font.ttf"))
    {
        cout<<"error"<<endl;
        system("pause");
    }
    text.setFont(font);
    text.setString(scor);
    text.setCharacterSize(20);
    text.setFillColor(Color::Red);
    over.draw(text);
    over.display();
    while (over.isOpen()){
        Event e2;
        while (over.pollEvent(e2))
        {
            if (e2.type == Event::Closed)   over.close();
        }
    }
}

int main()
{
    bool finish=false;
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");
    Time elapsed;

    int w=32;
    int grid[12][12];
    int sgrid[12][12]; //for showing

    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    generare_mapa(w, grid, sgrid);
    Clock clock;

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x/w;
        int y = pos.y/w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
              {
                app.close();
              }
            if (e.type == Event::MouseButtonPressed)
              if (e.key.code == Mouse::Left) {
                    sgrid[x][y]=grid[x][y];
                    if (grid[x][y]==9)
                    {
                        if (finish){
                            finish=false;
                            generare_mapa(w,grid,sgrid);
                        }
                        else {
                            elapsed=clock.getElapsedTime();
                            gameover(elapsed);
                            clock.restart();
                            finish=true;
                        }
                    }
               }
              else if (e.key.code == Mouse::Right) sgrid[x][y]=11;
        }

        app.clear(Color::White);

        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
           if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];
           s.setTextureRect(IntRect(sgrid[i][j]*w,0,w,w));
           s.setPosition(i*w, j*w);
           app.draw(s);
          }

        app.display();
    }

    return 0;
}
