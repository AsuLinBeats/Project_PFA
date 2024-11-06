#include<iostream>
#include<fstream>
#include"GamesEngineeringBase.h"
using namespace std;

//int* StringToArray(string s, int * array) {
//	int index = 0;
//	int currentNumber = 0;
//	bool isNumber = false;
//
//	for (unsigned int i = 0; s[i] != '\0'; i++) {
//		if (s[i] >= '0' && s[i] <= '9') {
//			// Transfer string to number
//			currentNumber = currentNumber * 10 + (s[i] - '0');
//			isNumber = true;
//		}
//		else if (s[i] == ',' && isNumber) {
//			// case when meeting ,
//			array[index++] = currentNumber;
//			currentNumber = 0;
//			isNumber = false;
//		}
//
//	}
//
//}

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

//void drawBox(GamesEngineeringBase::Window& canvas, int cx, int cy, int r) {
//	int r2 = r * r;
//	for (int x = -r; x < r + 1; x++) {
//		int y = sqrtf(r2 - (x * x));
//
//		if (cx + x > 0 && cx + x < canvas.getWidth()) {
//			if (cy + y > 0 && cy + y < canvas.getHeight())
//				canvas.draw(cx + x, cy + y, 255, 0, 0);
//			if (cy - y > 0 && cy - y < canvas.getHeight())
//				canvas.draw(cx + x, cy - y, 255, 0, 0);
//		}
//		//cout << cx + x << '\t' << cy + y << endl;
//	}
//}


class CObject
{
	// 
protected:

	GamesEngineeringBase::Image sprite;
public:
	int x, y;
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

	//void Animation(int number) {
	//	// class
	//	int currentIndex = 0;
	//	static int counter = 0;
	//	if (++counter % 5 == 0) {
	//		currentIndex++;
	//	}
	//	currentIndex = currentIndex % number; // make animation loop
	//}
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

	bool isWater() {


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


//class BoxCollider {
//public:
//	int x, y;
//	int tilesize;
//	BoxCollider(int _x, int _y, int _tilesize) {
//		x = _x;
//		y = _y;
//		tilesize = _tilesize;
//
//	}
//	bool isCollision(CObject& player) {
//		// Assume each box is 32x32
//		// Check collision between this and other objects
//
//		// Euclidean distance of two objects
//		if (x < player.GetX() + player.GetWidth() && x + tilesize > player.GetX() &&
//			y < player.GetY() + player.GetHeight() && y + tilesize > player.GetY()) {
//			cout << "box collision detected" << endl;
//			return true;
//		}
//		else { return false; }
//	};
//};


const int maxSizeY = 80;
const int maxSizeX = 80;

class world {
	tileSet tiles;
	tileSet alphas;
	// unsigned int* map;
	unsigned int size;
	unsigned int* map1;
	unsigned finiteMap[200][40];
public: unsigned int map[maxSizeX][maxSizeY];
	  bool isWater = false;

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

				cout << "map[i][j]" << map[i][j] << endl;
				//if ((map[i][j] >= 14) && (map[i][j] <= 22)) {
				////	isWater = true;
				////	cout << "collision applied for this tile: " << map[i][j] << endl;
				////	int tileX = i * 32;
				////	int tileY = j * 32;

				////}
				////else { isWater = false; }
			}
		}
	}
	//world(string filename){
	//	tiles.Load();
	//	ifstream infile(filename);
	//	int tilenum, i,j;
	//	string s;

	//	infile >> tilenum;
	//	cout << tilenum << endl; 
	//	// map1 = new unsigned int[tilenum];

	//	for (i = 0; i < tilenum; i++) {
	//		for (j = 0; j < tilenum; j++) {
	//			infile >> map[i][j];
	//			cout << map[i][j] << endl;
	//		}

	//	}
	//	infile.close();
	//	}

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
		//while (!infile.eof()) {
		//	infile >> ch;
		//	cout << "ch is " << ch << endl;
		//}
	//	while (getline(infile, s)) {
			// access each line
		//for (unsigned int z = 0; z < tileshigh; z++) {
		//	cout << "s is " << s << endl;
		//	for (unsigned int i = 0; i < tileswide; i++) {
		//		for (unsigned int j = 0; j < tileshigh; j++) {
		//			cout << s[z] << endl;
		//			
		//		}
		//	}
		//	//}
		//}

		int i = 0, j = 0;
		char ch;
		int num = 0;
		bool readingNumber = false;

		while (infile.get(ch)) {
			if (ch >= '0' && ch <= '9') {
				// Accumulate the number character by character
				num = num * 10 + (ch - '0'); // transfer to int
				readingNumber = true;
				cout << num << endl;
			}
			else if (ch == ',' || ch == '\n') {
				// If we encounter a comma or newline, we complete the current number
				if (readingNumber) {
					if (i < 200 && j < 200) {
						map[i][j] = num;

						j++;
						if (j >= 200) { // Move to the next row if column limit is reached
							j = 0;
							i++;
						}
						cout << "map i j is" << map[i][j] << endl;
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
		}
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

	//~world() {
	//	delete[] map1;
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


	//bool collision(GamesEngineeringBase::Window& canvas, CObject& player, unsigned worldX, unsigned worldY) {
	//	bool l1 = testlinex(canvas, player.GetX(), player.GetWidth(), worldX, worldY, player.GetHeight());
	//	//bool l3 = testline1();
	//	//bool l4 = testline1();
	//	return l1;
	//}

	//bool collision(GamesEngineeringBase::Window& canvas, CObject& player, unsigned worldX, unsigned worldY) {
	//	 //Use worldX and worldY in place of wx and wy
	//	bool b1 = testline(canvas, player.GetX(), player.GetY(), player.GetWidth(), player.GetHeight(), worldX, worldY, player.GetHeight() / 3);
	//	bool b2 = testline(canvas, player.GetX() + 19, player.GetY() + 10, player.GetWidth() - 5, player.GetHeight() - 5, worldX, worldY, (player.GetHeight() / 2) - 1);

	//	 //Use logical AND (&&) for boolean logic
	//	return b1 && b2;
	//}

//bool CheckCollidor(CObject& player) {
//	for (unsigned i = 0; i < 100; i++) {
//		for (unsigned j = 0; j < 100; j++) {
//			//cout << "map[i][j] reading" << w.map[i][j] << endl;

//			if ((map[i][j] >= 14) && (map[i][j] <= 22)) {
//				cout << "collision applied for this tile: " << map[i][j] << endl;
//				int tileX = i * 32;
//				int tileY = j * 32;
//				BoxCollider boxcollision(tileX, tileY, 32);
//				return boxcollision.isCollision(player);
//				//! here the map[i][j] remains unchanged even we apply true random, needs to find why

//				// return(boxcollision.isCollision(player));

//				// return boxCollidor(player, x, y);

//			}


//		}
//	}
//}


private:
	//bool testline(GamesEngineeringBase::Window& canvas, unsigned int playerX, unsigned int playerY, unsigned int playerWidth, unsigned playerHeight, unsigned int worldX, unsigned int worldY,unsigned int offset) {
//	bool testline(GamesEngineeringBase::Window& canvas, unsigned int linex, unsigned int length, unsigned int worldX, unsigned int worldY, unsigned int offset) {
//		cout << " test line running" << endl;
//		bool col = false;
//		// find the tiles
//		int Y = (worldY + offset) / 32;
//		int X = (worldX + offset) / 32;
//		
//			cout << "size not = 0" << endl;
//			tile& t = alphas[map[X % size][Y % size]]; // locate tiles
//
//			unsigned int y = t.GetHeight() - ((offset + worldY) % 32); // calculate y position within the tile
//			//unsigned int x = t.GetWidth() - ((offset + worldX) % 32); // calculate x position within the tile
//
//			// start from left, to whole line
//			for (unsigned int i = linex; i < linex + length && i < canvas.getWidth(); i++) {
//				// draw bounding line 
//				cout << "for loop is running" << endl;
//				if (i > canvas.getWidth()) continue;
//				std::cout << "Checking at(i, y, 0) with i = " << i << ", y = " << y << ", width = " << canvas.getWidth() << ", height = " << canvas.getHeight() << std::endl;
//				if (t.GetSprite().at(i, y, 0) < 100) {
//					canvas.draw(i, canvas.getHeight() - offset, 255, 0, 0); // draw line around plane
//					col = true;
//				}
//				else {
//					canvas.draw(i, canvas.getHeight() - offset, 0, 255, 0);
//				}
//
//
//			}
//			return col;
//
//
//	};
//};
//
//bool testlinex(GamesEngineeringBase::Window& canvas, unsigned int linex, unsigned int length, unsigned int worldX, unsigned int worldY, unsigned int offset) {
//	cout << " test line running" << endl;
//	bool col = false;
//	// find the tiles
//	int Y = (worldY + offset) / 32;
//	int X = (worldX + offset) / 32;
//
//	cout << "size not = 0" << endl;
//	tile& t = tiles[map[X % size][Y % size]]; // locate tiles
//
//	unsigned int y = t.GetHeight() - ((offset + worldY) % 32); // calculate y position within the tile
//	//unsigned int x = t.GetWidth() - ((offset + worldX) % 32); // calculate x position within the tile
//
//	// start from left, to whole line
//	for (unsigned int i = linex; i < linex + length && i < canvas.getWidth(); i++) {
//		// draw bounding line 
//		cout << "for loop is running" << endl;
//		if (i > canvas.getWidth()) continue;
//		std::cout << "Checking at(i, y, 0) with i = " << i << ", y = " << y << ", width = " << canvas.getWidth() << ", height = " << canvas.getHeight() << std::endl;
//		if (t.GetSprite().at(i, y, 0) < 100) {
//			canvas.draw(i, canvas.getHeight() - offset, 255, 0, 0); // draw line around plane
//			col = true;
//		}
//		else {
//			canvas.draw(i, canvas.getHeight() - offset, 0, 255, 0);
//		}
//
//
//	}
//	return col;
//
//
//};
//};

};
const unsigned int maxSize1 = 1000;

class Enemy { //: public CObject {


	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 2.f; // the time to next enemy creation
	int offset = 200;

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
				timeThreshold -= 0.02f;
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
		if (isOutBound(enemyArray[i]->GetX(), enemyArray[i]->GetY(), canvas, 350)) {
			CObject* enemyDelete = enemyArray[i];
			enemyArray[i] = nullptr;
			delete enemyDelete;
			cout << "destroyed " << i << endl;
		}
	}



public:
	CObject* enemyArray[1000];
	unsigned int currentSize = 0;
	int px = 200;
	int py = 200;

	Enemy() { };


	void Update(GamesEngineeringBase::Window& canvas, CObject& player, float dt) {

		GenerateEnemy(canvas, dt);
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



//void UIchoice(bool& running, bool&running1) {
//	GamesEngineeringBase::Window menu;
//	menu.create(1024, 768, "menu");
//	bool menu1 = true;
//	while (menu1) {
//		CObject logo(menu.getWidth() / 2, menu.getHeight(), "Resources/L.png");
//		CObject choice1(menu.getWidth() / 2, menu.getHeight() / 5 * 4, "Resources/L.png");
//		CObject choice2(menu.getWidth() / 2, menu.getHeight() / 5 * 3, "Resources/L.png");
//		CObject choice3(menu.getWidth() / 2, menu.getHeight() / 5 * 2, "Resources/L.png");
//		CObject notice(menu.getWidth() / 2, menu.getHeight() / 5, "Resources/L.png"); // notice player to press keys
//		if (score > 1000){
//			CObject egg(menu.getWidth()/5, menu.getHeight() , "Resources/L.png"); // eggs to hiddern level
//		}
//		if (menu.keyPressed(VK_ESCAPE)) break;
//		if (menu.keyPressed('1')) running = true;
//		if (menu.keyPressed('2')) running1 = true;
//	}
//
//}
int main() {
	//srand(static_cast<unsigned int>(time(NULL))); // make sure number are number each time
	// construct windows
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Survivor");

	// construct objects
	CObject player(canvas.getWidth() / 2, canvas.getHeight() / 2, "Resources/L.png");

	Enemy enemy;
	// world w("Resources/tiles.txt");
	world w;
	// GamesEngineeringBase::Timer tim;
	int x = 0, y = 0; // position of hero
	bool running = true; // To control game main loop
	bool running1 = false;
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
		bool alpha = false;
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('W')) y -= 2;
		if (canvas.keyPressed('S')) y += 2;
		if (canvas.keyPressed('A')) x -= 2;
		if (canvas.keyPressed('D')) x += 2;
		if (canvas.keyPressed('Q')) alpha = !alpha;


		//if (canvas.keyPressed('W')) player.Update(0,2);
		//if (canvas.keyPressed('S')) player.Update(0, -2);
		//if (canvas.keyPressed('A')) player.Update(-2, 0);
		//if (canvas.keyPressed('D')) player.Update(2, 0);
		// Hero Creation

		// player.Update(canvas, x, y);


		// Enemy Creation

		// Weapon Creation



		// Draw canvas
		for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++) {
			for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++) {
				canvas.draw(tempx, tempy, 0, 0, 255);
			}
		}

		////GamesEngineeringBase::Window& canvas, CObject& player, unsigned worldX, unsigned worldY
		/*if (alpha) {
			w.drawAlpha(canvas, x, y);
		}
		else {
			w.draw(canvas, x, y);
		}*/
		enemy.Update(canvas, player, dt);
		enemy.Collision(player);
		player.Draw(canvas);
		// w.collision(canvas, player, x, y);
	   //w.CheckCollidor(player, x, y);
	   // Display
	   // enemy.Draw(canvas);

	   //player.draw(canvas);

	   // Frame display
		canvas.present();
	}

	//while (running1) {

	//}
	return 0;
}