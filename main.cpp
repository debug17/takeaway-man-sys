#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>   
#include <sys/stat.h>
#include <time.h>

// 用户结构体
typedef struct {
    char username[50];
    char password[50];
} User;

// 菜品结构体
typedef struct {
    char name[50];
    float price;
    int isDeleted;//0-正常，1-已删除
} Dish;

// 店家结构体
typedef struct {
    char shopname[50];
    char password[50];
    char address[100];
    Dish dishes[100];
    int dishCount;
} Shop;

// 管理员结构体
typedef struct {
    char username[50];
    char password[50];
} Admin;

// 订单项结构体
typedef struct {
    char dishName[50];
    float price;
    int quantity;
} OrderItem;

// 订单结构体
typedef struct {
    char orderId[20];
    char username[50];
    char shopname[50];
    char rider[50];
    OrderItem items[10];
    int itemCount;
    float totalPrice;
    int status; // 0-待接单 1-已接单 2-配送中 3-已完成
    time_t orderTime;
} Order;

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
Order orders[100];
int orderCount = 0;
const char* ORDER_FILE = "./data/orders.txt";

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
    createDataDirectory();// 确保目录存在
    loadUsersFromTxt();// 加载用户数据
    loadShopsFromTxt();// 加载店家数据
    loadRidersFromTxt();// 加载骑手数据
    loadOrdersFromTxt();// 加载订单数据
    saveUsersToTxt();
    saveShopsToTxt();
    saveRidersToTxt();
    saveOrdersToTxt();
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
    shops[shopCount].dishCount = 0;
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
        printf("1. 查看店家及菜品\n");  // 合并选项
        printf("2. 下单\n");
        printf("3. 查看订单\n");
        printf("0. 退出登录\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: viewShopsWithDishes(); break;  // 新函数
            case 2: placeOrder(username); break;
            case 3: viewUserOrders(username); break;
            case 0: return;
            default: printf("无效选择!\n");
        }
    }
}

// 下单功能
void placeOrder(char* username) {
    if(shopCount == 0) {
        printf("当前没有可下单的商家！\n");
        return;
    }
    
    // 显示商家列表
    viewShopsWithDishes();
    
    int shopChoice;
    printf("\n请选择商家编号(0取消): ");
    scanf("%d", &shopChoice);
    
    if(shopChoice == 0) return;
    if(shopChoice < 1 || shopChoice > shopCount) {
        printf("无效的商家编号！\n");
        return;
    }
    
    Shop *selectedShop = &shops[shopChoice-1];
    
    // 检查商家是否有有效菜品
    int validDishes = 0;
    for(int i = 0; i < selectedShop->dishCount; i++) {
        if(!selectedShop->dishes[i].isDeleted) {
            validDishes++;
        }
    }
    
    if(validDishes == 0) {
        printf("该商家没有有效菜品！\n");
        return;
    }
    
    // 创建新订单
    Order newOrder;
    strcpy(newOrder.username, username);
    strcpy(newOrder.shopname, selectedShop->shopname);
    newOrder.rider[0] = '\0'; // 初始无骑手
    newOrder.itemCount = 0;
    newOrder.totalPrice = 0;
    newOrder.status = 0; // 待接单
    newOrder.orderTime = time(NULL);
    
    // 生成订单ID
    sprintf(newOrder.orderId, "ORD%04d", orderCount+1);
    
    int continueOrdering = 1;
    while(continueOrdering && newOrder.itemCount < 10) {
        // 显示菜品
        printf("\n%s的菜单:\n", selectedShop->shopname);
        int dishIndex = 1;
        int validDishIndices[50] = {0};
        
        for(int i = 0; i < selectedShop->dishCount; i++) {
            if(!selectedShop->dishes[i].isDeleted) {
                printf("%d. %-20s %.2f元\n", 
                      dishIndex,
                      selectedShop->dishes[i].name,
                      selectedShop->dishes[i].price);
                validDishIndices[dishIndex-1] = i;
                dishIndex++;
            }
        }
        
        int dishChoice;
        printf("\n请选择菜品编号(0结束下单): ");
        scanf("%d", &dishChoice);
        
        if(dishChoice == 0) {
            continueOrdering = 0;
        } else if(dishChoice < 1 || dishChoice >= dishIndex) {
            printf("无效的菜品编号！\n");
        } else {
            int actualDishIndex = validDishIndices[dishChoice-1];
            
            int quantity;
            printf("请输入%s的份数: ", selectedShop->dishes[actualDishIndex].name);
            scanf("%d", &quantity);
            
            if(quantity <= 0) {
                printf("份数必须大于0！\n");
                continue;
            }
            
            // 添加到订单
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
        printf("\n下单成功！\n");
        printf("订单号: %s\n", newOrder.orderId);
        printf("总金额: %.2f元\n", newOrder.totalPrice);
    } else {
        printf("订单已取消，没有添加任何菜品。\n");
    }
}

// 查看用户订单
void viewUserOrders(char* username) {
    printf("\n====== 我的订单 ======\n");
    
    int found = 0;
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].username, username) == 0) {
            found = 1;
            
            // 格式化时间
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M", 
                    localtime(&orders[i].orderTime));
            
            printf("\n订单号: %s\n", orders[i].orderId);
            printf("商家: %s\n", orders[i].shopname);
            printf("下单时间: %s\n", timeStr);
            printf("状态: ");
            switch(orders[i].status) {
                case 0: printf("待接单"); break;
                case 1: printf("已接单"); break;
                case 2: printf("配送中"); break;
                case 3: printf("已完成"); break;
            }
            printf("\n骑手: %s\n", orders[i].rider[0] ? orders[i].rider : "暂无");
            
            printf("\n订单明细:\n");
            for(int j = 0; j < orders[i].itemCount; j++) {
                printf("%d. %s x%d %.2f元\n", 
                      j+1,
                      orders[i].items[j].dishName,
                      orders[i].items[j].quantity,
                      orders[i].items[j].price * orders[i].items[j].quantity);
            }
            printf("总计: %.2f元\n", orders[i].totalPrice);
            printf("----------------------------\n");
        }
    }
    
    if(!found) {
        printf("您还没有任何订单记录。\n");
    }
}

// 保存订单到文件
void saveOrdersToTxt() {
    FILE *fp = fopen(ORDER_FILE, "w");
    if(fp) {
        fprintf(fp, "订单ID,用户名,商家,骑手,总价,状态,下单时间,订单项数\n");
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
            
            // 保存订单项到单独文件
            char itemFile[100];
            sprintf(itemFile, "./data/order_%s.txt", orders[i].orderId);
            FILE *itemFp = fopen(itemFile, "w");
            if(itemFp) {
                fprintf(itemFp, "菜品名,价格,数量\n");
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

// 从文件加载订单
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
            
            // 加载订单项
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

// 查看店家及菜品
void viewShopsWithDishes() {
    if(shopCount == 0) {
        printf("\n当前没有入驻商家！\n");
        return;
    }

    printf("\n====== 商家及菜品列表 ======\n");
    for(int i = 0; i < shopCount; i++) {
        // 显示商家信息
        printf("\n%d. %s - %s\n", i+1, shops[i].shopname, shops[i].address);
        
        // 显示该商家菜品
        if(shops[i].dishCount == 0) {
            printf("   (暂无菜品)\n");
            continue;
        }
        //解决验证缺失问题
        char input[10];
        while(1) {
            printf("\n输入0返回上级菜单(下单也先输入0): ");
            
            // 获取整行输入
            if(fgets(input, sizeof(input), stdin) == NULL) {
                printf("输入错误！\n");
                continue;
            }
            
            // 转换为数字
            int choice;
            if(sscanf(input, "%d", &choice) != 1) {
                printf("请输入数字！\n");
                continue;
            }
            
            if(choice == 0) return;
            printf("无效选择！请输入0返回\n");
        }
        
        int validDish = 0;
        for(int j = 0; j < shops[i].dishCount; j++) {
            if(!shops[i].dishes[j].isDeleted) {
                printf("   %d.%s %.2f元\n", 
                      ++validDish,
                      shops[i].dishes[j].name,
                      shops[i].dishes[j].price);
            }
        }
        if(validDish == 0) printf("   (暂无有效菜品)\n");
    }
    
}


// 店家菜单
void shopMenu(char* shopname) {
    Shop *currentShop = NULL;
    for(int i = 0; i < shopCount; i++) {
        if(strcmp(shops[i].shopname, shopname) == 0) {
            currentShop = &shops[i];
            break;
        }
    }
    if(!currentShop) {
        printf("商家信息错误！\n");
        return;
    }

    int choice;
    while(1) {
        printf("\n====== 商家管理 [%s] ======\n", shopname);
        printf("1. 添加菜品\n");
        printf("2. 删除菜品\n");
        printf("3. 查看菜品\n");
        printf("0. 退出登录\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addDish(currentShop); break;
            case 2: deleteDish(currentShop); break;
            case 3: displayDishes(currentShop); break;
            case 0: return;
            default: printf("无效选择！\n");
        }
    }
}


//菜品显示
void displayDishes(Shop *shop) {
    printf("\n====== 当前菜品列表 ======\n");
    int count = 0;
    for(int i = 0; i < shop->dishCount; i++) {
        if(!shop->dishes[i].isDeleted) {
            printf("%d. %-20s %.2f元\n", 
                  i+1, 
                  shop->dishes[i].name, 
                  shop->dishes[i].price);
            count++;
        }
    }
    if(count == 0) printf("暂无有效菜品\n");
}

//菜品删除
void deleteDish(Shop *shop) {
    if(shop->dishCount == 0) {
        printf("当前没有菜品可删除！\n");
        return;
    }

    displayDishes(shop);
    
    int choice;
    printf("\n请输入要删除的菜品编号(0取消): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > shop->dishCount) {
        printf("无效选择！\n");
        return;
    }

    int index = choice - 1;
    if(shop->dishes[index].isDeleted) {
        printf("该菜品已被删除！\n");
        return;
    }

    shop->dishes[index].isDeleted = 1;
    printf("菜品【%s】已删除！\n", shop->dishes[index].name);
    saveShopsToTxt();
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
        fprintf(fp, "店名,密码,地址,菜品数\n");
        for(int i = 0; i < shopCount; i++) {
            fprintf(fp, "%s,%s,%s,%d\n",
                   shops[i].shopname,
                   shops[i].password,
                   shops[i].address,
                   shops[i].dishCount);
            
            // 保存菜品到单独文件
            char dishFile[100];
            sprintf(dishFile, "./data/dishes.txt", shops[i].shopname);
            FILE *dishFp = fopen(dishFile, "w");
            if(dishFp) {
                fprintf(dishFp, "菜品名,价格,删除标记\n");
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
            strcpy(shops[shopCount].password, token);
            
            token = strtok(NULL, ",");
            strcpy(shops[shopCount].address, token);
            
            token = strtok(NULL, ",\n");
            shops[shopCount].dishCount = atoi(token);
            
            // 加载菜品数据
            char dishFile[100];
            sprintf(dishFile, "./data/dishes.txt", shops[shopCount].shopname);
            FILE *dishFp = fopen(dishFile, "r");
            if(dishFp) {
                char dishLine[256];
                fgets(dishLine, sizeof(dishLine), dishFp); // 跳过表头
                
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
    int riderIndex = -1;
    for(int i = 0; i < riderCount; i++) {
        if(strcmp(riders[i].username, username) == 0) {
            riderIndex = i;
            break;
        }
    }
    if(riderIndex == -1) {
        printf("骑手信息错误！\n");
        return;
    }

    int choice;
    while(1) {
        printf("\n====== 骑手菜单 (%s) ======\n", username);
        printf("当前状态: %s\n", riders[riderIndex].status ? "接单中" : "休息中");
        printf("1. 开始接单\n");
        printf("2. 结束接单\n");
        printf("3. 查看待接订单\n");
        printf("4. 接单\n");
        printf("5. 查看已接订单\n");
        printf("6. 配送订单\n");
        printf("7. 完成订单\n");
        printf("0. 退出登录\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                riders[riderIndex].status = 1;
                printf("已设置为接单状态！\n");
                saveRidersToTxt();
                break;
            case 2: 
                riders[riderIndex].status = 0;
                printf("已设置为休息状态！\n");
                saveRidersToTxt();
                break;
            case 3: viewPendingOrders(); break;
            case 4: acceptOrder(username); break;
            case 5: viewAcceptedOrders(username); break;
            case 6: deliverOrder(username); break;
            case 7: completeOrder(username); break;
            case 0: return;
            default: printf("无效选择!\n");
        }
    }
}

// 查看待接订单
void viewPendingOrders() {
    printf("\n====== 待接订单 ======\n");
    int found = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].status == 0 && strlen(orders[i].rider) == 0) { // 状态为待接单
            found = 1;
            
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M", 
                    localtime(&orders[i].orderTime));
            
            printf("\n订单号: %s\n", orders[i].orderId);
            printf("商家: %s\n", orders[i].shopname);
            printf("用户: %s\n", orders[i].username);
            printf("下单时间: %s\n", timeStr);
            printf("总金额: %.2f元\n", orders[i].totalPrice);
            
            printf("\n订单明细:\n");
            for(int j = 0; j < orders[i].itemCount; j++) {
                printf("%d. %s x%d %.2f元\n", 
                      j+1,
                      orders[i].items[j].dishName,
                      orders[i].items[j].quantity,
                      orders[i].items[j].price * orders[i].items[j].quantity);
            }
            printf("----------------------------\n");
        }
    }
    
    if(!found) {
        printf("当前没有待接订单。\n");
    }
}
// 骑手接单
void acceptOrder(char* ridername) {
    if(orderCount == 0) {
        printf("当前没有可接的订单！\n");
        return;
    }
    
    // 显示待接订单
    printf("\n====== 待接订单 ======\n");
    int pendingOrders[100] = {0};
    int pendingCount = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].status == 0) { // 状态为待接单
            printf("%d. 订单号: %s (%.2f元)\n", 
                  pendingCount+1, 
                  orders[i].orderId, 
                  orders[i].totalPrice);
            pendingOrders[pendingCount] = i;
            pendingCount++;
        }
    }
    
    if(pendingCount == 0) {
        printf("当前没有待接订单。\n");
        return;
    }
    
    int choice;
    printf("\n请选择要接的订单编号(0取消): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > pendingCount) {
        printf("无效的订单编号！\n");
        return;
    }
    
    int orderIndex = pendingOrders[choice-1];
    
    // 检查骑手是否已接单
    for(int i = 0; i < orderCount; i++) {
        if(orders[i].status == 1 && strcmp(orders[i].rider, ridername) == 0) {
            printf("您已有正在配送的订单，请先完成当前订单！\n");
            return;
        }
    }
    
    // 接单
    strcpy(orders[orderIndex].rider, ridername);
    orders[orderIndex].status = 1; // 已接单
    saveOrdersToTxt();
    
    printf("成功接单！订单号: %s\n", orders[orderIndex].orderId);
}

// 查看已接订单
void viewAcceptedOrders(char* ridername) {
    printf("\n====== 我的订单 ======\n");
    int found = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].rider, ridername) == 0 && 
           (orders[i].status == 1 || orders[i].status == 2)) {
            found = 1;
            
            // 格式化时间
            char timeStr[20];
            strftime(timeStr, 20, "%Y-%m-%d %H:%M", 
                    localtime(&orders[i].orderTime));
            
            printf("\n订单号: %s\n", orders[i].orderId);
            printf("商家: %s\n", orders[i].shopname);
            printf("用户: %s\n", orders[i].username);
            printf("下单时间: %s\n", timeStr);
            printf("状态: %s\n", orders[i].status == 1 ? "已接单" : "配送中");
            printf("总金额: %.2f元\n", orders[i].totalPrice);
            
            printf("\n订单明细:\n");
            for(int j = 0; j < orders[i].itemCount; j++) {
                printf("%d. %s x%d %.2f元\n", 
                      j+1,
                      orders[i].items[j].dishName,
                      orders[i].items[j].quantity,
                      orders[i].items[j].price * orders[i].items[j].quantity);
            }
            printf("----------------------------\n");
        }
    }
    
    if(!found) {
        printf("您当前没有已接订单。\n");
    }
}

// 配送订单
void deliverOrder(char* ridername) {
    printf("\n====== 配送订单 ======\n");
    int deliveringOrders[100] = {0};
    int deliveringCount = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].rider, ridername) == 0 && orders[i].status == 1) {
            printf("%d. 订单号: %s (%.2f元)\n", 
                  deliveringCount+1, 
                  orders[i].orderId, 
                  orders[i].totalPrice);
            deliveringOrders[deliveringCount] = i;
            deliveringCount++;
        }
    }
    
    if(deliveringCount == 0) {
        printf("您当前没有需要配送的订单。\n");
        return;
    }
    
    int choice;
    printf("\n请选择要开始配送的订单编号(0取消): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > deliveringCount) {
        printf("无效的订单编号！\n");
        return;
    }
    
    int orderIndex = deliveringOrders[choice-1];
    orders[orderIndex].status = 2; // 配送中
    saveOrdersToTxt();
    
    printf("订单 %s 已开始配送！\n", orders[orderIndex].orderId);
}

// 完成订单
void completeOrder(char* ridername) {
    printf("\n====== 完成订单 ======\n");
    int deliveringOrders[100] = {0};
    int deliveringCount = 0;
    
    for(int i = 0; i < orderCount; i++) {
        if(strcmp(orders[i].rider, ridername) == 0 && orders[i].status == 2) {
            printf("%d. 订单号: %s (%.2f元)\n", 
                  deliveringCount+1, 
                  orders[i].orderId, 
                  orders[i].totalPrice);
            deliveringOrders[deliveringCount] = i;
            deliveringCount++;
        }
    }
    
    if(deliveringCount == 0) {
        printf("您当前没有正在配送的订单。\n");
        return;
    }
    
    int choice;
    printf("\n请选择要完成的订单编号(0取消): ");
    scanf("%d", &choice);
    
    if(choice == 0) return;
    if(choice < 1 || choice > deliveringCount) {
        printf("无效的订单编号！\n");
        return;
    }
    
    int orderIndex = deliveringOrders[choice-1];
    orders[orderIndex].status = 3; // 已完成
    saveOrdersToTxt();
    
    printf("订单 %s 已完成配送！\n", orders[orderIndex].orderId);
}

// 保存骑手数据到TXT
void saveRidersToTxt() {
    FILE *fp = fopen(RIDER_FILE, "w");
    if(fp) {
        fprintf(fp, "用户名,密码,状态\n");
        for(int i = 0; i < riderCount; i++) {
            fprintf(fp, "%s,%s,%d\n", 
                   riders[i].username, 
                   riders[i].password,
                   riders[i].status);
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
            strcpy(riders[riderCount].password, token);
            
            token = strtok(NULL, ",\n");
            riders[riderCount].status = atoi(token);
            
            riderCount++;
        }
        fclose(fp);
    }
}

// 添加菜品
void addDish(Shop *shop) {
    if(shop->dishCount >= 100) {
        printf("菜品数量已达上限！\n");
        return;
    }
    
    printf("\n====== 添加新菜品 ======\n");
    printf("请输入菜品名称: ");
    scanf("%s", shop->dishes[shop->dishCount].name);
    
    printf("请输入菜品价格: ");
    scanf("%f", &shop->dishes[shop->dishCount].price);
    
    shop->dishes[shop->dishCount].isDeleted = 0;
    shop->dishCount++;
    
    printf("添加成功！\n");
    saveShopsToTxt();
}