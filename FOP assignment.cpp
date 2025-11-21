#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

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

int tableNumber = 0;
int pax = 0;

int DineOption(){
  int option = 0;
  cout << "Please choose your option: \n";
  cout << "1. Dine In" << endl;
  cout << "2. Take Away\n" << endl;
  cout << "\nEnter your option(0 to return): ";
  cin >> option;
  
  if (option == 0){
    cout << "Returning to order page...\n" << endl;
  }

  while(option < 0 && option > 2){
    cout << "\nNo such option. Please try again.\n";
    cout << "\nEnter your option (0 to return): ";
    cin >> option;
  }

  if(option == 1)
    cout << "\nYou have chosen Dine In.\n" << endl;
  else if(option == 2)
    cout << "\nYou have chosen Take Away.\n" << endl;

  return option;
}

void Table() 
{
    cout << "Enter table number: ";
    cin >> tableNumber;

    cout << "Enter number of pax: ";
    cin >> pax;

    cout << "\n--- Table Details ---\n";
    cout << "Table Number: " << tableNumber << endl;
    cout << "Number of Pax: " << pax << "\n" << endl;
}

vector<MenuItem> menu = {
    {1, 2.0, "Roti Canai", "Main"},   
    {2, 3.0, "Nasi Lemak", "Main"},
    {3, 5.0, "Nasi Briyani", "Main"}, 
    {4, 2.2, "Teh O", "Drink"},
    {5, 2.0, "Kopi O", "Drink"},
};

vector<CartItem> cart;

void mainMenu() {
  cout << "1. Dine Option" << endl;
  cout << "2. Add Item to Cart" << endl;
  cout << "3. View Cart" << endl;
  cout << "4. Remove Item from Cart" << endl;
  cout << "5. Checkout" << endl;
  cout << "6. Return To Main Page\n" << endl;
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

void mainPage(){
  cout << "\n===== Welcome to Restaurant Management System =====\n\n";
  cout << "1. View Menu" << endl;
  cout << "2. Order" << endl;
  cout << "3. Admin Page" << endl;
}

void viewCart(const vector<CartItem> &cart);

bool addToCart(vector<MenuItem> menu, vector<CartItem> &cart, int DineOption) {
  if(DineOption == 0){
    cout << "Please choose your dine option first. \n" << endl;
    return false;
  }
  
  displayMenu();

  int id;
  int quantity;
  char YN = 'Y';
  bool found;

  while (YN == 'Y' || YN == 'y') {
    found = false;
    while (!found) {
      cout << "Enter Item ID (0 to cancel): ";
      cin >> id;

      if (id == 0) {
        cout << "Returning to order page...\n" << endl;
        return false;
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
      cout << "Enter Quantity (0 to cancel): ";
      cin >> quantity;
      
      if (quantity == 0) {
        cout << "Returning to order page...\n" << endl;
        return false;
      }
        else if (quantity < 0)
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
      cin >> YN;
        
      if (YN == 'N' || YN == 'n' || YN == 'Y' || YN == 'y') {
        found = true;
      } else {
        cout << "Invalid choice. Please try again." << endl;
      }
    }
  }
  
  found = false;
  while (!found) {
    cout << "Proceed to checkout? (Y/N): ";
    cin >> YN;
    if(YN == 'Y' || YN == 'y'){
        found = true;
        return true;
    }
    else if(YN == 'N' || YN == 'n'){
        found = true;
        return false;
    }
    else
        cout << "Invalid choice. Please try again." << endl;
  }
  cout << "\n" << endl;
  return false;
}

void viewCart(const vector<CartItem> &cart) {
  if (cart.empty()) {
    cout << "Cart is empty.\n" << endl;
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
  
  if (id == 0) {
    cout << "Returning to order page...\n" << endl;
    break;
  }
 
  for (auto j = cart.begin(); j != cart.end(); j++) {
    if (j->order.id == id) {
      found = true;
      while (found){
      cout << "Enter quantity to remove: ";
      cin >> quantity;
      if (j->quantity > quantity) {
        j->quantity -= quantity;
        j->totalPrice = j->order.price * j->quantity;
        cout << "Item quantity updated. \n" << endl;
        break;
      } else if (j->quantity < quantity || j->quantity < 0) {
        cout << "Invalid quantity. Please try again." << endl;
      } else
        cart.erase(j);
      cout << "Item removed from cart. \n" << endl;
      break;
      }
    }
    if (!found)
      cout << "Item not found. Please try again." << endl;
  }
  }
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


bool checkout(vector<CartItem> &cart, int DineOption){
  time_t timestamp;
  time(&timestamp);
  if(DineOption == 0){
    cout << "Please choose your dine option first.\n" << endl;
    return false;
  }
  if(cart.empty()){
    cout << "Cart is empty.\n" << endl;
    return false;
  }
  string optionName[] = {"Dine In","Take Away"};
  cout << right << setw(34) << "================= ORDER SUMMARY ================\n" << endl;
  cout << left << setw(5) << ctime(&timestamp);
  if (DineOption == 1) {
    cout << left << setw(5) << "Table Number: " << setw(21) << tableNumber 
    << setw(5) << "No. Pax: " << setw(16) << pax << endl;
  }
  cout << left << setw(5) << "Dine Option: " << setw(22) << optionName[DineOption - 1] 
  << "Total Qty: " << setw(16) << getTotalQuantity(cart)<< endl;
  cout << string(48, '-') << endl;
  cout << left << setw(5) << "ID" << setw(16) << "Item" << setw(16) << "Quantity" << "Total Price" << endl;
  cout << string(48, '-') << endl;
  double Total = 0;
  for (int i = 0; i < cart.size(); i++){
      cout << left << setw(5) << cart[i].order.id << setw(16) << cart[i].order.name << setw(16) << cart[i].quantity << fixed << setprecision(2) << "RM" << cart[i].totalPrice << endl;
      Total += cart[i].totalPrice;
      }
  cout << string(48, '-') << endl;
  
  double Tax = Total * 0.06;
  double TotalWithTax = Total + Tax;

  cout << right << setw(39) << "Subtotal       : RM" << Total << endl;
  cout << right << setw(39) << "Service Tax(6%): RM" << Tax << endl;
  
  double RoundingTotal = round(TotalWithTax * 10) / 10;
  double Rounding = fabs(RoundingTotal - TotalWithTax);
  cout << fixed << setprecision(2);
  
  cout << right << setw(39) << "Rounding       : RM" << Rounding << endl;
  cout << right << setw(39) << "Total(Inc. Tax): RM" << RoundingTotal << endl;
  cout << right << setw(34) << "================================================" << endl;

  char confirm;
    cout << "\nConfirm checkout? (Y/N): ";
    cin >> confirm;
    if(confirm == 'Y' || confirm == 'y'){
      int paymentChoice = Payment();
        string paymentMethods[] = {"Credit or Debit Card", "QR Code Payment", "Cash"};

        // **NEW: Displaying Final Confirmation with Payment Method**
        cout << "\n--- Final Transaction Details ---\n";
        cout << "Amount Due: RM" << fixed << setprecision(2) << RoundingTotal << endl;
        cout << "Payment Method: " << paymentMethods[paymentChoice - 1] << endl;
        cout << "Processing Payment..." << endl;
      
      cout << "Checkout successful. Thank you for your order!" << endl;
      return true;
    }
    else{
      cout << "Returning to main menu." << endl;
      return false;
    }
}



void orderPage() {
  int choice = 0;
  int DineOpt = 0;
  while (choice != 6) {
    mainMenu();
    cout << "Enter your choice: ";
    cin >> choice;
    cout << "\n";
    switch (choice) {
    case 1:
      DineOpt = DineOption();
      if (DineOpt == 1) { 
        Table();      
      }
      break;
    case 2:
      if(addToCart(menu, cart, DineOpt)){
        if(checkout(cart, DineOpt))
            choice = 6;
      }
      break;
    case 3:
      viewCart(cart);
      break;
    case 4:
      removeFromCart(cart);
      break;
    case 5:
      if(checkout(cart, DineOpt))
        choice = 6;
      break;
    case 6:
      break;
    default:
      cout << "\nInvalid choice. Please try again.\n\n";
    }
  }
}

void adminPage(){
    cout << "Welcome To Admin Page" << endl;
    int choice = 1;
    while (choice !=0){
    cout << "Enter 0 to return to Main Page: ";
    cin >> choice;
    cout << "Invalid choice! Please Try Again" << endl;
    }
}

int main(){
    int choice = 0;
    bool found = false;
    while (found == false){
        mainPage();
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";
        switch (choice) {
            case 1:
            displayMenu();
            choice = 1;
            while(choice != 0){
                cout << "Enter 0 to return to Main Page: ";
                cin >> choice;
                if(choice != 0){
                    cout << "Invalid choice! Please Try Again." << endl;
                }
            }
            break;
            case 2:
            orderPage();
            break;
            case 3:
            adminPage();
            break;
            default:
            cout << "\nInvalid choice. Please try again.\n\n";
        }
    }
}
