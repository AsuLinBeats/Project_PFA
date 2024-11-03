
void draw(GamesEngineeringBase::Window& canvas, int wx, int wy) {
	int height = tiles[0].GetHeight(); // should not be limited in specific tile, but considering every tile should be sliced to 32*32 for pixel game, so it is fine 
	int width = tiles[0].GetWidth();

	int Y = wy / height;
	int rY = wy % height;

	int X = wx / width;
	int rX = wx % width;

	tiles[map[(X) % maxSizeX][(Y) % maxSizeY]].Draw(canvas, (canvas.getWidth() / 2) + rX, (canvas.getHeight() / 2) + rY);
	tiles[map[(X + 1) % maxSizeX][(Y + 1) % maxSizeY]].Draw(canvas, rX, rY);
	tiles[map[(X + 2) % maxSizeX][(Y + 2) % maxSizeY]].Draw(canvas, -width + rX, -height + rY);

	int tileSize = 32;
	for (unsigned i = 0; i < canvas.getWidth() / width; i++) {
		for (unsigned j = 0; j < canvas.getHeight() / height; j++) {

			int posX = i * tileSize;
			int posY = j * tileSize + (wy % tileSize); // scrolling effect

			//int tileIndex = map[(j * 32 + i) % size];
			//tiles[tileIndex].Draw(canvas, posX, posY);

			tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, 32 * i, 32 * j);

			// tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, (canvas.getWidth() / 2) + rWidth, (canvas.getHeight() / 2) + rHeight);
			//tiles[map[(X + 1+i) % maxSizeX][(Y + 1) % maxSizeY]].Draw(canvas, rWidth, rHeight);
			//tiles[map[(X + 2+i) % maxSizeX][(Y + 2) % maxSizeY]].Draw(canvas, -height + rHeight, -width + rWidth);
			//
			// tiles[map[(X+i) % maxSize]].Draw(canvas, (canvas.getWidth() / 2) + rWidth, (canvas.getHeight() / 2) + rHeight);
			//tiles[map[(X + i) % maxSizeX][(Y + j) % maxSizeY]].Draw(canvas, (i * width) - rWidth + (canvas.getWidth() / 2), (j * height) - rHeight + (canvas.getHeight() / 2));
		}
	}
}
//for (unsigned int i = 0; i < 32; i++) {
		//	for (unsigned int j = 0; j < 24; j++) {
		//		tiles[map[i*j]].Draw(canvas, 0 + 32 * i, 32 * j);
		//	} 

		//}

		//for (unsigned int i = 0; i < 32; i++) {
		//	for (unsigned int j = 0; j < 24; j++) {
		//		unsigned int tileIndex = map[i + j * 32];  // Calculate 1D index based on 2D position
		//		tiles[tileIndex].Draw(canvas, i * width, j * height);  // Adjusted to use width and height
		//	}
		//}

//METHOD YTB
		//int type = 0;
		//for (unsigned int i = 0; i < 32; i++) {
		//	for (unsigned int j = 0; j < 24; j++) {
		//		type = map1[i][j];
		//		tiles[type].Draw(canvas, i*32, j*24);
		//	}
		//}


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