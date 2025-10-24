# Project: Simulate trading in a stock market
https://gitlab.lrz.de/tum-i05/public/advprog-project-ideas/-/blob/886c71ff5955d17b6a91760ea2ce5d04293c587c/Trading-stock-market-simulation/trading-market-simulation.md

Idea contributed by Andrea De Girolamo <andrea.de-girolamo@tum.de> and Michael Pio Basile <michael.basile@tum.de>.

## General project description

The goal of this project is to simulate the performance of certain portfolios in a simulated stock market. The whole project is divided into 2 simulations: the market simulation and the investor simulation. Later, it will be possible to create interactions between the simulations of the investors and the simulations of the market, therefore creating cause and effect relationships.


The market simulation will involve the creation of a stochastic process through a mathematical model, in which the performance of each share is represented by a pseudo-random function that evolves over time. The trend of the shares will be characterized by statistical parameters that will determine their volatility over time.

The investor simulation will involve the management of many stock wallets, with each wallet being able to follow investment 'strategies'. In the first phase, the market shares will be assigned at the beginning of the simulation and will stay in the assigned wallets until the end of the simulation. Later, the wallets will be able to buy and sell market shares during the simulation by following the selected 'strategies'.

## Sources

- To better understand what the topic is about: https://en.wikipedia.org/wiki/Stock_market_simulator
- To understand what risk management is and how to deal with it (Monte Carlo simulations, statistical parameters for shares): https://www.investopedia.com/risk-management-4689652

- If you want to know more about mathematics for finance, this is a basic book on it:
https://link.springer.com/chapter/10.1007%2F1-85233-846-6_1

## Sprint 1
In the first sprint, at the beginning of the simulation, the wallets will be initialized with a limited amount of market shares. The market will evolve and modify the amount of money in the wallets. In this phase, it will be possible to choose between two types of investment 'strategies', a low-risk/low-return strategy and a high-risk strategy with more chance of higher income.

### Definion of "done"
- User will be able to input:
    - funds to invest in the market
    - strategies (e.g. percentages of available funds used on different shares, the user can choose among different possibilities)
    - shares (e.g. array of strings representing the name of the company)
    - shares' statistical parameters (e.g. change in stock market, standard deviation of returns, expected return, all float/double numbers)


### ⚠️ Caution! For Group 80 ⚠️

We found that the **price change input** is unnecessary for our code, so we have decided to remove it.

### Updated Process:
1. **Inputs**:
  - initial fund (wallet initial value)
  - Stock's name
  - Stock's initial price
  - Stock's Annual return
  -  Stock's Annual variance

2. **User Interaction**:
  - The user selects a strategy.
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

Sample:
- one risk level stock available:
```
        Input:
        fund: 100
        
             stocks: a b c
        
             variance: 0.1 0.2 0.3
        
             expected_return: 1 1 1
        
             initial_value: 100 100 100
        
        WARNING: Only one risk level available!
        So all the stocks will be equally allocated.
        Do you want to enter another strategy (yes/stop)? stop
        Price trend for Stock a:
        First 10 prices: 100 100.328 100.683 101.098 101.461 101.843 102.31 102.737 103.106 103.558
        Last 10 prices: 264.463 265.54 266.493 267.891 268.844 269.847 270.931 271.872 272.888 274.215
        
        Simulation Results for Strategy: single_risk_level
        Initial Investment: $100
        Expected Portfolio Value after 1 year: $276.40
        Percentage change in portfolio value: 176.40%
        Allocation breakdown:
        a: 33.3%
        b: 33.3%
        c: 33.3%
        ----------------------------------------
        
        Process finished with exit code 0
```

- 2 risk level stock available:
```

    Input: 
        fund: 100

        stocks: a b c

        variance: 0.1 1.1 1.1

        expected_return: 1 1 1

        initial_value: 100 100 100

    Choose a strategy:
    1. Conservative (80-20)
    2. Balanced (50-50)
    3. Aggressive (20-80)
    4. Custom
    1
    Allocated 80% to first category, 20% to second category.
    Do you want to enter another strategy (yes/stop)? yes
    Choose a strategy:
    1. Conservative (80-20)
    2. Balanced (50-50)
    3. Aggressive (20-80)
    4. Custom
    2
    Allocated 50% to first category, 50% to second category.
    Do you want to enter another strategy (yes/stop)? stop
    Price trend for Stock a:
    First 10 prices: 100 100.414 100.848 101.186 101.375 101.731 102.047 102.49 102.922 103.291 
    Last 10 prices: 260.738 262.104 263.241 264.158 265.342 266.392 267.372 268.306 269.351 270.654 

    Simulation Results for Strategy: Conservative
    Initial Investment: $100
    Expected Portfolio Value after 1 year: $272.64
    Percentage change in portfolio value: 172.64%
    Allocation breakdown:
    a: 80.0%
    b: 10.0%
    c: 10.0%
    ----------------------------------------
    Price trend for Stock a:
    First 10 prices: 100.0 100.4 100.7 101.1 101.4 101.9 102.4 102.6 103.1 103.5 
    Last 10 prices: 261.7 262.7 263.9 265.1 266.3 267.2 268.3 269.2 270.2 271.4 

    Simulation Results for Strategy: Balanced
    Initial Investment: $100
    Expected Portfolio Value after 1 year: $273.97
    Percentage change in portfolio value: 173.97%
    Allocation breakdown:
    a: 50.0%
    b: 25.0%
    c: 25.0%
    ----------------------------------------

    Process finished with exit code 0


```
- 3 risk level stock available:

```
    Input: 
        fund: 100

        stocks: a b c

        variance: 0.1 1.1 2.1

        expected_return: 1 1 1

        initial_value: 100 100 100

    Choose a strategy:
    1. Conservative (70% low, 20% medium, 10% high)
    2. Balanced (30% low, 40% medium, 30% high)
    3. Aggressive (10% low, 20% medium, 70% high)
    4. Custom
    1
    Allocated 70% to low risk, 20% to medium risk, 10% to high risk.
    Do you want to enter another strategy (yes/stop)? yes
    Choose a strategy:
    1. Conservative (70% low, 20% medium, 10% high)
    2. Balanced (30% low, 40% medium, 30% high)
    3. Aggressive (10% low, 20% medium, 70% high)
    4. Custom
    2
    Allocated 30% to low risk, 40% to medium risk, 30% to high risk.
    Do you want to enter another strategy (yes/stop)? stop
    Price trend for Stock a:
    First 10 prices: 100 100.421 100.893 101.28 101.696 102.069 102.35 102.839 103.232 103.795 
    Last 10 prices: 261.708 262.681 263.758 264.881 265.644 266.837 268.248 269.085 270.119 271.043 

    Simulation Results for Strategy: Conservative
    Initial Investment: $100
    Expected Portfolio Value after 1 year: $273.45
    Percentage change in portfolio value: 173.45%
    Allocation breakdown:
    a: 70.0%
    b: 20.0%
    c: 10.0%
    ----------------------------------------
    Price trend for Stock a:
    First 10 prices: 100.0 100.5 100.9 101.3 101.6 102.0 102.5 103.0 103.3 103.8 
    Last 10 prices: 257.0 258.3 259.5 260.5 261.5 262.2 263.2 264.2 265.1 265.6 

    Simulation Results for Strategy: Balanced
    Initial Investment: $100
    Expected Portfolio Value after 1 year: $269.33
    Percentage change in portfolio value: 169.33%
    Allocation breakdown:
    a: 30.0%
    b: 40.0%
    c: 30.0%
    ----------------------------------------

    Process finished with exit code 0
    
```
---


#### Original example of input
    "input": {
        "fund": 1000000, // amount of money to invest for one wallet
        "strategies": 1, // option of multichoice menu for numbered strategies for one wallet
                         // A "strategy" is a procedure to distribute invested money (fund) on shares
                         // e.g. 50% on low-risk shares, 30% on mid-risk shares, 20% on high-risk shares
        "shares": ["Google", "Amazon", "Tesla", "Ferrero"], // array of strings, each string is the company to which the shares refer
        "variance": [3.1415927, 1.5707963, 6.2831853, 1.0471975], // statistical parameters for each share
        "price_change": [-4.27, 2.75, 0.23, 5.02], // statistical parameters for each share
        "expected_return": [0.10, 0.05, 0.2, 0.25], // statistical parameters for each share (percentage)
        "initial_value": [10.34, 1.92, 5.23, 4.01] // initial values of the shares
    }


- Output will be:
    - trends of the market shares (e.g. a float/double data structure which can register the fluctuations) at the end of the market simulation
    - funds available on the wallets, or percentage of income/loss, at the end of the wallet investments simulation

#### Original example of output
    "output": {
        "trend_google": [10.34, 9.84, 11.05, 13.22, 25.85, ...], // trends for each share
        "trend_amazon": [1.92, 1.89, 1.85, 1.95, 1.99, ...], // trends for each share
        "trend_tesla": [5.23, 25.23, 24.78, 17.12, 4.56, ...], // trends for each share
        "trend_ferrero": [4.01, 4.02, 4.04, 4.51, 5.01, ...], // trends for each share
        ...,
        "final_funds": 1014593.52 // final amount of money in the wallet
                                  // alternatively: "income": 0.23, percentage of income at the end of the simulation
    }

## Sprint 2
The objective of the second sprint is, thanks to the use of object-oriented programming, to create different classes for shares, wallets, strategies.Through this code refactoring, it will be possible to create interactions between the market simulation and the wallets simulation. A massive shares purchase in the market will consequentially change the value of the shares themselves. The statistical data concerning the recent market fluctuations and the quotes will be registered, and they can be utilized in the single investment strategies.

### Definition of "done"
- The market model and the investment model were successfully converted to object-oriented models

#### Example of possible class implementation

    "Share": {
        "name": "string",
        "startValue": "initial_market_value",
        "variance": "statParam1",
        "price_change": "statParam2",
        "expected_return": "statParam3"
    }

    "Wallet": {
        "name": "string",
        "funds": "float",
        "shares": "array(int)",
        "strategy": "int".
    }

    "Strategy": {
        "id": "int",
        "fppsr": "array(double)" //fppsr = funding percentage per share risk
    }

- The simulations were correctly interconnected, i.e., there is a cause-effect relationship between purchases and market values: for example, if many wallets buy the same share, this share is affected by this in the form of a rise in its value.

This can be done, for example, by inserting as input of the simulation a new object with information on the number of purchases for each share, and using this information to modify the fluctuations of the shares.



## Sprint 3
In the final sprint, the code performance will be evaluated and improved. To do this, bulk tests will be executed. Finding potential bottlenecks and investigating optimization options for the code, including loop transformations, STL containers, vectorization options and complexity analysis to find potential improvements will also be part of this sprint.

### Definition of "done"
- A file `performance.md` presents the observations from the performance analysis
- The same file presents at least one different optimization technique you applied, with the observable performance effects.

