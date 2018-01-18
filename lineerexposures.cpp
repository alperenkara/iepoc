// ==========================================================================
//
//
//  Version:    1.1
//  $Workfile: LineerExposures.cpp $
//  $Project  : Image Enhancement Prior To Object Classification 
//  $Created : 2017-10-28 09:27:42
//
//
//  Description:
//				This single code created for especially "The German Traffic Sign Recognition Dataset"
//				It is able to create four different exposured images from folder with Linear Contrast Control
//
// ==========================================================================

#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

int main() {
	//data.txt has file path of original dataset pictures
	ifstream myReadFile;
	myReadFile.open("file-paths-00042.txt");
	char output[200];
	//counters
	int ex1 = 0;
	int ex2 = 0;
	//if file is not able read go to return
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {


			myReadFile >> output;
	
			//cout << output << endl;;

			//Simple contrast control 
			double alpha = 1; 
			double beta = 0;		

			for (int ex = 0; ex < 4; ex++) {
				
				/// Read main image was given by user
				Mat image = imread(output);
				//reading size and type
				Mat new_image = Mat::zeros(image.size(), image.type());

			
				//alpha*image(i,j) + beta
				image.convertTo(new_image, -1, alpha, beta);//without for loop

				char path[512];
				snprintf(path, 512, "C:/exposures/FourExposures/00042/v1_%d_%05d_%05d.ppm", ex,ex1,ex2);
				cv::imwrite(path, new_image);
			
		
			
				alpha++;
				beta = beta + 50;
				if (2 <= alpha) { alpha = 1.00; }
				//Move another picture in every fourth copy
				if (beta == 200) { beta = 0.00; ex2++; }
				//Move next main class in every 29 sub-class
				if (ex2 == 30) { ex2 = 0; ex1++; }
				

			}

			
		}
	}
	myReadFile.close();
	return 0;
}

