#include<iostream>
#include<fstream> // for file handling
#include<cmath>
#include"GamesEngineeringBase.h" // for main function building
using namespace std;
// Declaration: The naming convention followed by Microsoft rules.

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
	}

	void Update(int _x, int _y) {
		x += _x;
		y += _y;
	}

	void Update(GamesEngineeringBase::Window &canvas,int _x, int _y) {
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


class plane {
protected:
	int x, y;
	GamesEngineeringBase::Image sprite;
public:
	plane(int _x, int _y, string filename) {
		sprite.load(filename);
		x = _x - (sprite.width / 2);
		y = _y;
	}

	void draw(GamesEngineeringBase::Window& canvas) {
		for (unsigned int i = 0; i < sprite.height; i++)
			if (y + i < canvas.getHeight() && y + i >= 0) {
				for (unsigned int n = 0; n < sprite.width; n++)
				{
					if (x + n < canvas.getWidth() && x + n >= 0) {

						if (sprite.alphaAt(n, i) > 200)
							canvas.draw(x + n, y + i, sprite.at(n, i));
					}
				}
			}
	}
	void update(int _x, int _y) {
		x += _x;
		y += _y;
	}

	void update(GamesEngineeringBase::Window& canvas, int _x, int _y) {
		x += _x;
		y += _y;

		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x + sprite.width > canvas.getWidth()) x = canvas.getWidth() - sprite.width;
		if (y + sprite.height > canvas.getHeight()) y = canvas.getHeight() - sprite.height;
	}

	int getY() {
		return y;
	}
	int getX() {
		return x;
	}
};
























//class CCharacter : public CObject {
//public:
//	int _maxblood = 100;
//	CCharacter(int _x, int _y, string filename, int _maxblood) : CObject(_x, _y, filename) {
//
//	}
//	// 因为视角锁定中心，其实也不一定需要boundary check
//	// prob do not need boundary check as the camera is located at centre, following player
//	void Update(GamesEngineeringBase::Window& canvas, int _x, int _y) {
//		x += _x;
//		y += _y;
//		// boundary check
//		if (x + sprite.width > canvas.getWidth()) x = canvas.getWidth();
//		if (y + sprite.height > canvas.getHeight()) y = canvas.getHeight();
//	}
//};

const unsigned int maxSize1 = 1000;

class Enemy{//: public CObject {
	CObject* enemyArray[maxSize1];
	unsigned int currentSize = 0;
	float timeElapsed = 0.f; // time since last enemy created
	float timeThreshold = 2.f; // the time to next enemy creation
	int px, py;
	int offset;

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

	//void CheckDeletedEnemy(GamesEngineeringBase::Window& canvas, unsigned int i) {
	//	if (i >= maxSize1 || enemyArray[i] == nullptr) return;
	//	if (isOutBound(enemyArray[i]->GetX(), enemyArray[i]->GetY(),canvas,offset)) {
	//		//CObject* enemyDelete = enemyArray[i];
	//		delete enemyArray[i];
	//		enemyArray[i] = nullptr;
	//		cout << "destroyed " << i << endl;
	//	}
	//}

	void CheckDeletedEnemy(GamesEngineeringBase::Window& canvas, unsigned int i) {
		if (i >= maxSize1 || enemyArray[i] == nullptr) return; // Null check

		if (isOutBound(enemyArray[i]->GetX(), enemyArray[i]->GetY(), canvas, offset)) {
			delete enemyArray[i]; // Delete once
			enemyArray[i] = nullptr; // Set to nullptr to avoid double deletion
			cout << "destroyed " << i << endl;
		}
	}

public:
	Enemy() {
		for (unsigned int i = 0; i < maxSize1; i++) {
			// initialise array
			enemyArray[i] = nullptr;
		}
	};

	void Update(GamesEngineeringBase::Window& canvas, float dt, CObject player) {
		
		GenerateEnemy(canvas, dt);
		// define speed
		int speed = static_cast<int>((100.0f * dt));

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
					// CheckDeletedEnemy(canvas, i);
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

int main() {
	// srand(static_cast<unsigned int>(time(NULL)));
	// construct windows
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Survivor");
	
	// construct objects
	CObject player(canvas.getWidth() / 2, canvas.getHeight() / 2, "Resources/L.png");

	Enemy enemy;
	GamesEngineeringBase::Timer tim;
	bool running = true; // To control game main loop
	// game runniung
	while (running) {

		// variables needs to be updated each frame
		int x=0, y=0; // position of hero
		

		// Functions implementation
		// check input
		canvas.checkInput();
		// clear windows for next frame
		canvas.clear();

		float dt = tim.dt();
		// int move = static_cast<int>((500.f * dt));
		// move function implementation
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('W')) y -= 2;
		if (canvas.keyPressed('S')) y += 2;
		if (canvas.keyPressed('A')) x -= 2;
		if (canvas.keyPressed('D')) x += 2;


		// Hero Creation
		 player.Update(canvas, x, y);
		//player.update(canvas, x, y);
		enemy.Update(canvas, dt, player);
		//enemy.Collision(player);
		// Weapon Creation

		// Enemy Creation

		// Draw canvas
		for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++)
			for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++)
				canvas.draw(tempx, tempy, 0, 0, 255);

		// Display
		//enemy.Draw(canvas);
		//player.Draw(canvas);
		//player.draw(canvas);

		// Frame display
		canvas.present();
	}
	return 0;
}
