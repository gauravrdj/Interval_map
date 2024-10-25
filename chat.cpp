#include <bits/stdc++.h>

template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val
    template<typename V_forward>
    interval_map(V_forward&& val)
        : m_valBegin(std::forward<V_forward>(val)) {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    template<typename V_forward>
    void assign(const K& keyBegin, const K& keyEnd, V_forward&& val) {
        if (!(keyBegin < keyEnd)) {
            return;
        }
        if (m_map.empty()) {
            if (val != m_valBegin) {
                m_map[keyBegin] = val;
                m_map[keyEnd] = m_valBegin;
            }
            return;
        }

        auto it_begin = m_map.lower_bound(keyBegin);
        auto it_end = m_map.lower_bound(keyEnd);

        V before_it_begin = (it_begin == m_map.begin()) ? m_valBegin : std::prev(it_begin)->second;
        V after_it_end = (it_end == m_map.end()) ? m_valBegin : ((it_end != m_map.begin() && std::prev(it_end)->first == keyEnd) ? it_end->second : std::prev(it_end)->second);

        m_map.erase(it_begin, it_end);

        if (before_it_begin != val) {
            m_map[keyBegin] = val;
        }

        if (after_it_end != val) {
            m_map[keyEnd] = after_it_end;
        } else if (it_end != m_map.end() && it_end->first == keyEnd) {
            m_map.erase(it_end);
        }
    }

    // look-up of the value associated with key
    V const& operator[](const K& key) const {
        auto it = m_map.upper_bound(key);
        return (it == m_map.begin()) ? m_valBegin : std::prev(it)->second;
    }

    // Corrected getValue function
    V const& getValue(const K& key) const {
       if(m_map.find(key)!=m_map.end()){
        auto it = m_map.lower_bound(key);
        return (it)->second;
       }
    auto it = m_map.lower_bound(key);
    if(it==m_map.begin()){
        return m_valBegin;
    }
    else{
        return std::prev(it)->second;
    }
    }
};

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        interval_map<int, char> Map('A');
        std::map<int, char> referenceMap;

        int startKey = std::rand() % t;
        int endKey = startKey + std::rand() % 50;
        char value = static_cast<char>('A' + std::rand() % 26);

        Map.assign(startKey, endKey, value);
        for (int key = startKey; key < endKey; ++key) {
            referenceMap[key] = value;
        }

        for (const auto& entry : referenceMap) {
            int key = entry.first;
            char expectedValue = entry.second;
            char actualValue = Map.getValue(key);

            if (actualValue != expectedValue) {
                std::cout << "Test " << i << " failed: Key " << key << ", Expected " << expectedValue << ", Actual " << actualValue << std::endl;
            }
        }
    }
    std::cout << "Randomized test completed." << std::endl;
}
