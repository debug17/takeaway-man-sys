#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>   
#include <sys/stat.h>

// �û��ṹ��
typedef struct {
    char username[50];
    char password[50];
} User;

// ��Ʒ�ṹ��
typedef struct {
    char name[50];
    float price;
    int isDeleted;//0-������1-��ɾ��
} Dish;

// ��ҽṹ��
typedef struct {
    char shopname[50];
    char password[50];
    char address[100];
    Dish dishes[100];
    int dishCount;
} Shop;

// ����Ա�ṹ��
typedef struct {
    char username[50];
    char password[50];
} Admin;

// ���ֽṹ��
typedef struct {
    char username[50];
    char password[50];
    int status; // 0-��Ϣ 1-�ӵ���
} Rider;

// ȫ�ֱ���
User users[100];
Shop shops[50];
Admin admin = {"admin", "admin123"};//����Ա�˺�
int userCount = 0;
int shopCount = 0;
const char* USER_FILE = "./data/users.txt";  // Windows·��
const char* SHOP_FILE = "./data/shops.txt";  // Windows·��
Rider riders[50];
int riderCount = 0;
const char* RIDER_FILE = "./data/riders.txt";

// ��������
void userRegister();
void shopRegister();
void userLogin();
void shopLogin();
void adminLogin();
void userMenu(char* username);
void shopMenu(char* shopname);
void adminMenu();
void saveUsersToTxt();
void saveShopsToTxt();
void loadUsersFromTxt();
void loadShopsFromTxt();
void createDataDirectory();
void riderRegister();
void riderLogin();
void riderMenu(char* username);
void saveRidersToTxt();
void loadRidersFromTxt();
void roleMenu();
void userAuthMenu();
void shopAuthMenu();
void riderAuthMenu();
void addDish(Shop *shop);
void deleteDish(Shop *shop);
void displayDishes(Shop *shop);
void viewShopsWithDishes();


int main() {
    createDataDirectory();  // ȷ��Ŀ¼����
    loadUsersFromTxt();     // �����û�����
    loadShopsFromTxt();     // ���ص������
    loadRidersFromTxt();  // ������������
    roleMenu();
    return 0;
}

// ��ɫѡ�����˵�
void roleMenu() {
    int choice;
    while(1) {
        printf("\n====== ֣���Ṥҵ��ѧУ԰����ϵͳ ======\n");
        printf("��ѡ���������:\n");
        printf("1. �û�\n");
        printf("2. �̼�\n");
        printf("3. ����\n");
        printf("4. ����Ա\n");
        printf("0. �˳�ϵͳ\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: userAuthMenu(); break;
            case 2: shopAuthMenu(); break;
            case 3: riderAuthMenu(); break;
            case 4: adminLogin(); break;
            case 0: exit(0);
            default: printf("��Чѡ��! ����������\n");
        }
    }
}

// �û���֤�˵�
void userAuthMenu() {
    int choice;
    while(1) {
        printf("\n====== �û����� ======\n");
        printf("1. �û���¼\n");
        printf("2. �û�ע��\n");
        printf("0. �����ϼ�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: userLogin(); break;
            case 2: userRegister(); break;
            case 0: return;
            default: printf("��Чѡ��! ����������\n");
        }
    }
}

// �̼���֤�˵�
void shopAuthMenu() {
    int choice;
    while(1) {
        printf("\n====== �̼Ҳ��� ======\n");
        printf("1. �̼ҵ�¼\n");
        printf("2. �̼�ע��\n");
        printf("0. �����ϼ�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: shopLogin(); break;
            case 2: shopRegister(); break;
            case 0: return;
            default: printf("��Чѡ��! ����������\n");
        }
    }
}

// ������֤�˵�
void riderAuthMenu() {
    int choice;
    while(1) {
        printf("\n====== ���ֲ��� ======\n");
        printf("1. ���ֵ�¼\n");
        printf("2. ����ע��\n");
        printf("0. �����ϼ�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: riderLogin(); break;
            case 2: riderRegister(); break;
            case 0: return;
            default: printf("��Чѡ��! ����������\n");
        }
    }
}


// �û�ע��
void userRegister() {
    if(userCount >= 100) {
        printf("�û������Ѵ�����!\n");
        return;
    }
    
    printf("\n====== �û�ע�� ======\n");
    printf("�������û���: ");
    scanf("%s", users[userCount].username);
    
    // ����û����Ƿ��Ѵ���
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, users[userCount].username) == 0) {
            printf("�û����Ѵ���!\n");
            return;
        }
    }
    
    printf("����������: ");
    scanf("%s", users[userCount].password);
    
    userCount++;
    printf("ע��ɹ�!\n");
    saveUsersToTxt();
}

// ���ע��
void shopRegister() {
    if(shopCount >= 50) {
        printf("��������Ѵ�����!\n");
        return;
    }
    
    printf("\n====== ���ע�� ======\n");
    printf("���������: ");
    scanf("%s", shops[shopCount].shopname);
    
    // �������Ƿ��Ѵ���
    for(int i = 0; i < shopCount; i++) {
        if(strcmp(shops[i].shopname, shops[shopCount].shopname) == 0) {
            printf("�����Ѵ���!\n");
            return;
        }
    }
    
    printf("����������: ");
    scanf("%s", shops[shopCount].password);
    
    printf("�������ַ: ");
    scanf("%s", shops[shopCount].address);
    shops[shopCount].dishCount = 0;
    shopCount++;
    printf("ע��ɹ�!\n");
    saveShopsToTxt();
}

// �û���¼
void userLogin() {
    char username[50], password[50];
    
    printf("\n====== �û���¼ ======\n");
    printf("�û���: ");
    scanf("%s", username);
    printf("����: ");
    scanf("%s", password);
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0 && 
           strcmp(users[i].password, password) == 0) {
            printf("��¼�ɹ�!\n");
            userMenu(username);
            return;
        }
    }
    
    printf("�û������������!\n");
}

// ��ҵ�¼
void shopLogin() {
    char shopname[50], password[50];
    
    printf("\n====== ��ҵ�¼ ======\n");
    printf("����: ");
    scanf("%s", shopname);
    printf("����: ");
    scanf("%s", password);
    
    for(int i = 0; i < shopCount; i++) {
        if(strcmp(shops[i].shopname, shopname) == 0 && 
           strcmp(shops[i].password, password) == 0) {
            printf("��¼�ɹ�!\n");
            shopMenu(shopname);
            return;
        }
    }
    
    printf("�������������!\n");
}

// ����Ա��¼
void adminLogin() {
    char username[50], password[50];
    
    printf("\n====== ����Ա��¼ ======\n");
    printf("�û���: ");
    scanf("%s", username);
    printf("����: ");
    scanf("%s", password);
    
    if(strcmp(admin.username, username) == 0 && 
       strcmp(admin.password, password) == 0) {
        printf("��¼�ɹ�!\n");
        adminMenu();
    } else {
        printf("�û������������!\n");
    }
}

// �û��˵�
void userMenu(char* username) {
    int choice;
    while(1) {
        printf("\n====== �û��˵� (%s) ======\n", username);
        printf("1. �鿴��Ҽ���Ʒ\n");  // �ϲ�ѡ��
        printf("2. �µ�\n");
        printf("3. �鿴����\n");
        printf("0. �˳���¼\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: viewShopsWithDishes(); break;  // �º���
            case 2: printf("�µ����ܴ�ʵ��\n"); break;
            case 3: printf("�鿴�������ܴ�ʵ��\n"); break;
            case 0: return;
            default: printf("��Чѡ��!\n");
        }
    }
}

// �鿴��Ҽ���Ʒ
void viewShopsWithDishes() {
    if(shopCount == 0) {
        printf("\n��ǰû����פ�̼ң�\n");
        return;
    }

    printf("\n====== �̼Ҽ���Ʒ�б� ======\n");
    for(int i = 0; i < shopCount; i++) {
        // ��ʾ�̼���Ϣ
        printf("\n%d. %s - %s\n", i+1, shops[i].shopname, shops[i].address);
        
        // ��ʾ���̼Ҳ�Ʒ
        if(shops[i].dishCount == 0) {
            printf("   (���޲�Ʒ)\n");
            continue;
        }

        int validDish = 0;
        for(int j = 0; j < shops[i].dishCount; j++) {
            if(!shops[i].dishes[j].isDeleted) {
                printf("   %d.%s %.2fԪ\n", 
                      ++validDish,
                      shops[i].dishes[j].name,
                      shops[i].dishes[j].price);
            }
        }
        if(validDish == 0) printf("   (������Ч��Ʒ)\n");
    }
    
    // ��Ӳ�����ʾ
    printf("\n��ʾ�����¼�����µ��ġ��̼ұ�š��͡���Ʒ��š�\n");
    printf("      �ں����µ�������ʹ����Щ���ѡ��\n");
}


// ��Ҳ˵�
void shopMenu(char* shopname) {
    Shop *currentShop = NULL;
    for(int i = 0; i < shopCount; i++) {
        if(strcmp(shops[i].shopname, shopname) == 0) {
            currentShop = &shops[i];
            break;
        }
    }
    if(!currentShop) {
        printf("�̼���Ϣ����\n");
        return;
    }

    int choice;
    while(1) {
        printf("\n====== �̼ҹ��� [%s] ======\n", shopname);
        printf("1. ��Ӳ�Ʒ\n");
        printf("2. ɾ����Ʒ\n");
        printf("3. �鿴��Ʒ\n");
        printf("0. �˳���¼\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addDish(currentShop); break;
            case 2: deleteDish(currentShop); break;
            case 3: displayDishes(currentShop); break;
            case 0: return;
            default: printf("��Чѡ��\n");
        }
    }
}


//��Ʒ��ʾ
void displayDishes(Shop *shop) {
    printf("\n====== ��ǰ��Ʒ�б� ======\n");
    int count = 0;
    for(int i = 0; i < shop->dishCount; i++) {
        if(!shop->dishes[i].isDeleted) {
            printf("%d. %-20s %.2fԪ\n", 
                  i+1, 
                  shop->dishes[i].name, 
                  shop->dishes[i].price);
            count++;
        }
    }
    if(count == 0) printf("������Ч��Ʒ\n");
}

//��Ʒɾ��
void deleteDish(Shop *shop) {
    if(shop->dishCount == 0) {
        printf("��ǰû�в�Ʒ��ɾ����\n");
        return;
    }

    displayDishes(shop);
    
    int choice;
    printf("\n������Ҫɾ���Ĳ�Ʒ���(0ȡ��): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > shop->dishCount) {
        printf("��Чѡ��\n");
        return;
    }

    int index = choice - 1;
    if(shop->dishes[index].isDeleted) {
        printf("�ò�Ʒ�ѱ�ɾ����\n");
        return;
    }

    shop->dishes[index].isDeleted = 1;
    printf("��Ʒ��%s����ɾ����\n", shop->dishes[index].name);
    saveShopsToTxt();
}

// ����Ա�˵�
void adminMenu() {
    int choice;
    while(1) {
        printf("\n====== ����Ա�˵� ======\n");
        printf("1. �鿴�����û�\n");
        printf("2. �鿴���е��\n");
        printf("3. ɾ���û�\n");
        printf("4. ɾ�����\n");
        printf("0. �˳���¼\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                printf("\n�����û�:\n");
                for(int i = 0; i < userCount; i++) {
                    printf("%d. %s\n", i+1, users[i].username);
                }
                break;
            case 2: 
                printf("\n���е��:\n");
                for(int i = 0; i < shopCount; i++) {
                    printf("%d. %s - %s\n", i+1, shops[i].shopname, shops[i].address);
                }
                break;
            case 3: printf("ɾ���û����ܴ�ʵ��\n"); break;
            case 4: printf("ɾ����ҹ��ܴ�ʵ��\n"); break;
            case 0: return;
            default: printf("��Чѡ��!\n");
        }
    }
}
// ====== �������ļ��������� ======
// ��������Ŀ¼
void createDataDirectory() {
    #ifdef _WIN32
        _mkdir("./data");
    #else
        mkdir("./data", 0777);//��windowsϵͳ
    #endif
}//ȷ�������ڲ�ͬϵͳ���ȶ�����

// �����û����ݵ�TXT
void saveUsersToTxt() {
    FILE *fp = fopen("./data/users.txt", "w");
    if(fp) {
        fprintf(fp, "�û���,����\n");
        for(int i = 0; i < userCount; i++) {
            fprintf(fp, "%s,%s\n", users[i].username, users[i].password);
        }
        fclose(fp);
    }
}

// ���������ݵ�TXT
void saveShopsToTxt() {
    FILE *fp = fopen("./data/shops.txt", "w");
    if(fp) {
        fprintf(fp, "����,����,��ַ,��Ʒ��\n");
        for(int i = 0; i < shopCount; i++) {
            fprintf(fp, "%s,%s,%s,%d\n",
                   shops[i].shopname,
                   shops[i].password,
                   shops[i].address,
                   shops[i].dishCount);
            
            // �����Ʒ�������ļ�
            char dishFile[100];
            sprintf(dishFile, "./data/dishes.txt", shops[i].shopname);
            FILE *dishFp = fopen(dishFile, "w");
            if(dishFp) {
                fprintf(dishFp, "��Ʒ��,�۸�,ɾ�����\n");
                for(int j = 0; j < shops[i].dishCount; j++) {
                    fprintf(dishFp, "%s,%.2f,%d\n",
                           shops[i].dishes[j].name,
                           shops[i].dishes[j].price,
                           shops[i].dishes[j].isDeleted);
                }
                fclose(dishFp);
            }
        }
        fclose(fp);
    }
}


// ��TXT�����û�����
void loadUsersFromTxt() {
    FILE *fp = fopen("./data/users.txt", "r");
    if(fp) {
        char line[256];
        fgets(line, sizeof(line), fp); // ������ͷ
        while(fgets(line, sizeof(line), fp)) {
            char *token = strtok(line, ",");
            strcpy(users[userCount].username, token);
            token = strtok(NULL, ",\n");
            if(token) {
                strcpy(users[userCount].password, token);
                userCount++;
            }
        }
        fclose(fp);
    }
}

// ��TXT���ص������
void loadShopsFromTxt() {
    FILE *fp = fopen("./data/shops.txt", "r");
    if(fp) {
        char line[256];
        fgets(line, sizeof(line), fp); // ������ͷ
        
        while(fgets(line, sizeof(line), fp)) {
            char *token = strtok(line, ",");
            strcpy(shops[shopCount].shopname, token);
            
            token = strtok(NULL, ",");
            strcpy(shops[shopCount].password, token);
            
            token = strtok(NULL, ",");
            strcpy(shops[shopCount].address, token);
            
            token = strtok(NULL, ",\n");
            shops[shopCount].dishCount = atoi(token);
            
            // ���ز�Ʒ����
            char dishFile[100];
            sprintf(dishFile, "./data/dishes.txt", shops[shopCount].shopname);
            FILE *dishFp = fopen(dishFile, "r");
            if(dishFp) {
                char dishLine[256];
                fgets(dishLine, sizeof(dishLine), dishFp); // ������ͷ
                
                for(int j = 0; j < shops[shopCount].dishCount; j++) {
                    if(fgets(dishLine, sizeof(dishLine), dishFp)) {
                        char *dishToken = strtok(dishLine, ",");
                        strcpy(shops[shopCount].dishes[j].name, dishToken);
                        
                        dishToken = strtok(NULL, ",");
                        shops[shopCount].dishes[j].price = atof(dishToken);
                        
                        dishToken = strtok(NULL, ",\n");
                        shops[shopCount].dishes[j].isDeleted = atoi(dishToken);
                    }
                }
                fclose(dishFp);
            }
            shopCount++;
        }
        fclose(fp);
    }
}

// ����ע��
void riderRegister() {
    if(riderCount >= 50) {
        printf("���������Ѵ�����!\n");
        return;
    }
    
    printf("\n====== ����ע�� ======\n");
    printf("�������û���: ");
    scanf("%s", riders[riderCount].username);
    
    // ����û����Ƿ��Ѵ���
    for(int i = 0; i < riderCount; i++) {
        if(strcmp(riders[i].username, riders[riderCount].username) == 0) {
            printf("�û����Ѵ���!\n");
            return;
        }
    }
    
    printf("����������: ");
    scanf("%s", riders[riderCount].password);
    
    riders[riderCount].status = 0; // Ĭ����Ϣ״̬
    riderCount++;
    printf("ע��ɹ�!\n");
    saveRidersToTxt();
}

// ���ֵ�¼
void riderLogin() {
    char username[50], password[50];
    
    printf("\n====== ���ֵ�¼ ======\n");
    printf("�û���: ");
    scanf("%s", username);
    printf("����: ");
    scanf("%s", password);
    
    for(int i = 0; i < riderCount; i++) {
        if(strcmp(riders[i].username, username) == 0 && 
           strcmp(riders[i].password, password) == 0) {
            printf("��¼�ɹ�!\n");
            riderMenu(username);
            return;
        }
    }
    
    printf("�û������������!\n");
}

// ���ֲ˵�
void riderMenu(char* username) {
    int choice;
    while(1) {
        printf("\n====== ���ֲ˵� (%s) ======\n", username);
        printf("1. ��ʼ�ӵ�\n");
        printf("2. �����ӵ�\n");
        printf("3. �鿴���Ӷ���\n");
        printf("4. �ӵ�\n");
        printf("5. �鿴�ѽӶ���\n");
        printf("0. �˳���¼\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                // ����״̬Ϊ�ӵ���
                break;
            case 2: 
                // ����״̬Ϊ��Ϣ
                break;
            case 3: printf("�鿴���Ӷ������ܴ�ʵ��\n"); break;
            case 4: printf("�ӵ����ܴ�ʵ��\n"); break;
            case 5: printf("�鿴�ѽӶ������ܴ�ʵ��\n"); break;
            case 0: return;
            default: printf("��Чѡ��!\n");
        }
    }
}

// �����������ݵ�TXT
void saveRidersToTxt() {
    FILE *fp = fopen(RIDER_FILE, "w");
    if(fp) {
        fprintf(fp, "�û���,����,״̬\n");
        for(int i = 0; i < riderCount; i++) {
            fprintf(fp, "%s,%s,%d\n", riders[i].username, riders[i].password, riders[i].status);
        }
        fclose(fp);
    }
}

// ��TXT������������
void loadRidersFromTxt() {
    FILE *fp = fopen(RIDER_FILE, "r");
    if(fp) {
        char line[256];
        fgets(line, sizeof(line), fp); // ������ͷ
        while(fgets(line, sizeof(line), fp)) {
            char *token = strtok(line, ",");
            strcpy(riders[riderCount].username, token);
            token = strtok(NULL, ",");
            if(token) strcpy(riders[riderCount].password, token);
            token = strtok(NULL, ",\n");
            if(token) {
                riders[riderCount].status = atoi(token);
                riderCount++;
            }
        }
        fclose(fp);
    }
}

// ��Ӳ�Ʒ
void addDish(Shop *shop) {
    if(shop->dishCount >= 100) {
        printf("��Ʒ�����Ѵ����ޣ�\n");
        return;
    }
    
    printf("\n====== ����²�Ʒ ======\n");
    printf("�������Ʒ����: ");
    scanf("%s", shop->dishes[shop->dishCount].name);
    
    printf("�������Ʒ�۸�: ");
    scanf("%f", &shop->dishes[shop->dishCount].price);
    
    shop->dishes[shop->dishCount].isDeleted = 0;
    shop->dishCount++;
    
    printf("��ӳɹ���\n");
    saveShopsToTxt();
}