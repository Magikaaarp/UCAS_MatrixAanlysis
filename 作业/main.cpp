#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
const int n = 4;

void PA_LU(double a[n][n], double b[n], double x[n]) {
    // PA = LU �ֽ⺯��
    int p[n]; for (int i = 0; i < n; i++) p[i] = i; // ����p ���ڼ�¼��λ�ñ任
    for (int pivot = 0; pivot < n; pivot++) {
        // �� pivot ��ѡ��Ԫ������ pivot �е���Ԫ��
        int col = pivot;
        int max_row = p[pivot];
        double max_val = 0;

        for (int i = pivot; i < n; i++) {
            int row = p[i];
            if (fabs(a[row][col]) > max_val) { // ����ֵ�����Ǹ���ѡΪ��Ԫ
                max_val = fabs(a[row][col]);
                max_row = i;// ��¼�±�, ֮�� p[i] ������ p[pivot] ����
            }
        }

        // �б任��¼������ p ��
        if (max_row != p[pivot]) {
            int tmp = p[pivot];
            p[pivot] = p[max_row];
            p[max_row] = tmp;
        }

        cout << "��ѡ��Ԫ�������";
        for (int x : p)cout << x << "\t";
        cout << endl << endl << "��ѡ��Ԫ��ľ���" << endl;
        // ѡȡ��Ԫ��ִ����ȥ����
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << setw(14) << fixed << setprecision(10) << a[p[i]][j] << "\t";
            cout << endl;
        }
        cout << endl;

        // ��ʼ��ȥ
        int p_row = p[pivot];//��Ԫ������
        int p_col = pivot; // ��Ԫ������

        for (int i = pivot + 1; i < n; i++) {
            int row = p[i];
            double  s = a[row][p_col] / a[p_row][p_col];
            for (int col = pivot + 1; col < n; col++)
                a[row][col] -= a[p_row][col] * s; // ��������������
            a[row][p_col] = s;                    // ��������������
        }

        cout << "��ȥ��" << endl;
        // ִ����ȥ��
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << setw(14) << fixed << setprecision(10) << a[p[i]][j] << "\t";
            cout << endl;
        }
        cout << endl;
    }

    // ��ȥ���LU����
    cout << "���յ�LU����Ϊ��" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(14) << fixed << setprecision(10) << a[p[i]][j] << "\t";
        cout << endl;
    }
    cout << endl;

    // ��� Ly=b 
    double y[n] = { 0,0,0,0 };
    for (int i = 0; i < n; i++) {
        int row = p[i];
        for (int col = 0; col < i; col++)
            b[row] -= a[row][col] * y[p[col]];
        y[row] = b[row];
    }

    // ��� Ux=y 
    for (int i = n - 1; i >= 0; i--) {
        int row = p[i];
        for (int col = n - 1; col >= i + 1; col--)
            y[row] -= a[row][col] * x[col];
        x[i] = y[row] / a[row][i];
    }
}

int main() {
    double A[n][n] = { {1,2,4,17},{3,6,-12,3},{2,3,-3,2},{0,2,-2,6} };
    double b[n] = { 17,3,3,4 };
    double x[n] = { 0,0,0,0 };
    PA_LU(A, b, x);
    // setw ��ռ�Ŀո���Ŀ
    // fixed������ͨ��ʽ���������, �����ǿ�ѧ������;
    // setprecision��������С������λ��
    cout << "������Ľ�xΪ:" << endl;
    for (int i = 0; i < n; i++)
        cout << setw(12) << fixed << setprecision(10) << x[i] << "\t";
    cout << endl;
    return 0;
}