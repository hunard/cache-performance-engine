#include "trace_reader.h"

TraceReader::TraceReader(const std::string& filename) {
    file.open(filename);
}

bool TraceReader::isOpen() {
    return file.is_open();
}

bool TraceReader::nextAddress(uint64_t& address) {
    return (bool)(file >> address);
}