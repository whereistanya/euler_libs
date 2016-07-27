#include <assert.h>
#include <stdio.h>

#include "matrix.h"

using namespace std;

bool testSet() {
	cout << "testSet" << endl;
	Matrix i(2, 4);
	// 1 2 3 4
	// 5 6 7 8
	assert(i.set(0, 0, 1) == true);
	assert(i.set(0, 1, 2) == true);
	assert(i.set(0, 2, 3) == true);
	assert(i.set(0, 3, 4) == true);
  assert(i.set(1, 0, 5) == true);
  assert(i.set(1, 1, 6) == true);
  assert(i.set(1, 2, 7) == true);
  assert(i.set(1, 3, 8) == true);
	assert(i.get(1, 2) == 7);
	assert(i.get(0, 3) == 4);
}

bool testBulkSet() {
	cout << "testBulkSet" << endl;
	int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix m(3, 3);
	m.bulkset(values, 9);
	assert(m.get(0, 0) == 1);
	assert(m.get(0, 1) == 2);
	assert(m.get(0, 2) == 3);
	assert(m.get(1, 0) == 4);
	assert(m.get(2, 1) == 8); 
	Matrix n(4, 1);
	n.Silent(true);
	assert(n.bulkset(values, 9) == false);
	assert(n.set(0, 1, 7) == false);
	assert(n.get(0, 1) == -1);
	assert(n.set(2, 0, 7) == true); 
	assert(n.get(2, 0) == 7);
	return true;
}

bool testDotProduct() {
	cout << "testDotProduct" << endl;
	Matrix i(3, 1);
	int i_values[] = { 2, 4, 6 };
	i.bulkset(i_values, 3);
	Matrix j(3, 3);
	int j_values[] = { 3, 6, 9, 12, 15, 18, 21, 24, 27, 30 };
	j.bulkset(j_values, 9);
	Matrix k(3, 1);
	assert(j.DotProduct(&i, &k) == true);
	Matrix expected_result(3, 1);
	int result_values[] = { 36, 180, 432 };
	expected_result.bulkset(result_values, 3);
	assert(expected_result == k);
	return true;
}

bool testGaussianElimination() {
	cout << "testGaussianElimination" << endl;
	Matrix m(3, 4);
	// C++ is grooossssssss.
	m.bulkset((int[]){1, 1, 1, 1, 4, 2, 1, 8, 9, 3, 1, 27}, 12);
	//m.bulkset((int[]){5, 8, 11, 9, 3, 8, 4, 10, 1, 16, 4, 5}, 12);
	m.GaussianEliminate();
}

int main() {
	testSet();
  testBulkSet();
	testDotProduct();
	testGaussianElimination();
	return 0;

}
