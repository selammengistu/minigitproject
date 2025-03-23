//Selamawit Mengistu
//UGR/4008/16

#include <iostream>
#include <string>
using namespace std; 

//number 1
int main() {
    std::cout << "Hello,welcome to myflixer website!" << std::endl;
    std::cout << "This website allows you to watch HD TV Movie Movies And Shows Online For Free and Download the latest TV Movie movies and shows" << std::endl;
    std::cout << "Remember that C++ is a compiled language which means that the code you write needs to be compiled into machine code before it can be executed." << std::endl;


//number 2

std::string productName = "Shoes";
    int productCategory = 5;
    int initial_inventory_quantity = 50;
    double product_price_per_unit = 9.99;
    int number_of_item_sold = 20;

// 3


int newInventory = 30;
    double total_sales_amount = 14;
    std::string inventoryStatus ;
    

// 4. demonstrate different initialization method 

//declaration of variables 
int a, b; 
// Assignment after declaration  
    b = 2; 
    a = b+2;         
 

// 5. demonstrate different initialization method 

 //auto keyword 
int totalSalesAmount = 100; 
auto s = totalSalesAmount; 
// decltype inventory  
int Inventory = 50; 
decltype (Inventory) I;  


// 6. Define constants 
//tax rate constant using preprocessor 
#define taxRate 0.35; 


//tax rate using constant 
const double taxRate;
         


// 7. Input from the user 
using std::string ; productname, productcat; 
    cout << "What's the productname? "; 
getline (cin, productname); 
    cout << "The product name is: " << productname << ".\n"; 
    cout << "What is the product catagory? "; 
getline (cin, productcat); 
    cout << "The product category is:  " << productcat << " .\n"; 
int c, p, h; 
    cout << "What's the intial inventory quantity? "; 
    cin>>a; 
    cout << "The initial inventory quantity is:  " << c << " .\n"; 
    cout << "What's the product price ? "; 
    cin>>p; 
    cout << "The product price is:  " << p << " .\n"; 
    cout << "What's the number of items sold? "; 
    cin>>s; 
    cout << "The number of items sold is:  " << h << " .\n"; 
   


// 8. Perform calculations 

int n, i=50, j=20, k=10;  
n=i-j; 
    cout << "The new inventory amount is:  "<<n<<".\n"; 
    cout << "The total sales amount is:  "<<j*k<<".\n"; 
   


// 9. Use a conditional (Ternary )operator 

 int x; 
    cout << "Enter the inventory amount"; 
    cin>>x; 
    if (x < 10) 
cout << "Low Invetory"; 
    else 
cout << "Sufficient Inventory"; 
    
 

//10. Implement flow control  
 
int e; 
// using if  
    cout << "Product category range from 1 to 5"; 
    cin>>x; 
    if (e ==  1) 
cout << "Electronics"; 
    else if (e == 2) 
cout << "Groceries"; 
    else if (e == 3) 
cout << "Clothing "; 
    else if (e == 4) 
cout << "Stationary "; 
    else if (e == 5) 
cout << "Miscellaneous "; 
    else 
cout << "Out of valid range";
// Switch 
switch (e) { 
case 1: 
cout << "Electronics"; 
break; 
case 2: 
cout << "Groceries"; 
break; 
case 3: 
cout << "Clothing"; 
break; 
case 4: 
cout << "Stationary"; 
break; 
case 5: 
cout << "Miscellaneous"; 
break; 
default: 
cout << "out of valid range"; 
}


//11. Use a for loop 

int price=10, m; 
cout << "Enter the number of items sold\n"; 
cin>>m; 
for (int n=1; n<=a; n++) { 
cout << "The item sold "<< n << "price is "<<price<<".\n "; 
}


// 12. Output all information   
#define TaxRate 0.35      
 
 
    cout << "Taxe rate is "<< TaxRate << ".\n "; 
const double 0.35;  
    cout << "Taxe rate is "<< TaxRate << ".\n "; 
std::string productname, productcat; 
int h, p=10, s, a=50, t;//h new inventory, p price, s sold items, a initial inventory, total sales amount 
cout << "Enter the number of items sold "; 
cin>>s 
cout << "What's the product name? "; 
getline (cin, productname); 
cout << "What is the product catagory? "; 
getline (cin, productcat); 
cout << "The product details :  " << " name "<<productname<<" Catagory "<<productcat <<" intial ";
inventory"<<a<< " Price "<<p<< " items sold "<< s << "endl""; 
h=a-s; // new inventory 
cout << "The new invetory :  " << h<< " .\n"; 
t=p*s; // total sales amount 
cout << "The total sales amount:  " << t<< " .\n"; 
// inventory status 
if (h < 10) 
cout << "Low Invetory"; 
else 
cout << "Sufficient Inventory"; 
//auto keyword 
int TotalSalesAmount = 100; 
auto s = TotalSalesAmount; 
// decltype inventory  
int Inventory = 50; 
decltype (Inventory) I; 
return 0;
}