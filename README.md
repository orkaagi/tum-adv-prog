# Stock market simulation by Group 80

## Acknowledgements
Team members: Liming, Sadhanna, Agi

## Sprint 3 optimizations
See the detailed documentation of the optimizations
- [Performance.md](performance.md)
- [Optimization.md](optimization.md)
- [Profiling with gprof](optimization_documentation/gprof_Analysis/Profiling_with_gprof.md)

## Short Description

The goal of this project is to **simulate trading in a stock market** by simulating the performance of certain portfolios.

- The simulation involves the management of many stock wallets, with each wallet being able to follow investment 'strategies'. 
- User input the stock properties (name, variance, expected return, initial value) and the initial fund for each wallet.Or read the stock properties from a CSV file.
- User input the initial fund for each wallet and choose or create a strategy for each wallet.
- The wallets buy shares of the stocks on the first day of the simulation, based on the strategy chosen.
- Then the simulator will simulate the performance of the wallets over a year, using a Monte Carlo simulation.
- The stock's volatility will increase due to the shares purchased by wallets on day 1, as these purchases will impact the market's performance.

___for debug purposes, the monto carlo simulation is using a fixed seed, so the results are reproducible.___

- See [the detailed project description here](trading-market-simulation.md).



## Usage

The project includes a _CMakeLists.txt_ in the root of the project, so you can use **CMake to build the project** using the following commands:
```bash
cmake .
make
```

The user can decide whether he/she wants to input the fund and the stock properties (name, variance, expected return, initial value) manually or wants to use those already saved in CSV files under the data folder.

If you want to **input stocks through the command line**, run the program using the following command:
```bash
./group_80
```
If you want to **use the data defined in CSV files**, run the program using the following command:

```bash
./group_80 CSV
```

When the program is running, after optionally inputing stocks, follow the prompts to **input parameters** as well.

After defining the strategies you'll **see the simulation results for each wallet** as an output.


1. **Inputs**:
- Stock's name
- Stock's initial price
- Stock's Annual return
- Stock's Annual variance

2. **User Interaction**:
- The user inputs the initial wallet fund.
- The user selects a strategy or creates a new one.
- Corresponding allocations are set based on the stock's risk level.
> **Explanation**:
> - **Initial Wallet**: $1000 initial money in the wallet.
    >   - **Strategy**:
          >     - `{0.70, 0.20, 0.10}` → **Conservative**
          >       - Allocation: LowRisk (70%), MidRisk (20%), HighRisk (10%).
          >     - **Example Allocation**:
                  >       - $700 → LowRisk
                  >       - $200 → MidRisk
>       - $100 → HighRisk
>   - **Stock Allocation**:
      >     - The stocks are equally allocated within each risk level.
      >     - Example:
              >       - If there are two low-risk stocks:
              >         - Stock A (LowRisk), Stock B (LowRisk).
              >         - Each gets 50% of the 70% allocated to low-risk stocks.
>         - \$350 → Stock A, \$350 → Stock B.

3. **Simulation**:
- Perform a Monte Carlo simulation:
    - Simulate the total wallet value over **255 days** for each stock.
    - Repeat the simulation **1000 times**.
- Results show the wallet(portfolio)'s performance after **1 year**.

### Sample:
Input
```
 Fund: amount of money to invest for one wallet. Must be an integer, formatted without colons or spaces, between 0 and 1
e+06:.
 Stocks: an array of strings separated by spaces and terminated by a new line character. Each string is the name of the
company to which the stock refers.
 Variance: statistical parameter for each share. Input as many doubles as the number of stocks. Input doubles must be se
parated by spaces and terminated by a newline character.
 Expected_return: statistical parameter for each share (percentage). Input as many doubles as the number of stocks. Inpu
t doubles must be separated by spaces and terminated by a newline character.
 Initial_value: initial values of the shares. Input as many doubles as the number of stocks. Input doubles must be separ
ated by spaces and terminated by a newline character.

Input:
         stocks:A B C


         variance:0.1 0.6 0.9


         expected_return:0.01 0.1 0.5


         initial_value:100 20 30


Enter Wallet ID:1

Enter initial investment amount:1000

Creating strategy for Wallet ID: 1...

Available categories:
Medium risk
High risk

Choose a strategy:
1. Conservative (80%-20%)
2. Balanced (50%-50%)
3. Aggressive (20%-80%)
4. Custom
1

Wallet created successfully with strategy: Conservative!
Press any key to create another wallet. Type 'no' to stop:q

Enter Wallet ID:2

Enter initial investment amount:10005

Creating strategy for Wallet ID: 2...

Available categories:
Medium risk
High risk

Choose a strategy:
1. Conservative (80%-20%)
2. Balanced (50%-50%)
3. Aggressive (20%-80%)
4. Custom
3

Wallet created successfully with strategy: Aggressive!
Press any key to create another wallet. Type 'no' to stop:no
```

Output

    ```
    Wallet creation finished.
    Wallets Information:
    Wallet ID: 1
    Initial Investment: 1000
    Strategy: Conservative
    --------------------------------------
    Wallet ID: 2
    Initial Investment: 10005
    Strategy: Aggressive
    --------------------------------------
    2
    Simulation Results for Wallet: 1
    ----------------------------------------
    Initial Investment: $1000
    Expected Portfolio Value after 1 year: $1066.89
    Percentage change in portfolio value: 6.69%
    Allocation breakdown:
    A: 80.0%
    B: 10.0%
    C: 10.0%
    ----------------------------------------
    
    Simulation Results for Wallet: 2
    ----------------------------------------
    Initial Investment: $10005.0
    Expected Portfolio Value after 1 year: $12766.17
    Percentage change in portfolio value: 27.60%
    Allocation breakdown:
    A: 20.0%
    B: 40.0%
    C: 40.0%
    ----------------------------------------
    
    Process finished with exit code 0
    
    


## Appendix for Interaction Between Total Stock Shares Bought by Wallets and the Volatility of Individual Stocks"

Sample Test
Input:

    Input: 
         stocks: A 
    
         variance: 0.1
    
         expected_return: 0.1
    
         initial_value: 11
    
    Enter Wallet ID: 1
    Enter initial investment amount: 100
    Creating strategy for Wallet ID: 1...
    
    Available categories:
    Medium risk
    
    Choose a strategy:
    Only Custom strategy is available.
    Enter a name for your custom strategy: Custom
    Enter percentage for medium risk: 100
    Wallet created successfully with strategy: Custom!
    Press any key to create another wallet. Type 'no' to stop: no

Result:
the Stock A's volatility will change from 0.31622776601683794 to 0.38932808094588428

since the wallet bought ~9.09 shares of stock A on day 1.
