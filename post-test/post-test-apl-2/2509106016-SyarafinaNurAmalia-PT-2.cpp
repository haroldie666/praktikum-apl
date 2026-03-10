#include <iostream>
#include <iomanip>
#include <limits>
#include <conio.h>   // untuk getch() dan menyamarkan input password
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
    kadaluarsa kadaluarsa; // nested struct
};

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
    
    produkList[0].id = 1;
    produkList[0].namaBahan = "Ragi";
    produkList[0].jumlahStok = 50;
    produkList[0].hargaBeli = 1000;
    produkList[0].hargaJual = 1500;
    produkList[0].jumlahTerjual = 100;
    produkList[0].kadaluarsa = {15, 12, 2026};
    
    produkList[1].id = 2;
    produkList[1].namaBahan = "Pewarna";
    produkList[1].jumlahStok = 30;
    produkList[1].hargaBeli = 8000;
    produkList[1].hargaJual = 12000;
    produkList[1].jumlahTerjual = 80;
    produkList[1].kadaluarsa = {10, 8, 2026};

    produkList[2].id = 3;
    produkList[2].namaBahan = "Gula";
    produkList[2].jumlahStok = 40;
    produkList[2].hargaBeli = 8000;
    produkList[2].hargaJual = 12000;
    produkList[2].jumlahTerjual = 80;
    produkList[2].kadaluarsa = {26, 10, 2026};
    jumlahProduk = 3;

    int menuUtama;
    string tempInput;
    bool isAngka;

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
            getline(cin, tempInput);
            if (tempInput.empty()) { 
                cout << "Silakan masukkan pilihan (hanya angka)\n"; 
                continue; }
            isAngka = true; 
                for (char c : tempInput) { if (!isdigit(c)) { isAngka = false; break; } }
                    if (isAngka) { menuUtama = stoi(tempInput); 
                        break; }
                cout << "Silakan masukkan pilihan (hanya angka)\n";
        }

        switch (menuUtama) {
            case 1: {
                int kesempatan = 3;
                sudahLogin = false;
                
                while (kesempatan > 0 && !sudahLogin) {
                    system("cls");
                    cout << "\n======== LOGIN ========\n" << endl;
                    
                    string usn, pass = "";
                    cout << "Masukkan username : ";
                    getline(cin, usn);
                    
                    cout << "Masukkan password : ";
                    char ch;
                    while ((ch = _getch()) != '\r') { 
                        if (ch == '\b') { 
                            if (pass.length() > 0) { cout << "\b \b"; pass.pop_back(); }
                        } else {
                            pass.push_back(ch); cout << '*'; 
                        }
                    }
                    cout << endl;
                    
                    for (int i = 0; i < jumlahUser; i++) {
                        if (users[i].usn == usn && users[i].pass == pass) {
                            userAktif = users[i];
                            sudahLogin = true;
                            cout << "\nLogin berhasil, selamat datang di Isekai Bakery " << users[i].usn << endl;
                            break;
                        }
                    }

                    if (!sudahLogin) {
                        kesempatan--;
                        if (kesempatan > 0) {
                            cout << "\nSayang sekali, login gagal" << endl;
                            cout << "Sisa percobaan Anda adalah: " << kesempatan;
                            cout << "\nTekan enter untuk mencoba lagi...";
                            cin.get();
                        } else {
                            cout << "\nMaaf, kesempatan Anda telah habis" << endl;
                            cout << "====== Terima kasih telah berkunjung ke Isekai Bakery ======" << endl;
                            return 0; 
                        }
                    }
                }

                if (sudahLogin) {
                    cout << "\nTekan enter untuk melanjutkan...";
                    cin.get();
                    
                    if (userAktif.isAdmin) {
                        int menuAdmin;
                        do {
                            system("cls");
                            cout << "====== Menu admin ======\n" << endl;
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
                                getline(cin, tempInput);
                                if (tempInput.empty()) { 
                                    cout << "Silakan masukkan pilihan (hanya angka)\n"; 
                                    continue; 
                                }
                                isAngka = true; 
                                    for (char c : tempInput) { if (!isdigit(c)) { isAngka = false; break; } }
                                        if (isAngka) { menuAdmin = stoi(tempInput); 
                                            break; 
                                        }
                                    cout << "Silakan masukkan pilihan (hanya angka)\n";
                            }
                            
                            switch (menuAdmin) {
                                case 1: { 
                                    system("cls");
                                    cout << "\n====== Data Produk (admin) ======\n" << endl;
                                    if (jumlahProduk == 0) { 
                                        cout << "Belum ada data produk." << endl; 
                                        break; }
                                    
                                    Table tblAdmin;
                                    tblAdmin.add_row({"ID", "Nama Bahan", "Stok", "Harga Beli", "Harga Jual", "Terjual", "Kadaluarsa"});
                                    tblAdmin.row(0).format().font_align(FontAlign::center);
                                    
                                    for (int i = 0; i < jumlahProduk; i++) {
                                        string tglKadaluarsa = to_string(produkList[i].kadaluarsa.tanggal) + "/" + to_string(produkList[i].kadaluarsa.bulan) + "/" + to_string(produkList[i].kadaluarsa.tahun);
                                        tblAdmin.add_row({ to_string(produkList[i].id), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp " + to_string(produkList[i].hargaBeli), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tglKadaluarsa });
                                    }
                                    tblAdmin.column(0).format().width(6).font_align(FontAlign::center);
                                    tblAdmin.column(1).format().width(18).font_align(FontAlign::center);
                                    tblAdmin.column(2).format().width(8).font_align(FontAlign::center);
                                    tblAdmin.column(3).format().width(12).font_align(FontAlign::center);
                                    tblAdmin.column(4).format().width(12).font_align(FontAlign::center);
                                    tblAdmin.column(5).format().width(10).font_align(FontAlign::center);
                                    tblAdmin.column(6).format().width(12).font_align(FontAlign::center); 
                                    cout << tblAdmin << endl;
                                    break;
                                }
                                case 2: { 
                                    system("cls");
                                    cout << "\n====== Tambah Produk ======\n" << endl;
                                    if (jumlahProduk >= maxProduk) { 
                                        cout << "Kapasitas produk penuh" << endl; 
                                        break; 
                                    }
                                    
                                    produkList[jumlahProduk].id = jumlahProduk + 1;
                                    while (true) {
                                        cout << "Nama produk : ";
                                        getline(cin, produkList[jumlahProduk].namaBahan);
                                        
                                        if (produkList[jumlahProduk].namaBahan.empty()) {
                                            cout << "Nama produk tidak boleh kosong!\n";
                                            continue;
                                        }
                                        break;
                                    }
                                    
                                    while (true) {
                                        cout << "Jumlah stok : "; getline(cin, tempInput);
                                        if (tempInput.empty()) { cout << "Silakan masukkan stok dalam bentuk angka\n"; 
                                            continue; 
                                        }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } 
                                            }
                                        if (isAngka) { produkList[jumlahProduk].jumlahStok = stoi(tempInput); 
                                            break; }
                                        cout << "Tolong masukkan dalam bentuk angka\n";
                                    }

                                    while (true) {
                                        cout << "Harga Beli (Rp) : "; getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan harga beli dalam bentuk angka\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                            break; } }
                                        if (isAngka) { produkList[jumlahProduk].hargaBeli = stoi(tempInput); 
                                            break; }
                                        cout << "Tolong masukkan dalam bentuk angka\n";
                                    }

                                    while (true) {
                                        cout << "Harga Jual (Rp) : "; getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan harga jual dalam bentuk angka\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } }
                                        if (isAngka) { produkList[jumlahProduk].hargaJual = stoi(tempInput); 
                                            break; }
                                        cout << "Tolong masukkan dalam bentuk angka\n";
                                    }

                                    while (true) {
                                        cout << "Jumlah Terjual : "; getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan jumlah terjual dalam bentuk angka\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } }
                                        if (isAngka) { produkList[jumlahProduk].jumlahTerjual = stoi(tempInput); 
                                            break; }
                                        cout << "Tolong masukkan dalam bentuk angka\n";
                                    }
                                    
                                    cout << "\n--- Tanggal Kadaluarsa ---" << endl;
                                    while (true) {
                                        cout << "Tanggal : "; getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan tanggal dalam bentuk angka\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } }
                                        if (isAngka) { produkList[jumlahProduk].kadaluarsa.tanggal = stoi(tempInput); 
                                            break; }
                                        cout << "Tolong masukkan dalam bentuk angka\n";
                                    }

                                    while (true) {
                                        cout << "Bulan : "; getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan bulan dalam bentuk angka\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } }
                                        if (isAngka) { produkList[jumlahProduk].kadaluarsa.bulan = stoi(tempInput); 
                                            break; }
                                        cout << "Tolong masukkan dalam bentuk angka\n";
                                    }

                                    while (true) {
                                        cout << "Tahun : "; getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan tahun dalam bentuk angka\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } }
                                        if (isAngka) { produkList[jumlahProduk].kadaluarsa.tahun = stoi(tempInput); 
                                            break; }
                                        cout << "Tolong masukkan dalam bentuk angka\n";
                                    }
                                    
                                    jumlahProduk++;
                                    cout << "\nProduk telah ditambahkan" << endl;
                                    break;
                                }
                                case 3: { 
                                    system("cls");
                                    cout << "\n====== Edit Data Produk ======\n" << endl;
                                    if (jumlahProduk == 0) { cout << "Belum ada produk untuk diubah." << endl; break; }
                                    
                                    Table tabelEdit;
                                    tabelEdit.add_row({"ID", "Nama Bahan", "Stok", "Harga Beli", "Harga Jual", "Terjual", "Kadaluarsa"});
                                    tabelEdit.row(0).format().font_align(FontAlign::center);
                                    for (int i = 0; i < jumlahProduk; i++) {
                                        string tgl = to_string(produkList[i].kadaluarsa.tanggal) + "/" + to_string(produkList[i].kadaluarsa.bulan) + "/" + to_string(produkList[i].kadaluarsa.tahun);
                                        tabelEdit.add_row({ to_string(produkList[i].id), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp" + to_string(produkList[i].hargaBeli), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tgl });
                                    }
                                    tabelEdit.column(0).format().width(6).font_align(FontAlign::center);
                                    tabelEdit.column(1).format().width(18).font_align(FontAlign::center);
                                    tabelEdit.column(2).format().width(8).font_align(FontAlign::center);
                                    tabelEdit.column(3).format().width(12).font_align(FontAlign::center);
                                    tabelEdit.column(4).format().width(12).font_align(FontAlign::center);
                                    tabelEdit.column(5).format().width(10).font_align(FontAlign::center);
                                    tabelEdit.column(6).format().width(12).font_align(FontAlign::center); 
                                    cout << tabelEdit << endl;
                                    
                                    int indexEdit;
                                    while (true) {
                                        cout << "\nMasukkan ID produk yang akan diubah : ";
                                        getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan pilihan (hanya angka)\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } }
                                        if (isAngka) { indexEdit = stoi(tempInput); 
                                            break; }
                                        cout << "Silakan masukkan pilihan (hanya angka)\n";
                                    }
                                    
                                    if (indexEdit > 0 && indexEdit <= jumlahProduk) {
                                        int idx = indexEdit - 1;

                                        cout << "Nama produk [" << produkList[idx].namaBahan << "]: ";
                                        string inputStr;
                                        getline(cin, inputStr);
                                        if (!inputStr.empty()) produkList[idx].namaBahan = inputStr;

                                        while (true) {
                                            cout << "Jumlah stok [" << produkList[idx].jumlahStok << "]: "; getline(cin, tempInput);
                                            if (tempInput.empty()) 
                                            break;
                                            isAngka = true; 
                                            for (char c : tempInput) { 
                                                if (!isdigit(c)) { isAngka = false; 
                                                    break; } }
                                            if (isAngka) { produkList[idx].jumlahStok = stoi(tempInput); 
                                                break; }
                                            cout << "Silakan masukkan pilihan (hanya angka)\n";
                                        }

                                        while (true) {
                                            cout << "Harga Beli (Rp) [" << produkList[idx].hargaBeli << "]: "; getline(cin, tempInput);
                                            if (tempInput.empty()) 
                                            break;
                                            isAngka = true; 
                                            for (char c : tempInput) { 
                                                if (!isdigit(c)) { isAngka = false; 
                                                    break; } }
                                            if (isAngka) { produkList[idx].hargaBeli = stoi(tempInput); 
                                                break; }
                                            cout << "Silakan masukkan pilihan (hanya angka)\n";
                                        }

                                        while (true) {
                                            cout << "Harga Jual (Rp) [" << produkList[idx].hargaJual << "]: "; getline(cin, tempInput);
                                            if (tempInput.empty()) 
                                            break;
                                            isAngka = true; 
                                            for (char c : tempInput) { 
                                                if (!isdigit(c)) { isAngka = false; 
                                                    break; } }
                                            if (isAngka) { produkList[idx].hargaJual = stoi(tempInput); 
                                                break; }
                                            cout << "Silakan masukkan pilihan (hanya angka)\n";
                                        }

                                        while (true) {
                                            cout << "Jumlah Terjual [" << produkList[idx].jumlahTerjual << "]: "; getline(cin, tempInput);
                                            if (tempInput.empty()) 
                                            break;
                                            isAngka = true; 
                                            for (char c : tempInput) { 
                                                if (!isdigit(c)) { isAngka = false; 
                                                    break; } }
                                            if (isAngka) { produkList[idx].jumlahTerjual = stoi(tempInput); 
                                                break; }
                                            cout << "Silakan masukkan pilihan (hanya angka)\n";
                                        }
                                        
                                        cout << "\n--- Tanggal Kadaluarsa ---" << endl;
                                        while (true) {
                                            cout << "tanggal [" << produkList[idx].kadaluarsa.tanggal << "]: "; getline(cin, tempInput);
                                            if (tempInput.empty()) 
                                            break;
                                            isAngka = true; 
                                            for (char c : tempInput) { 
                                                if (!isdigit(c)) { isAngka = false; 
                                                    break; } }
                                            if (isAngka) { produkList[idx].kadaluarsa.tanggal = stoi(tempInput); 
                                                break; }
                                            cout << "Silakan masukkan pilihan (hanya angka)\n";
                                        }

                                        while (true) {
                                            cout << "Bulan [" << produkList[idx].kadaluarsa.bulan << "]: "; getline(cin, tempInput);
                                            if (tempInput.empty()) 
                                            break;
                                            isAngka = true; 
                                            for (char c : tempInput) { 
                                                if (!isdigit(c)) { isAngka = false; 
                                                    break; } }
                                            if (isAngka) { produkList[idx].kadaluarsa.bulan = stoi(tempInput); 
                                                break; }
                                            cout << "Silakan masukkan pilihan (hanya angka)\n";
                                        }

                                        while (true) {
                                            cout << "Tahun [" << produkList[idx].kadaluarsa.tahun << "]: "; getline(cin, tempInput);
                                            if (tempInput.empty()) 
                                            break;
                                            isAngka = true; 
                                            for (char c : tempInput) { 
                                                if (!isdigit(c)) { isAngka = false; 
                                                    break; } }
                                            if (isAngka) { produkList[idx].kadaluarsa.tahun = stoi(tempInput); 
                                                break; }
                                            cout << "Silakan masukkan pilihan (hanya angka)\n";
                                        }
                                        
                                        cout << "\nData berhasil diedit" << endl;
                                    } else {
                                        cout << "ID produk tidak ditemukan, silakan pilih dengan menginput angka saja" << endl;
                                    }
                                    break;
                                }
                                case 4: { 
                                    system("cls");
                                    cout << "\n====== Hapus Data Produk ======\n" << endl;
                                    if (jumlahProduk == 0) { 
                                        cout << "Belum ada produk untuk dihapus." << endl; 
                                        break; }

                                    Table tabelHapus;
                                    tabelHapus.add_row({"ID", "Nama Bahan", "Stok", "Harga Beli", "Harga Jual", "Terjual", "Kadaluarsa"});
                                    tabelHapus.row(0).format().font_align(FontAlign::center);
                                    for (int i = 0; i < jumlahProduk; i++) {
                                        string tgl = to_string(produkList[i].kadaluarsa.tanggal) + "/" + to_string(produkList[i].kadaluarsa.bulan) + "/" + to_string(produkList[i].kadaluarsa.tahun);
                                        tabelHapus.add_row({ to_string(produkList[i].id), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp" + to_string(produkList[i].hargaBeli), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tgl });
                                    }
                                    tabelHapus.column(0).format().width(6).font_align(FontAlign::center);
                                    tabelHapus.column(1).format().width(18).font_align(FontAlign::center);
                                    tabelHapus.column(2).format().width(8).font_align(FontAlign::center);
                                    tabelHapus.column(3).format().width(12).font_align(FontAlign::center);
                                    tabelHapus.column(4).format().width(12).font_align(FontAlign::center);
                                    tabelHapus.column(5).format().width(10).font_align(FontAlign::center);
                                    tabelHapus.column(6).format().width(12).font_align(FontAlign::center); 
                                    cout << tabelHapus << endl;
                                    
                                    int indexHapus;
                                    while (true) {
                                        cout << "\nMasukkan ID produk yang akan dihapus : ";
                                        getline(cin, tempInput);
                                        if (tempInput.empty()) { 
                                            cout << "Silakan masukkan pilihan (hanya angka)\n"; 
                                            continue; }
                                        isAngka = true; 
                                        for (char c : tempInput) { 
                                            if (!isdigit(c)) { isAngka = false; 
                                                break; } }
                                        if (isAngka) { indexHapus = stoi(tempInput); 
                                            break; }
                                        cout << "Silakan masukkan pilihan (hanya angka)\n";
                                    }
                                    
                                    if (indexHapus > 0 && indexHapus <= jumlahProduk) {
                                        int idx = indexHapus - 1;

                                        for (int i = idx; i < jumlahProduk - 1; i++) {
                                            produkList[i] = produkList[i + 1];
                                        }
                                        jumlahProduk--;

                                        for (int i = 0; i < jumlahProduk; i++) {
                                            produkList[i].id = i + 1;
                                        }
                                        
                                        cout << "\nProduk berhasil dihapus" << endl;
                                    } else {
                                        cout << "ID produk tidak valid, silakan pilih lagi" << endl;
                                    }
                                    break;
                                }
                                case 5:
                                    sudahLogin = false;
                                    break;
                                default:
                                    cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
                            }
                            
                            if (menuAdmin != 5) {
                                cout << "\nTekan enter untuk melanjutkan...";
                                cin.get();
                            }
                        } while (menuAdmin != 5 && sudahLogin);
                    } else {
                        int menuUser;
                        do {
                            system("cls");
                            
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
                                getline(cin, tempInput);
                                if (tempInput.empty()) { 
                                    cout << "Silakan masukkan pilihan (hanya angka)\n"; 
                                    continue; }
                                isAngka = true; 
                                for (char c : tempInput) { 
                                    if (!isdigit(c)) { isAngka = false; 
                                        break; } }
                                if (isAngka) { menuUser = stoi(tempInput); 
                                    break; }
                                cout << "Silakan masukkan pilihan (hanya angka)\n";
                            }
                            
                            switch (menuUser) {
                                case 1: { 
                                    system("cls");
                                    cout << "\n=== DAFTAR PRODUK (USER) ===\n" << endl;
                                    if (jumlahProduk == 0) { cout << "Belum ada data produk." << endl; break; }
                                    
                                    Table tabelUser;
                                    tabelUser.add_row({"ID", "Produk", "Stok", "Harga", "Terjual", "Kadaluarsa"});
                                    tabelUser.row(0).format().font_style({FontStyle::bold}).font_align(FontAlign::center);
                                    
                                    for (int i = 0; i < jumlahProduk; i++) {
                                        string tglKadaluarsa = to_string(produkList[i].kadaluarsa.tanggal) + "/" + to_string(produkList[i].kadaluarsa.bulan) + "/" + to_string(produkList[i].kadaluarsa.tahun);
                                        tabelUser.add_row({ to_string(produkList[i].id), produkList[i].namaBahan, to_string(produkList[i].jumlahStok), "Rp" + to_string(produkList[i].hargaJual), to_string(produkList[i].jumlahTerjual), tglKadaluarsa });
                                    }
                                    tabelUser.column(0).format().width(6).font_align(FontAlign::center);
                                    tabelUser.column(1).format().width(18).font_align(FontAlign::center);
                                    tabelUser.column(2).format().width(8).font_align(FontAlign::center);
                                    tabelUser.column(3).format().width(12).font_align(FontAlign::center);
                                    tabelUser.column(4).format().width(10).font_align(FontAlign::center);
                                    tabelUser.column(5).format().width(12).font_align(FontAlign::center);
                                    cout << tabelUser << endl;
                                    break;
                                }
                                case 2:
                                    sudahLogin = false;
                                    break;
                                default:
                                    cout << "Pilihan tidak valid, silakan pilih lagi" << endl;
                            }
                            
                            if (menuUser != 2) {
                                cout << "\nTekan enter untuk melanjutkan...";
                                cin.get();
                            }
                        } while (menuUser != 2 && sudahLogin);
                    }
                }
                break;
            }
            case 2: {
                system("cls");
                cout << "\n====== Form Registrasi ======\n" << endl;
                
                if (jumlahUser >= maxUser) { 
                    cout << "Kapasitas user penuh!" << endl; 
                    break; }
                
                cout << "Masukkan username : ";
                getline(cin, users[jumlahUser].usn);
                
                cout << "Password : ";
                string passReg = "";
                char chReg;
                while ((chReg = _getch()) != '\r') { 
                    if (chReg == '\b') { 
                        if (passReg.length() > 0) { cout << "\b \b"; passReg.pop_back(); }
                    } else {
                        passReg.push_back(chReg); cout << '*'; 
                    }
                }
                cout << endl;
                users[jumlahUser].pass = passReg;
                users[jumlahUser].isAdmin = false; 
                jumlahUser++;
                cout << "\nRegistrasi berhasil, silakan login" << endl;
                
                cout << "\nTekan enter untuk melanjutkan...";
                cin.get();
                break;
            }
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