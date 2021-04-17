#include <iostream>
#include <unordered_map>

template<typename ProductType>
class ProductRegister;

template <typename ProductType>
class ProductFactory {
public:
    ProductFactory& instance() {
        static ProductFactory ins;
        return ins;
    }

    void register_product(ProductRegister<ProductType>* pregister,
            const std::string& name) {
        if (_product_map.find(name) == _product_map.end()) {
            _product_map[name] = pregister;
        }
    }

    ProductType* get_product(const std::string& name) {
        if (_product_map.find(name) != _product_map.end()) {
            return _product_map[name]->create_product();
        }
        return nullptr;
    }

private:
    ProductFactory() {}
    ~ProductFactory(){}
    ProductFactory(const ProductFactory&);
    ProductFactory& operator=(const ProductFactory&);
    std::unordered_map<std::string, ProductRegister<ProductType>> _product_map;
};

template <typename ProductType>
class ProductRegister {
public:
    explicit ProductRegister(std::string& name) {
        ProductFactory<ProductType>::instance().register_product(this, name);
    }

    ProductType* create_product(){
        return new ProductType();
    }
};
    
