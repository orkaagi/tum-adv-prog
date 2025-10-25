#include "InputWallet.h"
#include "Wallet.h"

#include <unordered_map>

// General input validation function
double getValidInput(double min, double max) {
    double value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a value between " << min << " and " << max << ": ";
        } else {
            return value;
        }
    }
}

// Helper function to push a strategy
void pushStrategy(std::vector<Strategy>& strategies, const std::string& name, double low, double medium, double high) {
    Strategy strategy = Strategy(name, low, medium, high);
    strategies.push_back(strategy);
    std::cout << "Strategy added: " << name
              << " (Low: " << low << "%, Medium: " << medium << "%, High: " << high << "%)\n";
}

Strategy handleCategories(int counts[3]) {
    // Determine available risk categories
    std::vector<int> available_categories;
    std::cout << "\nAvailable categories:\n";
    for (size_t i{0}; i < 3; ++i) {
        if (counts[i] > 0) {
            available_categories.push_back(i + 1); // Map i to 1 (Low), 2 (Medium), 3 (High)
            std::cout << (i == 0 ? "Low" : (i == 1 ? "Medium" : "High")) << " risk\n";
        }
    }

    // Strategy selection
    std::cout << "\nChoose a strategy:\n";
    int choice;
    std::string strategy_name;
    double low = 0, medium = 0, high = 0;

    if (available_categories.size() == 1) {
        // Only Custom strategy is available
        std::cout << "Only Custom strategy is available.\n";
        choice = 4; // Automatically set choice to Custom
    } else {
        // Show available predefined strategies
        if (available_categories.size() == 2) {
            std::cout << "1. Conservative (80%-20%)\n";
            std::cout << "2. Balanced (50%-50%)\n";
            std::cout << "3. Aggressive (20%-80%)\n";
        } else if (available_categories.size() == 3) {
            std::cout << "1. Conservative (70%-20%-10%)\n";
            std::cout << "2. Balanced (30%-40%-30%)\n";
            std::cout << "3. Aggressive (10%-20%-70%)\n";
        }
        std::cout << "4. Custom\n";

        // Get user's choice between available options
        choice = static_cast<int>(getValidInput(1, 4));
    }

    if (choice == 4) {
        std::cout << "Enter a name for your custom strategy: ";
        std::cin >> strategy_name;

        // Custom strategy logic
        if (counts[0] > 0) {
            std::cout << "Enter percentage for low risk: ";
            low = getValidInput(0.0, 100.0);
        }
        if (counts[1] > 0) {
            std::cout << "Enter percentage for medium risk: ";
            medium = getValidInput(0.0, 100.0 - low);
        }
        if (counts[2] > 0) {
            std::cout << "Enter percentage for high risk: ";
            high = getValidInput(0.0,100.0 - low - medium);
        }
        
    } else {
        // Predefined strategies for two categories
        double allocation1 = 0.0, allocation2 = 0.0;
        if (choice == 1) { allocation1 = 80; allocation2 = 20; strategy_name="Conservative"; } 
        else if (choice == 2) { allocation1 = 50; allocation2 = 50; strategy_name="Balanced";}  
        else if (choice == 3) { allocation1 = 20; allocation2 = 80; strategy_name="Aggressive";}  

        // Map allocations to available categories
        if (available_categories[0] == 1 && available_categories[1] == 2) {
            // Low and Medium
            low = allocation1;
            medium = allocation2;
        } 
        else if (available_categories[0] == 1 && available_categories[1] == 3) {
            // Low and High
            low = allocation1;
            high = allocation2;
        } 
        else if (available_categories[0] == 2 && available_categories[1] == 3) {
            // Medium and High
            medium = allocation1;
            high = allocation2;
        }

        // Predefined strategies for three categories
        else if (available_categories.size() == 3) {
            if (choice == 1) { low = 70; medium = 20; high = 10; strategy_name="Conservative";  }
            else if (choice == 2) { low = 30; medium = 40; high = 30; strategy_name="Balanced";}
            else if (choice == 3) { low = 10; medium = 20; high = 70; strategy_name="Aggressive";}
        }
    }

    // Push the finalized strategy
    return Strategy(strategy_name, low, medium, high);
}

// Main function to create wallets
void createWallets(std::vector<Wallet>& wallets, int counts[3]) {
    if (counts[0] == 0 && counts[1] == 0 && counts[2] == 0) {
        std::cout << "No stocks available.\n";
        return;
    }

    std::string input;
    while (true) {
        // Input wallet ID
        std::cout << "Enter Wallet ID (int): ";
        int wallet_id;
        std::cin >> wallet_id;

        // Input initial investment
        std::cout << "Enter initial investment amount: ";
        double initial_investment = getValidInput(0.0, 1e6);

        // Create strategy for this wallet
        std::cout << "Creating strategy for Wallet ID: " << wallet_id << "...\n";
        Strategy strategy = handleCategories(counts);

        // Create and add wallet to the list
        Wallet wallet(wallet_id, initial_investment, strategy,std::unordered_map<std::string, double>());
        wallets.push_back(wallet);
        std::cout << "Wallet created successfully with strategy: " << strategy.name() << "!\n";

        // Option to create more wallets
        std::cout << "Press any key to create another wallet. Type 'no' to stop: ";
        std::cin >> input;
        if (input == "no") {
            break;
        }
    }
    //JUST TO CHECK IF WALLETS ARE BEING CREATED
    std::cout << "Wallet creation finished.\n"; // Debug statement
    // Output wallet details
    std::cout << "Wallets Information:\n";
    for (const Wallet& wallet : wallets) {
        std::cout << "Wallet ID: " << wallet.id() << "\n";
        std::cout << "Initial Investment: " << wallet.initial_investment() << "\n";
        std::cout << "Strategy: " << wallet.strategy().name() << "\n";
        /*
        std::cout << "Stock Shares:\n";
        for (const auto& stock_share : wallet.stock_shares()) {
            std::cout << "  " << stock_share.first << ": " << stock_share.second << "\n";
        }
        */
        std::cout << "--------------------------------------\n";
    }

}