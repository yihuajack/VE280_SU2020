/*
 * Lab2 Ex2 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct {
    // TODO: complete struct
    int ChineseScore;
    int MathScore;
    int EnglishScore;
    int TotalScore;
    char Name[16];
} Student;

int compare(const void* p1, const void* p2) {
    // TODO: complete compare function for qsort()
    return (*(Student*)p2).TotalScore - (*(Student*)p1).TotalScore;
}

int main() {
    // TODO: read input
    int i, n;
    cin >> n;
    Student student[n];
    for (i = 0; i < n; i++) {
        cin >> student[i].Name >> student[i].ChineseScore >> student[i].MathScore >> student[i].EnglishScore;
        student[i].TotalScore = student[i].ChineseScore + student[i].MathScore + student[i].EnglishScore;
    }
    // TODO: sort array with qsort()
    qsort(student, n, sizeof(Student), compare);
    // TODO: print result
    for (i = 0; i < n; i++) {
        cout << student[i].Name << " " << student[i].ChineseScore << " " << student[i].MathScore << " " << student[i].EnglishScore << endl;
    }
    return 0;
}