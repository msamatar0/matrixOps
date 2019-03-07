#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#define idx i * col + j
using namespace std;

class mexp{
	string m;
public:
	mexp(int a){
		m = a == 0 ?
			"Cannot add matrices - sizes unequal" : a == 1 ?
			"Cannot subtract matrices - sizes unequal" :
			"Cannot multiply matrices - incompatible";
		m += "\n";
	}
	string what(){ return m; }
};
template <typename t> class matrix{
	vector<t> elem;
	int row = 0, col = 0, size = 0;
public:
	matrix(){}
	matrix(const matrix& m) : row(m.row), col(m.col), size(m.size){
		for(int i = 0; i < m.size; ++i)
			elem.push_back(m.elem[i]);
	}
	matrix(int){
		string s;
		stringstream ss;
		cout << "Enter Matrix elements, type \";\" to end\n";
		int c = 0, i = 0;
		do{
			cout << "Enter element of row " << row + 1 << ": ";
			getline(cin, s);
			ss << s;
			if(s == ";") break;
			for(t a; !ss.eof(); ++c){
				ss >> a;
				elem.push_back(a);
			}
			ss.clear();
			if(i == 0){
				col = c;
				i++;
			}
		}while(row++ < 8);
		size = row * col;
		cout << endl;
	}
	matrix operator+(matrix &m) const{
		matrix x;
		try{
			if(row != m.row || col != m.col) throw mexp(0);
		}
		catch(mexp m){
			cerr << m.what();
			return x;
		}
		x.elem.reserve(size);
		x.col = col;
		x.row = row;
		x.size = size;
		for(int i = 0; i < row; ++i)
			for(int j = 0; j < col; ++j)
				x.elem.push_back(elem[idx] + m.elem[idx]);
		return x;
	}
	matrix operator-(matrix &m) const{
		matrix x;
		try{
			if(row != m.row) throw mexp(1);
		}
		catch(mexp m){
			cerr << m.what();
			return x;
		}
		x.elem.reserve(size);
		x.col = col;
		x.row = row;
		x.size = size;
		for(int i = 0; i < row; ++i)
			for(int j = 0; j < col; ++j)
				x.elem.push_back(elem[idx] - m.elem[idx]);
		return x;
	}
	matrix operator*(matrix &m) const{
		matrix x;
		try{
			if(row != m.col) throw mexp(777);
		}
		catch(mexp m){
			cerr << m.what();
			x.row = 0;
			x.col = 0;
			x.size = 0;
			return x;
		}
		x.elem.reserve(size);
		x.size = row * m.col;
		x.row = row;
		x.col = m.col;
		for(int i = 0; i < row; ++i)
			for(int j = 0; j < m.col; ++j)
				for(int k = 0; k < col; ++k)
					x.elem.push_back(elem[i * col + k] * m.elem[k * m.row + j]);
		return x;
	}
	void transpose(){
		vector<t> temp;
		temp.reserve(size);
		int r = col, c = row;
		for(int i = 0; i < row; ++i)
			for(int j = 0; j < col; ++j)
				temp.push_back(elem[i * col + j]);
		for(int i = 0; i < size; ++i)
				elem[i] = temp[i];
		row = r;
		col = c;
		cout << endl << *this;
	}
	friend ostream& operator<<(ostream &mout, matrix &m){
		for(int i = 0; i < m.row; ++i)
			for(int j = 0; j < m.col; ++j)
				mout << m.elem[i * m.col + j] << (j == m.col - 1 ? "\n" : " ");
		return mout << endl;
	}
};