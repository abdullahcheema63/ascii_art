//============================================================================
// Name        : ascii-art.cpp
// Author      : Abdullah Cheema
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cmath>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

#define WIDTH 480	
#define HEIGHT 720
const int w=3;
float imMax=0,imMin=255,asciiMax=0,asciiMin=255;
int imArray[HEIGHT][WIDTH];
int asciiArray[250][230];
float averageAsciiArray[10][10];
float averageImArray[720/w][480/w];
float scaledImArray[720/w][480/w];
float scaledAsciiArray[10][10];
float scaledAscii1d[100];
char asciiChArray[100];
void ReadAsciiCharactersImage(int array[][230]) {

	CImg<unsigned char> img("./ascii-char-set-25_23-95-grid.png");
	int k = 0;
	for (int i = 0; i < 250; ++i)
		for (int j = 0; j < 230; ++j)
			array[i][j] = img[k++];

}
void ReadImage(string imgname, int imgArray[][WIDTH]) {
	CImg<unsigned char> img(imgname.c_str());
	int k = 0;
	for (int i = 0; i < img.height(); ++i)
		for (int j = 0; j < img.width(); ++j)
			imgArray[i][j] = img[k++];
}

int main(int argc, char *argv[]) {

	int winsize = 5;
	if (argc < 2 || argc > 3) {
		cerr << "\nProgram require at least one input \n "
				"Usage: ascii-art <filename> <window-size (by default 5> \n"
				" " << endl;
		return 0;
	}
	string imname = argv[1]; // variable to store given image name
	if (argc == 3)
		winsize = atoi(argv[2]);

	// Your code goes here, write auxliary functions and
	// call them here
	
	ReadAsciiCharactersImage(asciiArray);
	ReadImage(imname,imArray);
	//avrerage of ascii image
	for (int h=0,r=0;h<250;r=0,h+=25)
	{
		for (;r<230;r+=23)
		{
			for (int i=h;i<h+25;i++)
			{
				for (int j=r;j<r+23;j++)
				{
					averageAsciiArray[h/25][r/23]+=asciiArray[i][j];
				}
			}
			averageAsciiArray[h/25][r/23]/=25*23;
		}
	}
	//calculating average of image
	for (int h=0,r=0;h<720;r=0,h+=w)
	{
		for (;r<480;r+=w)
		{
			for (int i=h;i<h+w;i++)
			{
				for (int j=r;j<r+w;j++)
				{
					averageImArray[h/w][r/w]+=imArray[i][j];
				}
			}
			averageImArray[h/w][r/w]/=w*w;
		}
	}
	
	//calculating max and min of image array 
	for (int i=0;i<720/w;i++)
	{
		for (int j=0;j<480/w;j++)
		{
			if (averageImArray[i][j]<imMin)
			{
				imMin=averageImArray[i][j];
			}
			if (averageImArray[i][j]>imMax)
			{
				imMax=averageImArray[i][j];
			}
		}
	}
	//calculate max and min of ascii array
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			if (averageAsciiArray[i][j]<asciiMin)
			{
				asciiMin=averageAsciiArray[i][j];
			}
			if (averageAsciiArray[i][j]>asciiMax)
			{
				asciiMax=averageAsciiArray[i][j];
			}
		}
	}

	//rescaling image arrays
	for (int i=0;i<720/w;i++)
	{
		for (int j=0;j<480/w;j++)
		{
			scaledImArray[i][j]=(averageImArray[i][j]-imMin)/(imMax-imMin);
		}
	}
	//rescaling asciiarray
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			scaledAsciiArray[i][j]=(averageAsciiArray[i][j]-asciiMin)/(asciiMax-asciiMin);
		}
	}
	//converting 2d ASCII array to 1d

	for (int i=0,k=0;i<10;i++)
	{
		for (int j=0;j<10;j++,k++)
		{
			scaledAscii1d[k]=scaledAsciiArray[i][j];
			
			asciiChArray[k]=k+32;
		}
	}
	float temp1;char temp2;
	//sorting the 1d asciiarray to find the closest
	for (int i =0;i<100;i++)
	{
		for (int j=0;j<99;j++)
		{
			if (scaledAscii1d[j]>scaledAscii1d[j+1])
			{
				temp1=scaledAscii1d[j];
				temp2=asciiChArray[j];
				scaledAscii1d[j]=scaledAscii1d[j+1];
				asciiChArray[j]=asciiChArray[j+1];
				scaledAscii1d[j+1]=temp1;
				asciiChArray[j+1]=temp2;
			}
		}
	}
	//finding closest one
	float selectorIm;
	int k;
	for (int i=0;i<720/w;i++)
	{
		for (int j=0;j<480/w;j++)
		{
			selectorIm=scaledImArray[i][j];
			for (k=0;selectorIm>scaledAscii1d[k];k++)
			{}
			cout<<asciiChArray[k-1];
		}
		cout<<endl;
	}
	cout<<endl;
}	
