#ifndef TUBASNABILA9FIX_H
#define TUBASNABILA9FIX_H

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> // Untuk std::find_if, std::transform, std::swap

using namespace std;

// ================== KONSTANTA UKURAN ==================
const int MAX_MAPEL = 20;
const int MAX_SISWA = 60;
const int MAX_GURU = 40;
const int MAX_TRANSAKSI = 200;
const int MAX_EVENT = 60;
const int MAX_USERS = MAX_SISWA + MAX_GURU + 10;
const int MAX_LAPORAN = 50;
const int MAX_SURAT = 80;
const int MAX_ARSIP = 100;
const int MAX_INVENTARIS = 100;
const int MAX_STRUKTUR = 30;
const int MAX_HARI = 5;
const int MAX_KEGIATAN_PER_HARI = 10;
const int MAX_NILAI_COMPONENT = 4;
const int MAX_SOAL_KUIS = 10;
const int MAX_MATERI = 50;
// KONSTANTA BARU MODUL 6
const int MAX_ANTRIAN_DOKUMEN = 20;
const int CLEAR_BUFFER = 999999;
// KONSTANTA BARU MODUL 10 (TRIE - tidak digunakan di versi ini)
const int ALPHABET_SIZE = 26; 


void clearInput();
void clearScreen();
void pauseProgram();

// ================== KELAS-KELAS STANDAR ==================

class MataPelajaran {
private:
    string kode;
    string nama;
    string guruPengampu;
public:
    MataPelajaran() : kode(""), nama(""), guruPengampu("") {}
    void setData(const string &k, const string &n, const string &g) {
        kode = k;
        nama = n;
        guruPengampu = g;
    }
    string getKode() const { return kode; }
    string getNama() const { return nama; }
    string getGuru() const { return guruPengampu; }
    void tampil() const {
        cout << left << setw(8) << kode << " | " << setw(25) << nama << " | " << setw(15) << guruPengampu << '\n';
    }
};

class Jadwal {
private:
    string table[MAX_HARI][8];
public:
    Jadwal() {
        for (int d = 0; d < MAX_HARI; ++d)
            for (int h = 0; h < 8; ++h)
                table[d][h] = "-";
    }
    void setJam(int hari, int jam, const string &kode) {
        if (hari >= 0 && hari < MAX_HARI && jam >= 0 && jam < 8) table[hari][jam] = kode;
    }
    void tampil() const {
        cout << "Hari\\Jam | ";
        for (int h = 0; h < 8; ++h)
            cout << "J" << (h+1) << "  ";
        cout << '\n';
        for (int d = 0; d < MAX_HARI; ++d) {
            cout << left << setw(8) << ("Hari " + to_string(d+1)) << "| ";
            for (int h = 0; h < 8; ++h)
                cout << setw(3) << table[d][h] << " ";
            cout << '\n';
        }
    }
    int countAssigned() const {
        int count = 0;
        for (int d = 0; d < MAX_HARI; ++d) {
            for (int h = 0; h < 8; ++h) {
                if (table[d][h] != "-") {
                    count++;
                }
            }
        }
        return count;
    }
    string getMapelCode(int hari, int jam) const {
        if (hari >= 0 && hari < MAX_HARI && jam >= 0 && jam < 8) {
            return table[hari][jam];
        }
        return "";
    }
};

class Event {
private:
    string tanggal;
    string deskripsi;
public:
    Event() : tanggal(""), deskripsi("") {}
    void setData(const string &t, const string &d) { 
	tanggal = t; 
	deskripsi = d; 
    }
    void tampil() const {
        cout << tanggal << " : " << deskripsi << '\n';
    }
};

class Penilaian {
public:
    double komponen[MAX_NILAI_COMPONENT];
    Penilaian() {
        for (int i=0;i<MAX_NILAI_COMPONENT;++i)
            komponen[i]= -1.0;
    }
    double rata() const {
        double sum=0; int c=0;
        for (int i=0;i<MAX_NILAI_COMPONENT;++i)
            if (komponen[i] >= 0) {
                sum += komponen[i];
                ++c;
            }
        return (c==0) ? 0.0 : sum / c;
    }
};

class Siswa {
private:
    string nis;
    string nama;
    string kelas;
    bool hadir[365];
public:
    Siswa() : nis(""), nama(""), kelas("") {
        for (int i=0;i<365;++i) hadir[i]=false;
    }
    void setData(const string &id, const string &n, const string &k) {
        nis = id;
        nama = n;
        kelas = k;
    }
    string getId() const {
        return nis;
    }
    string getNama() const {
        return nama;
    }
    string getKelas() const {
        return kelas;
    }
    void tampilRingkas() const {
        cout << left << setw(8) << nis << " | " << setw(20) << nama << " | Kelas: " << kelas << '\n';
    }
    void setHadir(int hariIndex, bool v) { if (hariIndex>=0 && hariIndex<365) hadir[hariIndex] = v; }
    int hitungHadir() const {
        int count = 0;
        for (int idx = 0; idx < 365; ++idx) {
            if (hadir[idx]) {
                count++;
            }
        }
        return count;
    }
    double hitungPersenHadir() const {
        return (365 == 0) ? 0.0 : (hitungHadir() * 100.0 / 365.0);
    }
};

class Guru {
private:
    string nip;
    string nama;
    string mapel;
    string senioritas; // BARU: Untuk DLL Senioritas
public:
    Guru() : nip(""), nama(""), mapel(""), senioritas("") {}
    void setData(const string &id, const string &n, const string &m, const string &s) {
        nip=id;
        nama=n;
        mapel=m;
        senioritas=s;
    }
    string getNip() const {
        return nip;
    }
    string getNama() const {
        return nama;
    }
    string getMapel() const {
        return mapel;
    }
    string getSenioritas() const { // BARU
        return senioritas;
    }
    void tampil() const {
        cout << left << setw(8) << nip << " | " << setw(20) << nama << " | " << setw(15) << mapel << " | Senioritas: " << senioritas << '\n';
    }
};

class Transaksi {
private:
    string id;
    string siswaId;
    double jumlah;
    string keterangan;
public:
    Transaksi() : id(""), siswaId(""), jumlah(0.0), keterangan("") {}
    void setData(const string &i, const string &sid, double j, const string &k) {	
	    id=i;	
		siswaId=sid;	
		jumlah=j;	
		keterangan=k;	
	}
    double getJumlah() const {	
	    return jumlah;	
	}
    void tampil() const {
        cout << left << setw(8) << id << " | " << setw(8) << siswaId << " | Rp " << setw(10) << fixed << setprecision(0) << jumlah << " | " << keterangan << '\n';
    }
};

class User {
private:
    string username;
    string password;
    string role;
    string nis;
public:
    User() : username(""), password(""), role(""), nis("") {}
    void setData(const string &u, const string &p, const string &r, const string &n) {
        username=u; password=p; role=r; nis=n;
    }
    bool auth(const string &u, const string &p) const {	
	    return (username==u && password==p);	
    }
    string getRole() const {	
	    return role;	
	}
    string getUser() const {	
	    return username;	
	}
    string getPassword() const {	
	    return password;	
	}
    string getNis() const {	
	    return nis;	
	}
};

class Laporan {
private:
    string id;
    string isi;
public:
    Laporan() : id(""), isi("") {}
    void setData(const string &i, const string &s) {	
	    id = i; isi = s;	
	}
    string getId() const {	
	    return id;	
	}
    void tampil() const {	
	    cout << id << " | " << isi << '\n';	
	}
};

class ProfilSekolah {
private:
    string nama;
    string alamat;
    string akreditasi;
    string visi;
    string misi;
public:
    ProfilSekolah() : nama("Nama Sekolah"), alamat("Alamat Sekolah"), akreditasi("A"), visi("Visi Sekolah"), misi("Misi Sekolah") {}
    void setData(const string &n, const string &a, const string &ak, const string &v, const string &m) {
        nama=n;	
		alamat=a;	
		akreditasi=ak;	
		visi=v;	
		misi=m;
    }
    void tampil() const {
        cout << "\n=== PROFIL SEKOLAH ===\n";
        cout << "Nama    : " << nama << '\n';
        cout << "Alamat  : " << alamat << '\n';
        cout << "Akredit : " << akreditasi << '\n';
        cout << "Visi    : " << visi << '\n';
        cout << "Misi    : " << misi << '\n';
    }
};

class StrukturOrganisasi {
private:
    string jabatan[MAX_STRUKTUR];
    string nama[MAX_STRUKTUR];
    int jumlah;
public:
    StrukturOrganisasi() : jumlah(0) {}
    void tambah(const string &j, const string &n) {
        if (jumlah < MAX_STRUKTUR) {
            jabatan[jumlah] = j;	
			nama[jumlah] = n;	
			jumlah++;
            cout << "Ditambahkan.\n";
        } else cout << "Kapasitas struktur penuh.\n";
    }
    void tampil() const {
        for (int idx = 0; idx < jumlah; ++idx) {
            cout << left << setw(20) << jabatan[idx] << " : " << nama[idx] << '\n';
        }
    }
};

class Surat {
private:
    string nomor;
    string jenis;
    string tanggal;
    string perihal;
public:
    Surat() : nomor(""), jenis(""), tanggal(""), perihal("") {}
    void setData(const string &no, const string &j, const string &t, const string &p) {
        nomor = no;	
		jenis = j;	
		tanggal = t;	
		perihal = p;
    }
    string getNomor() const {	
	    return nomor;	
	}
    string getPerihal() const {	
	    return perihal;	
	}
    void tampil() const {
        cout << left << setw(12) << nomor << setw(10) << jenis << setw(14) << tanggal << perihal;
        cout << endl;
    }
};

class ManajemenSurat {
private:
    Surat daftar[MAX_SURAT];
    int jumlah;
public:
    ManajemenSurat() : jumlah(0) {}
    void tambah(const Surat& s) {
        if (jumlah >= MAX_SURAT) {	
		cout << "Kapasitas surat penuh.\n";	
		return;	
	}
        daftar[jumlah] = s;
        jumlah++;
        cout << "Surat tersimpan.";
        cout << endl;
    }
    void tambah() {
        if (jumlah >= MAX_SURAT) {	
		cout << "Kapasitas surat penuh.\n";	
		return;	
	}
        string no,j,t,p;
        cout << "Nomor: ";
        getline(cin,no);
        cout << "Jenis (Masuk/Keluar): ";
        getline(cin,j);
        cout << "Tanggal: ";
        getline(cin,t);
        cout << "Perihal: ";
        getline(cin,p);
        daftar[jumlah].setData(no,j,t,p);
        jumlah++;
        cout << "Surat tersimpan.\n";
    }
    void tampil() const {
        for (int idx = 0; idx < jumlah; ++idx) {
            daftar[idx].tampil();
        }
    }
    void hapus() {
        string no; cout << "Nomor surat yang dihapus: ";	
		getline(cin,no);
        for (int i=0;i<jumlah;++i) {
            if (daftar[i].getNomor() == no) {
                for (int j=i;j<jumlah-1;++j) daftar[j] = daftar[j+1];
                jumlah--;
                cout << "Dihapus.";
                cout << endl;
                return;
            }
        }
        cout << "Tidak ditemukan.";
        cout << endl;
    }
    int getJumlah() const {	
	    return jumlah;	
	}
};

class Arsip {
private:
    string judul[MAX_ARSIP];
    string tanggal[MAX_ARSIP];
    int jumlah;
public:
    Arsip() : jumlah(0) {}
    void tambah() {
        if (jumlah >= MAX_ARSIP) {	
		cout << "Kapasitas arsip penuh.\n";	
		return;	
	}
        string j,t;	
		cout << "Judul: ";	
		getline(cin,j);
        cout << "Tanggal: ";	
		getline(cin,t);
        judul[jumlah] = j;	
		tanggal[jumlah] = t;	
		jumlah++;
        cout << "Arsip ditambahkan.";
        cout << endl;
    }
    void tampil() const {
        for (int idx = 0; idx < jumlah; ++idx) {
            cout << left << setw(40) << judul[idx] << " (" << tanggal[idx] << ")";
            cout << endl;
        }
    }
};

class Inventaris {
private:
    string namaBarang[MAX_INVENTARIS];
    string kategori[MAX_INVENTARIS];
    string lokasi[MAX_INVENTARIS];
    int jumlahBarang[MAX_INVENTARIS];
    int total;
public:
    Inventaris() : total(0) {}
    void tambah() {
        if (total >= MAX_INVENTARIS) {	
		cout << "Kapasitas penuh.\n";	
		return;	
	}
        string n,k,l;	
		int j;
        cout << "Nama barang: ";
        getline(cin,n);
        cout << "Kategori: ";
        getline(cin,k);
        cout << "Lokasi: ";
        getline(cin,l);
        cout << "Jumlah: ";
        cin >> j;	
		clearInput();
        namaBarang[total]=n;	
		kategori[total]=k;	
		lokasi[total]=l;	
		jumlahBarang[total]=j;	
		total++;
        cout << "Barang ditambahkan.\n";
    }
    void tampil() const {
        for (int idx = 0; idx < total; ++idx) {
            cout << left << setw(25) << namaBarang[idx] << setw(15) << kategori[idx] << setw(12) << lokasi[idx] << jumlahBarang[idx] ;
            cout << endl;
        }
    }
    int totalBarang() const {
        int sum = 0;
        for (int idx = 0; idx < total; ++idx) {
            sum += jumlahBarang[idx];
        }
        return sum;
    }
};

class JadwalKegiatan {
private:
    string hari[MAX_HARI];
    string kegiatan[MAX_HARI][MAX_KEGIATAN_PER_HARI];
public:
    JadwalKegiatan() {
        hari[0]="Senin";	
		hari[1]="Selasa";	
		hari[2]="Rabu";	
		hari[3]="Kamis";	
		hari[4]="Jumat";
        for (int i=0;i<MAX_HARI;++i)
            for (int j=0;j<MAX_KEGIATAN_PER_HARI;++j)
                kegiatan[i][j] = "-";
    }
    void isiHari() {
        int h;
        cout << "Pilih hari (0=Senin..4=Jumat): ";
        if (!(cin>>h)) {	
		clearInput();
        cout<<"Input salah\n";	
		return;	
	}
        clearInput();
        if (h < 0 || h >= MAX_HARI) {
        cout << "Hari tidak valid\n";
        return;
        }
        for (int k=0;k<MAX_KEGIATAN_PER_HARI;++k) {
            cout << "Kegiatan ke-" << (k+1) << " (kosong=tidak diisi): ";
            string s;
            getline(cin,s);
            if (s.size() > 0) kegiatan[h][k] = s;
        }
    }
    void tampilSemua() const {
        for (int hariIndex = 0; hariIndex < MAX_HARI; ++hariIndex) {
            cout << hari[hariIndex] << ":";
            cout << endl;
            for (int kIndex = 0; kIndex < MAX_KEGIATAN_PER_HARI; ++kIndex) {
                cout << "- " << kegiatan[hariIndex][kIndex] ;
                cout << endl;
            }
        }
    }
};


// ================== KELAS MODUL 3 - MATERI MENGGUNAKAN STACK ARRAY ==================
class MateriStack {
private:
    string judul[MAX_MATERI];
    string url[MAX_MATERI];
    int top; // Pointer to the top of the stack (Last-In, First-Out)
public:
    MateriStack() : top(-1) {}

    // PUSH operation (Tambah Materi)
    void push(const string &j, const string &u) {
        if (top >= MAX_MATERI - 1) {
            cout << "Stack materi penuh. Tidak bisa menambah materi lagi.\n";
            return;
        }
        top++;
        judul[top] = j;
        url[top] = u;
        cout << "Materi (STACK) ditambahkan.\n";
    }

    // POP operation (Hapus Materi Teratas)
    void pop() {
        if (top < 0) {
            cout << "Stack materi kosong. Tidak ada yang bisa dihapus.";
            cout << endl;
            return;
        }
        cout << "Materi teratas dihapus: " << judul[top] ;
        cout << endl;
        top--;
    }
	
	// PEEK operation (Lihat Materi Teratas) - FITUR TAMBAHAN
	void peek() const {
		if (top < 0) {
			cout << "Stack materi kosong. Tidak ada materi teratas.";
			cout << endl;
			return;
		}
		cout << "\n--- MATERI TERATAS (PEEK) ---\n";
		cout << "Judul : " << judul[top] << "\n";
		cout << "URL  : " << url[top] << "\n";
	}
    
    // Tampil (Iterate from top down, showing latest first)
    void tampil() const {
        if (top < 0) {
            cout << "Belum ada materi (Stack kosong).";
            cout << endl;
            return;
        }
        cout << "--- Daftar Materi (Terbaru di Atas) ---";
        cout << endl;
        for (int i = top; i >= 0; --i) {	
            cout << left << setw(2) << (top - i + 1) << ". " << judul[i] << " (" << url[i] << ")";
            cout << endl;
        }
    }
};

// ================== KELAS MODUL 5 - PERSETUJUAN MENGGUNAKAN QUEUE ARRAY ==================
struct ApprovalItem {
    string id;
    string tipe; // Surat, Laporan, Data Siswa
    string deskripsi;
    bool disetujui;
    ApprovalItem() : id(""), tipe(""), deskripsi(""), disetujui(false) {}
};

class ManajemenPersetujuan {
private:
    ApprovalItem daftar[MAX_LAPORAN]; // Reuse MAX_LAPORAN for queue size
    int front; // front of queue (dequeue/peek)
    int rear;	// rear of queue (enqueue)
    int count;

public:
    ManajemenPersetujuan() : front(0), rear(-1), count(0) {}

    // Enqueue operation (Tambah Persetujuan)
    void tambah(const string &id, const string &tipe, const string &desk) {
        if (count >= MAX_LAPORAN) {
            cout << "Antrian persetujuan penuh.";
            cout << endl;
            return;
        }
        rear = (rear + 1) % MAX_LAPORAN;
		
        // Menggunakan penugasan anggota eksplisit
        daftar[rear].id = id;
        daftar[rear].tipe = tipe;
        daftar[rear].deskripsi = desk;
        daftar[rear].disetujui = false;
		
        count++;
        cout << "Permintaan persetujuan ditambahkan (ID: " << id << ")";
        cout << endl;
    }

    void tampil() const {
        if (count == 0) {
            cout << "Tidak ada permintaan persetujuan tertunda.";
            cout << endl;
            return;
        }
        cout << left << setw(5) << "No." << setw(10) << "ID" << setw(15) << "Tipe" << "Deskripsi";
        cout << endl;
        cout << string(50, '-') ;
        cout << endl;
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_LAPORAN;
            cout << left << setw(5) << (i + 1)
				<< setw(10) << daftar[idx].id
				<< setw(15) << daftar[idx].tipe
				<< daftar[idx].deskripsi	
				<< (daftar[idx].disetujui ? " (Disetujui)" : " (Tertunda)") ;
				cout << endl;
        }
    }

    void prosesPersetujuan(const string &targetId) {
        int foundIdx = -1;
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_LAPORAN;
            if (daftar[idx].id == targetId && !daftar[idx].disetujui) {
                foundIdx = idx;
                break;
            }
        }
		
        if (foundIdx != -1) {
            daftar[foundIdx].disetujui = true;
            cout << "ID " << targetId << " dari tipe " << daftar[foundIdx].tipe << " berhasil disetujui.";
            cout << endl;
			
            // If the approved item is the front, dequeue it (FIFO logic)
            if (foundIdx == front) {
                front = (front + 1) % MAX_LAPORAN;
                count--;
                cout << "Item terdepan dikeluarkan dari antrian persetujuan.";
                cout << endl;
            }
        } else {
            cout << "Permintaan persetujuan tertunda dengan ID " << targetId << " tidak ditemukan atau sudah disetujui.";
            cout << endl;
        }
    }

    int getJumlahTertunda() const {
        int tertunda = 0;
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_LAPORAN;
            if (!daftar[idx].disetujui) {
                tertunda++;
            }
        }
        return tertunda;
    }
};

class Kuis {
private:
    string pertanyaan[MAX_SOAL_KUIS];
    string kunciJawaban[MAX_SOAL_KUIS];
    string jawabanSiswa[MAX_SOAL_KUIS];
    int jumlahSoal;
    string nisTerakhir;

    int cekJawaban() const {
        int skor = 0;
        for (int indexSoal = 0; indexSoal < jumlahSoal; ++indexSoal) {
            if (jawabanSiswa[indexSoal] == kunciJawaban[indexSoal]) {
                skor++;
            }
        }
        return skor;
    }
public:
    Kuis() : jumlahSoal(0), nisTerakhir("") {}

    void buatKuis() {
        cout << "Buat Kuis Baru (max " << MAX_SOAL_KUIS << " soal).";
        cout << endl;
        cout << "Jumlah soal: ";
        if (!(cin >> jumlahSoal)) {
        clearInput();
        jumlahSoal=0;
        cout<<"Input salah.";
        cout << endl;
            return;
        }
        clearInput();
        if (jumlahSoal > MAX_SOAL_KUIS) jumlahSoal = MAX_SOAL_KUIS;
        if (jumlahSoal <= 0) {	
		cout << "Jumlah soal tidak valid.";
		cout << endl;
        jumlahSoal = 0;
			return;
        }

        for (int i=0; i<jumlahSoal; ++i) {
            cout << "Pertanyaan " << (i+1) << ": ";
            getline(cin, pertanyaan[i]);
            cout << "Kunci Jawaban " << (i+1) << ": ";
            getline(cin, kunciJawaban[i]);
        }
        cout << "Kuis telah dibuat.\n";
    }

    void ambilKuis(const string &nis) {
        if (jumlahSoal == 0) {
        cout << "Belum ada kuis yang dibuat.";
        cout << endl;
        return;
        }
        nisTerakhir = nis;
        cout << "--- KUIS DIMULAI UNTUK NIS: " << nis << " ---";
        cout << endl;
        for (int i=0; i<jumlahSoal; ++i) {
            cout << (i+1) << ". " << pertanyaan[i] ;
            cout << endl;
            cout << "Jawaban: ";
            getline(cin, jawabanSiswa[i]);
        }
        cout << "--- KUIS SELESAI ---";
        cout << endl;
    }

    void nilaiKuis() {
        if (nisTerakhir == "") {
        cout << "Belum ada siswa yang mengambil kuis.";
        cout << endl;
			return;
        }

        int skorBenar = cekJawaban();
        double nilaiAkhir = (jumlahSoal == 0) ? 0.0 : (double)skorBenar / jumlahSoal * 100.0;

        cout << "--- HASIL KUIS NIS: " << nisTerakhir << " ---\n";
        cout << "Jawaban Benar: " << skorBenar << " dari " << jumlahSoal;
        cout << endl;
        cout << "Nilai Akhir: " << fixed << setprecision(2) << nilaiAkhir;
        cout << endl;
    }
};

// ================== KELAS MODUL 4: ORANG TUA/WALI - LINKED LIST VERSIONS ==================

struct NilaiNode {
    int mapelIdx;
    double nilai;
    NilaiNode* next;
    NilaiNode(int m, double n) : mapelIdx(m), nilai(n), next(nullptr) {}
};

struct KehadiranNode {
    int hariIdx;
    int status; // 0 = tidak hadir, 1 = hadir
    KehadiranNode(int h, int s) : hariIdx(h), status(s), next(nullptr) {}
    KehadiranNode* next;
};

class DataAnakOrangTua {
private:
    string nisAnak;
    NilaiNode* headNilai;
    KehadiranNode* headKehadiran;
public:
    DataAnakOrangTua() : nisAnak(""), headNilai(nullptr), headKehadiran(nullptr) {}
	
    ~DataAnakOrangTua() {
        while (headNilai != nullptr) {
            NilaiNode* temp = headNilai;
            headNilai = headNilai->next;
            delete temp;
        }
        while (headKehadiran != nullptr) {
            KehadiranNode* temp = headKehadiran;
            headKehadiran = headKehadiran->next;
            delete temp;
        }
    }
	
    void setNis(const string &nis) { nisAnak = nis; }
    string getNis() const { return nisAnak; }
	
    void setNilai(int mapelIdx, double nilai) {
        NilaiNode* newNode = new NilaiNode(mapelIdx, nilai);
        newNode->next = headNilai;
        headNilai = newNode;
    }
	
    double getNilai(int mapelIdx) const {
        NilaiNode* current = headNilai;
        while (current != nullptr) {
            if (current->mapelIdx == mapelIdx) {
                return current->nilai;
            }
            current = current->next;
        }
        return -1;
    }
	
    void setKehadiran(int hariIdx, int status) {
        KehadiranNode* newNode = new KehadiranNode(hariIdx, status);
        newNode->next = headKehadiran;
        headKehadiran = newNode;
    }
	
    int totalKehadiran() const {
        int total = 0;
        KehadiranNode* current = headKehadiran;
        while (current != nullptr) {
            if (current->status == 1) total++;
            current = current->next;
        }
        return total;
    }
	
    void tampilNilai() const {
        if (headNilai == nullptr) {
            cout << "Belum ada data nilai.";
            cout << endl;
            return;
        }
        NilaiNode* current = headNilai;
        while (current != nullptr) {
            cout << "Mapel Index: " << current->mapelIdx
				<< " => Nilai: " << fixed << setprecision(2) << current->nilai;
				cout << endl;
            current = current->next;
        }
    }
};

struct TugasNode {
    string nama;
    string mapel;
    string tanggalKumpul;
    TugasNode* next;
    TugasNode(const string &n, const string &m, const string &t) : nama(n), mapel(m), tanggalKumpul(t), next(nullptr) {}
};

class ManajemenTugas {
private:
    TugasNode* head;
public:
    ManajemenTugas() : head(nullptr) {}
    ~ManajemenTugas() {
        while (head != nullptr) {
            TugasNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void tambahTugas(const string &nama, const string &mapel, const string &tanggal) {
        TugasNode* newNode = new TugasNode(nama, mapel, tanggal);
        newNode->next = head;
        head = newNode;
    }
    void lihatTugas() const {
        if (head == nullptr) {
            cout << "Tidak ada tugas saat ini.";
            cout << endl;
            return;
        }
        int nomor = 1;
        TugasNode* current = head;
        cout << "\n=== DAFTAR TUGAS ANAK ===\n";
        while (current != nullptr) {
            cout << nomor << ". [" << current->mapel << "] " << current->nama
				<< " (Kumpul: " << current->tanggalKumpul << ")";
				cout << endl;
            current = current->next;
            nomor++;
        }
    }
	
	// FITUR TAMBAHAN: Cari Tugas (Pencarian Linear pada Linked List)
	void cariTugas(const string& keyword) const {
		if (head == nullptr) {
			cout << "Tidak ada tugas untuk dicari.\n";
			return;
		}
		TugasNode* current = head;
		bool found = false;
		cout << "\n=== HASIL PENCARIAN TUGAS (Keyword: " << keyword << ") ===\n";
		int nomor = 1;
		while (current != nullptr) {
			// Menggunakan find dari <string> untuk mencari keyword di nama atau mapel
			if (current->nama.find(keyword) != string::npos || current->mapel.find(keyword) != string::npos) {
				cout << nomor << ". [" << current->mapel << "] " << current->nama
					<< " (Kumpul: " << current->tanggalKumpul << ")\n";
				found = true;
				nomor++;
			}
			current = current->next;
		}
		if (!found) {
			cout << "Tidak ada tugas yang cocok dengan keyword '" << keyword << "'.\n";
		}
	}
};

struct TagihanNode {
    string idTagihan;
    string deskripsi;
    double jumlah;
    string tanggal;
    string status; // "Belum Bayar" atau "Sudah Bayar"
    TagihanNode(const string &id, const string &d, double j, const string &t, const string &s)
        : idTagihan(id), deskripsi(d), jumlah(j), tanggal(t), status(s), next(nullptr) {}
    TagihanNode* next;
};

class AntrianPembayaran {
private:
    TagihanNode* head;
public:
    AntrianPembayaran() : head(nullptr) {}
    ~AntrianPembayaran() {
        while (head != nullptr) {
            TagihanNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void tambahTagihan(const string &id, const string &deskripsi, double jumlah, const string &tanggal) {
        TagihanNode* newNode = new TagihanNode(id, deskripsi, jumlah, tanggal, "Belum Bayar");
        newNode->next = head;
        head = newNode;
    }
    void lihatTagihan() const {
        if (head == nullptr) {
            cout << "Tidak ada tagihan.";
            cout << endl;
            return;
        }
        TagihanNode* current = head;
        cout << "\n=== DAFTAR TAGIHAN & RIWAYAT PEMBAYARAN ===\n";
        int nomor = 1;
        while (current != nullptr) {
            cout << nomor << ". [" << current->status << "] " << current->deskripsi
				<< " - Rp " << fixed << setprecision(0) << current->jumlah
				<< " (" << current->tanggal << ")";
            cout << endl;
            current = current->next;
            nomor++;
        }
    }
    bool bayarTagihan(const string &idTagihan) {
        TagihanNode* current = head;
        while (current != nullptr) {
            if (current->idTagihan == idTagihan) {
                current->status = "Sudah Bayar";
                cout << "Pembayaran berhasil dicatat.";
                cout << endl;
                return true;
            }
            current = current->next;
        }
        cout << "Tagihan tidak ditemukan.";
        cout << endl;
        return false;
    }
    double hitungTotalTagihan() const {
        double total = 0;
        TagihanNode* current = head;
        while (current != nullptr) {
            if (current->status == "Belum Bayar") {
                total += current->jumlah;
            }
            current = current->next;
        }
        return total;
    }
};

struct PesanNode {
    string pengirim;
    string pesan;
    string tanggal;
    PesanNode(const string &p, const string &msg, const string &tgl)
        : pengirim(p), pesan(msg), tanggal(tgl), next(nullptr) {}
    PesanNode* next;
};

class StackPesan {
private:
    PesanNode* head;
public:
    StackPesan() : head(nullptr) {}
    ~StackPesan() {
        while (head != nullptr) {
            PesanNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void kirimPesan(const string &pengirim, const string &pesan, const string &tanggal) {
        PesanNode* newNode = new PesanNode(pengirim, pesan, tanggal);
        newNode->next = head;
        head = newNode;
    }
    void lihatPesanTerakhir() const {
        if (head == nullptr) {
            cout << "Belum ada percakapan.\n";
            return;
        }
        cout << "\n=== PERCAKAPAN DENGAN GURU/WALI KELAS ===\n";
        cout << "Pesan Terakhir:";
        cout << endl;
        cout << "Dari: " << head->pengirim;
        cout << endl;
        cout << "Pesan: " << head->pesan;
        cout << endl;
        cout << "Tanggal: " << head->tanggal;
        cout << endl;
    }
    void lihatRiwayatPesan() const {
        if (head == nullptr) {
            cout << "Belum ada percakapan.";
            cout << endl;
            return;
        }
        cout << "\n=== RIWAYAT CHAT (Terbaru ke Terlama) ===\n";
        PesanNode* current = head;
        int nomor = 1;
        while (current != nullptr) {
            cout << nomor << ". [" << current->tanggal << "] " << current->pengirim
				<< ": " << current->pesan;
            cout << endl;
            current = current->next;
            nomor++;
        }
    }
};

struct NotifikasiNode {
    string judul;
    string deskripsi;
    string tanggal;
    NotifikasiNode(const string &j, const string &d, const string &t)
        : judul(j), deskripsi(d), tanggal(t), next(nullptr) {}
    NotifikasiNode* next;
};

class QueueNotifikasi {
private:
    NotifikasiNode* head;
public:
    QueueNotifikasi() : head(nullptr) {}
    ~QueueNotifikasi() {
        while (head != nullptr) {
            NotifikasiNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void tambahNotifikasi(const string &judul, const string &deskripsi, const string &tanggal) {
        NotifikasiNode* newNode = new NotifikasiNode(judul, deskripsi, tanggal);
        newNode->next = head;
        head = newNode;
    }
    void lihatNotifikasi() const {
        if (head == nullptr) {
            cout << "Tidak ada notifikasi.";
            cout << endl;
            return;
        }
        cout << "\n=== NOTIFIKASI KEGIATAN SEKOLAH ===\n";
        NotifikasiNode* current = head;
        int nomor = 1;
        while (current != nullptr) {
            cout << nomor << ". [" << current->tanggal << "] " << current->judul;
            cout << endl;
            cout << "    " << current->deskripsi;
            cout << endl;
            current = current->next;
            nomor++;
        }
    }
    void lihatNotifikasiTerbaru() const {
        if (head == nullptr) {
            cout << "Tidak ada notifikasi.";
            cout << endl;
            return;
        }
        cout << "\n=== NOTIFIKASI TERBARU ===\n";
        cout << "Judul: " << head->judul << "\n";
        cout << "Deskripsi: " << head->deskripsi << "\n";
        cout << "Tanggal: " << head->tanggal << "\n";
    }
};

// ================== KELAS MODUL 6: ANTRIAN DOKUMEN (QUEUE CIRCULAR ARRAY) ==================

struct DokumenPermintaan {
private:
    string nis;
    string jenisDokumen;
    string tanggalMinta;
    string status;      // Menunggu / Diproses / Selesai
    string lokasiSimpan;
    int prioritas;      // 1-3 (Tinggi-Rendah)
public:
    // Konstruktor default
    DokumenPermintaan() : nis(""), jenisDokumen(""), tanggalMinta(""), status("Kosong"), lokasiSimpan(""), prioritas(0) {}

    // Setter
    void setData(const string &n, const string &jd, const string &tgl, const string &lok, int prio) {
        nis = n;	
		jenisDokumen = jd;	
		tanggalMinta = tgl;	
		status = "Menunggu";	
		lokasiSimpan = lok;	
		prioritas = prio;
    }
    void setStatus(const string &s) { status = s; }

    // Getter
    string getNis() const {	
	    return nis;	
	}
    string getJenisDokumen() const {	
	    return jenisDokumen;	
	}
    string getTanggalMinta() const {	
		return tanggalMinta;	
	}
    string getStatus() const {	
		return status;	
	}
    string getLokasiSimpan() const {	
		return lokasiSimpan;	
	}
    int getPrioritas() const {	
		return prioritas;	
	}
};

class AntrianDokumen {
private:
    DokumenPermintaan antrian[MAX_ANTRIAN_DOKUMEN];
    int front; // Indeks depan
    int rear;	// Indeks belakang
    int count; // Jumlah elemen saat ini
public:
    AntrianDokumen() : front(0), rear(-1), count(0) {}
	
    int getCount() const {	
	return count;	
	}	
	
    // ENQUEUE (Menambah Permintaan)
    void enqueue(const string &n, const string &jd, const string &tgl, const string &lok, int prio) {
        if (count >= MAX_ANTRIAN_DOKUMEN) {
            cout << "Antrian dokumen penuh, harap tunggu atau hubungi admin.";
            cout << endl;
            return;
        }
        rear = (rear + 1) % MAX_ANTRIAN_DOKUMEN;
		
        // Menggunakan method setter untuk inisialisasi
        antrian[rear].setData(n, jd, tgl, lok, prio);

        count++;
        cout << "Permintaan dokumen (NIS: " << n << ") berhasil ditambahkan ke antrian. Prioritas: " << prio;
        cout << endl;
    }
    
    // Deklarasi Dequeue function (diimplementasikan di bawah karena perlu akses ke arsipDokumenSelesai)
    DokumenPermintaan dequeue_impl();	
    
    // DEQUEUE (Melayani Permintaan)
    DokumenPermintaan dequeue() {
        return dequeue_impl();
    }

    // PEEK (Melihat Permintaan Terdepan)
    void peek() const {
        if (count == 0) {
            cout << "Antrian dokumen kosong.";
            cout << endl;
            return;
        }
        cout << "\n=== PERMINTAAN TERDEPAN (PEEK) ===\n";
        cout << "	NIS: " << antrian[front].getNis()	
				<< ", Dokumen: " << antrian[front].getJenisDokumen()	
				<< " | Status: " << antrian[front].getStatus()
				<< " | Prioritas: " << antrian[front].getPrioritas()
				<< " | Lokasi: " << antrian[front].getLokasiSimpan();
        cout << endl;
    }

    void tampil() const {
        if (count == 0) {
            cout << "Antrian dokumen kosong.";
            cout << endl;
            return;
        }
        cout << "\n--- Daftar Antrian Dokumen (Urutan Pelayanan) ---\n";
        cout << string(90, '=');
        cout << endl;
        cout << left << setw(5) << "No." << setw(10) << "NIS" << setw(25) << "Jenis Dokumen"	
				<< setw(12) << "Tgl Minta" << setw(12) << "Prioritas" << setw(12) << "Status" << "Lokasi\n";
        cout << string(90, '-');
        cout << endl;
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_ANTRIAN_DOKUMEN;
            cout << left << setw(5) << (i + 1)
				<< setw(10) << antrian[idx].getNis()
				<< setw(25) << antrian[idx].getJenisDokumen()
				<< setw(12) << antrian[idx].getTanggalMinta()
				<< setw(12) << antrian[idx].getPrioritas()
				<< setw(12) << antrian[idx].getStatus()
				<< antrian[idx].getLokasiSimpan();
            cout << endl;
        }
        cout << string(90, '=');
        cout << endl;
    }
	
    // FITUR BARU: Pencarian Dokumen (Linear Search)
    void cariDokumen(const string& nisTarget) const {
        bool found = false;
        cout << "\n=== HASIL PENCARIAN DOKUMEN (NIS: " << nisTarget << ") ===\n";
        cout << string(60, '=');
        cout << endl;
        cout << left << setw(25) << "Jenis Dokumen" << setw(15) << "Tgl Minta" << setw(10) << "Prioritas" << "Status\n";
        cout << string(60, '-');
        cout << endl;
		
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_ANTRIAN_DOKUMEN;
            if (antrian[idx].getNis() == nisTarget) {
                cout << left << setw(25) << antrian[idx].getJenisDokumen()
					<< setw(15) << antrian[idx].getTanggalMinta()
					<< setw(10) << antrian[idx].getPrioritas()
					<< antrian[idx].getStatus();
                cout << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Dokumen untuk NIS " << nisTarget << " tidak ditemukan dalam antrian aktif.";
            cout << endl;
        }
        cout << string(60, '=');
        cout << endl;
    }
	
    // FITUR BARU: Update Status Dokumen
    void updateStatusDokumen(const string& nisTarget, const string& jenisTarget, const string& newStatus) {
        bool updated = false;
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_ANTRIAN_DOKUMEN;
            if (antrian[idx].getNis() == nisTarget && antrian[idx].getJenisDokumen() == jenisTarget) {
                antrian[idx].setStatus(newStatus);
                cout << "Status dokumen NIS " << nisTarget << " (" << jenisTarget << ") berhasil diubah menjadi: " << newStatus << '\n';
                updated = true;
                break;	
            }
        }
        if (!updated) {
            cout << "Dokumen dengan NIS " << nisTarget << " dan jenis " << jenisTarget << " tidak ditemukan dalam antrian aktif.";
            cout << endl;
        }
    }

    // FITUR BARU: Simulasi Prioritas (Melihat siapa yang harusnya dilayani duluan)
    void simulasiPrioritas() const {
        if (count == 0) {
            cout << "Antrian kosong.";
            cout << endl;
            return;
        }
		
        int bestIdx = -1;
        int lowestPrio = 4; // Lebih tinggi dari max prioritas (3)
		
        // Cari prioritas terendah (angka 1 adalah prioritas tertinggi)
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_ANTRIAN_DOKUMEN;
            if (antrian[idx].getPrioritas() < lowestPrio) {
                lowestPrio = antrian[idx].getPrioritas();
                bestIdx = idx;
            }
        }
		
        cout << "\n=== HASIL SIMULASI PRIORITAS (Prioritas Terendah = Paling Penting) ===\n";
        cout << string(70, '=') << '\n';
        if (bestIdx != -1) {
            cout << "Permintaan paling penting (Prioritas " << lowestPrio << ") adalah:\n";
            cout << "	NIS: " << antrian[bestIdx].getNis()	
					<< ", Dokumen: " << antrian[bestIdx].getJenisDokumen()	
					<< ", Status: " << antrian[bestIdx].getStatus() << "\n";
			
        }
        cout << string(70, '-');
        cout << endl;
        cout << "CATATAN: Antrian ini masih mengikuti FIFO, Prioritas hanya untuk informasi.\n";
        cout << string(70, '=');
        cout << endl;
    }

    // FITUR BARU: Statistik (Untuk Laporan)
    void laporanStatistik() const {
        if (count == 0) {
            cout << "Antrian kosong. Tidak ada data statistik.";
            cout << endl;
            return;
        }
		
        // Simpan hitungan jenis dokumen (simulasi Map/Hash menggunakan array)
        string jenisDoc[MAX_ANTRIAN_DOKUMEN];
        int hitungan[MAX_ANTRIAN_DOKUMEN] = {0};
        int jenisUnik = 0;

        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_ANTRIAN_DOKUMEN;
            string currentJenis = antrian[idx].getJenisDokumen();
            bool isNew = true;
			
            for (int j = 0; j < jenisUnik; ++j) {
                if (jenisDoc[j] == currentJenis) {
                    hitungan[j]++;
                    isNew = false;
                    break;
                }
            }
			
            if (isNew && jenisUnik < MAX_ANTRIAN_DOKUMEN) {
                jenisDoc[jenisUnik] = currentJenis;
                hitungan[jenisUnik] = 1;
                jenisUnik++;
            }
        }

        cout << "\n--- STATISTIK JENIS DOKUMEN DALAM ANTRIAN ---\n";
        cout << string(50, '=');
        cout << endl;
        for (int i = 0; i < jenisUnik; ++i) {
            cout << left << setw(30) << jenisDoc[i] << ": " << hitungan[i] << " permintaan\n";
        }
        cout << string(50, '=');
        cout << endl;
    }
    
    // FITUR BARU: Filter Antrian Berdasarkan Status
    void filterStatus(const string& statusTarget) const {
        if (count == 0) {
            cout << "Antrian dokumen kosong.\n";
            return;
        }
        cout << "\n--- Filter Antrian (Status: " << statusTarget << ") ---\n";
        cout << string(90, '=') << endl;
        cout << left << setw(5) << "No." << setw(10) << "NIS" << setw(25) << "Jenis Dokumen"  
              << setw(12) << "Tgl Minta" << setw(12) << "Prioritas" << setw(12) << "Status" << "Lokasi\n";
        cout << string(90, '-') << endl;

        int nomor = 1;
        bool found = false;
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_ANTRIAN_DOKUMEN;
            if (antrian[idx].getStatus() == statusTarget) {
                cout << left << setw(5) << nomor
                     << setw(10) << antrian[idx].getNis()
                     << setw(25) << antrian[idx].getJenisDokumen()
                     << setw(12) << antrian[idx].getTanggalMinta()
                     << setw(12) << antrian[idx].getPrioritas()
                     << setw(12) << antrian[idx].getStatus()
                     << antrian[idx].getLokasiSimpan() << endl;
                nomor++;
                found = true;
            }
        }
        if (!found) {
            cout << "Tidak ada dokumen dengan status '" << statusTarget << "' dalam antrian aktif.\n";
        }
        cout << string(90, '=') << endl;
    }
    
    // FITUR BARU: Hapus Dokumen Berdasarkan NIS dan Jenis
    void hapusDokumen(const string& nisTarget, const string& jenisTarget) {
        if (count == 0) {
            cout << "Antrian dokumen kosong.\n";
            return;
        }
        
        int deleteIdx = -1;
        int deletePos = -1;

        // Temukan indeks (circular array) dan posisi (urutan antrian) dari dokumen yang akan dihapus
        for (int i = 0; i < count; ++i) {
            int idx = (front + i) % MAX_ANTRIAN_DOKUMEN;
            if (antrian[idx].getNis() == nisTarget && antrian[idx].getJenisDokumen() == jenisTarget) {
                deleteIdx = idx;
                deletePos = i;
                break;
            }
        }
        
        if (deleteIdx != -1) {
            // Jika yang dihapus adalah elemen terdepan, gunakan dequeue_impl (untuk arsip otomatis)
            if (deleteIdx == front) {
                dequeue_impl(); 
                cout << "Dokumen terdepan berhasil dihapus/dilayani (menggunakan dequeue).\n";
                return;
            }
            
            // Jika bukan elemen terdepan, geser elemen setelahnya
            for (int i = deletePos; i < count - 1; ++i) {
                int currentIdx = (front + i) % MAX_ANTRIAN_DOKUMEN;
                int nextIdx = (front + i + 1) % MAX_ANTRIAN_DOKUMEN;
                antrian[currentIdx] = antrian[nextIdx];
            }
            
            // Atur ulang rear dan count
            rear = (rear - 1 + MAX_ANTRIAN_DOKUMEN) % MAX_ANTRIAN_DOKUMEN;
            count--;
            
            // Optional: Bersihkan slot terakhir
            antrian[(rear + 1) % MAX_ANTRIAN_DOKUMEN] = DokumenPermintaan();
            
            cout << "Dokumen NIS " << nisTarget << " (" << jenisTarget << ") berhasil dihapus dari antrian.\n";
        } else {
            cout << "Dokumen tidak ditemukan dalam antrian aktif.\n";
        }
    }
};


// ================== KELAS MODUL 7: DOUBLE LINKED LIST (DLL) BARU ==================

// --- FITUR 1: Arsip Dokumen Selesai (DLL) ---

struct ArsipDokumenNode {
    DokumenPermintaan data; // Re-use struct DokumenPermintaan
    ArsipDokumenNode* prev;
    ArsipDokumenNode* next;

    ArsipDokumenNode(const DokumenPermintaan& d) : data(d), prev(nullptr), next(nullptr) {}
};

class ArsipDokumenSelesai {
private:
    ArsipDokumenNode* head;
    ArsipDokumenNode* tail;
public:
    ArsipDokumenSelesai() : head(nullptr), tail(nullptr) {}
    ~ArsipDokumenSelesai() {
        ArsipDokumenNode* current = head;
        while (current != nullptr) {
            ArsipDokumenNode* next = current->next;
            delete current;
            current = next;
        }
    }

    // 1. TAMBAH (Selalu di akhir/tail untuk urutan waktu)
    void tambahArsip(const DokumenPermintaan& d) {
        ArsipDokumenNode* newNode = new ArsipDokumenNode(d);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Dokumen selesai diarsip (DLL).";
        cout << endl;
    }

    // 2. TAMPIL MAJU (Urutan Kronologis - Terlama ke Terbaru)
    void tampilMaju() const {
        if (head == nullptr) {
            cout << "Arsip dokumen selesai kosong.\n";
            return;
        }
        cout << "\n--- ARSIP DOKUMEN (Terlama ke Terbaru) ---\n";
        cout << string(70, '=') << '\n';
        ArsipDokumenNode* current = head;
        int nomor = 1;
        while (current != nullptr) {
            cout << left << setw(4) << nomor << ". NIS: " << current->data.getNis()
                << ", Jenis: " << current->data.getJenisDokumen()
                << ", Tgl: " << current->data.getTanggalMinta() << "\n";
            current = current->next;
            nomor++;
        }
        cout << string(70, '=') << '\n';
    }

    // 3. TAMPIL MUNDUR (Urutan Kronologis - Terbaru ke Terlama)
    void tampilMundur() const {
        if (tail == nullptr) {
            cout << "Arsip dokumen selesai kosong.\n";
            return;
        }
        cout << "\n--- ARSIP DOKUMEN (Terbaru ke Terlama) ---\n";
        cout << string(70, '=') << '\n';
        ArsipDokumenNode* current = tail;
        int nomor = 1;
        while (current != nullptr) {
            cout << left << setw(4) << nomor << ". NIS: " << current->data.getNis()
                << ", Jenis: " << current->data.getJenisDokumen()
                << ", Tgl: " << current->data.getTanggalMinta() << "\n";
            current = current->prev;
            nomor++;
        }
        cout << string(70, '=') << '\n';
    }
};

// --- FITUR 2: Riwayat Penilaian Tugas/Ujian (DLL) ---

struct PenilaianTugasNode {
    string idTugas;
    string mapel;
    string deskripsi;
    double nilaiRata;
    PenilaianTugasNode* prev;
    PenilaianTugasNode* next;

    PenilaianTugasNode(const string& id, const string& m, const string& d, double n) 
        : idTugas(id), mapel(m), deskripsi(d), nilaiRata(n), prev(nullptr), next(nullptr) {}
};

class RiwayatPenilaianTugas {
private:
    PenilaianTugasNode* head;
    PenilaianTugasNode* tail;
public:
    RiwayatPenilaianTugas() : head(nullptr), tail(nullptr) {}
    ~RiwayatPenilaianTugas() {
        PenilaianTugasNode* current = head;
        while (current != nullptr) {
            PenilaianTugasNode* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // Tambah (Selalu di Head/Depan, Terbaru)
    void tambahPenilaian(const string& id, const string& mapel, const string& desk, double nilai) {
        PenilaianTugasNode* newNode = new PenilaianTugasNode(id, mapel, desk, nilai);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        cout << "Penilaian Tugas berhasil diarsip (DLL, Terbaru).\n";
    }

    // Tampil Terbaru ke Terlama
    void tampilRiwayat() const {
        if (head == nullptr) {
            cout << "Tidak ada riwayat penilaian tugas.\n";
            return;
        }
        cout << "\n--- RIWAYAT PENILAIAN TUGAS (Terbaru ke Terlama) ---\n";
        cout << string(70, '=') << '\n';
        PenilaianTugasNode* current = head;
        int nomor = 1;
        while (current != nullptr) {
            cout << left << setw(4) << nomor << ". [" << current->mapel << "] "	
                << current->deskripsi << " (ID: " << current->idTugas << ")"
                << " - Nilai: " << fixed << setprecision(2) << current->nilaiRata << "\n";
            current = current->next;
            nomor++;
        }
        cout << string(70, '=') << '\n';
    }

    // Navigasi Mundur (Terlama ke Terbaru)
    void tampilReverse() const {
        if (tail == nullptr) {
            cout << "Tidak ada riwayat penilaian tugas.\n";
            return;
        }
        cout << "\n--- RIWAYAT PENILAIAN TUGAS (Terlama ke Terbaru) ---\n";
        cout << string(70, '=') << '\n';
        PenilaianTugasNode* current = tail;
        int nomor = 1;
        while (current != nullptr) {
            cout << left << setw(4) << nomor << ". [" << current->mapel << "] "	
                << current->deskripsi << " (ID: " << current->idTugas << ")"
                << " - Nilai: " << fixed << setprecision(2) << current->nilaiRata << "\n";
            current = current->prev;
            nomor++;
        }
        cout << string(70, '=') << '\n';
    }
};

// --- FITUR 3: Hierarki Senioritas Guru (DLL) ---

struct StaffNode {
    Guru data; // Re-use class Guru
    StaffNode* prev;
    StaffNode* next;

    StaffNode(const Guru& g) : data(g), prev(nullptr), next(nullptr) {}
};

class SenioritasGuru {
private:
    StaffNode* head;
    StaffNode* tail;
public:
    SenioritasGuru() : head(nullptr), tail(nullptr) {}
    ~SenioritasGuru() {
        StaffNode* current = head;
        while (current != nullptr) {
            StaffNode* next = current->next;
            delete current;
            current = next;
        }
    }

    // Tambah (di akhir list, diasumsikan yang ditambahkan adalah yang paling junior)
    void tambahGuru(const Guru& g) {
        StaffNode* newNode = new StaffNode(g);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    // Hapus Guru berdasarkan NIP (Cek di semua node DLL)
    void hapusGuru(const string& nip) {
        StaffNode* current = head;
        while (current != nullptr) {
            if (current->data.getNip() == nip) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next; // Menghapus Head
                }

                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev; // Menghapus Tail
                }
                delete current;
                cout << "Guru dengan NIP " << nip << " berhasil dihapus dari daftar senioritas.\n";
                return;
            }
            current = current->next;
        }
        cout << "Guru dengan NIP " << nip << " tidak ditemukan.\n";
    }

    // Tampil Maju (Head ke Tail = Paling Senior ke Paling Junior)
    void tampilSenioritasMaju() const {
        if (head == nullptr) {
            cout << "Daftar guru senioritas kosong.\n";
            return;
        }
        cout << "\n--- URUTAN SENIORITAS (Senior ke Junior) ---\n";
        cout << left << setw(15) << "NIP" << setw(25) << "Nama" << "Senioritas\n";
        cout << string(70, '=') << '\n';
        StaffNode* current = head;
        while (current != nullptr) {
            cout << left << setw(15) << current->data.getNip() 
                << setw(25) << current->data.getNama() 
                << current->data.getSenioritas() << "\n";
            current = current->next;
        }
        cout << string(70, '=') << '\n';
    }

    // Tampil Mundur (Tail ke Head = Paling Junior ke Paling Senior)
    void tampilSenioritasMundur() const {
        if (tail == nullptr) {
            cout << "Daftar guru senioritas kosong.\n";
            return;
        }
        cout << "\n--- URUTAN JUNIORITAS (Junior ke Senior) ---\n";
        cout << left << setw(15) << "NIP" << setw(25) << "Nama" << "Senioritas\n";
        cout << string(70, '=') << '\n';
        StaffNode* current = tail;
        while (current != nullptr) {
            cout << left << setw(15) << current->data.getNip() 
                << setw(25) << current->data.getNama() 
                << current->data.getSenioritas() << "\n";
            current = current->prev;
        }
        cout << string(70, '=') << '\n';
    }
    
    // Fungsi untuk menyisipkan guru baru berdasarkan urutan senioritas (Simulasi)
    void sisipGuru(const Guru& newGuru, const string& nipBefore) {
        StaffNode* newNode = new StaffNode(newGuru);
        if (head == nullptr) {
            head = tail = newNode;
            cout << "Guru pertama berhasil ditambahkan.\n";
            return;
        }
        
        StaffNode* current = head;
        while (current != nullptr) {
            if (current->data.getNip() == nipBefore) {
                // Sisipkan newNode sebelum current
                newNode->next = current;
                newNode->prev = current->prev;
                if (current->prev) {
                    current->prev->next = newNode;
                } else {
                    head = newNode; // Jadi Head baru
                }
                current->prev = newNode;
                cout << "Guru " << newGuru.getNama() << " berhasil disisipkan sebelum NIP " << nipBefore << ".\n";
                return;
            }
            current = current->next;
        }
        
        // Jika nipBefore tidak ditemukan, tambahkan di akhir (paling junior)
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        cout << "NIP referensi tidak ditemukan, Guru " << newGuru.getNama() << " ditambahkan di akhir (paling junior).\n";
    }
};

// ================== KELAS MODUL 8: POHON KELUARGA SISWA (BST) - FITUR BARU 1 ==================

// Struktur Node BST
struct SiswaKeluargaNode {
    string nis;
    string namaWali;
    string kontakDarurat;
    SiswaKeluargaNode* left;
    SiswaKeluargaNode* right;

    SiswaKeluargaNode(const string& n, const string& nw, const string& k) 
        : nis(n), namaWali(nw), kontakDarurat(k), left(nullptr), right(nullptr) {}
};

class PohonKeluarga {
private:
    SiswaKeluargaNode* root;

    // Fungsi bantu rekursif untuk penambahan (berdasarkan NIS)
    SiswaKeluargaNode* insertRecursive(SiswaKeluargaNode* node, const string& nis, const string& namaWali, const string& kontak) {
        if (node == nullptr) {
            return new SiswaKeluargaNode(nis, namaWali, kontak);
        }

        // Perbandingan string NIS untuk menentukan arah (diasumsikan NIS adalah string unik)
        if (nis < node->nis) {
            node->left = insertRecursive(node->left, nis, namaWali, kontak);
        } else if (nis > node->nis) {
            node->right = insertRecursive(node->right, nis, namaWali, kontak);
        } else {
            // Jika NIS sudah ada, update data wali
            cout << "NIS " << nis << " sudah ada, data wali di-update.\n";
            node->namaWali = namaWali;
            node->kontakDarurat = kontak;
        }

        return node;
    }

    // Fungsi bantu rekursif untuk pencarian (In-Order Traversal)
    void inOrderTraversal(SiswaKeluargaNode* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << left << setw(10) << node->nis << " | Wali: " << setw(20) << node->namaWali << " | Kontak: " << node->kontakDarurat << '\n';
            inOrderTraversal(node->right);
        }
    }

    // Fungsi bantu rekursif untuk pencarian (berdasarkan NIS)
    SiswaKeluargaNode* searchRecursive(SiswaKeluargaNode* node, const string& nis) const {
        if (node == nullptr || node->nis == nis) {
            return node;
        }

        if (nis < node->nis) {
            return searchRecursive(node->left, nis);
        } else {
            return searchRecursive(node->right, nis);
        }
    }

    // Fungsi bantu untuk cleanup memori
    void destroyRecursive(SiswaKeluargaNode* node) {
        if (node != nullptr) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    PohonKeluarga() : root(nullptr) {}
    ~PohonKeluarga() {
        destroyRecursive(root);
    }

    // Method publik untuk penambahan
    void tambahDataKeluarga(const string& nis, const string& namaWali, const string& kontak) {
        root = insertRecursive(root, nis, namaWali, kontak);
    }

    // Method publik untuk menampilkan (Terurut berdasarkan NIS)
    void tampilkanDataTerurut() const {
        if (root == nullptr) {
            cout << "Pohon keluarga kosong.\n";
            return;
        }
        cout << "\n--- DATA KELUARGA SISWA (BST - Terurut Berdasarkan NIS) ---\n";
        cout << string(60, '-') << '\n';
        inOrderTraversal(root);
        cout << string(60, '-') << '\n';
    }

    // Method publik untuk mencari
    void cariDataKeluarga(const string& nis) const {
        SiswaKeluargaNode* result = searchRecursive(root, nis);
        if (result != nullptr) {
            cout << "\n--- HASIL PENCARIAN (NIS: " << nis << ") ---\n";
            cout << "NIS: " << result->nis << " | Wali: " << result->namaWali << " | Kontak: " << result->kontakDarurat << '\n';
        } else {
            cout << "Data keluarga untuk NIS " << nis << " tidak ditemukan.\n";
        }
    }
};
// ================== END KELAS MODUL 8 ==================


// ================== KELAS MODUL 9: INVENTARIS RUANGAN HIERARKIS (GENERAL TREE) - FITUR BARU 2 ==================

// Struktur Node General Tree (menggunakan first-child/next-sibling representation)
struct RuanganInventarisNode {
    string namaLokasi; // Contoh: "Sekolah", "Gedung A", "Ruang Lab Kimia"
    string detailAset; // Contoh: "Meja Guru (1)", "Komputer (15)"
    RuanganInventarisNode* firstChild;
    RuanganInventarisNode* nextSibling;

    RuanganInventarisNode(const string& n, const string& d = "Lokasi Tanpa Aset") 
        : namaLokasi(n), detailAset(d), firstChild(nullptr), nextSibling(nullptr) {}
};

class InventarisRuanganTree {
private:
    RuanganInventarisNode* root;

    // Fungsi bantu untuk menambahkan anak
    RuanganInventarisNode* tambahAnak(RuanganInventarisNode* parent, const string& namaLokasi, const string& detailAset) {
        RuanganInventarisNode* newNode = new RuanganInventarisNode(namaLokasi, detailAset);
        if (parent->firstChild == nullptr) {
            parent->firstChild = newNode;
        } else {
            // Tambahkan sebagai sibling terakhir dari firstChild
            RuanganInventarisNode* current = parent->firstChild;
            while (current->nextSibling != nullptr) {
                current = current->nextSibling;
            }
            current->nextSibling = newNode;
        }
        return newNode;
    }

    // Fungsi bantu untuk pencarian lokasi
    RuanganInventarisNode* findLocationRecursive(RuanganInventarisNode* current, const string& targetLocation) const {
        if (current == nullptr) return nullptr;
        if (current->namaLokasi == targetLocation) return current;

        // Cari di anak
        RuanganInventarisNode* result = findLocationRecursive(current->firstChild, targetLocation);
        if (result != nullptr) return result;

        // Cari di sibling
        return findLocationRecursive(current->nextSibling, targetLocation);
    }

    // Fungsi bantu untuk tampilan (Pre-Order Traversal)
    void displayRecursive(RuanganInventarisNode* node, int depth) const {
        if (node == nullptr) return;

        cout << string(depth * 4, ' ');
        cout << "|-- " << node->namaLokasi;
        if (node->detailAset != "Lokasi Tanpa Aset") {
            cout << " [" << node->detailAset << "]";
        }
        cout << '\n';

        displayRecursive(node->firstChild, depth + 1);
        displayRecursive(node->nextSibling, depth);
    }
    
    // Fungsi bantu untuk cleanup memori
    void destroyRecursive(RuanganInventarisNode* node) {
        if (node != nullptr) {
            destroyRecursive(node->firstChild);
            destroyRecursive(node->nextSibling);
            delete node;
        }
    }


public:
    InventarisRuanganTree(const string& rootName = "SEKOLAH UTAMA") {
        root = new RuanganInventarisNode(rootName, "Lokasi Pusat");
    }
    ~InventarisRuanganTree() {
        destroyRecursive(root);
    }
    
    // Method publik untuk mendapatkan root
    RuanganInventarisNode* getRoot() const {
        return root;
    }

    // Method publik untuk tambah node (memerlukan lokasi parent)
    void tambahLokasi(const string& parentLocation, const string& newLocation, const string& asetDetail) {
        RuanganInventarisNode* parent = findLocationRecursive(root, parentLocation);
        if (parent != nullptr) {
            tambahAnak(parent, newLocation, asetDetail);
            cout << "Lokasi '" << newLocation << "' ditambahkan di bawah '" << parentLocation << "'.\n";
        } else {
            cout << "Lokasi parent '" << parentLocation << "' tidak ditemukan. Gagal menambahkan.\n";
        }
    }

    // Method publik untuk menampilkan hierarki
    void tampilkanHierarki() const {
        cout << "\n--- INVENTARIS RUANGAN HIERARKIS (GENERAL TREE) ---\n";
        cout << "Memodelkan aset berdasarkan lokasi hirarkis. \n";
        displayRecursive(root, 0);
        cout << "--------------------------------------------------\n";
    }

    // Method publik untuk melihat detail aset suatu lokasi
    void lihatDetailAset(const string& targetLocation) const {
        RuanganInventarisNode* location = findLocationRecursive(root, targetLocation);
        if (location != nullptr) {
            cout << "\n--- DETAIL ASET LOKASI: " << targetLocation << " ---\n";
            cout << "Detail Aset: " << location->detailAset << '\n';
        } else {
            cout << "Lokasi '" << targetLocation << "' tidak ditemukan.\n";
        }
    }
};

// ================== END KELAS MODUL 9 ==================


// ================== KELAS MODUL 10 BARU: POHON EVALUASI KEPUTUSAN (MAX HEAP) - FITUR BARU 3 ==================

struct EvaluasiNode {
    string idKeputusan;
    string program;
    int skorDampak; // 1 (Rendah) - 100 (Tinggi/Urgent)

    EvaluasiNode() : idKeputusan(""), program(""), skorDampak(0) {}
    EvaluasiNode(const string& id, const string& p, int s) : idKeputusan(id), program(p), skorDampak(s) {}
};

class PohonEvaluasiMaxHeap {
private:
    EvaluasiNode heapArray[MAX_LAPORAN]; // Menggunakan MAX_LAPORAN sebagai ukuran Max Heap
    int size;

    // Fungsi bantu untuk Max Heapify (memastikan properti Max Heap terpenuhi)
    void maxHeapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heapArray[left].skorDampak > heapArray[largest].skorDampak) {
            largest = left;
        }

        if (right < size && heapArray[right].skorDampak > heapArray[largest].skorDampak) {
            largest = right;
        }

        if (largest != i) {
            // Menggunakan std::swap dari <algorithm>
            swap(heapArray[i], heapArray[largest]); 
            maxHeapify(largest);
        }
    }

    // Fungsi untuk menaikkan nilai (saat insert)
    void increaseKey(int i) {
        int parent = (i - 1) / 2;
        // Perbaiki jika parent lebih kecil dari child
        while (i != 0 && heapArray[parent].skorDampak < heapArray[i].skorDampak) {
            // Menggunakan std::swap dari <algorithm>
            swap(heapArray[i], heapArray[parent]); 
            i = parent;
            parent = (i - 1) / 2;
        }
    }

public:
    PohonEvaluasiMaxHeap() : size(0) {}
    
    int getSize() const { return size; }

    // 1. Tambah Evaluasi (Insert)
    void insert(const string& id, const string& program, int skor) {
        if (size >= MAX_LAPORAN) {
            cout << "Heap evaluasi penuh.\n";
            return;
        }
        
        heapArray[size] = EvaluasiNode(id, program, skor);
        increaseKey(size); // Naikkan elemen baru ke posisi yang benar
        size++;
        cout << "Evaluasi Program '" << program << "' berhasil ditambahkan. Skor Dampak: " << skor << ".\n";
    }

    // 2. Lihat Keputusan Paling Utama (Extract Max / Peek)
    void peekMax() const {
        if (size == 0) {
            cout << "Tidak ada program evaluasi dalam antrian Max Heap.\n";
            return;
        }
        cout << "\n--- PROGRAM EVALUASI PALING UTAMA (Max Heap Root) ---\n";
        cout << "ID Keputusan : " << heapArray[0].idKeputusan << '\n';
        cout << "Program      : " << heapArray[0].program << '\n';
        cout << "Skor Dampak  : " << heapArray[0].skorDampak << " (Skor Tertinggi)\n";
        cout << "Catatan: Program ini memiliki skor dampak/urgensi paling tinggi.\n";
    }
    
    // 3. Proses Keputusan Utama (Extract Max)
    EvaluasiNode extractMax() {
        if (size <= 0) {
            cout << "Heap kosong, tidak ada keputusan untuk diproses.\n";
            return EvaluasiNode();
        }
        if (size == 1) {
            size--;
            EvaluasiNode extracted = heapArray[0];
            cout << "Keputusan Utama '" << extracted.program << "' diproses dan dikeluarkan.\n";
            return extracted;
        }

        EvaluasiNode rootNode = heapArray[0];
        heapArray[0] = heapArray[size - 1]; // Pindahkan elemen terakhir ke root
        size--;
        maxHeapify(0); // Perbaiki struktur Max Heap
        
        cout << "Keputusan Utama '" << rootNode.program << "' diproses dan dikeluarkan. Heap diperbaiki.\n";
        return rootNode;
    }

    // 4. Tampilkan Isi Heap (Visualisasi Struktural)
    void tampilkanStruktur() const {
        if (size == 0) {
            cout << "Heap kosong.\n";
            return;
        }
        cout << "\n--- STRUKTUR MAX HEAP (Berdasarkan Skor Dampak) ---\n";
        cout << "Urutan: Root (Tertinggi) | Level 1 | Level 2 | ... \n";
        for (int i = 0; i < size; ++i) {
            int level = 0;
            int temp = i + 1;
            while (temp > 1) {
                temp /= 2;
                level++;
            }
            cout << "Node " << i << " (Level " << level << "): [ID: " << heapArray[i].idKeputusan 
                 << ", Skor: " << heapArray[i].skorDampak << "] Program: " << heapArray[i].program << '\n';
        }
        cout << "----------------------------------------------------\n";
    }
};

// ================== END KELAS MODUL 10 BARU ==================

// ================== FITUR BARU: RIGHT-SKEWED TREE (RIWAYAT PELANGGARAN) ==================

struct PelanggaranNode {
    string nis;
    string jenisPelanggaran;
    string tanggal;
    int poinMinus;
    PelanggaranNode* right; // Hanya menggunakan pointer kanan (Skewed Right)

    PelanggaranNode(string n, string jp, string t, int p) 
        : nis(n), jenisPelanggaran(jp), tanggal(t), poinMinus(p), right(nullptr) {}
};

class RiwayatPelanggaranTree {
private:
    PelanggaranNode* root;

public:
    RiwayatPelanggaranTree() : root(nullptr) {}

    // Menambahkan pelanggaran (Selalu ke daun paling kanan)
    void tambahPelanggaran(string nis, string jenis, string tgl, int poin) {
        PelanggaranNode* newNode = new PelanggaranNode(nis, jenis, tgl, poin);
        if (root == nullptr) {
            root = newNode;
        } else {
            PelanggaranNode* current = root;
            while (current->right != nullptr) {
                current = current->right;
            }
            current->right = newNode;
        }
        cout << "Data pelanggaran berhasil dicatat di sistem (Right-Skewed Tree).\n";
    }

    // Menampilkan semua riwayat untuk NIS tertentu (Linear Traversal pada Skewed Tree)
    void tampilkanRiwayatSiswa(string targetNis) {
        if (root == nullptr) {
            cout << "Belum ada riwayat pelanggaran di sistem.\n";
            return;
        }

        cout << "\n--- RIWAYAT PELANGGARAN SISWA (NIS: " << targetNis << ") ---\n";
        cout << left << setw(15) << "Tanggal" << setw(30) << "Jenis Pelanggaran" << "Poin\n";
        cout << string(55, '-') << endl;

        PelanggaranNode* current = root;
        bool found = false;
        int totalPoin = 0;

        while (current != nullptr) {
            if (current->nis == targetNis) {
                cout << left << setw(15) << current->tanggal 
                     << setw(30) << current->jenisPelanggaran 
                     << "-" << current->poinMinus << "\n";
                totalPoin += current->poinMinus;
                found = true;
            }
            current = current->right; // Melangkah ke kanan
        }

        if (!found) {
            cout << "Siswa ini tidak memiliki catatan pelanggaran (Bersih).\n";
        } else {
            cout << string(55, '-') << endl;
            cout << "Total Pengurangan Poin: " << totalPoin << " Poin.\n";
        }
    }
};


// ================== DATABASE GLOBAL ==================
extern MataPelajaran daftarMapel[MAX_MAPEL];
extern int jumlahMapel;
extern Jadwal jadwalPelajaran;
extern Event kalender[MAX_EVENT];
extern int jumlahEvent;
extern Siswa daftarSiswa[MAX_SISWA];
extern int jumlahSiswa;
extern Guru daftarGuru[MAX_GURU];
extern int jumlahGuru;
extern Penilaian matrixNilai[MAX_SISWA][MAX_MAPEL];
extern Transaksi daftarTransaksi[MAX_TRANSAKSI];
extern int jumlahTransaksi;
extern User daftarUser[MAX_USERS];
extern int jumlahUser;
extern Laporan daftarLaporan[MAX_LAPORAN];
extern int jumlahLaporan;
extern ProfilSekolah profilSekolah;
extern StrukturOrganisasi strukturOrg;
extern ManajemenSurat manSurat;
extern Arsip arsipDigital;
extern Inventaris inventarisSekolah;
extern JadwalKegiatan jadwalKegSekolah;
extern Kuis kuisAktif;

// Global variables for Modul 3, 4, 5 & 6
extern MateriStack manMateri;
extern ManajemenPersetujuan manPersetujuan;

extern DataAnakOrangTua dataAnak[MAX_SISWA];
extern ManajemenTugas daftarTugasAnak;
extern AntrianPembayaran antrianTagihan;
extern StackPesan chatAnak;
extern QueueNotifikasi notifikasiSekolah;
// MODUL 6
extern AntrianDokumen antrianDokumenSekolah;
// MODUL 7 - BARU DENGAN DLL
extern ArsipDokumenSelesai arsipDokumenSelesai; 
extern RiwayatPenilaianTugas riwayatPenilaianTugas; // DLL untuk riwayat penilaian
extern SenioritasGuru senioritasGuru; // DLL untuk senioritas guru

// MODUL 8, 9, 10 - BARU DENGAN TREE
extern PohonKeluarga pohonKeluargaSiswa; // BST (Modul 8)
extern InventarisRuanganTree inventarisTree; // General Tree (Modul 9)
extern PohonEvaluasiMaxHeap pohonEvaluasi; // Max Heap (Modul 10)

extern RiwayatPelanggaranTree pohonPelanggaran;


// ================== DEKLARASI FUNGSI ==================
void tampilMapel();
void tampilSiswa();
void tampilGuru();
double totalPemasukan();
void tampilEvent();
int cariIndexSiswa(const string &nis);
int cariIndexMapel(const string &kode);
bool cekUsernameExist(const string &username);
bool cekNisExist(const string &nis);
void prosesPendaftaranSiswa();
void lihatNilaiSiswa(int si);
void lihatAbsensiSiswa(int si);
void menuELearningSiswa(string nis);
void menuPohonKeluargaSiswa();
void menuInventarisRuanganTree();
void menuPohonEvaluasi();
void menuManajemenAkademik();
void menuManajemenDataSiswa();
void menuManajemenDataGuru();
void menuKeuangan();
void menuLayananDokumenAdmin();
void menuLayananDokumenSiswa(const string& nis);
void menuRiwayatPenilaianTugas();
void menuSenioritasGuru();
void menuArsipDokumenSelesai();
void menuELearningAdmin();
void menuKepegawaian();
void menuTataUsaha();
void menuLaporan();
void menuManajemenPersetujuan();
void menuDashboardKepalaSekolah();
void mainMenuAdmin();
void mainMenuSiswa(const string &nis);
void mainMenuKepalaSekolah();
void lihatNilaiKehadiranAnak(const string &nis);
void menuOrangTuaWali();

#endif // TUBASNABILA9FIX_H
