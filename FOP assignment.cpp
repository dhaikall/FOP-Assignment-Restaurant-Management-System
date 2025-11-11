#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int DineOption();

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

void mainMenu() {
  cout << "\n===== Welcome to Restaurant Management System =====\n\n";
  cout << "1. Dine Option" << endl;
  cout << "2. View Menu" << endl;
  cout << "3. Add Item to Cart" << endl;
  cout << "4. View Cart" << endl;
  cout << "5. Remove Item from Cart" << endl;
  cout << "6. Checkout" << endl;
  cout << "7. Exit\n" << endl;
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

void viewCart(const vector<CartItem> &cart);

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
    cout << "\n";
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
  cout << right << setw(39) << "Service Tax(6%): RM" << Total * 0.06 << endl;
  cout << right << setw(39) << "Rounding       : RM" << fabs(rounding(Total * 1.06) - Total * 1.06) << endl;
  cout << right << setw(39) << "Total(Inc. Tax): RM" << rounding(Total * 1.06) << endl;
  cout << right << setw(34) << "================================================" << endl;

  char confirm;
    cout << "\nConfirm checkout? (Y/N): ";
    cin >> confirm;
    if(confirm == 'Y' || confirm == 'y'){
      cout << "Checkout successful. Thank you for your order!" << endl;
      return true;
    }
    else{
      cout << "Returning to main menu." << endl;
      return false;
    }
}



int main() {
  int choice = 0;
  int DineOpt = 0;
  while (choice != 7) {
    mainMenu();
    cout << "Enter your choice: ";
    cin >> choice;
    cout << "\n";
    switch (choice) {
    case 1:
      DineOpt = DineOption();
      break;
    case 2:
      displayMenu();
      break;
    case 3:
      addToCart(menu, cart);
      break;
    case 4:
      viewCart(cart);
      break;
    case 5:
      removeFromCart(cart);
      break;
    case 6:
      if(checkout(cart, DineOpt))
        choice = 7;
      break;
    case 7:
      cout << "Thank you for using our Restaurant Management System." << endl;
      break;
    default:
      cout << "\nInvalid choice. Please try again.\n\n";
    }
  }
}

