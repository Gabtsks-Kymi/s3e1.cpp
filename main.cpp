#include <iostream>
#include <iomanip>
#include <exception>

using namespace std;

template<typename T>
class ChessBoardArray {
 public:
 class out_of_range: public exception {};
 
 protected:
 class Row {
 public:
 
 Row(ChessBoardArray &a, int i):ChessRowArray(a), row(i){};
 
 int & operator [] (int i) const{
    return ChessRowArray.select(row, i)
 };
 
 private:
 int row;
 ChessBoardArray &ChessRowArray;
 };

 class ConstRow {
   public:
 
 ConstRow(const ChessBoardArray &a, int i):ChessRowArray(a), row(i){};
 
 int operator [] (int i) const{
    return ChessRowArray.select(row, i)
 };
 
 private:
 int row;
 const ChessBoardArray &ChessRowArray;
 };
 
 T *data;
 int Base_Row, Base_Col;
 unsigned Size_Row, Size_Col;
 
 unsigned int loc(int i, int j) const throw(out_of_range){
   
   int di = i - Base_Row;
   int dj = j - Base_Col;
   
   if((di < 0) || (di > Size_Row) || (dj < 0) || (dj > Size_Col))
     throw out_of_range("Invalid Number");
   else if((di%2 != 0) || (dj%2 != 0))
     throw out_of_range("Invalid Number"); 
   else   
   return (((di - 1)(dj/2 + dj%2[(di+1)%2])) + dj/2);
 };

 public:
 
 ChessBoardArray(unsigned size = 0, unsigned base = 0): 
 data (new T[size]), Base_Row(base), Base_Col(base), 
 Size_Row(size), Size_Col(size){
   for(unsigned i = 0; i < size; ++i){
     data[i] = 0;
   }
 };

 ChessBoardArray(const ChessBoardArray &a):
 data(new T[a.Size]), Size_Row(a.Size), Size_Col(a.Size),
 Base_Row(a.Base), Base_Col{};

 ~ChessBoardArray(){
   delete [] data;
 };

 ChessBoardArray & operator = (const ChessBoardArray &a){
   delete [] data;
   data = new T[a.Size];
   Size_Col = a.Size;
   Size_Row = a.Size;
   Base_Col = a.Base;
   Base_Row = a.Base;
   for(unsigned i = 0; i < a.Size; ++i)
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

 friend ostream & operator << (ostream &out, const ChessBoardArray &a);

 
 };
