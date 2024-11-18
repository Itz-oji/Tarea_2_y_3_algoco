#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace chrono;

int costo_delet[26];
int costo_insert[26];
int costo_susti[26][26];
int costo_transponer[26][26];

int costo_sub(char a, char b){
    int costo;
    costo = costo_susti[a - 'a'][b - 'a'];
    return costo;
}

int costo_ins(char b){
    int costo;
    costo = costo_insert[ b - 'a'];
    return costo;
}

int costo_del(char a){
    int costo;
    costo = costo_delet[a - 'a'];
    return costo;
}

int costo_trans(char a, char b){
    int costo;
    costo = costo_transponer[a - 'a'][b - 'a'];
    return costo;
}

int comparacion(string& S1, string& S2, vector<vector<int>>& matrix){

    int fin1 = S1.size(), fin2 = S2.size();

    for(int i=0;i<=fin1;++i)
        matrix[i][0] = i;
    for(int j = 0;j<=fin2; ++j)
        matrix[0][j] = j;

    for(int i=1; i<=fin1;++i){
        for(int j = 1; j<=fin2; ++j){
            if(S1[i - 1] == S2[j - 1])
                matrix[i][j] = matrix[i-1][j-1];
            else if( i > 1 && j > 1 && S1[i-2] == S2[j-1] && S1[i-1 ]==S2[j-2])
                matrix[i][j] = matrix[i-2][j-2] + costo_trans(S1[i-2],S1[i-1]); 
            else
                matrix[i][j] = min({matrix[i-1][j]+costo_del(S1[i-1]),matrix[i][j-1]+costo_ins(S2[j-1]), matrix[i-1][j-1] + costo_sub(S1[i-1], S2[j-1])});
        }
    }
    return matrix[fin1][fin2];
}

int main (){

    ifstream fich1("cost_insert.txt");
    ifstream fich2("cost_delete.txt");
    ifstream fich3("cost_replace.txt");
    ifstream fich4("cost_transpose.txt");
    ifstream fich5("dataset1.txt");

    if (!fich1.is_open()){
        cout << "Error al abrir cost_insert.txt\n";
        exit(EXIT_FAILURE);}
    if (!fich2.is_open()){
        cout << "Error al abrir cost_delete.txt\n";
        exit(EXIT_FAILURE);}
    if (!fich3.is_open()){
        cout << "Error al abrir cost_replace.txt\n";
        exit(EXIT_FAILURE);}
    if (!fich4.is_open()){
        cout << "Error al abrir cost_transpose.txt\n";
        exit(EXIT_FAILURE);}
    if (!fich5.is_open()){
        cout << "Error al abrir cost_transpose.txt\n";
        exit(EXIT_FAILURE);}

    int valor,i=0;
    while(fich1 >> valor){
        costo_insert[i] = valor;
        i++;
    }
    fich1.close();

    i=0;
    while(fich2 >> valor){
        costo_delet[i] = valor;
        i++;
    }
    fich2.close();

    for (int i=0;i<26;i++) {
        for (int j=0;j<26;j++){
            fich3>>costo_susti[i][j];
        }
    }
    fich3.close();

    for (int i=0;i<26;i++) {
        for (int j=0;j<26;j++){
            fich4 >> costo_transponer[i][j];
        }
    }
    fich4.close();

    string S1,S2;
    auto start_total = high_resolution_clock::now();

    while(true){
        if (!getline(fich5, S1)) break;
        if (!getline(fich5, S2)) break;
        cout<<"cadena 1 "<< S1<<endl;
        cout<<"cadena 2 "<< S2<<endl;
        vector<vector<int>> matrix(S1.size() + 1, vector<int>(S2.size() + 1));
        auto start_pair = high_resolution_clock::now();
        int resultado = comparacion(S1,S2,matrix);
        auto end_pair = high_resolution_clock::now();

        cout << "Resultado: " << resultado << endl;
        cout << "Tiempo para este par: " << duration_cast<milliseconds>(end_pair - start_pair).count() << " ms\n" << endl;
    }
    fich5.close();  
    auto end_total = high_resolution_clock::now();

    cout << "Tiempo total: " << duration_cast<milliseconds>(end_total - start_total).count() << " ms" << endl;
    return 0;
}

//c++ Dinamico.cpp -o Dinamico
//Dinamico