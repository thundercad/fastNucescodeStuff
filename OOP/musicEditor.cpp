#include <iostream>
#include "wavfile.h"
using namespace std;
void menue()
{
	cout << endl;
	cout << "enter 2 to upsample\n";
	cout << "enter 3 to downsample\n";
	cout << "enter 4 to merge array\n";
	cout << "enter 5 to apply moving filter\n";
	cout << endl;
}
void print(unsigned char*&arr,int size)
{
	for (int i = 0;i < size;i++)
	{
		cout << arr[i];
	}
}
void allocateArray(unsigned char*& arr, int size)
{
	arr = new unsigned char[size];
}
void deallocateArray(unsigned char*& arr)
{
	delete[] arr;
}
void playfile(char* str) {
	if (playWavFile(str) == 0)
		cout << "Error: File not found!" << endl;
}
unsigned char* double_array(const unsigned char* arr, int& size) 
{
	unsigned char* doubled_arr = new unsigned char[size * 2];
	for (int i = 0; i < size; i++)
	{
		doubled_arr[2 * i] = arr[i];
		doubled_arr[2 * i + 1] = arr[i];
	}
	return doubled_arr;
}
unsigned char* shrink_array(const unsigned char* arr, int& size)
{
	unsigned char* shrunken_arr = new unsigned char[size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		shrunken_arr[i] = arr[2 * i];
	}
	return shrunken_arr;
}
//Sample function for reading and storing sound data
void read_data(char* str, unsigned char* &ptr,int& size,int &sampleRate) 
{
	readWavFile(str, ptr, size, sampleRate);
}
void FillWithMean(const unsigned char* in, unsigned char* out, int N, int size) 
{
	for (int i = 0; i < size; i++) 
	{
	   int sum = 0, count = 0;
	   int left = i - N, right = i + N;
	   while (left <= right)
	   {
		  if (left >= 0 && left < size)
		  {
		  sum += in[left];
		   count++;
		  }
				left++;
	   }
			out[i] = sum / count;
	}

}

unsigned char* mergeArray(const unsigned char* arr1, const int size1, unsigned char* arr2, const int size2)
{
	int size3 = size1 + size2;
	unsigned char*arr3 = new unsigned char[size3];
	int i = 0, j = 0, k = 0;

	while (i < size1 && j < size2) {
		arr3[k++] = arr1[i++];
		arr3[k++] = arr2[j++];
	}

	while (i < size1) {
		arr3[k++] = arr1[i++];
	}

	while (j < size2) {
		arr3[k++] = arr2[j++];
	}

	return arr3;
}
void mix_samples()
{
	unsigned char* pointer1 = nullptr;
    unsigned char* pointer2 = nullptr;
	unsigned char* mixedaudio = nullptr;
	int len1 = 300000, sr1 = 8000, sr2 = 8000;
	int len2 = 300000;
	char *f1 = new char[50];
	char* f2 = new char[50];
	allocateArray(pointer1, len1);
	allocateArray(pointer2, len2);
	allocateArray(mixedaudio, len1 + len2);
	cout << "enter the name of first file";
	cin >> f1;
	cout << "enter the name of second file";
	cin >> f2;
	cout << endl;
	readWavFile(f1, pointer1, len1, sr1);
	cout << endl;
	readWavFile(f2, pointer2, len2, sr2);

	char mix1[10] = "mix1.wav";
	char mix2[10] = "mix2.wav";
	mixedaudio = mergeArray(pointer1, len1, pointer2, len2);

	//with the sample rate of dhani
	writeWavFile(mix1, mixedaudio, len1, sr1);

	//with sample rate of sallimono
	writeWavFile(mix2, mixedaudio, len2, sr2);

	int choice = 0;
	cout << endl;
	cout << "choose the sample rate with which ypu want it to be played\n enter 1 to play with sample rate of dhani\nenter 2 to play with the sample rate of sallimono";
	cout << endl;
	cin >> choice;
	if (choice == 1)
	{
		playfile(mix1);;
	}

	if (choice == 2)
	{
		playfile(mix2);
	}

	deallocateArray(pointer1);
	deallocateArray(pointer2);
	deallocateArray(mixedaudio);

}

void upsamplearray(unsigned char*ptr,int& size,int sr)
{
	unsigned char* dodafa = double_array(ptr, size);
	char uparr[50] = "up.wav";
	int y = size * 2;
	writeWavFile(uparr, dodafa, y, sr);
	readWavFile(uparr, dodafa, y, sr);
	playfile(uparr);
	deallocateArray(dodafa);

}

void downsamplearr(unsigned char*ptr,int size,int sr)
{
	unsigned char* adhidafa = shrink_array(ptr, size);
	char downarr[10] = "down.wav";
	int y = size / 2;
	writeWavFile(downarr, adhidafa, y, sr);
	readWavFile(downarr, adhidafa, y, sr);
	playfile(downarr);
	deallocateArray(adhidafa);
}

void movingaveragefilter(unsigned char*ptr,int size,int sr)
{
	unsigned char* mean_in = new unsigned char[size];
	unsigned char* mean_out = new unsigned char[size];
	for (int i = 0;i < size;i++)
	{
		mean_in[i] = ptr[i];
	}
	char name1[20] = "move_1.wav";
	char name2[20] = "move_2.wav";
	char name3[20] = "move_3.wav";
	int x = 5;
	int y = 15;
	int z = 100;
	int option = 0;
	cout << "choose the value of n 5,15,100: ";
	cin >> option;
	if (option == 5)
	{
		FillWithMean(mean_in, mean_out, x, size);
		writeWavFile(name1, mean_out, size, sr);
		readWavFile(name1, mean_out, size, sr);
		playfile(name1);
	}

	if (option == 15)
	{
		FillWithMean(mean_in, mean_out, y, size);
		writeWavFile(name2, mean_out, size, sr);
		readWavFile(name2, mean_out, size, sr);
		playfile(name2);
	}

	if (option == 100)
	{
		FillWithMean(mean_in, mean_out, z, size);
		writeWavFile(name3, mean_out, size, sr);
		readWavFile(name3, mean_out, size, sr);
		playfile(name3);
	}

	deallocateArray(mean_in);
	deallocateArray(mean_out);
}





int main() {
	char str[50] = "";
	unsigned char* ptr = nullptr;
	int size = 10000000;
	int samplerate = 10000;
	bool flag = true;
	while (flag)
	{
		cout << "enter the name of the file with wav ot exit: ";
		cin >> str;
		int operation = 0;
		if (strcmp(str, "exit") != 0)
		{
			allocateArray(ptr, size);
			readWavFile(str, ptr, size, samplerate);
			playWavFile(str);
			menue();
			cin >> operation;
			if (operation == 2)
			{
				upsamplearray(ptr, size, samplerate);
			}

		    if (operation == 3)
			{
				downsamplearr(ptr, size, samplerate);
			}
			if (operation == 4)
			{
				mix_samples();
			}
			if (operation == 5)
			{
				movingaveragefilter(ptr, size, samplerate);
			}
		}
	}
	deallocateArray(ptr);
		

	return 0;
}

