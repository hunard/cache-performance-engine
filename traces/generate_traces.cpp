#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

void logAccess(std::ofstream& file, void* addr) {
    file << (uint64_t)addr << "\n";
}

void matrixMultiply(int size, std::ofstream& traceFile) {
    std::vector<std::vector<int>> A(size, std::vector<int>(size, 1));
    std::vector<std::vector<int>> B(size, std::vector<int>(size, 1));
    std::vector<std::vector<int>> C(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                logAccess(traceFile, &A[i][k]);
                logAccess(traceFile, &B[k][j]);
                logAccess(traceFile, &C[i][j]);
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void linkedListTraversal(int size, std::ofstream& traceFile) {
    struct Node {
        int value;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < size; i++) {
        Node* newNode = new Node{i, nullptr};
        if (!head) head = newNode;
        else tail->next = newNode;
        tail = newNode;
    }

    Node* current = head;
    while (current) {
        logAccess(traceFile, current);
        current = current->next;
    }

    current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int main() {
    std::ofstream matrixTrace("traces/matrix.trace");
    std::ofstream linkedListTrace("traces/linkedlist.trace");

    std::cout << "Generating matrix multiply trace..." << std::endl;
    matrixMultiply(64, matrixTrace);

    std::cout << "Generating linked list trace..." << std::endl;
    linkedListTraversal(1000, linkedListTrace);

    std::cout << "Done. Check traces/matrix.trace and traces/linkedlist.trace" << std::endl;
}
