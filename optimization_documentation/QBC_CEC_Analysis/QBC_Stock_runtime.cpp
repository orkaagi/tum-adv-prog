#include <vector>
#include <string>
#include <random>

class StockOld {
    private:
        std::string _name;
        double _ann_return;
        double _daily_mean_return;
        double _ann_volatility;
        double _daily_vol;

        int _risk_level;
        double _init_value;
        std::vector<double> _price_trend;
        std::normal_distribution<double> _dist;
    
    public:
        StockOld() {}
        
        StockOld(std::string name, double ann_return, double ann_volatility, int risk_level, double init_value, std::vector<double> price_trend)
            : _name(name), _ann_return(ann_return), _ann_volatility(ann_volatility), _risk_level(risk_level), _init_value(init_value), _price_trend(price_trend) {
            if (_price_trend.empty()) {
                _price_trend.push_back(_init_value);
            }
        }

        ~StockOld() {}

        void set_daily_mean_return() {
            _daily_mean_return = 2.00;
        }

        double daily_mean_return() {
            return _daily_mean_return;
        }
};

class StockNew {
    private:
        std::normal_distribution<double> _dist; // distribution member variable for simulator
        float _init_value;
        int _risk_level;
        float _ann_return;
        float _ann_volatility;
        float _daily_mean_return;  
        float _daily_vol;
                
        std::vector<float> _price_trend;        
        std::string _name;

    public:
        StockNew() {}
        
        StockNew(std::string name, float ann_return, float ann_volatility, int risk_level, float init_value, std::vector<float> price_trend)
            : _name(name), _ann_return(ann_return), _ann_volatility(ann_volatility), _risk_level(risk_level), _init_value(init_value), _price_trend(price_trend) {
            if (_price_trend.empty()) {
                _price_trend.push_back(_init_value);
            }
        }

        ~StockNew() {}

        void set_daily_mean_return() {
            _daily_mean_return = 2.00;
        }

        float daily_mean_return() {
            return _daily_mean_return;
        }
};

static void StockUnaligned(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<StockOld> stocks(100);

    for (auto && s : stocks){
        s.set_daily_mean_return();
    }
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(stocks);
  }
}
BENCHMARK(StockUnaligned);

static void StockAligned(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<StockNew> stocks(100);

    for (auto && s : stocks){
        s.set_daily_mean_return();
    }
    benchmark::DoNotOptimize(stocks);
  }
}
BENCHMARK(StockAligned);

