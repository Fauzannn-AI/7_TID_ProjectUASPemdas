#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;

void ClearScreen(){
    cout << "\033[2J\033[1;H";
}

struct Item{
    string Nama;
    int Harga;
};

struct Barang{
    Item Es_Krim[3];
    Item Snack[3];
    Item Minuman[3];
    Item Roti[3];
    Item Makanan[3];
} hargaBarang= {
    {
    {"Vanilla", 5000},
    {"Coklat", 7000},
    {"Strawberry", 6000}
    },

    {
    {"Chitato", 11000}, 
    {"Taro", 9000}, 
    {"Lays", 10000},
    },

    {
    {"Teh Botol", 4000}, 
    {"Aqua", 3000}, 
    {"Coca Cola", 7000}
    },

    {
    {"Roti Tawar", 15000}, 
    {"Roti Coklat", 20000}, 
    {"Roti Keju", 25000}
    },

    {
    {"Nasi Rendang", 18000}, 
    {"Ayam Kentucky", 10000}, 
    {"Nasi Katsu", 15000}
    }
};

string Nama_Kategori[5] = {
    "Es Krim",
    "Snack",
    "Minuman",
    "Roti",
    "Makanan Berat"
};

void simpanTransaksi(const string &isi) {
    ofstream file("transaksi.txt", ios::app);
    file << isi << endl;
    file.close();
}

void tampilkanKategori(Item arr[3], string judul) {
    ClearScreen();
    cout << "====== " << judul << " ======" << "\n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << arr[i].Nama 
             << " - Rp " << arr[i].Harga << endl;
    }
    cout << "\n" << "Tekan ENTER untuk kembali...";
    getch();
}

void Menu_Data_Barang(){
    int pilihan = 0;
    
    while(true){
        ClearScreen();
        cout << "======= DATA BARANG =======" << '\n' << '\n';
        cout << "Pilih barang:" << '\n';

        for(int i=0; i<5; i++){
           if(i==pilihan) cout << "=> ";
           else cout << "  ";
            cout << Nama_Kategori[i] << '\n';
        }
        
        cout << "\n" << "W/S untuk navigasi, ENTER untuk pilih, Q untuk keluar.";

        char t = getch();
        if(t == 'w' || t == 'W') pilihan = (pilihan + 4) % 5;
        else if(t == 's' || t == 'S') pilihan = (pilihan + 1) % 5;
        else if(t == 13){
            switch(pilihan){
                case 0:
                    tampilkanKategori(hargaBarang.Es_Krim, "ES KRIM");
                    break;
                case 1:
                    tampilkanKategori(hargaBarang.Snack, "JAJANAN");
                    break;
                case 2:
                    tampilkanKategori(hargaBarang.Minuman, "MINUMAN");
                    break;
                case 3:
                    tampilkanKategori(hargaBarang.Roti, "ROTI");
                    break;
                case 4:
                    tampilkanKategori(hargaBarang.Makanan, "MAKANAN");
                    break;
            }
        }
        else if(t == 'q' || t == 'Q') break;
        }
    }
    
void Menu_Transaksi(){
    ClearScreen();
    int total = 0;

    cout << "=========== TRANSAKSI ===========" << "\n";

    string receipt = "===== Rincian Transaksi =====\n";

    while(true){
        cout << "\n" << "Pilih kategori:" << "\n";
        for(int i=0; i<5; i++)
            cout << i+1 << ". " << Nama_Kategori[i] << '\n';

        cout << "0. Selesai" << "\n";

        int kategori;
        cout << "Kategori: ";
        cin >> kategori;

        if(kategori == 0) break;
        if(kategori < 1 || kategori > 5) continue;

        Item* arr;
        switch(kategori){
            case 1: arr = hargaBarang.Es_Krim; break;
            case 2: arr = hargaBarang.Snack; break;
            case 3: arr = hargaBarang.Minuman; break;
            case 4: arr = hargaBarang.Roti; break;
            case 5: arr = hargaBarang.Makanan; break;
        }

        cout << "\n" << "Pilih item:" << "\n";
        for(int i=0; i<3; i++)
            cout << i+1 << ". " << arr[i].Nama << " - Rp " << arr[i].Harga << endl;

        int kode;
        cout << "Kode barang (1-3): ";
        cin >> kode;

        if(kode < 1 || kode > 3) continue;

        int Banyak;
        cout << "Jumlah: ";
        cin >> Banyak;
        int Harga_Item = arr[kode-1].Harga * Banyak;
        total += Harga_Item;
        cout << Banyak << " x " <<  arr[kode-1].Nama << " ditambahkan." << '\n';
        cout << "Subtotal: Rp " << Harga_Item << "\n";

        receipt += arr[kode-1].Nama + " x " + to_string(Banyak) + " - Rp " + to_string(Harga_Item) + "\n";
    }
        cout << "Total akhir: Rp " << total << "\n";

        receipt += string("Total Transaksi: Rp ") + to_string(total) + "\n";
        receipt += "------------------------------\n";

        cout << "transkasi disimpan" << '\n' << "Tekan ENTER untuk melanjutkan..." << '\n';
        simpanTransaksi(receipt);
        getch();
}

void Menu_Riwayat(){
    ClearScreen();
    ifstream file("transaksi.txt");
    cout << "======= RIWAYAT TRANSAKSI =======" << '\n';
    
    if(!file.is_open()){
        cout << "Tidak ada riwayat transaksi." << '\n';
    } else {
        string line;
        bool isEmpty = true;
        while(getline(file, line)){
            cout << line << '\n';
            isEmpty = false;
        }
        if(isEmpty)
            cout << "Tidak ada riwayat transaksi." << '\n';
        file.close();
    }
    cout << "\n" << "Tekan ENTER untuk kembali...";
    getch();
}

void Menu_Hapus_Riwayat(){
    int lokasi = 0;
    string pilihan[2] = {"ya", "tidak"};
    while(true){
        ClearScreen();
        cout << "======= HAPUS RIWAYAT TRANSAKSI =======" << '\n' << '\n';
        cout << "Apakah anda yakin ingin menghapus riwayat transaksi?" << '\n' << '\n';

        for(int i=0; i<2; i++){
                if(i == lokasi) cout << "=> ";
              else cout << "  ";
                cout << pilihan[i] << '\n';
     }
        cout << "\n" << "W/S untuk navigasi, ENTER untuk pilih.";

        char t = getch();
        if(t == 'w' || t == 'W')
        lokasi = (lokasi + 1) % 2;
        else if(t == 's' || t == 'S')
        lokasi = (lokasi + 1) % 2;
        else if(t == 13){
            if(lokasi == 0){
            remove("transaksi.txt");
            cout << "\n" << "Riwayat transaksi telah dihapus.";
            cout << "\n" << "Tekan ENTER untuk kembali...";
            getch();
            return;
            } 
            else if(lokasi == 1){
                return;
            }
        }
    }
}

void Menu_Utama(){;
    string Menu[4] = {
        "Transaksi",
        "Data Barang",
        "Riwayat Transaksi",
        "Hapus Riwayat"
    };

    int Lokasi = 0;

    while(true){
        ClearScreen();
        cout << "======= APLIKASI KASIR =======" << '\n' << '\n';

        for(int i=0; i<4; i++){
            if(i == Lokasi) cout << "=> ";
            else cout << "  ";
            cout << Menu[i] << '\n';
        }

        cout << "\n" << "W/S untuk navigasi, ENTER untuk pilih.";

        char T = getch();
        if(T == 'w' || T == 'W') 
        Lokasi = (Lokasi + 3) % 4;
        else if(T == 's' || T == 'S') 
        Lokasi = (Lokasi + 1) % 4;
        else if(T == 13){
            if(Lokasi == 0) Menu_Transaksi();
            else if(Lokasi == 1) Menu_Data_Barang();
            else if(Lokasi == 2) Menu_Riwayat();
            else if(Lokasi == 3) Menu_Hapus_Riwayat();
         }
    }
}

int main (){
    Menu_Utama();
    return 0;

}

