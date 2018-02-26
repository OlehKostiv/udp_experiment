#pragma once
#include <iostream>
#include <string>

constexpr int port = 8888;

extern void ErrorMessage(const std::string& message, int error = 0, std::ostream& output = std::cerr);
