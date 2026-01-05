#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> // Untuk std::find_if, std::transform, std::swap

using namespace std;

// ================== STRUKTUR DATA KTP ==================
struct Date {
    int day;
    int month;
    int year;
};

struct Alamat {
    string jalan;
    string rt;
    string rw;
    string kelurahan;
    string kecamatan;
};

struct KTP {
    string nik;
    string nama;
    string tempat_lahir;
    Date tgl_lahir;
    int jenis_kelamin; // 1 = Laki-laki, 0 = Perempuan
    string gol_darah;
    Alamat alamat;
    int agama; // 1=Islam, 2=Kristen, 3=Katolik
    int status_perkawinan; // 1=Kawin, 0=Belum
    string pekerjaan;
    int kewarganegaraan; // 1=WNI, 0=WNA
    Date berlaku_hingga;
};

class ArrayKTP {
private:
    KTP data[100];
    int count;
public:
    ArrayKTP() : count(0) {}
    
    void insert(const KTP &ktp) {
        if (count < 100) {
            data[count++] = ktp;
        }
    }
    
    void display() const {
        if (count == 0) {
            cout << "Array KTP kosong.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << "\nKTP ke-" << (i+1) << ":\n";
            cout << "NIK: " << data[i].nik << "\n";
            cout << "Nama: " << data[i].nama << "\n";
            cout << "Tempat/Tgl Lahir: " << data[i].tempat_lahir << ", " 
                 << data[i].tgl_lahir.day << "/" << data[i].tgl_lahir.month << "/" << data[i].tgl_lahir.year << "\n";
            cout << "Jenis Kelamin: " << (data[i].jenis_kelamin ? "Laki-laki" : "Perempuan") << "\n";
            cout << "Alamat: " << data[i].alamat.jalan << ", RT " << data[i].alamat.rt 
                 << "/RW " << data[i].alamat.rw << ", " << data[i].alamat.kelurahan 
                 << ", " << data[i].alamat.kecamatan << "\n";
        }
    }
    
    KTP* findByNIK(const string &nik) {
        for (int i = 0; i < count; i++) {
            if (data[i].nik == nik) {
                return &data[i];
            }
        }
        return nullptr;
    }
    
    void removeByNIK(const string &nik) {
        for (int i = 0; i < count; i++) {
            if (data[i].nik == nik) {
                for (int j = i; j < count - 1; j++) {
                    data[j] = data[j + 1];
                }
                count--;
                cout << "Data KTP dengan NIK " << nik << " berhasil dihapus dari array.\n";
                return;
            }
        }
        cout << "Data KTP dengan NIK " << nik << " tidak ditemukan dalam array.\n";
    }
    
    int getCount() const { return count; }
};

struct NodeKTP {
    KTP data;
    NodeKTP* prev;
    NodeKTP* next;
    
    NodeKTP(const KTP &ktp) : data(ktp), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    NodeKTP* head;
    NodeKTP* tail;
    int count;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    ~DoublyLinkedList() {
        NodeKTP* current = head;
        while (current != nullptr) {
            NodeKTP* next = current->next;
            delete current;
            current = next;
        }
    }
    
    void insert(const KTP &ktp) {
        NodeKTP* newNode = new NodeKTP(ktp);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }
    
    void display() const {
        if (head == nullptr) {
            cout << "Doubly Linked List KTP kosong.\n";
            return;
        }
        
        NodeKTP* current = head;
        int i = 1;
        while (current != nullptr) {
            cout << "\nKTP ke-" << i++ << " (DLL):\n";
            cout << "NIK: " << current->data.nik << "\n";
            cout << "Nama: " << current->data.nama << "\n";
            cout << "Tempat/Tgl Lahir: " << current->data.tempat_lahir << ", " 
                 << current->data.tgl_lahir.day << "/" << current->data.tgl_lahir.month 
                 << "/" << current->data.tgl_lahir.year << "\n";
            cout << "Jenis Kelamin: " << (current->data.jenis_kelamin ? "Laki-laki" : "Perempuan") << "\n";
            cout << "Alamat: " << current->data.alamat.jalan << ", RT " << current->data.alamat.rt 
                 << "/RW " << current->data.alamat.rw << ", " << current->data.alamat.kelurahan 
                 << ", " << current->data.alamat.kecamatan << "\n";
            current = current->next;
        }
    }
    
    KTP* findByNIK(const string &nik) {
        NodeKTP* current = head;
        while (current != nullptr) {
            if (current->data.nik == nik) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    void removeByNIK(const string &nik) {
        NodeKTP* current = head;
        while (current != nullptr) {
            if (current->data.nik == nik) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                
                delete current;
                count--;
                cout << "Data KTP dengan NIK " << nik << " berhasil dihapus dari DLL.\n";
                return;
            }
            current = current->next;
        }
        cout << "Data KTP dengan NIK " << nik << " tidak ditemukan dalam DLL.\n";
    }
    
    int getCount() const { return count; }
};

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

// Global KTP Database
ArrayKTP ktpDatabase;
DoublyLinkedList ktpDLL;

void clearInput() {
    cin.clear();
    cin.ignore(CLEAR_BUFFER, '\n');
}

void clearScreen() {
    cout << "\n" << string(50, '=') << "\n";
}

void pauseProgram() {
    cout << "\nTekan Enter untuk melanjutkan...";
    // Periksa jika ada newline yang tersisa
    if (cin.peek() == '\n') 
        cin.get();
    else
        cin.ignore(CLEAR_BUFFER, '\n');
}

// Fungsi untuk input data KTP
KTP inputKTP() {
    KTP k;
    
    cout << "Masukkan Nama: ";
    getline(cin, k.nama);
    
    cout << "Masukkan NIK: ";
    getline(cin, k.nik);

    cout << "Tempat Lahir: ";
    getline(cin, k.tempat_lahir);

    cout << "Tanggal lahir (dd mm yyyy): ";
    cin >> k.tgl_lahir.day >> k.tgl_lahir.month >> k.tgl_lahir.year;

    cout << "Jenis kelamin (1=Laki, 0=Perempuan): ";
    cin >> k.jenis_kelamin;

    cout << "Golongan darah (A/B/O/AB): ";
    cin >> k.gol_darah;
    clearInput();

    cout << "Isi alamat\n";
    cout << "Jalan: ";
    getline(cin, k.alamat.jalan);
    cout << "RT: ";
    getline(cin, k.alamat.rt);
    cout << "RW: ";
    getline(cin, k.alamat.rw);
    cout << "Kelurahan: ";
    getline(cin, k.alamat.kelurahan);
    cout << "Kecamatan: ";
    getline(cin, k.alamat.kecamatan);

    cout << "Agama (1=Islam, 2=Kristen, 3=Katolik): ";
    cin >> k.agama;

    cout << "Status perkawinan (1=kawin, 0=belum): ";
    cin >> k.status_perkawinan;
    clearInput();

    cout << "Pekerjaan: ";
    getline(cin, k.pekerjaan);

    cout << "Kewarganegaraan (1=WNI, 0=WNA): ";
    cin >> k.kewarganegaraan;

    cout << "Berlaku Hingga (dd mm yyyy): ";
    cin >> k.berlaku_hingga.day 
        >> k.berlaku_hingga.month 
        >> k.berlaku_hingga.year;

    clearInput();
    return k;
}

// Fungsi untuk login dengan KTP
KTP* loginWithKTP() {
    string nik;
    cout << "\n=== LOGIN DENGAN KTP ===\n";
    cout << "Masukkan NIK: ";
    getline(cin, nik);
    
    // Cari di Array KTP
    KTP* ktp = ktpDatabase.findByNIK(nik);
    if (ktp == nullptr) {
        // Cari di DLL
        ktp = ktpDLL.findByNIK(nik);
    }
    
    return ktp;
}

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
    string nik; // Menyimpan NIK dari KTP
public:
    Siswa() : nis(""), nama(""), kelas(""), nik("") {
        for (int i=0;i<365;++i) hadir[i]=false;
    }
    void setData(const string &id, const string &n, const string &k, const string &nik_ktp = "") {
        nis = id;
        nama = n;
        kelas = k;
        nik = nik_ktp;
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
    string getNik() const {
        return nik;
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
    string nik; // Menyimpan NIK dari KTP
public:
    Guru() : nip(""), nama(""), mapel(""), senioritas(""), nik("") {}
    void setData(const string &id, const string &n, const string &m, const string &s, const string &nik_ktp = "") {
        nip=id;
        nama=n;
        mapel=m;
        senioritas=s;
        nik = nik_ktp;
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
    string getNik() const {
        return nik;
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
    string nik; // Menyimpan NIK dari KTP untuk autentikasi
public:
    User() : username(""), password(""), role(""), nis(""), nik("") {}
    void setData(const string &u, const string &p, const string &r, const string &n, const string &nik_ktp = "") {
        username=u; password=p; role=r; nis=n; nik=nik_ktp;
    }
    bool auth(const string &u, const string &p) const {    
        return (username==u && password==p);    
    }
    bool authWithNIK(const string &nik_input) const {
        return (nik == nik_input);
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
    string getNik() const {
        return nik;
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
    int rear;    // rear of queue (enqueue)
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
    int rear;    // Indeks belakang
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
        cout << "    NIS: " << antrian[front].getNis()    
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
            cout << "    NIS: " << antrian[bestIdx].getNis()    
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
MataPelajaran daftarMapel[MAX_MAPEL];
int jumlahMapel = 0;
Jadwal jadwalPelajaran;
Event kalender[MAX_EVENT];
int jumlahEvent = 0;
Siswa daftarSiswa[MAX_SISWA];
int jumlahSiswa = 0;
Guru daftarGuru[MAX_GURU];
int jumlahGuru = 0;
Penilaian matrixNilai[MAX_SISWA][MAX_MAPEL];
Transaksi daftarTransaksi[MAX_TRANSAKSI];
int jumlahTransaksi = 0;
User daftarUser[MAX_USERS];
int jumlahUser = 0;
Laporan daftarLaporan[MAX_LAPORAN];
int jumlahLaporan = 0;
ProfilSekolah profilSekolah;
StrukturOrganisasi strukturOrg;
ManajemenSurat manSurat;
Arsip arsipDigital;
Inventaris inventarisSekolah;
JadwalKegiatan jadwalKegSekolah;
Kuis kuisAktif;

// Global variables for Modul 3, 4, 5 & 6
MateriStack manMateri;
ManajemenPersetujuan manPersetujuan;

DataAnakOrangTua dataAnak[MAX_SISWA];
ManajemenTugas daftarTugasAnak;
AntrianPembayaran antrianTagihan;
StackPesan chatAnak;
QueueNotifikasi notifikasiSekolah;
// MODUL 6
AntrianDokumen antrianDokumenSekolah;
// MODUL 7 - BARU DENGAN DLL
ArsipDokumenSelesai arsipDokumenSelesai; 
RiwayatPenilaianTugas riwayatPenilaianTugas; // DLL untuk riwayat penilaian
SenioritasGuru senioritasGuru; // DLL untuk senioritas guru

// MODUL 8, 9, 10 - BARU DENGAN TREE
PohonKeluarga pohonKeluargaSiswa; // BST (Modul 8)
InventarisRuanganTree inventarisTree; // General Tree (Modul 9)
PohonEvaluasiMaxHeap pohonEvaluasi; // Max Heap (Modul 10)

RiwayatPelanggaranTree pohonPelanggaran;


// ================== HELPER & FUNGSI UMUM ==================

// Implementasi Dequeue untuk integrasi DLL
DokumenPermintaan AntrianDokumen::dequeue_impl() {
    if (count == 0) {
        cout << "Antrian dokumen kosong. Tidak ada permintaan untuk dilayani.";
        cout << endl;
        return DokumenPermintaan();    
    }
    DokumenPermintaan dilayani = antrian[front];
    
    cout << string(40, '-');
    cout << endl;
    cout << "Melayani permintaan terdepan (FIFO):";
    cout << endl;
    cout << "    NIS: " << dilayani.getNis()    
            << ", Dokumen: " << dilayani.getJenisDokumen()    
            << " (Status Sebelumnya: " << dilayani.getStatus() << ")";
    cout << endl;
    
    front = (front + 1) % MAX_ANTRIAN_DOKUMEN;
    count--;

    // Simulasi status akhir
    dilayani.setStatus("Selesai");
    cout << "Permintaan telah dilayani dan dikeluarkan dari antrian. Status Akhir: " << dilayani.getStatus() << ".\n";
    cout << string(40, '-');
    cout << endl;
    
    // INTEGRASI DLL BARU (FITUR 1)
    arsipDokumenSelesai.tambahArsip(dilayani);    
    
    return dilayani;
}


void tampilMapel() {
    for (int idx = 0; idx < jumlahMapel; ++idx) {
        daftarMapel[idx].tampil();
    }
}
void tampilSiswa() {
    for (int idx = 0; idx < jumlahSiswa; ++idx) {
        daftarSiswa[idx].tampilRingkas();
    }
}
void tampilGuru() {
    for (int idx = 0; idx < jumlahGuru; ++idx) {
        daftarGuru[idx].tampil();
    }
}
double totalPemasukan() {
    double total = 0.0;
    for (int idx = 0; idx < jumlahTransaksi; ++idx) {
        total += daftarTransaksi[idx].getJumlah();
    }
    return total;
}
void tampilEvent() {
    for (int idx = 0; idx < jumlahEvent; ++idx) {
        kalender[idx].tampil();
    }
}
int cariIndexSiswa(const string &nis) {
    for (int i=0;i<jumlahSiswa;++i) if (daftarSiswa[i].getId() == nis) return i;
    return -1;
}
int cariIndexMapel(const string &kode) {
    for (int i=0;i<jumlahMapel;++i) if (daftarMapel[i].getKode() == kode) return i;
    return -1;
}
bool cekUsernameExist(const string &username) {
    for(int i=0; i<jumlahUser; ++i) {
        if(daftarUser[i].getUser() == username) return true;
    }
    return false;
}
bool cekNisExist(const string &nis) {
    return cariIndexSiswa(nis) != -1;
}


void prosesPendaftaranSiswa() {
    if (jumlahSiswa >= MAX_SISWA || jumlahUser >= MAX_USERS) {
        cout << "Kapasitas sistem penuh. Tidak bisa mendaftar.";
        cout << endl;
        return;
    }

    string nis, nama, kelas, username, password;
    cout << "--- Pendaftaran Akun Siswa ---";
    cout << endl;

    while(true) {
        cout << "NIS: ";
        getline(cin, nis);
        if(nis.empty()) {
        cout << "NIS tidak boleh kosong.";
        cout << endl;
        continue;
        }
        if(cekNisExist(nis)) {
        cout << "NIS ini sudah terdaftar.";
        cout << endl;
        continue;
        }
        break;
    }
    cout << "Nama Lengkap: ";
    getline(cin, nama);
    cout << "Kelas: ";
    getline(cin, kelas);

    while(true) {
        cout << "Username: ";
        getline(cin, username);
        if(username.empty()) {
        cout << "Username tidak boleh kosong.";
        cout << endl;
        continue;    
    }
        if(cekUsernameExist(username)) {
        cout << "Username ini sudah dipakai.";
        cout << endl;
        continue;    
    }
        break;
    }
    cout << "Password: ";
    getline(cin, password);

    daftarSiswa[jumlahSiswa].setData(nis, nama, kelas);
    daftarUser[jumlahUser].setData(username, password, "siswa", nis);

    for (int m=0;m<MAX_MAPEL;++m) {
        matrixNilai[jumlahSiswa][m] = Penilaian();
    }

    jumlahSiswa++;
    jumlahUser++;

    cout << "Registrasi berhasil untuk siswa: " << nama << "!";
    cout << endl;
}

// ================== FUNGSI SPESIFIK SISWA ==================

void lihatNilaiSiswa(int si) {
    clearScreen();
    cout << "--- Nilai Akademik Anda ---\n";
    cout << "Siswa: " << daftarSiswa[si].getNama() << " (" << daftarSiswa[si].getId() << ")";
    cout << endl << endl;

    bool adaNilai = false;
    for (int m = 0; m < jumlahMapel; ++m) {
        double rata = matrixNilai[si][m].rata();
        if (rata >= 0) {
            cout << left << setw(25) << daftarMapel[m].getNama()
                << " | Nilai Akhir: " << fixed << setprecision(2) << rata;
            cout << endl;
            adaNilai = true;
        }
    }
    if (!adaNilai) {
        cout << "Belum ada data nilai yang diinput oleh guru.";
        cout << endl;
    }
    pauseProgram();
}

void lihatAbsensiSiswa(int si) {
    clearScreen();
    cout << "--- Absensi Anda ---\n";
    cout << "Siswa: " << daftarSiswa[si].getNama() << " (" << daftarSiswa[si].getId() << ")";
    cout << endl << endl;
    cout << "Total Kehadiran: " << daftarSiswa[si].hitungHadir() << " hari.";
    cout << endl;
    pauseProgram();
}

void menuELearningSiswa(string nis) {
    int p;
    do {
        clearScreen();
        cout << "\n--- MODUL E-LEARNING (SISWA) ---\n";
        cout << "1. Lihat Materi Pembelajaran";
        cout << endl;
        cout << "2. Lihat Materi Teratas (PEEK)"; // PEEK Tambahan
        cout << endl;
        cout << "3. Ambil Kuis";
        cout << endl;
        cout << "4. Lihat Hasil Kuis Terakhir";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {
            clearInput();
            p=-1;
        }
        clearInput();

        if (p==1) {
            clearScreen();
            manMateri.tampil();
            pauseProgram();
        } else if (p==2) { // PEEK
            clearScreen();
            manMateri.peek();
            pauseProgram();
        } else if (p==3) {
            clearScreen();
            kuisAktif.ambilKuis(nis);
            pauseProgram();
        } else if (p==4) {
            clearScreen();
            kuisAktif.nilaiKuis();
            pauseProgram();
        }
    } while (p!=0);
}

// ================== FUNGSI SPESIFIK ADMIN ==================

// ================== FUNGSI MODUL 8: BST ==================
void menuPohonKeluargaSiswa() {
    int p;
    do {
        clearScreen();
        cout << "\n--- MODUL 8: DATA KELUARGA SISWA (BINARY SEARCH TREE) ---\n";
        // MEMPERBAIKI ERROR SINTAKSIS PADA BARIS BERIKUT:
        cout << "BST membantu menyimpan kontak darurat terurut berdasarkan NIS untuk akses cepat. \n";
        cout << "1. Tambah/Update Data Keluarga\n";
        cout << "2. Lihat Data Terurut (In-Order Traversed)\n";
        cout << "3. Cari Data Keluarga (Berdasarkan NIS)\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        if (!(cin >> p)) { clearInput(); p = -1; }
        clearInput();

        if (p == 1) {
            string nis, namaWali, kontak;
            cout << "NIS Siswa: "; getline(cin, nis);
            cout << "Nama Wali: "; getline(cin, namaWali);
            cout << "Kontak Darurat: "; getline(cin, kontak);
            pohonKeluargaSiswa.tambahDataKeluarga(nis, namaWali, kontak);
        } else if (p == 2) {
            pohonKeluargaSiswa.tampilkanDataTerurut();
        } else if (p == 3) {
            string nis;
            cout << "Masukkan NIS yang dicari: "; getline(cin, nis);
            pohonKeluargaSiswa.cariDataKeluarga(nis);
        }
        if (p != 0) pauseProgram();
    } while (p != 0);
}

// ================== FUNGSI MODUL 9: GENERAL TREE ==================
void menuInventarisRuanganTree() {
    int p;
    // Inisialisasi data awal (simulasi)
    if (inventarisTree.getRoot()->firstChild == nullptr) {
        inventarisTree.tambahLokasi("SEKOLAH UTAMA", "Gedung A", "Ruang Kelas (20)");
        inventarisTree.tambahLokasi("Gedung A", "Ruang Lab Kimia", "Reagen (50), Meja Lab (10)");
        inventarisTree.tambahLokasi("SEKOLAH UTAMA", "Gedung B", "Ruang Guru (1)");
    }

    do {
        clearScreen();
        cout << "\n--- MODUL 9: INVENTARIS RUANGAN HIERARKIS (GENERAL TREE) ---\n";
        cout << "1. Tampilkan Hierarki Inventaris\n";
        cout << "2. Tambah Lokasi/Aset Baru\n";
        cout << "3. Lihat Detail Aset Lokasi\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        if (!(cin >> p)) { clearInput(); p = -1; }
        clearInput();

        if (p == 1) {
            inventarisTree.tampilkanHierarki();
        } else if (p == 2) {
            string parent, newLoc, aset;
            cout << "Nama Lokasi Parent (cth: Gedung A): "; getline(cin, parent);
            cout << "Nama Lokasi Baru/Ruangan: "; getline(cin, newLoc);
            cout << "Detail Aset (cth: Komputer (10), Meja (1)): "; getline(cin, aset);
            inventarisTree.tambahLokasi(parent, newLoc, aset);
        } else if (p == 3) {
            string target;
            cout << "Nama Lokasi yang dicari: "; getline(cin, target);
            inventarisTree.lihatDetailAset(target);
        }
        if (p != 0) pauseProgram();
    } while (p != 0);
}

// ================== FUNGSI MODUL 10 BARU: EVALUASI KEPUTUSAN (MAX HEAP) ==================
void menuPohonEvaluasi() {
    int p;
    // Data Simulasi Awal
    if (pohonEvaluasi.getSize() == 0) {
        pohonEvaluasi.insert("EV003", "Revisi Buku Ajar Fisika", 85);
        pohonEvaluasi.insert("EV001", "Peningkatan Keamanan Gedung B", 95);
        pohonEvaluasi.insert("EV002", "Penambahan Alat Musik Ekskul", 60);
    }
    
    do {
        clearScreen();
        cout << "\n--- MODUL 10: POHON EVALUASI KEPUTUSAN (MAX HEAP) ---\n";
        cout << "Total Program Evaluasi Tertunda: " << pohonEvaluasi.getSize() << "\n";
        cout << "Max Heap memastikan keputusan paling penting (skor tertinggi) selalu diakses pertama. \n";
        cout << "1. Tambah Program Evaluasi Baru (Insert)\n";
        cout << "2. Lihat Program Prioritas Tertinggi (Peek Max)\n";
        cout << "3. Proses Program Prioritas Tertinggi (Extract Max)\n";
        cout << "4. Tampilkan Struktur Max Heap\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        if (!(cin >> p)) { clearInput(); p = -1; }
        clearInput();

        if (p == 1) {
            string id, prog; int skor;
            cout << "ID Keputusan (cth: EV004): "; getline(cin, id);
            cout << "Nama Program: "; getline(cin, prog);
            cout << "Skor Dampak (1-100, 100=Paling Urgent): "; 
            if (!(cin >> skor)) { clearInput(); skor = 50; }
            clearInput();
            if (skor < 1 || skor > 100) skor = 50;
            pohonEvaluasi.insert(id, prog, skor);
        } else if (p == 2) {
            pohonEvaluasi.peekMax();
        } else if (p == 3) {
            pohonEvaluasi.extractMax();
        } else if (p == 4) {
            pohonEvaluasi.tampilkanStruktur();
        }
        if (p != 0) pauseProgram();
    } while (p != 0);
}


void menuManajemenAkademik() {
    int p;
    do {
        clearScreen();
        cout << "\n--- MANAJEMEN AKADEMIK (ADMIN) ---\n";
        cout << "1. Data Mata Pelajaran";
        cout << endl;
        cout << "2. Jadwal Pelajaran";
        cout << endl;
        cout << "3. Kalender Akademik";
        cout << endl;
        cout << "4. Penilaian (Input Nilai Siswa)";
        cout << endl;
        cout << "5. Absensi Siswa (Input Absensi)";
        cout << endl;
        cout << "6. Cetak Rapor Sederhana";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {
            clearInput();
            p=-1;
        }
        clearInput();
        if (p==1) {
            int q;
            do {
                clearScreen();
                cout << "\n-- DATA MATA PELAJARAN --\n";
                cout << "1. Tambah Mapel";
                cout << endl;
                cout << "2. Lihat Mapel";
                cout << endl;
                cout << "3. Hapus Mapel";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();
                    q=-1;
                }
                clearInput();
                if (q==1) {
                    if (jumlahMapel >= MAX_MAPEL) {
                    cout << "Kapasitas mapel penuh.";
                    cout << endl;
                    }
                    else {
                        string kode,nama,guru;    
                        cout << "Kode: ";
                        getline(cin,kode);
                        cout << "Nama: ";
                        getline(cin,nama);
                        cout << "Guru pengampu: ";
                        getline(cin,guru);
                        daftarMapel[jumlahMapel].setData(kode,nama,guru);
                        jumlahMapel++;
                        cout << "Mapel ditambahkan.\n";
                    }
                } else if (q==2) {
                    cout << left << setw(8) << "Kode" << " | " << setw(25) << "Nama" << " | " << "Guru";
                    cout << endl;
                    tampilMapel();
                } else if (q==3) {
                    string kode; cout << "Masukkan kode mapel yang dihapus: ";
                    getline(cin,kode);
                    int idx = cariIndexMapel(kode);
                    if (idx == -1)
                    cout << "Mapel tidak ditemukan.\n";
                    else {
                        for (int i=idx;i<jumlahMapel-1;++i) daftarMapel[i]=daftarMapel[i+1];
                        for (int s=0;s<jumlahSiswa;++s) matrixNilai[s][idx] = matrixNilai[s][jumlahMapel-1];
                        jumlahMapel--;
                        cout << "Mapel dihapus.";
                        cout << endl;
                    }
                }
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==2) {
            int q;
            do {
                clearScreen();
                cout << "\n-- JADWAL PELAJARAN --\n";
                cout << "1. Set Jam";
                cout << endl;
                cout << "2. Lihat Jadwal";
                cout << endl;
                cout << "3. Hitung slot terisi";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();
                    q=-1;
                }
                clearInput();
                if (q==1) {
                    int hari,jam; string kode;
                    cout << "Hari(0..4): ";
                    cin >> hari;
                    cout << "Jam(0..7): ";
                    cin >> jam;
                    clearInput();
                    cout << "Masukkan kode mapel utk slot ini: ";
                    getline(cin,kode);
                    jadwalPelajaran.setJam(hari,jam,kode);
                    cout << "Tersimpan.\n";
                } else if (q==2) {
                    jadwalPelajaran.tampil();
                } else if (q==3) {
                    cout << "Slot terisi: " << jadwalPelajaran.countAssigned() << " dari " << (MAX_HARI*8);
                    cout << endl;
                }
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==3) {
            int q;
            do {
                clearScreen();
                cout << "\n-- KALENDER AKADEMIK --\n";
                cout << "1. Tambah Event";
                cout << endl;
                cout << "2. Lihat Event";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();
                    q=-1;
                }
                clearInput();
                if (q==1) {
                    if (jumlahEvent >= MAX_EVENT) {
                    cout << "Kapasitas event penuh.";
                    cout << endl;
                    }
                    else {
                        string t,d; cout << "Tanggal(YYYY-MM-DD): ";
                        getline(cin,t);
                        cout << "Deskripsi event: ";
                        getline(cin,d);
                        kalender[jumlahEvent].setData(t,d);
                        jumlahEvent++;
                        cout << "Event ditambahkan.";
                        cout << endl;
                    }
                } else if (q==2) {
                    tampilEvent();
                }
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==4) {
            int q;
            do {
                clearScreen();
                cout << "\n-- PENILAIAN --\n";
                cout << "1. Input Nilai Komponen (harian,tugas,uts,uas)";
                cout << endl;
                cout << "2. Lihat Nilai Siswa per Mapel";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                clearInput();    
                q=-1;
                }
                clearInput();
                if (q==1) {
                    string nis,kode,idTugas;
                    double rata;
                    cout << "NIS: ";
                    getline(cin,nis);
                    int si = cariIndexSiswa(nis);
                    if (si == -1) {
                        cout << "Siswa tidak ditemukan.";
                        cout << endl;
                    }
                    else {
                        cout << "Kode Mapel: ";
                        getline(cin,kode);
                        int mi = cariIndexMapel(kode);
                        if (mi == -1) { cout << "Mapel tidak ditemukan.";
                        cout << endl;    
                    }
                        else {
                            double totalNilai=0; int countNilai=0;
                            for (int c=0;c<MAX_NILAI_COMPONENT;++c) {
                                double v;
                                cout << "Nilai komponen " << c+1 << " : ";
                                cin >> v;
                                clearInput();
                                matrixNilai[si][mi].komponen[c] = v;
                                if(v>=0) {
                                    totalNilai += v;
                                    countNilai++;
                                }
                            }
                            rata = (countNilai > 0) ? totalNilai / countNilai : 0;
                            
                            // Integrasi DLL Penilaian Tugas (Fitur 2)
                            cout << "ID Tugas yang Dinilai (contoh: TGS001): ";
                            getline(cin, idTugas);
                            riwayatPenilaianTugas.tambahPenilaian(idTugas, daftarMapel[mi].getNama(), 
                                "Tugas/Ujian " + daftarMapel[mi].getKode() + " (NIS: " + nis + ")", rata);

                            cout << "Nilai disimpan.\n";
                        }
                    }
                } else if (q==2) {
                    string nis; cout << "NIS: ";
                    getline(cin,nis);
                    int si = cariIndexSiswa(nis);
                    if (si == -1) {
                    cout << "Siswa tidak ditemukan.";
                    cout << endl;
                    }
                    else {
                        cout << "Nilai untuk " << daftarSiswa[si].getNama() << ":";
                        cout << endl;
                        for (int m=0;m<jumlahMapel;++m) {
                            cout << daftarMapel[m].getKode() << " - " << daftarMapel[m].getNama() << " => ";
                            double avg = matrixNilai[si][m].rata();
                            cout << "Rata komponen: " << avg;
                            cout << endl;
                        }
                    }
                }
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==5) {
            int q;
            do {
                clearScreen();
                cout << "\n-- ABSENSI SISWA --\n";
                cout << "1. Set hadir (hariIndex 0..364)";
                cout << endl;
                cout << "2. Hitung hadir (per siswa)";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                clearInput();    
                q=-1;
                }
                clearInput();
                if (q==1) {
                    string nis; int hariIndex; int hadirVal;
                    cout << "NIS: ";
                    getline(cin,nis);
                    int si = cariIndexSiswa(nis);
                    if (si==-1) {
                    cout<<"Siswa tidak ditemukan";
                    cout << endl;
                    }
                    else {
                        cout << "Hari index (0..364): ";
                        cin >> hariIndex;
                        clearInput();
                        cout << "Hadir (1=ya,0=tidak): ";
                        cin >> hadirVal;
                        clearInput();
                        daftarSiswa[si].setHadir(hariIndex, hadirVal==1);
                        cout << "Tersimpan.";
                        cout << endl;
                    }
                } else if (q==2) {
                    for (int s=0;s<jumlahSiswa;++s) {
                        cout << daftarSiswa[s].getNama() << " hadir: " << daftarSiswa[s].hitungHadir() << " hari";
                        cout << endl;
                    }
                }
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==6) {
            clearScreen();
            cout << "\n--- CETAK RAPOR SEDERHANA ---\n";
            for (int s=0;s<jumlahSiswa;++s) {
                double sum=0; int cnt=0;
                for (int m=0;m<jumlahMapel;++m) {
                    double r = matrixNilai[s][m].rata();
                    if (r>0) { sum += r; cnt++; }
                }
                double rata = (cnt==0)?0:sum/cnt;
                cout << "NIS: " << daftarSiswa[s].getId() << " | Nama: " << daftarSiswa[s].getNama() << " | Rata-rata: " << fixed << setprecision(2) << rata;
                cout << endl;
            }
            pauseProgram();
        }
    } while (p!=0);
}

void menuManajemenGuru() {
    int p;
    do {
        clearScreen();
        cout << "\n--- MANAJEMEN GURU & STAFF (ADMIN) ---\n";
        cout << "1. Biodata Guru (Array)";
        cout << endl;
        cout << "2. Daftar Senioritas Guru (DLL)";
        cout << endl; // Fitur 3
        cout << "3. Jadwal Mengajar (Lihat)";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {
            clearInput();    
            p=-1;
        }
        clearInput();
        if (p==1) {
            int q;
            do {
                clearScreen();
                cout << "\n-- BIODATA GURU --\n";
                cout << "1. Tambah Guru (ke Array)";
                cout << endl;
                cout << "2. Lihat Guru";
                cout << endl;
                cout << "3. Hapus Guru";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();    
                    q=-1;
                }
                clearInput();
                if (q==1) {
                    if (jumlahGuru >= MAX_GURU) {
                    cout << "Kapasitas guru penuh.";
                    cout << endl;
                    }
                    else {
                        string nip,nama,mapel,senioritas;
                        cout << "NIP: ";
                        getline(cin,nip);
                        cout << "Nama: ";
                        getline(cin,nama);
                        cout << "Mapel: ";
                        getline(cin,mapel);
                        cout << "Senioritas (Tahun Masuk): ";
                        getline(cin,senioritas);
                        daftarGuru[jumlahGuru].setData(nip,nama,mapel,senioritas);
                        senioritasGuru.tambahGuru(daftarGuru[jumlahGuru]); // Tambahkan ke DLL Senioritas
                        jumlahGuru++;
                        cout << "Guru ditambahkan.";
                        cout << endl;
                    }
                } else if (q==2) {
                    tampilGuru();
                } else if (q==3) {
                    string nip; cout << "Masukkan NIP yang dihapus: ";
                    getline(cin,nip);
                    int idx=-1;
                    for (int i=0;i<jumlahGuru;++i) if (daftarGuru[i].getNip()==nip) {    
                    idx=i;    
                    break;    
                    }
                    if (idx==-1)    
                    cout << "Tidak ditemukan.\n";
                    else {
                        // Hapus dari array
                        for (int i=idx;i<jumlahGuru-1;++i) daftarGuru[i]=daftarGuru[i+1];
                        jumlahGuru--;
                        // Hapus dari DLL Senioritas
                        senioritasGuru.hapusGuru(nip);    
                        cout << "Dihapus.";
                        cout << endl;
                    }
                }
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p == 2) { // Fitur 3 - Senioritas Guru DLL
            int q;
            do {
                clearScreen();
                cout << "\n-- DAFTAR SENIORITAS GURU (DLL) --\n";
                cout << "1. Tampilkan Urutan Senioritas (Senior ke Junior)";
                cout << endl;
                cout << "2. Tampilkan Urutan Junioritas (Junior ke Senior)";
                cout << endl;
                cout << "3. Sisipkan Guru ke Tengah Daftar (Simulasi Promosi)";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) { clearInput(); q = -1; }
                clearInput();

                if (q == 1) senioritasGuru.tampilSenioritasMaju();
                else if (q == 2) senioritasGuru.tampilSenioritasMundur();
                else if (q == 3) {
                    string nip,nama,mapel,senioritas, nipBefore;
                    cout << "NIP Guru baru: "; getline(cin, nip);
                    cout << "Nama Guru baru: "; getline(cin, nama);
                    cout << "Mapel: "; getline(cin, mapel);
                    cout << "Senioritas (Tahun Masuk): "; getline(cin, senioritas);
                    cout << "Sisipkan SEBELUM NIP (contoh: G102): "; getline(cin, nipBefore);
                    
                    Guru newGuru;    
                    newGuru.setData(nip, nama, mapel, senioritas);
                    senioritasGuru.sisipGuru(newGuru, nipBefore);
                }

                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==3) {
            jadwalPelajaran.tampil();
            cout << "Note: jadwal yang ditampilkan menggunakan kode mapel.";
            cout << endl;
            pauseProgram();
        }
    } while (p!=0);
}

void menuManajemenSiswa() {
    int p;
    do {
        clearScreen();
        cout << "\n--- MANAJEMEN SISWA (ADMIN) ---\n";
        cout << "1. Pendaftaran Siswa Baru (Buat Akun)";
        cout << endl;
        cout << "2. Lihat Semua Siswa";
        cout << endl;
        cout << "3. Cetak Kartu Sederhana";
        cout << endl;
        cout << "4. Mutasi/Hapus Siswa";
        cout << endl;
        cout << "5. Modul 8: Data Keluarga Siswa (BST) - FITUR BARU";
        cout << endl;
        cout << "6. Catat Pelanggaran Siswa (Right-Skewed Tree)";
        cout << endl;
        cout << "7. Lihat Riwayat Pelanggaran Siswa";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {
        clearInput();    
        p=-1;
        }
        clearInput();
        if (p==1) {
            prosesPendaftaranSiswa();
            pauseProgram();
        } else if (p==2) {
            tampilSiswa();
            pauseProgram();
        } else if (p==3) {
            string nis; cout << "Masukkan NIS untuk cetak kartu: ";
            getline(cin, nis);
            int si = cariIndexSiswa(nis);
            if (si == -1)    
            cout << "Siswa tidak ditemukan.\n";
            else {
                cout << "\n=== KARTU PELAJAR ===\n";
                cout << "NIS: " << daftarSiswa[si].getId() << "\nNama: " << daftarSiswa[si].getNama() << "\nKelas: " << daftarSiswa[si].getKelas();
            }
            pauseProgram();
        } else if (p==4) {
            string nis; cout << "NIS yang dihapus: ";
            getline(cin,nis);
            int idx=cariIndexSiswa(nis);
            if (idx==-1)    
            cout << "Tidak ditemukan.\n";
            else {
                int userIdx = -1;
                for(int i=0; i<jumlahUser; ++i) {
                    if(daftarUser[i].getNis() == nis) {
                        userIdx = i;
                        break;
                    }
                }
                if (userIdx != -1) {
                    for(int j=userIdx; j<jumlahUser-1; ++j) {
                        daftarUser[j] = daftarUser[j+1];
                    }
                    jumlahUser--;
                }

                for (int i=idx;i<jumlahSiswa-1;++i) {
                    daftarSiswa[i] = daftarSiswa[i+1];
                    for (int m=0;m<MAX_MAPEL;++m) matrixNilai[i][m] = matrixNilai[i+1][m];
                }
                jumlahSiswa--;

                cout << "Siswa dan akun terkait telah dihapus.";
                cout << endl;
            }
            pauseProgram();
        } else if (p == 5) { // Modul 8 BST
            menuPohonKeluargaSiswa();
        }
        else if (p == 6) {
            string nis, jenis, tgl; int poin;
            cout << "Masukkan NIS Siswa: "; getline(cin, nis);
            if (cariIndexSiswa(nis) == -1) {
                cout << "Siswa tidak ditemukan!\n";
            } else {
                cout << "Jenis Pelanggaran: "; getline(cin, jenis);
                cout << "Tanggal (YYYY-MM-DD): "; getline(cin, tgl);
                cout << "Poin Minus: "; cin >> poin; clearInput();
                pohonPelanggaran.tambahPelanggaran(nis, jenis, tgl, poin);
            }
            pauseProgram();
        } else if (p == 7) {
            string nis;
            cout << "Masukkan NIS Siswa: "; getline(cin, nis);
            pohonPelanggaran.tampilkanRiwayatSiswa(nis);
            pauseProgram();
        }
    } while (p!=0);
}

void menuManajemenKeuangan() {
    int p;
    do {
        clearScreen();
        cout << "\n--- MANAJEMEN KEUANGAN (ADMIN) ---\n";
        cout << "1. Tambah Transaksi";
        cout << endl;
        cout << "2. Lihat Transaksi";
        cout << endl;
        cout << "3. Total Pemasukan";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {
            clearInput();    
            p=-1;
        }
        clearInput();
        if (p==1) {
            if (jumlahTransaksi >= MAX_TRANSAKSI) {
            cout << "Kapasitas transaksi penuh.";
            cout << endl;
            }
            else {
                string id, nis, ket;    
                double jml;
                cout << "ID Transaksi: ";
                getline(cin,id);
                cout << "NIS Pembayar: ";
                getline(cin,nis);
                cout << "Jumlah: ";
                cin >> jml;
                clearInput();
                cout << "Keterangan: ";
                getline(cin,ket);
                daftarTransaksi[jumlahTransaksi].setData(id, nis, jml, ket);
                jumlahTransaksi++;
                cout << "Transaksi disimpan.";
                cout << endl;
            }
        } else if (p==2) {
            cout << left << setw(8) << "ID" << " | " << setw(8) << "NIS" << " | " << setw(10) << "Jumlah" << " | Ket\n";
            for (int i=0;i<jumlahTransaksi;++i) daftarTransaksi[i].tampil();
        } else if (p==3) {
            cout << "Total pemasukan: Rp " << fixed << setprecision(0) << totalPemasukan();
            cout << endl;
        }
        if(p!=0) pauseProgram();
    } while (p!=0);
}

void menuAdministrasiSekolah() {
    int p;
    do {
        clearScreen();
        cout << "\n--- MODUL 2: ADMINISTRASI SEKOLAH (ADMIN) ---\n";
        cout << "1. Profil Sekolah (Set/Lihat)";
        cout << endl;
        cout << "2. Struktur Organisasi";
        cout << endl;
        cout << "3. Surat Menyurat";
        cout << endl;
        cout << "4. Arsip Dokumen Digital (Array)";
        cout << endl;
        cout << "5. Inventaris & Aset (Array)";
        cout << endl;
        cout << "6. Jadwal Kegiatan Sekolah";
        cout << endl;
        cout << "7. Modul 6: Antrian Dokumen (QUEUE ARRAY CIRCULAR)";
        cout << endl;    
        cout << "8. Modul 7: Arsip Dokumen Selesai (DLL)";
        cout << endl; // Fitur 1
        cout << "9. Modul 9: Inventaris Ruangan Hierarkis (General Tree) - FITUR BARU";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {
            clearInput();    
            p=-1;
        }
        clearInput();
        if (p==1) {
            int q;
            do {
                clearScreen();
                profilSekolah.tampil();
                cout << "\n1. Edit Profil\n2. Kembali\nPilih: ";
                if (!(cin >> q)) {    
                clearInput();    
                q = -1;    
            }
                clearInput();
                if (q == 1) {
                    string n,a,ak,v,m;
                    cout << "Nama sekolah: ";
                    getline(cin,n);
                    cout << "Alamat: ";
                    getline(cin,a);
                    cout << "Akreditasi: ";
                    getline(cin,ak);
                    cout << "Visi: ";
                    getline(cin,v);
                    cout << "Misi: ";
                    getline(cin,m);
                    profilSekolah.setData(n,a,ak,v,m);
                    cout << "Profil diperbarui.";
                    cout << endl;
                }
                if(q!=2 && q!=1) pauseProgram();
            } while (q != 2);
        } else if (p==2) {
            int q;
            do {
                clearScreen();
                cout << "\n-- STRUKTUR ORGANISASI --\n";
                cout << "1. Tambah Data";
                cout << endl;
                cout << "2. Lihat";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();    
                    q=-1;
                }
                clearInput();
                if (q==1) {
                    string jab, nam;
                    cout << "Jabatan: ";
                    getline(cin,jab);
                    cout << "Nama: ";
                    getline(cin,nam);
                    strukturOrg.tambah(jab,nam);
                } else if (q==2) strukturOrg.tampil();
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==3) {
            int q;
            do {
                clearScreen();
                cout << "\n-- SURAT MENYURAT --\n";
                cout << "1. Tambah Surat";
                cout << endl;
                cout << "2. Lihat Surat";
                cout << endl;
                cout << "3. Hapus Surat";
                cout << endl;
                cout << "4. Kirim Surat ke Antrian Persetujuan (Modul 5)";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();    
                    q=-1;
                }
                clearInput();
                if (q==1) manSurat.tambah();
                else if (q==2) manSurat.tampil();
                else if (q==3) manSurat.hapus();
                else if (q==4) {
                    string id;
                    cout << "Masukkan ID/Nomor Surat untuk persetujuan: ";
                    getline(cin, id);
                    manPersetujuan.tambah(id, "Surat Keputusan", "Pengajuan Surat: " + id);
                }
                if(q!=0) pauseProgram();
            } while (q!=0);
        }
        else if (p==4) {
            int q;
            do {
                clearScreen();
                cout << "\n-- ARSIP DIGITAL --\n";
                cout << "1. Tambah Arsip";
                cout << endl;
                cout << "2. Lihat Arsip";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();    
                    q=-1;
                }
                clearInput();
                if (q==1) arsipDigital.tambah();
                else if (q==2) arsipDigital.tampil();
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==5) {
            int q;
            do {
                clearScreen();
                cout << "\n-- INVENTARIS & ASET (Array) --\n";
                cout << "1. Tambah Barang";
                cout << endl;
                cout << "2. Lihat Barang";
                cout << endl;
                cout << "3. Total Barang";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();    
                    q=-1;
                }
                clearInput();
                if (q==1) inventarisSekolah.tambah();
                else if (q==2) inventarisSekolah.tampil();
                else if (q==3)
                cout << "Total barang: " << inventarisSekolah.totalBarang();
                cout << endl;
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==6) {
            int q;
            do {
                clearScreen();
                cout << "\n-- JADWAL KEGIATAN SEKOLAH --\n1. Input Kegiatan per Hari\n2. Lihat Semua Jadwal\n0. Kembali\nPilih: ";
                if (!(cin >> q)) {
                    clearInput(); q=-1;
                }
                clearInput();
                if (q==1) jadwalKegSekolah.isiHari();
                else if (q==2) jadwalKegSekolah.tampilSemua();
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p == 7) { // LOGIKA MODUL 6
            int q;
            do {
                clearScreen();
                cout << "\n-- MODUL 6: MANAJEMEN ARSIP DOKUMEN AKTIF (QUEUE CIRCULAR) --\n";
                cout << "Total Antrian Aktif: " << antrianDokumenSekolah.getCount() << " / " << MAX_ANTRIAN_DOKUMEN << "\n";
                cout << string(60, '=');
                cout << endl;
                cout << "1. Tambah Permintaan Dokumen (ENQUEUE)";
                cout << endl;
                cout << "2. Layani Permintaan Terdepan (DEQUEUE)";
                cout << endl;
                cout << "3. Lihat Antrian Lengkap";
                cout << endl;
                cout << "4. Cari & Update Status Dokumen";
                cout << endl;    
                cout << "5. Laporan Statistik Jenis Dokumen";
                cout << endl;
                cout << "6. Simulasi Prioritas Dokumen";
                cout << endl;    
                cout << "7. Filter Antrian Berdasarkan Status";    
                cout << endl;
                cout << "8. Hapus Dokumen Tertentu (Non-FIFO)";    
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                    clearInput();    
                    q = -1;
                }
                clearInput();
                if (q == 1) {
                    string nis, jenis, tgl, lok;
                    int prio;
                    cout << "NIS Siswa: ";    
                    getline(cin, nis);
                    cout << "Jenis Dokumen (Suket/Transkrip/Ijazah): ";    
                    getline(cin, jenis);
                    cout << "Tanggal Permintaan (YYYY-MM-DD): ";    
                    getline(cin, tgl);
                    cout << "Lokasi Simpan Awal: ";    
                    getline(cin, lok);
                    cout << "Prioritas (1=Tinggi, 2=Sedang, 3=Rendah): ";    
                    if (!(cin >> prio)) {    
                    clearInput();    
                    prio = 3;    
                }
                    clearInput();
                    if (prio < 1 || prio > 3) prio = 3;
                    antrianDokumenSekolah.enqueue(nis, jenis, tgl, lok, prio);
                } else if (q == 2) {
                    antrianDokumenSekolah.dequeue();
                } else if (q == 3) {
                    antrianDokumenSekolah.tampil();
                } else if (q == 4) {
                    string nisCari, jenisCari, statusBaru;
                    cout << "Masukkan NIS Siswa yang dicari: ";    
                    getline(cin, nisCari);
                    antrianDokumenSekolah.cariDokumen(nisCari); // Tampilkan dulu
                    cout << "\n--- UPDATE STATUS ---\n";
                    cout << "Pilih Jenis Dokumen yang akan diubah: ";    
                    getline(cin, jenisCari);
                    cout << "Status Baru (Contoh: Diproses, Selesai): ";    
                    getline(cin, statusBaru);
                    antrianDokumenSekolah.updateStatusDokumen(nisCari, jenisCari, statusBaru);
                } else if (q == 5) {
                    antrianDokumenSekolah.laporanStatistik();
                } else if (q == 6) {
                    antrianDokumenSekolah.simulasiPrioritas();
                } else if (q == 7) {    
                    string statusTarget;
                    cout << "Masukkan Status yang difilter (Menunggu/Diproses/Selesai): ";
                    getline(cin, statusTarget);
                    antrianDokumenSekolah.filterStatus(statusTarget);
                } else if (q == 8) {    
                    string nisHapus, jenisHapus;
                    cout << "Masukkan NIS Dokumen yang akan dihapus: ";
                    getline(cin, nisHapus);
                    cout << "Masukkan Jenis Dokumen yang akan dihapus: ";
                    getline(cin, jenisHapus);
                    antrianDokumenSekolah.hapusDokumen(nisHapus, jenisHapus);
                }
                if (q != 0) pauseProgram();
            } while (q != 0);
        } else if (p == 8) { // MODUL 7 - Arsip Dokumen Selesai (DLL) - Fitur 1
            int q;
            do {
                clearScreen();
                cout << "\n-- MODUL 7: ARSIP DOKUMEN SELESAI (DOUBLE LINKED LIST) --\n";
                cout << "1. Lihat Arsip (Terlama ke Terbaru)";
                cout << endl;
                cout << "2. Lihat Arsip (Terbaru ke Terlama)";    
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) { clearInput(); q = -1; }
                clearInput();

                if (q == 1) arsipDokumenSelesai.tampilMaju();
                else if (q == 2) arsipDokumenSelesai.tampilMundur();
                
                if(q != 0) pauseProgram();
            } while (q != 0);
        } else if (p == 9) { // MODUL 9 - General Tree
            menuInventarisRuanganTree();
        }
    } while (p!=0);
}

void menuELearningAdmin() {
    int p;
    do {
        clearScreen();
        cout << "\n--- MODUL 3: E-LEARNING (ADMIN) ---\n";
        cout << "1. Manajemen Materi Pembelajaran (STACK ARRAY)";
        cout << endl;
        cout << "2. Manajemen Kuis Online";
        cout << endl;
        cout << "3. Riwayat Penilaian Tugas (DLL)"; // Fitur 2
        cout << endl;
        cout << "4. Modul 10: Pohon Evaluasi Keputusan (Max Heap) - FITUR BARU";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {
            clearInput();    
            p=-1;
        }
        clearInput();

        if (p==1) {
            int q;
            do {
                clearScreen();
                cout << "\n-- Manajemen Materi (Stack Array) --\n";
                cout << "1. Tambah Materi (PUSH)";
                cout << endl;
                cout << "2. Hapus Materi Teratas (POP)";
                cout << endl;
                cout << "3. Lihat Materi Teratas (PEEK)"; // PEEK Tambahan
                cout << endl;
                cout << "4. Lihat Semua Materi";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) {
                clearInput();    
                q=-1;
                }
                clearInput();
                if (q==1) {
                    string j,u;
                    cout << "Judul: ";
                    getline(cin,j);
                    cout << "URL File: ";
                    getline(cin,u);
                    manMateri.push(j,u); // PUSH operation
                } else if (q==2) {
                    manMateri.pop(); // POP operation
                } else if (q==3) {
                    manMateri.peek(); // PEEK operation
                } else if (q==4) manMateri.tampil();
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p==2) {
            clearScreen();
            cout << "\n-- Manajemen Kuis Online --\n";
            kuisAktif.buatKuis();
            pauseProgram();
        } else if (p == 3) { // Fitur 2 - Riwayat Penilaian Tugas DLL
            int q;
            do {
                clearScreen();
                cout << "\n-- RIWAYAT PENILAIAN TUGAS (DLL) --\n";
                cout << "1. Tambah Data Penilaian (Simulasi)";
                cout << endl;
                cout << "2. Lihat Riwayat (Terbaru ke Terlama)";
                cout << endl;
                cout << "3. Lihat Riwayat (Terlama ke Terbaru - Reverse)";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> q)) { clearInput(); q = -1; }
                clearInput();
                
                if (q == 1) {
                    string id, mapel, desk; double nilai;
                    cout << "ID Tugas: "; getline(cin, id);
                    cout << "Mapel: "; getline(cin, mapel);
                    cout << "Deskripsi: "; getline(cin, desk);
                    cout << "Nilai Rata-rata: "; cin >> nilai; clearInput();
                    riwayatPenilaianTugas.tambahPenilaian(id, mapel, desk, nilai);
                } else if (q == 2) {
                    riwayatPenilaianTugas.tampilRiwayat();
                } else if (q == 3) {
                    riwayatPenilaianTugas.tampilReverse();
                }
                
                if(q!=0) pauseProgram();
            } while (q!=0);
        } else if (p == 4) { // Modul 10 Max Heap
            menuPohonEvaluasi();
        }
    } while (p!=0);
}


// ================== FUNGSI MODUL 5: KEPALA SEKOLAH ==================

void dashboardRingkasanAktivitas() {
    clearScreen();
    cout << "\n--- DASHBOARD RINGKASAN AKTIVITAS SEKOLAH ---\n";
    cout << "----------------------------------------------\n";
    cout << "    Akademik & SDM:\n";
    cout << "    Total Siswa Terdaftar: " << jumlahSiswa << " siswa";
    cout << endl;
    cout << "    Total Guru & Staf:      " << jumlahGuru << " orang";
    cout << endl;
    cout << "    Total Mata Pelajaran:   " << jumlahMapel << " mapel";
    cout << endl;
    cout << "    Jadwal & Agenda:";
    cout << endl;
    cout << "    Slot Jadwal Terisi:     " << jadwalPelajaran.countAssigned() << " slot";
    cout << endl;
    cout << "    Event Kalender Aktif:   " << jumlahEvent << " event";
    cout << endl;
    cout << "    Keuangan & Administrasi:";
    cout << endl;
    cout << "    Total Pemasukan (Simulasi): Rp " << fixed << setprecision(0) << totalPemasukan();
    cout << endl;
    cout << "    Total Aset Inventaris: " << inventarisSekolah.totalBarang() << " barang";
    cout << endl;
    cout << "    Persetujuan Tertunda:   " << manPersetujuan.getJumlahTertunda() << " item (Queue)";
    cout << endl;
    cout << "    Antrian Dokumen:      " << antrianDokumenSekolah.getCount() << " item (Queue Circular)"; // TAMBAHAN
    cout << endl;
    cout << "----------------------------------------------";
    cout << endl;
    pauseProgram();
}

void laporanKinerja() {
    clearScreen();
    cout << "\n--- LAPORAN KINERJA GURU & SISWA ---\n";
    
    // 1. Kinerja Siswa (Rata-rata Nilai)
    double totalRataSiswa = 0;
    int siswaCount = 0;
    cout << "\n[ KINERJA SISWA ]\n";
    for (int s = 0; s < jumlahSiswa; ++s) {
        double sumMapel = 0;
        int countMapel = 0;
        for (int m = 0; m < jumlahMapel; ++m) {
            double r = matrixNilai[s][m].rata();
            if (r > 0) {    
            sumMapel += r;    
            countMapel++;    
            }
        }
        double rata = (countMapel == 0) ? 0.0 : sumMapel / countMapel;
        if (rata > 0) {
            cout << left << setw(20) << daftarSiswa[s].getNama() << " | Rata-rata: " << fixed << setprecision(2) << rata;
            cout << endl;
            totalRataSiswa += rata;
            siswaCount++;
        }
    }
    double rataRataSekolah = (siswaCount == 0) ? 0.0 : totalRataSiswa / siswaCount;
    cout << "\n>> Rata-Rata Nilai Sekolah: " << fixed << setprecision(2) << rataRataSekolah;
    cout << endl;

    // 2. Kinerja Guru (Beban Ajar)
    cout << "\n[ KINERJA GURU (Beban Ajar) ]\n";
    for (int g = 0; g < jumlahGuru; ++g) {
        int beban = 0;
        for(int h=0; h < MAX_HARI; ++h) {
            for(int j=0; j < 8; ++j) {
                int mapelIdx = cariIndexMapel(jadwalPelajaran.getMapelCode(h, j));
                if (mapelIdx != -1 && daftarMapel[mapelIdx].getGuru() == daftarGuru[g].getNama()) {
                    beban++;
                }
            }
        }
        cout << left << setw(20) << daftarGuru[g].getNama() << " | Mapel Ajar: " << daftarGuru[g].getMapel() << " | Beban Jam: " << beban;
        cout << endl;
    }
    pauseProgram();
}

void monitoringKeuangan() {
    clearScreen();
    cout << "\n--- MONITORING KEUANGAN ---\n";
    cout << "Total Pemasukan Tercatat: Rp " << fixed << setprecision(0) << totalPemasukan();
    cout << endl;
    cout << "Rincian Transaksi:";
    cout << endl;
    cout << left << setw(8) << "ID" << " | " << setw(8) << "NIS" << " | " << setw(10) << "Jumlah" << " | Ket\n";
    for (int i=0;i<jumlahTransaksi;++i) daftarTransaksi[i].tampil();
    pauseProgram();
}

void statistikAkademikKehadiran() {
    clearScreen();
    cout << "\n--- STATISTIK AKADEMIK & KEHADIRAN ---\n";
    
    // Statistik Akademik
    double totalRataSekolah = 0;
    int totalSiswaValid = 0;
    for (int s = 0; s < jumlahSiswa; ++s) {
        double sumMapel = 0;
        int countMapel = 0;
        for (int m = 0; m < jumlahMapel; ++m) {
            double r = matrixNilai[s][m].rata();
            if (r > 0) {    
            sumMapel += r;    
            countMapel++;    
            }
        }
        double rata = (countMapel == 0) ? 0.0 : sumMapel / countMapel;
        if (rata > 0) {
            totalRataSekolah += rata;
            totalSiswaValid++;
        }
    }
    double rataRataSekolah = (totalSiswaValid == 0) ? 0.0 : totalRataSekolah / totalSiswaValid;
    cout << "[ AKADEMIK ]\n";
    cout << "Rata-Rata Nilai Akademik Sekolah: " << fixed << setprecision(2) << rataRataSekolah;
    cout << endl;

    // Statistik Kehadiran
    double totalPersenHadir = 0;
    for (int s = 0; s < jumlahSiswa; ++s) {
        totalPersenHadir += daftarSiswa[s].hitungPersenHadir();
    }
    double rataRataHadir = (jumlahSiswa == 0) ? 0.0 : totalPersenHadir / jumlahSiswa;
    cout << "\n[ KEHADIRAN ]\n";
    cout << "Rata-Rata Persentase Kehadiran Siswa: " << fixed << setprecision(1) << rataRataHadir << "%";
    cout << endl;
    
    pauseProgram();
}

void persetujuanSuratData() {
    int p;
    do {
        clearScreen();
        cout << "\n--- PERSETUJUAN DATA & SURAT KEPUTUSAN (QUEUE) ---\n";
        manPersetujuan.tampil();
        cout << "\n1. Setujui Permintaan (Dequeue Front/ID)\n";
        cout << "2. Tambah Permintaan Baru (Simulasi)";
        cout << endl;
        cout << "0. Kembali";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> p)) {    
        clearInput();    
        p = -1; }
        clearInput();

        if (p == 1) {
            string id;
            cout << "Masukkan ID Persetujuan yang disetujui: ";
            getline(cin, id);
            manPersetujuan.prosesPersetujuan(id);
        } else if (p == 2) {
            string id, tipe, desk;
            cout << "ID Permintaan: ";
            getline(cin, id);
            cout << "Tipe (Surat/Laporan): ";
            getline(cin, tipe);
            cout << "Deskripsi: ";
            getline(cin, desk);
            manPersetujuan.tambah(id, tipe, desk);
        }
        if(p!=0) pauseProgram();
    } while (p != 0);
}

void mainMenuKepalaSekolah() {
    int pilih;
    do {
        clearScreen();
        cout << "\n========================================\n";
        cout << "     MODUL 5: PORTAL KEPALA SEKOLAH\n";
        cout << "========================================";
        cout << endl;
        cout << "1. Dashboard Ringkasan Aktivitas Sekolah";
        cout << endl;
        cout << "2. Laporan Kinerja Guru & Siswa";
        cout << endl;
        cout << "3. Monitoring Keuangan";
        cout << endl;
        cout << "4. Statistik Akademik dan Kehadiran";
        cout << endl;
        cout << "5. Persetujuan Data & Surat Keputusan";
        cout << endl;
        cout << "0. Logout";
        cout << endl;
        cout << "Pilih menu: ";
        if (!(cin >> pilih)) {
            clearInput();
            pilih = -1;
        }
        clearInput();

        if (pilih == 1) dashboardRingkasanAktivitas();
        else if (pilih == 2) laporanKinerja();
        else if (pilih == 3) monitoringKeuangan();
        else if (pilih == 4) statistikAkademikKehadiran();
        else if (pilih == 5) persetujuanSuratData();

    } while (pilih != 0);
    cout << "Anda telah logout dari portal Kepala Sekolah.";
    cout << endl;
    pauseProgram();
}

void mainMenuAdmin() {
    int pilih;
    do {
        clearScreen();
        cout << "\n========================================\n";
        cout << "    † SISTEM MANAJEMEN SEKOLAH (ADMIN)    † \n";
        cout << "========================================\n";
        cout << "1. Modul Utama (Akademik, Guru, Siswa, Keuangan)";
        cout << endl;
        cout << "2. Modul - Administrasi Sekolah (Modul 2, 6, 7, 9)";
        cout << endl;
        cout << "3. Modul - E-Learning (Modul 3, 10)";
        cout << endl;
        cout << "0. Logout";
        cout << endl;
        cout << "Pilih menu: ";
        if (!(cin >> pilih)) {
        //clearInput();
        pilih=-1;
        }
        clearInput();

        if (pilih == 1) {
            int sub;
            do {
                clearScreen();
                cout << "\n--- MODUL UTAMA (ADMIN) ---\n";
                cout << "1. Manajemen Akademik";
                cout << endl;
                cout << "2. Manajemen Guru & Staff";
                cout << endl;
                cout << "3. Manajemen Siswa (Termasuk Modul 8: BST Keluarga)";
                cout << endl;
                cout << "4. Manajemen Keuangan";
                cout << endl;
                cout << "0. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> sub)) {
                clearInput();
                sub=-1;
                }
                clearInput();
                if (sub==1) menuManajemenAkademik();
                else if (sub==2) menuManajemenGuru();
                else if (sub==3) menuManajemenSiswa();
                else if (sub==4) menuManajemenKeuangan();
                else if (sub==0) break;
            } while (true);
        } else if (pilih == 2) {
            menuAdministrasiSekolah();
        } else if (pilih == 3) {
            menuELearningAdmin();
        }
        
    } while (pilih != 0);
    cout << "Anda telah logout.";
    cout << endl;
    pauseProgram();
}

void mainMenuSiswa(string nis) {
    int si = cariIndexSiswa(nis);
    if (si == -1) {
        cout << "Error: Data siswa tidak ditemukan. Harap hubungi admin.";
        cout << endl;
        pauseProgram();
        return;
    }
    string namaSiswa = daftarSiswa[si].getNama();

    int pilih;
    do {
        clearScreen();
        cout << "\n========================================\n";
        cout << "    † SELAMAT DATANG, " << namaSiswa << "\n";
        cout << "========================================";
        cout << endl;
        cout << "1. Lihat Jadwal Pelajaran";
        cout << endl;
        cout << "2. Lihat Kalender Akademik";
        cout << endl;
        cout << "3. Lihat Nilai Saya";
        cout << endl;
        cout << "4. Lihat Absensi Saya";
        cout << endl;
        cout << "5. Modul E-Learning";
        cout << endl;
        cout << "0. Logout";
        cout << endl;
        cout << "Pilih: ";
        if (!(cin >> pilih)) {
        clearInput();
        pilih=-1;
        }
        clearInput();

        if (pilih == 1) {
            clearScreen();
            cout << "--- Jadwal Pelajaran ---";
            cout << endl;
            jadwalPelajaran.tampil();
            pauseProgram();
        } else if (pilih == 2) {
            clearScreen();
            cout << "--- Kalender Akademik ---";
            cout << endl;
            tampilEvent();
            pauseProgram();
        } else if (pilih == 3) {
            lihatNilaiSiswa(si);
        } else if (pilih == 4) {
            lihatAbsensiSiswa(si);
        } else if (pilih == 5) {
            menuELearningSiswa(nis);
        }
    } while (pilih != 0);
    cout << "Anda telah logout.";
    cout << endl;
    pauseProgram();
}

void lihatNilaiKehadiranAnak(const string &nisAnak) {
    clearScreen();
    cout << "=== NILAI & KEHADIRAN ANAK (Array 2D) ===";
    cout << endl;

    int siAnak = cariIndexSiswa(nisAnak);
    if (siAnak == -1) {
        cout << "Data anak tidak ditemukan.";
        cout << endl;
        pauseProgram();
        return;
    }

    cout << "Nama Anak: " << daftarSiswa[siAnak].getNama();
    cout << endl;
    cout << "NIS: " << nisAnak;
    cout << endl << endl;

    bool adaNilai = false;
    cout << "--- NILAI AKADEMIK PER MAPEL ---\n";
    for (int m = 0; m < jumlahMapel; ++m) {
        double rata = matrixNilai[siAnak][m].rata();
        if (rata >= 0) {
            cout << left << setw(25) << daftarMapel[m].getNama()
                << " | Nilai: " << fixed << setprecision(2) << rata << "\n";
            adaNilai = true;
        }
    }
    if (!adaNilai) {
        cout << "Belum ada data nilai.";
        cout << endl;
    }

    cout << "\n--- KEHADIRAN ANAK ---\n";
    int totalHadir = daftarSiswa[siAnak].hitungHadir();
    cout << "Total Hadir: " << totalHadir << " hari.\n";
    cout << "Tingkat Kehadiran: " << fixed << setprecision(1)
        << daftarSiswa[siAnak].hitungPersenHadir() << "%";
    cout << endl;

    pauseProgram();
}

void menuOrangTuaWali() {
    clearScreen();
    cout << "\n========================================\n";
    cout << "          MODUL 4: PORTAL ORANG TUA / WALI\n";
    cout << "========================================";
    cout << endl << endl;

    string nisAnak;
    cout << "Masukkan NIS anak Anda: ";
    getline(cin, nisAnak);

    int siAnak = cariIndexSiswa(nisAnak);
    if (siAnak == -1) {
        cout << "Data anak tidak ditemukan dalam sistem.";
        cout << endl;
        pauseProgram();
        return;
    }

    int pilih;
    do {
        clearScreen();
        cout << "\n========================================\n";
        cout << "    PORTAL ORANG TUA - " << daftarSiswa[siAnak].getNama() << "\n";
        cout << "========================================\n";
        cout << "1. Melihat Nilai & Kehadiran Anak";
        cout << endl;
        cout << "2. Melihat Jadwal & Tugas Anak (Linked List)";
        cout << endl;
        cout << "3. Tagihan & Riwayat Pembayaran";
        cout << endl;
        cout << "4. Chat dengan Wali Kelas/Guru (Stack)";
        cout << endl;
        cout << "5. Notifikasi Kegiatan Sekolah";
        cout << endl;
        cout << "0. Kembali ke Menu Utama";
        cout << endl;
        cout << "Pilih menu: ";
        if (!(cin >> pilih)) {
        clearInput();
        pilih = -1;
    }
        clearInput();

        if (pilih == 1) {
            lihatNilaiKehadiranAnak(nisAnak);
        } else if (pilih == 2) {
            int sub;
            do {
                clearScreen();
                cout << "\n--- JADWAL & TUGAS ANAK ---\n";
                cout << "1. Lihat Jadwal Pelajaran";
                cout << endl;
                cout << "2. Lihat Daftar Tugas (Linked List)";
                cout << endl;
                cout << "3. Cari Tugas (Keyword)"; // FITUR TAMBAHAN
                cout << endl;
                cout << "4. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> sub)) {    
                clearInput();    
                sub = -1;    
            }
                clearInput();

                if (sub == 1) {
                    clearScreen();
                    cout << "--- Jadwal Pelajaran Anak ---";
                    cout << endl;
                    jadwalPelajaran.tampil();
                    pauseProgram();
                } else if (sub == 2) {
                    clearScreen();
                    daftarTugasAnak.lihatTugas();
                    pauseProgram();
                } else if (sub == 3) { // FITUR TAMBAHAN: Cari Tugas
                    clearScreen();
                    string keyword;
                    cout << "Masukkan keyword pencarian (Nama Tugas/Mapel): ";
                    getline(cin, keyword);
                    daftarTugasAnak.cariTugas(keyword);
                    pauseProgram();
                }
            } while (sub != 4 && sub != -1);
        } else if (pilih == 3) {
            int sub;
            do {
                clearScreen();
                cout << "\n--- TAGIHAN & PEMBAYARAN ---\n";
                cout << "1. Lihat Tagihan";
                cout << endl;
                cout << "2. Bayar Tagihan";
                cout << endl;
                cout << "3. Lihat Total Tagihan Belum Bayar";
                cout << endl;
                cout << "4. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> sub)) {
                    clearInput();
                    sub = -1;
                }
                clearInput();

                if (sub == 1) {
                    clearScreen();
                    antrianTagihan.lihatTagihan();
                    pauseProgram();
                } else if (sub == 2) {
                    clearScreen();
                    string idTagihan;
                    cout << "Masukkan ID Tagihan yang dibayar: ";
                    getline(cin, idTagihan);
                    antrianTagihan.bayarTagihan(idTagihan);
                    pauseProgram();
                } else if (sub == 3) {
                    clearScreen();
                    double totalBelumBayar = antrianTagihan.hitungTotalTagihan();
                    cout << "Total Tagihan Belum Bayar: Rp "
                            << fixed << setprecision(0) << totalBelumBayar << "\n";
                    pauseProgram();
                }
            } while (sub != 4 && sub != -1);
        } else if (pilih == 4) {
            int sub;
            do {
                clearScreen();
                cout << "\n--- CHAT DENGAN GURU/WALI KELAS (Stack) ---\n";
                cout << "1. Lihat Pesan Terakhir";
                cout << endl;
                cout << "2. Lihat Riwayat Chat";
                cout << endl;
                cout << "3. Kirim Pesan Baru";
                cout << endl;
                cout << "4. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> sub)) {
                    clearInput();
                    sub = -1;
                }
                clearInput();

                if (sub == 1) {
                    clearScreen();
                    chatAnak.lihatPesanTerakhir();
                    pauseProgram();
                } else if (sub == 2) {
                    clearScreen();
                    chatAnak.lihatRiwayatPesan();
                    pauseProgram();
                } else if (sub == 3) {
                    clearScreen();
                    string pengirim, pesan, tanggal;
                    cout << "Nama Pengirim (Orang Tua): ";
                    getline(cin, pengirim);
                    cout << "Pesan: ";
                    getline(cin, pesan);
                    cout << "Tanggal (YYYY-MM-DD): ";
                    getline(cin, tanggal);
                    chatAnak.kirimPesan(pengirim, pesan, tanggal);
                    pauseProgram();
                }
            } while (sub != 4 && sub != -1);
        } else if (pilih == 5) {
            int sub;
            do {
                clearScreen();
                cout << "\n--- NOTIFIKASI KEGIATAN SEKOLAH    ---\n";
                cout << "1. Lihat Notifikasi Terakhir";
                cout << endl;
                cout << "2. Lihat Semua Notifikasi";
                cout << endl;
                cout << "3. Kembali";
                cout << endl;
                cout << "Pilih: ";
                if (!(cin >> sub)) {
                    clearInput();
                    sub = -1;
                }
                clearInput();

                if (sub == 1) {
                    clearScreen();
                    notifikasiSekolah.lihatNotifikasiTerbaru();
                    pauseProgram();
                } else if (sub == 2) {
                    clearScreen();
                    notifikasiSekolah.lihatNotifikasi();
                    pauseProgram();
                }
            } while (sub != 3 && sub != -1);
        }
    } while (pilih != 0);
}

// ================== FUNGSI TAMBAHAN: MANAJEMEN DATA KTP ==================
void menuManajemenKTP() {
    int p;
    do {
        clearScreen();
        cout << "\n=== MANAJEMEN DATA KTP ===\n";
        cout << "1. Tambah Data KTP\n";
        cout << "2. Tampilkan Data KTP (Array)\n";
        cout << "3. Tampilkan Data KTP (DLL)\n";
        cout << "4. Cari Data KTP berdasarkan NIK\n";
        cout << "5. Hapus Data KTP\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        if (!(cin >> p)) { clearInput(); p = -1; }
        clearInput();

        if (p == 1) {
            KTP k = inputKTP();
            ktpDatabase.insert(k);
            ktpDLL.insert(k);
            cout << "Data KTP berhasil ditambahkan!\n";
        } else if (p == 2) {
            ktpDatabase.display();
        } else if (p == 3) {
            ktpDLL.display();
        } else if (p == 4) {
            string nik;
            cout << "Masukkan NIK yang dicari: ";
            getline(cin, nik);
            
            KTP* ktpArray = ktpDatabase.findByNIK(nik);
            if (ktpArray) {
                cout << "\nData ditemukan di Array KTP:\n";
                cout << "NIK: " << ktpArray->nik << "\n";
                cout << "Nama: " << ktpArray->nama << "\n";
            } else {
                KTP* ktpDLLResult = ktpDLL.findByNIK(nik);
                if (ktpDLLResult) {
                    cout << "\nData ditemukan di DLL KTP:\n";
                    cout << "NIK: " << ktpDLLResult->nik << "\n";
                    cout << "Nama: " << ktpDLLResult->nama << "\n";
                } else {
                    cout << "Data KTP dengan NIK " << nik << " tidak ditemukan.\n";
                }
            }
        } else if (p == 5) {
            string nik;
            cout << "Masukkan NIK yang ingin dihapus: ";
            getline(cin, nik);
            ktpDatabase.removeByNIK(nik);
            ktpDLL.removeByNIK(nik);
        }
        if (p != 0) pauseProgram();
    } while (p != 0);
}

// ================== FUNGSI LOGIN DENGAN KTP ==================
bool loginWithKTPSystem(string &role, string &nis_nip) {
    KTP* ktp = loginWithKTP();
    if (ktp == nullptr) {
        cout << "NIK tidak ditemukan dalam sistem. Silakan daftar terlebih dahulu.\n";
        return false;
    }
    
    // Cari apakah NIK ini terdaftar sebagai siswa
    for (int i = 0; i < jumlahUser; ++i) {
        if (daftarUser[i].getNik() == ktp->nik) {
            role = daftarUser[i].getRole();
            nis_nip = daftarUser[i].getNis();
            cout << "\n=== LOGIN BERHASIL ===\n";
            cout << "Selamat datang, " << ktp->nama << "!\n";
            cout << "Role: " << role << "\n";
            return true;
        }
    }
    
    // Jika tidak ditemukan, tawarkan untuk mendaftar
    cout << "\nNIK ditemukan (" << ktp->nama << ") tetapi belum terdaftar di sistem sekolah.\n";
    cout << "Silakan hubungi admin untuk mendaftarkan Anda ke sistem.\n";
    return false;
}

// ================== MAIN PROGRAM & INITIALIZATION ==================

int main() {
    // Inisialisasi Akun Admin dan Kepala Sekolah
    daftarUser[0].setData("admin", "admin123", "admin", "", "");
    daftarUser[1].setData("kepala", "kepala123", "kepala", "", ""); // New role
    jumlahUser = 2;
    
    // Inisialisasi beberapa data Guru untuk DLL Senioritas
    daftarGuru[0].setData("G101", "Budi Santoso", "Matematika Peminatan", "2005");
    senioritasGuru.tambahGuru(daftarGuru[0]);
    daftarGuru[1].setData("G102", "Siti Aisyah", "Fisika", "2010");
    senioritasGuru.tambahGuru(daftarGuru[1]);
    daftarGuru[2].setData("G103", "Joko Susilo", "Kimia", "2020");
    senioritasGuru.tambahGuru(daftarGuru[2]);
    daftarGuru[3].setData("G104", "Dewi Kartika", "Biologi", "2015");
    senioritasGuru.tambahGuru(daftarGuru[3]);
    daftarGuru[4].setData("G105", "Kusuma Putri", "PAI", "2017");
    senioritasGuru.tambahGuru(daftarGuru[4]);
    daftarGuru[5].setData("G106", "Safina Eka", "Matematika Wajib", "2017");
    senioritasGuru.tambahGuru(daftarGuru[5]);
    daftarGuru[6].setData("G107", "Nabila Putri", "Sejarah", "2024");
    senioritasGuru.tambahGuru(daftarGuru[6]);
    daftarGuru[7].setData("G108", "Lathiifah Faatimah", "Seni Budaya", "2022");
    senioritasGuru.tambahGuru(daftarGuru[7]);
    daftarGuru[8].setData("G109", "Budi Setiawan", "Bahasa Arab", "2007");
    senioritasGuru.tambahGuru(daftarGuru[8]);
    daftarGuru[9].setData("G110", "Indriana Dewi", "Fisika", "2010");
    senioritasGuru.tambahGuru(daftarGuru[9]);
    daftarGuru[10].setData("G111", "Dinik", "Seni Budaya", "2010");
    senioritasGuru.tambahGuru(daftarGuru[10]);
    daftarGuru[11].setData("G112", "Amir Syarifudin", "Bahasa Indonesia", "2012");
    senioritasGuru.tambahGuru(daftarGuru[11]);
    daftarGuru[12].setData("G113", "Totok", "Ekonomi", "2022");
    senioritasGuru.tambahGuru(daftarGuru[12]);
    daftarGuru[13].setData("G114", "Syafiq Ahmad", "TIK", "2020");
    senioritasGuru.tambahGuru(daftarGuru[13]);
    daftarGuru[14].setData("G115", "Eko Wibowo", "Bahasa Inggris", "2011");
    senioritasGuru.tambahGuru(daftarGuru[14]);
    daftarGuru[15].setData("G116", "Tutik Sulis", "Bahasa Jerman", "2015");
    senioritasGuru.tambahGuru(daftarGuru[9]);
    daftarGuru[16].setData("G117", "Solistyo", "PPKN", "2006");
    senioritasGuru.tambahGuru(daftarGuru[16]);
    daftarGuru[17].setData("G118", "Irwansyah Putra", "Penjasorkes", "2010");
    senioritasGuru.tambahGuru(daftarGuru[17]);
    daftarGuru[18].setData("G119", "Hastiti", "Bimbingan Konseling", "2008");
    senioritasGuru.tambahGuru(daftarGuru[18]);
    daftarGuru[19].setData("G120", "Arwan Kusnandar", "Sosiologi", "2010");
    senioritasGuru.tambahGuru(daftarGuru[19]);
    jumlahGuru = 20;


    int pilih;
    do {
        cout << "\n========================================\n";
        cout << "      SISTEM MANAJEMEN SEKOLAH TERPADU\n";
        cout << "          (SMA N 2 YOGYAKARTA)\n";
        cout << "========================================\n";
        cout << "1. Login dengan Username/Password\n";
        cout << "2. Login dengan KTP (NIK)\n";
        cout << "3. Register (Siswa Baru)\n";
        cout << "4. Portal Orang Tua/Wali (Modul 4)\n";
        cout << "5. Manajemen Data KTP\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "Pilih menu: ";
        if (!(cin >> pilih)) {
            clearInput();
            pilih = -1;
        }
        clearInput();

        if (pilih == 1) {
            string u, p;
            cout << "--- LOGIN DENGAN USERNAME ---\n";
            cout << "Username: ";
            getline(cin, u);
            cout << "Password: ";
            getline(cin, p);

            bool loginSuccess = false;
            for(int i = 0; i < jumlahUser; ++i) {
                if(daftarUser[i].auth(u, p)) {
                    loginSuccess = true;
                    string role = daftarUser[i].getRole();
                    string nis = daftarUser[i].getNis();

                    cout << "Login berhasil! Selamat datang.";
                    cout << endl;
                    
                    pauseProgram();

                    if(role == "admin") {
                        mainMenuAdmin();
                    } else if (role == "siswa") {
                        mainMenuSiswa(nis);
                    } else if (role == "kepala") {
                        mainMenuKepalaSekolah();
                    }
                    break;
                }
            }
            if (!loginSuccess) {
                cout << "Login gagal. Username atau password salah.";
                cout << endl;
                pauseProgram();
            }
        } else if (pilih == 2) {
            string role, nis_nip;
            if (loginWithKTPSystem(role, nis_nip)) {
                pauseProgram();
                if(role == "admin") {
                    mainMenuAdmin();
                } else if (role == "siswa") {
                    mainMenuSiswa(nis_nip);
                } else if (role == "kepala") {
                    mainMenuKepalaSekolah();
                }
            } else {
                pauseProgram();
            }
        } else if (pilih == 3) {
            cout << "========================================\n";
            cout << "          PENDAFTARAN AKUN SISWA BARU\n";
            cout << "========================================\n";
            
            // Tanya apakah memiliki KTP
            char pilihan;
            cout << "Apakah Anda sudah memiliki data KTP di sistem? (y/n): ";
            cin >> pilihan;
            clearInput();
            
            if (pilihan == 'y' || pilihan == 'Y') {
                // Login dengan KTP terlebih dahulu
                string nik;
                cout << "Masukkan NIK dari KTP: ";
                getline(cin, nik);
                
                KTP* ktp = ktpDatabase.findByNIK(nik);
                if (ktp == nullptr) {
                    ktp = ktpDLL.findByNIK(nik);
                }
                
                if (ktp) {
                    cout << "\nData KTP ditemukan: " << ktp->nama << "\n";
                    // Lanjutkan pendaftaran dengan data KTP
                    prosesPendaftaranSiswa();
                    // Update NIK di data siswa
                    if (jumlahSiswa > 0) {
                        daftarSiswa[jumlahSiswa-1].setData(
                            daftarSiswa[jumlahSiswa-1].getId(),
                            daftarSiswa[jumlahSiswa-1].getNama(),
                            daftarSiswa[jumlahSiswa-1].getKelas(),
                            ktp->nik
                        );
                        // Update NIK di data user
                        if (jumlahUser > 0) {
                            daftarUser[jumlahUser-1].setData(
                                daftarUser[jumlahUser-1].getUser(),
                                daftarUser[jumlahUser-1].getPassword(),
                                daftarUser[jumlahUser-1].getRole(),
                                daftarUser[jumlahUser-1].getNis(),
                                ktp->nik
                            );
                        }
                        cout << "Data KTP telah ditautkan dengan akun siswa.\n";
                    }
                } else {
                    cout << "NIK tidak ditemukan. Silakan tambahkan data KTP terlebih dahulu.\n";
                }
            } else {
                prosesPendaftaranSiswa();
            }
            pauseProgram();
        } else if (pilih == 4) {
            menuOrangTuaWali();
        } else if (pilih == 5) {
            menuManajemenKTP();
        } else if (pilih == 0) {
            cout << "Keluar. Sampai jumpa.";
            cout << endl;
        } else {
            cout << "Pilihan tidak valid.";
            cout << endl;
            pauseProgram();
        }
    } while (pilih != 0);

    return 0;
}
