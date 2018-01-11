// ==========================================================================
//
//
//  Version:    1.1
//  $Workfile: source.cpp $
//  $Project  : Image Enhancement Prior To Object Classification 
//  $Created : 2017-10-28 09:27:42
//
//
//  Description:
//				This single code created for especially "The German Traffic Sign Recognition Dataset"
//				It is able to read four different exposured images from folder which merged with Mertens's Fusion Algorithm	
//
// ==========================================================================

#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

void loadExposureSeq(vector<Mat>&, vector<float>&);
int ex5 = 0;
int main(int, char**argv)
{	
	
	while(true) {
		//every sub-class have 29 pictures in the dataset(00000-00029.ppm)
		for (int ex4 = 0; ex4 <= 29; ex4++) {

			vector<Mat> images;
			vector<float> times;
		
	// giving name and merging images
	loadExposureSeq(images, times);

	Mat fusion;
	Ptr<MergeMertens> merge_mertens = createMergeMertens();
	merge_mertens->process(images, fusion);

	//"C:/exposures/vb1/SR1/00000/%05d_%05d.ppm"
	//file path must change for the new save folder

	char path0[512];
	snprintf(path0, 512, "C:/exposures/vb1/SR1/00042/%05d_%05d.ppm", ex5,ex4);
	//cv::imwrite(path0,images);
	imwrite(path0, fusion * 255);
	////////////////////////////////////////////////////////
	// after 29 sub-class, increase to main class number
	if (ex4 == 29) { ex5++; }
		}
	}
	
}
int ex1 = 0;
int ex2 = 0;
void loadExposureSeq(vector<Mat>& images, vector<float>& times)
{	
	
		//reading different exposured images v1_0_00000_00000.ppm
	for (int ex = 0; ex <= 3; ex++) {
		char path[512];
		snprintf(path, 512, "C:/exposures/FourExposures/00042/v1_%d_%05d_%05d.ppm", ex, ex1, ex2);

		cout << path << endl;
		
		Mat img = imread(path);
		images.push_back(img);

		//Move to another picture in every fourth exposured image
		if (ex == 3) { ex2++; }
		//Move to another sub-class in every 29 pictures	
		if (ex2 == 30) { ex2 = 0; ex1++; }
		}
	
}
