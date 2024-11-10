//#include<iostream>
//#include"GamesEngineeringBase.h"
//
//using namespace std;
//
//
////
////
////void updateMovementAnim(string name,GamesEngineeringBase::Window& canvas, int x, int y) {
////    int animIndex = 0;  
////    const int totalIndex = 5;
////    int counter = 0;
////    //if (++counter % 5 == 0) {
////    //    animIndex++;
////    //}
////    //animIndex = animIndex % totalIndex;
////    GamesEngineeringBase::Image sprite[totalIndex];
////
////    for (unsigned int i=0; i < 5; i++) {
////        sprite[i].load("Resources/" + name + to_string(i) + ".png");
////    }
////
////    if (animIndex < 5) {
////        animIndex++;
////    }
////    else {
////        animIndex = 0;
////    }
////    for (unsigned int i = 0; i < sprite[animIndex].width; i++) {
////        if (x + i > 0 && x + i < canvas.getWidth()) {
////            for (unsigned int j = 0; j < sprite[animIndex].height; j++) {
////                if (y + j > 0 && y + j < canvas.getHeight()) {
////                    if (sprite[animIndex].alphaAt(i, j) > 200)
////                        canvas.draw(x + i, y + j, sprite[animIndex].at(i, j));
////
////                }
////            }
////        }
////    }
////}
////
////int main() {
////    GamesEngineeringBase::Window canvas;
////    canvas.create(1024, 768, "Survivor");
////
////    GamesEngineeringBase::Timer dt;
////    bool running = true;
////    while (running) {
////        canvas.clear();
////        for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++) {
////            for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++) {
////                canvas.draw(tempx, tempy, 0, 0, 255);
////            }
////        }
////
////        updateMovementAnim("slime", canvas, 200, 200);
////
////
////        canvas.present();
////    }
////
////}
//
//void Draw(GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& sprite, int x, int y) {
//	// Draw objects to screen in its original material
//	for (unsigned int i = 0; i < sprite.width; i++) {
//		if (x + i > 0 && x + i < canvas.getWidth()) {
//			for (unsigned int j = 0; j < sprite.height; j++) {
//				if (y + j > 0 && y + j < canvas.getHeight()) {
//					if (sprite.alphaAt(i, j) > 200)
//						canvas.draw(x + i, y + j, sprite.at(i, j));
//				}
//			}
//		}
//	}
//}
//int main() {
//	GamesEngineeringBase::SoundManager soundmanager;
//	GamesEngineeringBase::Sound bgm;
//	soundmanager.loadMusic("bgm.wav");
//	GamesEngineeringBase::Window canvas;
//	canvas.create(1024, 768, "Survivor");
//
//	GamesEngineeringBase::Image title;
//	GamesEngineeringBase::Image title1;
//	GamesEngineeringBase::Image title2;
//
//	GamesEngineeringBase::Image menu;
//	GamesEngineeringBase::Image menu1;
//	GamesEngineeringBase::Image menu2;
//
//
//	GamesEngineeringBase::Image mode;
//	GamesEngineeringBase::Image mode1;
//	GamesEngineeringBase::Image mode2;
//
//
//	GamesEngineeringBase::Image exit;
//	GamesEngineeringBase::Image exit1;
//	GamesEngineeringBase::Image exit2;
//
//	GamesEngineeringBase::Image egg;
//	GamesEngineeringBase::Image egg1;
//	GamesEngineeringBase::Image egg2;
//
//
//	GamesEngineeringBase::Image background;
//
//	title.load("Resources/title0.png");
//	title1.load("Resources/title1.png");
//	title2.load("Resources/title2.png");
//
//	menu.load("Resources/menu0.png");
//	menu1.load("Resources/menu1.png");
//	menu2.load("Resources/menu2.png");
//	
//	mode.load("Resources/mode0.png");
//	mode1.load("Resources/mode1.png");
//	mode2.load("Resources/mode2.png");
//
//	exit.load("Resources/exit0.png");
//	exit1.load("Resources/exit1.png");
//	exit2.load("Resources/exit2.png");
//
//
//	egg.load("Resources/egg0.png");
//	egg1.load("Resources/egg1.png");
//	egg2.load("Resources/egg2.png");
//
//	background.load("Resources/background.png");
//	int offset = 225;
//	int offset1 = 380;
//
//	soundmanager.playMusic();
//	while (true) {
//		
//		canvas.clear();
//		for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++) {
//		for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++) {
//		canvas.draw(tempx, tempy, 0, 0, 255);
//			}
//		}
//		Draw(canvas, background, 0, 0);
//
//		Draw(canvas, title, offset, 75);
//		Draw(canvas, title1, offset+title.width, 75);
//		Draw(canvas, title2, offset+title.width + title1.width, 75);
//
//		Draw(canvas, menu, offset1, 300);
//		Draw(canvas, menu1, offset1 + menu.width, 300);
//		Draw(canvas, menu2, offset1 + menu.width + menu1.width, 300);
//
//		Draw(canvas, mode, offset1, 400);
//		Draw(canvas, mode1, offset1 + mode.width, 400);
//		Draw(canvas, mode2, offset1 + mode.width + mode1.width, 400);
//
//		Draw(canvas, exit, offset1, 500);
//		Draw(canvas, exit1, offset1 + exit.width, 500);
//		Draw(canvas, exit2, offset1 + exit.width + exit1.width, 500);
//
//		Draw(canvas, egg, offset1, 600);
//		Draw(canvas, egg1, offset1 + egg.width, 600);
//		Draw(canvas, egg2, offset1 + egg.width + egg1.width, 600);
//		canvas.present();
//	}
//
//	return 0;
//}
//	
//void dead(GamesEngineeringBase::Window& canvas) {
//	GamesEngineeringBase::Image dead;
//	dead.load("Resources/dead.png");
//	Draw(canvas, dead, 0, 0);
//}


#include<iostream>
#include<fstream>
#include"GamesEngineeringBase.h"
using namespace std;

int score = 0;

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

void DrawHealthBar(GamesEngineeringBase::Window& canvas, int x, int y, int currentHealth, int maxHealth, int barWidth, int barHeight) {
	// draw health bar based on percentage at canvas at specific location
	// calculate percentage
	if (maxHealth > 0) {
		float percentage = static_cast<float>(currentHealth) / maxHealth;

		bool runOnce = false;


		if (!runOnce) {
			for (unsigned int i = 0; i < barWidth; i++) {
				for (unsigned int j = 0; j < barHeight; j++) {
					if (x + i < canvas.getWidth() && y + j < canvas.getHeight())
						canvas.draw(x + i, y + j, 255, 255, 255); // draw background
					runOnce = true;
				}
			}

		}

		for (unsigned int i = 0; i < static_cast<int> (barWidth * percentage); i++) {
			for (unsigned int j = 0; j < barHeight; j++) {
				if (x + i < canvas.getWidth() && y + j < canvas.getHeight())
					canvas.draw(x + i, y + j, 255, 0, 0); // draw real time blood
			}
		}

	}

}


class CObject
{
private:

protected:
	GamesEngineeringBase::Image sprite;
public:
	int attack;
	int currentHealth;
	int maxHealth;
	int x, y; // world position
	CObject() {}
	CObject(int _x, int _y, string filename, int _maxHealth, int _attack) {
		sprite.load(filename);
		x = _x - sprite.width / 2;
		y = _y;
		attack = _attack;
		maxHealth = _maxHealth;
		currentHealth = maxHealth;
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

		//drawCircle(canvas, x + sprite.width / 2, y + sprite.height / 2, sprite.width / 3);
	}


	void Draw(GamesEngineeringBase::Window& canvas, int x, int y) {
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

		//drawCircle(canvas, x + sprite.width / 2, y + sprite.height / 2, sprite.width / 3);
	}

	virtual void DrawHealth(GamesEngineeringBase::Window& canvas) {
		DrawHealthBar(canvas, x, y + sprite.height, currentHealth, maxHealth, sprite.width, 3);
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

	bool CircleCollidor(CObject& other, int type) {
		// Check collision between this and other objects
		int dx = x - other.x;
		int dy = y - other.y;

		float radius = static_cast<float>(sprite.width / 2.5f);
		float otherRadius = static_cast<float>(other.sprite.width / 2.5f);
		// Euclidean distance of two objects
		float d = sqrtf(dx * dx + dy * dy);
		if (type == 0) {
			if (d < 2.0f * otherRadius) {
				return true;
			}
			else return false;
		}
		if (type == 1) {
			if (d < 2.0f * radius) {
				return true;
			}
			else return false;
		}

	}



	void NotCross() {
		// ban moving at this time, the player can move in the next frame
		x = x;
		y = y;
	}

	int getAttack() {
		return attack;
	}

	int getHealth() {
		return currentHealth;
	}

	void decreaseHealth(int decrease) {
		currentHealth -= decrease;
		if (currentHealth <= 0) currentHealth = 0;
	}

	void testdecreaseHealth() {
		currentHealth -= 20;
		if (currentHealth <= 0) currentHealth = 0;
	}

	bool isAlive() {
		return currentHealth > 0;
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

	void fight(CObject& other) {
		if (currentHealth > 0 && other.currentHealth > 0) {
			other.decreaseHealth(attack);
			decreaseHealth(other.attack);
		}
	}

	void gameOver(bool& running) {
		bool isalive = isAlive();
		if (!isalive) {
			running = false;
			cout << "game over" << endl;
			cout << "score is: " << score << endl;
		}
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
						canvas.draw(x + i, y + j, sprite.atUnchecked(i, j));
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

	bool CircleCollidor(CObject& other, int px, int py) {
		// Check collision between this and other objects
		int dx = px - other.x;
		int dy = py - other.y;

		float radius = static_cast<float>(sprite.width / 2.5f);
		// Euclidean distance of two objects
		float d = sqrtf(dx * dx + dy * dy);
		if (d < 2.0f * radius) return true;
		else return false;
	}

	GamesEngineeringBase::Image& GetSprite() {
		return sprite;
	}

	bool isWater(int num) {
		if (num >= 14 && num <= 22) {
			return true;
		}

	}
};

const unsigned int tileNum = 23;
class tileSet {
	tile tiles[tileNum];
public:
	tileSet() {}
	void Load(string s = "") {
		for (unsigned i = 0; i < tileNum; i++) {
			string filename = "Resources/" + s + to_string(i) + ".png";
			tiles[i].Load(filename);
			// cout << "Load complete" << endl;
		}
	}
	// overload [] to access individual elements from array directly
	tile& operator[](unsigned int index)
	{
		return tiles[index];
	}

};



const int maxSizeY = 80;
const int maxSizeX = 80;

class world {
	tileSet tiles;
	tileSet alphas;
	// unsigned int* map;
	unsigned int size = 80;
	unsigned int* map1;
	unsigned finiteMap[200][40];
public:
	unsigned int map[maxSizeX][maxSizeY];
	bool isWater[maxSizeX][maxSizeY];


	// int map1[32][24];
public:

	world() {
		// try use number of tile for whole screen:32*24=768 tiles
		// try AREA method
		size = maxSizeX;
		// map = new unsigned int[maxSizeX][maxSizeY];
		tiles.Load();
		alphas.Load("alpha");

		for (unsigned int i = 0; i < maxSizeX; i++) {
			for (unsigned int j = 0; j < maxSizeY; j++) {
				map[i][j] = rand() % tileNum; // randomly choose a tile and put it into 2D array

				if (map[i][j] >= 14 && map[i][j] <= 22) {
					isWater[i][j] = true;
				}
				else {
					isWater[i][j] = false;
				}
			}
		}
	}

	world(std::string filename) {
		tiles.Load();
		alphas.Load("alpha");
		int tileswide = 42;
		int tileshigh = 42;
		int tilewidth = 32;
		int tileheight = 32;
		std::ifstream infile(filename);
		if (!infile.is_open()) {
			// opening error check
			cout << "Error opening file: " << filename << std::endl;
			return;
		}

		int i = 0, j = 0;
		char ch;
		int num = 0;
		bool readingNumber = false;
		cout << "map is loading..." << endl;
		while (infile.get(ch)) {
			if (ch >= '0' && ch <= '9') {
				// Accumulate the number character by character
				num = num * 10 + (ch - '0'); // transfer to int
				readingNumber = true;
			}
			if (ch == ',' || ch == '\n') {
				// If we encounter a comma or newline, we complete the current number
				if (readingNumber) {
					if (i < maxSizeX && j < maxSizeY) {
						map[j][i] = num;
						// cout << "map[" << i << "][" << j << "] = " << num << endl;
						j++;
						if (j >= 200) { // Move to the next row if column limit is reached
							j = 0;
							i++;
						}
					}
					num = 0;           // Reset num for the next number
					readingNumber = false; // Reset flag
				}

				// If newline is encountered, reset column and go to next row
				if (ch == '\n') {
					j = 0;
					i++;
				}
			}

			if (map[i][j] >= 14 && map[i][j] <= 22) {
				isWater[i][j] = true;
			}
			else {
				isWater[i][j] = false;
			}
		}
		cout << "loading completed" << endl;
	}
	void draw(GamesEngineeringBase::Window& canvas, CObject& player, int wx, int wy) {
		int height = tiles[0].GetHeight(); // should not be limited in specific tile, but considering every tile should be sliced to 32*32 for pixel game, so it is fine 
		int width = tiles[0].GetWidth();

		int Y = wy / height;
		int rY = wy % height;

		int X = wx / width;
		int rX = wx % width;

		int tileSize = 32;
		for (unsigned i = 0; i < canvas.getWidth() / width; i++) {
			for (unsigned j = 0; j < canvas.getHeight() / height; j++) {
				tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, 32 * i, 32 * j);
				if (map[i][j] >= 14 && map[i][j] <= 22) {
					// apply circle collider
					if (tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].CircleCollidor(player, 32 * i, 32 * j)) {
						cout << "collidor deteted" << endl;
					}
				}
			}

		}
	}


	void drawAlpha(GamesEngineeringBase::Window& canvas, int wx, int wy) {
		int height = tiles[0].GetHeight(); // should not be limited in specific tile, but considering every tile should be sliced to 32*32 for pixel game, so it is fine 
		int width = tiles[0].GetWidth();

		int Y = wy / height;
		int rY = wy % height;

		int X = wx / width;
		int rX = wx % width;

		int tileSize = 32;
		for (unsigned i = 0; i < canvas.getWidth() / width; i++) {
			for (unsigned j = 0; j < canvas.getHeight() / height; j++) {
				alphas[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, 32 * i, 32 * j);
			}
		}
	}

	bool isCollision(int num) {
		if (num >= 14 && num <= 22) {
			return true;
		}

	}

	//bool Tilecollider(CObject& player,int x, int y) {
	//	for (unsigned int i = x; i < x + player.GetWidth(); i++) {
	//		for (unsigned int j = y; j < y + player.GetHeight(); i++) {
	//			//cout << "map[i / 32][j / 32]" << map[i / 32][j / 32] << endl;
	//			cout << "i" << i << endl;
	//			//cout << "map[i / 32][j / 32]" << map[i / 32][j / 32] << endl;
	//			if (tiles[map[i / 32][j / 32]].isWater(map[i / 32][j / 32]))// should not be const number.
	//				
	//				cout << "collision detected" << endl;
	//				return true;
	//		}
	//	}
	//	return false;
	//}

	//bool Tilecollider(CObject& player, int x, int y) {
	//	int tileWidth = 32;
	//	int tileHeight = 32;

	//	// Get the range of tiles covered by the player's bounding box
	//	int startX = x / tileWidth;
	//	int startY = y / tileHeight;
	//	int endX = (x + player.GetWidth()) / tileWidth;
	//	int endY = (y + player.GetHeight()) / tileHeight;

	//	for (int i = startX; i <= endX; i++) {
	//		for (int j = startY; j <= endY; j++) {
	//			int tileIndex = map[j][i];  // Access the tile index in the map

	//			//cout << "Checking tile at (" << i << ", " << j << ") with index: " << tileIndex << endl;
	//			//cout << "tileindex is" << tileIndex << endl;
	//			// Check if the tile at the current position is water or has collision
	//			if (tiles[tileIndex].isWater(tileIndex)) {
	//				// cout << "Collision detected with water tile at (" << i << ", " << j << ")" << endl;
	//				return true;
	//			}
	//		}
	//	}
	//	return false;
	//}
	bool Tilecollider(CObject& player, int x, int y) {
		int tileWidth = 32;
		int tileHeight = 32;

		// Calculate player's position in terms of tile indices
		int playerTileX = x / tileWidth;
		int playerTileY = y / tileHeight;

		// Calculate the bounding box in terms of tile indices
		int startX = playerTileX;
		int startY = playerTileY;
		int endX = (x + player.GetWidth()) / tileWidth;
		int endY = (y + player.GetHeight()) / tileHeight;

		// Loop over the range of tiles occupied by the player
		for (int i = startX; i <= endX; i++) {
			for (int j = startY; j <= endY; j++) {
				// Ensure i and j are within map bounds to prevent out-of-range errors
				if (i >= 0 && i < 42 && j >= 0 && j < 42) { // assuming map is 42x42
					int tileIndex = map[j][i];

					// Calculate the original top-left position of this tile in pixels
					int tilePosX = i * tileWidth;
					int tilePosY = j * tileHeight;

					//std::cout << "Tile at (" << i << ", " << j << ") has original position: ("<< tilePosX << ", " << tilePosY << ") with index: " << tileIndex << std::endl;

					// Check for collision using the tile's properties (e.g., if it's water)
					if (tiles[tileIndex].isWater(tileIndex)) {
						//std::cout << "Collision detected with water tile at (" << i << ", " << j << ")" << std::endl;
						return true;
					}
				}
			}
		}
		return false;
	}

};


class FiniteWorld {
	tileSet tiles;
	tileSet alphas;
	unsigned int sizeX = 200;  // Define the width of the world
	unsigned int sizeY = 40;   // Define the height of the world
	unsigned int map[maxSizeX][maxSizeY];  // Map array for tiles
	bool isWater[maxSizeX][maxSizeY];  // Water detection array

public:
	// Constructor for generating the world with a finite map
	FiniteWorld() {
		tiles.Load();
		alphas.Load("alpha");

		// Generate the map with random tiles for a finite world
		for (unsigned int i = 0; i < sizeX; i++) {
			for (unsigned int j = 0; j < sizeY; j++) {
				map[i][j] = rand() % tileNum; // Randomly choose a tile
				isWater[i][j] = (map[i][j] >= 14 && map[i][j] <= 22);  // Detect water tiles
			}
		}
	}

	// Constructor for loading a world from a file (finite)
	FiniteWorld(string filename) {
		tiles.Load();
		alphas.Load("alpha");

		ifstream infile(filename);
		if (!infile.is_open()) {
			cout << "Error opening file: " << filename << endl;
			return;
		}

		int i = 0, j = 0;
		char ch;
		int num = 0;
		bool readingNumber = false;

		while (infile.get(ch)) {
			if (ch >= '0' && ch <= '9') {
				num = num * 10 + (ch - '0');
				readingNumber = true;
			}
			if (ch == ',' || ch == '\n') {
				if (readingNumber) {
					if (i < sizeX && j < sizeY) {
						map[j][i] = num;
						j++;
						if (j >= sizeY) {
							j = 0;
							i++;
						}
					}
					num = 0;
					readingNumber = false;
				}
				if (ch == '\n') {
					j = 0;
					i++;
				}
			}
		}
	}

	// Function to draw the finite world
	void draw(GamesEngineeringBase::Window& canvas, CObject& player, int wx, int wy) {
		int height = tiles[0].GetHeight();
		int width = tiles[0].GetWidth();

		int Y = wy / height;
		int X = wx / width;

		for (unsigned i = 0; i < canvas.getWidth() / width; i++) {
			for (unsigned j = 0; j < canvas.getHeight() / height; j++) {
				int tileX = (X + i) % sizeX;
				int tileY = (Y + j) % sizeY;
				tiles[map[tileX][tileY]].Draw(canvas, 32 * i, 32 * j);

				// Check for collision with water tiles
				if (isWater[tileX][tileY]) {
					if (tiles[map[tileX][tileY]].CircleCollidor(player, 32 * i, 32 * j)) {
						cout << "Collider detected!" << endl;
					}
				}
			}
		}
	}

	// Function to draw alpha layer (optional)
	void drawAlpha(GamesEngineeringBase::Window& canvas, int wx, int wy) {
		int height = tiles[0].GetHeight();
		int width = tiles[0].GetWidth();

		int Y = wy / height;
		int X = wx / width;

		for (unsigned i = 0; i < canvas.getWidth() / width; i++) {
			for (unsigned j = 0; j < canvas.getHeight() / height; j++) {
				int tileX = (X + i) % sizeX;
				int tileY = (Y + j) % sizeY;
				alphas[map[tileX][tileY]].Draw(canvas, 32 * i, 32 * j);
			}
		}
	}

	// Check if a given tile is water
	bool isCollision(int x, int y) {
		if (x < sizeX && y < sizeY) {
			return isWater[x][y];
		}
		return false;
	}
};


// class bullet; //forward declaration to make enemy collider only accepts bullet
const unsigned int maxSize1 = 1000;
//
class Enemy : public CObject { //: public CObject {
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 2.f; // the time to next enemy creation

	float attackElapsed = 0.f; // time since last attack
	float attackThreshold = 2.f; // the time to next attack

	int offset = 200;
	void Random(GamesEngineeringBase::Window& canvas, int _offset) {
		offset = _offset;
		int side = rand() % 4;
		switch (side) {
		case 0:
			// Generate enemy from topsssss
			px = rand() % canvas.getWidth();
			py = -offset;
			break;
		case 1:
			// Generate enemy from bottom
			px = rand() % canvas.getWidth();
			py = canvas.getHeight() + offset;
			break;
		case 2:
			// generate enemy from left
			px = -offset;
			py = rand() % canvas.getHeight();
			break;
		case 3:
			// generate enemy from right
			px = canvas.getWidth() + offset;
			py = rand() % canvas.getHeight();
			break;
		}
	}



	bool isOutBound(int _px, int _py, GamesEngineeringBase::Window& canvas, int _offset) {
		// check if object out boundary
		px = _px;
		py = _py;
		return (px < -_offset ||
			px > canvas.getWidth() + _offset ||
			py < -_offset ||
			py > canvas.getHeight() + _offset);
	}

	void DeleteOutBound(GamesEngineeringBase::Window& canvas, unsigned int i) {
		if (i >= maxSize1 || enemyArray[i] == nullptr) return;
		if (isOutBound(enemyArray[i]->GetX(), enemyArray[i]->GetY(), canvas, 350)) {
			CObject* enemyDelete = enemyArray[i];
			enemyArray[i] = nullptr;
			delete enemyDelete;
			kills++;
			cout << "destroyed " << i << endl;
		}
	}



public:

	int maxHealth = 20;
	int currentHealth;
	int attack = 10;
	GamesEngineeringBase::Image sprite;
	CObject* enemyArray[100];
	unsigned int currentSize = 0;
	int px = 200;
	int py = 200;
	int x;
	int y;
	int award = 10;
	unsigned int kills = 0;
	Enemy(int _x, int _y) {
		x = _x;
		y = _y;
		currentHealth = maxHealth;
	};

	void GenerateEnemy(GamesEngineeringBase::Window& canvas, float dt, string filename) {
		Random(canvas, 100);
		timeElapsed += dt;
		//x = px;
		//y = py;
		if (currentSize < maxSize1) {
			if (timeElapsed > timeThreshold) {
				CObject* newEnemy = new CObject(px, py, filename, maxHealth, attack);
				cout << "Enemy created: " << currentSize << endl;
				// Save address of new enemy to array
				enemyArray[currentSize++] = newEnemy;
				// reset generation parameter
				timeElapsed = 0.f;
				timeThreshold -= 0.02f;
				// difficulty control
				timeThreshold = max(0.9f, timeThreshold);
				DrawHealth(canvas);
			}
		}
		else {
			cout << "Last Enemy!!!" << endl;
		}
	}

	void Update(GamesEngineeringBase::Window& canvas, CObject& player, CObject& bullet, float dt, string filename) {

		GenerateEnemy(canvas, dt, filename);

		// cout << "After generate enemy running!" << endl;
		  // define speed
		int speed = static_cast<int>((70.0f * dt));

		for (unsigned int i = 0; i < currentSize; i++) {
			if (enemyArray[i] != nullptr) {
				// calculate direction between player and enemy
				float dx = player.GetX() - enemyArray[i]->GetX();
				float dy = player.GetY() - enemyArray[i]->GetY();
				float distance = sqrtf(dx * dx + dy * dy);
				// add check to avoid devided by 0
				if (distance > 0.0f) {
					int moveX = static_cast<int>((dx / distance) * speed);
					int moveY = static_cast<int>((dy / distance) * speed);
					enemyArray[i]->Update(moveX, moveY);

					// cout << "collision result is: " << Collision(player) << endl;
					// cout << "the result of circlecollidor is" << CircleCollidor(bullet) << endl;
					if (enemyArray[i]->currentHealth <= 0) {

						// if crush, delete immediately
						CObject* enemyDelete = enemyArray[i];
						enemyArray[i] = nullptr;
						delete enemyDelete;
						kills++;
						score += award;
						//	}
							// If a collision is detected, delete this specific enemy

							//cout << "destroyed " << i << endl;
					}
					else if (enemyArray[i]->CircleCollidor(player, 1)) {
						attackElapsed += dt;
						if (attackElapsed > attackThreshold) {
							player.decreaseHealth(attack);
							attackElapsed = 0.f;
						}
					}

				}
			}
			DeleteOutBound(canvas, i);
		}

	}

	void Draw(GamesEngineeringBase::Window& canvas) {
		for (unsigned int i = 0; i < currentSize; i++) {
			if (enemyArray[i] != nullptr) {
				enemyArray[i]->Draw(canvas);
				// enemyArray[i]->DrawHealth(canvas);
			}
		}
	}


	void DrawHealth(GamesEngineeringBase::Window& canvas) override {
		DrawHealthBar(canvas, px, py, currentHealth, maxHealth, 83, 3);
	}


};
//class Enemy : public CObject {
//	float timeElapsed = 0.f;
//	float timeThreshold = 2.f;
//
//	float attackElapsed = 0.f;
//	float attackThreshold = 2.f;
//
//	int offset = 200;
//
//	void Random(GamesEngineeringBase::Window& canvas, int _offset) {
//		offset = _offset;
//		int side = rand() % 4;
//		switch (side) {
//		case 0: // Top
//			px = rand() % canvas.getWidth();
//			py = -offset;
//			break;
//		case 1: // Bottom
//			px = rand() % canvas.getWidth();
//			py = canvas.getHeight() + offset;
//			break;
//		case 2: // Left
//			px = -offset;
//			py = rand() % canvas.getHeight();
//			break;
//		case 3: // Right
//			px = canvas.getWidth() + offset;
//			py = rand() % canvas.getHeight();
//			break;
//		}
//	}
//
//	bool isOutBound(int _px, int _py, GamesEngineeringBase::Window& canvas, int _offset) {
//		return (_px < -_offset || _px > canvas.getWidth() + _offset ||
//			_py < -_offset || _py > canvas.getHeight() + _offset);
//	}
//
//	void DeleteOutBound(GamesEngineeringBase::Window& canvas, unsigned int i) {
//		if (i >= maxSize1 || enemyArray[i] == nullptr) return;
//		if (isOutBound(enemyArray[i]->GetX(), enemyArray[i]->GetY(), canvas, 350)) {
//			CObject* enemyDelete = enemyArray[i];
//			enemyArray[i] = nullptr;
//			delete enemyDelete;
//			kills++;
//			cout << "Destroyed " << i << endl;
//		}
//	}
//
//public:
//	int maxHealth = 20;
//	int currentHealth;
//	int attack = 10;
//	GamesEngineeringBase::Image sprite;
//	CObject* enemyArray[100];
//	unsigned int currentSize = 0;
//	int px = 200;
//	int py = 200;
//	int x;
//	int y;
//	int award = 10;
//	unsigned int kills = 0;
//
//	Enemy(int _x, int _y) {
//		x = _x;
//		y = _y;
//		currentHealth = maxHealth;
//	};
//
//	void GenerateEnemy(GamesEngineeringBase::Window& canvas, float dt, const std::string& filename) {
//		Random(canvas, 100);
//		timeElapsed += dt;
//		x = px;
//		y = py;
//		if (currentSize < maxSize1 && timeElapsed > timeThreshold) {
//			CObject* newEnemy = new CObject(px, py, filename, maxHealth, attack);
//			enemyArray[currentSize++] = newEnemy;
//			timeElapsed = 0.f;
//			timeThreshold = max(0.9f, timeThreshold - 0.02f); // Difficulty control
//			DrawHealth(canvas);
//		}
//	}
//
//	void Update(GamesEngineeringBase::Window& canvas, CObject& player, CObject& bullet, float dt, const std::string& filename, int mapOffsetX, int mapOffsetY) {
//		GenerateEnemy(canvas, dt, filename);
//
//		// define enemy speed
//		int speed = static_cast<int>((70.0f * dt));
//
//		for (unsigned int i = 0; i < currentSize; i++) {
//			if (enemyArray[i] != nullptr) {
//				// Get the player's position relative to the screen after map offset
//				float playerScreenX = player.GetX() - mapOffsetX;
//				float playerScreenY = player.GetY() - mapOffsetY;
//
//				// Calculate direction between the player and the enemy, considering map offset
//				float dx = playerScreenX - enemyArray[i]->GetX();
//				float dy = playerScreenY - enemyArray[i]->GetY();
//				float distance = sqrtf(dx * dx + dy * dy);
//
//				// If distance > 0, move the enemy toward the player
//				if (distance > 0.0f) {
//					int moveX = static_cast<int>((dx / distance) * speed);
//					int moveY = static_cast<int>((dy / distance) * speed);
//
//					// Move the enemy towards the player with adjusted direction
//					enemyArray[i]->Update(moveX, moveY);
//				}
//
//				// Handle enemy death and collision with player
//				if (enemyArray[i]->currentHealth <= 0) {
//					CObject* enemyDelete = enemyArray[i];
//					enemyArray[i] = nullptr;
//					delete enemyDelete;
//					kills++;
//					score += award;
//				}
//				else if (enemyArray[i]->CircleCollidor(player, 1)) {
//					attackElapsed += dt;
//					if (attackElapsed > attackThreshold) {
//						player.decreaseHealth(attack);
//						attackElapsed = 0.f;
//					}
//				}
//			}
//			DeleteOutBound(canvas, i);
//		}
//	}
//
//	void Draw(GamesEngineeringBase::Window& canvas, int mapOffsetX, int mapOffsetY) {
//		for (unsigned int i = 0; i < currentSize; i++) {
//			if (enemyArray[i] != nullptr) {
//				// Apply map offset only when drawing
//				int drawX = enemyArray[i]->GetX() + mapOffsetX;
//				int drawY = enemyArray[i]->GetY() + mapOffsetY;
//				enemyArray[i]->Draw(canvas, drawX, drawY);
//			}
//		}
//	}
//
//	void DrawHealth(GamesEngineeringBase::Window& canvas) override {
//		DrawHealthBar(canvas, px, py, currentHealth, maxHealth, 83, 3);
//	}
//};



class Enemy2 :public Enemy {
public:
	Enemy2(int _x, int _y) : Enemy(_x, _y) {

	};

	int maxHealth = 50;
	int currentHealth;
	GamesEngineeringBase::Image sprite;
	CObject* enemyArray[50];
	unsigned int currentSize = 0;
	int px = 200;
	int py = 200;
	int x = 0;
	int y = 0;
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 5.f; // the time to next enemy creation
	int offset = 200;
	int award = 30;
};

class Enemy3 : public Enemy {
public:
	Enemy3(int _x, int _y) : Enemy(_x, _y) {

	};
	int maxHealth = 70;
	int currentHealth;
	GamesEngineeringBase::Image sprite;
	CObject* enemyArray[30];
	unsigned int currentSize = 0;
	int px = 200;
	int py = 200;
	int x = 0;
	int y = 0;
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 15.f; // the time to next enemy creation
	int offset = 200;
	int award = 50;
};




class Enemy4 : public Enemy {
public:
	Enemy4(int _x, int _y) : Enemy(_x, _y) {

	};
	int maxHealth = 10;
	int currentHealth;
	GamesEngineeringBase::Image sprite;
	CObject* enemyArray[5];
	unsigned int currentSize = 0;
	int px = 200;
	int py = 200;
	int x = 0;
	int y = 0;
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 12.f; // the time to next enemy creation
	int offset = 200;
	int award = 40;
	float attackElapsed = 0.f; // time since last attack
	float attackThreshold = 5.f; // the time to next attack

	void GenerateEnemy(GamesEngineeringBase::Window& canvas, float dt, string filename) {
		px = rand() % canvas.getWidth();
		py = rand() % canvas.getHeight();
		timeElapsed += dt;
		if (currentSize < maxSize1) {
			if (timeElapsed > timeThreshold) {
				CObject* newEnemy = new CObject(px, py, filename, maxHealth, attack);
				cout << "Enemy created: " << currentSize << endl;
				// Save address of new enemy to array
				enemyArray[currentSize++] = newEnemy;
				// reset generation parameter
				timeElapsed = 0.f;
				timeThreshold -= 0.02f;
				// difficulty control
				timeThreshold = max(5.f, timeThreshold);

				DrawHealth(canvas);
			}
		}
		else {
			cout << "Last Enemy!!!" << endl;
		}
	}

	void Update(GamesEngineeringBase::Window& canvas, CObject& player, CObject bullet, float dt, string filename) {


		GenerateEnemy(canvas, dt, filename);
		for (unsigned int i = 0; i < currentSize; i++) {
			if (enemyArray[i]->CircleCollidor(player, 1) || enemyArray[i]->CircleCollidor(bullet, 1)) {
				// fight(player);
				//if (currentHealth <= 0) {
				CObject* enemyDelete = enemyArray[i];
				enemyArray[i] = nullptr;
				delete enemyDelete;
				kills++;
				score += 10;
			}
		}
	}
};



int level[5] = { 1,2,3,4,5 };
int const weaponLevel = 1;
int maxBullet = weaponLevel;
int const numberBullets = 1000;

class AoeAttack : public CObject {
public:
	float timeElapsed = 0.f;
	float timeThreshold = 5.f; // the time to next available attack

	void Aoe(Enemy& enemy, int damage, int dt) {
		timeElapsed += dt;
		// define empty array for enemy and their blood
		CObject* targetEnemies[3] = { nullptr, nullptr, nullptr }; // pointer to each enemy
		int targetHealth[3] = { 0,0,0 };
		// target enemy
		for (unsigned int i = 0; i < enemy.currentSize; i++) {
			if (enemy.enemyArray[i] != nullptr) {
				// check and compare their current health
				int health = enemy.enemyArray[i]->currentHealth;

				if (health > targetHealth[0]) {
					// push current values back
					targetEnemies[2] = targetEnemies[1];
					targetHealth[2] = targetHealth[1];
					targetEnemies[1] = targetEnemies[0];
					targetHealth[1] = targetHealth[0];
					// assign new values and health
					targetEnemies[0] = enemy.enemyArray[i];
					targetHealth[0] = health;
				}
				else if (health > targetHealth[1]) {

					targetEnemies[2] = targetEnemies[1];
					targetHealth[2] = targetHealth[1];
					targetEnemies[1] = enemy.enemyArray[i];
					targetHealth[1] = health;
				}
				else if (health > targetHealth[2]) {
					targetEnemies[2] = enemy.enemyArray[i];
					targetHealth[2] = health;
				}
				else { cout << "No AOE target" << endl; }
			}
		}
		// executive attack
		if (targetEnemies != nullptr) {
			for (unsigned int i = 0; i < 3; i++) {
				targetEnemies[i]->decreaseHealth(damage);
				cout << "AOE attack finished" << endl;
			}
			timeElapsed = 0.f;
			timeThreshold -= 0.02f;
		}
	}
};



class bullet : public CObject {

public:
	int attack = 30;
	float timeElapsed = 0.f; // time since last bullet
	float timeThreshold = 2.5f; // the time to next bullet generation
	bool isCollision;
	CObject* bullets[numberBullets];
	unsigned int currentNumber = 0;
	//float dx = 0.f;
	//float dy = 0.f;
	//float distance = 0.f;
	bullet() {

	}

	// bullet targeted to enemy
	void GenerateBullet(GamesEngineeringBase::Window& canvas, CObject& player, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4, float dt) {
		// the number of bullet targeted to enemy depends on weaponLevel

		timeElapsed += dt;
		if (currentNumber < numberBullets) {

			if (timeElapsed > timeThreshold) {
				CObject* closestEnemy = FindClosestEnemy(canvas, player, enemy, enemy2, enemy3, enemy4);

				//cout << "value of cloest enemy after findcloest enemy is" << closestEnemy << endl;

				// loop from existing enemy to find closest one;
				if (closestEnemy != nullptr) {
					// cout << "4th if running" << endl;
					// create new bullet start from player's position
					CObject* newBullet = new CObject(player.GetX() + player.GetWidth() / 2, player.GetY() + player.GetHeight() / 2, "Resources/bullet1.png", 0, 20);
					//cout << "Bullet created" << endl;
					bullets[currentNumber++] = newBullet;

					timeElapsed = 0.f;
					timeThreshold = 2 / weaponLevel; // generate bullets more frequent as level increases;
					timeThreshold = max(1.f, timeThreshold); // set maximum frequency
					//cout << "generate bullet finished" << endl;
				}
			}
		}
	}

	CObject* FindClosestEnemy(GamesEngineeringBase::Window& canvas, CObject& player, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4) {
		CObject* closestEnemy = nullptr;

		float smallestDistance = canvas.getHeight() / 2;

		Enemy* enemies[] = { &enemy, &enemy2, &enemy3,&enemy4 };
		for (Enemy* enemy : enemies) {
			for (unsigned int i = 0; i < enemy->currentSize; i++) {
				// searching enemy which has already been generated
				if (enemy->enemyArray[i] != nullptr) {
					// calculate distance
					float dx = player.GetX() - enemy->enemyArray[i]->GetX();
					float dy = player.GetY() - enemy->enemyArray[i]->GetY();
					float distance = sqrtf(dx * dx + dy * dy);
					if (distance < smallestDistance) {
						smallestDistance = distance;
						closestEnemy = enemy->enemyArray[i];

						// cout << "value of cloest enemy in findcloest enemy is" << closestEnemy << endl;
					}
				}

			}
		}
		return closestEnemy;
	}


	void Update(GamesEngineeringBase::Window& canvas, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4, CObject& player, float dt) {
		// make bullet fly to enemy

		GenerateBullet(canvas, player, enemy, enemy2, enemy3, enemy4, dt);
		// cout << "value of cloest enemy update enemy is" << closestEnemy << endl;
		int speed = 80.0f * dt;

		for (unsigned int i = 0; i < currentNumber; i++) {
			if (bullets[i] != nullptr) {
				// Find the closest enemy for each bullet movement update
				CObject* closestEnemy = FindClosestEnemy(canvas, player, enemy, enemy2, enemy3, enemy4);
				// cout << "closest enemy is " << closestEnemy << endl;
				if (closestEnemy != nullptr) {
					float dx = closestEnemy->GetX() - bullets[i]->GetX() + 25;
					float dy = closestEnemy->GetY() - bullets[i]->GetY() + 50;
					float distance = sqrtf(dx * dx + dy * dy);

					if (distance > 0.0f) {

						int moveX = static_cast<int>((dx / distance) * speed);
						int moveY = static_cast<int>((dy / distance) * speed);
						bullets[i]->Update(moveX, moveY);
						isCollision = bullets[i]->CircleCollidor(*closestEnemy, 0);
						// cout << "closet enemy blood: " << closestEnemy->currentHealth;
						if (isCollision || closestEnemy == nullptr) {
							// cout << "bullet checking result is" << bullets[i]->CircleCollidor(*closestEnemy,0) << endl;
							// If a collision is detected, delete this specific enemy
							//cout << "enemy" << i << "is collision with player" << endl;
							// CheckDeletedEnemy(canvas, i);
							CObject* bulletDelete = bullets[i];
							bullets[i] = nullptr;
							delete bulletDelete;
							closestEnemy->decreaseHealth(attack);


						}
					}
				}
			}
		}
	}

	void Draw(GamesEngineeringBase::Window& canvas) {
		for (unsigned int i = 0; i < currentNumber; i++) {
			if (bullets[i] != nullptr)
				bullets[i]->Draw(canvas);
		}
	}

};

//class enemyBullet : public bullet {
//public:
//	
//	void GenerateBullet(GamesEngineeringBase::Window& canvas, CObject& player, Enemy4& enemy, float dt) {
//		// the number of bullet targeted to enemy depends on weaponLevel
//
//		timeElapsed += dt;
//		if (currentNumber < numberBullets) {
//
//			if (timeElapsed > timeThreshold) {
//				
//					CObject* newBullet = new CObject(enemy.px, enemy.py / 2,"Resources/bullet1.png",1,10);
//					//cout << "Bullet created" << endl;
//					bullets[currentNumber++] = newBullet;
//
//					timeElapsed = 0.f;
//					timeThreshold = 2; // generate bullets more frequent as level increases;
//					
//					//cout << "generate bullet finished" << endl;
//				
//			}
//		}
//	}
//
//	void Update(GamesEngineeringBase::Window& canvas, Enemy4& enemy, CObject& player, float dt) {
//		// make bullet fly to enemy
//
//		GenerateBullet(canvas, player, enemy, dt);
//		// cout << "value of cloest enemy update enemy is" << closestEnemy << endl;
//		int speed = 30.0f * dt;
//
//		for (unsigned int i = 0; i < currentNumber; i++) {
//			if (bullets[i] != nullptr) {
//				// Find the closest enemy for each bullet movement update
//				CObject* closestEnemy = FindClosestEnemy(canvas, player, enemy);
//				// cout << "closest enemy is " << closestEnemy << endl;
//				if (closestEnemy != nullptr) {
//					float dx = player.GetX() - bullets[i]->GetX() + 25;
//					float dy = player.GetY() - bullets[i]->GetY() + 50;
//					float distance = sqrtf(dx * dx + dy * dy);
//
//					if (distance > 0.0f) {
//
//						int moveX = static_cast<int>((dx / distance) * speed);
//						int moveY = static_cast<int>((dy / distance) * speed);
//						bullets[i]->Update(moveX, moveY);
//
//						if (bullets[i]->CircleCollidor(player,0)) {
//							// If a collision is detected, delete this specific enemy
//							//cout << "enemy" << i << "is collision with player" << endl;
//							// CheckDeletedEnemy(canvas, i);
//							CObject* bulletDelete = bullets[i];
//							bullets[i] = nullptr;
//							delete bulletDelete;
//							player.decreaseHealth(attack);
//							cout << "bullet destroyed " << i << endl;
//						}
//					}
//				}
//			}
//		}
//	}
//
//};

int currentLevel = 0;
void Draw(GamesEngineeringBase::Window& canvas, GamesEngineeringBase::Image& sprite, int x, int y) {
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
}
void levelup(int& currentLevel, int& score) {
	currentLevel = score / 100;
	currentLevel = min(currentLevel, 5); // control the level scope to be limited for design purpose
	// some sfx to notify upgrade!
}
// !global parameters
int aoeDamage = 20 * currentLevel;

class gameSystem {
public:
	void save(CObject& player, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4, bool& running) {
		ofstream outfile("player.txt");
		// ofstream outfile("player.dat", ios::binary);
		if (!outfile) {
			cout << "saving error!" << endl;
		}
		outfile << "global variables:" << endl;
		outfile << currentLevel << " " << score << " " << endl;

		outfile << "player:" << endl;
		outfile << player.GetX() << " " << player.GetY() << " " << player.currentHealth << endl;

		outfile << "Enemy: " << endl;
		outfile << enemy.currentSize << endl;
		// save each enemy alive
		for (unsigned int i = 0; i < enemy.currentSize; i++) {
			if (enemy.enemyArray[i] != nullptr) {
				outfile << enemy.enemyArray[i]->x << " " << enemy.enemyArray[i]->y << " " << enemy.enemyArray[i]->currentHealth << endl;
			}
			if (enemy2.enemyArray[i] != nullptr) {
				outfile << enemy2.enemyArray[i]->x << " " << enemy2.enemyArray[i]->y << " " << enemy2.enemyArray[i]->currentHealth << endl;
			}
			if (enemy3.enemyArray[i] != nullptr) {
				outfile << enemy3.enemyArray[i]->x << " " << enemy3.enemyArray[i]->y << " " << enemy3.enemyArray[i]->currentHealth << endl;
			}
			//if (enemy4.enemyArray[i] != nullptr) {
			//	outfile << enemy4.enemyArray[i]->x << " " << enemy4.enemyArray[i]->y << " " << enemy4.enemyArray[i]->currentHealth << endl;
			//}
		}

		cout << "save successfully" << endl;
		outfile.close();
		running = false;
	}

	bool load() {
		ifstream infile("player.dat", ios::binary);
		if (!infile) {
			cout << "loading error!" << endl;
			return false;
		}



	}

	void UIchoice(bool& running, bool& running1) {
		GamesEngineeringBase::Window first;
		first.create(1024, 768, "menu");
		bool menuRunning = true;
		/*GamesEngineeringBase::SoundManager soundmanager;
		GamesEngineeringBase::Sound bgm;
		soundmanager.loadMusic("bgm.wav");*/

		int offset = 300;
		int offset1 = 400;

		CObject title(offset, 75, "Resources/title0.png", NULL, NULL);
		CObject title1(offset + title.GetWidth(), 75, "Resources/title1.png", NULL, NULL);
		CObject title2(offset + title.GetWidth() + title1.GetWidth(), 75, "Resources/title2.png", NULL, NULL);

		CObject menu(offset1, 300, "Resources/menu0.png", NULL, NULL);
		CObject menu1(offset1 + menu.GetWidth(), 300, "Resources/menu1.png", NULL, NULL);
		CObject menu2(offset1 + menu.GetWidth() + menu1.GetWidth(), 300, "Resources/menu2.png", NULL, NULL);


		CObject mode(offset1, 400, "Resources/mode0.png", NULL, NULL);
		CObject mode1(offset1 + mode.GetWidth(), 400, "Resources/mode1.png", NULL, NULL);
		CObject mode2(offset1 + mode.GetWidth() + mode1.GetWidth(), 400, "Resources/mode2.png", NULL, NULL);


		CObject exit(offset1, 500, "Resources/exit0.png", NULL, NULL);
		CObject exit1(offset1 + exit.GetWidth(), 500, "Resources/exit1.png", NULL, NULL);
		CObject exit2(offset1 + exit.GetWidth() + exit1.GetWidth(), 500, "Resources/exit2.png", NULL, NULL);

		CObject egg(offset1, 600, "Resources/egg0.png", NULL, NULL);
		CObject egg1(offset1 + egg.GetWidth(), 600, "Resources/egg1.png", NULL, NULL);
		CObject egg2(offset1 + egg.GetWidth() + egg1.GetWidth(), 600, "Resources/egg2.png", NULL, NULL);


		CObject background(512, 0, "Resources/background.png", NULL, NULL);

		//soundmanager.playMusic();

		while (menuRunning) {
			first.checkInput();

			first.clear();
			background.Draw(first);

			title.Draw(first);
			title1.Draw(first);
			title2.Draw(first);

			menu.Draw(first);
			menu1.Draw(first);
			menu2.Draw(first);

			mode.Draw(first);
			mode1.Draw(first);
			mode2.Draw(first);

			exit.Draw(first);
			exit1.Draw(first);
			exit2.Draw(first);

			egg.Draw(first);
			egg1.Draw(first);
			egg2.Draw(first);

			first.present();
			if (first.keyPressed(VK_ESCAPE)) break;
			if (first.keyPressed('1')) {
				menuRunning = false;
				running = true;
			}
			if (first.keyPressed('2')) {
				menuRunning = false;
				running1 = true;
			}
		}

	}

};








int main() {
	srand(static_cast<unsigned int>(time(NULL))); // make sure number are number each time
	gameSystem sys;
	bool running = false; // To control game main loop
	bool running1 = false;
	sys.UIchoice(running, running1);
	GamesEngineeringBase::Timer timer;
	float dt = 0;
	float fps;
	// construct windows
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Survivor");

	// construct objects
	// CObject player(canvas.getWidth() / 2, canvas.getHeight() / 2, "Resources/L.png",100,0);
	int x = 0, y = 0; // position of hero

	// enemyBullet enemyShoot;
	CObject player(canvas.getWidth() / 2, canvas.getHeight() / 2, "Resources/L.png", 100, 0);
	world w("Resources/tiles.txt");
	//world w;
	// GamesEngineeringBase::Timer tim;
	bullet shoot;
	FiniteWorld finite("Resources/tiles.txt");
	tileSet tiles;
	tiles.Load();
	AoeAttack aoe;
	Enemy enemy(x, y);
	Enemy2 enemy2(x, y);
	Enemy3 enemy3(x, y);
	Enemy4 enemy4(x, y);
	GamesEngineeringBase::SoundManager bgm;
	// bgm.loadMusic();
	int count = 0;
	float time = 0;
	// game runniung
	while (running) {
		levelup(currentLevel, score);
		// variables needs to be updated each frame



		// Functions implementation
		// check input
		canvas.checkInput();
		// clear windows for next frame
		canvas.clear();




		float dt = timer.dt();
		time += dt;
		const float maxDt = 0.04f;  // Maximum allowable delta time
		if (dt > maxDt) dt = maxDt;

		fps = (1.f / dt);

		// int move = static_cast<int>((500.f * dt));
		// move function implementation
		bool alpha = false;
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('W')) y -= 2;
		if (canvas.keyPressed('S')) y += 2;
		if (canvas.keyPressed('A')) x -= 2;
		if (canvas.keyPressed('D')) x += 2;
		if (canvas.keyPressed('E')) {
			if (enemy.enemyArray != nullptr && enemy.currentHealth != NULL) {
				aoe.Aoe(enemy, aoeDamage, dt);
				cout << "Comfirmed Kill" << endl;
			}
		}
		if (canvas.keyPressed('Q')) alpha = !alpha;
		if (canvas.keyPressed('I')) {
			sys.save(player, enemy, enemy2, enemy3, enemy4, running);
		}
		if (canvas.keyPressed('O')) {
			sys.load();

		}


		//if (canvas.keyPressed('W')) player.Update(0,2);
		//if (canvas.keyPressed('S')) player.Update(0, -2);
		//if (canvas.keyPressed('A')) player.Update(-2, 0);
		//if (canvas.keyPressed('D')) player.Update(2, 0);
		// Hero Creation

		// player.Update(canvas, x, y);


		// Enemy Creation

		// Weapon Creation



		// Draw canvas
		//for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++) {
		//	for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++) {
		//		canvas.draw(tempx, tempy, 0, 0, 255);
		//	}
		//}

			////GamesEngineeringBase::Window& canvas, CObject& player, unsigned worldX, unsigned worldY
		if (alpha) {
			w.drawAlpha(canvas, x, y);
		}
		else {
			w.draw(canvas, player, x, y);
		}
		// cout << "player x" << player.GetX() << endl;
		w.Tilecollider(player, x, y);

		int mapOffsetX = x; // The x position of the map based on player input
		int mapOffsetY = y; // The y position of the map based on player input

		enemy.Update(canvas, player, shoot, dt, "Resources/slime0.png");
		enemy2.Update(canvas, player, shoot, dt, "Resources/slimeGreen.png");
		enemy3.Update(canvas, player, shoot, dt, "Resources/slimeRed.png");


		/*
		enemy.Update(canvas, player, shoot, dt, "Resources/slime0.png",  -mapOffsetX, -mapOffsetY);
		enemy2.Update(canvas, player, shoot, dt, "Resources/slimeGreen.png",  -mapOffsetX, -mapOffsetY);
		enemy3.Update(canvas, player, shoot, dt, "Resources/slimeRed.png", - mapOffsetX, -mapOffsetY);
*/






//enemy4.Update(canvas, player, shoot, dt, "Resources/L4.png");
 //enemy.Collision(player);
//if (enemy4.currentSize > 0) {
	//enemyShoot.Update(canvas, enemy4, player, dt);
//}


		shoot.Update(canvas, enemy, enemy2, enemy3, enemy4, player, dt);
		// player.CheckPlayer(running, enemy);
		player.Draw(canvas);
		// cout << "player current health" << player.currentHealth << endl;
		//if (count == 0) {
		//	player.testdecreaseHealth();
		//	count = 1;
		//}

		player.DrawHealth(canvas);
		//
		enemy.Draw(canvas);
		enemy2.Draw(canvas);
		enemy3.Draw(canvas);

		//enemy.Draw(canvas, -mapOffsetX, -mapOffsetY);
		//enemy2.Draw(canvas, -mapOffsetX, -mapOffsetY);
		//enemy3.Draw(canvas, -mapOffsetX, -mapOffsetY);




		//enemy4.Draw(canvas);
		// enemy.DrawHealth(canvas);
		shoot.Draw(canvas);
		//enemyShoot.Draw(canvas);
	// 	cout << "score is: " << score << endl;
		// w.collision(canvas, player, x, y);

		//w.CheckCollidor(player, x, y);
		// Display

		// w.collision(canvas, player, x, y);
		player.gameOver(running);


		// show other essential data for player:
		//cout << "fps: " << fps << endl;
		//cout << "Your score" << score << endl;
		//cout << "Time survived" << time << endl;
		//if (aoe.timeElapsed == 0) {
		//	cout << "AOE READY" << endl;
		//}

		// w.collisiton(canvas, player);
		//player.draw(canvas);

		// Frame display
		canvas.present();
	}

	while (running1) {
		levelup(currentLevel, score);
		// variables needs to be updated each frame



		// Functions implementation
		// check input
		canvas.checkInput();
		// clear windows for next frame
		canvas.clear();


		//float dt = tim.dt();
		float dt = 0.04f;
		// int move = static_cast<int>((500.f * dt));
		// move function implementation
		bool alpha = false;
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('W')) y -= 2;
		if (canvas.keyPressed('S')) y += 2;
		if (canvas.keyPressed('A')) x -= 2;
		if (canvas.keyPressed('D')) x += 2;
		if (canvas.keyPressed('E')) {
			if (enemy.enemyArray != nullptr && enemy.currentHealth != NULL) {
				aoe.Aoe(enemy, aoeDamage, dt);
			}
		}
		if (canvas.keyPressed('Q')) alpha = !alpha;
		if (canvas.keyPressed('I')) {
			sys.save(player, enemy, enemy2, enemy3, enemy4, running);
		}
		if (canvas.keyPressed('O')) {
			sys.load();

		}


		//if (canvas.keyPressed('W')) player.Update(0,2);
		//if (canvas.keyPressed('S')) player.Update(0, -2);
		//if (canvas.keyPressed('A')) player.Update(-2, 0);
		//if (canvas.keyPressed('D')) player.Update(2, 0);
		// Hero Creation

		// player.Update(canvas, x, y);


		// Enemy Creation

		// Weapon Creation



		// Draw canvas
		//for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++) {
		//	for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++) {
		//		canvas.draw(tempx, tempy, 0, 0, 255);
		//	}
		//}

			////GamesEngineeringBase::Window& canvas, CObject& player, unsigned worldX, unsigned worldY
		if (alpha) {
			finite.drawAlpha(canvas, x, y);
		}
		else {
			finite.draw(canvas, player, x, y);
		}
		// cout << "player x" << player.GetX() << endl;
		// finite.Tilecollider(player, x, y);

		int mapOffsetX = x; // The x position of the map based on player input
		int mapOffsetY = y; // The y position of the map based on player input

		enemy.Update(canvas, player, shoot, dt, "Resources/slime0.png");
		enemy2.Update(canvas, player, shoot, dt, "Resources/slimeGreen.png");
		enemy3.Update(canvas, player, shoot, dt, "Resources/slimeRed.png");


		/*
		enemy.Update(canvas, player, shoot, dt, "Resources/slime0.png",  -mapOffsetX, -mapOffsetY);
		enemy2.Update(canvas, player, shoot, dt, "Resources/slimeGreen.png",  -mapOffsetX, -mapOffsetY);
		enemy3.Update(canvas, player, shoot, dt, "Resources/slimeRed.png", - mapOffsetX, -mapOffsetY);
*/






//enemy4.Update(canvas, player, shoot, dt, "Resources/L4.png");
 //enemy.Collision(player);
//if (enemy4.currentSize > 0) {
	//enemyShoot.Update(canvas, enemy4, player, dt);
//}


		shoot.Update(canvas, enemy, enemy2, enemy3, enemy4, player, dt);
		// player.CheckPlayer(running, enemy);
		player.Draw(canvas);


		player.DrawHealth(canvas);
		//
		enemy.Draw(canvas);
		enemy2.Draw(canvas);
		enemy3.Draw(canvas);

		shoot.Draw(canvas);

		player.gameOver(running);
		// Frame display
		canvas.present();
	}
	return 0;
}