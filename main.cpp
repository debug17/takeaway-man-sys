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

// ��ҽṹ��
typedef struct {
    char shopname[50];
    char password[50];
    char address[100];
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
        printf("1. �鿴���е��\n");
        printf("2. �µ�\n");
        printf("3. �鿴����\n");
        printf("0. �˳���¼\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                printf("\n���е��:\n");
                for(int i = 0; i < shopCount; i++) {
                    printf("%d. %s - %s\n", i+1, shops[i].shopname, shops[i].address);
                }
                break;
            case 2: printf("�µ����ܴ�ʵ��\n"); break;
            case 3: printf("�鿴�������ܴ�ʵ��\n"); break;
            case 0: return;
            default: printf("��Чѡ��!\n");
        }
    }
}

// ��Ҳ˵�
void shopMenu(char* shopname) {
    int choice;
    while(1) {
        printf("\n====== ��Ҳ˵� (%s) ======\n", shopname);
        printf("1. ��Ӳ�Ʒ\n");
        printf("2. �鿴����\n");
        printf("3. �޸���Ϣ\n");
        printf("0. �˳���¼\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: printf("��Ӳ�Ʒ���ܴ�ʵ��\n"); break;
            case 2: printf("�鿴�������ܴ�ʵ��\n"); break;
            case 3: printf("�޸���Ϣ���ܴ�ʵ��\n"); break;
            case 0: return;
            default: printf("��Чѡ��!\n");
        }
    }
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
        fprintf(fp, "����,����,��ַ\n");
        for(int i = 0; i < shopCount; i++) {
            fprintf(fp, "%s,%s,%s\n", shops[i].shopname, shops[i].password, shops[i].address);
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
            if(token) strcpy(shops[shopCount].password, token);
            token = strtok(NULL, ",\n");
            if(token) {
                strcpy(shops[shopCount].address, token);
                shopCount++;
            }
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
