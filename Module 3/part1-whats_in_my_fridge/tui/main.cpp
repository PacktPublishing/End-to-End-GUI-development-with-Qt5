// tui/main.cpp
#include <QCoreApplication>
#include <QTextStream>

#include "../entities/grocery_items.h"
#include "../repositories/grocery_items_repo_dummy.h"
#include "../usecases/check_available_groceries/check_available_groceries.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto groceryItems = new entities::GroceryItems(&a);
    auto groceryItemsRepoDummy = new repositories::GroceryItemsRepoDummy(&a);
    auto checkAvailableGroceries = new usecases::CheckAvailableGroceries(groceryItems, &a);

    groceryItems->setRepository(groceryItemsRepoDummy);

    QTextStream cout(stdout);

    QObject::connect(checkAvailableGroceries, &usecases::CheckAvailableGroceries::success,
                     [&cout, groceryItems](QString message) {
        cout << message << endl;
        for (auto item : groceryItems->list())
            cout << item.toMap().value("name").toString() << endl;
    });

    (cout << "Enter action: ").flush();

    QTextStream cin(stdin);
    QString action(cin.readLine());

    if (action == "check available groceries") {
        checkAvailableGroceries->run();
        a.exit(0);
    } else {
        cout << "Action not supported" << endl;
        a.exit(1);
    }
}
