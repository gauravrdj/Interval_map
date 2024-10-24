#include <bits/stdc++.h>
template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val
    template<typename V_forward>
    interval_map(V_forward&& val)
    : m_valBegin(std::forward<V_forward>(val))
    {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    template<typename V_forward>
    void assign( K const& keyBegin, K const& keyEnd, V_forward&& val )
        requires (std::is_same<std::remove_cvref_t<V_forward>, V>::value)
    {
        if(!(keyBegin < keyEnd)){
            return;
        }

        if(m_map.size() == 0){
            if(val != m_valBegin){
                m_map[keyBegin] = val;
                m_map[keyEnd] = m_valBegin;
            }
            return;
        }

        auto it_begin = m_map.lower_bound(keyBegin);
        auto it_end = m_map.lower_bound(keyEnd);

        V before_it_begin;
        if(it_begin == m_map.begin()){
            before_it_begin = m_valBegin;
        } else {
            auto temp = it_begin;
            before_it_begin = (*--temp).second;
        }

        V after_it_end;
        if(it_end == m_map.begin()){
            after_it_end = m_valBegin;
        } else if(it_end == m_map.end()){
            auto temp = m_map.end();
            after_it_end = (*--temp).second;
        } else {
            if((*it_end).first == keyEnd){
                after_it_end = (*it_end).second;
            } else {
                auto temp = it_end;
                after_it_end = (*--temp).second;
            }
        }

        m_map.erase(it_begin, it_end);

        if(before_it_begin != val){
            m_map[keyBegin] = val;
        }

        if(after_it_end == val){
            if(it_end != m_map.end() && (*it_end).first == keyEnd){
                m_map.erase(it_end);
            }
        } else {
            m_map[keyEnd] = after_it_end;
        }
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        auto it = m_map.upper_bound(key);
        if(it == m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }

    V const& getValue(K const& key) const {
        if(m_map.find(key) != m_map.end()) return m_map[key];
        auto it = m_map.lower_bound(key);
        if(it == m_map.begin()){
            return m_valBegin;
        } else {
            return (*--it).second;
        }
    }
};

// Randomized test function for interval_map
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        interval_map<int, char> Map('A');

        std::map<int, char> referenceMap;

        // Randomly generate startKey, endKey, and value
        int startKey = std::rand() % t;
        int endKey = startKey + std::rand() % 50;
        char value = static_cast<char>('A' + std::rand() % 26);

        // Perform the assignment in both the interval_map and referenceMap
        Map.assign(startKey, endKey, value);
        for (int key = startKey; key <= endKey; ++key) {
            referenceMap[key] = value;
        }

        // Compare the results of interval_map with the referenceMap
        // and print an error message if they differ
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
