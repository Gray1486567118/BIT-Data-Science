#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const double PI = 3.14159265358979323846;
const int INF = 0x3f3f3f3f;
const int N = 10001;
const int MOD = 10000000;



struct Order
{
    int orderId;
    int stockId;
    float price;
    int quantity;
    char type;
    Order* next;

    Order (int id, int stock, float pr, int qty, char t):
        orderId(id), stockId(stock), price(pr), quantity(qty), type(t), next(nullptr) {}
    // default
    Order(): orderId(0), stockId(0), price(0.0), quantity(0), type('B'), next(nullptr) {}
};


class OrderList {
public:
    Order* head;

    OrderList(): head(nullptr) {}

    bool compare(Order* a, Order* b) {
        if (a->type == 'b') {
            return a->price > b->price;
        } else {
            return a->price < b->price;
        }
    }

    void insertOrder(Order* newOrder) {
        if (!head || compare(newOrder, head)) {
            newOrder->next = head;
            head = newOrder;
        } else {
            Order* curr = head;
            while (curr->next && !compare(newOrder, curr->next)) {
                curr = curr->next;
            }
            newOrder->next = curr->next;
            curr->next = newOrder;
        }
    }

    void searchOrder(const string& typeName, OrderList& list, int stock) {
        cout << typeName << " orders:" << endl;
        if (!list.head) return;

        Order* curr = list.head;
        while (curr) {
            if (curr->stockId == stock) {
                cout << "orderid: " << setw(4) << setfill('0') << curr->orderId
                 << ", stockid:" << setw(4) << setfill('0') << curr->stockId
                 << ", price: "  << setw(6) << fixed << setfill(' ') << setprecision(1) << curr->price
                 << ", quantity: " << setw(4) << curr->quantity
                 << ", b/s: " << curr->type << endl;
            }
            curr = curr->next;
        }
    }

    bool cancelOrder(int OrderId, Order& canceledOrder) {
        Order* curr = head;
        Order* prev = nullptr;
        while (curr) {
            if (curr->orderId == OrderId) {
                canceledOrder = *curr;
                if (prev) {
                    prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }
};


int orderCount = 1;


void matchOrder(OrderList& buyList, OrderList& sellList, Order* newOrder);
void deleteZero(Order* order, OrderList& orderlist);



int main() {
    OrderList buyList, sellList;

    while (true) {
        int command;
        cin >> command;

        if (command == 0) break;

        if (command == 1) {
            int stockId, quantity;
            float price;
            char type;
            cin >> stockId >> price >> quantity >> type;

            Order* newOrder = new Order(orderCount++, stockId, price, quantity, type);
            cout << "orderid: " << setw(4) << setfill('0') << newOrder->orderId << endl;

            // 不交易0股
            if (quantity > 0) {
                if (type == 'b') {
                    buyList.insertOrder(newOrder);
                } else {
                    sellList.insertOrder(newOrder);
                }
                matchOrder(buyList, sellList, newOrder);
            } else {
                delete newOrder;
            }
        } else if (command == 2) {
            int stockId;
            cin >> stockId;

            buyList.searchOrder("buy", buyList, stockId);
            sellList.searchOrder("sell", sellList, stockId);
        } else if (command == 3) {
            int orderId;
            cin >> orderId;

            Order canceledOrder;

            if (buyList.cancelOrder(orderId, canceledOrder) || sellList.cancelOrder(orderId, canceledOrder)) {
                cout << "deleted order:orderid: " << setw(4) << setfill('0') << orderId 
                     << ", stockid:" << setw(4) << setfill('0') << canceledOrder.stockId 
                     << ", price: "  << setw(6) << fixed << setfill(' ') << setprecision(1) << canceledOrder.price
                     << ", quantity: " << setw(4) << canceledOrder.quantity 
                     << ", b/s: " << canceledOrder.type << endl;
            } else {
                cout << "not found" << endl;
            }
        }
    }
    return 0;
}



void matchOrder(OrderList& buyList, OrderList& sellList, Order* newOrder) {
    if (newOrder->type == 'b') {
        // buy order
        while (sellList.head) {
            Order* sellcurr = sellList.head;
            Order* sellprev = nullptr;
            Order* sellOrder = nullptr;

            while (sellcurr) {
                if (sellcurr->stockId == newOrder->stockId && sellcurr->price <= newOrder->price) {
                    if (!sellOrder) {
                        sellOrder = sellcurr;
                    } else {
                        if (sellcurr->price < sellOrder->price) {
                            sellOrder = sellcurr;
                        }
                    }
                }

                sellprev = sellcurr;
                sellcurr = sellcurr->next;
            }

            if (!sellOrder) break;  // no matched order

            // deal price & quantity
            float dealPrice = 0.5 * (newOrder->price + sellOrder->price);
            int dealQuantity = min(newOrder->quantity, sellOrder->quantity);

            newOrder->quantity -= dealQuantity;
            sellOrder->quantity -= dealQuantity;

            // output
            cout << "deal--price: " << setw(5) << fixed << setfill(' ') << setprecision(1) << dealPrice
                 << "  quantity:" << setw(4) << dealQuantity
                 << "  buyorder:" << setw(4) << setfill('0') << newOrder->orderId
                 << "  sellorder:" << setw(4) << setfill('0') << sellOrder->orderId << endl;

            if (sellOrder->quantity == 0) {
                deleteZero(sellOrder, sellList);
            }

            if (newOrder->quantity == 0) {
                deleteZero(newOrder, buyList);
                break;
            }
        }
    } else {
        // sell order
        while (buyList.head) {
            Order* buycurr = buyList.head;
            Order* buyprev = nullptr;
            Order* buyOrder = nullptr;

            while (buycurr) {
                if (buycurr->stockId == newOrder->stockId && buycurr->price >= newOrder->price) {
                    if (!buyOrder) {
                        buyOrder = buycurr;
                    } else {
                        if (buycurr->price > buyOrder->price) {
                            buyOrder = buycurr;
                        }
                    }
                }

                buyprev = buycurr;
                buycurr = buycurr->next;
            }

            if (!buyOrder) break;  // no matched order

            // deal price & quantity
            float dealPrice = (newOrder->price + buyOrder->price) / 2;
            int dealQuantity = min(newOrder->quantity, buyOrder->quantity);

            newOrder->quantity -= dealQuantity;
            buyOrder->quantity -= dealQuantity;

            // output
            cout << "deal--price: " << setw(5) << fixed << setfill(' ') << setprecision(1) << dealPrice
                 << "  quantity:" << setw(4) << dealQuantity
                 << "  sellorder:" << setw(4) << setfill('0') << newOrder->orderId
                 << "  buyorder:" << setw(4) << setfill('0') << buyOrder->orderId << endl;

            if (buyOrder->quantity == 0) {
                deleteZero(buyOrder, buyList);
            }

            if (newOrder->quantity == 0) {
                deleteZero(newOrder, sellList);
                break;
            }
        }
    }
}


void deleteZero(Order* order, OrderList& orderlist) {
    if (orderlist.head == order) {
        // 删除头节点
        orderlist.head = order->next;
    } else {
        // 删除中间或尾节点
        Order* temp = orderlist.head;
        Order* prev = nullptr;

        while (temp != order) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
    }
    delete order;
}
