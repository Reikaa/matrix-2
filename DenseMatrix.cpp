/*
*   DenseMatrix.cpp
*   Written by Carson Woods and Dan Mailman
*   6/1/2018
*/

#include "DenseMatrix.h"

#include <iostream> //Imports cout

using namespace std;


DenseMatrix::~DenseMatrix() {                                   //Destructor
    delete[] Data;
}


DenseMatrix::DenseMatrix() {                                    //Default Constructor
    DenseMatrix(0,0);
}


DenseMatrix::DenseMatrix(size_t _R,size_t _C) :                 //Initializer constructor
    Rows(_R), Columns(_C), Data(new double[Rows*Columns]) {}


DenseMatrix::DenseMatrix(const DenseMatrix& _DM) {              //Copy Constructor
    this->Rows = _DM.Rows;
    this->Columns = _DM.Columns;
    this->Data = _DM.Data;
}


DenseMatrix::DenseMatrix(DenseMatrix&& _DM) {                   //Move Constructor
    //Moves resources to new DenseMatric object
    this->Rows = _DM.Rows;
    this->Columns = _DM.Columns;
    this->Data = _DM.Data;

    //Releases resources of Dense Matrix parameter
    _DM.Data = nullptr;
    _DM.Rows = 0;
    _DM.Columns = 0;

}

DenseMatrix::DenseMatrix(initializer_list< initializer_list<double> > _Il) { //Initializer List Constructor
    //Sets size of matrix based on size of _Il
    Rows = _Il.size(); //Gets row size from external iterator list size
    Columns= _Il.begin()->size(); //Gets column size from internal iterator list size
    Data = new double[Rows*Columns];

    //Define indices for data
    size_t R(0), C(0);

    //Iterates through __Il and adds its data to proper location in Data
    for (auto iRow(_Il.begin()); iRow != _Il.end(); ++iRow) {
        for (auto iElement(iRow->begin()); iElement != iRow->end(); ++iElement) {
            (*this)(R,C) = *iElement;
            C++;
        }
        R++;
        C = 0;
    }
}


//Gets data[index] at (Row,Column) location in Data
const size_t DenseMatrix::Index(const size_t _R, const size_t _C) const { return (_R*Columns)+_C; }


/*
*     ** Overloaded Operators **
*/

//Overloads assignment operator for copy
DenseMatrix& DenseMatrix::operator=(const DenseMatrix &_RHS) {
    //Checks for self assignment
    if (&_RHS == this) {
        return *this;
    }

    //Checks for dimensinal mismatch
    if (!((this->Rows == _RHS.Rows && this->Columns == _RHS.Columns))) {
        //If it occures Data is cleared then resized.
        delete[] Data;
        this->Rows = _RHS.Rows;
        this->Columns = _RHS.Columns;
        Data = new double[Rows*Columns];
    }

    //Populates this->Data with data from parameter
    for (size_t iElement(0); iElement < (Rows*Columns); iElement++) {
        Data[iElement] = _RHS.Data[iElement];
    }
    return *this;
}

//Overloads assignment operator for move
DenseMatrix& DenseMatrix::operator=(DenseMatrix&& _DM) {
    if (this != &_DM) {
        delete[] Data; //Ensures Data is clear before proceeding

        Data = _DM.Data;
        Rows = _DM.Rows;
        Columns = _DM.Columns;

        //Releases resources of Dense Matrix parameter
        _DM.Data = nullptr;
        _DM.Rows = 0;
        _DM.Columns = 0;
    }
    return *this;
}

//Overloads multiplication operator
DenseMatrix DenseMatrix::operator*(const DenseMatrix& RHS) const  {
    const DenseMatrix &LHS(*this);

    //Test for dimensional mismatch
    if (((LHS.Columns != RHS.Rows))) {
        printf("Error: Columns of LHS and Rows of RHS must Match.\n");
        printf("Current Columns: %ld\n",LHS.Columns);
        printf("Current Rows: %ld\n",RHS.Rows);
        return DenseMatrix();
    }

    DenseMatrix RET(LHS.Rows,RHS.Columns);

    double Sum = 0;

    for (size_t iRow(0); iRow < LHS.Rows; iRow++) {
        for (size_t iCol(0); iCol < RHS.Columns; iCol++) {
            Sum = 0;
            for (size_t iSum(0); iSum < RHS.Rows; iSum++) {
                Sum += LHS(iRow, iSum) * RHS(iSum,iCol);
            }
            RET(iRow, iCol) = Sum;
        }
    }
    return RET;
}

//Overloads << operator
ostream& operator<<(ostream& os, const DenseMatrix &DM) {
    os << "{";
    for (size_t R(0); R < DM.Rows; R++) {
        os << " ";
        os << "[";
        for (size_t C(0); C < DM.Columns; C++) {
            os << " " << DM(R,C);
        }
        if (R != DM.Rows-1) {
            os << " ]" << endl << " ";
        } else {
            os << " ]";
        }
    }
    os << " }";
    return os;
}