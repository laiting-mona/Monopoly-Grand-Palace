/**
 * @file Error.hpp
 * @brief 錯誤處理模組，定義未實作功能的例外類別。
 */
#ifndef _ERROR_H_
#define _ERROR_H_

#include <exception>
#include <string>

 /**
  * @brief Exception class indicating a function is not yet implemented.
  */
class NotImplement : public std::exception {
private:
    std::string message; ///< Error message describing the unimplemented feature

public:
    /**
     * @brief Construct a NotImplement exception with a message.
     * @param msg Description of the unimplemented feature.
     */
    inline NotImplement(std::string&& msg) : message(msg) {}

    /**
     * @brief Get the error message.
     * @return C-string pointing to the error message.
     */
    inline const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // _ERROR_H_