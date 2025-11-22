#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

int tableNumber = 0;
int pax = 0;
int DineOpt=0;

struct MenuItem {
  int id;
  double price;
  string name, category;
};

struct CartItem {
  MenuItem order;
  int quantity;
  double totalPrice;
};

vector<MenuItem> menu = {
    {1, 2.0, "Roti Canai", "Main"},   
    {2, 3.0, "Nasi Lemak", "Main"},
    {3, 5.0, "Nasi Briyani", "Main"},
    {4, 2.2, "Teh O", "Drink"},
    {5, 2.0, "Kopi O", "Drink"},
};

vector<CartItem> cart;

string salesFile = "sales.txt";

void generateSimpleReport() {
    ifstream file(salesFile);
    if (!file.is_open()) {
        cout << "No sales file found.\n";
        return;
    }

    cout << "\n=== Sales Report ===\n";
    cout << "1. Daily\n";
    cout << "2. Monthly\n";
    cout << "3. Yearly\n";
    cout << "Choose: ";
    
    int opt;
    cin >> opt;

    string key;
    if (opt == 1) {
        cout << "Enter date (YYYY-MM-DD): ";
    } else if (opt == 2) {
        cout << "Enter month (YYYY-MM): ";
    } else if (opt == 3) {
        cout << "Enter year (YYYY): ";
    } else {
        cout << "Invalid option.\n";
        return;
    }
    cin >> key;

    double total = 0;
    string line;

    cout << "\nMatching Records:\n";

    while (getline(file, line)) {
        if (line.rfind(key, 0) == 0) {  // starts with key
            cout << line << endl;

            size_t pos = line.find("|");
            if (pos != string::npos) {
                double amount = stod(line.substr(pos + 1));
                total += amount;
            }
        }
    }

    cout << "\nTotal Sales: RM" << fixed << setprecision(2) << total << endl;
    file.close();
}


void saveMenuToFile() {
    ofstream file("menu.txt"); 
    
    if (file.is_open()) {
        file << menu.size() << endl; 

        for (int i = 0; i < menu.size(); i++) {
            file << menu[i].id << endl;
            file << menu[i].price << endl;
            file << menu[i].name << endl;
            file << menu[i].category << endl;
        }
        file.close();
    } 
    else
      cout << "Error: Unable to save menu." << endl;
}

void loadMenuFromFile() {
    ifstream file("menu.txt");
    
    if (!file.is_open()) {
        saveMenuToFile();
        return; 
    }

    int totalItems;
    file >> totalItems;

    menu.clear();

    for (int i = 0; i < totalItems; i++) {
        MenuItem item;
        
        file >> item.id;
        file >> item.price;
        
        file.ignore(); 
        getline(file, item.name);
        getline(file, item.category);

        menu.push_back(item);
    }
    file.close();
}

void Table() 
{
    cout << "Enter table number: ";
    cin >> tableNumber;

    cout << "Enter number of pax: ";
    cin >> pax;

    cout << "\n--- Table Details ---\n";
    cout << "Table Number: " << tableNumber << endl;
    cout << "Number of Pax: " << pax << endl;
}

void displayMenu() {
  cout << right << setw(34) << "========== MENU ==========" << endl;
  cout << left << setw(5) << "ID" << setw(16) << "Item" << setw(16)
  << "Category" << "Price" << endl;
  cout << string(42, '-') << endl;
  for (int i = 0; i < menu.size(); i++)
    cout << left << setw(5) << menu[i].id << setw(16) << menu[i].name
         << setw(16) << menu[i].category << fixed << setprecision(2) << "RM"
         << menu[i].price << endl;
  cout << string(42, '-') << endl;
}

void viewCart(const vector<CartItem> &cart) {
  if (cart.empty()) {
    cout << "Cart is empty." << endl;
    return;
  }

  cout << right << setw(34) << "========== CART ==========" << endl;
  cout << left << setw(5) << "ID" << setw(16) << "Item" << setw(16)
       << "Quantity" << "Total Price" << endl;
  cout << string(42, '-') << endl;

  double Total = 0;
  for (int i = 0; i < cart.size(); i++) {
    cout << left << setw(5) << cart[i].order.id << setw(16)
         << cart[i].order.name << setw(16) << cart[i].quantity << fixed
         << setprecision(2) << "RM" << cart[i].totalPrice << endl;
    Total += cart[i].totalPrice;
  }
  cout << string(42, '-') << endl;
  cout << "Total (excl. tax): RM" << Total << endl;
  cout << string(42, '-') << endl;
}

string discountCode = "";
int redemptionCount = 0;
const int MAX_REDEMPTION = 50;

time_t now = time(0);
tm* timeinfo = localtime(&now);
int hour = timeinfo->tm_hour;
int day = timeinfo->tm_wday;

void discount(){
  char AddDisc;
  string disc;
  while (AddDisc != 'Y' && AddDisc != 'y' && AddDisc != 'N' && AddDisc != 'n'){
    cout << "Add Discount? (Y/N): ";
    cin >> AddDisc;
    if(AddDisc == 'Y' || AddDisc == 'y'){
        bool validCode = false;
        while (!validCode){
            cout << "Enter Discount Code(0 to cancel): ";
            cin >> discountCode;
      
            if (discountCode == "20OFF"){
                if (redemptionCount < MAX_REDEMPTION){
                redemptionCount++;
                cout << "Discount Applied!" << endl;
                validCode = true;
                }
                else{
                cout << "Redemption Limit Reached!" << endl;
                discountCode = "";
                }
            }
            else if(discountCode == "LUNCHHOUR"){
                if ((day >= 1 && day <= 5) && (hour >= 12 && hour < 14)){
                    cout << "Discount Applied!" << endl;
                    validCode = true;
                }
                else {
                    cout << "Discount only valid on weekdays 12-2pm!" << endl;
                    discountCode = "";
                }
            }
            else if (discountCode == "0")
                break;
            else{
                cout << "Invalid Code. Please Try Again!" << endl;
                discountCode = "";
            }
        }
        break;
    }
    else if(AddDisc == 'N' || AddDisc == 'n')
        break;
    else 
        cout << "Invalid input. Please Try Again!" << endl;
  }
}

void addToCart(vector<MenuItem> menu, vector<CartItem> &cart) {
  char addMore = 'Y';

  while (addMore == 'Y' || addMore == 'y') {
    displayMenu();

    int id;
    int quantity;
    bool found = false;

    
    while (!found) {
      cout << "Enter Item ID (0 to cancel): ";
      cin >> id;

      if (id == 0) {
        cout << "Returning to main menu..." << endl;
        return;
      }

      for (int i = 0; i < menu.size(); i++) {
        if (menu[i].id == id) {
          found = true;
          break;
        }
      }

      if (!found)
        cout << "There is no such item! Please try again." << endl;
    }

    
    found = false;
    while (!found) {
      cout << "Enter Quantity: ";
      cin >> quantity;

      if (quantity <= 0)
        cout << "Invalid quantity! Please try again." << endl;
      else if (quantity > 100)
        cout << "Quantity exceeds limit! Please try again." << endl;
      else
        found = true;
    }

    
    for (int i = 0; i < menu.size(); i++) {
      if (menu[i].id == id) {
        CartItem NewItem = {menu[i], quantity, menu[i].price * quantity};
        cart.push_back(NewItem);
        cout << menu[i].name << " x" << quantity << " added to cart." << endl;
        break;
      }
    }

    cout << "\n";
    viewCart(cart);
    cout << "\n";

    found = false;
    while (!found) {
      cout << "Add more items? (Y/N): ";
      cin >> addMore;
        
      if (addMore == 'N' || addMore == 'n' || 
          addMore == 'Y' || addMore == 'y') {
        found = true;
      } else {
        cout << "Invalid choice. Please try again." << endl;
      }
    }
  }
    discount();
    cout << "\n";
}

void removeFromCart(vector<CartItem> &cart) {
  if (cart.empty()) {
    cout << "Cart is empty." << endl;
    return;
  }
  bool found = false;
  viewCart(cart);
    cout << "\n";
  while (!found){  
  int id;
  int quantity;
  cout << "Enter Item ID to remove: ";
  cin >> id;

 
  for (auto j = cart.begin(); j != cart.end(); j++) {
    if (j->order.id == id) {
      found = true;
      while (found){
      cout << "Enter quantity to remove: ";
      cin >> quantity;
      if (j->quantity > quantity) {
        j->quantity -= quantity;
        j->totalPrice = j->order.price * j->quantity;
        cout << "Item quantity updated." << endl;
        break;
      } else if (j->quantity < quantity || j->quantity < 0) {
        cout << "Invalid quantity. Please try again." << endl;
      } else
        cart.erase(j);
      cout << "Item removed from cart." << endl;
      break;
      }
    }
    if (!found)
      cout << "Item not found. Please try again." << endl;
  }
  }
}

int DineOption(){
  int option;
  cout << "Please choose your option: \n";
  cout << "1. Dine In" << endl;
  cout << "2. Take Away\n" << endl;
  cout << "\nEnter your option: ";
  cin >> option;

  while(option != 1 && option != 2){
    cout << "\nNo such option. Please try again.\n";
    cout << "\nEnter your option: ";
    cin >> option;
  }

  if(option == 1)
    cout << "\nYou have chosen Dine In.\n" << endl;
  else if(option == 2)
    cout << "\nYou have chosen Take Away.\n" << endl;

  return option;
}

int Payment() 
{
    int paymentOption;
    cout << "\nChoose Payment Method:\n";
    cout << "1. Credit or Debit card" << endl;
    cout << "2. QR Code Payment" << endl;
    cout << "3. Cash" << endl;
    cout << "\nEnter payment option: ";
    cin >> paymentOption;

    while (paymentOption < 1 || paymentOption > 3) {
        cout << "Invalid option. Please choose 1, 2, or 3: ";
        cin >> paymentOption;
    }
    return paymentOption;
}

int getTotalQuantity(vector<CartItem> &cart){
    int total = 0;
    for(const auto &item : cart){
        total += item.quantity;
    }
    return total;
}

double rounding(double amount){
    double cents = amount * 100.0;  
    int lastDigit = abs((int)cents % 10);  

    if(lastDigit < 5){
        cents = cents - lastDigit;
    }
    else if(lastDigit >= 5 && lastDigit <= 9){
        cents = cents - lastDigit + 5;
    }

    return cents / 100.0;
}

bool checkout(vector<CartItem> &cart, int DineOption){
  time_t timestamp;
  time(&timestamp);
  if(DineOption == 0){
    cout << "Please choose your dine option first." << endl;
    return false;
  }
  if(cart.empty()){
    cout << "Cart is empty." << endl;
    return false;
  }
  string optionName[] = {"Dine In","Take Away"};
  cout << right << setw(34) << "================= ORDER SUMMARY ================\n" << endl;
  cout << left << setw(5) << ctime(&timestamp) << endl;
  cout << left << setw(5) << "Dine Option: " << setw(16) << optionName[DineOption - 1] << endl;
 if (DineOption == 1) { // Dine In
    cout << left << setw(5) << "Table Number: " << setw(16) << tableNumber << endl;
    cout << left << setw(5) << "No. of Pax: " << setw(16) << pax << endl;
}
  cout << left << setw(5) << "Total Quantity: " << setw(16) << getTotalQuantity(cart)<< endl;
  cout << string(48, '-') << endl;
  cout << left << setw(5) << "ID" << setw(16) << "Item" << setw(16) << "Quantity" << "Total Price" << endl;
  cout << string(48, '-') << endl;
  
  double Total = 0;
  for (int i = 0; i < cart.size(); i++){
      cout << left << setw(5) << cart[i].order.id << setw(16) << cart[i].order.name << setw(16) << cart[i].quantity << fixed << setprecision(2) << "RM" << cart[i].totalPrice << endl;
      Total += cart[i].totalPrice;
      }
      
  cout << string(48, '-') << endl;
  cout << right << setw(39) << "Subtotal       : RM" << Total << endl;
  
  double discountAmount = 0;
  if (discountCode == "20OFF"){
      discountAmount = Total * 0.2;
      if (discountAmount >= 20)
        discountAmount = 20;
      cout << right << setw(39) << "Discount(20OFF): RM" << discountAmount << endl;
  }
  else if (discountCode == "LUNCHHOUR"){
      discountAmount = Total * 0.1;
      cout << right << setw(39) << "Discount(LUNCH): RM" << discountAmount << endl;
  }
  
  Total = Total - discountAmount;
  
  cout << right << setw(39) << "Service Tax(6%): RM" << Total * 0.06 << endl;
  cout << right << setw(39) << "Rounding       : RM" << fabs(rounding(Total * 1.06) - Total * 1.06) << endl;
    double finalTotal = rounding(Total * 1.06);
  cout << right << setw(39) << "Total(Inc. Tax): RM" << rounding(Total * 1.06) << endl;
  cout << right << setw(34) << "================================================" << endl;

  char confirm;
    cout << "\nConfirm checkout? (Y/N): ";
    cin >> confirm;
    if(confirm == 'Y' || confirm == 'y'){
      
        int paymentChoice = Payment();
        string paymentMethods[] = {"Credit or Debit Card", "QR Code Payment", "Cash"};

        // **NEW: Displaying Final Confirmation with Payment Method**
        cout << "\n--- Final Transaction Details ---\n";
        cout << "Amount Due: RM" << fixed << setprecision(2) << finalTotal << endl;
        cout << "Payment Method: " << paymentMethods[paymentChoice - 1] << endl;
        cout << "Processing Payment..." << endl;
      
      cout << "Checkout successful. Thank you for your order!" << endl;
      ofstream sales(salesFile, ios::app);
      time_t now = time(0);
      tm *ltm = localtime(&now);

      char dateStr[11];
      sprintf(dateStr, "%04d-%02d-%02d",
        1900 + ltm->tm_year,
        1 + ltm->tm_mon,
        ltm->tm_mday);
      sales << dateStr << " | " << finalTotal << endl;
      sales.close();
      
      discountCode = "";
      return true;
    }
    else{
      cout << "Returning to main menu." << endl;
      return false;
    }
}

void addMenuItem(){
  MenuItem newItem;
  bool itemExistCheck=false;

  do{
    itemExistCheck=false;
    cout << "\nEnter new item ID: ";
    cin >> newItem.id;
    for(const auto &i : menu){
      if(i.id==newItem.id){
        cout << "Item with same ID already exists. Please try again."<<endl;
        itemExistCheck=true;
        break;
        }
      }
    }while(itemExistCheck);

  cin.ignore();
  
  cout << "Enter Item Name: ";
  getline(cin, newItem.name);

  int categoryChoice;
  do{
    cout << "Enter Item Category(1-Main, 2-Drink): ";
    cin >> categoryChoice;
    
    if (categoryChoice == 1)
      newItem.category = "Main";
    else if (categoryChoice == 2)
      newItem.category = "Drink";
    else cout << "Invalid choice, please enter 1 or 2.\n" << endl;
  }while(categoryChoice!=1 && categoryChoice!=2);
  cout << "Enter Item Price: RM";
  cin >> newItem.price;

  menu.push_back(newItem);

  saveMenuToFile();
}

void removeMenuItem() {
    int id;
    bool itemExists = false;
    
    displayMenu();
    cout << "\nEnter Item ID to remove: ";
    cin >> id;

    for (auto it = menu.begin(); it != menu.end(); ++it) {
        if (it->id == id) {
            menu.erase(it); 
            itemExists = true;
            cout << "Item removed successfully." << endl;
            
            saveMenuToFile(); 
            break;
        }
    }

    if (!itemExists) {
        cout << "Item ID not found." << endl;
    }
}

void editMenuItem() {
    int id;
    bool itemExists = false;

    displayMenu(); // Show menu so user knows the IDs
    cout << "\nEnter Item ID to edit: ";
    cin >> id;

    for (auto &item : menu) {
        if (item.id == id) {
            itemExists = true;
            int editChoice = 0;

            cout << "\nCurrently Editing Item: " << item.name << endl;
            cout << "1. Edit Name" << endl;
            cout << "2. Edit Price" << endl;
            cout << "3. Edit Category" << endl;
            cout << "4. Cancel" << endl;
            cout << "Enter choice: ";
            cin >> editChoice;

            if (editChoice == 1) {
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, item.name);
                cout << "Name updated." << endl;
            } 
            else if (editChoice == 2) {
                cout << "Enter New Price: RM";
                cin >> item.price;
                cout << "Price updated." << endl;
            } 
            else if (editChoice == 3) {
                int catChoice;
                do {
                    cout << "Enter New Category (1-Main, 2-Drink): ";
                    cin >> catChoice;
                    if (catChoice == 1) 
                      item.category = "Main";
                    else if (catChoice == 2) 
                      item.category = "Drink";
                    else 
                      cout << "Invalid choice." << endl;
                }while (catChoice != 1 && catChoice != 2);
                cout << "Category updated." << endl;
            } 
            else {
                cout << "Edit cancelled." << endl;
                return;
            }

            saveMenuToFile();
            break; 
        }
    }

    if (!itemExists) {
        cout << "Item ID not found." << endl;
    }
}

void displayOrder() {
  int choice=0;

  if (DineOpt == 0){
    DineOpt = DineOption();
      if (DineOpt == 1)
      Table();
  }

  while (choice!=3){
    cout << "\n===== Order Menu =====\n\n";
    cout << "1. View Menu" << endl;
    cout << "2. Add Item to Cart" << endl;
    cout << "3. Return" << endl;
    
    cout << "\nEnter choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      displayMenu();
      break;
    case 2:
      addToCart(menu,cart);
      break;
    case 3:
      break;
    default:
      cout << "\nInvalid choice. Please try again.\n\n";
    }
  }
}

void displayCart() {
  int choice=0;
  while (choice!=4){
    cout << "\n===== Cart Menu =====\n\n";
    cout << "1. View Cart" << endl;
    cout << "2. Remove Item" << endl;
    cout << "3. Checkout" << endl;
    cout << "4. Return" << endl;
    
    cout << "\nEnter choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      viewCart(cart);
      break;
    case 2:
      removeFromCart(cart);
      break;
    case 3:
      checkout(cart,DineOpt);
      break;
    case 4:
        break;
    default:
      cout << "\nInvalid choice. Please try again.\n\n";
    }
  }
}

void displayAdmin() {
  int choice=0;

  while (choice!=5){
    cout << "\n===== Admin Menu =====\n\n";
    cout << "1. Add Menu Item" << endl;
    cout << "2. Delete Menu Item" << endl;
    cout << "3. Edit Existing Menu Item" << endl;
    cout << "4. Generate Sales Reports" << endl;
    cout << "5. Return" << endl;

    cout << "\nEnter choice: ";
    cin >> choice;  
    switch (choice) {
    case 1:
      addMenuItem();
      break;
    case 2:
      removeMenuItem();
      break;
    case 3:
      editMenuItem();
      break;
    case 4:
      generateSimpleReport();
      break;
    case 5:
      break;
    default:
      cout << "\nInvalid choice. Please try again.\n\n";
    }
  }
}

bool displayMain() {
  int choice = 0;
  cout << "\n===== Welcome to Restaurant Management System =====\n\n";
  cout << "1. Create Orders" << endl;
  cout << "2. Cart" << endl;
  cout << "3. Admin Panel" << endl;
  cout << "4. Exit" << endl;

  cout << "\nEnter choice: ";
  cin >> choice;

  switch (choice) {
    case 1:
      displayOrder();
      break;
    case 2:
      displayCart();
      break;
    case 3:
      displayAdmin();
      break;
    case 4:
      cout << "Thank you for using our Restaurant Management System." << endl;
      return false;
    default:
      cout << "\nInvalid choice. Please try again.\n\n";
  }
  return (true);
}

int main() {
  loadMenuFromFile();
  while (displayMain()) {}
  return(0);
}
