#include<iostream>
#include<fstream>
#include"GamesEngineeringBase.h"
using namespace std;


void drawCircle(GamesEngineeringBase::Window& canvas, int cx, int cy, int r) {
	int r2 = r * r;
	for (int x = -r; x < r + 1; x++) {
		int y = sqrtf(r2 - (x * x));

		if (cx + x > 0 && cx + x < canvas.getWidth()) {
			if (cy + y > 0 && cy + y < canvas.getHeight())
				canvas.draw(cx + x, cy + y, 255, 0, 0);
			if (cy - y > 0 && cy - y < canvas.getHeight())
				canvas.draw(cx + x, cy - y, 255, 0, 0);
		}
		//cout << cx + x << '\t' << cy + y << endl;
	}
}


class CObject
{
	// 
protected:
	int x, y;
	GamesEngineeringBase::Image sprite;
public:
	CObject(int _x, int _y, string filename) {
		sprite.load(filename);
		x = _x - sprite.width / 2;
		y = _y;
	};

	void Draw(GamesEngineeringBase::Window& canvas) {
		// Draw objects to screen in its original material
		for (unsigned int i = 0; i < sprite.width; i++) {
			if (x + i > 0 && x + i < canvas.getWidth()) {
				for (unsigned int j = 0; j < sprite.height; j++) {
					if (y + j > 0 && y + j < canvas.getHeight()) {
						if (sprite.alphaAt(i, j) > 200)
							canvas.draw(x + i, y + j, sprite.at(i, j));
					}
				}
			}
		}
		drawCircle(canvas, x + sprite.width / 2, y + sprite.height / 2, sprite.width / 3);
	}

	void virtual Update(int _x, int _y) {
		x += _x;
		y += _y;
	}

	void virtual Update(GamesEngineeringBase::Window& canvas, int _x, int _y) {
		x += _x;
		y += _y;

		if (x < 0) x = 0;
		if (y < 0) y = 0;
		//if (x + sprite.width > canvas.getWidth()) x = canvas.getWidth();
		//if (y + sprite.height > canvas.getHeight()) y = canvas.getHeight();

		if (x + sprite.width > canvas.getWidth()) x = canvas.getWidth() - sprite.width;
		if (y + sprite.height > canvas.getHeight()) y = canvas.getHeight() - sprite.height;

	}

	bool CircleCollidor(CObject& other) {
		// Check collision between this and other objects
		int dx = x - other.x;
		int dy = y - other.y;

		float radius = static_cast<float>(sprite.width / 2.5f);
		// Euclidean distance of two objects
		float d = sqrtf(dx * dx + dy * dy);
		if (d < 2.0f * radius) return true;
		else return false;
	}

	int GetX() {
		return x;
	}

	int GetY() {
		return y;
	}

	int GetHeight() {
		return sprite.height;
	}

	int GetWidth() {
		return sprite.width;
	}
};




// Tiles:
class tile {
	GamesEngineeringBase::Image sprite;
public:
	tile() {}
	void Load(string filename) {
		sprite.load(filename);
	}
	void Draw(GamesEngineeringBase::Window& canvas, int x, int y) {
		// Draw objects to screen in its original material
		for (unsigned int i = 0; i < sprite.width; i++) {
			if (x + i > 0 && x + i < canvas.getWidth()) {
				for (unsigned int j = 0; j < sprite.height; j++) {
					if (y + j > 0 && y + j < canvas.getHeight()) {
						canvas.draw(x+i, y + j, sprite.atUnchecked(i, j));
					}
				}
			}
		}
	}

	int GetHeight() {
		return sprite.height;
	}

	int GetWidth() {
		return sprite.width;
	}

	GamesEngineeringBase::Image GetSprite() {
		return sprite;
	}
};

const unsigned int tileNum = 23;
class tileSet {
	tile tiles[tileNum];
public:
	tileSet() {}
	void Load() {
		for (unsigned i = 0; i < tileNum; i++) {
			string filename = "Resources/" + to_string(i) + ".png";
			tiles[i].Load(filename);
			cout << "Load complete" << endl;
		}
	}
	// overload [] to access individual elements from array directly
	tile& operator[](unsigned int index)
	{
		return tiles[index];
	}

};

const int maxSizeY = 200;
const int maxSizeX = 200;

class world {
	tileSet tiles;
	tileSet alphas;
	// unsigned int* map;
	unsigned int size;
	unsigned int map[maxSizeX][maxSizeY];
	unsigned int* map1;
	// int map1[32][24];
public:
	world() {
		// try use number of tile for whole screen:32*24=768 tiles
		// try AREA method
		size = maxSizeX;
		// map = new unsigned int[maxSizeX][maxSizeY];
		tiles.Load();

		for (unsigned int i = 0; i < maxSizeX; i++) {
			for (unsigned int j = 0; j < maxSizeY; j++) {
				map[i][j] = rand() % tileNum; // randomly choose a tile and put it into 2D array
				// map[i][j] = rand() % tileNum; // randomly choose a tile and put it into 2D array
				cout << map[i][j] << endl;
			}
		}
	}
	world(string filename){
		tiles.Load();
		ifstream infile(filename);
		int tilenum, i;
		string s;

		infile >> tilenum;
		cout << tilenum << endl; 
		map1 = new unsigned int[tilenum];

		for (i = 0; i < tilenum; i++) {
			infile >> map1[i];
			cout << map1[i] << endl;
		}
		infile.close();
		}

		//for (unsigned int i = 0; i < 32; i++) {
//	for (unsigned int j = 0; j < 24; j++) {
//		map1[i][j] = rand() % tileNum; // randomly choose a tile and put it into 2D array
//		// map[i][j] = rand() % tileNum; // randomly choose a tile and put it into 2D array
//		cout << map1[i][j] << endl;
//	}
//}

		//for (unsigned int i = 0; i < screenSize; i++) {
		//	map[i] = rand() % tileNum;
		//	cout << "map is" << map[i] << endl;
		//}

	~world() {
		delete[] map1;
	}//int worldX, int worldY


	void draw(GamesEngineeringBase::Window& canvas, int wx, int wy) {
		int height = tiles[0].GetHeight(); // should not be limited in specific tile, but considering every tile should be sliced to 32*32 for pixel game, so it is fine 
		int width = tiles[0].GetWidth();

		int Y = wy / height;
		int rY = wy % height;

		int X = wx / width;
		int rX = wx % width;

		int tileSize = 32;
		for (unsigned i = 0; i < canvas.getWidth() / width; i++) {
			for (unsigned j = 0; j < canvas.getHeight() / height; j++) {
				//int tileIndex = map[(j * 32 + i) % size];
				//tiles[tileIndex].Draw(canvas, posX, posY);

				tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, 32 * i, 32 * j);


			}
		}
	}

			//bool collision(GamesEngineeringBase::Window & canvas, CObject & player, unsigned worldX, unsigned worldY) {
			//	bool b1 = testline(canvas, player.GetX(), player.GetY(), player.GetWidth(),player.GetHeight(),wx, wy, h.getHeight() / 3);
			//	bool b2 = testline(canvas, player.GetX() + 19, player.GetWidth() - 5, player.GetHeight() - 5, wx,wy, (h.getHeight() / 2) - 1);
			//	return b1 & b2;
			//}

			bool collision(GamesEngineeringBase::Window& canvas, CObject& player, unsigned worldX, unsigned worldY) {
				// Use worldX and worldY in place of wx and wy
				bool b1 = testline(canvas, player.GetX(), player.GetY(), player.GetWidth(), player.GetHeight(), worldX, worldY, player.GetHeight() / 3);
				bool b2 = testline(canvas, player.GetX() + 19, player.GetY() + 10, player.GetWidth() - 5, player.GetHeight() - 5, worldX, worldY, (player.GetHeight() / 2) - 1);

				// Use logical AND (&&) for boolean logic
				return b1 && b2;
			}


private:
	bool testline(GamesEngineeringBase::Window& canvas, unsigned int playerX, unsigned int playerY, unsigned int playerWidth, unsigned playerHeight, unsigned int worldX, unsigned int worldY,unsigned int offset) {
		bool col = false;
		int Y = (worldY + offset) / 32;
		int X = (worldX + offset) / 32;

		tile& t = alphas[map[X % size][Y % size]];

		unsigned int y = t.GetHeight() - ((offset + worldY) % 32); // calculate y position within the tile
		unsigned int x = t.GetWidth() - ((offset + worldX) % 32); // calculate x position within the tile

		for (unsigned int i = playerX; i < playerX + playerWidth; i++) {
			for (unsigned int j = playerY; j < playerY + playerHeight; j++) {

				if (i > canvas.getWidth() || j > canvas.getHeight()) continue;

				if (t.GetSprite().at(i, y, 0) < 100) {
					canvas.draw(i, canvas.getHeight() - offset, 255, 0, 0); // draw line around plane
					col = true;
				}
				else {
					canvas.draw(i, canvas.getHeight() - offset, 0, 255, 0);
				}

			}
		}
		return col;
	}

		
};


int main() {
		srand(static_cast<unsigned int>(time(NULL))); // make sure number are number each time
		// construct windows
		GamesEngineeringBase::Window canvas;
		canvas.create(1024, 768, "Survivor");

		// construct objects
		CObject player(canvas.getWidth() / 2, canvas.getHeight() / 2, "Resources/L.png");

		// Enemy enemy;
		world w;
		// GamesEngineeringBase::Timer tim;
		int x=0, y = 0; // position of hero
		bool running = true; // To control game main loop

		tileSet tiles;
		tiles.Load();
		// game runniung
		while (running) {

			// variables needs to be updated each frame



			// Functions implementation
			// check input
			canvas.checkInput();
			// clear windows for next frame
			canvas.clear();


			//float dt = tim.dt();
			float dt = 0.025f;
			// int move = static_cast<int>((500.f * dt));
			// move function implementation

			if (canvas.keyPressed(VK_ESCAPE)) break;
			if (canvas.keyPressed('W')) y -= 2;
			if (canvas.keyPressed('S')) y += 2;
			if (canvas.keyPressed('A')) x -= 2;
			if (canvas.keyPressed('D')) x += 2;


			//if (canvas.keyPressed('W')) player.Update(0,2);
			//if (canvas.keyPressed('S')) player.Update(0, -2);
			//if (canvas.keyPressed('A')) player.Update(-2, 0);
			//if (canvas.keyPressed('D')) player.Update(2, 0);
			// Hero Creation
			
			// player.Update(canvas, x, y);


			// Enemy Creation
			// enemy.Update(canvas, player, dt);
			// enemy.Collision(player);
			// Weapon Creation



			// Draw canvas
			//for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++)
			//	for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++)

			//		canvas.draw(tempx, tempy, 0, 0, 255);

			w.draw(canvas,x,y);
			w.collision(canvas, player, x, y);

			// Display
			// enemy.Draw(canvas);
			player.Draw(canvas);
			//player.draw(canvas);

			// Frame display
			canvas.present();
		}
		return 0;
	}

