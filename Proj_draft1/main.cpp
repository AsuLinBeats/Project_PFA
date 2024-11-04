#include<iostream>
#include<fstream> // for file handling
#include<cmath>
#include"GamesEngineeringBase.h" // for main function building
using namespace std;
// Declaration: The naming convention followed by Microsoft rules.


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
						if(sprite.alphaAt(i,j) > 200)
							canvas.draw(x + i, y + j, sprite.at(i,j));
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

	void virtual Update(GamesEngineeringBase::Window &canvas,int _x, int _y) {
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






















class CCharacter : public CObject {
public:
	int _maxblood = 100;
	GamesEngineeringBase::Image sprite;
	CCharacter(int _x, int _y, string filename) : CObject(_x, _y, filename){
		// 
		y = y - sprite.height / 2;
	}
	void Update(int _x, int _y) override {
		x += _x;
		y += _y;

	}
};

const unsigned int maxSize1 = 10000;

class Enemy{ //: public CObject {
	CObject* enemyArray[maxSize1];
	unsigned int currentSize = 0;
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 2.f; // the time to next enemy creation
	int px = 200;
	int py = 200;
	int offset=200;

	void Random(GamesEngineeringBase::Window& canvas, int _offset) {
		offset = _offset;
		int side = rand() % 4;
		switch (side) {
		case 0:
			// Generate enemy from top
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

	void GenerateEnemy(GamesEngineeringBase::Window& canvas, float dt) {
		Random(canvas, 150);
		timeElapsed += dt;
		if (currentSize < maxSize1) {
			if (timeElapsed > timeThreshold) {
				CObject* newEnemy = new CObject(px, py, "Resources/L2.png");
				cout << "Enemy created: " << currentSize << endl;
				// Save address of new enemy to array
				enemyArray[currentSize++] = newEnemy;
				// reset generation parameter
				timeElapsed = 0.f;
				timeThreshold -= 0.2f;
				// difficulty control
				timeThreshold = max(0.2f, timeThreshold);
			}
		}
		else {
			cout << "Last Enemy!!!" << endl;
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

	void CheckDeletedEnemy(GamesEngineeringBase::Window& canvas, unsigned int i) {
		if (i >= maxSize1 || enemyArray[i] == nullptr) return;
		if (isOutBound(enemyArray[i]->GetX(), enemyArray[i]->GetY(),canvas,250)) {
			CObject* enemyDelete = enemyArray[i];
			enemyArray[i] = nullptr;
			delete enemyDelete;
			cout << "destroyed " << i << endl;
		}
	}



public:
	Enemy() { };


	void Update(GamesEngineeringBase::Window& canvas,CObject& player,float dt) {
		
		 GenerateEnemy(canvas, dt);
		// cout << "After generate enemy running!" << endl;
		  // define speed
		int speed = static_cast<int>((70.0f * dt));

		for (unsigned int i = 0; i < currentSize; i++) {
			if (enemyArray[i] != nullptr) {
				// calculate distance between player and enemy
				float dx = player.GetX() - enemyArray[i]->GetX();
				float dy = player.GetY() - enemyArray[i]->GetY();
				float distance = sqrtf(dx * dx + dy * dy);
				// add check to avoid devided by 0
				if (distance > 0.0f) {
					int moveX = static_cast<int>((dx / distance) * speed);
					int moveY = static_cast<int>((dy / distance) * speed);
					enemyArray[i]->Update(moveX, moveY);
					CheckDeletedEnemy(canvas, i);
				}
			}
		}
	}

	void Draw(GamesEngineeringBase::Window& canvas) {
		for (unsigned int i = 0; i < currentSize; i++) {
			if (enemyArray[i] != nullptr)
				enemyArray[i]->Draw(canvas);
		}
	}

	bool Collision(CObject& player) {
		for (unsigned int i = 0; i < currentSize; i++) {
			if (enemyArray[i] != nullptr && enemyArray[i]->CircleCollidor(player)) {
				cout << "crash: " << i << endl;
				return true;
			}
		}
		return false;
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
	// unsigned int* map;
	unsigned int size;
	unsigned int map[maxSizeX][maxSizeY];

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
	//~world() {
	//	delete[] map;
	//}//int worldX, int worldY
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
	int x = 0, y = 0; // position of hero
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

		w.draw(canvas, x, y);


		// Display
		// enemy.Draw(canvas);
		player.Draw(canvas);
		//player.draw(canvas);

		// Frame display
		canvas.present();
	}
	return 0;
}
