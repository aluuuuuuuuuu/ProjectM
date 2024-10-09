#pragma once

// クラスをシングルトンパターンで実装するテンプレート
template<typename T>
class Singleton 
{
public:

    // インスタンスを提供する
    static T& getInstance() {
        static T instance;
        return instance;
    }

protected:
    
    // インスタンスのコピーを制限する
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    // コンストラクタとデストラクタの外からのアクセスを制限する
    Singleton() {}
    ~Singleton() {}
};