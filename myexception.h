#pragma once

#include <string>
#include <exception>

class ValidationException : public std::exception
{
private:
    std::string message;

public:
    explicit ValidationException(const std::string& msg) : message(msg) {}

    // Override what() to provide custom error message
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};


class RepoException : public std::exception
{
private:
    std::string message;

public:
    explicit RepoException(const std::string& msg) : message(msg) {}

    // Override what() to provide custom error message
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};


class UndoException : public std::exception
{
private:
    std::string message;

public:
    explicit UndoException(const std::string& msg) : message(msg) {}

    // Override what() to provide custom error message
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};


class SkillDiffLRatioException : public std::exception
{
private:
    std::string message;

public:
    explicit SkillDiffLRatioException(const std::string& msg) : message(msg) {}

    // Override what() to provide custom error message
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};
