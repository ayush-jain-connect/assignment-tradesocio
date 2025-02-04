#include <bits/stdc++.h>

using namespace std;

class Order {
private:
    int orderId;
    string symbol;
    string type;
    float orderPrice;
    int quantity;

public:
    Order(string symbol, string type, float orderPrice, int quantity, int orderId) {
        this->symbol = symbol;
        this->type = type;
        this->orderPrice = orderPrice;
        this->quantity = quantity;
        this->orderId = orderId;
    }

    int getOrderId() const {
        return orderId;
    }

    string getSymbol() const {
        return symbol;
    }

    string getType() const {
        return type;
    }

    float getOrderPrice() const {
        return orderPrice;
    }

    int getQuantity() const {
        return quantity;
    }
};

class Tick {
private:
    string symbol;
    float tickPrice;
    string timeStamp;

public:
    Tick(string symbol, float tickPrice, string timeStamp) {
        this->symbol = symbol;
        this->tickPrice = tickPrice;
        this->timeStamp = timeStamp;
    }

    string getSymbol() const {
        return symbol;
    }

    float getTickPrice() const {
        return tickPrice;
    }

    string getTimeStamp() const {
        return timeStamp;
    }
};

class TradingSystem {
private:
    unordered_map<string, priority_queue<Order>> buy_orders;
    int order_counter = 0;

public:
    void addOrder(string symbol, string type, float orderPrice, int quantity) {
        Order newOrder(symbol, type, orderPrice, quantity, order_counter++);
        buy_orders[symbol].push(newOrder);
    }

    void newTick(const Tick& tick) {
        string symbol = tick.getSymbol();
        float tickPrice = tick.getTickPrice();
        string timestamp = tick.getTimeStamp();

        if (buy_orders.find(symbol) == buy_orders.end()) 
            return;

        auto& pq = buy_orders[symbol];

        while (!pq.empty() && pq.top().getOrderPrice() >= tickPrice) {
            Order topOrder = pq.top();
            pq.pop();
            cout << "Order executed at " << timestamp
                 << ", Symbol: " << symbol
                 << ", Price: " << tickPrice
                 << ", Quantity: " << topOrder.getQuantity() << endl;
        }
    }
};

// Client Code
int main() {
    TradingSystem tradingSystem;

    tradingSystem.addOrder("AAPL", "BL", 100.0f, 10);
    tradingSystem.addOrder("AAPL", "BL", 105.0f, 5);
    tradingSystem.addOrder("AAPL", "BL", 102.0f, 15);
    tradingSystem.addOrder("AAPL", "BL", 98.0f, 15);
    tradingSystem.addOrder("GOOG", "BL", 200.0f, 10);
    tradingSystem.addOrder("GOOG", "BL", 201.0f, 15);
    tradingSystem.addOrder("GOOG", "BL", 198.0f, 10);

    tradingSystem.newTick(Tick("AAPL", 106.0f, "08:58"));
    tradingSystem.newTick(Tick("AAPL", 104.0f, "09:00"));
    tradingSystem.newTick(Tick("AAPL", 102.0f, "09:01"));
    tradingSystem.newTick(Tick("AAPL", 98.0f, "09:02"));
    tradingSystem.newTick(Tick("GOOG", 200.0f, "09:03"));

    return 0;
}
