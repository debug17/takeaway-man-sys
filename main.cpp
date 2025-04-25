#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>   
#include <sys/stat.h>

// 用户结构体
typedef struct {
    char username[50];
    char password[50];
} User;

// 店家结构体
typedef struct {
    char shopname[50];
    char password[50];
    char address[100];
} Shop;

// 管理员结构体
typedef struct {
    char username[50];
    char password[50];
} Admin;

// 骑手结构体
typedef struct {
    char username[50];
    char password[50];
    int status; // 0-休息 1-接单中
} Rider;

// 全局变量
User users[100];
Shop shops[50];
Admin admin = {"admin", "admin123"};//管理员账号
int userCount = 0;
int shopCount = 0;
const char* USER_FILE = "./data/users.txt";  // Windows路径
const char* SHOP_FILE = "./data/shops.txt";  // Windows路径
Rider riders[50];
int riderCount = 0;
const char* RIDER_FILE = "./data/riders.txt";

// 函数声明
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
    createDataDirectory();  // 确保目录存在
    loadUsersFromTxt();     // 加载用户数据
    loadShopsFromTxt();     // 加载店家数据
    loadRidersFromTxt();  // 加载骑手数据
    roleMenu();
    return 0;
}

// 角色选择主菜单
void roleMenu() {
    int choice;
    while(1) {
        printf("\n====== 郑州轻工业大学校园外卖系统 ======\n");
        printf("请选择您的身份:\n");
        printf("1. 用户\n");
        printf("2. 商家\n");
        printf("3. 骑手\n");
        printf("4. 管理员\n");
        printf("0. 退出系统\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: userAuthMenu(); break;
            case 2: shopAuthMenu(); break;
            case 3: riderAuthMenu(); break;
            case 4: adminLogin(); break;
            case 0: exit(0);
            default: printf("无效选择! 请重新输入\n");
        }
    }
}

// 用户认证菜单
void userAuthMenu() {
    int choice;
    while(1) {
        printf("\n====== 用户操作 ======\n");
        printf("1. 用户登录\n");
        printf("2. 用户注册\n");
        printf("0. 返回上级\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: userLogin(); break;
            case 2: userRegister(); break;
            case 0: return;
            default: printf("无效选择! 请重新输入\n");
        }
    }
}

// 商家认证菜单
void shopAuthMenu() {
    int choice;
    while(1) {
        printf("\n====== 商家操作 ======\n");
        printf("1. 商家登录\n");
        printf("2. 商家注册\n");
        printf("0. 返回上级\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: shopLogin(); break;
            case 2: shopRegister(); break;
            case 0: return;
            default: printf("无效选择! 请重新输入\n");
        }
    }
}

// 骑手认证菜单
void riderAuthMenu() {
    int choice;
    while(1) {
        printf("\n====== 骑手操作 ======\n");
        printf("1. 骑手登录\n");
        printf("2. 骑手注册\n");
        printf("0. 返回上级\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: riderLogin(); break;
            case 2: riderRegister(); break;
            case 0: return;
            default: printf("无效选择! 请重新输入\n");
        }
    }
}


// 用户注册
void userRegister() {
    if(userCount >= 100) {
        printf("用户数量已达上限!\n");
        return;
    }
    
    printf("\n====== 用户注册 ======\n");
    printf("请输入用户名: ");
    scanf("%s", users[userCount].username);
    
    // 检查用户名是否已存在
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, users[userCount].username) == 0) {
            printf("用户名已存在!\n");
            return;
        }
    }
    
    printf("请输入密码: ");
    scanf("%s", users[userCount].password);
    
    userCount++;
    printf("注册成功!\n");
    saveUsersToTxt();
}

// 店家注册
void shopRegister() {
    if(shopCount >= 50) {
        printf("店家数量已达上限!\n");
        return;
    }
    
    printf("\n====== 店家注册 ======\n");
    printf("请输入店名: ");
    scanf("%s", shops[shopCount].shopname);
    
    // 检查店名是否已存在
    for(int i = 0; i < shopCount; i++) {
        if(strcmp(shops[i].shopname, shops[shopCount].shopname) == 0) {
            printf("店名已存在!\n");
            return;
        }
    }
    
    printf("请输入密码: ");
    scanf("%s", shops[shopCount].password);
    
    printf("请输入地址: ");
    scanf("%s", shops[shopCount].address);
    
    shopCount++;
    printf("注册成功!\n");
    saveShopsToTxt();
}

// 用户登录
void userLogin() {
    char username[50], password[50];
    
    printf("\n====== 用户登录 ======\n");
    printf("用户名: ");
    scanf("%s", username);
    printf("密码: ");
    scanf("%s", password);
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0 && 
           strcmp(users[i].password, password) == 0) {
            printf("登录成功!\n");
            userMenu(username);
            return;
        }
    }
    
    printf("用户名或密码错误!\n");
}

// 店家登录
void shopLogin() {
    char shopname[50], password[50];
    
    printf("\n====== 店家登录 ======\n");
    printf("店名: ");
    scanf("%s", shopname);
    printf("密码: ");
    scanf("%s", password);
    
    for(int i = 0; i < shopCount; i++) {
        if(strcmp(shops[i].shopname, shopname) == 0 && 
           strcmp(shops[i].password, password) == 0) {
            printf("登录成功!\n");
            shopMenu(shopname);
            return;
        }
    }
    
    printf("店名或密码错误!\n");
}

// 管理员登录
void adminLogin() {
    char username[50], password[50];
    
    printf("\n====== 管理员登录 ======\n");
    printf("用户名: ");
    scanf("%s", username);
    printf("密码: ");
    scanf("%s", password);
    
    if(strcmp(admin.username, username) == 0 && 
       strcmp(admin.password, password) == 0) {
        printf("登录成功!\n");
        adminMenu();
    } else {
        printf("用户名或密码错误!\n");
    }
}

// 用户菜单
void userMenu(char* username) {
    int choice;
    while(1) {
        printf("\n====== 用户菜单 (%s) ======\n", username);
        printf("1. 查看所有店家\n");
        printf("2. 下单\n");
        printf("3. 查看订单\n");
        printf("0. 退出登录\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                printf("\n所有店家:\n");
                for(int i = 0; i < shopCount; i++) {
                    printf("%d. %s - %s\n", i+1, shops[i].shopname, shops[i].address);
                }
                break;
            case 2: printf("下单功能待实现\n"); break;
            case 3: printf("查看订单功能待实现\n"); break;
            case 0: return;
            default: printf("无效选择!\n");
        }
    }
}

// 店家菜单
void shopMenu(char* shopname) {
    int choice;
    while(1) {
        printf("\n====== 店家菜单 (%s) ======\n", shopname);
        printf("1. 添加菜品\n");
        printf("2. 查看订单\n");
        printf("3. 修改信息\n");
        printf("0. 退出登录\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: printf("添加菜品功能待实现\n"); break;
            case 2: printf("查看订单功能待实现\n"); break;
            case 3: printf("修改信息功能待实现\n"); break;
            case 0: return;
            default: printf("无效选择!\n");
        }
    }
}

// 管理员菜单
void adminMenu() {
    int choice;
    while(1) {
        printf("\n====== 管理员菜单 ======\n");
        printf("1. 查看所有用户\n");
        printf("2. 查看所有店家\n");
        printf("3. 删除用户\n");
        printf("4. 删除店家\n");
        printf("0. 退出登录\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                printf("\n所有用户:\n");
                for(int i = 0; i < userCount; i++) {
                    printf("%d. %s\n", i+1, users[i].username);
                }
                break;
            case 2: 
                printf("\n所有店家:\n");
                for(int i = 0; i < shopCount; i++) {
                    printf("%d. %s - %s\n", i+1, shops[i].shopname, shops[i].address);
                }
                break;
            case 3: printf("删除用户功能待实现\n"); break;
            case 4: printf("删除店家功能待实现\n"); break;
            case 0: return;
            default: printf("无效选择!\n");
        }
    }
}
// ====== 新增的文件操作函数 ======
// 创建数据目录
void createDataDirectory() {
    #ifdef _WIN32
        _mkdir("./data");
    #else
        mkdir("./data", 0777);//非windows系统
    #endif
}//确保程序在不同系统的稳定运行

// 保存用户数据到TXT
void saveUsersToTxt() {
    FILE *fp = fopen("./data/users.txt", "w");
    if(fp) {
        fprintf(fp, "用户名,密码\n");
        for(int i = 0; i < userCount; i++) {
            fprintf(fp, "%s,%s\n", users[i].username, users[i].password);
        }
        fclose(fp);
    }
}

// 保存店家数据到TXT
void saveShopsToTxt() {
    FILE *fp = fopen("./data/shops.txt", "w");
    if(fp) {
        fprintf(fp, "店名,密码,地址\n");
        for(int i = 0; i < shopCount; i++) {
            fprintf(fp, "%s,%s,%s\n", shops[i].shopname, shops[i].password, shops[i].address);
        }
        fclose(fp);
    }
}

// 从TXT加载用户数据
void loadUsersFromTxt() {
    FILE *fp = fopen("./data/users.txt", "r");
    if(fp) {
        char line[256];
        fgets(line, sizeof(line), fp); // 跳过表头
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

// 从TXT加载店家数据
void loadShopsFromTxt() {
    FILE *fp = fopen("./data/shops.txt", "r");
    if(fp) {
        char line[256];
        fgets(line, sizeof(line), fp); // 跳过表头
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
// 骑手注册
void riderRegister() {
    if(riderCount >= 50) {
        printf("骑手数量已达上限!\n");
        return;
    }
    
    printf("\n====== 骑手注册 ======\n");
    printf("请输入用户名: ");
    scanf("%s", riders[riderCount].username);
    
    // 检查用户名是否已存在
    for(int i = 0; i < riderCount; i++) {
        if(strcmp(riders[i].username, riders[riderCount].username) == 0) {
            printf("用户名已存在!\n");
            return;
        }
    }
    
    printf("请输入密码: ");
    scanf("%s", riders[riderCount].password);
    
    riders[riderCount].status = 0; // 默认休息状态
    riderCount++;
    printf("注册成功!\n");
    saveRidersToTxt();
}

// 骑手登录
void riderLogin() {
    char username[50], password[50];
    
    printf("\n====== 骑手登录 ======\n");
    printf("用户名: ");
    scanf("%s", username);
    printf("密码: ");
    scanf("%s", password);
    
    for(int i = 0; i < riderCount; i++) {
        if(strcmp(riders[i].username, username) == 0 && 
           strcmp(riders[i].password, password) == 0) {
            printf("登录成功!\n");
            riderMenu(username);
            return;
        }
    }
    
    printf("用户名或密码错误!\n");
}

// 骑手菜单
void riderMenu(char* username) {
    int choice;
    while(1) {
        printf("\n====== 骑手菜单 (%s) ======\n", username);
        printf("1. 开始接单\n");
        printf("2. 结束接单\n");
        printf("3. 查看待接订单\n");
        printf("4. 接单\n");
        printf("5. 查看已接订单\n");
        printf("0. 退出登录\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                // 设置状态为接单中
                break;
            case 2: 
                // 设置状态为休息
                break;
            case 3: printf("查看待接订单功能待实现\n"); break;
            case 4: printf("接单功能待实现\n"); break;
            case 5: printf("查看已接订单功能待实现\n"); break;
            case 0: return;
            default: printf("无效选择!\n");
        }
    }
}

// 保存骑手数据到TXT
void saveRidersToTxt() {
    FILE *fp = fopen(RIDER_FILE, "w");
    if(fp) {
        fprintf(fp, "用户名,密码,状态\n");
        for(int i = 0; i < riderCount; i++) {
            fprintf(fp, "%s,%s,%d\n", riders[i].username, riders[i].password, riders[i].status);
        }
        fclose(fp);
    }
}

// 从TXT加载骑手数据
void loadRidersFromTxt() {
    FILE *fp = fopen(RIDER_FILE, "r");
    if(fp) {
        char line[256];
        fgets(line, sizeof(line), fp); // 跳过表头
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
