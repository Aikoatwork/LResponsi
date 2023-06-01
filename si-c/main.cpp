#include <iostream>
#include <string>
using namespace std;

// Struktur data untuk buku
struct Book {
    string title;
    string author;
    string status;
    Book* next;
};

// Fungsi untuk memasukkan data buku baru
void inputDataBook(Book*& head) {
    Book* newBook = new Book;
    cout << "Masukkan Judul Buku: ";
    cin.ignore();
    getline(cin, newBook->title);
    cout << "Masukkan Penulis Buku: ";
    getline(cin, newBook->author);
    cout << "Masukkan Status Buku (tersedia/dipinjam): ";
    getline(cin, newBook->status);
    newBook->next = head;
    head = newBook;
    cout << "Buku berhasil ditambahkan!" << endl;
}

// Fungsi untuk melihat data buku
void viewDataBook(Book* head) {
    if (head == NULL) {
        cout << "Data buku kosong." << endl;
        return;
    }

    cout << "Data Buku:" << endl;
    while (head != NULL) {
        cout << "Judul: " << head->title << endl;
        cout << "Penulis: " << head->author << endl;
        cout << "Status: " << head->status << endl;
        cout << "=============================" << endl;
        head = head->next;
    }
}

// Fungsi untuk menghapus data buku
void deleteDataBook(Book*& head) {
    if (head == NULL) {
        cout << "Data buku kosong." << endl;
        return;
    }

    string title;
    cout << "Masukkan Judul Buku yang akan dihapus: ";
    cin.ignore();
    getline(cin, title);

    Book* prev = NULL;
    Book* current = head;
    while (current != NULL) {
        if (current->title == title) {
            if (prev == NULL) {
                head = head->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Buku berhasil dihapus!" << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Buku tidak ditemukan." << endl;
}

// Fungsi untuk meminjam buku
void borrowBook(Book*& head, Book*& borrowedBooks) {
    if (head == NULL) {
        cout << "Data buku kosong." << endl;
        return;
    }

    string title;
    cout << "Masukkan Judul Buku yang ingin dipinjam: ";
    cin.ignore();
    getline(cin, title);

    Book* prev = NULL;
    Book* current = head;
    while (current != NULL) {
        if (current->title == title) {
            if (current->status == "tersedia") {
                // Ubah status buku menjadi "dipinjam"
                current->status = "dipinjam";

                // Tambahkan buku ke dalam borrowedBooks (queue)
                Book* borrowedBook = new Book;
                borrowedBook->title = current->title;
                borrowedBook->author = current->author;
                borrowedBook->status = current->status;
                borrowedBook->next = NULL;

                if (borrowedBooks == NULL) {
                    borrowedBooks = borrowedBook;
                } else {
                    Book* lastBook = borrowedBooks;
                    while (lastBook->next != NULL) {
                        lastBook = lastBook->next;
                    }
                    lastBook->next = borrowedBook;
                }

                cout << "Buku berhasil dipinjam!" << endl;
            } else {
                cout << "Buku sedang tidak tersedia." << endl;
            }
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Buku tidak ditemukan." << endl;
}

// Fungsi untuk mengembalikan buku
void returnBook(Book*& head, Book*& borrowedBooks) {
    if (borrowedBooks == NULL) {
        cout << "Anda belum meminjam buku." << endl;
        return;
    }

    Book* returnedBook = borrowedBooks;
    borrowedBooks = borrowedBooks->next;

    // Ubah status buku yang dikembalikan menjadi "tersedia"
    Book* current = head;
    while (current != NULL) {
        if (current->title == returnedBook->title) {
            current->status = "tersedia";
            break;
        }
        current = current->next;
    }

    cout << "Buku berhasil dikembalikan!" << endl;
    cout << "Buku yang dikembalikan:" << endl;
    cout << "Judul: " << returnedBook->title << endl;
    cout << "Penulis: " << returnedBook->author << endl;
    cout << "Status: " << returnedBook->status << endl;
    delete returnedBook;
}

// Fungsi untuk menampilkan menu admin
void adminMenu(Book*& head) {
    int choice;
    while (true) {
        cout << "\nMenu Admin:" << endl;
        cout << "1. Input Data Buku" << endl;
        cout << "2. Lihat Data Buku" << endl;
        cout << "3. Hapus Data Buku" << endl;
        cout << "4. Kembali ke Menu Awal" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputDataBook(head);
                break;
            case 2:
                viewDataBook(head);
                break;
            case 3:
                deleteDataBook(head);
                break;
            case 4:
                return;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

// Fungsi untuk menampilkan menu pengguna
void userMenu(Book* head, Book*& borrowedBooks) {
    int choice;
    while (true) {
        cout << "\nMenu Pengguna:" << endl;
        cout << "1. Lihat Data Buku" << endl;
        cout << "2. Pinjam Buku" << endl;
        cout << "3. Kembalikan Buku" << endl;
        cout << "4. Kembali ke Menu Awal" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewDataBook(head);
                break;
            case 2:
                borrowBook(head, borrowedBooks);
                break;
            case 3:
                returnBook(head, borrowedBooks);
                break;
            case 4:
                return;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
}

// Fungsi utama
int main() {
    Book* head = NULL; // Linked list data buku
    Book* borrowedBooks = NULL; // Queue buku yang dipinjam

    int userType;
    while (true) {
        cout << "Selamat datang di Sistem Perpustakaan!" << endl;
        cout << "1. Masuk sebagai Admin" << endl;
        cout << "2. Masuk sebagai Pengguna" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> userType;

        switch (userType) {
            case 1:
                adminMenu(head);
                break;
            case 2:
                userMenu(head, borrowedBooks);
                break;
            case 0:
                cout << "Terima kasih telah menggunakan program ini. Sampai jumpa!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}
