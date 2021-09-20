/**
 * Header file for table
 * 
 * Author: Bradley Henderson
*/

#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <cstdlib>
#include <iostream>

using namespace std;

template<typename T>
class Table
{
    //Output
    template <typename S>
    friend ostream& operator<<(ostream&, const Table<S>&);
    
    //friend Table<T> operator+(const Table<T>&, const T(*)(T));
    friend Table<T> operator+(const Table<T>&, T (*)(T));
    /*{
      Table<T> newTable(oldTable.rowCount, oldTable.columnCount);
      for(int row = 0; row < newTable.rowCount; row++)
      {
        for(int column = 0; column < newTable.columnCount; column++)
        {
          newTable.qTable[row][column] = f(oldTable.qTable[row][column]);
          //newTable(row,column) = f(oldTable(row,column));
          //newTable(row, column = &f(oldTable[row][column]));
        }
      }

      return newTable;
    }*/

    public:
        /*Table<T> operator+(const Table<T>& oldTable, T(*f)(T))
        {
          Table<T> newTable(oldTable.rowCount, oldTable.columnCount);

          for(int row = 0; row < newTable.rowCount; row++)
          {
            for(int column = 0; column < newTable.columnCount; column++)
            {
              newTable.qTable[row][column] = f(oldTable.qTable[row][column]);
            }
          }

          return newTable;
        }*/

        Table(int, int);
        explicit Table(int);
        Table(Table&);
        Table& operator=(const Table&);
        ~Table();

        int get_rows();
        int get_cols();

        Table<T> append_rows(const Table<T>&);
        Table<T> append_cols(const Table<T>&);

        T& operator()(int, int);
        Table<T> operator()(int, int, int, int);
    private:
        int rowCount;
        int columnCount;
        T** pTable;
};

#endif