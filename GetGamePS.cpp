//SCRIPT RENTAL PS
#include <iostream>
#include <algorithm>
using namespace std;
//test

struct Penyewa {
    string nama; // Nama penyewa
    int id; // ID penyewa
    int versi; // Versi PS yang disewa
    bool stick; // Apakah menyewa stick PS atau tidak
    bool tv; // Apakah menyewa TV atau tidak
    Penyewa* next; // Pointer ke penyewa selanjutnya
};


class RentalPS {
    private:
        int size; // Ukuran array
        Penyewa** arr; // Array of pointers ke linked lists
    public:
        // Constructor
        RentalPS (int s) {
            size = s;
            arr = new Penyewa* [size];
            for (int i = 0; i < size; i++) {
                arr [i] = NULL;
            }
        }

        // Destructor
        ~RentalPS () {
            for (int i = 0; i < size; i++) {
                Penyewa* temp = arr [i];
                while (temp != NULL) {
                    Penyewa* next = temp->next;
                    delete temp;
                    temp = next;
                }
            }
            delete [] arr;
        }

        
        int hash (int id) {
            return id % size;
        }

        
        void tambah (string nama, int id, int versi, bool stick, bool tv) {
            Penyewa* baru = new Penyewa;
            baru->nama = nama;
            baru->id = id;
            baru->versi = versi;
            baru->stick = stick;
            baru->tv = tv;
            baru->next = NULL;
            int indeks = hash (id);
            if (arr [indeks] == NULL) {
                arr [indeks] = baru;
            } else {
                Penyewa* temp = arr [indeks];
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = baru;
            }
        }

        
        void hapus (int id) {
            int indeks = hash (id);
            Penyewa* temp = arr [indeks];
            Penyewa* prev = NULL;
            while (temp != NULL && temp->id != id) {
                prev = temp;
                temp = temp->next;
            }
            if (temp == NULL) {
                cout << "Data tidak ditemukan\n";
                return;
            }
            if (prev == NULL) {
                arr [indeks] = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
        }

        
        Penyewa* cari (int id) {
            int indeks = hash (id);
            Penyewa* temp = arr [indeks];
            while (temp != NULL && temp->id != id) {
                temp = temp->next;
            }
            return temp;
        }

       
        

static bool comparePenyewa(Penyewa* a, Penyewa* b) {
    return a->nama < b->nama;
}

void urutkan() {
    // Membuat array of pointers ke penyewa
    Penyewa** data = new Penyewa*[size];
    int n = 0; // Jumlah data yang ada
    for (int i = 0; i < size; i++) {
        Penyewa* temp = arr[i];
        while (temp != NULL) {
            data[n] = temp;
            n++;
            temp = temp->next;
        }
    }
    // Menggunakan std::sort dengan custom comparator function
    sort(data, data + n, comparePenyewa);
    // Menampilkan data yang sudah diurutkan
    cout << "Data penyewa yang sudah diurutkan berdasarkan nama:\n";
    for (int i = 0; i < n; i++) {
        cout << data[i]->nama << " " << data[i]->id << " " << data[i]->versi << " ";
        if (data[i]->stick)
            cout << "Ya ";
        else
            cout << "Tidak ";
        if (data[i]->tv)
            cout << "Ya\n";
        else
            cout << "Tidak\n";
    }
    delete[] data;
}


        // Fungsi untuk menampilkan data penyewa yang sedang menggunakan PS, stick, dan TV
        void tampilkan () {
            // Membuat stack untuk menyimpan data penyewa yang menggunakan PS
            Penyewa** stack = new Penyewa* [size];
            int top = -1; // Indeks top dari stack
            // Membuat queue untuk menyimpan data penyewa yang menggunakan stick
            Penyewa** queue = new Penyewa* [size];
            int front = 0;
            int rear = -1; 
            
            for (int i = 0; i < size; i++) {
                Penyewa* temp = arr [i];
                while (temp != NULL) {
                    //menggunakan PS, masukkan ke stack
                    if (temp->versi > 0) {
                        top++;
                        stack [top] = temp;
                    }
                    // menggunakan stick, masukkan ke queue
                    if (temp->stick) {
                        rear++;
                        queue [rear] = temp;
                    }
                    temp = temp->next;
                }
            }
            // Menampilkan data penyewa yang menggunakan PS dari stack
            cout << "Data penyewa yang menggunakan PS:\n";
            while (top >= 0) {
                Penyewa* p = stack [top];
                cout << p->nama << " " << p->id << " " << p->versi << " ";
                if (p->stick) cout << "Ya ";
                else cout << "Tidak ";
                if (p->tv) cout << "Ya\n";
                else cout << "Tidak\n";
                top--;
            }
            // Menampilkan data penyewa yang menggunakan stick dari queue
            cout << "Data penyewa yang menggunakan stick:\n";
            while (front <= rear) {
                Penyewa* p = queue [front];
                cout << p->nama << " " << p->id << " " << p->versi << " ";
                if (p->stick) cout << "Ya ";
                else cout << "Tidak ";
                if (p->tv) cout << "Ya\n";
                else cout << "Tidak\n";
                front++;
            }
            delete [] stack;
            delete [] queue;
        }
};


void menu () {
    cout << "Menu pilihan:\n";
    cout << "1. Tambah data penyewa\n";
    cout << "2. Hapus data penyewa\n";
    cout << "3. Cari data penyewa\n";
    cout << "4. Urutkan data penyewa\n";
    cout << "5. Tampilkan data penyewa\n";
    cout << "6. Keluar\n";
    cout << "Masukkan pilihan Anda: ";
}

// Fungsi utama
int main () {
    // Membuat objek RentalPS dengan ukuran array 10
    RentalPS rps (10);
    // Membuat variabel untuk menyimpan pilihan pengguna
    int pilihan;
    // Membuat loop untuk menjalankan program
    do {
        // Menampilkan menu pilihan
        menu ();
        // Membaca pilihan pengguna
        cin >> pilihan;
        // Menjalankan program sesuai dengan pilihan
        switch (pilihan) {
            case 1: // Tambah data penyewa
                {
                    // Membuat variabel untuk menyimpan data penyewa
                    string nama;
                    int id, versi;
                    bool stick, tv;
                    char s, t;
                    // Membaca data penyewa dari pengguna
                    cout << "Masukkan nama penyewa: ";
                    cin >> nama;
                    cout << "Masukkan id penyewa: ";
                    cin >> id;
                    cout << "Masukkan versi PS yang disewa (1,2, atau 3): ";
                    cin >> versi;
                    cout << "Apakah menyewa stick PS? (Y/N): ";
                    cin >> s;
                    stick = (s == 'Y' || s == 'y') ? true : false;
                    cout << "Apakah menyewa TV? (Y/N): ";
                    cin >> t;
                    tv = (t == 'Y' || t == 'y') ? true : false;
                    // Menambah data penyewa ke RentalPS
                    rps.tambah(nama, id, versi, stick, tv);
                    cout << "Data penyewa berhasil ditambahkan.\n";
                    break;
                }
            case 2: // Hapus data penyewa
                {
                    // Membuat variabel untuk menyimpan id penyewa yang akan dihapus
                    int id;
                    // Membaca id penyewa dari pengguna
                    cout << "Masukkan id penyewa yang akan dihapus: ";
                    cin >> id;
                    // Menghapus data penyewa dari RentalPS
                    rps.hapus(id);
                    break;
                }
            case 3: // Cari data penyewa
                {
                    // Membuat variabel untuk menyimpan id penyewa yang akan dicari
                    int id;
                    // Membaca id penyewa dari pengguna
                    cout << "Masukkan id penyewa yang akan dicari: ";
                    cin >> id;
                    // Mencari data penyewa di RentalPS
                    Penyewa* hasil = rps.cari(id);
                    // Menampilkan hasil pencarian
                    if (hasil != NULL) {
                        cout << "Data ditemukan:\n";
                        cout << "Nama: " << hasil->nama << endl;
                        cout << "ID: " << hasil->id << endl;
                        cout << "Versi PS: " << hasil->versi << endl;
                        cout << "Stick PS: " << (hasil->stick ? "Ya" : "Tidak") << endl;
                        cout << "TV: " << (hasil->tv ? "Ya" : "Tidak") << endl;
                    } else {
                        cout << "Data tidak ditemukan.\n";
                    }
                    break;
                }
            case 4: // Urutkan data penyewa
                rps.urutkan();
                break;
            case 5: // Tampilkan data penyewa
                rps.tampilkan();
                break;
            case 6: // Keluar
                cout << "Program selesai. Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 6);
    return 0;
}

