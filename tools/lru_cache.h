#include <list>
#include <map>
#include <mutex>
#include <unordered_map>

template <typename KeyType, typename ValueType>
class LruCache {
public:
    LruCache(const LruCache&) = delete;
    LruCache& operator=(const LruCache&) = delete;

    explicit LruCache(size_t capacity);
    ~LruCache();

    // get the value of key from the cache
    // update the cache
    // return nullptr if no value found
    bool get(const KeyType& key, ValueType* value);

    // get the value from the cache
    // if not exist, return default_value
    ValueType get_or_default(const KeyType& key,
            const ValueType& default_value = ValueType());

    // save value in cache
    // if the key already exist, old value will by replaced by new one
    void put(const KeyType& key, const ValueType& value);

    // remove by key
    // if not exists, return false
    // otherwise, return true
    bool remove(const KeyType& key) {
        std::unique_lock<std::mutex> lock(_mutex);
        return internal_remove(key);
    }

    // if key exists, return true
    // otherwise, return false
    bool has_key(const KeyType& key) const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _index.find(key) != _index.end();
    }

    //clear all value
    void clear();

    size_t size() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _value_list.size();
    }

    size_t capacity() const {
        return _capacity;
    }

    bool is_empty() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _value_list.empty();
    }

    bool is_full() const {
        std::unique_lock<std::mutex> _lock(_mutex);
        return _index.size() == _capacity;
    }

private:
    bool internal_remove(const KeyType& key);

private:
    typedef std::list<std::pair<KeyType, ValueType>> List;
    List _value_list;
    std::unordered_map<KeyType, typename List::iterator> _index;
    size_t _capacity;
    std::mutex _mutex;
};

template <typename KeyType, typename ValueType>
LruCache<KeyType, ValueType>::LruCache(size_t capacity)
    : _capacity(capacity) {
    }

template <typename KeyType, typename ValueType>
LruCache<KeyType, ValueType>::~LruCache() {
    clear();
}

template <typename KeyType, typename ValueType>
bool LruCache<KeyType, ValueType>::get(const KeyType& key, ValueType* value) {
    std::unique_lock<std::mutex> lock(_mutex);

    auto iter = _index.find(key);
    if (iter != _index.end()) {
        _value_list.splice(_value_list.begin(), _value_list, iter->second);
        iter->second = _value_list.begin();
        *value = iter->second->second;
        return true;
    }
    return false;
}

template <typename KeyType, typename ValueType>
ValueType LruCache<KeyType, ValueType>::get_or_default(const KeyType& key,
        const ValueType& default_value) {
    ValueType value;
    if (get(key, &value)) {
        return value;
    }
    return default_value;
}

template <typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) {
    std::unique_lock<std::mutex> lock(_mutex);
    auto iter = _index.find(key);
    if (iter != _index.end()) {
        if (iter->second->second == value) {
            return;
        }
        internal_remove(key);
    }

    _value_list.push_front(std::make_pair(key, value));

    auto list_iter = _value_list.begin();
    _index[key] = list_iter;

    if (_index.size() > _capacity) {
        list_iter = _value_list.end();
        --iter;
        internal_remove(list_iter->first);
    }
}

template <typename KeyType, typename ValueType>
bool LruCache<KeyType, ValueType>::internal_remove(const KeyType& key) {
    auto iter = _index.find(key);
    if (iter == _index.end()) {
        return false;
    }

    _value_list.erase(iter->second);
    _index.erase(iter);
    return true;
}

template <typename KeyType, typename ValueType>
void LruCache<KeyType, ValueType>::clear() {
    std::unique_lock<std::mutex> lock(_mutex);
    _value_list.clear();
    _index.clear();
}



