#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Struktur Mahasiswa
struct Mahasiswa {
    int nim;
    string nama;
    int usia;
    string jurusan;
    Mahasiswa* next;
};

// Tambah Mahasiswa baru ke dalam linked list
void tambahMahasiswa(Mahasiswa** head, int nim, string nama, int usia, string jurusan) {
    Mahasiswa* newMahasiswa = new Mahasiswa;
    newMahasiswa->nim = nim;
    newMahasiswa->nama = nama;
    newMahasiswa->usia = usia;
    newMahasiswa->jurusan = jurusan;
    newMahasiswa->next = nullptr;

    if (*head == nullptr) {
        *head = newMahasiswa;
    } else {
        Mahasiswa* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newMahasiswa;
    }
}

// Hapus Mahasiswa berdasarkan NIM
void hapusMahasiswa(Mahasiswa** head, int nim) {
    if (*head == nullptr) {
        cout << "Linked list kosong" << endl;
        return;
    }

    if ((*head)->nim == nim) {
        Mahasiswa* temp = *head;
        *head = (*head)->next;
        delete temp;
        cout << "Mahasiswa dengan NIM " << nim << " berhasil dihapus" << endl;
        return;
    }

    Mahasiswa* prev = *head;
    Mahasiswa* curr = (*head)->next;
    while (curr != nullptr && curr->nim != nim) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan" << endl;
    } else {
        prev->next = curr->next;
        delete curr;
        cout << "Mahasiswa dengan NIM " << nim << " berhasil dihapus" << endl;
    }
}

// Tampilkan seluruh data Mahasiswa dalam linked list
void tampilkanMahasiswa(Mahasiswa* head) {
    if (head == nullptr) {
        cout << "Linked list kosong" << endl;
        return;
    }

    cout << "Data Mahasiswa:" << endl;
    Mahasiswa* temp = head;
    while (temp != nullptr) {
        cout << "NIM: " << temp->nim << endl;
        cout << "Nama: " << temp->nama << endl;
        cout << "Usia: " << temp->usia << endl;
        cout << "Jurusan: " << temp->jurusan << endl;
        cout << endl;
        temp = temp->next;
    }
}

// Cari Mahasiswa berdasarkan NIM
Mahasiswa* cariMahasiswa(Mahasiswa* head, int nim) {
    Mahasiswa* temp = head;
    while (temp != nullptr) {
        if (temp->nim == nim) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Bubble Sort untuk mengurutkan data Mahasiswa berdasarkan NIM
void bubbleSortMahasiswa(Mahasiswa** head) {
    if (*head == nullptr || (*head)->next == nullptr) {
        return;
    }

    bool swapped;
    Mahasiswa* curr;
    Mahasiswa* last = nullptr;
    do {
        swapped = false;
        curr = *head;

        while (curr->next != last) {
            if (curr->nim > curr->next->nim) {
                swap(curr->nim, curr->next->nim);
                swap(curr->nama, curr->next->nama);
                swap(curr->usia, curr->next->usia);
                swap(curr->jurusan, curr->next->jurusan);
                swapped = true;
            }
            curr = curr->next;
        }
        last = curr;
    } while (swapped);
}

// Quick Sort untuk mengurutkan data Mahasiswa berdasarkan NIM
Mahasiswa* partition(Mahasiswa* head, Mahasiswa* tail, Mahasiswa** newHead, Mahasiswa** newTail) {
    Mahasiswa* pivot = tail;
    Mahasiswa* prev = nullptr;
    Mahasiswa* curr = head;
    Mahasiswa* end = tail;

    while (curr != pivot) {
        if (curr->nim < pivot->nim) {
            if (*newHead == nullptr) {
                *newHead = curr;
            }
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) {
                prev->next = curr->next;
            }
            Mahasiswa* temp = curr->next;
            curr->next = nullptr;
            end->next = curr;
            end = curr;
            curr = temp;
        }
    }

    if (*newHead == nullptr) {
        *newHead = pivot;
    }

    *newTail = end;
    return pivot;
}

Mahasiswa* quickSortRec(Mahasiswa* head, Mahasiswa* tail) {
    if (head == nullptr || head == tail) {
        return head;
    }

    Mahasiswa* newHead = nullptr;
    Mahasiswa* newTail = nullptr;
    Mahasiswa* pivot = partition(head, tail, &newHead, &newTail);

    if (newHead != pivot) {
        Mahasiswa* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;
        newHead = quickSortRec(newHead, temp);
        temp = cariMahasiswa(newHead, pivot->nim);
        temp->next = pivot;
    }
    pivot->next = quickSortRec(pivot->next, newTail);

    return newHead;
}

void quickSortMahasiswa(Mahasiswa** head) {
    if (*head == nullptr || (*head)->next == nullptr) {
        return;
    }

    Mahasiswa* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    *head = quickSortRec(*head, temp);
}

// Simpan data Mahasiswa ke dalam file
void simpanDataMahasiswaKeFile(Mahasiswa* head, string namaFile) {
    ofstream file(namaFile);

    if (!file) {
        cout << "Gagal membuka file" << endl;
        return;
    }

    Mahasiswa* temp = head;
    while (temp != nullptr) {
        file << temp->nim << "," << temp->nama << "," << temp->usia << "," << temp->jurusan << endl;
        temp = temp->next;
    }

    file.close();
    cout << "Data Mahasiswa berhasil disimpan ke dalam file" << endl;
}

// Baca data Mahasiswa dari file
void bacaDataMahasiswaDariFile(Mahasiswa** head, string namaFile) {
    ifstream file(namaFile);

    if (!file) {
        cout << "Gagal membuka file" << endl;
        return;
    }

    int nim, usia;
    string nama, jurusan;
    char delimiter;
    while (file >> nim >> delimiter && getline(file, nama, ',') && file >> usia >> delimiter && getline(file, jurusan)) {
        tambahMahasiswa(head, nim, nama, usia, jurusan);
    }

    file.close();
    cout << "Data Mahasiswa berhasil dibaca dari file" << endl;
}

// Fungsi untuk membersihkan linked list
void clearLinkedList(Mahasiswa** head) {
    Mahasiswa* temp = *head;
    while (temp != nullptr) {
        Mahasiswa* next = temp->next;
        delete temp;
        temp = next;
    }
    *head = nullptr;
}

int main() {
    Mahasiswa* head = nullptr;
    int pilihan;
    string namaFile;

    do {
        cout << "Menu Utama:" << endl;
        cout << "1. Tambah Mahasiswa" << endl;
        cout << "2. Hapus Mahasiswa" << endl;
        cout << "3. Tampilkan Mahasiswa" << endl;
        cout << "4. Cari Mahasiswa" << endl;
        cout << "5. Urutkan Mahasiswa (Bubble Sort)" << endl;
        cout << "6. Urutkan Mahasiswa (Quick Sort)" << endl;
        cout << "7. Simpan Data Mahasiswa ke File" << endl;
        cout << "8. Baca Data Mahasiswa dari File" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int nim, usia;
                string nama, jurusan;

                cout << "NIM: ";
                cin >> nim;
                cout << "Nama: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Usia: ";
                cin >> usia;
                cout << "Jurusan: ";
                cin.ignore();
                getline(cin, jurusan);

                tambahMahasiswa(&head, nim, nama, usia, jurusan);
                break;
            }
            case 2: {
                int nim;

                cout << "NIM Mahasiswa yang akan dihapus: ";
                cin >> nim;

                hapusMahasiswa(&head, nim);
                break;
            }
            case 3: {
                tampilkanMahasiswa(head);
                break;
            }
            case 4: {
                int nim;

                cout << "NIM Mahasiswa yang akan dicari: ";
                cin >> nim;

                Mahasiswa* mahasiswa = cariMahasiswa(head, nim);
                if (mahasiswa != nullptr) {
                    cout << "Mahasiswa ditemukan:" << endl;
                    cout << "NIM: " << mahasiswa->nim << endl;
                    cout << "Nama: " << mahasiswa->nama << endl;
                    cout << "Usia: " << mahasiswa->usia << endl;
                    cout << "Jurusan: " << mahasiswa->jurusan << endl;
                } else {
                    cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan" << endl;
                }
                break;
            }
            case 5: {
                bubbleSortMahasiswa(&head);
                cout << "Data Mahasiswa berhasil diurutkan menggunakan Bubble Sort" << endl;
                break;
            }
            case 6: {
                quickSortMahasiswa(&head);
                cout << "Data Mahasiswa berhasil diurutkan menggunakan Quick Sort" << endl;
                break;
            }
            case 7: {
                cout << "Masukkan nama file: ";
                cin >> namaFile;
                simpanDataMahasiswaKeFile(head, namaFile);
                break;
            }
            case 8: {
                cout << "Masukkan nama file: ";
                cin >> namaFile;
                bacaDataMahasiswaDariFile(&head, namaFile);
                break;
            }
            case 9: {
                clearLinkedList(&head);
                cout << "Program selesai" << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid" << endl;
                break;
            }
        }

        cout << endl;

    } while (pilihan != 9);

    return 0;
}
