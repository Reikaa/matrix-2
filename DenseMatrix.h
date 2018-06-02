/*
*   DenseMatrix.h
*   Written by Carson Woods and Dan Mailman
*   6/1/2018
*/

#include <iostream> //cout

using namespace std;

class DenseMatrix {
    protected:
        size_t Rows,Columns;
        double *Data;

    public:
        //default AND initializer constructor
        DenseMatrix(size_t _R=0,size_t _C=0) :
            Rows(_R), Columns(_C), Data(new double[Rows*Columns]) {}

        //initializer_list constructor
        DenseMatrix(initializer_list< initializer_list<double> > _Il) {
            //sets size of matrix based on size of _Il
            Rows = _Il.size();
            Columns= _Il.begin()->size();
            Data = new double[Rows*Columns];

            //define indices for data
            size_t R(0), C(0);

            //iterates through __Il and adds its data to proper location in Data
            for (auto iRow(_Il.begin()); iRow != _Il.end(); ++iRow) {
                for (auto iElement(iRow->begin()); iElement != iRow->end(); ++iElement) {
                    (*this)(R,C) = *iElement;
                    C++;
                }
                R++;
                C = 0;
            }
        }

        //clears data when object leaves scope
        virtual ~DenseMatrix() {delete[] Data;}


        /*
        *     ** Overloaded Operators **
        */

        //overloads assignment operator
        DenseMatrix& operator=(const DenseMatrix &_RHS) {
            //checks for self assignment
            if (&_RHS == this) {
                return *this;
            }

            //checks for dimensinal mismatch
            if (!((this->Rows == _RHS.Rows && this->Columns == _RHS.Columns))) {
                //if it occures Data is cleared then resized.
                delete[] Data;
                this->Rows = _RHS.Rows;
                this->Columns = _RHS.Columns;
                Data = new double[Rows*Columns];

            }

            //populates this->Data with data from parameter
            for (size_t iElement(0); iElement < (Rows*Columns); iElement++) {
                Data[iElement] = _RHS.Data[iElement];
            }

            return *this;
        }

        //overloads () operator for assigning a certain value at a certain location
        double& operator()(size_t _R, size_t _C) {
            return Data[(_R*Columns)+_C];
        }

        //overloads () operator for retrieving a const value at a certain location
        const double& operator()(size_t _R, size_t _C) const {
            return Data[(_R*Columns)+_C];
        }

        friend ostream& operator<<(ostream& os, const DenseMatrix &DM) {
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
                    os << " ]" << " }";
                }
            }
            return os;
        }
};