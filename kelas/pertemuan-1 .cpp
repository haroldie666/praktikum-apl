// #include <iostream>

// using namespace std;

// int main() {
//     int tahun;

//     cout << "Masukkan tahun: ";
//     cin >> tahun;

//     if (tahun % 400 == 0) {
//         cout << tahun << " adalah tahun kabisat" << endl;
//     } 
//     else if (tahun % 100 == 0) {
//         cout << tahun << " bukan tahun kabisat" << endl;
//     } 
//     else if (tahun % 4 == 0) {
//         cout << tahun << " adalah tahun kabisat" << endl;
//     } 
//     else {
//         cout << tahun << " bukan tahun kabisat" << endl;
//     }

//     return 0;
// }

#include <iostream>
using namespace std;

int main() {
    double harga;
    double total_belanja = 0;
    double diskon = 0;
    double total_akhir = 0;

    cout << "=== PROGRAM KASIR SEDERHANA ===" << endl;

    while (true) {
        cout << "Masukkan Harga Barang: Rp ";
        cin >> harga;

        if (harga == 0) {
            break; 
        }

        total_belanja += harga;
    }

    if (total_belanja > 100000) {
        diskon = total_belanja * 0.10;
    } else {
        diskon = 0;
    }

    total_akhir = total_belanja - diskon;
    
    cout << endl << "Total Belanja   : Rp " << total_belanja << endl;
    cout << "Diskon (10%)    : Rp " << diskon << endl;
    cout << "Total Akhir     : Rp " << total_akhir << endl;
    return 0;
}