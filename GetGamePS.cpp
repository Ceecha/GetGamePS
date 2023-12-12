#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Struct untuk menyimpan informasi pemain
struct Pemain {
    string nama;
    int id;
};

// Struct untuk menyimpan informasi game
struct Game {
    string nm_game;
    int id;
};

int main() {
    const int MAX_PEMAIN = 10;
    const int MAX_GAME = 5;

    Pemain pemain[MAX_PEMAIN];
    Game game[MAX_GAME];

    int jmlhPemain = 0;
    int jmlhGame = 0;

    int* playerQueue = new int[MAX_PEMAIN]; // menggunakan array sebagai antrian pemain
    int queueFront = 0;
    int queueRear = 0;

    while (true) {
        cout << "=== Rental PS Management ===" << endl;
        cout << "1. Tambah Pemain" << endl;
        cout << "2. Keluarkan Pemain" << endl;
        cout << "3. Lihat Antrian Pemain" << endl;
        cout << "4. Tambah Game" << endl;
        cout << "5. Pilih Game" << endl;
        cout << "6. Lihat Status PS" << endl;
        cout << "7. Keluar dari Program" << endl;

        int pilih;
        cout << "Pilih menu (1-8): ";
        cin >> pilih;

        switch (pilih) {
            case 1: // Tambah Pemain
                if (jmlhPemain < MAX_PEMAIN) {
                    Pemain pemainBaru;
                    cout << "Masukkan nama pemain: ";
                    cin >> pemainBaru.nama;
                    pemainBaru.id = jmlhPemain + 1;
                    pemain[jmlhPemain++] = pemainBaru;
                    playerQueue[queueRear] = jmlhPemain - 1;
                    queueRear = (queueRear + 1) % MAX_PEMAIN;
                    cout << "Pemain berhasil ditambahkan." << endl;
                } else {
                    cout << "Antrian pemain penuh. Tidak dapat menambahkan pemain baru." << endl;
                }
                cout << endl;
                break;

            case 2: // Keluarkan Pemain
                if (queueFront != queueRear) {
                    int removedPlayerIndex = playerQueue[queueFront];
                    cout << pemain[removedPlayerIndex].nama << " keluar dari antrian." << endl;
                    queueFront = (queueFront + 1) % MAX_PEMAIN;
                } else {
                    cout << "Antrian pemain kosong. Tidak ada pemain untuk dikeluarkan." << endl;
                }
                cout << endl;
                break;

            case 3: // Lihat Antrian Pemain
                if (queueFront != queueRear) {
                    cout << "Antrian Pemain:" << endl;
                    int i = queueFront;
                    do {
                        cout << pemain[playerQueue[i]].id << ". " << pemain[playerQueue[i]].nama << endl;
                        i = (i + 1) % MAX_PEMAIN;
                    } while (i != queueRear);
                } else {
                    cout << "Antrian pemain kosong." << endl;
                }
                cout << endl;
                break;

            case 4: // Tambah Game
                if (jmlhGame < MAX_GAME) {
                    Game gameBaru;
                    cout << "Masukkan nama game: ";
                    cin >> gameBaru.nm_game;
                    gameBaru.id = jmlhGame + 1;
                    game[jmlhGame++] = gameBaru;
                    cout << "Game berhasil ditambahkan." << endl;
                } else {
                    cout << "Daftar game penuh. Tidak dapat menambahkan game baru." << endl;
                }
                cout << endl;
                break;

            case 5: // Pilih Game
			    if (jmlhGame > 0) {
			        cout << "Daftar Game:" << endl;
			        for (int i = 0; i < jmlhGame; ++i) {
			            cout << game[i].id << ". " << game[i].nm_game << endl;
			        }
			
			        int idGame;
			        cout << "Masukkan ID game yang dipilih: ";
			        cin >> idGame;
			
			        if (idGame > 0 && idGame <= jmlhGame) {
			            cout << "Anda memilih game: " << game[idGame - 1].nm_game << endl;
			        } else {
			            cout << "ID game tidak valid." << endl;
			        }
			    } else {
			        cout << "Daftar game kosong." << endl;
			    }
			    cout << endl;
			    break;

            case 6: // Lihat Status PS
                // Implementasikan sesuai kebutuhan
                cout << "Status PS: Normal" << endl;
                cout << endl;
                break;

            case 7: // Keluar dari Program
                cout << "<Terima kasih telah bermain di Rental PS kami (SYALALA PS Group)>" << endl;
                delete[] playerQueue; // hapus alokasi memori dinamis
                return 0;

            default:
                cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
        }
    }

    return 0;
}

/* Program C++ di atas adalah implementasi sederhana untuk manajemen rental PS dengan beberapa fitur seperti menambahkan pemain, 
mengeluarkan pemain, melihat antrian pemain, menambah game, memilih game, dan melihat status PS. 
Berikut adalah penjelasan singkat untuk setiap bagian program:

1. Struct Pemain dan Game:
	* Dua struktur, 'Pemain' dan 'Game', digunakan untuk menyimpan informasi pemain dan game.
	
2. Deklarasi Variabel dan Konstanta:
	* MAX_PEMAIN dan MAX_GAME adalah konstanta yang menentukan batas maksimum pemain dan game.
	* 'pemain' dan 'game' adalah array untuk menyimpan data pemain dan game.
	* 'jmlhPemain' dan 'jmlhGame' adalah variabel untuk menghitung jumlah pemain dan game.
	* 'playerQueue' adalah array dinamis sebagai antrian pemain dengan konsep circular queue.
	
3. Loop Utama:
	* Program berjalan dalam loop utama yang terus berjalan hingga pengguna memilih keluar.

4. Menu Utama:
	* Menampilkan opsi-opsi menu kepada pengguna.

5. Switch Case untuk Opsi Menu:
	* Program menggunakan 'switch' untuk menangani berbagai opsi menu yang dapat dipilih oleh pengguna.

6. Tambah Pemain (Case 1):
	* Meminta pengguna untuk memasukkan nama pemain baru.
	* Menambahkan pemain ke dalam array 'pemain' dan ID pemain ke dalam antrian 'playerQueue'.

7. Keluarkan Pemain (Case 2):
	* Mengeluarkan pemain dari antrian setelah selesai bermain dan menampilkan nama pemain yang keluar.

8. Lihat Antrian Pemain (Case 3):
	* Menampilkan antrian pemain menggunakan circular queue.

9. Tambah Game (Case 4):
	* Meminta pengguna untuk memasukkan nama game baru.
	* Menambahkan game ke dalam array game.

10. Pilih Game (Case 5):
	* Menampilkan daftar game dan meminta pengguna untuk memilih game berdasarkan ID.

11. Lihat Status PS (Case 6):
	* Menampilkan status PS, dalam hal ini ditampilkan "Normal".

12. Keluar dari Program (Case 7):
	* Memberikan pesan terima kasih dan menghapus alokasi memori dinamis untuk playerQueue.

*/


