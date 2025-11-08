#include <iomanip>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

struct menuItem{
    int id;
    double price;
    string name, category;
};

struct cartItem{
    menuItem order;
    int quantity;
    double totalPrice;
};

vector<menuItem> menu = {
    {1, 2.0, "Roti Canai", "Main"},   
    {2, 3.0, "Nasi Lemak", "Main"},
    {3, 5.0, "Nasi Briyani", "Main"}, 
    {4, 2.2, "Teh O", "Drink"},
    {5, 2.0, "Kopi O", "Drink"},
};

vector<cartItem> cart;

void mainMenu(){
    cout << "\n===== Welcome to Restaurant Management System =====\n\n";
    cout << "1. Dine Option" << endl;
    cout << "2. View Menu" << endl;
    cout << "3. Add Item to Cart" << endl;
    cout << "4. View Cart" << endl;
    cout << "5. Remove Item from Cart" << endl;
    cout << "6. Checkout" << endl;
    cout << "7. Exit\n" << endl;
}

void displayMenu(){
    cout << right << setw(34) << "========== MENU ==========" << endl;
    cout << left << setw(5) << "ID" << setw(16) << "Item" << setw(16) << "Category"<< "Price" << endl;
    cout << string(42, '-') << endl;
    for (int i = 0; i < menu.size(); i++)
    cout << left << setw(5) << menu[i].id << setw(16) << menu[i].name << setw(16) << menu[i].category << fixed << setprecision(2) << "RM" << menu[i].price << endl;
    cout << string(42, '-') << endl;
}

void addToCart(vector<menuItem> menu, vector<cartItem> &cart){
    int id;
    int quantity;
    cout << "Enter Item ID: ";
    cin >> id;
    cout << "Enter Quantity: ";
    cin >> quantity;

    if(quantity <= 0){
        cout << "Invalid quantity! Please try again." << endl;
        return;
        }
    else if(quantity > 100){ 
        cout << "Quantity exceeds limit! Please try again." << endl;
        return;
  }

    bool found = false;
    for (int i = 0; i < menu.size(); i++){
        if (menu[i].id == id){
            found = true;
            cartItem newItem = {menu[i], quantity, menu[i].price * quantity};
            cart.push_back(newItem);
            cout << "Item added to cart." << endl;
            break;
            }
        }
    if (!found)
        cout << "There is no such item! Please try again." << endl;
}

void viewCart(const vector<cartItem> &cart){
    if(cart.empty()){
        cout << "Cart is empty." << endl;
        return;
  }
  
  cout << right << setw(34) << "========== CART ==========" << endl;
  cout << left << setw(5) << "ID" << setw(16) << "Item" << setw(16) << "Quantity"<< "Total Price" << endl;
  cout << string(42, '-') << endl;

  double grandTotal = 0;
  for (int i = 0; i < cart.size(); i++){
    cout << left << setw(5) << cart[i].order.id << setw(16) << cart[i].order.name << setw(16) << cart[i].quantity << fixed << setprecision(2) << "RM" << cart[i].totalPrice << endl;
    grandTotal += cart[i].totalPrice;
  }
    cout << string(42, '-') << endl;
    cout << "Grand Total: RM" << grandTotal << endl;
    cout << string(42, '-') << endl;

}

void removeFromCart(vector<cartItem> &cart){
  if(cart.empty()){
    cout << "Cart is empty." << endl;
    return;
  }

  int id;
  int quantity;
  cout << "Enter Item ID to remove: ";
  cin >> id;
  cout << "Enter quantity to remove: ";
  cin >> quantity;

  bool found = false;
  for(auto j = cart.begin(); j != cart.end(); j++){
    if(j->order.id == id){
      found = true;
      if(j->quantity > quantity){
        j->quantity -= quantity;
        j->totalPrice = j->order.price * j->quantity;
        cout << "Item quantity updated." << endl;
      }
      else if(j->quantity < quantity){
        cout << "Invalid quantity. Please try again." << endl;
        return;
      }
      else
        cart.erase(j);
      cout << "Item removed from cart." << endl;
      break;
    }
    if (!found)
      cout << "Item not found. Please try again." << endl;
  }
}

void DineOption(){
  int option;
  cout << right << setw(34) << "Please choose your option: \n";
  cout << right << setw(23) << "1. Dine In" << endl;
  cout << right << setw(25) << "2. Take Away\n" << endl;
  cout << "\nEnter your option: ";
  cin >> option;
  if(option == 1)
    cout << "\nYou have chosen Dine In.\n" << endl;
  else if(option == 2)
    cout << "\nYou have chosen Take Away.\n" << endl;
  else
    cout << "\nNo such option. Please try again.\n" << endl;
  return;
}

int main(){
    int choice = 0;
    while (choice != 6){
    mainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";
        switch (choice){
        case 1:
            DineOption();
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
            break;
        case 7:
			cout << "Thank you for using our Restaurant Management System." << endl;
			break;
		default:
            cout << "\nInvalid choice. Please try again.\n\n";
        }
    }
}

//testpullrequest//
