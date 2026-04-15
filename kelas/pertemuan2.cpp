#include <iostream>
#include <string>

using namespace std;

struct menu {
    string nama;
    int harga;
    bool ada;
};

int main() {
    menu daftarMenu[3] = {
        {"Nasi Goreng", 15000, true}, 
        {"Mie Ayam", 12000, true},    
        {"Es Teh", 5000, false}       
    };

    cout << "=== DAFTAR MENU KANTIN KAMPUS ===" << endl;

    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". Nama Menu : " << daftarMenu[i].nama << endl;
        cout << "   Harga     : Rp" << daftarMenu[i].harga << endl;
        cout << "   Status    : ";
        if (daftarMenu[i].ada == true) {
            cout << "ada" << endl;
        } 
        else {
            cout << "Habis" << endl;
        }
    }
}