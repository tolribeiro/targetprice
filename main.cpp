#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <regex>

using namespace std;

unordered_multimap<string, string> priceToTitle;
unordered_multimap<string, string> priceToID;
vector<float> prices;
float targetPrice;
string fileName;
string targetPriceString;
bool foundCombination;
int option;

// calculates sum of values from partial array
float calculatePartialTotal(vector<float> partialMenu)
{
    float partialTotal = 0;
    for (float partialElement : partialMenu) {
        partialTotal += partialElement;
    }
    return partialTotal;
}

// prints the combination that sums up to a targetPrice
void printPartialMenuItems(vector<float> partialMenu, float targetPrice)
{
    cout << "Option " << option+1 << ":" << "\n";
    cout << "-----------\n";
    
    for (float partialItem : partialMenu)
    {
        // fixing decimal precision for float value
        stringstream stream;
        stream << fixed << setprecision(2) << partialItem;
        string par = stream.str();
        
        auto searchID = priceToID.find(par);
        string idProduct;
        
        // getting productID based on price
        if(searchID != priceToID.end()) {
            idProduct = searchID->second;
        }
        
        auto searchTitle = priceToTitle.find(idProduct);
        
        // print name of the product based on ID
        if(searchTitle != priceToTitle.end()) {
            cout << searchTitle->second << " - " << "$" << par << "\n";
        }
        
        foundCombination = true;
    }
    cout << "-----------\n";
    cout << "Total: $" << targetPrice << "\n" << endl;
    option++;
}

// recursive function that goes through items trying to find targetprice combination
void calculatePartialTotalFromSubset(vector<float> menuItems, float targetPrice, vector<float> partialMenu)
{
    // calculates the sum
    float partialTotal = calculatePartialTotal(partialMenu);
    
    // prints one combination if found
    if(partialTotal == targetPrice) {
        printPartialMenuItems(partialMenu, targetPrice);
    }
    
    // criteira to stop calling function: found sum greater or equals target
    if(partialTotal >= targetPrice)
        return;
    
    float item;
    
    for (int i = 0; i < menuItems.size(); ++i) {
        item = menuItems[i];
        vector<float> remainingItems;
        for(int j = i; j < menuItems.size(); ++j) {
            if(menuItems[j] == menuItems[i]) continue;
            remainingItems.push_back(menuItems[j]);
        }
        vector<float> partialTmp = partialMenu;
        partialTmp.push_back(item);
        calculatePartialTotalFromSubset(remainingItems, targetPrice, partialTmp);
    }
}

void calculateTargetFromMenu(vector<float> menuItems, float targetPrice)
{
    calculatePartialTotalFromSubset(menuItems, targetPrice, vector<float>());
}

void createMenuFromCSV(string fileName)
{
    string line;
    ifstream csvFile (fileName);
    
    int i = 0;
    if (csvFile.is_open()) {
        while ( getline (csvFile, line))
        {
            // line format as specified
            regex input ("[a-zA-Z ]+\\,\\$[0-9]+\\.[0-9][0-9]");
            if (line != "") {
                if (!regex_match(line, input)) {
                    cout << "Error: please enter product title and price correctly (Ex.: banana,$81.49).\n";
                    exit(1);
                } else {
                    size_t found = line.find(",");
                    string price = line.substr (found+1);
                    price = price.substr(1);
                    if (!i) {
                        targetPrice = stof(price);
                    } else {
                        string title = line.substr(0, found);
                        prices.push_back(stof(price));
                        priceToTitle.emplace(to_string(i), title);
                        priceToID.emplace(price, to_string(i));
                    }
                    ++i;
                }
            }
            
        }
        csvFile.close();
    } else {
        cout << "Error: could not open file.\n";
        exit(1);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Error: please use <program> <fileName>.\n";
    } else {
        fileName = argv[1];
        createMenuFromCSV(fileName);
        calculateTargetFromMenu(prices, targetPrice);
        if (!foundCombination) {
            cout << "There is no combination of dishes that is equal to target price.\n";
            exit(1);
        }
    }
    
    return 0;
}
