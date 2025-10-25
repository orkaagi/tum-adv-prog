#include <vector>
#include <string>

class StrategyOld {
    private:
        std::string _name;
        double _low_risk_alloc;
        double _med_risk_alloc;
        double _high_risk_alloc;
    
    public:
        StrategyOld() {}

        StrategyOld(std::string name, double low_risk_alloc, double med_risk_alloc, double high_risk_alloc)
            : _name(name), _low_risk_alloc(low_risk_alloc), _med_risk_alloc(med_risk_alloc), _high_risk_alloc(high_risk_alloc) {}

        ~StrategyOld() {}
        
        double get_low_risk_allocation() {
            return _low_risk_alloc;
        }
};

class StrategyNew {
    private:
        std::string _name;
        float _low_risk_alloc;
        float _med_risk_alloc;
        float _high_risk_alloc;
    
    public:
        StrategyNew() {}

        StrategyNew(std::string name, float low_risk_alloc, float med_risk_alloc, float high_risk_alloc)
            : _name(name), _low_risk_alloc(low_risk_alloc), _med_risk_alloc(med_risk_alloc), _high_risk_alloc(high_risk_alloc) {}

        ~StrategyNew() {}
        
        float get_low_risk_allocation() {
            return _low_risk_alloc;
        }


};

static void StrategyUnaligned(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<StrategyOld> strategies(100);

    double foo{};
    for (auto && s : strategies){
        foo = s.get_low_risk_allocation();
    }
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(strategies);
  }
}
BENCHMARK(StrategyUnaligned);

static void StrategyAligned(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<StrategyNew> strategies(100);

    float foo{};
    for (auto && s : strategies){
        foo = s.get_low_risk_allocation();
    }
    benchmark::DoNotOptimize(strategies);
  }
}
BENCHMARK(StrategyAligned);
