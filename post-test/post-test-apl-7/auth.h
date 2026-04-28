#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <algorithm>
#include <conio.h>

using namespace std;

struct user {
    string usn;      
    string pass;      
    bool isAdmin;          
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

string toLowerCase(string str) { 
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
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

#endif