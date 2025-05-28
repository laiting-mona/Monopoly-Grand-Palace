/**
 * @file SingletonManager.hpp
 * @brief SingletonManager �u�����O�A�Ω�Τ@�޲z��Ҫ��󪺾P���C
 */
#ifndef SINGLETON_MANAGER_HPP
#define SINGLETON_MANAGER_HPP

#include <functional>
#include <vector>

 /**
  * @brief Utility class to register and invoke destructors for singleton instances.
  */
class SingletonManager {
private:
    static std::vector<std::function<void()>> destructors; ///< List of destructor callbacks

public:
    /**
     * @brief Register a destructor function for a singleton object.
     * @param destructor A no-argument function that destroys a singleton.
     */
    static void registerDestructor(std::function<void()> destructor);

    /**
     * @brief Call all registered destructors and clear them (typically at program termination).
     */
    static void destroyAll();
};

#endif // SINGLETON_MANAGER_HPP