
#include <bangtal.h>


SceneID scene1;
ObjectID startButton, endButton;
ObjectID image00, image01, image02, image10, image12, image20, image21, image22, blank;
TimerID timer1;

static ObjectID image[3][3] = {
	{image00, image01, image02},
	{image10, blank, image12},
	{image20, image21, image22}
};

static int blank_loc[3][3] = {
	{1, 1, 1},
	{1, 0, 1},
	{1, 1, 1}
};

int Xcoordin[3][3] = { 
	{101, 468, 835},
	{101, 468, 835},
	{101, 468, 835}
};
int Ycoordin[3][3] = {
	{480, 480, 480},
	{290, 290, 290},
	{100, 100, 100}

};

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void image_swap(ObjectID* a, ObjectID* b)
{
	ObjectID temp = *a;
	*a = *b;
	*b = temp;
}

void startGame()
{
	hideObject(startButton);
	hideObject(endButton);

	showObject(image[0][0]);
	showObject(image[0][1]);
	showObject(image[0][2]);
	showObject(image[1][0]);
	showObject(image[1][2]);
	showObject(image[2][0]);
	showObject(image[2][1]);
	showObject(image[2][2]);

	setTimer(timer1, 20.0f);
	startTimer(timer1);

}

void closeGame()
{
	showMessage("시간 종료!");
	showObject(endButton);
	stopTimer(timer1);
}

void timerCallback(TimerID timer)
{
	if (timer == timer1)
	{
		closeGame();
	}
}


ObjectID makeObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);

	locateObject(object, scene, x, y);

	if (shown)
	{
		showObject(object);
	}
	return object;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	int flag = false;

	

	if (object == startButton)
	{
		startGame();
	}
	else if (object == endButton) {
		endGame();
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (object == image[i][j] && blank_loc[i][j]) {
				if (j < 2 && !blank_loc[i][j + 1]) {
					locateObject(image[i][j], scene1, Xcoordin[i][j + 1], Ycoordin[i][j + 1]);
					swap(&blank_loc[i][j], &blank_loc[i][j + 1]);
					image_swap(&image[i][j], &image[i][j + 1]);
					

					
					flag = true;
					break;

					

					
				}
				else if (j > 0 && !blank_loc[i][j - 1]) {
					locateObject(image[i][j], scene1, Xcoordin[i][j - 1], Ycoordin[i][j - 1]);
					
					swap(&blank_loc[i][j], &blank_loc[i][j - 1]);
					image_swap(&image[i][j], &image[i][j - 1]);
					


					flag = true;
					break;

					
					
				}
				else if (i < 2 && !blank_loc[i + 1][j]) {
					locateObject(image[i][j], scene1, Xcoordin[i + 1][j], Ycoordin[i + 1][j]);
					swap(&blank_loc[i][j], &blank_loc[i + 1][j]);
					image_swap(&image[i][j], &image[i + 1][j]);


					flag = true;
					break;

				
					
				}
				else if (i > 0 && !blank_loc[i - 1][j]) {
					locateObject(image[i][j], scene1, Xcoordin[i - 1][j], Ycoordin[i - 1][j]);
					swap(&blank_loc[i][j], &blank_loc[i - 1][j]);
					image_swap(&image[i][j], &image[i - 1][j]);

					flag = true;
					break;
					

				}
			}
		}
		if (flag == true)
		{
			break;
		}
	}
}

int main()
{
	
	setTimerCallback(timerCallback);
	setMouseCallback(mouseCallback);

	scene1 = createScene("퍼즐 맞추기", "scene1.png");

	startButton = makeObject("start.png", scene1, 530, 50, true);
	endButton = makeObject("end.png", scene1, 650, 50, true);

	// x좌표 : 101, 468, 835
	// y좌표 : 100, 290, 480

	image[0][0] = makeObject("image1.png", scene1, Xcoordin[0][0], Ycoordin[0][0], false);
	image[0][1] = makeObject("image6.png", scene1, Xcoordin[0][1], Ycoordin[0][1], false);
	image[0][2] = makeObject("image2.png", scene1, Xcoordin[0][2], Ycoordin[0][2], false);
	image[1][0] = makeObject("image7.png", scene1, Xcoordin[1][0], Ycoordin[1][0], false);
	image[1][2] = makeObject("image3.png", scene1, Xcoordin[1][2], Ycoordin[1][2], false);
	image[2][0] = makeObject("image5.png", scene1, Xcoordin[2][0], Ycoordin[2][0], false);
	image[2][1] = makeObject("image4.png", scene1, Xcoordin[2][1], Ycoordin[2][1], false);
	image[2][2] = makeObject("image8.png", scene1, Xcoordin[2][2], Ycoordin[2][2], false);

	timer1 = createTimer(20.0f);
	showTimer(timer1);
	

	startGame(scene1);
	
	
}