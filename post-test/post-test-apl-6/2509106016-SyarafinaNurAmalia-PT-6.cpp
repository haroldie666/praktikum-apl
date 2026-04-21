#include <iostream>
#include <conio.h>
#include <limits>
#include <algorithm> 
#include <cctype> 
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

struct kadaluarsa {
    int tanggal;
    int bulan;
    int tahun;
};

struct user {
    string usn;      
    string pass;      
    bool isAdmin;          
};

struct produk {
    int id;
    string namaBahan;          
    int jumlahStok;            
    int hargaBeli;              
    int hargaJual;              
    int jumlahTerjual;                    
    kadaluarsa kadaluarsa; 
};

void header(string judul) { 
    cout << "\n====== " << judul << " ======\n" << endl;
}

string password(string pesan) {
    string pass = "";
    char ch;
    cout << pesan;
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') { 
            if (pass.length() > 0) { cout << "\b \b"; pass.pop_back(); }
        } else {
            pass.push_back(ch); cout << '*'; 
        }
    }
    cout << endl;
    return pass;
}

string toLowerCase(string str) { // Fungsi agar inputan tidak case sensitive
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void insertionSortId(produk arr[], int n) {
    for (int i = 1; i < n; i++) {
        produk key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertionSortByStok(produk arr[], int n) {
    for (int i = 1; i < n; i++) {
        produk key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].jumlahStok > key.jumlahStok) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int binarySearchId(produk *arr, int size, int *targetId) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (arr[mid].id == *targetId) {
            return mid;
        } else if (arr[mid].id < *targetId) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int binarySearchStok(produk *arr, int size, int *targetStok) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (arr[mid].jumlahStok == *targetStok) {
            return mid;
        } else if (arr[mid].jumlahStok < *targetStok) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int linearSearchNama(produk *arr, int size, string *targetNama) {
    string targetLower = toLowerCase(*targetNama); 
    for (int i = 0; i < size; i++) {
        if (toLowerCase(arr[i].namaBahan) == targetLower) {
            return i;
        }
    }
    return -1;
}

void cetakSatuProduk(produk p, bool isAdmin) {
    Table tbl;
    string tgl = to_string(p.kadaluarsa.tanggal) + "/" + to_string(p.kadaluarsa.bulan) + "/" + to_string(p.kadaluarsa.tahun);
    if (isAdmin) {
        tbl.add_row({"ID", "Nama Bahan", "Stok", "Harga Beli", "Harga Jual", "Terjual", "Kadaluarsa"});
        tbl.add_row({to_string(p.id), p.namaBahan, to_string(p.jumlahStok), "Rp" + to_string(p.hargaBeli), "Rp" + to_string(p.hargaJual), to_string(p.jumlahTerjual), tgl});
    } else {
        tbl.add_row({"Produk", "Stok", "Harga", "Terjual", "Kadaluarsa"});
        tbl.add_row({p.namaBahan, to_string(p.jumlahStok), "Rp" + to_string(p.hargaJual), to_string(p.jumlahTerjual), tgl});
    }
    tbl.row(0).format().font_align(FontAlign::center);
    cout << "\n" << tbl << "\n";
}

bool login(user users[], int jumlahUser, user &userAktif, int percobaan) { 
    system("cls");
    header("LOGIN");
    
    string usn;
    cout << "Masukkan username : ";
    getline(cin, usn);
    string pass = password("Masukkan password : ");
    
    for (int i = 0; i < jumlahUser; i++) {
        if (users[i].usn == usn && users[i].pass == pass) {
            userAktif = users[i];
            cout << "\nLogin berhasil, selamat datang di Isekai Bakery " << users[i].usn << endl;
            return true;
        }
    }

    if (percobaan - 1 == 0) {
        cout << "\nMaaf, kesempatan Anda telah habis" << endl;
        return false;
    }
    
    cout << "\nSayang sekali, login gagal" << endl;
    cout << "Sisa percobaan Anda adalah: " << percobaan - 1;
    cout << "\nTekan enter untuk mencoba lagi...";
    cin.get();
    
    return login(users, jumlahUser, userAktif, percobaan - 1);
}

void registerr(user users[], int *jumlahUser, int maxUser) {
    system("cls");
    header("Form Registrasi");

    if (*jumlahUser >= maxUser) { 
        cout << "Kapasitas user penuh" << endl; 
        return; 
    }
    
    string usnBaru;
    while (true) {
        cout << "Masukkan username : ";
        getline(cin, usnBaru);
        
        if (usnBaru.empty()) {
            cout << "Username tidak boleh kosong\n";
            continue;
        }
        
        bool isDuplicate = false;
        for (int i = 0; i < *jumlahUser; i++) {
            if (users[i].usn == usnBaru) {
                isDuplicate = true;
                break; 
            }
        }
        
        if (isDuplicate) {
            cout << "Username sudah digunakan. Silakan coba nama lain.\n";
        } else {
            users[*jumlahUser].usn = usnBaru; 
            break; 
        }
    }

    while (true) {
        string passBaru = password("Password : ");
        if (passBaru.empty()) {
            cout << "Password tidak boleh kosong\n";
        } else {
            users[*jumlahUser].pass = passBaru;
            break;
        }
    }

    users[*jumlahUser].isAdmin = false; 

    (*jumlahUser)++;
    cout << "\nRegistrasi berhasil, silakan login" << endl;
}

void readAdmin(produk produkList[], int jumlahProduk, bool isAdmin) {
    Table tbl;
    if (isAdmin) {
        tbl.add_row({"No", "ID", "Nama Bahan", "Stok", "Harga Beli", "Harga Jual", "Terjual", "Kadaluarsa"});
    } else {
        tbl.add_row({"No", "Produk", "Stok", "Harga", "Terjual", "Kadaluarsa"});
    }
    tbl.row(0).format().font_align(FontAlign::center);
    
    for (int i = 0; i < jumlahProduk; i++) {
        string tgl = to_string(produkList[i].kadaluarsa.tanggal) + "/" + to_string(produkList[i].kadaluarsa.bulan) + "/" + to_string(produkList[i].kadaluarsa.tahun);
        if (isAdmin) {
            tbl.add_row({ to_string(i + 1), to_string(produkList[i].id), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp" + to_string(produkList[i].hargaBeli), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tgl });
        } else {
            tbl.add_row({ to_string(i + 1), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tgl });
        }
    }

    tbl.column(0).format().width(5).font_align(FontAlign::center); 
    
    if (isAdmin) {
        tbl.column(1).format().width(5).font_align(FontAlign::center);
        tbl.column(2).format().width(18).font_align(FontAlign::center);
        tbl.column(3).format().width(8).font_align(FontAlign::center);
        tbl.column(4).format().width(12).font_align(FontAlign::center);
        tbl.column(5).format().width(12).font_align(FontAlign::center);
        tbl.column(6).format().width(10).font_align(FontAlign::center);
        tbl.column(7).format().width(12).font_align(FontAlign::center);
    } else {
        tbl.column(1).format().width(18).font_align(FontAlign::center);
        tbl.column(2).format().width(8).font_align(FontAlign::center);
        tbl.column(3).format().width(12).font_align(FontAlign::center);
        tbl.column(4).format().width(10).font_align(FontAlign::center);
        tbl.column(5).format().width(12).font_align(FontAlign::center);
    }
    cout << tbl << endl;
}

void quickSort(produk arr[], int low, int high) {
    if (low >= high) 
    return;

    int mid = low + (high - low) / 2;
    string pivot = arr[mid].namaBahan;
    
    int i = low, j = high;

    while (i <= j) {
        while (arr[i].namaBahan > pivot) 
        i++;
        while (arr[j].namaBahan < pivot) 
        j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (low < j) quickSort(arr, low, j);
    if (i < high) quickSort(arr, i, high);
}

void insertionSort(produk arr[], int n) {
    for (int i = 1; i < n; i++) {
        produk key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].hargaJual > key.hargaJual) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(produk arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indeksMax = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].jumlahStok > arr[indeksMax].jumlahStok) {
                indeksMax = j;
            }
        }
        if (indeksMax != i) {
            swap(arr[i], arr[indeksMax]);
        }
    }
}

void menuSearching(produk produkList[], int jumlahProduk, bool isAdmin) {
    if (jumlahProduk == 0) {
        cout << "Belum ada data produk." << endl;
        return;
    }
    int pilihan;
    do {
        system("cls");
        header("Menu Searching Produk");
        Table tbl;
        tbl.add_row({"No", "Menu Searching"});

        if (isAdmin) {
            tbl.add_row({"1", "Mencari produk berdasarkan ID"});
        } else {
            tbl.add_row({"1", "Mencari produk berdasarkan jumlah stok"});
        }
        
        tbl.add_row({"2", "Mencari produk berdasarkan nama bahan"});
        tbl.add_row({"3", "Kembali ke menu sebelumnya"});
        
        tbl.row(0).format().font_align(FontAlign::center);
        tbl.column(0).format().width(5).font_align(FontAlign::center);
        
        cout << tbl << endl;
        
        while (true) {
            cout << "Pilih menu searching: ";
            if (cin.peek() == '\n') {
                cout << "Silakan pilih menu yang tersedia\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin >> pilihan;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Silakan masukkan angka saja.\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        if (pilihan == 1) {
            if (isAdmin) {
                int idCari;
                while (true) {
                    cout << "\nMasukkan ID Produk yang dicari: ";
                    if (cin.peek() == '\n') {
                        cout << "Silakan masukkan angka saja\n";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cin >> idCari;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Silakan masukkan angka saja\n";
                    } else if (idCari <= 0) {
                        cout << "ID harus angka positif\n";
                    } else {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                }
                
                system("cls");
                header("Hasil Pencarian Berdasarkan ID");
                
                insertionSortId(produkList, jumlahProduk); 
                int idx = binarySearchId(produkList, jumlahProduk, &idCari); 
                
                if (idx != -1) {
                    cetakSatuProduk(produkList[idx], isAdmin);
                } else {
                    cout << "Produk dengan ID " << idCari << " tidak ditemukan." << endl;
                }
            } else {
                int stokCari;
                while (true) {
                    cout << "\nMasukkan Jumlah Stok yang dicari: ";
                    if (cin.peek() == '\n') {
                        cout << "Silakan masukkan angka saja\n";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cin >> stokCari;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Silakan masukkan angka saja\n";
                    } else if (stokCari < 0) {
                        cout << "Stok tidak boleh negatif\n";
                    } else {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                }
                
                system("cls");
                header("Hasil Pencarian Berdasarkan Stok");
                
                insertionSortByStok(produkList, jumlahProduk); 
                int idx = binarySearchStok(produkList, jumlahProduk, &stokCari); 
                
                if (idx != -1) {
                    cetakSatuProduk(produkList[idx], isAdmin);
                } else {
                    cout << "Produk dengan stok berjumlah " << stokCari << " tidak ditemukan." << endl;
                }
            }
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        } else if (pilihan == 2) {
            string namaCari;
            while (true) {
                cout << "\nMasukkan Nama Bahan yang dicari: ";
                getline(cin, namaCari);
                
                if (namaCari.empty()) {
                    cout << "Silakan masukkan nama produk\n";
                } else {
                    bool isHuruf = true;
                    for (char c : namaCari) {
                        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                            isHuruf = false;
                            break;
                        }
                    }
                    if (!isHuruf) {
                        cout << "Silakan masukkan huruf saja\n";
                    } else {
                        break; 
                    }
                }
            }
            
            system("cls");
            header("Hasil Pencarian Berdasarkan Nama");
            
            int idx = linearSearchNama(produkList, jumlahProduk, &namaCari); 
            
            if (idx != -1) {
                cetakSatuProduk(produkList[idx], isAdmin);
            } else {
                cout << "Produk dengan nama '" << namaCari << "' tidak ditemukan." << endl;
            }
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        } else if (pilihan != 3) {
            cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        }
    } while (pilihan != 3);
}

void menuSorting(produk produkList[], int jumlahProduk, bool isAdmin) {
    if (jumlahProduk == 0) {
        cout << "Belum ada data produk." << endl;
        return;
    }
    int pilihan;
    do {
        system("cls");
        header("Menu Sorting Produk");
        Table tbl;
        tbl.add_row({"No", "Menu Sorting"});
        tbl.add_row({"1", "Mengurutkan Produk Berdasarkan Nama Bahan (Z-A)"});
        tbl.add_row({"2", "Mengurutkan Produk Berdasarkan Harga Jual (Termurah-Termahal)"});
        tbl.add_row({"3", "Mengurutkan Produk Berdasarkan Stok (Banyak-Sedikit)"});
        tbl.add_row({"4", "Kembali ke menu sebelumnya"});
        
        tbl.row(0).format().font_align(FontAlign::center);
        tbl.column(0).format().width(5).font_align(FontAlign::center);
        
        cout << tbl << endl;
        
        while (true) {
            cout << "Pilih menu sorting: ";
            if (cin.peek() == '\n') {
                cout << "Silakan pilih menu yang tersedia\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin >> pilihan;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Silakan masukkan angka saja.\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        if (pilihan == 1) {
            quickSort(produkList, 0, jumlahProduk - 1);
            system("cls");
            cout << "\nData Berdasarkan Nama Bahan (Z-A)\n\n";
            readAdmin(produkList, jumlahProduk, isAdmin);
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        } else if (pilihan == 2) {
            insertionSort(produkList, jumlahProduk);
            system("cls");
            cout << "\nData Berdasarkan Harga Jual (Termurah-Termahal)\n\n";
            readAdmin(produkList, jumlahProduk, isAdmin);
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        } else if (pilihan == 3) {
            selectionSort(produkList, jumlahProduk);
            system("cls");
            cout << "\nData Berdasarkan Jumlah Stok (Banyak-Sedikit)\n\n";
            readAdmin(produkList, jumlahProduk, isAdmin);
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        } else if (pilihan != 4) {
            cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        }
    } while (pilihan != 4);
}

void createAdmin(produk produkList[], int *jumlahProduk, int maxProduk) {
    system("cls");
    header("Tambah Produk");
    
    if (*jumlahProduk >= maxProduk) { 
        cout << "Kapasitas produk penuh" << endl; 
        return; 
    }
    
    produk *produkBaru = &produkList[*jumlahProduk];

    int maxId = 0;
    for (int i = 0; i < *jumlahProduk; i++) {
        if (produkList[i].id > maxId) {
            maxId = produkList[i].id;
        }
    }
    produkBaru->id = maxId + 1; 
    
    while (true) {
        cout << "Nama produk : ";
        getline(cin, produkBaru->namaBahan);
        
        if (produkBaru->namaBahan.empty()) {
            cout << "Silakan masukkan nama produk\n";
        } else {
            bool isHuruf = true;
            for (char c : produkBaru->namaBahan) {
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                    isHuruf = false;
                    break;
                }
            }
            if (!isHuruf) {
                cout << "Silakan masukkan huruf saja\n";
            } else {
                break; 
            }
        }
    }
    
    while (true) {
        cout << "Jumlah stok : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan jumlah stok\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> produkBaru->jumlahStok;
        
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Silakan masukkan angka saja\n";
        } else if (produkBaru->jumlahStok < 0) {
            cout << "Angka harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            break; 
        }
    }
    
    while (true) {
        cout << "Harga Beli (Rp) : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan harga beli\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> produkBaru->hargaBeli;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkBaru->hargaBeli < 0) {
            cout << "Harga harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    while (true) {
        cout << "Harga Jual (Rp) : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan harga jual\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> produkBaru->hargaJual;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkBaru->hargaJual < 0) {
            cout << "Harga harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    while (true) {
        cout << "Jumlah Terjual : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan jumlah terjual\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> produkBaru->jumlahTerjual;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkBaru->jumlahTerjual < 0) {
            cout << "Angka harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    cout << "\n--- Tanggal Kadaluarsa ---" << endl;
    while (true) {
        cout << "Tanggal : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan tanggal\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> produkBaru->kadaluarsa.tanggal;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkBaru->kadaluarsa.tanggal <= 0 || produkBaru->kadaluarsa.tanggal > 31) {
            cout << "Tanggal harus antara 1-31\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    while (true) {
        cout << "Bulan : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan bulan\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> produkBaru->kadaluarsa.bulan;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkBaru->kadaluarsa.bulan <= 0 || produkBaru->kadaluarsa.bulan > 12) {
            cout << "Bulan harus antara 1-12\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    while (true) {
        cout << "Tahun : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan tahun\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> produkBaru->kadaluarsa.tahun;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkBaru->kadaluarsa.tahun <= 0) {
            cout << "Tahun tidak valid, silakan coba lagi\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    (*jumlahProduk)++;
    cout << "\nProduk telah ditambahkan" << endl;
}

void editAdmin(produk produkList[], int jumlahProduk) {
    system("cls");
    header("Edit Data Produk");
    if (jumlahProduk == 0) { 
        cout << "Belum ada produk untuk diubah." << endl; 
        return; 
    }
    
    readAdmin(produkList, jumlahProduk, true);
    
    int target;
    int idx = -1; 

    insertionSortId(produkList, jumlahProduk);

    while (true) {
        cout << "\nMasukkan ID produk yang akan diubah : ";
        if (cin.peek() == '\n') {
            cout << "Silakan masukkan ID produk\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> target;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            idx = binarySearchId(produkList, jumlahProduk, &target);
            if (idx == -1) {
                cout << "ID produk tidak ada, silakan masukkan ID yang tersedia\n";
            } else {
                break; 
            }
        }
    }

    produk *produkEdit = &produkList[idx];

    while (true) {
        cout << "Nama produk [" << produkEdit->namaBahan << "] : ";
        string namaBaru;
        getline(cin, namaBaru);
        
        if (namaBaru.empty()) {
            break; 
        } else {
            bool isHuruf = true;
            for (char c : namaBaru) {
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                    isHuruf = false;
                    break;
                }
            }
            if (!isHuruf) {
                cout << "Silakan masukkan huruf saja\n";
            } else {
                produkEdit->namaBahan = namaBaru; 
                break; 
            }
        }
    }

    while (true) {
        cout << "Jumlah stok [" << produkEdit->jumlahStok << "] : ";
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; 
        }
        
        int stokBaru;
        cin >> stokBaru;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (stokBaru < 0) {
            cout << "Stok harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkEdit->jumlahStok = stokBaru; 
            break;
        }
    }

    while (true) {
        cout << "Harga Beli (Rp) [" << produkEdit->hargaBeli << "] : ";
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; 
        }
        
        int hargaBeliBaru;
        cin >> hargaBeliBaru;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (hargaBeliBaru < 0) {
            cout << "Harga harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkEdit->hargaBeli = hargaBeliBaru;
            break;
        }
    }

    while (true) {
        cout << "Harga Jual (Rp) [" << produkEdit->hargaJual << "] : ";
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; 
        }
        
        int hargaJualBaru;
        cin >> hargaJualBaru;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (hargaJualBaru < 0) {
            cout << "Harga harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkEdit->hargaJual = hargaJualBaru;
            break;
        }
    }

    while (true) {
        cout << "Jumlah Terjual [" << produkEdit->jumlahTerjual << "] : ";
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; 
        }
        
        int terjualBaru;
        cin >> terjualBaru;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (terjualBaru < 0) {
            cout << "Jumlah terjual harus positif\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkEdit->jumlahTerjual = terjualBaru;
            break;
        }
    }

    cout << "\n--- Tanggal Kadaluarsa ---" << endl;
    while (true) {
        cout << "Tanggal [" << produkEdit->kadaluarsa.tanggal << "] : ";
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; 
        }
        
        int tglBaru;
        cin >> tglBaru;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (tglBaru <= 0 || tglBaru > 31) {
            cout << "Tanggal harus antara 1-31\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkEdit->kadaluarsa.tanggal = tglBaru;
            break;
        }
    }

    while (true) {
        cout << "Bulan [" << produkEdit->kadaluarsa.bulan << "] : ";
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; 
        }
        
        int blnBaru;
        cin >> blnBaru;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (blnBaru <= 0 || blnBaru > 12) {
            cout << "Bulan harus antara 1-12\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkEdit->kadaluarsa.bulan = blnBaru;
            break;
        }
    }

    while (true) {
        cout << "Tahun [" << produkEdit->kadaluarsa.tahun << "] : ";
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; 
        }
        
        int thnBaru;
        cin >> thnBaru;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (thnBaru <= 0) {
            cout << "Tahun tidak valid\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkEdit->kadaluarsa.tahun = thnBaru;
            break;
        }
    }

    cout << "\nData berhasil diedit" << endl;
}

void deleteAdmin(produk produkList[], int *jumlahProduk) { 
    system("cls");
    header("Hapus Data Produk");
    
    if (*jumlahProduk == 0) { 
        cout << "Belum ada produk untuk dihapus." << endl; 
        return; 
    }

    readAdmin(produkList, *jumlahProduk, true);
    
    int targetId;
    int idx = -1;

    insertionSortId(produkList, *jumlahProduk);

    while (true) {
        cout << "\nMasukkan ID produk yang akan dihapus : ";
        if (cin.peek() == '\n') {
            cout << "Silakan pilih ID yang tersedia\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin >> targetId;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            idx = binarySearchId(produkList, *jumlahProduk, &targetId);
            if (idx == -1) {
                cout << "ID produk tidak ada, silakan masukkan ID yang tersedia\n";
            } else {
                break;
            }
        }
    }

    for (int i = idx; i < *jumlahProduk - 1; i++) {
        produkList[i] = produkList[i + 1];
    }
    
    (*jumlahProduk)--;
    
    cout << "\nProduk berhasil dihapus" << endl;
}

void menuAdmin(produk produkList[], int &jumlahProduk, int maxProduk, bool &sudahLogin) { 
    int menuAdminChoice;
    do {
        system("cls");
        header("Menu Admin");
        Table menuAdminTbl;
        menuAdminTbl.add_row({"No", "Menu"});
        menuAdminTbl.add_row({"1", "Lihat data produk (Read)"});
        menuAdminTbl.add_row({"2", "Tambah produk baru (Create)"});
        menuAdminTbl.add_row({"3", "Update data produk (Update)"});
        menuAdminTbl.add_row({"4", "Hapus data produk (Delete)"});
        menuAdminTbl.add_row({"5", "Menu Sorting"});
        menuAdminTbl.add_row({"6", "Menu Searching"});
        menuAdminTbl.add_row({"7", "Kembali ke menu sebelumnya"});
        
        menuAdminTbl.row(0).format().font_align(FontAlign::center);
        menuAdminTbl.column(0).format().width(6).font_align(FontAlign::center);
        menuAdminTbl.column(1).format().width(35);
        cout << menuAdminTbl << endl;

        while (true) {
            cout << "Silakan pilih menu admin: ";
            if (cin.peek() == '\n') {
                cout << "Silakan pilih menu yang tersedia\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            cin >> menuAdminChoice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Silakan masukkan angka saja\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        switch (menuAdminChoice) {
            case 1: 
                system("cls");
                header("Data Produk (Admin)");
                if (jumlahProduk == 0) cout << "Belum ada data produk." << endl;
                else readAdmin(produkList, jumlahProduk, true);
                break;
            case 2: 
                createAdmin(produkList, &jumlahProduk, maxProduk); 
            break;
            case 3: 
                editAdmin(produkList, jumlahProduk); 
            break;
            case 4: 
                deleteAdmin(produkList, &jumlahProduk); 
            break;
            case 5:
                menuSorting(produkList, jumlahProduk, true);
            break;
            case 6:
                menuSearching(produkList, jumlahProduk, true);
            break;
            case 7: sudahLogin = false; 
            break;
            default: cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
        }
        
        if (menuAdminChoice != 7 && menuAdminChoice != 5 && menuAdminChoice != 6) {
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        }
    } while (menuAdminChoice != 7 && sudahLogin);
}

void menuUser(produk produkList[], int jumlahProduk, bool &sudahLogin) {
    int menuUserChoice;
    do {
        system("cls");
        header("Menu User");
        Table menuUserTbl;
        menuUserTbl.add_row({"No", "Menu"});
        menuUserTbl.add_row({"1", "Lihat produk"});
        menuUserTbl.add_row({"2", "Menu Sorting"});
        menuUserTbl.add_row({"3", "Menu Searching"});
        menuUserTbl.add_row({"4", "Kembali ke menu sebelumnya"});
        
        menuUserTbl.row(0).format().font_align(FontAlign::center);
        menuUserTbl.column(0).format().width(6).font_align(FontAlign::center);
        menuUserTbl.column(1).format().width(30);
        cout << menuUserTbl << endl;

        while (true) {
            cout << "Silakan pilih menu yang tersedia: ";
            if (cin.peek() == '\n') {
                cout << "Silakan pilih menu yang tersedia\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            cin >> menuUserChoice;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Silakan masukkan angka saja\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        switch (menuUserChoice) {
            case 1: 
                system("cls");
                header("Daftar Produk (User)");
                if (jumlahProduk == 0) cout << "Belum ada data produk." << endl;
                else readAdmin(produkList, jumlahProduk, false);
                break;
            case 2:
                menuSorting(produkList, jumlahProduk, false);
                break;
            case 3:
                menuSearching(produkList, jumlahProduk, false);
                break;
            case 4: sudahLogin = false; 
            break;
            default: cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
        }
        
        if (menuUserChoice != 4 && menuUserChoice != 2 && menuUserChoice != 3) {
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        }
    } while (menuUserChoice != 4 && sudahLogin);
}

int main() {
    const int maxUser = 100;
    const int maxProduk = 100;

    user users[maxUser];
    int jumlahUser = 0;

    produk produkList[maxProduk];
    int jumlahProduk = 0;

    user userAktif;
    bool sudahLogin = false;

    users[0].usn = "senku";
    users[0].pass = "1234";
    users[0].isAdmin = false; 

    users[1].usn = "fina";
    users[1].pass = "016";
    users[1].isAdmin = true; 
    jumlahUser = 2; 
    
    produkList[0] = {1, "Ragi", 50, 1000, 1500, 100, {15, 12, 2026}};
    produkList[1] = {2, "Pewarna", 30, 8000, 12000, 80, {10, 8, 2026}};
    produkList[2] = {3, "Gula", 40, 8000, 12000, 80, {26, 10, 2026}};
    jumlahProduk = 3;

    int menuUtama;

    do {
        system("cls");
        cout << "\n========= ISEKAI BAKERY =========\n" << endl;
        
        Table menuUtamaTbl;
        menuUtamaTbl.add_row({"No", "Menu"});
        menuUtamaTbl.add_row({"1", "Login"});
        menuUtamaTbl.add_row({"2", "Register"});
        menuUtamaTbl.add_row({"3", "Logout"});
        
        menuUtamaTbl.row(0).format().font_align(FontAlign::center);
        menuUtamaTbl.column(0).format().width(6).font_align(FontAlign::center);
        menuUtamaTbl.column(1).format().width(20);
        cout << menuUtamaTbl << endl;
        
        while (true) {
            cout << "Silakan pilih menu yang tersedia : ";
            if (cin.peek() == '\n') {
                cout << "Silakan pilih menu yang tersedia\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            cin >> menuUtama;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Silakan masukkan angka saja.\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        switch (menuUtama) {
            case 1: {
                bool statusLogin = login(users, jumlahUser, userAktif, 3);
                if (statusLogin) {
                    sudahLogin = true;
                    cout << "\nTekan enter untuk melanjutkan...";
                    cin.get();
                    if (userAktif.isAdmin) {
                        menuAdmin(produkList, jumlahProduk, maxProduk, sudahLogin);
                    } else {
                        menuUser(produkList, jumlahProduk, sudahLogin);
                    }
                } else {
                    cout << "====== Terima kasih telah berkunjung ke Isekai Bakery ======" << endl;
                    return 0; 
                }
                break;
            }
            case 2: 
                registerr(users, &jumlahUser, maxUser); 
                cout << "\nTekan enter untuk melanjutkan...";
                cin.get();
                break;
            case 3: 
                cout << "====== Terima kasih telah berkunjung ke Isekai Bakery ======" << endl;
                break;
            default:
                cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
                cout << "\nTekan enter untuk melanjutkan...";
                cin.get();
        }
    } while (menuUtama != 3);

    return 0;
}