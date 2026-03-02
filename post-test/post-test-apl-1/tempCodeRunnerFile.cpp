#include <iostream>
#include <string>
#include <cstdlib>   // untuk clear terminal
#include <conio.h>   // untuk getch() dan menyamarkan password

using namespace std;

int main(){
    string namaa, password;
    string nama = "Fina"; 
    string pass = "016";    
    int percobaan = 0;
    bool login = false;
    char ch; 

    system("cls");
    
    while(percobaan < 3){
        cout << "=========================================" << endl;
        cout << "                   LOGIN                 " << endl;    
        cout << "=========================================" << endl;
        cout << "Masukkan Nama      : ";
        getline(cin, namaa);
        cout << "Masukkan password : ";
        password = "";
        
        while(true){
            ch = getch();  
            if(ch == 13){ 
                break;
            } else if(ch == 8){ 
                if(password.length() > 0){
                    password.pop_back();
                    cout << "\b \b";  
                }
            } else {
                password += ch;
                cout << "*";  
            }
        }
        cout << endl << endl;
        
        if(namaa == nama && password == pass){
            login = true;
            cout << "Login berhasil, silakan pilih menu dengan menekan enter terlebih dahulu" << endl;
            cout << endl;
            getch();
            break;
        } else {
            percobaan++;
            cout << "Nama atau passwordd salah. Sisa percobaan : " << (3 - percobaan) << " kali" << endl;
            cout << endl;
            cout << "Tekan enter untuk mencoba lagi";
            getch();
            system("cls");
            
            if(percobaan >= 3){
                cout << "Sisa percobaan kamu telah habis. Maaf, Anda tidak bisa mengakses program." << endl;
                return 0;
            }
        }
    }
    
    int pilihan;
    bool keluar = false;
    
    while(keluar == false){ 
        system("cls"); 
        
        cout << endl;
        cout << "=========================================" << endl;
        cout << "               MENU KONVERSI             " << endl;
        cout << "=========================================" << endl;
        cout << "| [ 1 ] Konversi Jam ke Menit dan Detik |" << endl;
        cout << "| [ 2 ] Konversi Menit ke Jam dan Detik |" << endl;
        cout << "| [ 3 ] Konversi Detik ke Jam dan Menit |" << endl;
        cout << "| [ 4 ] Keluar                          |" << endl;
        cout << "=========================================" << endl;
        cout << "Masukkan pilihan (1-4): ";
        cin >> pilihan;
        cout << endl;
        
        if(pilihan == 1){
            system ("cls");
            int jam, menit, detik;
            cout << "=======================================" << endl;
            cout << "    Konversi Jam ke Menit dan Detik    " << endl;
            cout << "=======================================" << endl;
            cout << "Masukkan jumlah jam: ";
            cin >> jam;
            
            menit = jam * 60;
            detik = jam * 3600;
            
            cout << endl;
            cout << "=======================================" << endl;
            cout << "              Hasil Konversi           " << endl;
            cout << "---------------------------------------" << endl;
            cout << jam << " Jam = " << menit << " Menit dan " << detik << " Detik" << endl;
            cout << "=======================================" << endl;
            
            cout << endl;
            cout << "Tekan enter untuk kembali ke menu";
            getch();
            
        } else if(pilihan == 2){
            system("cls");
            int menit, jam, detik;
            cout << "=======================================" << endl;
            cout << "    Konversi Menit ke Jam dan Detik    " << endl;
            cout << "=======================================" << endl;
            cout << "Masukkan jumlah menit: ";
            cin >> menit;
            

            jam = menit / 60;
            detik = menit * 60;
            
            cout << endl;
            cout << "=======================================" << endl;
            cout << "              Hasil Konversi           " << endl;
            cout << "---------------------------------------" << endl;
            cout << menit << " Menit = " << jam << " Jam dan " << detik << " Detik" << endl;
            cout << "=======================================" << endl;
            
            cout << endl;
            cout << "Tekan enter untuk kembali ke menu";
            getch();
            
        } else if(pilihan == 3){
            system("cls");
            int detik, jam, menit;
            cout << "=======================================" << endl;
            cout << "    Konversi Detik ke Jam dan Menit    " << endl;
            cout << "=======================================" << endl;
            cout << "Masukkan jumlah detik: ";
            cin >> detik;

            jam = detik / 3600;
            menit = (detik % 3600) / 60;
            
            cout << endl;
            cout << "========================================" << endl;
            cout << "        Hasil Konversi     " << endl;
            cout << "----------------------------------------" << endl;
            cout << detik << " Detik = " << jam << " Jam dan " << menit << " Menit" << endl;
            cout << "========================================" << endl;
            
            cout << endl;
            cout << "Tekan enter untuk kembali ke menu";
            getch();
            
        } else if(pilihan == 4){
            system("cls");
            cout << "========================================" << endl;
            cout << "              PROGRAM SELESAI           " << endl;
            cout << "========================================" << endl;
            keluar = true;
            
        } else {
            cout << "Pilihan tidak valid. Silakan pilih angka 1-4." << endl;
            cout << endl;
            cout << "Tekan enter untuk kembali ke menu";
            getch();
        }
    }
    
    return 0;
}