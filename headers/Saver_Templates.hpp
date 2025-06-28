#pragma once
#include "Saver.h"
#include <memory>
#define READ_ERROR 11

template <typename T, typename Func, std::size_t... Is>
void Saver::forEachImpl(T &&t, Func fn, std::index_sequence<Is...>) {
  (fn(std::get<Is>(t)), ...);
}

template <typename... Args, typename Func>
void Saver::forEachInTuple(const std::tuple<Args...> &t, Func fn) {
  forEachImpl(t, fn, std::index_sequence_for<Args...>{});
}

template <typename T>
void Saver::saveElement(std::ofstream &File, vector<T> &inputVector) {
  size_t size = inputVector.size();
  saveElement(File, size);
  for (auto &element : inputVector) {
    saveElement(File, element);
  }
}

template <typename T>
void Saver::saveElement(std::ofstream &File, std::stack<T> &inputStack) {
  size_t size = inputStack.size();
  saveElement(File, size);
  std::stack<T> tempStack = inputStack;
  while (!tempStack.empty()) {
    saveElement(File, tempStack.top());
    tempStack.pop();
  }
}

template <IsTrivial T> void Saver::saveElement(std::ofstream &File, T &input) {
  File.write(reinterpret_cast<const char *>(&input), sizeof(input));
}

template <typename T>
void Saver::readElement(std::ifstream &File, vector<T> &inputVector) {
  size_t size = 0;
  readElement(File, size);
  if (size > 1000000) {
    std::cerr << "Error in read size of vector. Received: " << size
              << std::endl;
    exit(READ_ERROR);
  }
  inputVector.resize(size);
  for (size_t i = 0; i < size; ++i) {
    readElement(File, inputVector[i]);
  }
}

template <typename T>
void Saver::readElement(std::ifstream &File, std::stack<T> &inputStack) {
  size_t size{0};
  readElement(File, size);
  if (size > 1000000) {
    std::cerr << "Error in read size of stack. Received: " << size << std::endl;
    exit(READ_ERROR);
  }
  for (size_t i = 0; i < size; i++) {
    T element;
    readElement(File, element);
    inputStack.push(element);
  }
  std::stack<T> reversedStack;
  while (!inputStack.empty()) {
    reversedStack.push(inputStack.top());
    inputStack.pop();
  }
  inputStack = reversedStack;
}
template <IsTrivial T> void Saver::readElement(std::ifstream &File, T &input) {
  File.read(reinterpret_cast<char *>(&input), sizeof(input));
}

template <typename Key, typename Value>
void Saver::saveElement(std::ofstream &File, std::map<Key, Value> &inputMap) {
  size_t size = inputMap.size();
  saveElement(File, size);
  for (auto &[key, value] : inputMap) {
    saveElement(File, key);
    saveElement(File, value);
  }
}
template <typename Key, typename Value>
void Saver::saveElement(std::ofstream &File,
                        std::unordered_map<Key, Value> &inputMap) {

  size_t size = inputMap.size();
  saveElement(File, size);
  for (auto &[key, value] : inputMap) {
    saveElement(File, key);
    saveElement(File, value);
  }
}

template <typename Key, typename Value>
void Saver::readElement(std::ifstream &File, std::map<Key, Value> &inputMap) {
  size_t size{0};
  readElement(File, size);
  if (size > 1000000) {
    std::cerr << "Error in read size of map. Received: " << size << std::endl;
    exit(READ_ERROR);
  }
  for (size_t i = 0; i < size; ++i) {
    Key _key;
    Value _value;
    readElement(File, _key);
    readElement(File, _value);
    inputMap[_key] = _value;
  }
}
template <typename Key, typename Value>
void Saver::readElement(std::ifstream &File,
                        std::unordered_map<Key, Value> &inputMap) {

  size_t size{0};
  readElement(File, size);
  if (size > 1000000) {
    std::cerr << "Error in read size of unordered_map. Received: " << size
              << std::endl;
    exit(READ_ERROR);
  }
  for (size_t i = 0; i < size; ++i) {
    Key _key;
    Value _value;
    readElement(File, _key);
    readElement(File, _value);
    inputMap[_key] = _value;
  }
}

template <typename T>
void Saver::saveClass(std::ofstream &File, T &inputClass) {
  if (std::is_class_v<T>) {
    if (!File) {
      std::cerr << "Error in saveClass() File, file not found";
      exit(ERROR_FILE);
    }
    auto allMembers = inputClass.getAllMembers();
    saveElement(File, allMembers);

  } else {
    notClass();
  }
}
template <typename T>
void Saver::readClass(std::ifstream &File, T &inputClass) {
  if (std::is_class_v<T>) {
    if (!File) {
      std::cerr << "Error in readClass() File, file not found";
      exit(ERROR_FILE);
    }
    auto allMembers = inputClass.getAllMembers();
    readElement(File, allMembers);
    inputClass.setAllMembers(allMembers);
  } else {
    notClass();
  }
}

template <IsStruct T>
void Saver::saveElement(std::ofstream &File, T &inputStruct) {
  forEachInTuple(inputStruct.toTuple(),
                 [&](auto &it) { saveElement(File, it); });
}

template <IsStruct T>
void Saver::readElement(std::ifstream &File, T &inputStruct) {
  T struct2;
  std::apply([&](auto &...args) { ((readElement(File, args)), ...); },
             struct2.toTuple());
  inputStruct = struct2;
}

template <typename... Args> void Saver::saveAllClasses(Args &&...args) {
  truncFile();
  auto File = saveFile();
  ((saveClass(File, std::forward<Args>(args)), ...));
}
template <typename... Args> void Saver::readAllClasses(Args &&...args) {
  auto File = readFile();
  ((readClass(File, std::forward<Args>(args)), ...));
}

template <IsClass T>
void Saver::saveElement(std::ofstream &File, shared_ptr<T> &inputClass) {
  bool exists = static_cast<bool>(inputClass);
  saveElement(File, exists);

  if (exists) {
    auto allMembers = inputClass->getAllMembers();
    saveElement(File, allMembers);
  }
}
template <IsClass T>
void Saver::readElement(std::ifstream &File, shared_ptr<T> &inputClass) {
  bool exists = false;
  readElement(File, exists);

  if (exists) {
    if (!inputClass) {
      inputClass = std::make_shared<T>();
      typename T::AllMembersType allMembers;
      readElement(File, allMembers);
      inputClass->setAllMembers(allMembers);
    }
  } else {
    inputClass.reset();
  }
}
