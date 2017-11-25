#include <iostream>

#include "BilliardsHandle.h"

using namespace std;
using namespace cv;

static void help() {

	cout << "This is a demo billiard handler program\n"
		"OpenCV version " << CV_VERSION << endl;
	cout << "It uses ready video by default, but you can provide a path to video as an argument.\n";
	cout << "Now you need to calibrate the colour of the balls and field" << endl;
	cout << "Please, right click on the field, left click on the ball" << endl;
	cout << "After that press the Enter key" << endl;
}

static void onMouse(int event, int x, int y, int, void* handler) {
	BilliardHandle* localHandler = static_cast<BilliardHandle*>(handler);
	if (event == EVENT_LBUTTONDOWN) {
		localHandler->setBallPointForCalibration(x, y);
		std::cout << "Point of the ball with coordinates (" << x << ", " << y << ") is taken" << std::endl;
	}
	if (event == EVENT_RBUTTONDOWN) {
		localHandler->setFieldPointForCalibration(x, y);
		std::cout << "Point of the field with coordinates (" << x << ", " << y << ") is taken" << std::endl;
	}
};

int main(int argc, char** argv) {

	help();
	BilliardHandle game;
	VideoCapture capture;

	if (argc != 2) {
		capture.open("Shary_2.mp4");
	} else {
		capture.open(argv[1]);
	}
	
	if (!capture.isOpened()) {
		cout << "Could not initialize capturing...\n";
		return 0;
	}

	namedWindow("Calibration", WINDOW_AUTOSIZE);
	setMouseCallback("Calibration", onMouse, &game);

	while (1) {
		capture >> game.in_cam;
		resize(game.in_cam, game.img, game.img.size());
		imshow("Calibration", game.img);
		char c = (char)cvWaitKey(10);
		if (c == 13)
			break;
	}

	game.calibrate();

	cout << "Calibration is completed" << endl;

	game.findField();

	while (1) {
		capture >> game.in_cam;
		resize(game.in_cam, game.img, Size(480, 260));

		game.printColorsOnImg();

		imshow("Calibration", game.img);
		char c = (char)cvWaitKey(10);
		if (c == 27)
			break;
	}
	return 0;
}
