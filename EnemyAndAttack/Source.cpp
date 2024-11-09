#include<iostream>
#include"GamesEngineeringBase.h"

using namespace std;


//
//
//void updateMovementAnim(string name,GamesEngineeringBase::Window& canvas, int x, int y) {
//    int animIndex = 0;  
//    const int totalIndex = 5;
//    int counter = 0;
//    //if (++counter % 5 == 0) {
//    //    animIndex++;
//    //}
//    //animIndex = animIndex % totalIndex;
//    GamesEngineeringBase::Image sprite[totalIndex];
//
//    for (unsigned int i=0; i < 5; i++) {
//        sprite[i].load("Resources/" + name + to_string(i) + ".png");
//    }
//
//    if (animIndex < 5) {
//        animIndex++;
//    }
//    else {
//        animIndex = 0;
//    }
//    for (unsigned int i = 0; i < sprite[animIndex].width; i++) {
//        if (x + i > 0 && x + i < canvas.getWidth()) {
//            for (unsigned int j = 0; j < sprite[animIndex].height; j++) {
//                if (y + j > 0 && y + j < canvas.getHeight()) {
//                    if (sprite[animIndex].alphaAt(i, j) > 200)
//                        canvas.draw(x + i, y + j, sprite[animIndex].at(i, j));
//
//                }
//            }
//        }
//    }
//}
//
//int main() {
//    GamesEngineeringBase::Window canvas;
//    canvas.create(1024, 768, "Survivor");
//
//    GamesEngineeringBase::Timer dt;
//    bool running = true;
//    while (running) {
//        canvas.clear();
//        for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++) {
//            for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++) {
//                canvas.draw(tempx, tempy, 0, 0, 255);
//            }
//        }
//
//        updateMovementAnim("slime", canvas, 200, 200);
//
//
//        canvas.present();
//    }
//
//}

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
int main() {
	GamesEngineeringBase::SoundManager soundmanager;
	GamesEngineeringBase::Sound bgm;
	soundmanager.loadMusic("bgm.wav");
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Survivor");

	GamesEngineeringBase::Image title;
	GamesEngineeringBase::Image title1;
	GamesEngineeringBase::Image title2;

	GamesEngineeringBase::Image menu;
	GamesEngineeringBase::Image menu1;
	GamesEngineeringBase::Image menu2;


	GamesEngineeringBase::Image mode;
	GamesEngineeringBase::Image mode1;
	GamesEngineeringBase::Image mode2;


	GamesEngineeringBase::Image exit;
	GamesEngineeringBase::Image exit1;
	GamesEngineeringBase::Image exit2;

	GamesEngineeringBase::Image egg;
	GamesEngineeringBase::Image egg1;
	GamesEngineeringBase::Image egg2;


	GamesEngineeringBase::Image background;

	title.load("Resources/title0.png");
	title1.load("Resources/title1.png");
	title2.load("Resources/title2.png");

	menu.load("Resources/menu0.png");
	menu1.load("Resources/menu1.png");
	menu2.load("Resources/menu2.png");
	
	mode.load("Resources/mode0.png");
	mode1.load("Resources/mode1.png");
	mode2.load("Resources/mode2.png");

	exit.load("Resources/exit0.png");
	exit1.load("Resources/exit1.png");
	exit2.load("Resources/exit2.png");


	egg.load("Resources/egg0.png");
	egg1.load("Resources/egg1.png");
	egg2.load("Resources/egg2.png");

	background.load("Resources/background.png");
	int offset = 225;
	int offset1 = 380;

	soundmanager.playMusic();
	while (true) {
		
		canvas.clear();
		for (unsigned int tempx = 0; tempx < canvas.getWidth(); tempx++) {
		for (unsigned int tempy = 0; tempy < canvas.getHeight(); tempy++) {
		canvas.draw(tempx, tempy, 0, 0, 255);
			}
		}
		Draw(canvas, background, 0, 0);

		Draw(canvas, title, offset, 75);
		Draw(canvas, title1, offset+title.width, 75);
		Draw(canvas, title2, offset+title.width + title1.width, 75);

		Draw(canvas, menu, offset1, 300);
		Draw(canvas, menu1, offset1 + menu.width, 300);
		Draw(canvas, menu2, offset1 + menu.width + menu1.width, 300);

		Draw(canvas, mode, offset1, 400);
		Draw(canvas, mode1, offset1 + mode.width, 400);
		Draw(canvas, mode2, offset1 + mode.width + mode1.width, 400);

		Draw(canvas, exit, offset1, 500);
		Draw(canvas, exit1, offset1 + exit.width, 500);
		Draw(canvas, exit2, offset1 + exit.width + exit1.width, 500);

		Draw(canvas, egg, offset1, 600);
		Draw(canvas, egg1, offset1 + egg.width, 600);
		Draw(canvas, egg2, offset1 + egg.width + egg1.width, 600);
		canvas.present();
	}

	return 0;
}
	
void dead(GamesEngineeringBase::Window& canvas) {
	GamesEngineeringBase::Image dead;
	dead.load("Resources/dead.png");
	Draw(canvas, dead, 0, 0);
}