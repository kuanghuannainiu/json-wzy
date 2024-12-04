#include <vector>
#include <map>
#ifndef _WZY_JSON_
#define _WZY_JSON_

namespace wzy{
namespace json{

class Json{
public:

    //固定的类型处理，在编译时期就检查。提前发现错误
    enum Type{
        json_null = 0,
        json_int,
        json_double,
        json_bool,
        json_object,
        json_string,
        json_array
    }
    Json();
    Json(int value);
    Json(double value);
    Json(bool value);
    Json(const char *value);        //C风格字符串
    Json(const string &value);      //C++风格字符串
    Json(Type type);                //通过类型构造
    Json(const Json &other);

    //原本没有const
    operator bool() const;
    operator int() const;
    operator double() const;
    operator string() const;

    Json& operator [](int index);
    void append(const Josn &other);

    string str() const;

    Json& operator [](const char *key);
    Json& operator [](const string &key);
private:
    /*
    使用指针:
        简化内存。联合体不需要直接存储这些数据
        灵活性更高，Json数据有可能变化，使用指针允许数据允许时
    */
    union Value{
        bool m_bool;
        int m_int;
        double m_double;
        std::string *m_string;
        std::vector<Json> *m_array;
        std::map<string, Json> *m_object;
    }
    Type m_type;
    Value m_value;
};

}   //namespace json
}   //namespace wzy

#endif

