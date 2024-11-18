#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream fich1("cost_insert.txt");
    ofstream fich2("cost_delete.txt");
    ofstream fich3("cost_replace.txt");
    ofstream fich4("cost_transpose.txt");

    for (int i = 0; i < 26; ++i)
        fich1 << 1 << " ";
    for (int i = 0; i < 26; ++i)
        fich2 << 1 << " ";
    for (int i=0;i<26;i++) {
        for (int j=0;j<26;j++){
            if(j == i) fich3 << 0 << " ";
            else fich3 << 2 << " ";
        }
        fich3 << endl;
    }
    for (int i=0;i<26;i++) {
        for (int j=0;j<26;j++){
            if(j == i) fich4 << 0 << " ";
            else fich4 << 1 << " ";
        }
        fich4 << endl;
    }

    fich1.close();
    fich2.close();
    fich3.close();
    fich4.close();
}

//c++ generador_costos.cpp -o generador_costos
//generador_costos