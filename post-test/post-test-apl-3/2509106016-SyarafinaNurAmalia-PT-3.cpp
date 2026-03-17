#include <iostream>
#include <conio.h>
#include <limits>
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

int cariProduk(produk arr[], int size, int idTarget) { 
    for (int i = 0; i < size; i++) {
        if (arr[i].id == idTarget) return i;
    }
    return -1;
}

int cariProduk(produk arr[], int size, string namaTarget) {
    for (int i = 0; i < size; i++) {
        if (arr[i].namaBahan == namaTarget) return i;
    }
    return -1;
}

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

bool login(user users[], int jumlahUser, user &userAktif, int kesempatan) { 
    if (kesempatan == 0) {
        cout << "\nMaaf, kesempatan Anda telah habis" << endl;
        return false;
    }

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
    
    cout << "\nSayang sekali, login gagal" << endl;
    cout << "Sisa percobaan Anda adalah: " << kesempatan - 1;
    cout << "\nTekan enter untuk mencoba lagi...";
    cin.get();
    
    return login(users, jumlahUser, userAktif, kesempatan - 1);
}

void registerr(user users[], int &jumlahUser, int maxUser) {
    system("cls");
    header("Form Registrasi");
    if (jumlahUser >= maxUser) { 
        cout << "Kapasitas user penuh" << endl; 
        return; 
    }
    
    string usnBaru;
    while (true) {
        cout << "Masukkan username : ";
        getline(cin, usnBaru);
        
        if (usnBaru.empty()) {
            cout << "Username tidak boleh kosong!\n";
            continue;
        }
        
        bool isDuplicate = false;
        for (int i = 0; i < jumlahUser; i++) {
            if (users[i].usn == usnBaru) {
                isDuplicate = true;
                break; 
            }
        }
        
        if (isDuplicate) {
            cout << "Username sudah digunakan. Silakan coba nama lain.\n";
        } else {
            users[jumlahUser].usn = usnBaru; 
            break; 
        }
    }
    
    users[jumlahUser].pass = password("Password : ");
    users[jumlahUser].isAdmin = false; 
    jumlahUser++;
    cout << "\nRegistrasi berhasil, silakan login" << endl;
}

void readAdmin(produk produkList[], int jumlahProduk, bool isAdmin) {
    Table tbl;
    if (isAdmin) {
        tbl.add_row({"ID", "Nama Bahan", "Stok", "Harga Beli", "Harga Jual", "Terjual", "Kadaluarsa"});
    } else {
        tbl.add_row({"ID", "Produk", "Stok", "Harga", "Terjual", "Kadaluarsa"});
    }
    tbl.row(0).format().font_style({FontStyle::bold}).font_align(FontAlign::center);
    
    for (int i = 0; i < jumlahProduk; i++) {
        string tgl = to_string(produkList[i].kadaluarsa.tanggal) + "/" + to_string(produkList[i].kadaluarsa.bulan) + "/" + to_string(produkList[i].kadaluarsa.tahun);
        if (isAdmin) {
            tbl.add_row({ to_string(produkList[i].id), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp" + to_string(produkList[i].hargaBeli), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tgl });
        } else {
            tbl.add_row({ to_string(produkList[i].id), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tgl });
        }
    }
    
    tbl.column(0).format().width(6).font_align(FontAlign::center);
    tbl.column(1).format().width(18).font_align(FontAlign::center);
    tbl.column(2).format().width(8).font_align(FontAlign::center);
    
    if (isAdmin) {
        tbl.column(3).format().width(12).font_align(FontAlign::center);
        tbl.column(4).format().width(12).font_align(FontAlign::center);
        tbl.column(5).format().width(10).font_align(FontAlign::center);
        tbl.column(6).format().width(12).font_align(FontAlign::center);
    } else {
        tbl.column(3).format().width(12).font_align(FontAlign::center);
        tbl.column(4).format().width(10).font_align(FontAlign::center);
        tbl.column(5).format().width(12).font_align(FontAlign::center);
    }
    cout << tbl << endl;
}

void createAdmin(produk produkList[], int &jumlahProduk, int maxProduk) {
    system("cls");
    header("Tambah Produk");
    if (jumlahProduk >= maxProduk) { 
        cout << "Kapasitas produk penuh" << endl; 
        return; 
    }
    
    produkList[jumlahProduk].id = jumlahProduk + 1;
    
    while (true) {
        cout << "Nama produk : ";
        getline(cin, produkList[jumlahProduk].namaBahan);
        
        if (produkList[jumlahProduk].namaBahan.empty()) {
            cout << "Silakan masukkan nama produk\n";
        } else {
            bool isHuruf = true;
            for (char c : produkList[jumlahProduk].namaBahan) {
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
        
        cin >> produkList[jumlahProduk].jumlahStok;
        
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Silakan masukkan angka saja\n";
        } else if (produkList[jumlahProduk].jumlahStok < 0) {
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
        
        cin >> produkList[jumlahProduk].hargaBeli;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkList[jumlahProduk].hargaBeli < 0) {
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
        
        cin >> produkList[jumlahProduk].hargaJual;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkList[jumlahProduk].hargaJual < 0) {
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
        
        cin >> produkList[jumlahProduk].jumlahTerjual;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkList[jumlahProduk].jumlahTerjual < 0) {
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
        
        cin >> produkList[jumlahProduk].kadaluarsa.tanggal;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkList[jumlahProduk].kadaluarsa.tanggal <= 0 || produkList[jumlahProduk].kadaluarsa.tanggal > 31) {
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
        
        cin >> produkList[jumlahProduk].kadaluarsa.bulan;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja\n";
        } else if (produkList[jumlahProduk].kadaluarsa.bulan <= 0 || produkList[jumlahProduk].kadaluarsa.bulan > 12) {
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
        
        cin >> produkList[jumlahProduk].kadaluarsa.tahun;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Silakan masukkan angka saja!\n";
        } else if (produkList[jumlahProduk].kadaluarsa.tahun <= 0) {
            cout << "Tahun tidak valid, silakan coba lagi\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    
    jumlahProduk++;
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
    int idx = -1; // Menyimpan indeks dari hasil pencarian
    
    // Perulangan untuk terus meminta input sampai ID yang valid dimasukkan
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
            cout << "Pilih ID produk yang tersedia\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            idx = cariProduk(produkList, jumlahProduk, target);
            if (idx == -1) {
                cout << "ID produk tidak ada, silakan masukkan ID yang tersedia\n";
            } else {
                break; // Jika ID benar dan ditemukan, keluar dari perulangan
            }
        }
    }

    while (true) {
        cout << "Nama produk [" << produkList[idx].namaBahan << "] : ";
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
                produkList[idx].namaBahan = namaBaru; 
                break; 
            }
        }
    }

    while (true) {
        cout << "Jumlah stok [" << produkList[idx].jumlahStok << "] : ";
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
            produkList[idx].jumlahStok = stokBaru; 
            break;
        }
    }

    while (true) {
        cout << "Harga Beli (Rp) [" << produkList[idx].hargaBeli << "] : ";
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
            produkList[idx].hargaBeli = hargaBeliBaru;
            break;
        }
    }

    while (true) {
        cout << "Harga Jual (Rp) [" << produkList[idx].hargaJual << "] : ";
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
            produkList[idx].hargaJual = hargaJualBaru;
            break;
        }
    }

    while (true) {
        cout << "Jumlah Terjual [" << produkList[idx].jumlahTerjual << "] : ";
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
            produkList[idx].jumlahTerjual = terjualBaru;
            break;
        }
    }

    cout << "\n--- Tanggal Kadaluarsa ---" << endl;
    while (true) {
        cout << "Tanggal [" << produkList[idx].kadaluarsa.tanggal << "] : ";
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
            cout << "Tanggal harus antara 1-31!\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkList[idx].kadaluarsa.tanggal = tglBaru;
            break;
        }
    }

    while (true) {
        cout << "Bulan [" << produkList[idx].kadaluarsa.bulan << "] : ";
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
            cout << "Bulan harus antara 1-12!\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            produkList[idx].kadaluarsa.bulan = blnBaru;
            break;
        }
    }

    while (true) {
        cout << "Tahun [" << produkList[idx].kadaluarsa.tahun << "] : ";
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
            produkList[idx].kadaluarsa.tahun = thnBaru;
            break;
        }
    }

    cout << "\nData berhasil diedit" << endl;
}

void deleteAdmin(produk produkList[], int &jumlahProduk) {
    system("cls");
    header("Hapus Data Produk");
    if (jumlahProduk == 0) { 
        cout << "Belum ada produk untuk dihapus." << endl; 
        return; 
    }

    readAdmin(produkList, jumlahProduk, true);
    
    int targetId;
    int idx = -1;
    
    // Logika pengulangan pencarian yang sama diterapkan pada fitur hapus
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
            
            idx = cariProduk(produkList, jumlahProduk, targetId);
            if (idx == -1) {
                cout << "ID produk tidak ada, silakan masukkan ID yang tersedia\n";
            } else {
                break;
            }
        }
    }
    
    for (int i = idx; i < jumlahProduk - 1; i++) {
        produkList[i] = produkList[i + 1];
    }
    jumlahProduk--;
    for (int i = 0; i < jumlahProduk; i++) {
        produkList[i].id = i + 1;
    }
    cout << "\nProduk berhasil dihapus" << endl;
}

void menuAdmin(produk produkList[], int &jumlahProduk, int maxProduk, bool &sudahLogin) {
    int menuAdmin;
    do {
        system("cls");
        header("Menu Admin");
        Table menuAdminTbl;
        menuAdminTbl.add_row({"No", "Menu"});
        menuAdminTbl.add_row({"1", "Lihat data produk (Read)"});
        menuAdminTbl.add_row({"2", "Tambah produk baru (Create)"});
        menuAdminTbl.add_row({"3", "Update data produk (Update)"});
        menuAdminTbl.add_row({"4", "Hapus data produk (Delete)"});
        menuAdminTbl.add_row({"5", "Logout"});
        
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
            
            cin >> menuAdmin;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Tolong masukkan angka saja\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        switch (menuAdmin) {
            case 1: 
                system("cls");
                header("Data Produk (Admin)");
                if (jumlahProduk == 0) cout << "Belum ada data produk." << endl;
                else readAdmin(produkList, jumlahProduk, true);
                break;
            case 2: createAdmin(produkList, jumlahProduk, maxProduk); 
            break;
            case 3: editAdmin(produkList, jumlahProduk); 
            break;
            case 4: deleteAdmin(produkList, jumlahProduk); 
            break;
            case 5: sudahLogin = false; 
            break;
            default: cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
        }
        
        if (menuAdmin != 5) {
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        }
    } while (menuAdmin != 5 && sudahLogin);
}

void menuUser(produk produkList[], int jumlahProduk, bool &sudahLogin) {
    int menuUser;
    do {
        system("cls");
        header("Menu User");
        Table menuUserTbl;
        menuUserTbl.add_row({"No", "Menu"});
        menuUserTbl.add_row({"1", "Lihat Produk"});
        menuUserTbl.add_row({"2", "Logout"});
        
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
            
            cin >> menuUser;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Tolong masukkan angka\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        switch (menuUser) {
            case 1: 
                system("cls");
                header("Daftar Produk (User)");
                if (jumlahProduk == 0) cout << "Belum ada data produk." << endl;
                else readAdmin(produkList, jumlahProduk, false);
                break;
            case 2: sudahLogin = false; 
            break;
            default: cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
        }
        
        if (menuUser != 2) {
            cout << "\nTekan enter untuk melanjutkan...";
            cin.get();
        }
    } while (menuUser != 2 && sudahLogin);
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
                cout << "Input tidak valid! Harap masukkan angka saja.\n";
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
                    cout << "\n====== Terima kasih telah berkunjung ke Isekai Bakery ======" << endl;
                    return 0; 
                }
                break;
            }
            case 2: 
                registerr(users, jumlahUser, maxUser);
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