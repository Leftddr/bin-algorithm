#include <stdio.h>
#include <Windows.h>
#include <string.h>
#pragma warning(disable:4996)

struct nodetype {
	char key[100];
	nodetype* left;
	nodetype* right;
};
struct tree {
	nodetype*root;
};

nodetype* p;
tree t;
float A[100][100];
int R[100][100];
char key[100][100] = { {NULL}, {"CASE"},{"ELSE"},{"END"},{"IF"},{"OF"},{"THEN"} };
float p1[7] = { NULL, 0.05,0.15,0.05,0.35,0.05,0.35 };

void search(char *);
void optsearchtree(int);
float sum(int, int);
nodetype* tree1(int, int);

int main() {
	int n = sizeof(p1) / sizeof(float);
	char p[100] = "END";
	optsearchtree(n);
	tree1(1, 6);
	printf("\n");
	search(p);
	system("pause");
	return 0;
}

void search(char *keyin) {
	bool found;
	p = t.root;
	found = false;
	while (!found) {
		if (strcmp(p->key, keyin) == 0) {
			printf("p->key = %s\n", p->key); found = true;
		}
		else if (strcmp(p->key, keyin) > 0) p = p->left;
		else p = p->right;
	}
}

void optsearchtree(int n) {
	int i, j, k, diagonal;
	float min;
	for (i = 1; i <= n; i++) {
		A[i][i - 1] = 0; A[i][i] = p1[i]; R[i][i] = i; R[i][i - 1] = 0; A[0][i - 1] = NULL; R[0][i - 1] = NULL;
	}
	A[n + 1][n] = 0; R[n + 1][n] = 0; A[0][n] = NULL; R[0][n] = NULL;
	for (diagonal = 1; diagonal <= n - 1; diagonal++)
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			if (i == j) { A[i][j] = p1[i]; continue; }
			min = A[i][i - 1] + A[i + 1][j] + sum(i, j);
			for (k = i; k <= j; k++) {
				if (min >= A[i][k - 1] + A[k + 1][j] + sum(i, j)) {
					min = A[i][k - 1] + A[k + 1][j] + sum(i, j);
					R[i][j] = k;
				}
				A[i][j] = min;
			}
		}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%.2f ", A[i][j]);
		}
		printf("\n");
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", R[i][j]);
		}
		printf("\n");
	}
}

float sum(int begin, int end) {
	float sum_total = 0;
	for (int i = begin; i <= end; i++) {
		sum_total += p1[i];
	}
	return sum_total;
}

nodetype* tree1(int i, int j) {
	int k;
	nodetype*p;
	k = R[i][j];
	if (k == 0) return NULL;
	else {
		p = new nodetype;
		strcpy(p->key, key[k]);
		p->left = tree1(i, k - 1);
		p->right = tree1(k + 1, j);
		printf("%s ", p->key);
		return t.root = p;
	}
}