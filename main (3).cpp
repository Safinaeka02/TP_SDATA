#include "coba.h"

// ================== IMPLEMENTASI FUNGSI HELPER ==================

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

// ================== DATABASE GLOBAL (DEFINISI) ==================
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
    cout << "	NIS: " << dilayani.getNis()	
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
    cout << "	Akademik & SDM:\n";
    cout << "	Total Siswa Terdaftar: " << jumlahSiswa << " siswa";
    cout << endl;
    cout << "	Total Guru & Staf: 	 " << jumlahGuru << " orang";
    cout << endl;
    cout << "	Total Mata Pelajaran:	 " << jumlahMapel << " mapel";
    cout << endl;
    cout << "	Jadwal & Agenda:";
    cout << endl;
    cout << "	Slot Jadwal Terisi:	 " << jadwalPelajaran.countAssigned() << " slot";
    cout << endl;
    cout << "	Event Kalender Aktif:	 " << jumlahEvent << " event";
    cout << endl;
    cout << "	Keuangan & Administrasi:";
    cout << endl;
    cout << "	Total Pemasukan (Simulasi): Rp " << fixed << setprecision(0) << totalPemasukan();
    cout << endl;
    cout << "	Total Aset Inventaris: " << inventarisSekolah.totalBarang() << " barang";
    cout << endl;
    cout << "	Persetujuan Tertunda:	 " << manPersetujuan.getJumlahTertunda() << " item (Queue)";
    cout << endl;
    cout << "	Antrian Dokumen: 	 " << antrianDokumenSekolah.getCount() << " item (Queue Circular)"; // TAMBAHAN
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
        cout << "	 MODUL 5: PORTAL KEPALA SEKOLAH\n";
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
        cout << "	† SISTEM MANAJEMEN SEKOLAH (ADMIN)	† \n";
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

void mainMenuSiswa(const string &nis) {
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
        cout << "	† SELAMAT DATANG, " << namaSiswa << "\n";
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
    cout << "	 	 MODUL 4: PORTAL ORANG TUA / WALI\n";
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
        cout << "	PORTAL ORANG TUA - " << daftarSiswa[siAnak].getNama() << "\n";
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
                cout << "\n--- NOTIFIKASI KEGIATAN SEKOLAH	---\n";
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


// ================== MAIN PROGRAM & INITIALIZATION ==================

int main() {
    // Inisialisasi Akun Admin dan Kepala Sekolah
    daftarUser[0].setData("admin", "admin123", "admin", "");
    daftarUser[1].setData("kepala", "kepala123", "kepala", ""); // New role
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
    jumlahGuru = 17;


    int pilih;
    do {
        cout << "\n============================================================================\n";
        cout << "	 	 SISTEM MANAJEMEN SEKOLAH TERPADU\n";
        cout << "		 	 (SMP N 2 YOGYAKARTA)\n";
        cout << "===============================================================================\n";
        cout << "1. Login";
        cout << endl;
        cout << "2. Register (Siswa Baru)";
        cout << endl;
        cout << "3. Portal Orang Tua/Wali (Modul 4)";
        cout << endl;
        cout << "0. Keluar Aplikasi";
        cout << endl;
        cout << "Pilih menu: ";
        if (!(cin >> pilih)) {
            clearInput();
            pilih = -1;
        }
        clearInput();

        if (pilih == 1) {
            string u, p;
            cout << "--- LOGIN ---";
            cout << endl;
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
            cout << "========================================\n";
            cout << "	 	 PENDAFTARAN AKUN SISWA BARU\n";
            cout << "========================================\n";
            prosesPendaftaranSiswa();
            pauseProgram();
        } else if (pilih == 3) {
            menuOrangTuaWali();
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
