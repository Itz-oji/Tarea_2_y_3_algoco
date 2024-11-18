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

int comparacion(int fin1, int fin2, string& S1, string& S2){
    if(fin1 == 0) return fin2;

    if(fin2 == 0) return fin1;

    if(S1[fin1 - 1] == S2[fin2 - 1]){
        return comparacion(fin1-1, fin2-1, S1, S2);
    }

    int costo_min = INT_MAX;
    
    if(fin1 > 1 && fin2 > 1 &&S1[fin1 - 2] == S2[fin2 - 1 ] && S1[fin1 -1 ] == S2[fin2 - 2]){
        costo_min = min(costo_min, comparacion(fin1-2,fin2-2,S1,S2) + costo_trans(S1[fin1-2],S1[fin1-1]));
    }
    
    costo_min =  min(costo_min, comparacion(fin1-1,fin2,S1,S2) + costo_del(S1[fin1-1]));
    costo_min = min(costo_min ,comparacion(fin1,fin2-1,S1,S2)+costo_ins(S2[fin2-1]));
    costo_min = min(costo_min, comparacion(fin1-1,fin2-1,S1,S2) + costo_sub(S1[fin1-1], S2[fin2-1]));

    return costo_min;
}

int edit(string& S1, string& S2){
    return comparacion(S1.size(),S2.size(), S1, S2);
}

int main (){

    ifstream fich1("cost_insert.txt");
    ifstream fich2("cost_delete.txt");
    ifstream fich3("cost_replace.txt");
    ifstream fich4("cost_transpose.txt");
    ifstream fich5("dataset1.txt"); //Cambiar numero de dataset para revisar otros datasets

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

    auto inicio_total = high_resolution_clock::now();
    while(true){
        if (!getline(fich5, S1)) break;
        if (!getline(fich5, S2)) break;
        cout<<"cadena 1 "<< S1<<endl;
        cout<<"cadena 2 "<< S2<<endl;
        auto inicio_par = high_resolution_clock::now();
        int resultado = edit(S1,S2);
        auto fin_par = high_resolution_clock::now();

        auto duracion_par = duration_cast<milliseconds>(fin_par - inicio_par).count();
        cout << "Resultado: " << resultado << endl;
        cout << "Tiempo para este par: " << duracion_par << " ms\n" << endl;
    }
    fich5.close(); 
    auto fin_total = high_resolution_clock::now();
    auto duracion_total = duration_cast<milliseconds>(fin_total - inicio_total).count();
    cout << "Tiempo total: " << duracion_total << " ms" << endl;

    return 0;
}

//c++ Bruto.cpp -o Bruto
//Bruto


// https://www.geeksforgeeks.org/edit-distance-dp-5/