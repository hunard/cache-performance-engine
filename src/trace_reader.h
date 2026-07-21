#pragma once
#include <string>
#include <fstream>
#include <cstdint>

class TraceReader {
public:
    TraceReader(const std::string& filename);
    bool nextAddress(uint64_t& address);
    bool isOpen();

private:
    std::ifstream file;
};