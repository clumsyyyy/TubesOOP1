# MejaRajin: A MineCraft Crafting Table Implementation
> Program implementasi _crafting table_ berdasarkan game _Minecraft_ menggunakan bahasa C++ dan menerapkan konsep-konsep _Object-Oriented Programming_ (CLI/GUI)
> > Tugas Besar 1 IF2210 Pemrograman Berorientasi Objek
> > Semester II 2021/2022

## Deskripsi Singkat
MejaRajin adalah sebuah program berbasis _Command-Line Interface_ dan _Graphical User Interface_ untuk melakukan sistem _crafting_ sebagaimana sistem _crafting table_ bekerja dalam permainan populer _Minecraft_. Dengan menggunakan konsep-konsep _Object-Oriented Programming_, program ini dapat melakukan simulasi _crafting_.

## Requirements
- GNU C++ Compiler (GCC) **(disarankan v9.3.0)** pada **OS WSL2 / Linux**
- Make Compiler pada **WSL2 / Linux**

  > Gunakan perintah `sudo apt install gcc make` apabila kedua kebutuhan tersebut belum terpasang 
- _Visual Studio 2022_, dapat diunduh pada <a href = "https://visualstudio.microsoft.com/vs/community/"><b>tautan berikut</b></a>

## Cara Menggunakan
### Command-Line Interface
#### Melalui WSL
- Dari WSL, navigasi ke folder Lib dari root dengan perintah `cd Lib`
- Untuk melakukan _testing_ dengan file yang ada, jalankan perintah `make all`. _Testing_ akan berjalan dan hasil akhir akan ditampilkan
![image](https://user-images.githubusercontent.com/74661051/159971908-8bd0b668-09b4-429b-aefe-b67230c594db.png)
- Untuk melakukan penggunaan CLI, jalankan perintah `make run`. CLI akan terbuka dalam OS.
- Untuk membuka daftar perintah pada CLI, ketikkan perintah `HELP` dalam interface.
![image](https://user-images.githubusercontent.com/74661051/159972030-91c213d3-0620-4707-960d-58c56aa3b1b4.png)

#### Melalui Visual Studio
- Buka _Visual Studio_, Navigasikan ke folder dan buka file _solution_ `MinecraftCraftingTable.sln`
![image](https://user-images.githubusercontent.com/74661051/159973488-fe6fbe70-6101-4537-bae0-d11a27213aeb.png)

- Pada _Solution Explorer_, klik kanan pada **CLI** dan pilih _Select as Startup Project_. Pastikan tulisan **CLI** telah tercetak tebal.

![image](https://user-images.githubusercontent.com/74661051/159973620-1d598d07-9b76-468b-bd44-ab0866988c93.png)
- Jalankan _CLI_ dengan menekan tombol F5 atau menggunakan opsi _Local Windows Debugger_ pada _toolbar_ bagian atas.
![image](https://user-images.githubusercontent.com/71161031/159953110-ab476a8e-be15-4783-9a49-34496f5797ea.png)

### Graphical User Interface
#### Melalui Visual Studio
**[IMPORTANT]** Fitur ini harus diakses lewat Visual Studio!
- Buka _Visual Studio_, navigasikan ke folder dan buka file _solution_ `MinecraftCraftingTable.sln`
![image](https://user-images.githubusercontent.com/74661051/159973467-9cb0a872-a659-4f17-9dc4-afd2f4b8b9a8.png)
- Pada _Solution Explorer_, klik kanan pada **GUI** dan pilih _Select as Startup Project_. Pastikan tulisan **GUI** telah tercetak tebal.

![image](https://user-images.githubusercontent.com/71161031/159953407-36bb9941-0eff-4ad4-aac6-031089b7912c.png)
- Jalankan _GUI_ dengan menekan tombol F5 atau menggunakan opsi _Local Windows Debugger_ pada _toolbar_ bagian atas.
![image](https://user-images.githubusercontent.com/71161031/159953110-ab476a8e-be15-4783-9a49-34496f5797ea.png)

### Unit Testing (GoogleTest)
**[IMPORTANT]** Fitur ini harus diakses lewat Visual Studio!
- Buka _Visual Studio_, navigasikan ke folder dan buka file _solution_ `MinecraftCraftingTable.sln`
- Pada _Solution Explorer_, klik kanan pada **Lib.UnitTest** dan pilih _Select as Startup Project_. Pastikan tulisan **Lib.UnitTest** telah tercetak tebal.

![image](https://user-images.githubusercontent.com/71161031/159952730-c82b6d88-7185-4816-b1a6-3840dee21e84.png)
- Jalankan _unit tester_ dengan menekan tombol F5 atau menggunakan opsi _Local Windows Debugger_ pada _toolbar_ bagian atas.

![image](https://user-images.githubusercontent.com/71161031/159953110-ab476a8e-be15-4783-9a49-34496f5797ea.png)

## Anggota Kelompok
- Timothy Stanley Setiawan  - 13520028
- Andreas Indra Kurniawan   - 13520091
- Amar Fadil                - 13520103
- Owen Christian Wijaya     - 13520124
- Fachry Dennis Heraldi     - 13520139
- Thirafi Najwan Kurniatama - 13520157

