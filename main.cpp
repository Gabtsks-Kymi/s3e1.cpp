#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

template<typename T>
class ChessBoardArray {

 protected:
 class Row {
 public:
 
 Row(ChessBoardArray &a, int i):ChessRowArray(a), row(i){};
 
 int & operator [] (int i) const{
    return ChessRowArray.select(row, i);
 };
 
 private:
 int row;
 ChessBoardArray &ChessRowArray;
 };

 class ConstRow {
   public:
 
 ConstRow(const ChessBoardArray &a, int i):ChessConstRowArray(a), row(i){};
 
 int operator [] (int i) const{
    return ChessConstRowArray.select(row, i);
 };
 
 private:
 int row;
 const ChessBoardArray &ChessConstRowArray;
 };
 
 T *data;
 int Base_Row, Base_Col;
 unsigned Size_Row, Size_Col;
 
 unsigned int loc(int i, int j) const throw(out_of_range){
   
   int di = i - Base_Row;
   int dj = j - Base_Col;
   
   if((di < 0) || (di > Size_Row) || (dj < 0) || (dj > Size_Col) || ((di + dj)%2 != 0))
     throw out_of_range("Invalid Number");
   else {
   int temp1 = 0; 
   if(Size_Col%2!=0){
          for(int r = 1; r <= (di + 1); ++r)
            temp1+= Size_Col/2 + (Size_Col%2)*(r%2);
          
        }
        else
            temp1=(Size_Col + 1)/2;
   return temp1 + dj/2;
   }
 };

 public:
 
 ChessBoardArray(unsigned size = 0, unsigned base = 0): 
 data (new T[(size*size)/2 + (size*size)%2]), Base_Row(base), Base_Col(base), 
 Size_Row(size), Size_Col(size){
   int tempt = (size*size)/2 + (size*size)%2;
   for(unsigned i = 0; i < tempt; ++i){
     data[i] = 0;
   }
 };

 ChessBoardArray(const ChessBoardArray &a):
 data(new T[a.Size]), Size_Row(a.Size), Size_Col(a.Size),
 Base_Row(a.Base), Base_Col(a.Base){
   
   int tempt = (a.Size_Row*a.Size_Row)/2 + (a.Size_Row*a.Size_Row)%2;
   
   for(unsigned i = 0; i < tempt; ++i)
     data[i] = a.data[i];
 };

 ~ChessBoardArray(){
   delete [] data;
 };

 ChessBoardArray & operator = (const ChessBoardArray &a){
   delete [] data;
   data = new T[(a.Size*a.Size)/2 + (a.Size*a.Size)%2];
   Size_Col = a.Size;
   Size_Row = a.Size;
   Base_Col = a.Base;
   Base_Row = a.Base;
   for(unsigned i = 0; i < (a.Size*a.Size)/2 + (a.Size*a.Size)%2; ++i)
     data[i] = a.data[i];
   return *this;  
 }; 

 int & select(int i, int j){
   return data[loc(i, j)];
 };
 int select(int i, int j) const{
   return data[loc(i, j)];
 };


 const Row operator [] (int i){
   return Row(*this, i);
 };
 const ConstRow operator [] (int i) const{
   return ConstRow(*this, i);
 };

 friend ostream & operator << (ostream &out, const ChessBoardArray &a){
   int tempt = 0;
  for(int l = 0; l < a.Size_Row; ++l){
    for(int m = 0; m < a.Size_Col; ++m){
      if((l + m)%2 == 0)
      out <<  setw(4) << a.data[tempt];
     else
       out << setw(4) << 0;
  }
  out << endl;
  
  }

  return out;  
 };

 
 };

  int main(){
  ChessBoardArray<int> a(4, 1); // size 4x4, rows and columns numbered from 1
 a[3][1] = 42;
 a[4][4] = 17;
try { a[2][1] = 7; }
catch(out_of_range &e) { cout << "a[2][1] is blac" << endl; }
try { cout << a[1][2] << endl; }
catch(out_of_range &e) { cout << "and so is a[1][2]" << endl; }
 cout << a;
  return 0;

}

