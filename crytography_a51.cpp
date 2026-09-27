#include <iostream>
#include <cstdlib> // Thu vien cho h�m rand()
#include <ctime>   // Thu vien cho h�m time()
#include <cstring>
#include <string>
#include <iomanip>
#include <bitset>
#include <cmath>
using namespace std;

int x[19];
int y[22];
int z[23];
int k[1000];
int BinPlain[1000];
int BinCipher[1000];
//string cipherText;


// Ham sinh so ngau nhien trong doan [min, max]
int generateRandomNumber(int min_value, int max_value) {
    return min_value + rand() % (max_value + 1 - min_value);
}
void ranNum(int a[]){
	// Khoi tao seed cho h�m rand() dua tr�n thoi gian hien tai
    srand(static_cast<unsigned int>(time(0)));

    // Sinh v� xuat ra 5 so ngau nhien trong doan [0, 100]
    for(int i=0;i<23;i++){
    	a[i]=generateRandomNumber(0, 1);
	}
}
void output(int a[]){
	for (int i=0;i<23;i++)
	cout<<a[i];
}

void delSpace(string &s){
	int l=s.length();
	for (int i=0;i<l;i++){
		if(s[i]==' '){
			s.erase(i,1);
			l-=1;
		}
	}
}

int XoR(int x,int y){
	if ((x==0 && y==0)||(x==1 && y==1)) return 0;
	else return 1;
}

int maj(int x,int y,int z){
	return XoR(XoR(x,y),z);
}

void gom(int a[],int length){
	//if(j>=1&&j<length){
	
	for (int i=length-1;i>=1;i--){
		a[i]=a[i-1];
	}
	
}
void round(){
	int m = maj(x[8],y[10],z[10]);
	if (x[8]==m){
		int tx=maj(x[13],x[16],XoR(x[17],x[18]));
		gom(x,19);
		x[0]=tx;
	}
	if (y[10]==m){
		int ty=XoR(y[20],y[21]);
		gom(y,22);
		y[0]=ty;
	}
	if (z[10]==m){
		int tz=maj(z[7],z[20],XoR(z[21],z[22]));
		gom(z,23);
		z[0]=tz;
	}
}
void encrytion(string s){
	for(int i=0;i<(s.size()*8);i++){
		round();
		k[i]=maj(x[18],y[21],z[22]);
	}
	for(int i=0;i<(s.size()*8);i++){
		BinCipher[i]=XoR(BinPlain[i],k[i]);
	}
}
int binToChar(int &a){
	int n[8];
	for (int i=0;i<8;i++){
		n[i]=BinCipher[a];
		a++;
	}
	int b=0;
	int c=0;
	for(int i=7;i>=0;i--){
		if(n[i]==0){
			c++;
			continue;
		}
		b+= n[i]*pow(2,c);
		c++;
	}
	return b;
}
void output(int &a,string s){
	for(int i=0;i<s.size();i++){
		cout<<static_cast<char>(binToChar(a))<<" ";
	}
}
void binary(string c, int bin[]) { //chuyen ky tu ve m� nhi phan trong bang ma ascii
    for (int i = 7; i >= 0; --i) {  
        bin[i] = ((c[0] >> (7-i)) & 1) ;
    }
}
void giveBinToBinplain(int bin[], int &ind){ //ham dua chuoi nhi phan vao mang
	int j=ind;
	for(int i=0;i<8;i++){
		BinPlain[j] =bin[i];
		j++;
	}
	ind=j;
}
void changetoBin(string s,int bin[],int &j){
	for (int i=0;i<s.size();i++){
		/* tao ra mot chuoi 'c' voi do dai la 1, va ky tu dau tien cua chuoi d� l� k� tu thu i trong chuoi 's'*/
		string c(1,s[i]);
		binary(c,bin);
		giveBinToBinplain(bin,j);
		
	}
}

int main() {
	int bin[8];
	int saveIndex = 0;
	cout<<"nhap vao ban ro: ";
	string plaintext;
	getline(cin,plaintext);
	delSpace(plaintext);
	cout<<plaintext;
	ranNum(x);
	ranNum(y);
	ranNum(z);
	cout<<endl;
	changetoBin(plaintext,bin,saveIndex);
//	cout<<"\n";//
//	output(x);cout<<"\n";//
//	output(y);cout<<"\n";//
//	output(z);cout<<"\n";//
//	for(int i= 0;i<(plaintext.size()*8);i++){//
//		cout<<BinPlain[i];//
//	}//
	encrytion(plaintext);
	int a=0;
	cout<<"\n"<<"ket qua la: ";//
	output(a,plaintext);
	

    return 0;
}

