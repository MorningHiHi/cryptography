#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int location[2000];
int sizeOfLoca;
void creLocaArr(int a[],int length ){
	for(int i=0;i<length;i++)
	a[i]=6;
}
void gomArr(int b[],int length,int indexRemove){		//ham xoa di mot phan tu trong mang
	if(indexRemove>=0 && indexRemove<length){
		for(int i=indexRemove;i<length-1;i++){
			b[i]=b[i+1];
		}
	}
}

void changeArr(int a[],int& length){		//ham tra ve mang chi co cac phan tu khacs nhau
	int j=0;
	while(j<length){
		int i=j+1; 		//dam bao viec so sanh bat dau tu phan tu ke tiep
		while(i<length){
			if(a[j] == a[i]){
				gomArr(a,length,i);
				length-=1;		//dam bao mang se bi giam di sau moi lan xoa cac phan tu trung lap
			}else {
				i++;
			}
		}
	j++;
	}
}
bool check(int x,int a[],int length){
	for (int i=0; i<length; i++){
		if(x==a[i]){
			return false;
		}
	}
	return true;
}
void ChangeKeyToInt(string key, int a[],int& tempt){
	int l=0;
	while (true){
		a[l]=key[l];
		if(l<key.size()){
			l++;
		}else{
			tempt=l;
			break;
		}
	}
}
void giveTextToMatrix(int textToInt[],int matrix[][5],int& tempt){
	int l=0;
	int a=97;
	for(int i=0;i<5;i++){
		for (int j=0;j<5;j++){
			if(l<tempt){
				matrix[i][j]=textToInt[l];
				l++;
				continue;
			}
			if((a<=122) && check(a,textToInt,tempt)){
				if(a==106){
					a++;	
				}
				matrix[i][j]=a;
				a++;
			}else{
				j--;
				a++;
			}
		}
	}
}
void output(int a[][5]){
	for(int i=0; i<5;i++){
		for (int j=0;j<5;j++){
			cout<<setw(20)<<left<<a[i][j];
		}
		cout<<endl;
	}
}
void xuatTextToInt(int a[],int length){
	for(int i=0; i<length; i++)
		cout<<setw(5)<<left<<a[i];
		cout<<endl<<endl;
}
void del32InArr(int a[],int& length){
	for (int i=0;i<length;i++){
		if(a[i]==32){
			gomArr(a,length,i);
			length--;
		}
		if(a[i]==106) a[i]=105;// doi ly tu 'j' qua ky tu 'i'
	}
}
void saveColRow(int a[],int length,int row,int col){//luu dia chi phan tu da ma hoa vao mang
	for (int i=0;i<(length-1);i+=2){
		if(a[i]==6){
			a[i]=row;
			a[i+1]=col;
			break;
		}
	}
}
void searchMatrix(int a[][5],int search){//tim kiem gia tri tuong ung trong ma tran
	for (int i=0 ;i<5;i++){
		for (int j=0 ;j<5;j++){
			if(a[i][j]==search){
				saveColRow(location,sizeOfLoca,i,j);//luu dia chi phan tu vao mang location
				break;
			}
		}
	}
}
void plusArr(int a[],int length,int indexplus){		//them ky tu 'x' vao mang khi co hai ky tu giong nhau
	if(indexplus>=0 && indexplus<length){
		for (int i=length;i>indexplus;i--){
			a[i]=a[i-1];
			if(i==indexplus+1){
				a[indexplus]=120;
			}
		}
	}
}
void similarChar(int a[],int& length){
	for (int i=0;i<length-1;i+=2){
		if(a[i]==a[i+1]){
			plusArr(a,length,i+1);
			length++;
		}
	}
}
void creCiphertext(int a[],int matrix[][5],int length,int b[]){
	int j=0;
	for (int i=0;i<length-3;i+=4){
		int d=a[i],f=a[i+1],g=a[i+2],h=a[i+3];
		if( d==g ){//hai phan tu cung mot hang
			a[i+1]=(a[i+1]+1)%5;
			a[i+3]=(a[i+3]+1)%5;	
			b[j]=matrix[a[i]][a[i+1]];
			b[j+1]=matrix[a[i+2]][a[i+3]];
			j+=2;
		}else if( f==h ){//hai phan tu cung mot côt
			a[i]=(a[i]+1)%5;
			a[i+2]=(a[i+2]+1)%5;
			
			b[j]=matrix[a[i]][a[i+1]];
			b[j+1]=matrix[a[i+2]][a[i+3]];
			j+=2;
		}else{// hai phan tu tao thanh duong cheo
			swap(a[i+1],a[i+3]);
//			int z=a[i+1]-a[i+3];
//			if(z>0){ a[i+1]-=z; a[i+3]+=z;}
//			else{ a[i+1]-=z; a[i+3]+=z; }
			
			b[j]=matrix[a[i]][a[i+1]];
			b[j+1]=matrix[a[i+2]][a[i+3]];
			j+=2;
		} 
	}
}
int main(){
	int matrix[5][5];
	int textToInt[1000];
	string key;
	cout<<"nhap vao khoa ma hoa: ";getline(cin,key);
	
	int tempt=0;
	ChangeKeyToInt(key,textToInt,tempt);
	
	// khiên cac phân tu trong không trùng lap
	changeArr(textToInt,tempt);
	
	//cout<<tempt<<endl;
	giveTextToMatrix(textToInt,matrix,tempt);
	
	xuatTextToInt(textToInt,tempt);//
	output(matrix);//
	
	string plaintext;
	cout<<"nhap vao ban ro: "; getline(cin,plaintext);
	tempt = plaintext.size() ;
	for(int i=0;i<tempt;i++){		//dua ban ro ve dang mang so nguyen
		textToInt[i]=plaintext[i];
	}
	
	xuatTextToInt(textToInt,tempt);//
	del32InArr(textToInt,tempt);		//xoa cac ky tu khoang trang-(space) trong mang
	similarChar(textToInt,tempt);		//chen ky tu 'x' neu gap hai ky tu cung khoi giong nhau
	if(tempt % 2 != 0){			//kiem tra sl phan tu co le hay khong neu
		textToInt[tempt]=97;	// neu co them vao ky tu 'a' owr cuoi mang
		tempt+=1;
	}
	
	sizeOfLoca=tempt*2;		// dac kich thuoc mang luu dia chi gap hai lan mang luu plaintext
	//khoi tao gia tri ban dau(6) cho mang luu dia chi cac phan tu trong ma tran
	creLocaArr(location,sizeOfLoca);
	for (int index=0;index<tempt;index++){
		searchMatrix(matrix,textToInt[index]);
	}
	xuatTextToInt(textToInt,tempt);//
	xuatTextToInt(location,sizeOfLoca);//
	
	int ciphertext[1000];
	creCiphertext(location,matrix,sizeOfLoca,ciphertext);
	xuatTextToInt(ciphertext,tempt);//
	for(int i=0;i<tempt;i++){		//dua ban ro ve dang mang so nguyen
		cout<<static_cast<char>(ciphertext[i]);
	}
}
