using namespace std;

#include <assert.h>
#include <cmath>
#include <iostream>
#include <stdio.h>

class Matrix {
public:
	Matrix(int rows, int columns) {
		maxheight = rows;
		maxwidth = columns;
		data = new double[rows * columns];
		for (int i = 0; i < maxheight * maxwidth; i++) {
				data[i] = 0;
		}
		silent = false;
	}

	~Matrix() {
		delete[] data;
	}

	bool operator==(const Matrix& m) {
		for (int i = 0; i < maxheight * maxwidth; ++i) {
			if (data[i] != m.get(i)) {
				return false;
			}
		}
		return true;
	}
	ostream& operator<<(ostream& os) {
		for (int i = 0; i < maxwidth * maxheight; ++i) {
			if ((i != 0) && (i % maxwidth == 0)) printf("\n");
			os << data[i] << " ";
		}
		return os;
	}


	double get(int row, int column) const {
		if (InBounds(row, column)) {
			return data[column + row * maxwidth];
		}
		else {
			if (!silent) cout << "ERROR: Couldn't get " << row << ", " << column
				                << ": out of bounds" << endl;
			return -1;
		}
	}

	int get(int i) const {
		return data[i];
	}

	bool set(int row, int column, double value) {
		if (InBounds(row, column)) {
		 data[column + row * maxwidth] = value;
		 return true;
		} else {
			if (!silent) cout << "ERROR: Couldn't set " << row << ", " << column
				                << ": out of bounds" << endl;
			return false;
		}
	}

	bool bulkset(int* values, int count) {
		if (count > (maxheight * maxwidth)) {
			if (!silent) cout << "ERROR: too many values for matrix (" << count
				                << " vs " << maxheight * maxwidth << ")" << endl;
			return false;
		}
		for (int i = 0; i < count; ++i) {
			data[i] = values[i];
		}
		return true;
	}

	int width() {
		return maxwidth;
	}

	int height() {
		return maxheight;
	}

	void Print() {
		for (int i = 0; i < maxwidth * maxheight; ++i) {
			if ((i != 0) && (i % maxwidth == 0)) printf("\n");
			printf("%.4f ", data[i]);
		}
		printf("\n\n");
	}

	bool DotProduct(Matrix* multiplicant, Matrix* result) {
		// TODO: only good for multiplying by an Nx1 matrix.
		if (maxheight != multiplicant->height()) {
			if (!silent) cout << "ERROR: can't multiply matrices of different "
				                << "heights (" << maxheight << " vs "
												<< multiplicant->height() << ")" << endl;
			return false;
		}
		if (multiplicant->width() != 1) {
			if (!silent) cout << "ERROR: multiplier matrix should have width 1 (got "
			                  << multiplicant->width() << ")" << endl;
			return false;
		}
		if (maxheight != result->height()) {
			if (!silent) cout << "ERROR: result matrix is the wrong height ( got "
				                << result->height() << ", need " << height() << ")" << endl;
			return false;
		}
		if (result->width() != 1) {
			if (!silent) cout << "ERROR: result matrix should have width 1 (got "
				                << result->width() << ")" << endl;
			return false;
		}

		for (int h = 0; h < maxheight; ++h) {
			double output = 0;
			for (int w = 0; w < maxwidth; ++w) {
				output += get(h, w) * multiplicant->get(h, 0);
			}
			result->set(h, 0, output);
		}
		return true;
	}

	bool GaussianEliminate() {
		// Puts the matrix into row-echelon form, where it can be solved by
		// back-substitution.
		// Transformation is performed in-place, i.e., this matrix is destroyed.
		// Algorithm from http://en.wikipedia.org/wiki/Gaussian_elimination
		Matrix backup(maxheight, maxwidth);
		backup.bulkset((int*)data, maxwidth * maxheight);
		for (int k = 0; k < maxheight; ++k) { // for each column/row (following the diagonal)
			// pivot is the biggest value for the column, ignoring rows above this row.
			int max = 0;
			int maxrow = k;
			for (int r = k; r < maxheight; ++r) {
				int value = abs(get(r, k));
				if (value > max) {
					maxrow = r;
					max = value;
				}
			}
			if (get(maxrow, k) == 0) {
				cout << "ERROR: Matrix is singular! Can't eliminate." << endl;
				return false;
			}

			// swap pivot row with this row
			double tmp;
			for (int i = 0; i < maxwidth; ++i) {
				tmp = get(maxrow, i);
				double tmp2 = get(k, i);
				set(maxrow, i, tmp2);
				set(k, i, tmp);
			}

			for (int i = k + 1; i < maxheight; ++i) { // For all rows below the pivot row
				double ik = get(i, k); // we'll change this in a minute, so save it
				for (int j = k; j < maxwidth; ++j) {
					double reduce_by = get(k, j) * ik / get(k, k);
					set(i, j, get(i, j) - reduce_by);
				}
				set(i, k, 0);
			}
		}
		return true;
	}

	void Silent(bool is_silent) {
		// Useful for unit tests
		silent = is_silent;
	}

private:
	bool InBounds(int row, int column) const {
		if ((row < 0) || (column < 0)) {
			if (!silent) cout << "ERROR: less than zero" << endl;
			return false;
		}
		if (column >= maxwidth) {
			if (!silent) cout << "ERROR: column " << column << " is out of bounds ("
				                << maxwidth << ")." << endl;
			return false;
		}
		if (row >= maxheight) {
			if (!silent) cout << "ERROR: row " << row << " is out of bounds (" << maxheight
				                << ")." << endl;
		}
		return true;
	}

	int maxwidth, maxheight;
	double* data;
	bool silent;
};
