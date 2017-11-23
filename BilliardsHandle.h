#pragma once

#include <iostream>
#include <string>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

struct pointColor {
	float x, y, z;
};

struct pointPosition {

	pointPosition() = default;
	pointPosition(unsigned x, unsigned y) : coord_x(x), coord_y(y) {};

	void setCoordinates(unsigned x, unsigned y) {
		coord_x = x;
		coord_y = y;
	}

	unsigned getX() {
		return coord_x;
	}

	unsigned getY() {
		return coord_y;
	}

private:
	unsigned int coord_x, coord_y;
};

class BilliardHandle {

	pointColor A, B_Field, B_Ball, C;
	pointPosition pB, pF;
	int color_diff;

	double BC, AC, AB;
	double angle_alpha;
	double angle_beta;

	int indentTop, indentBottom;

public:

	void setBallPointForCalibration(unsigned x, unsigned y) {
		pB.setCoordinates(x, y);
	}

	void setFieldPointForCalibration(unsigned x, unsigned y) {
		pF.setCoordinates(x, y);
	}

	pointPosition getPointPosition() {
		return pB;
	}

	cv::Mat in_cam, img, imgField;

	BilliardHandle();

	void calibrate();
	void printColorsOnImg();
	void findField();

};


