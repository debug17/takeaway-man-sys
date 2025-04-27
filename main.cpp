#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>   
#include <sys/stat.h>
#include <time.h>

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

// ������ṹ��
typedef struct {
    char dishName[50];
    float price;
    int quantity;
} OrderItem;

// �����ṹ��
typedef struct {
    char orderId[20];
    char username[50];
    char shopname[50];
    char rider[50];
    OrderItem items[10];
    int itemCount;
    float totalPrice;
    int status; // 0-���ӵ� 1-�ѽӵ� 2-������ 3-�����
    time_t orderTime;
} Order;

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
Order orders[100];
int orderCount = 0;
const char* ORDER_FILE = "./data/orders.txt";

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
void placeOrder(char* username);
void saveOrdersToTxt();
void loadOrdersFromTxt();
void viewUserOrders(char* username);
void viewPendingOrders();
void acceptOrder(char* ridername);
void viewAcceptedOrders(char* ridername);
void deliverOrder(char* ridername);
void completeOrder(char* ridername);


int main() {
    createDataDirectory();// ȷ��Ŀ¼����
    loadUsersFromTxt();// �����û�����
    loadShopsFromTxt();// ���ص������
    loadRidersFromTxt();// ������������
    loadOrdersFromTxt();// ���ض�������
    saveUsersToTxt();
    saveShopsToTxt();
    saveRidersToTxt();
    saveOrdersToTxt();
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
            case 2: placeOrder(username); break;
            case 3: viewUserOrders(username); break;
            case 0: return;
            default: printf("��Чѡ��!\n");
        }
    }
}

// �µ�����
void placeOrder(char* username) {
    if(shopCount == 0) {
        printf("��ǰû�п��µ����̼ң�\n");
        return;
    }
    
    // ��ʾ�̼��б�
    viewShopsWithDishes();
    
    int shopChoice;
    printf("\n��ѡ���̼ұ��(0ȡ��): ");
    scanf("%d", &shopChoice);
    
    if(shopChoice == 0) return;
    if(shopChoice < 1 || shopChoice > shopCount) {
        printf("��Ч���̼ұ�ţ�\n");
        return;
    }
    
    Shop *selectedShop = &shops[shopChoice-1];
    
    // ����̼��Ƿ�����Ч��Ʒ
    int validDishes = 0;
    for(int i = 0; i < selectedShop->dishCount; i++) {
        if(!selectedShop->dishes[i].isDeleted) {
            validDishes++;
        }
    }
    
    if(validDishes == 0) {
        printf("���̼�û����Ч��Ʒ��\n");
        return;
    }
    
    // �����¶���
    Order newOrder;
    strcpy(newOrder.username, username);
    strcpy(newOrder.shopname, selectedShop->shopname);
    newOrder.rider[0] = '\0'; // ��ʼ������
    newOrder.itemCount = 0;
    newOrder.totalPrice = 0;
    newOrder.status = 0; // ���ӵ�
    newOrder.orderTime = time(NULL);
    
    // ���ɶ���ID
    sprintf(newOrder.orderId, "ORD%04d", orderCount+1);
    
    int continueOrdering = 1;
    while(continueOrdering && newOrder.itemCount < 10) {
        // ��ʾ��Ʒ
        printf("\n%s�Ĳ˵�:\n", selectedShop->shopname);
        int dishIndex = 1;
        int validDishIndices[50] = {0};
        
        for(int i = 0; i < selectedShop->dishCount; i++) {
            if(!selectedShop->dishes[i].isDeleted) {
                printf("%d. %-20s %.2fԪ\n", 
                      dishIndex,
                      selectedShop->dishes[i].name,
                      selectedShop->dishes[i].price);
                validDishIndices[dishIndex-1] = i;
                dishIndex++;
            }
        }
        
        int dishChoice;
        printf("\n��ѡ���Ʒ���(0�����µ�): ");
        scanf("%d", &dishChoice);
        
        if(dishChoice == 0) {
            continueOrdering = 0;
        } else if(dishChoice < 1 || dishChoice >= dishIndex) {
            printf("��Ч�Ĳ�Ʒ��ţ�\n");
        } else {
            int actualDishIndex = validDishIndices[dishChoice-1];
            
            int quantity;
            printf("������%s�ķ���: ", selectedShop->dishes[actualDishIndex].name);
            scanf("%d", &quantity);
            
            if(quantity <= 0) {
                printf("�����������0��\n");
                continue;
            }
            
            // ��ӵ�����
            strcpy(newOrder.items[newOrder.itemCount].dishName, 
                  selectedShop->dishes[actualDishIndex].name);
            newOrder.items[newOrder.itemCount].price = 
                selectedShop->dishes[actualDishIndex].price;
            newOrder.items[newOrder.itemCount].quantity = quantity;
            
            newOrder.totalPrice += 
                selectedShop->dishes[actualDishIndex].price * quantity;
            newOrder.itemCount++;
        }
    }
    
    if(newOrder.itemCount > 0) {
        orders[orderCount++] = newOrder;
        saveOrdersToTxt();
        printf("\n�µ��ɹ���\n");
        printf("������: %s\n", newOrder.orderId);
        printf("�ܽ��: %.2fԪ\n", newOrder.totalPrice);
    } else {
        printf("������ȡ����û������κβ�Ʒ��\n");
    }
}

// �鿴�û�����
void viewUserOrders(char* username) {
    printf("\n====== �ҵĶ��� ======\n");
    
    int found = 0;
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].username, username) == 0) {
            found = 1;
            
            // ��ʽ��ʱ��
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M", 
                    localtime(&orders[i].orderTime));
            
            printf("\n������: %s\n", orders[i].orderId);
            printf("�̼�: %s\n", orders[i].shopname);
            printf("�µ�ʱ��: %s\n", timeStr);
            printf("״̬: ");
            switch(orders[i].status) {
                case 0: printf("���ӵ�"); break;
                case 1: printf("�ѽӵ�"); break;
                case 2: printf("������"); break;
                case 3: printf("�����"); break;
            }
            printf("\n����: %s\n", orders[i].rider[0] ? orders[i].rider : "����");
            
            printf("\n������ϸ:\n");
            for(int j = 0; j < orders[i].itemCount; j++) {
                printf("%d. %s x%d %.2fԪ\n", 
                      j+1,
                      orders[i].items[j].dishName,
                      orders[i].items[j].quantity,
                      orders[i].items[j].price * orders[i].items[j].quantity);
            }
            printf("�ܼ�: %.2fԪ\n", orders[i].totalPrice);
            printf("----------------------------\n");
        }
    }
    
    if(!found) {
        printf("����û���κζ�����¼��\n");
    }
}

// ���涩�����ļ�
void saveOrdersToTxt() {
    FILE *fp = fopen(ORDER_FILE, "w");
    if(fp) {
        fprintf(fp, "����ID,�û���,�̼�,����,�ܼ�,״̬,�µ�ʱ��,��������\n");
        for(int i = 0; i < orderCount; i++) {
            fprintf(fp, "%s,%s,%s,%s,%.2f,%d,%ld,%d\n",
                   orders[i].orderId,
                   orders[i].username,
                   orders[i].shopname,
                   orders[i].rider,
                   orders[i].totalPrice,
                   orders[i].status,
                   orders[i].orderTime,
                   orders[i].itemCount);
            
            // ���涩��������ļ�
            char itemFile[100];
            sprintf(itemFile, "./data/order_%s.txt", orders[i].orderId);
            FILE *itemFp = fopen(itemFile, "w");
            if(itemFp) {
                fprintf(itemFp, "��Ʒ��,�۸�,����\n");
                for(int j = 0; j < orders[i].itemCount; j++) {
                    fprintf(itemFp, "%s,%.2f,%d\n",
                           orders[i].items[j].dishName,
                           orders[i].items[j].price,
                           orders[i].items[j].quantity);
                }
                fclose(itemFp);
            }
        }
        fclose(fp);
    }
}

// ���ļ����ض���
void loadOrdersFromTxt() {
    FILE *fp = fopen(ORDER_FILE, "r");
    if(fp) {
        char line[256];
        fgets(line, sizeof(line), fp);
        
        while(fgets(line, sizeof(line), fp)) {
            char *token = strtok(line, ",");
            strcpy(orders[orderCount].orderId, token);
            
            token = strtok(NULL, ",");
            strcpy(orders[orderCount].username, token);
            
            token = strtok(NULL, ",");
            strcpy(orders[orderCount].shopname, token);
            
            token = strtok(NULL, ",");
            strcpy(orders[orderCount].rider, token);
            
            token = strtok(NULL, ",");
            orders[orderCount].totalPrice = atof(token);
            
            token = strtok(NULL, ",");
            orders[orderCount].status = atoi(token);
            
            token = strtok(NULL, ",");
            orders[orderCount].orderTime = atol(token);
            
            token = strtok(NULL, ",\n");
            orders[orderCount].itemCount = atoi(token);
            
            // ���ض�����
            char itemFile[100];
            sprintf(itemFile, "./data/order_%s.txt", orders[orderCount].orderId);
            FILE *itemFp = fopen(itemFile, "r");
            if(itemFp) {
                char itemLine[256];
                fgets(itemLine, sizeof(itemLine), itemFp);
                
                for(int j = 0; j < orders[orderCount].itemCount; j++) {
                    if(fgets(itemLine, sizeof(itemLine), itemFp)) {
                        char *itemToken = strtok(itemLine, ",");
                        strcpy(orders[orderCount].items[j].dishName, itemToken);
                        
                        itemToken = strtok(NULL, ",");
                        orders[orderCount].items[j].price = atof(itemToken);
                        
                        itemToken = strtok(NULL, ",\n");
                        orders[orderCount].items[j].quantity = atoi(itemToken);
                    }
                }
                fclose(itemFp);
            }
            orderCount++;
        }
        fclose(fp);
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
        //�����֤ȱʧ����
        char input[10];
        while(1) {
            printf("\n����0�����ϼ��˵�(�µ�Ҳ������0): ");
            
            // ��ȡ��������
            if(fgets(input, sizeof(input), stdin) == NULL) {
                printf("�������\n");
                continue;
            }
            
            // ת��Ϊ����
            int choice;
            if(sscanf(input, "%d", &choice) != 1) {
                printf("���������֣�\n");
                continue;
            }
            
            if(choice == 0) return;
            printf("��Чѡ��������0����\n");
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
    int riderIndex = -1;
    for(int i = 0; i < riderCount; i++) {
        if(strcmp(riders[i].username, username) == 0) {
            riderIndex = i;
            break;
        }
    }
    if(riderIndex == -1) {
        printf("������Ϣ����\n");
        return;
    }

    int choice;
    while(1) {
        printf("\n====== ���ֲ˵� (%s) ======\n", username);
        printf("��ǰ״̬: %s\n", riders[riderIndex].status ? "�ӵ���" : "��Ϣ��");
        printf("1. ��ʼ�ӵ�\n");
        printf("2. �����ӵ�\n");
        printf("3. �鿴���Ӷ���\n");
        printf("4. �ӵ�\n");
        printf("5. �鿴�ѽӶ���\n");
        printf("6. ���Ͷ���\n");
        printf("7. ��ɶ���\n");
        printf("0. �˳���¼\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                riders[riderIndex].status = 1;
                printf("������Ϊ�ӵ�״̬��\n");
                saveRidersToTxt();
                break;
            case 2: 
                riders[riderIndex].status = 0;
                printf("������Ϊ��Ϣ״̬��\n");
                saveRidersToTxt();
                break;
            case 3: viewPendingOrders(); break;
            case 4: acceptOrder(username); break;
            case 5: viewAcceptedOrders(username); break;
            case 6: deliverOrder(username); break;
            case 7: completeOrder(username); break;
            case 0: return;
            default: printf("��Чѡ��!\n");
        }
    }
}

// �鿴���Ӷ���
void viewPendingOrders() {
    printf("\n====== ���Ӷ��� ======\n");
    int found = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].status == 0 && strlen(orders[i].rider) == 0) { // ״̬Ϊ���ӵ�
            found = 1;
            
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M", 
                    localtime(&orders[i].orderTime));
            
            printf("\n������: %s\n", orders[i].orderId);
            printf("�̼�: %s\n", orders[i].shopname);
            printf("�û�: %s\n", orders[i].username);
            printf("�µ�ʱ��: %s\n", timeStr);
            printf("�ܽ��: %.2fԪ\n", orders[i].totalPrice);
            
            printf("\n������ϸ:\n");
            for(int j = 0; j < orders[i].itemCount; j++) {
                printf("%d. %s x%d %.2fԪ\n", 
                      j+1,
                      orders[i].items[j].dishName,
                      orders[i].items[j].quantity,
                      orders[i].items[j].price * orders[i].items[j].quantity);
            }
            printf("----------------------------\n");
        }
    }
    
    if(!found) {
        printf("��ǰû�д��Ӷ�����\n");
    }
}
// ���ֽӵ�
void acceptOrder(char* ridername) {
    if(orderCount == 0) {
        printf("��ǰû�пɽӵĶ�����\n");
        return;
    }
    
    // ��ʾ���Ӷ���
    printf("\n====== ���Ӷ��� ======\n");
    int pendingOrders[100] = {0};
    int pendingCount = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].status == 0) { // ״̬Ϊ���ӵ�
            printf("%d. ������: %s (%.2fԪ)\n", 
                  pendingCount+1, 
                  orders[i].orderId, 
                  orders[i].totalPrice);
            pendingOrders[pendingCount] = i;
            pendingCount++;
        }
    }
    
    if(pendingCount == 0) {
        printf("��ǰû�д��Ӷ�����\n");
        return;
    }
    
    int choice;
    printf("\n��ѡ��Ҫ�ӵĶ������(0ȡ��): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > pendingCount) {
        printf("��Ч�Ķ�����ţ�\n");
        return;
    }
    
    int orderIndex = pendingOrders[choice-1];
    
    // ��������Ƿ��ѽӵ�
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].status == 1 && strcmp(orders[i].rider, ridername) == 0) {
            printf("�������������͵Ķ�����������ɵ�ǰ������\n");
            return;
        }
    }
    
    // �ӵ�
    strcpy(orders[orderIndex].rider, ridername);
    orders[orderIndex].status = 1; // �ѽӵ�
    saveOrdersToTxt();
    
    printf("�ɹ��ӵ���������: %s\n", orders[orderIndex].orderId);
}

// �鿴�ѽӶ���
void viewAcceptedOrders(char* ridername) {
    printf("\n====== �ҵĶ��� ======\n");
    int found = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].rider, ridername) == 0 && 
           (orders[i].status == 1 || orders[i].status == 2)) {
            found = 1;
            
            // ��ʽ��ʱ��
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M", 
                    localtime(&orders[i].orderTime));
            
            printf("\n������: %s\n", orders[i].orderId);
            printf("�̼�: %s\n", orders[i].shopname);
            printf("�û�: %s\n", orders[i].username);
            printf("�µ�ʱ��: %s\n", timeStr);
            printf("״̬: %s\n", orders[i].status == 1 ? "�ѽӵ�" : "������");
            printf("�ܽ��: %.2fԪ\n", orders[i].totalPrice);
            
            printf("\n������ϸ:\n");
            for(int j = 0; j < orders[i].itemCount; j++) {
                printf("%d. %s x%d %.2fԪ\n", 
                      j+1,
                      orders[i].items[j].dishName,
                      orders[i].items[j].quantity,
                      orders[i].items[j].price * orders[i].items[j].quantity);
            }
            printf("----------------------------\n");
        }
    }
    
    if(!found) {
        printf("����ǰû���ѽӶ�����\n");
    }
}

// ���Ͷ���
void deliverOrder(char* ridername) {
    printf("\n====== ���Ͷ��� ======\n");
    int deliveringOrders[100] = {0};
    int deliveringCount = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].rider, ridername) == 0 && orders[i].status == 1) {
            printf("%d. ������: %s (%.2fԪ)\n", 
                  deliveringCount+1, 
                  orders[i].orderId, 
                  orders[i].totalPrice);
            deliveringOrders[deliveringCount] = i;
            deliveringCount++;
        }
    }
    
    if(deliveringCount == 0) {
        printf("����ǰû����Ҫ���͵Ķ�����\n");
        return;
    }
    
    int choice;
    printf("\n��ѡ��Ҫ��ʼ���͵Ķ������(0ȡ��): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > deliveringCount) {
        printf("��Ч�Ķ�����ţ�\n");
        return;
    }
    
    int orderIndex = deliveringOrders[choice-1];
    orders[orderIndex].status = 2; // ������
    saveOrdersToTxt();
    
    printf("���� %s �ѿ�ʼ���ͣ�\n", orders[orderIndex].orderId);
}

// ��ɶ���
void completeOrder(char* ridername) {
    printf("\n====== ��ɶ��� ======\n");
    int deliveringOrders[100] = {0};
    int deliveringCount = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].rider, ridername) == 0 && orders[i].status == 2) {
            printf("%d. ������: %s (%.2fԪ)\n", 
                  deliveringCount+1, 
                  orders[i].orderId, 
                  orders[i].totalPrice);
            deliveringOrders[deliveringCount] = i;
            deliveringCount++;
        }
    }
    
    if(deliveringCount == 0) {
        printf("����ǰû���������͵Ķ�����\n");
        return;
    }
    
    int choice;
    printf("\n��ѡ��Ҫ��ɵĶ������(0ȡ��): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > deliveringCount) {
        printf("��Ч�Ķ�����ţ�\n");
        return;
    }
    
    int orderIndex = deliveringOrders[choice-1];
    orders[orderIndex].status = 3; // �����
    saveOrdersToTxt();
    
    printf("���� %s ��������ͣ�\n", orders[orderIndex].orderId);
}

// �����������ݵ�TXT
void saveRidersToTxt() {
    FILE *fp = fopen(RIDER_FILE, "w");
    if(fp) {
        fprintf(fp, "�û���,����,״̬\n");
        for(int i = 0; i < riderCount; i++) {
            fprintf(fp, "%s,%s,%d\n", 
                   riders[i].username, 
                   riders[i].password,
                   riders[i].status);
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
            strcpy(riders[riderCount].password, token);
            
            token = strtok(NULL, ",\n");
            riders[riderCount].status = atoi(token);
            
            riderCount++;
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