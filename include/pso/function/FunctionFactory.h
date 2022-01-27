#pragma once

#include <pso/function/Function.h>

#include <memory>

/**
 * Factory pattern for creating function instances
 */
class FunctionFactory {
public:
    FunctionFactory() = delete;

    /**
     * Get function name and return function instance
     * @param functionName
     * @return
     */
    static std::shared_ptr<Function> makeFunction(const std::string &functionName);
};