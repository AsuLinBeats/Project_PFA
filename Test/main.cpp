
#include<iostream>
#include<fstream>
#include"GamesEngineeringBase.h"

using namespace std;

int score = 0;

class Camera {
private:
	int offsetX, offsetY; // Offset of the camera
	int screenWidth, screenHeight;
	GamesEngineeringBase::Window canvas;
public:
	// sync camera with screen
	Camera(int width, int height) : screenWidth(width), screenHeight(height), offsetX(0), offsetY(0) {}

	// Update the camera position based on the player’s position
	void Update(int x, int y, int width, int height) {
		// Center the camera
		offsetX = x - screenWidth / 2 + width / 2;
		offsetY = y - screenHeight / 2 + height / 2;
	}

	int getOffsetX() const { return offsetX; }
	int getOffsetY() const { return offsetY; }
};


void DrawCircle(GamesEngineeringBase::Window& canvas, int cx, int cy, int r) {
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

		DrawCircle(canvas, x + sprite.width / 2, y + sprite.height / 2, sprite.width / 3);
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

	void virtual Update(GamesEngineeringBase::Window& canvas, int _x, int _y, int _px, int _py) {
		// Define padding on all sides (adjust as needed)
		int paddingX = _px;  // Space on the left and right sides
		int paddingY = _py;  // Space on the top and bottom sides

		// Horizontal movement within boundaries
		if (x + _x > paddingX && x + _x + sprite.width < canvas.getWidth() - paddingX) {
			x += _x;
		}

		// Vertical movement within boundaries
		if (y + _y > paddingY && y + _y + sprite.height < canvas.getHeight() - paddingY) {
			y += _y;
		}

		// use boundary to limit move
		if (x < paddingX) x = paddingX;
		if (y < paddingY) y = paddingY;
		if (x + sprite.width > canvas.getWidth() - paddingX) x = canvas.getWidth() - sprite.width - paddingX;
		if (y + sprite.height > canvas.getHeight() - paddingY) y = canvas.getHeight() - sprite.height - paddingY;
	}


	void UpdateWithTilemap(int _x, int _y, int tilemapOffsetX, int tilemapOffsetY) {
		// Update position with both direct movement and tilemap offset
		x += _x - tilemapOffsetX;
		y += _y - tilemapOffsetY;
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
	void SetX(int _x) {
		x = _x;
	}	
	void SetY(int _y) {
		x = _y;
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
	// for canmera only
	void Draw(GamesEngineeringBase::Window& canvas, const Camera& camera) {
		int drawX = x - camera.getOffsetX();
		int drawY = y - camera.getOffsetY();

		// Only draw if within canvas boundaries
		if (drawX + sprite.width > 0 && drawX < canvas.getWidth() &&
			drawY + sprite.height > 0 && drawY < canvas.getHeight()) {

			for (unsigned int i = 0; i < sprite.width; i++) {
				if (drawX + i > 0 && drawX + i < canvas.getWidth()) {
					for (unsigned int j = 0; j < sprite.height; j++) {
						if (drawY + j > 0 && drawY + j < canvas.getHeight()) {
							if (sprite.alphaAt(i, j) > 200)
								canvas.draw(drawX + i, drawY + j, sprite.at(i, j));
						}
					}
				}
			}
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

public:

	world() {
		// Pure random, which is not implemented in game loop
		size = maxSizeX;
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
		// cout << "loading completed" << endl;
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

					// Check for collision using the tile's properties (e.g., if it's water)
					if (tiles[tileIndex].isWater(tileIndex)) {
						//cout << "Collision detected with water tile at (" << i << ", " << j << ")" << std::endl;
						return true;
					}
				}
			}
		}
		return false;
	}
};


class FiniteWorld : public world{
	tileSet tiles;
	tileSet alphas;
	unsigned int sizeX = 42;  // Define the width of the world
	unsigned int sizeY = 42;   // Define the height of the world
	unsigned int map[maxSizeX][maxSizeY];  // Map array for tiles
	bool isWater[maxSizeX][maxSizeY];  // Water detection array

public:
	FiniteWorld(std::string filename) {
		tiles.Load();
		alphas.Load("alpha");

		std::ifstream infile(filename);
		if (!infile.is_open()) {
			std::cout << "Error opening file: " << filename << std::endl;
			return;
		}

		int i = 0, j = 0;
		char ch;
		int num = 0;
		bool readingNumber = false;
		std::cout << "map is loading..." << std::endl;

		// Load map from file
		while (infile.get(ch)) {
			if (ch >= '0' && ch <= '9') {
				num = num * 10 + (ch - '0');
				readingNumber = true;
			}
			if (ch == ',' || ch == '\n') {
				if (readingNumber) {
					if (i < maxSizeX && j < maxSizeY) {
						map[j][i] = num;
						j++;
						if (j >= 42) { // Move to the next row if column limit is reached
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

			if (map[i][j] >= 14 && map[i][j] <= 22) {
				isWater[i][j] = true;
			}
			else {
				isWater[i][j] = false;
			}
		}
	}

	void draw(GamesEngineeringBase::Window& canvas, CObject& player, int wx, int wy) {
		int height = tiles[0].GetHeight();
		int width = tiles[0].GetWidth();

		int tileSize = 32;
		int X = wx / width;
		int Y = wy / height;

		// Draw finite map without wrapping
		for (int i = 0; i < canvas.getWidth() / width; i++) {
			for (int j = 0; j < canvas.getHeight() / height; j++) {
				int mapX = X + i;
				int mapY = Y + j;

				// Check if within bounds of the finite map
				if (mapX >= 0 && mapX < 42 && mapY >= 0 && mapY < 42) {
					tiles[map[mapY][mapX]].Draw(canvas, i * tileSize, j * tileSize);
				}
			}
		}
	}

	void drawAlpha(GamesEngineeringBase::Window& canvas, int wx, int wy) {
		// want to add finite invincibility time when trigged
		int height = tiles[0].GetHeight();
		int width = tiles[0].GetWidth();

		int tileSize = 32;
		int startX = wx / width;
		int startY = wy / height;

		for (int i = 0; i < canvas.getWidth() / width; i++) {
			for (int j = 0; j < canvas.getHeight() / height; j++) {
				int mapX = startX + i;
				int mapY = startY + j;

				// Draw only within bounds
				if (mapX >= 0 && mapX < 42 && mapY >= 0 && mapY < 42) {
					alphas[map[mapY][mapX]].Draw(canvas, i * tileSize, j * tileSize);
				}
			}
		}
	}

	bool TileCollider(CObject& player, int x, int y) {
		int tileWidth = 32;
		int tileHeight = 32;

		int playerTileX = x / tileWidth;
		int playerTileY = y / tileHeight;
		int endX = (x + player.GetWidth()) / tileWidth;
		int endY = (y + player.GetHeight()) / tileHeight;

		for (int i = playerTileX; i <= endX; i++) {
			for (int j = playerTileY; j <= endY; j++) {
				if (i >= 0 && i < 42 && j >= 0 && j < 42) {
					int tileIndex = map[j][i];
					int tilePosX = i * tileWidth;
					int tilePosY = j * tileHeight;

					if (tiles[tileIndex].isWater(tileIndex)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	void limitMove(int& px, int& py) {
		if (px <= -480) {
			px = -480;
		}
		if (px >= 480) {
			px = 480;
		}
		if (py < -410) {
			py = -410;
		}
		if (py >= 860) {
			py = 860;
		}
		// I forgot add - initially, and it will "teleport" player to other side of map, which has a fake infinity, interesting and can be used for some skills
	}
};

const unsigned int maxSize1 = 1000;
class Enemy : public CObject { //: public CObject {
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 2.f; // the time to next enemy creation

	float attackElapsed = 0.f; // time since last attack
	float attackThreshold = 2.f; // the time to next attack

	int offset = 200;
	


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


protected:
	int maxHealth = 20;
	int attack = 10;
public:
	int currentHealth;
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


	virtual void GenerateEnemy(GamesEngineeringBase::Window& canvas, float dt, string filename) {
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

	virtual void Update(GamesEngineeringBase::Window& canvas, CObject& player, CObject& bullet, float dt, string filename, bool up, bool down, bool left, bool right) {

		GenerateEnemy(canvas, dt, filename);
		  // define speed
		int speed = static_cast<int>((150.0f * dt));

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
					int scale = 1;
					if (left) {
						enemyArray[i]->Update(scale, 0);
					}
					if (up) {
						enemyArray[i]->Update(0, scale);
					}
					if (right) {
						enemyArray[i]->Update(-scale, 0);
					}
					if (down) {
						enemyArray[i]->Update(0, -scale);
					}

					if (enemyArray[i]->currentHealth <= 0) {

						// if crush, delete immediately
						CObject* enemyDelete = enemyArray[i];
						enemyArray[i] = nullptr;
						delete enemyDelete;
						kills++;
						score += award;
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
};

class Enemy2 :public Enemy {
public:
	Enemy2(int _x, int _y) : Enemy(_x, _y) {
		maxHealth = 50;     
		attack = 20;         
		currentHealth = maxHealth;
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
	float timeThreshold = 3.f; // the time to next enemy creation
	int offset = 200;
	int award = 30;
};

class Enemy3 : public Enemy {
public:
	Enemy3(int _x, int _y) : Enemy(_x, _y) {
		maxHealth = 70;
		attack = 25;
		currentHealth = maxHealth;
	};

	GamesEngineeringBase::Image sprite;
	CObject* enemyArray[30];
	unsigned int currentSize = 0;
	int px = 200;
	int py = 200;
	int x = 0;
	int y = 0;
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 4.f; // the time to next enemy creation
	int offset = 200;
	int award = 50;
};


class Enemy4 : public Enemy {
public:
	Enemy4(int _x, int _y) : Enemy(_x, _y) {
		maxHealth = 10;
		attack = 10;
		currentHealth = maxHealth;
	}

	float timeElapsed = 0.f;
	float timeThreshold = 3.f; // time between enemy creations
	int award = 40;
	float attackElapsed = 0.f;
	float attackThreshold = 1.f;
	int currentSize2 = 0;
	int maxSize2 = 30;

	void GenerateEnemy(GamesEngineeringBase::Window& canvas, float dt, string filename) override {
		timeElapsed += dt;

		if (currentSize2 < maxSize2) {
			cout << "555555555555555555555555" << endl;
			if (timeElapsed > timeThreshold) {

				// Create a stationary enemy at (px, py)
				CObject* newEnemy = new CObject(px, py, filename, maxHealth, attack);
				cout << " 777777777777777777777" << currentSize2 << endl;

				// Save address of new enemy to array
				enemyArray[currentSize2++] = newEnemy;

				// Reset generation parameters
				timeElapsed = 0.f;
				timeThreshold -= 0.02f;

				// Difficulty control
				timeThreshold = max(0.9f, timeThreshold);
			}
		}
		else {
			cout << "Last Enemy!!!" << endl;
		}
	}

	void Update(GamesEngineeringBase::Window& canvas, CObject& player, CObject& bullet, float dt, string filename, bool up, bool down, bool left, bool right) override {
		GenerateEnemy(canvas, dt, filename);

		for (unsigned int i = 0; i < currentSize2; i++) {
			if (enemyArray[i] != nullptr) {
				// No need for movement code; leave the enemy at its original position
				int scale = 1;
				if (left) {
					enemyArray[i]->Update(scale, 0);
				}
				if (up) {
					enemyArray[i]->Update(0, scale);
				}
				if (right) {
					enemyArray[i]->Update(-scale, 0);
				}
				if (down) {
					enemyArray[i]->Update(0, -scale);

					if (enemyArray[i]->currentHealth <= 0) {
						// If the enemy is defeated, delete it
						CObject* enemyDelete = enemyArray[i];
						enemyArray[i] = nullptr;
						delete enemyDelete;
						kills++;
						score += award;
					}
					else if (enemyArray[i]->CircleCollidor(player, 1)) {
						// If the player collides with the enemy, deal damage
						attackElapsed += dt;
						if (attackElapsed > attackThreshold) {
							player.decreaseHealth(attack);
							attackElapsed = 0.f;
						}
					}
				}
			}
		}
	}
};

int level[5] = { 1,2,3,4,5 };
int weaponLevel = 1;
int maxBullet = weaponLevel;
int const numberBullets = 1000;

class AoeAttack : public CObject {
public:
	float timeElapsed = 0.f;
	float timeThreshold = 4.f; // the time to next available attack

	void Aoe(Enemy& enemy, int damage, int dt) {
		timeElapsed += dt;
		// define empty array for enemy and their blood
		CObject* targetEnemies[3] = { nullptr, nullptr, nullptr }; // pointer to each enemy
		int targetHealth[3] = { 0,0,0 };
		// target enemy
		if (enemy.currentSize >= 3) {
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
	}
};

class bullet : public CObject {
protected:
	unsigned int currentNumber = 0;
public:
	int attack = 30;
	float timeElapsed = 0.f; // time since last bullet
	float timeThreshold = 2.f; // the time to next bullet generation
	bool isCollision;
	CObject* bullets[numberBullets];
	
	bullet() {}
	// bullet targeted to enemy
	void GenerateBullet(GamesEngineeringBase::Window& canvas, CObject& player, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4, float dt) {
		// the number of bullet targeted to enemy depends on weaponLevel

		timeElapsed += dt;
		if (currentNumber < numberBullets) {

			if (timeElapsed > timeThreshold) {
				CObject* closestEnemy = FindClosestEnemy(canvas, player, enemy, enemy2, enemy3, enemy4);

				// loop from existing enemy to find closest one;
				if (closestEnemy != nullptr) {
					// create new bullet start from player's position
					CObject* newBullet = new CObject(player.GetX() + player.GetWidth() / 2, player.GetY() + player.GetHeight() / 2, "Resources/bullet1.png", 0, 20);
					bullets[currentNumber++] = newBullet;
					timeElapsed = 0.f;
					timeThreshold -= 0.1f; // generate bullets more frequent as level increases;
					timeThreshold = max(1.f, timeThreshold); // set maximum frequency
					
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
					}
				}

			}
		}
		return closestEnemy;
	}


	void Update(GamesEngineeringBase::Window& canvas, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4, CObject& player, float dt) {
		// make bullet fly to enemy

		GenerateBullet(canvas, player, enemy, enemy2, enemy3, enemy4, dt);
		
		int speed = 170.0f * dt;

		for (unsigned int i = 0; i < currentNumber; i++) {
			if (bullets[i] != nullptr) {
				// Find the closest enemy for each bullet movement update
				CObject* closestEnemy = FindClosestEnemy(canvas, player, enemy, enemy2, enemy3, enemy4);
		
				if (closestEnemy != nullptr) {
					float dx = closestEnemy->GetX() - bullets[i]->GetX() + 25;
					float dy = closestEnemy->GetY() - bullets[i]->GetY() + 50;
					float distance = sqrtf(dx * dx + dy * dy);

					if (distance > 0.0f) {

						int moveX = static_cast<int>((dx / distance) * speed);
						int moveY = static_cast<int>((dy / distance) * speed);
						bullets[i]->Update(moveX, moveY);
						isCollision = bullets[i]->CircleCollidor(*closestEnemy, 0);
						
						if (isCollision || closestEnemy == nullptr) {	
							// If a collision is detected, delete 

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

class enemyBullet : public bullet {
public:
	int currentNumber = 0;
	void GenerateBullet(GamesEngineeringBase::Window& canvas, CObject& player, Enemy4& enemy, float dt) {
		// the number of bullet targeted to enemy depends on weaponLevel
		timeElapsed += dt;
		if (currentNumber < numberBullets) {

			if (timeElapsed > timeThreshold) {
				
					CObject* newBullet = new CObject(enemy.px, enemy.py / 2,"Resources/bullet2.png",1,10);
					bullets[currentNumber++] = newBullet;
					timeElapsed = 0.f;
					timeThreshold = 2; // generate bullets more frequent as level increases;
			}
		}
	}

	void Update(GamesEngineeringBase::Window& canvas, Enemy4& enemy, CObject& player, float dt) {
		// make bullet fly to enemy
		GenerateBullet(canvas, player, enemy, dt);
		int speed = 160.f * dt;
		for (unsigned int i = 0; i < currentNumber; i++) {
			if (bullets[i] != nullptr) {

					float dx = player.GetX() - bullets[i]->GetX() + 25;
					float dy = player.GetY() - bullets[i]->GetY() + 50;
					float distance = sqrtf(dx * dx + dy * dy);

					if (distance > 0.0f) {

						int moveX = static_cast<int>((dx / distance) * speed);
						int moveY = static_cast<int>((dy / distance) * speed);
						bullets[i]->Update(moveX, moveY);

						if (bullets[i]->CircleCollidor(player, 0)) {
							// If a collision is detected, delete this specific enemy
							CObject* bulletDelete = bullets[i];
							bullets[i] = nullptr;
							delete bulletDelete;
							player.decreaseHealth(attack);
						}
					}
			
			}
		}
	}

};

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

int aoeDamage = 20 * currentLevel;

class gameSystem {

public: 
	
	bool menuRunning = false;
	void save(CObject& player, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4, bool& running) {
	//ofstream outfile("player.txt");
	ofstream outfile("player.dat", ios::binary);
	if (!outfile) {
		cout << "saving error!" << endl;
	}
		outfile << "global variables:" << endl;
		outfile << currentLevel << " " << score << " " << endl;

		outfile << "player:" << endl;
		outfile << player.GetX() << " " << player.GetY() << " " << player.currentHealth << endl;

		outfile << "Enemy: " << endl;
		outfile << enemy.currentSize << endl;
	// save each enemy alive separately 
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
		if (enemy4.enemyArray[i] != nullptr) {
			outfile << enemy4.enemyArray[i]->x << " " << enemy4.enemyArray[i]->y << " " << enemy4.enemyArray[i]->currentHealth << endl;
		}
	}

	cout << "save successfully" << endl;
	outfile.close();
	running = false;
}

	void load(CObject& player, Enemy& enemy, Enemy2& enemy2, Enemy3& enemy3, Enemy4& enemy4, bool& running) {
		ifstream infile("player.dat",ios::binary);
		if (!infile) {
			cout << "loading error!" << endl;
			return;
		}
		string label;
		// Skip marker
		infile >> label;
		if (label != "global") infile.ignore(1000, '\n');
		// Read global variables
		infile >> currentLevel >> score;

		// Skip marker
		infile >> label;
		if (label != "player:") infile.ignore(1000, '\n');
		// Read player data
		float playerX, playerY;
		int playerHealth;
		infile >> playerX >> playerY >> playerHealth;
		player.SetX(playerX);
		player.SetY(playerY);
		player.currentHealth = playerHealth;

		// Skip marker
		infile >> label;
		if (label != "Enemy:") infile.ignore(1000, '\n');

		// Read enemy data
		infile >> enemy.currentSize;
		// Load each enemy's data
		for (unsigned int i = 0; i < enemy.currentSize; i++) {
			float enemyX, enemyY;
			int enemyHealth;
			if (infile >> enemyX >> enemyY >> enemyHealth) {
				enemy.enemyArray[i] = new CObject(enemyX, enemyY, "Resources/slime0.png",20,10);
				enemy.enemyArray[i]->currentHealth = enemyHealth;
			}
			if (infile >> enemyX >> enemyY >> enemyHealth) {
				enemy2.enemyArray[i] = new CObject(enemyX, enemyY,"Resources/slimeGreen.png", 50, 20);
				enemy2.enemyArray[i]->currentHealth = enemyHealth;
			}
			if (infile >> enemyX >> enemyY >> enemyHealth) {
				enemy3.enemyArray[i] = new CObject(enemyX, enemyY,"Resources/slimeRed.png", 70, 25);
				enemy3.enemyArray[i]->currentHealth = enemyHealth;
			}
			if (infile >> enemyX >> enemyY >> enemyHealth) {
				enemy4.enemyArray[i] = new CObject(enemyX, enemyY,"Resources/enemy4_0.png", 20, 10);
				enemy4.enemyArray[i]->currentHealth = enemyHealth;
			}
		}
		cout << "load successfully" << endl;
		infile.close();
		running = true;
	}


	void UIchoice(bool& running, bool& running1, bool& loading) {
		GamesEngineeringBase::Window first;
		first.create(1024, 768, "menu");
		menuRunning = true;
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

			if (first.keyPressed('o')) {
				menuRunning = false;
				loading = true;
				
			}
		}

	}

};


int main() {
	// system and menu
	srand(static_cast<unsigned int>(time(NULL))); // make sure number are number each time
	gameSystem sys;
	// game loops
	bool loading = false;
	bool running = false; 
	bool running1 = false;
	sys.UIchoice(running, running1, loading);
	GamesEngineeringBase::Timer timer;
	float fps;

	// game play setting
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Survivor");

	// construct objects
	int x = 0, y = 0; // position of hero

	enemyBullet enemyShoot;
	CObject player(canvas.getWidth() / 2, canvas.getHeight() / 2, "Resources/player1.png", 200, 0);
	Camera camera(canvas.getWidth(), canvas.getHeight());
	world w("Resources/tiles.txt");

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
	if (loading) {
		sys.load(player, enemy, enemy2, enemy3, enemy4, running);
	}
	// bgm.loadMusic();
	int count = 0;
	float time = 0;

	// game runniung
	while (running) {
		float dt = timer.dt();
		time += dt;

		fps = (1.f / dt);
		levelup(currentLevel, score);

		camera.Update(player.GetX(), player.GetY()-50, player.GetWidth(), player.GetHeight());

		// check input
		canvas.checkInput();
		// clear windows for next frame
		canvas.clear();
		// introduce bools to control the enemy's moving while player is moving
		bool alpha = false;
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('W')) {
			y -= 2;
			up = true;
			
		} 
		if (canvas.keyPressed('S')) {
			y += 2;
			down = true;
		} 
		if (canvas.keyPressed('A')) {
			x -= 2;
			left = true;
		} 
		if (canvas.keyPressed('D')) {
			x += 2;
			right = true;
		}

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

		if (alpha) {
			w.drawAlpha(canvas, x, y);
		}
		else {
			w.draw(canvas, player, x, y);
		}

		w.Tilecollider(player, x, y);

		enemy.Update(canvas, player, shoot, dt, "Resources/slime0.png", up, down, left, right);
		enemy2.Update(canvas, player, shoot, dt, "Resources/slimeGreen.png", up, down, left, right);
		enemy3.Update(canvas, player, shoot, dt, "Resources/slimeRed.png", up, down, left, right);
		enemy4.Update(canvas, player, shoot, dt, "Resources/enemy4_0.png", up, down, left, right);

		shoot.Update(canvas, enemy, enemy2, enemy3, enemy4, player, dt);
		player.Draw(canvas,camera);
		player.DrawHealth(canvas);

		enemy.Draw(canvas);
		enemy2.Draw(canvas);
		enemy3.Draw(canvas);
		enemy4.Draw(canvas);

		if (enemy4.currentSize > 0) {
			enemyShoot.Update(canvas, enemy4, player, dt);
			enemyShoot.Draw(canvas);
		}

		shoot.Draw(canvas);
		player.gameOver(running);

		 //show other essential data for player:
		cout << "fps: " << fps << endl;
		 cout << "Your score" << score << endl;
		cout << "Time survived" << time << endl;
		if (aoe.timeElapsed == 0) {
			 cout << "AOE READY" << endl;
		}

		// Frame display
		canvas.present();
	}

	while (running1) {
		float dt = timer.dt();
		time += dt;

		fps = (1.f / dt);
		levelup(currentLevel, score);

		camera.Update(player.GetX(), player.GetY() - 50, player.GetWidth(), player.GetHeight());

		// check input
		canvas.checkInput();
		// clear windows for next frame
		canvas.clear();
		// introduce bools to control the enemy's moving while player is moving
		bool alpha = false;
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('W')) {
			y -= 2;
			up = true;

		}
		if (canvas.keyPressed('S')) {
			y += 2;
			down = true;
		}
		if (canvas.keyPressed('A')) {
			x -= 2;
			left = true;
		}
		if (canvas.keyPressed('D')) {
			x += 2;
			right = true;
		}
		finite.limitMove(x, y);
		cout << "x is " << x << endl;
		cout << "y is" << y << endl;
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

		if (alpha) {
			finite.drawAlpha(canvas, x, y);
		}
		else {
			finite.draw(canvas, player, x, y);
		}

		finite.Tilecollider(player, x, y);

		enemy.Update(canvas, player, shoot, dt, "Resources/slime0.png", up, down, left, right);
		enemy2.Update(canvas, player, shoot, dt, "Resources/slimeGreen.png", up, down, left, right);
		enemy3.Update(canvas, player, shoot, dt, "Resources/slimeRed.png", up, down, left, right);
		enemy4.Update(canvas, player, shoot, dt, "Resources/enemy4_0.png", up, down, left, right);

		shoot.Update(canvas, enemy, enemy2, enemy3, enemy4, player, dt);
		player.Draw(canvas, camera);
		player.DrawHealth(canvas);

		enemy.Draw(canvas);
		enemy2.Draw(canvas);
		enemy3.Draw(canvas);
		enemy4.Draw(canvas);

		if (enemy4.currentSize > 0) {
			enemyShoot.Update(canvas, enemy4, player, dt);
			enemyShoot.Draw(canvas);
		}

		shoot.Draw(canvas);
		player.gameOver(running);

		//show other essential data for player:
		cout << "fps: " << fps << endl;
		cout << "Your score" << score << endl;
		cout << "Time survived" << time << endl;
		if (aoe.timeElapsed == 0) {
			cout << "AOE READY" << endl;
		}

		// Frame display
		canvas.present();
	}
	return 0;
}