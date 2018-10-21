#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct {
    char maSinhVien[10];
    char ten[10];
    char soDienThoai[10];
} sinhVien;

void removeStdChar(char array[]) {
    if (strchr(array, '\n') == NULL) {
        while (fgetc(stdin) != '\n');
    }
}
void taoMenu() {
    printf("<--- Menu ---> \n");
    printf("1. Them moi sinh vien \n");
    printf("2. Hien thi danh sach sinh vien \n");
    printf("3. Luu danh sach sinh vien ra file \n");
    printf("4. Doc danh sach sinh vien tu file \n");
    printf("5. Ket thuc chuong trinh \n");
    printf("<---End Menu--->\n");
    printf("Nhap lua chon cua ban: ");
}
void themMoiSinhVien(sinhVien mangSinhVien[], int i) {
    do {
        printf("Moi ban nhap ma so sinh vien:\n");
        fgets(mangSinhVien[i].maSinhVien, sizeof(mangSinhVien[i].maSinhVien) * sizeof(char), stdin);
        removeStdChar(mangSinhVien[i].maSinhVien);

        mangSinhVien[i].maSinhVien[strlen(mangSinhVien[i].maSinhVien) - 1] = ' ';
        if (strlen(mangSinhVien[i].maSinhVien) != 6) {
            printf("Vui long nhap lai, ma so sinh vien phai co 05 ky tu\n");
        }
    }
    while (strlen(mangSinhVien[i].maSinhVien) != 6);
    printf("Nhap ten sinh vien:\n");
    fgets(mangSinhVien[i].ten, sizeof(mangSinhVien[i].ten) * sizeof(char), stdin);
    removeStdChar(mangSinhVien[i].ten);

    mangSinhVien[i].ten[strlen(mangSinhVien[i].ten) - 1] = ' ';
    printf("Nhap phone sinh vien:\n");
    fgets(mangSinhVien[i].soDienThoai, sizeof(mangSinhVien[i].soDienThoai) * sizeof(char), stdin);
    removeStdChar(mangSinhVien[i].soDienThoai);

    mangSinhVien[i].soDienThoai[strlen(mangSinhVien[i].soDienThoai) - 1] = ' ';
}
void hienThiDanhSachSinhVien(sinhVien mangSinhVien[], int i) {
    printf("\n|%-20s| %-20s| %-20s\n", "Ma So Sinh Vien", "Ten Sinh Vien", "So Dien Thoai");
    printf("\n%-20s %-20s %-20s\n", "_______________", "_______________", "____________________");
    for (int j = 0; j < i; j++) {
        printf("\n|%-20s| %-20s| %-20s\n", mangSinhVien[j].maSinhVien, mangSinhVien[j].ten, mangSinhVien[j].soDienThoai);
        printf("\n%-20s %-20s %-20s\n", "---------------", "---------------", "--------------------");
    }
}

void luuThongTin(FILE *fp, sinhVien mangSinhVien[], int i) {
    fprintf(fp, "\n%-20s|%-20s|%-20s\n", "Ma Sinh Vien", "Ten", "So Dien Thoai");
    for (int j = 0; j < i; j++) {
        fprintf(fp, "\n%-20s|%-20s|%-20s\n", mangSinhVien[j].maSinhVien, mangSinhVien[j].ten, mangSinhVien[j].soDienThoai);
    }
}

void docDanhSach(FILE *fp, char array[]) {
    while (fgets(array, 255, fp) != NULL) {
        printf("%s", array);
    }
}
int main() {
    int luachon;
    int soLuong = 0;
    sinhVien mangSinhVien[10];
    char danhsach[255];
    FILE *fp;
    while (1) {
        taoMenu();
        scanf("%d", &luachon);
        getchar();
        switch (luachon) {
            case 1:
                if (soLuong <= 10) {
                    themMoiSinhVien(mangSinhVien, soLuong);
                    soLuong++;
                } else {
                    printf("Full danh sach sinh vien \n");
                    break;
                }
                break;
            case 2:
                hienThiDanhSachSinhVien(mangSinhVien, soLuong);
                break;
            case 3:
                fp = fopen("danhsachsinhvien.txt", "w");
                if (fp != NULL) {
                    luuThongTin(fp, mangSinhVien, soLuong);
                    fclose(fp);
                }
                break;
            case 4:
                fp = fopen("danhsachsinhvien.txt", "r");
                docDanhSach(fp, danhsach);
                fclose(fp);
                break;
            case 5:
                return 0;
            default:
                printf("Ket thuc chuong trinh\n");
                break;
        }
    }
}