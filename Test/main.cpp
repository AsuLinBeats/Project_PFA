#include<iostream>
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
						canvas.draw(i, y + j, sprite.atUnchecked(i, j));
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

const int maxSizeY = 150;
const int maxSizeX = 150;

class world {
	tileSet tiles;
	unsigned int* map;
	unsigned int size;
	//unsigned int map[maxSizeX][maxSizeY];
public:
	world() {
		// try use number of tile for whole screen:32*24=768 tiles
		// try AREA method
		size = maxSizeX;
		int screenSize = 768;
		map = new unsigned int[screenSize];
		tiles.Load();
		//for (unsigned int i = 0; i < maxSizeX; i++) {
		//	for (unsigned int j = 0; j < maxSizeY; j++) {
		//		map[i][j] = rand() % tileNum; // randomly choose a tile and put it into 2D array
		//		// map[i][j] = rand() % tileNum; // randomly choose a tile and put it into 2D array
		//		cout << map[i][j] << endl;
		//	}
		//}
		for (unsigned int i = 0; i < screenSize; i++) {
			map[i] = rand() % tileNum;
			cout << "map is" << map[i] << endl;
		}

	}
	~world() {
		delete[] map;
	}//int worldX, int worldY
	void draw(GamesEngineeringBase::Window& canvas) {
		int height = tiles[0].GetHeight(); // should not be limited in specific tile, but considering every tile should be sliced to 32*32 for pixel game, so it is fine 
		int width = tiles[0].GetWidth();

		//for (unsigned int i = 0; i < 32; i++) {
		//	for (unsigned int j = 0; j < 24; j++) {
		//		tiles[map[i*j]].Draw(canvas, 0 + 32 * i, 32 * j);
		//	} 

		//}

		for (unsigned int i = 0; i < 32; i++) {
			for (unsigned int j = 0; j < 24; j++) {
				unsigned int tileIndex = map[i + j * 32];  // Calculate 1D index based on 2D position
				tiles[tileIndex].Draw(canvas, i * width, j * height);  // Adjusted to use width and height
			}
		}
	}


	// world y position
	//int Y = worldY / height;
	// world x position
	// int X = worldX / width;

	//int rHeight = worldY % height;
	//int rWidth = worldX % width;
	//tiles[map[Y % maxSize]].Draw(canvas, (canvas.getWidth() / 2) + rWidth, (canvas.getHeight() / 2) + rHeight);
	//tiles[map[(Y + 1) % maxSize]].Draw(canvas, r);
	//tiles[map[(Y + 2) % maxSize]].Draw(canvas, -height + r);
	// X: 32, Y: 24
	//int tileSize = 32;
	/* tiles[map[(X) % maxSizeX][(Y) % maxSizeY]].Draw(canvas, (canvas.getWidth() / 2) + rWidth, (canvas.getHeight() / 2) + rHeight);
	 tiles[map[(X + 1) % maxSizeX][(Y + 1) % maxSizeY]].Draw(canvas, rWidth, rHeight);
	 tiles[map[(X + 2) % maxSizeX][(Y + 2) % maxSizeY]].Draw(canvas, -height+rHeight, -width + rWidth);*/
	 //	for (unsigned i = 0; i < canvas.getWidth() / width; i++) {
	 //		for (unsigned j = 0; j < canvas.getHeight() / height; j++) {

	 //			int posX = i * tileSize;
	 //			int posY = j * tileSize + (wy % tileSize); // scrolling effect

	 //			int tileIndex = map[(j * 32 + i) % size];
	 //			tiles[tileIndex].Draw(canvas, posX, posY);

	 //			// tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, (canvas.getWidth() / 2) + rWidth, (canvas.getHeight() / 2) + rHeight);
	 //			//tiles[map[(X + 1+i) % maxSizeX][(Y + 1) % maxSizeY]].Draw(canvas, rWidth, rHeight);
	 //			//tiles[map[(X + 2+i) % maxSizeX][(Y + 2) % maxSizeY]].Draw(canvas, -height + rHeight, -width + rWidth);
	 //			//
	 //			// tiles[map[(X+i) % maxSize]].Draw(canvas, (canvas.getWidth() / 2) + rWidth, (canvas.getHeight() / 2) + rHeight);
	 //			//tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, (i * width) - rWidth + (canvas.getWidth() / 2), (j * height) - rHeight + (canvas.getHeight() / 2));
	 //		}
	 //	}
	 //}

	 //void draw(GamesEngineeringBase::Window& canvas, int wy) {
	 //	int tileSize = 32; // size of each square tile
	 //	int screenWidth = canvas.getWidth();
	 //	int screenHeight = canvas.getHeight();

	 //	int numTilesX = screenWidth / tileSize; // number of tiles horizontally
	 //	int numTilesY = screenHeight / tileSize; // number of tiles vertically

	 //	// Loop through each position in the grid
	 //	for (int y = 0; y < numTilesY; ++y) {
	 //		for (int x = 0; x < numTilesX; ++x) {
	 //			// Calculate a pseudo-random tile index for each position
	 //			int tileIndex = a[(y * numTilesX + x) % size];

	 //			// Calculate the position of each tile
	 //			int posX = x * tileSize;
	 //			int posY = y * tileSize + (wy % tileSize); // scrolling effect

	 //			// Draw the tile at the calculated position
	 //			tiles[tileIndex].Draw(canvas, posX, posY);
	 //		}
	 //	}
	 //}
};


int main() {
		// srand(static_cast<unsigned int>(time(NULL)));
		// construct windows
		GamesEngineeringBase::Window canvas;
		canvas.create(1024, 768, "Survivor");

		// construct objects
		CObject player(canvas.getWidth() / 2, canvas.getHeight() / 2, "Resources/L.png");

		// Enemy enemy;
		world w;
		GamesEngineeringBase::Timer tim;
		int x, y = 0; // position of hero
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

			if (canvas.keyPressed(VK_ESCAPE)) break;
			if (canvas.keyPressed('W')) y += 5;
			if (canvas.keyPressed('S')) y -= 1;
			if (canvas.keyPressed('A')) player.Update(-2, 0);
			if (canvas.keyPressed('D')) player.Update(2, 0);

			// Hero Creation
			// player.Update(canvas, canvas.getWidth()/2, canvas.getHeight()/2);
			player.Update(canvas, x, y);


			// Enemy Creation
			// enemy.Update(canvas, player, dt);
			// enemy.Collision(player);
			// Weapon Creation



			// Draw canvas
			//for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++)
			//	for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++)

			//		canvas.draw(tempx, tempy, 0, 0, 255);

			w.draw(canvas);


			// Display
			// enemy.Draw(canvas);
			player.Draw(canvas);
			//player.draw(canvas);

			// Frame display
			canvas.present();
		}
		return 0;
	}

