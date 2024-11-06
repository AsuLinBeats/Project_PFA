//class Enemy { //: public CObject {
//	
//	
//	float timeElapsed = 0.f; // time since last enemy created
//	float timeThreshold = 2.f; // the time to next enemy creation
//	int offset = 200;
//
//	void Random(GamesEngineeringBase::Window& canvas, int _offset) {
//		offset = _offset;
//		int side = rand() % 4;
//		switch (side) {
//		case 0:
//			// Generate enemy from top
//			px = rand() % canvas.getWidth();
//			py = -offset;
//			break;
//		case 1:
//			// Generate enemy from bottom
//			px = rand() % canvas.getWidth();
//			py = canvas.getHeight() + offset;
//			break;
//		case 2:
//			// generate enemy from left
//			px = -offset;
//			py = rand() % canvas.getHeight();
//			break;
//		case 3:
//			// generate enemy from right
//			px = canvas.getWidth() + offset;
//			py = rand() % canvas.getHeight();
//			break;
//		}
//	}
//
//	void GenerateEnemy(GamesEngineeringBase::Window& canvas, float dt) {
//		Random(canvas, 150);
//		timeElapsed += dt;
//		if (currentSize < maxSize1) {
//			if (timeElapsed > timeThreshold) {
//				CObject* newEnemy = new CObject(px, py, "Resources/L2.png");
//				cout << "Enemy created: " << currentSize << endl;
//				// Save address of new enemy to array
//				enemyArray[currentSize++] = newEnemy;
//				// reset generation parameter
//				timeElapsed = 0.f;
//				timeThreshold -= 0.2f;
//				// difficulty control
//				timeThreshold = max(0.2f, timeThreshold);
//			}
//		}
//		else {
//			cout << "Last Enemy!!!" << endl;
//		}
//	}
//
//	bool isOutBound(int _px, int _py, GamesEngineeringBase::Window& canvas, int _offset) {
//		// check if object out boundary
//		px = _px;
//		py = _py;
//		return (px < -_offset ||
//			px > canvas.getWidth() + _offset ||
//			py < -_offset ||
//			py > canvas.getHeight() + _offset);
//	}
//
//	void CheckDeletedEnemy(GamesEngineeringBase::Window& canvas, unsigned int i) {
//		if (i >= maxSize1 || enemyArray[i] == nullptr) return;
//		if (isOutBound(enemyArray[i]->GetX(), enemyArray[i]->GetY(), canvas, 250)) {
//			CObject* enemyDelete = enemyArray[i];
//			enemyArray[i] = nullptr;
//			delete enemyDelete;
//			cout << "destroyed " << i << endl;
//		}
//	}
//
//
//
//public:
//	CObject* enemyArray[1000];
//	unsigned int currentSize = 0;
//	int px = 200;
//	int py = 200;
//
//	Enemy() { };
//
//
//	void Update(GamesEngineeringBase::Window& canvas, CObject& player, float dt) {
//
//		GenerateEnemy(canvas, dt);
//		// cout << "After generate enemy running!" << endl;
//		  // define speed
//		int speed = static_cast<int>((70.0f * dt));
//
//		for (unsigned int i = 0; i < currentSize; i++) {
//			if (enemyArray[i] != nullptr) {
//				// calculate direction between player and enemy
//				float dx = player.GetX() - enemyArray[i]->GetX();
//				float dy = player.GetY() - enemyArray[i]->GetY();
//				float distance = sqrtf(dx * dx + dy * dy);
//				// add check to avoid devided by 0
//				if (distance > 0.0f) {
//					int moveX = static_cast<int>((dx / distance) * speed);
//					int moveY = static_cast<int>((dy / distance) * speed);
//					enemyArray[i]->Update(moveX, moveY);
//					CheckDeletedEnemy(canvas, i);
//				}
//			}
//		}
//	}
//
//	void Draw(GamesEngineeringBase::Window& canvas) {
//		for (unsigned int i = 0; i < currentSize; i++) {
//			if (enemyArray[i] != nullptr)
//				enemyArray[i]->Draw(canvas);
//		}
//	}
//
//	bool Collision(CObject& player) {
//		for (unsigned int i = 0; i < currentSize; i++) {
//			if (enemyArray[i] != nullptr && enemyArray[i]->CircleCollidor(player)) {
//				cout << "crash: " << i << endl;
//				return true;
//			}
//		}
//		return false;
//	}
//};
//
//int level[5] = { 1,2,3,4,5 };
//int const weaponLevel = 1;
//int maxBullet = weaponLevel;
//
//
//class bullet : public CObject {
//	CObject* bullet[weaponLevel];
//	unsigned int currentNumber = 0;
//	float timeElapsed = 0.f; // time since last bullet
//	float timeThreshold = 2.f; // the time to next bullet generation
//	// Enemy enemy;
//	// bullet targeted to enemy
//	void GenerateBullet(GamesEngineeringBase::Window& canvas, CObject& player, Enemy& enemy,float dt) {
//		// the number of bullet targeted to enemy depends on weaponLevel
//		timeElapsed += dt;
//		if (currentNumber < maxBullet) {
//			if (timeElapsed > timeThreshold) {
//				for (unsigned int i; i < enemy.currentSize; i++) {
//					// loop from existing enemy to find closest one;
//					if (enemy.enemyArray[i] != nullptr) {
//						// calculate distance
//						float dx = player.GetX() - enemy.enemyArray[i]->GetX();
//						float dy = player.GetY() - enemy.enemyArray[i]->GetY();
//						float distance = sqrtf(dx * dx + dy * dy);
//						if (distance > 0.0f) {
//							CObject* newBullet = new CObject(player.GetX(), player.GetY(), "projectile1.svg");
//							cout << "Bullet created" << endl;
//							bullet[currentNumber++] = newBullet;
//
//							timeElapsed = 0.f;
//							timeThreshold = 1 / weaponLevel; // generate bullets more frequent as level increases;
//							timeThreshold = max(0.4f, timeThreshold); // set maximum frequency
//						}
//					}
//				}
//			}
//		}
//	}
//
//	void BulletDelete(GamesEngineeringBase::Window& canvas, unsigned int i,bool collision) {
//		if (collision) {
//			CObject* bulletDelete = bullet[i];
//			bullet[i] = nullptr;
//			delete bulletDelete;
//			cout << "attack success" << endl;
//		}
//	}
//
//	bool Collision(Enemy& enemy) {
//		for (unsigned int i = 0; i < currentSize; i++) {
//			if (enemyArray[i] != nullptr && enemyArray[i]->CircleCollidor(enemy)) {
//				cout << "crash: " << i << endl;
//				return true;
//			}
//		}
//		return false;
//	}
//};