#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip> //untuk setw

using namespace std;

struct siswa {
    int nomor;
    string nama;
    int nilai;
};

int main() {
    vector<siswa> daftarSiswa;

    //1. membuka file
    ifstream fileku("bacaAku.txt");

    //2. cek apakah file bisa dibuka
    if (!fileku.is_open()) {
        cout << "file gagal dibuka!" << endl;
        return 1;
    }

    //3. membaca file per baris
    string baris;
    while (getline(fileku, baris)) {
        //melewati baris kosong
        if(baris.empty()) continue;

        siswa s;
        stringstream ss(baris);

        string token;
        getline(ss, token, ';');
        s.nomor = stoi(token);

        getline(ss, token, ';');
        s.nama = token;

        //4. Tangani nama yang mungkin mencakup nilai yang dipisahkan oleh ':'
        size_t colon_pos = s.nama.find(':');
        if (colon_pos != string::npos) {
            string nilai_str = s.nama.substr(colon_pos + 1);
            s.nama = s.nama.substr(0, colon_pos);
            s.nilai = stoi(nilai_str);
        } else {
            getline(ss, token, ';');
            if (!token.empty()) {
                s.nilai = stoi(token);
            } else {
                s.nilai = 0;
            }
        }

        //5. simpan data ke vector
        daftarSiswa.push_back(s);
    }

    fileku.close();

    //6. tampilkan data
    cout << "\nDaftar Siswa\n";
    for (const auto& student : daftarSiswa) {
        cout << left
                << setw(6) << student.nomor
                << setw(15) << student.nama
                << setw(8) << student.nilai
                << endl;
    }
    return 0;
}
