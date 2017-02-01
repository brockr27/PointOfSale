/* written by David De Leon
 * This is the driver class for the GUI. It holds
*/

#include "OrderForm.h"
#include "TableWindow.h"
#include <QApplication>
#include "mainwindow.h"
#include "FileSystem.h"

void createMenuItems(FileSystem* fs);
void createEmployees(FileSystem* fs);

int main(int argc, char *argv[])
{
    //variables
    QApplication a(argc, argv);
    OrderForm order;
    TableWindow tables;
    MainWindow window;
    FileSystem fs = FileSystem();

    //write the menuitem file if it doesn't exist
    bool exists = fs.FileExists("MenuItems.txt");
    if(!exists)
        createMenuItems(&fs);

    //write the Employee files if 123 doesn't exist
    exists = fs.FileExists("Employee123.txt");
    if(!exists)
        createEmployees(&fs);

    //show the login window
    window.show();

    //GENERIC CONNECTION TEMPLATE
    //QObject::connect(&CALLING_OBJECT,SIGNAL(CALLING_FUNCTION(ARGS)), &RECIEVING_OBJECT, SLOT(RECIEVING_FUNCTION(ARGS)));
    //SIGNAL clicking a table button will open the order page for that table
    QObject::connect(&tables, SIGNAL(tableSelect(int, int)),&order, SLOT(setTable(int, int)));
//PLACEHOLDER SIGNAL mainwindow activates tablewindow
    QObject::connect(&window, SIGNAL(employeeSelect(int)),&tables, SLOT(setEmployee(int)));
//PLACEHOLDER SIGNAL connects multiple order page buttons back to the inital login page
    QObject::connect(&order,SIGNAL(endSession()), &window, SLOT(showLogin()));
    return a.exec();
}

//this function will build the MenuItem file
//written by Mark, edited by Brock, David, and Bradley
void createMenuItems(FileSystem* fs) {
    std::vector<MenuItem> items;

    // appetizer objects
    MenuItem nachos(101, 6.99, "nachos");
    MenuItem chickenwings_buffalo(102, 6.99, "buffalo wings");
    MenuItem chickenwings_honeymustard(103, 6.99, "honeymustard wings");
    MenuItem jalepeno_poppers(104, 4.49, "jalepeno poppers");
    MenuItem mushrooms_stuffed(105, 5.49, "stuffed mushrooms");

    items.push_back(nachos);
    items.push_back(chickenwings_buffalo);
    items.push_back(chickenwings_honeymustard);
    items.push_back(jalepeno_poppers);
    items.push_back(mushrooms_stuffed);

    // soup and salad objects
    MenuItem soup_frenchOnion(201, 4.99, "french onion soup");
    MenuItem soup_blackBean(202, 5.99, "black bean soup");
    MenuItem soup_clamChowder(203, 6.99, "clam chowder");
    MenuItem salad_ceasar(204, 3.99, "ceaser salad");
    MenuItem salad_house(205, 2.99, "house salad");


    items.push_back(soup_frenchOnion);
    items.push_back(soup_blackBean);
    items.push_back(soup_clamChowder);
    items.push_back(salad_ceasar);
    items.push_back(salad_house);

    // meat objects
    MenuItem hamburger_classic(301, 6.49, "classic hamburger");
    MenuItem hamburger_kingKong(302, 9.99, "king kong burger");
    MenuItem hamburger_cheeseBacon(303, 7.49, "bacon cheeseburger");
    MenuItem steak_ribeye(304, 12.99, "ribeye steak");
    MenuItem steak_primeRib(305, 15.99, "prime rib");

    items.push_back(hamburger_classic);
    items.push_back(hamburger_cheeseBacon);
    items.push_back(hamburger_kingKong);
    items.push_back(steak_ribeye);
    items.push_back(steak_primeRib);

    // seafood objects
    MenuItem surf_n_turf(401, 24.99, "surf 'n' turf");
    MenuItem shrimp_trio(402, 12.99, "shrimp trio");
    MenuItem fish_seabass(403, 18.99, "sea bass");
    MenuItem fish_cohoSalmon(404, 15.99, "salmon");
    MenuItem crab_blue(405, 16.99, "blue crab");

    items.push_back(surf_n_turf);
    items.push_back(shrimp_trio);
    items.push_back(fish_seabass);
    items.push_back(fish_cohoSalmon);
    items.push_back(crab_blue);

    // side objects
    MenuItem greenBeans(501, 4.99, "green beans");
    MenuItem cinnamonApples(502, 4.99, "cinn apples");
    MenuItem frenchFries(503, 4.99, "french fries");
    MenuItem bakedPotato(504, 2.99, "baked potato");
    MenuItem coleSlaw(505, 3.99, "cole slaw");

    items.push_back(greenBeans);
    items.push_back(cinnamonApples);
    items.push_back(frenchFries);
    items.push_back(bakedPotato);
    items.push_back(coleSlaw);

    // dessert objects
    MenuItem tiramisu(601, 5.99, "tiramisu");
    MenuItem cake_chocolateLava(602, 5.99, "cake chocolate lava");
    MenuItem iceCream_rum(603, 5.99, "rum ice cream");
    MenuItem iceCream_vanilla(604, 5.99, "vanilla ice cream");
    MenuItem bananas_foster(605, 7.49, "bananas foster");

    items.push_back(tiramisu);
    items.push_back(cake_chocolateLava);
    items.push_back(iceCream_rum);
    items.push_back(iceCream_vanilla);
    items.push_back(bananas_foster);

    // kids menu objects
    MenuItem kids_hotDog(701, 4.49, "kids hotdog");
    MenuItem kids_hamburger(702, 4.49, "kids hamburger");
    MenuItem kids_chickenNuggets(703, 4.49, "kids chicken nuggets");
    MenuItem kids_macAndCheese(704, 4.49, "kids mac n cheese");

    items.push_back(kids_hotDog);
    items.push_back(kids_hamburger);
    items.push_back(kids_chickenNuggets);
    items.push_back(kids_macAndCheese);

    // drink objects
    MenuItem drink_cola(801, 1.99, "cola");
    MenuItem drink_sprite(802, 1.99, "sprite");
    MenuItem kids_rootBeer(803, 1.99, "root beer");
    MenuItem kids_drPepper(804, 1.99, "dr pepper");
    MenuItem kids_coffee(805, 1.99, "coffee");
    MenuItem kids_iceTea(806, 1.99, "ice tea");

    items.push_back(drink_cola);
    items.push_back(drink_sprite);
    items.push_back(kids_rootBeer);
    items.push_back(kids_drPepper);
    items.push_back(kids_coffee);
    items.push_back(kids_iceTea);

    // Just put all the menu items into a vector, and pass a pointer to this function
    fs->AddMenuItems(&items);
}

//this function creates Employee files
void createEmployees(FileSystem* fs){
    Employee num123 = Employee(123, "Danni");
    Employee num456 = Employee(456, "Freddy");
    Employee num789 = Employee(789, "Stephen");
    Employee num987 = Employee(987, "Debbie");
    Employee num654 = Employee(654, "Donny");
    Employee num321 = Employee(321, "Janet");
    fs->SaveEmployee(&num123);
    fs->SaveEmployee(&num456);
    fs->SaveEmployee(&num789);
    fs->SaveEmployee(&num987);
    fs->SaveEmployee(&num654);
    fs->SaveEmployee(&num321);
}
