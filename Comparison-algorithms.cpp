#include <iostream>
#include <fstream>
#include <ostream>
#include <string.h>

using namespace std;


void insertionsort(int *a, int count);
void mergesort(int *a, int*b, int low, int high);
void merge(int *a, int *b, int low, int middle, int high);
void quicksort(int *A, int p, int r);
int partion(int*A,int p, int r);
void countsort(int *A,int *B, int count, int highest);

void whichsort(int*a,int count,char*b, bool*errorchk);
void arraylength(int*count, char*temp, bool*errorchk);
void inputArray(int*array,char* filename);
void outputArray(int*array, int arraylength, char*outType);
void error(int errornum);

int highestnumber(int *A, int count);



int main(int atgc, char*argv[]){
	int count =0;
	bool errorchk = true;
	argv[1] = "input";
	argv[2] = "counting";
	argv[3] = "nodup";

	arraylength(&count, argv[1], &errorchk);// this will count the number of integers in the file

	int numberarray[count];// create an empty array of length "count"

	if (errorchk){
	inputArray(numberarray, argv[1]);
	whichsort(numberarray,count,argv[2], &errorchk);
		if (errorchk){
			outputArray(numberarray, count, argv[3]);
		}
	}

	return 0;

}
void arraylength(int*count, char*b, bool*errorchk){
	fstream txtfile(b);
	if (txtfile.is_open()){
		int temp, tempcount=0;
		while (!txtfile.eof()){
			txtfile >> temp;
			tempcount++;
		}
		*count = tempcount;
		txtfile.close();
	}
	else {
		*errorchk = false;
		error(1);
	}

}
void inputArray(int*array,char*filename){
	fstream txtfile(filename);
	if (txtfile.is_open()){
		int i=0;
		while (!txtfile.eof()){
			txtfile >> array[i];
			i++;
		}
	}
	else {
		error(1);
	}
	txtfile.close();
}
void outputArray(int*array, int arraylength, char*outType ){

	ofstream sortedtxt("output-numbers");
	if (strcmp(outType,"dup")==0){
		for (int i =0; i<arraylength; i++){
			sortedtxt<<array[i]<<endl;
		}
		return;
	}
	if(strcmp(outType,"nodup")==0){
		sortedtxt<<array[0]<<endl;
		for (int i = 1; i < arraylength; i++){
			if (array[i]!= array[i-1])
				sortedtxt<<array[i]<<endl;
		}
		return;
	}
	else{
		error(3);
	}
    	sortedtxt.close();
}

void insertionsort(int *a, int count){
	//insertion sort of numberarray[]
		int j, temp;
		for (int i = 0;i<count;i++){
			j = i;
			while (j>0 && a[j-1] > a[j]){
				temp = a[j];
				a[j] = a[j-1];
				a[j-1]=temp;
				j--;
			}
		}
}
void merge(int *a, int *b, int low, int middle, int high){

	int h,i,j;
	h=low;
	i=low;
	j=middle+1;

	while((h<=middle)&&(j<=high)){
		if(a[h]<=a[j]){
			b[i]=a[h];
			h++;
		}
		else{
			b[i]=a[j];
			j++;
		}
		i++;
	}
	if(h>middle) {
		for(int k=j; k<=high; k++){
			b[i]=a[k];
			i++;
		}
	}
	else {
		for(int k=h; k<=middle; k++){
			b[i]=a[k];
			i++;
		}
	}
	for(int k=low; k<=high; k++)
		a[k]=b[k];
}
void mergesort(int *a, int*b, int low, int high){
int middle;
	if(low<high){
		middle=(low+high)/2;
		mergesort(a,b,low,middle);
		mergesort(a,b,middle+1,high);
		merge(a,b,low,middle,high);
	}
}

void swap(int i,int j, int *A){
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

int partion(int*A,int p, int r){

	int pivot = A[r];
	int i = p-1;
	for (int j = p; j < r ; j++){
		if (A[j] <= pivot){
			i= i+1;
			swap(i,j,A);
		}
	}
	swap(i+1,r,A);

	return i+1;
}
void quicksort(int *A, int p, int r){
	int q;
	if (p<r){
		q = partion(A, p, r);
    		quicksort(A,p,q-1);
    		quicksort(A,q+1,r);
    	}
}
void countsort(int *A, int *B,int count, int highest){
	int C[highest];
	cout<< highest << "highest\n"<< count << "count\n";

	for (int i = 0; i < count; i++){
		C[i]=0;
	}
	for (int i = 0; i < count; i++){
		C[A[i]] = C[A[i]] + 1;
	}
	for (int i = 1; i < highest; i++){
		C[i] = C[i] + C[i-1];
		cout << C[i]<< endl;
	}
	for (int i = (count-1); i > -1; --i){
		B[C[A[i]]] = A[i];
		cout << " B "<< i << "  " << A[i] << " A "<< endl;
		C[A[i]]= (C[A[i]]-1);
	}
	for (int i = 0; i < count; i++){
		cout << B[i] << " B array \n";
		A[i] = B[i];
		cout << A[i] << " A array \n";
	}
}
void whichsort(int*a, int count,char*b, bool*errorchk){
	if(strcmp(b,"insert")==0||strcmp(b,"merge")==0||strcmp(b,"quick")==0||strcmp(b,"counting")==0){
		if(strcmp(b,"merge")==0){
			int i[count];
			mergesort(a,i,0,count-1);
			cout<< "done by mergesort \n";
		}
		if(strcmp(b,"insert")==0){
			insertionsort(a, count);
			cout<<"done by insertion sort"<< endl;
		}
		if(strcmp(b,"quick")==0){
			int i =0;
			quicksort(a,i,(count-1));
			cout<<"done by quick sort"<< endl;
		}
		if(strcmp(b,"counting")==0){
			int temparray[count];
			countsort(a,temparray,count, highestnumber(a, count));
			cout<<"done by counting sort"<<endl;
		}
	}

	else {
		*errorchk = false;
		error(2);
	}
}
int highestnumber(int *a, int count){
	int highest = a[0];
	for (int i = 1; i < count; i++){
			if (highest < a[i])
				highest = a[i];
	}

	return highest;
}
void error(int errornum){
	if (errornum == 1)
		cout << "Error in command 1 - No file exists by that name current, please check file names that are listed in your folder" << endl;
	if (errornum == 2)
		cout << "Error in command 2 - No sort function exists with that name, current names are insert, merge, quick,and counting" << endl;
	if (errornum == 3)
		cout << "Error in command 3 - Do you want Duplicates or Not in the output file, commands are dup (duplicates) or nodup (noduplicates)" << endl;
}
