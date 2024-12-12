Alur algoritma dari game Tic-Tac-Toe di atas adalah sebagai berikut:

1. Inisialisasi:

Array square[10] berfungsi untuk menyimpan status posisi dalam papan permainan (angka untuk posisi yang kosong dan 'X' atau 'O' untuk pemain yang sudah menempati posisi tersebut).

Variabel mode digunakan untuk memilih antara mode pemain vs pemain atau pemain vs komputer.



2. Memulai Permainan:

Program meminta pemain memilih mode permainan (Player vs Player atau Player vs Computer).

Setelah memilih mode, papan permainan direset, dengan setiap posisi memiliki angka dari '1' hingga '9'.



3. Gameplay:

Dalam permainan, pemain bergantian mengambil giliran untuk memilih posisi yang ingin mereka tandai (X atau O).

Pemain 1 selalu menggunakan simbol 'X', dan pemain 2 menggunakan simbol 'O'.

Jika mode adalah Player vs Player, pemain 1 dan pemain 2 bergiliran memasukkan pilihan mereka melalui input angka (1 hingga 9).

Jika mode adalah Player vs Computer, pemain 1 mengendalikan X, sementara pemain 2 (komputer) memilih langkah dengan algoritma Minimax.



4. Algoritma Minimax:

Minimax adalah algoritma rekursif yang digunakan untuk menentukan langkah terbaik bagi komputer (pemain 2).

Pada setiap langkah, Minimax menghitung kemungkinan langkah berdasarkan dua skenario:

Maximizing player (komputer) berusaha memaksimalkan nilainya (mencari langkah terbaik untuk menang).

Minimizing player (pemain) berusaha meminimalkan nilai komputer (untuk mencegah komputer menang).


Nilai dikembalikan untuk menentukan seberapa menguntungkan langkah tersebut, dengan komputer memilih langkah yang memberikan nilai maksimal.



5. Validasi Langkah:

Fungsi isMoveValid() digunakan untuk memeriksa apakah langkah yang dipilih valid (angka yang dipilih harus berada antara 1 dan 9 dan belum ditempati oleh simbol X atau O).



6. Pemeriksaan Kemenangan:

Fungsi checkwin() memeriksa apakah ada pemenang setelah setiap langkah:

Pemenang ditentukan berdasarkan garis horizontal, vertikal, atau diagonal yang terisi oleh simbol yang sama ('X' atau 'O').

Jika seluruh papan terisi tanpa ada pemenang, permainan berakhir seri.




7. Pencetakan Papan:

Fungsi board() digunakan untuk mencetak papan permainan di setiap langkah sehingga pemain dapat melihat status permainan.



8. Pengulangan Permainan:

Setelah permainan berakhir (baik ada pemenang atau seri), program menanyakan apakah pemain ingin bermain lagi. Jika ya, permainan dimulai dari awal.



9. Selesai:

Jika pemain memilih untuk berhenti, program akan menampilkan pesan terima kasih dan keluar.




Detail Alur:

Giliran Pemain:

Pemain dan komputer (jika ada) bergantian memilih posisi berdasarkan giliran mereka.

Pada setiap langkah, pemain atau komputer memilih angka, dan jika langkah tersebut valid, simbol (X atau O) ditambahkan pada posisi yang dipilih.


Komputer (Minimax):

Jika giliran komputer, algoritma Minimax digunakan untuk mengevaluasi langkah-langkah yang mungkin dilakukan.

Komputer memilih langkah terbaik berdasarkan evaluasi dari Minimax untuk memaksimalkan peluang menang atau mencegah kekalahan.



Penanganan Kekalahan dan Seri:

Jika ada pemenang, program akan mencetak nama pemain yang menang.

Jika tidak ada pemenang dan papan sudah penuh, permainan berakhir dengan hasil seri.


Program ini mengulang langkah-langkah di atas sampai pemain memilih untuk berhenti bermain.

