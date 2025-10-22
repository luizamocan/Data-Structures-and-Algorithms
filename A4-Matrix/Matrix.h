#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    int nrRows,nrCols;
    struct Triple {
        int row;
        int col;
        TElem value;
        Triple():row(-1),col(-1),value(NULL_TELEM){}
        Triple(int r, int c, TElem v):row(r),col(c),value(v){}
    };
    Triple* elements;
    int* flags; //0-empty 1-occupied 2-deleted
    int capacity;
    int size;
    double alpha=0.75;

    int hash(int row, int col, int i) const;
    void resizeAndHash();
    TElem search(int row, int col) const;
    TElem insert(int row, int col, TElem val);
    TElem remove(int row, int col);
public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    ~Matrix();

    void transpose();
    //transforms the current matrix into its own transpose(element from position i,j becomes element on position j,i
};
