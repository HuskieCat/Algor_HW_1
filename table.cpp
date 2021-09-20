/*
  Implementation file for table class

  Takes in 1 or 2 int values and generates an empty table of eithor a square or retangle respectivly. There are various methods for manipluating the tables.

  KNOWN BUGS:
  1. operator<< says it refuses to take setw, however it does compile and work anyways

  Author: Bradley Henderson
*/

#include <cstdlib>
#include <iostream>
#include "table.h"


//Allows the user to print the table logically
template<typename T>
ostream& operator<<(ostream& out, const Table<T>& table)
{
  const int width = out.width();

  if(table.rowCount == 0)
    return out << "∅";
  else if(table.columnCount == 0)
    return out << "∅";

  for(int row = 0; row < table.rowCount; row++)
  {
    for(int column = 0; column < table.columnCount; column++)
    {
      out << setw(width) << table.pTable[row][column];
    }
    out<<endl;
  }
  return out;
}

//Allows the user to add anything to the table through a function
template<typename T>
Table<T> operator+(Table<T>& oldTable, T (*f)(T))
{
  Table<T> newTable(oldTable.rowCount, oldTable.columnCount);

  for(int row = 0; row < newTable.rowCount; row++)
  {
    for(int column = 0; column < newTable.columnCount; column++)
    {
      newTable(row, column) = f(oldTable(row, column));
    }
  }

  return newTable;
}

//Constructor that takes 2 integer inputs for table sizing
template<typename T>
Table<T>::Table(const int row, const int column)
{
  rowCount = row;
  columnCount = column;
  pTable = new T*[row];
  for(int i = 0; i < row; i++)
  pTable[i] = new T[column];
}

//Constructor that takes 1 integer input for table sizing
template<typename T>
Table<T>::Table(int dimensions)
{
  rowCount = dimensions;
  columnCount = dimensions;
  pTable = new T*[dimensions];
  for(int i = 0; i < dimensions; i++)
  pTable[i] = new T[dimensions];
}

//Copy constructor, copies one table to the next
template<typename T>
Table<T>::Table(Table<T>& newTable)
{
  pTable = new T*[newTable.rowCount];
  for(int row = 0; row < newTable.rowCount; row++)
  {
    pTable[row] = new T[newTable.columnCount];
    for(int column = 0; column < newTable.columnCount; column++)
    {
      pTable[row][column] = newTable.pTable[row][column];
    }
  }

  rowCount = newTable.rowCount;
  columnCount = newTable.columnCount;
}

//Allows the user to set one table equal to the other
template<typename T>
Table<T>& Table<T>::operator=(const Table<T>& newTable)
{
  //Erase the table
  for(int row = 0; row < rowCount; row++)
    delete[] pTable[row];
  delete[] pTable;

  pTable = new T*[newTable.rowCount];
  for(int row = 0; row < newTable.rowCount; row++)
  {
    pTable[row] = new T[newTable.columnCount];
    for(int column = 0; column < newTable.columnCount; column++)
    {
      pTable[row][column] = newTable.pTable[row][column];
    }
  }
  rowCount = newTable.rowCount;
  columnCount = newTable.columnCount;
  return *this;
}

//Destructor
template<typename T>
Table<T>::~Table()
{
  for(int row = 0; row < rowCount; row++)
    delete[] pTable[row];
  delete[] pTable;
  rowCount = 0;
  columnCount = 0;
}

//Allows the user to return the number of rows in the table
template<typename T>
int Table<T>::get_rows()
{
  return rowCount;
}

//Allows the user to return the number of columns in the table
template<typename T>
int Table<T>::get_cols()
{
  return columnCount;
}

//Allows the user to add rows to an existing table
template<typename T>
Table<T> Table<T>::append_rows(const Table<T>& oldTable)
{
  Table<T> newTable(rowCount + oldTable.rowCount, columnCount);

  int secondIndex = 0;
  for(int row = 0; row < newTable.rowCount; row++)
  {
    for(int column = 0; column < newTable.columnCount; column++)
    {
      if(row < rowCount)
      {
        newTable.pTable[row][column] = pTable[row][column];
      }
      else
      {
        newTable.pTable[row][column] = oldTable.pTable[secondIndex][column];
      }
    }
    if(row > rowCount)
      secondIndex++;
  }

  return newTable;
}

//Allows the user to add columns to an existing table
template<typename T>
Table<T> Table<T>::append_cols(const Table<T>& oldTable)
{
  Table<T> newTable(rowCount, columnCount + oldTable.columnCount);

  for(int row = 0; row < newTable.rowCount; row++)
  {
    int secondIndex = 0;
    for(int column = 0; column < newTable.columnCount; column++)
    {
      if(column < columnCount)
      {
        newTable.pTable[row][column] = pTable[row][column];
      }
      else
      {
        newTable.pTable[row][column] = oldTable.pTable[row][secondIndex];
        secondIndex++;
      }
    }
  }

  return newTable;
}

//Allows the user to get a value at specified cordinates in the table
template<typename T>
T& Table<T>::operator()(int row, int column)
{
  return pTable[row][column];
}

//Allows the user to get a sub-table based off the main table, inclusively
template<typename T>
Table<T> Table<T>::operator()(int row1, int column1, int row2, int column2)
{
  int newRowCount = abs(row1-row2)+1;
  int newColumnCount = abs(column1-column2)+1;
  Table<T> newTable(newRowCount, newColumnCount);

  //Checks for the biggest so it doesn't matter which way the cordinates are placed in
  int biggerRow = row2;
  int smallerRow = row1;
  int biggerColumn = column2;
  int smallerColumn = column1;

  if(row1 > row2)
  {
    biggerRow = row1;
    smallerRow = row2;
  }
  if(column1 > column2)
  {
    biggerColumn = column1;
    smallerColumn = column2;
  }

  for(int row = smallerRow; row < biggerRow+1; row++)
  {
    for(int column = smallerColumn; column < biggerColumn+1; column++)
    {
      newTable.pTable[row-smallerRow][column-smallerColumn] = pTable[row][column];
    }
  }

  return newTable;
}