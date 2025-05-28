#include <iostream>
using namespace std;

int main() {
    int pilihan, jumlah;
    string, nama, ruangan;

    do {
        cout << "\n=== Menu Daftar Buku ===\n";
        cout << "1. Input Data Ruangan di Depan \n";
        cout << "1. Input Data Ruangan di Belakang\n";
        cout << "3. Hapus Data Ruangan\n";
        cout << "4. Tampilkan Daftar Buku\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan Data Ruangan : ";
                getline(cin, ruangan);
                cout << "Masukkan Nama Fasilitas: ";
                getline(cin, nama);
                cout << "Masukkan Jumlah : ";
                getline(cin, jumlah);
                tambahDepan();
                break;
            case 2:
                cout << "Masukkan Data Ruangan : ";
                getline(cin, ruangan);
                cout << "Masukkan Nama Fasilitas: ";
                getline(cin, nama);
                cout << "Masukkan Jumlah : ";
                getline(cin, jumlah);
                tambahBelakang();
                break;
            case 3:
                cout << "Masukkan Data Ruangan Yang Ingin Dihapus ";
                getline(cin, ruangan);
                hapus();
                break;
            case 4:
                tampilkanData();
                break;
            case 5:
                cout << "Terima kasih.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}
