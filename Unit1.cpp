//---------------------------------------------------------------------------

#include <fmx.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <FMX.Graphics.hpp>
#include <ctime>
#include <random>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;

float* meanarr;
float sum;
float** dataarr;
float** pearsonarr;
int row,col;
int** discretizearr;
float** permutationarr;
TBitmap* bitmap = new TBitmap();
TBitmap* bitmap2 = new TBitmap();
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1Click(TObject *Sender)
{
// Check if the current zoom level is 100%
	if (Image1->Width == row && Image1->Height == row) {
		// Zoom in by multiplying the width and height by a zoom factor
		Image1->Width = row * 1.5;
		Image1->Height = row * 1.5;
	} else {
		// Reset to original size
		Image1->Width = row;
		Image1->Height = row;
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image2Click(TObject *Sender)
{
	  // Check if the current zoom level is 100%
	if (Image2->Width == row && Image2->Height == row) {
		// Zoom in by multiplying the width and height by a zoom factor
		Image2->Width = row * 1.5;
		Image2->Height = row * 1.5;
	} else {
		// Reset to original size
		Image2->Width = row;
		Image2->Height = row;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::InputClick(TObject *Sender)
{
   System::String filename = TextBox->Text;

	std::ifstream fin;
	fin.open(filename.c_str());
	if (!fin.is_open()) {
		ShowMessage("Error opening file.");
	fin.close();
	}
	else
	{

    ShowMessage("File  Read!");
	// Read row and col from file
	fin >> row >> col;


dataarr=new float*[row];
for(int i=0;i<row;i++){
	dataarr[i]=new float[col];
}
for(int i=0;i<row;i++){
	for(int j=0;j<col;j++){
		fin>>dataarr[i][j];
	}
}
pearsonarr=new float*[row];
for(int i=0;i<row;i++){
	pearsonarr[i]=new float[row];
}

discretizearr=new int*[row];
for(int i=0;i<row;i++){
	discretizearr[i]=new int[row];
}


permutationarr=new float*[row];
for(int i=0;i<row;i++){
	permutationarr[i]=new float[col];
}
for(int i=0;i<row;i++){
	for(int j=0;j<col;j++){
		permutationarr[i][j]=dataarr[i][j];
	}
}
}

	fin.close();


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{

	Image2->Bitmap = nullptr;
// Calculate max value for each column
	for (int j = 0; j < row; ++j) {
		float maxVal = pearsonarr[0][j];
		for (int i = 1; i < row; ++i) {
			if (pearsonarr[i][j] > maxVal) {
				maxVal = pearsonarr[i][j];
			}
		}
		// Normalize values and apply green shade
		for (int i = 0; i < row; ++i) {
			float normalizedValue = (pearsonarr[i][j] / maxVal) * 255;
			TAlphaColor color = TAlphaColorRec::Green; // Default color is green


			if (normalizedValue < 0) {
				normalizedValue = 0;
			}
			else if (normalizedValue > 255) {
				normalizedValue = 255;
			}
			// Construct RGB color
			int greenIntensity = round(normalizedValue);
			color = MakeColor(0, greenIntensity, 0); // Green shade
			bitmap2->SetSize(row, row);
			// Set color for pixel in bitmap
			bitmap2->Canvas->BeginScene();
			bitmap2->Canvas->Fill->Color = color;
			TRectF rect(j, i, j + 1, i + 1);
			bitmap2->Canvas->FillRect(rect, 0, 0, AllCorners, 1.0f);
			bitmap2->Canvas->EndScene();
		}
	}



			Image2->Bitmap->Assign(bitmap2);


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{


Image1->Bitmap = nullptr;

float sum_x=0.0,sum_y=0.0,sum_xy=0.0,sum_x2=0.0,sum_y2=0.0;

			for(int i=0;i<row;i++){
				for(int j=0;j<row;j++){
					sum_x = 0.0;
					sum_y = 0.0;
					sum_xy = 0.0;
					sum_x2 = 0.0;
					sum_y2 = 0.0;
					for(int k=0;k<col;k++){
						sum_x+=dataarr[i][k];
						sum_y+=dataarr[j][k];
						sum_xy+=dataarr[i][k]*dataarr[j][k];
						sum_x2+=dataarr[i][k]*dataarr[i][k];
						sum_y2+=dataarr[j][k]*dataarr[j][k];
					}
					float d=sqrt(((col*sum_x2)-(sum_x*sum_x))*((col*sum_y2)-(sum_y*sum_y)));
					pearsonarr[i][j]=(col*sum_xy-sum_x*sum_y)/d;
				}
			}

			meanarr = new float[row];

			for(int i=0;i<row;i++){
				sum=0.0;
				for(int j=0;j<row;j++){
					sum+=pearsonarr[i][j];
				}
				meanarr[i]=sum/row;
			}
			for(int x=0;x<row;x++){
				for(int a=0;a<row;a++){
					if(meanarr[x]<pearsonarr[a][x]){
						discretizearr[a][x]=1;
					}
					else{
						discretizearr[a][x]=0;
					}
				}
			}



	for (int i = 0; i < row; ++i) {
	for (int j = 0; j < row; ++j) {
		TAlphaColor color;
		if (discretizearr[i][j] == 1) {
			color = TAlphaColorRec::Black;
		} else {
			color = TAlphaColorRec::White;
		}
		bitmap->SetSize(row,row);
		bitmap->Canvas->BeginScene();
		bitmap->Canvas->Fill->Color = color;
		TRectF rect(j, i, j + 1, i + 1); // Create a rectangle for the pixel
		bitmap->Canvas->FillRect(rect, 0, 0, AllCorners, 1.0f); // Fill the rectangle with color
		bitmap->Canvas->EndScene();


	}

	}


			Image1->Bitmap->Assign(bitmap);











}

//---------------------------------------------------------------------------
void __fastcall TForm1::PermutateClick(TObject *Sender)
{


for(int x=0;x<row;x++){
	int r;
	r = rand() % row;
	float* temp = dataarr[x];
	dataarr[x]=dataarr[r];
	dataarr[r]=temp;
						}

ShowMessage("Permutated Successfully");

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBoxItem1Click(TObject *Sender)
{
	if (ListBox1->ItemIndex >= 0)
	{
		// Get the selected item from the ListBox and assign it to the TextBox
		TextBox->Text = ListBox1->Items->Strings[ListBox1->ItemIndex];
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBoxItem2Click(TObject *Sender)
{
      if (ListBox1->ItemIndex >= 0)
	{
		// Get the selected item from the ListBox and assign it to the TextBox
		TextBox->Text = ListBox1->Items->Strings[ListBox1->ItemIndex];
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBoxItem3Click(TObject *Sender)
{
   if (ListBox1->ItemIndex >= 0)
	{
		// Get the selected item from the ListBox and assign it to the TextBox
		TextBox->Text = ListBox1->Items->Strings[ListBox1->ItemIndex];
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClusterClick(TObject *Sender)
{




// clustering
float sigval[row];
float sum;
float temp[col];

for(int x=0;x<row;x++){
	sum=0.0;
	for(int y=0;y<col;y++){
		sum+=dataarr[x][y];
	}
	sigval[x]=(sum*sum)/col;
}

int temp2;
for(int x=0;x<row;x++){
	for(int y=x+1;y<row;y++){
		if(sigval[y]>sigval[x]){
			for(int z=0;z<col;z++){
				temp[z]=dataarr[x][z];
				dataarr[x][z]=dataarr[y][z];
				dataarr[y][z]=temp[z];
			}
				temp2 = sigval[y];
				sigval[y] = sigval[x];
				sigval[x] = temp2;
		}
	}
}





ShowMessage("Clustered!");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
ShowMessage("Thank you for using our code:\n Developers:\n Muhammad Shabih Ul Hassan 2023506\n Syed Ghazi Abbas 2023679");

delete bitmap;
delete bitmap2;

for (int i = 0; i < row; ++i) {
		delete[] dataarr[i];
		delete[] pearsonarr[i];
		delete[] discretizearr[i];
	}
	delete[] dataarr;
	delete[] pearsonarr;
	delete[] discretizearr;
	delete[] meanarr;
}
//---------------------------------------------------------------------------

