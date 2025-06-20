#pragma once
#include "Saver.h"

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
  File.write(reinterpret_cast<char *>(inputVector.data()), size * sizeof(T));
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

template <typename T> void Saver::saveElement(std::ofstream &File, T &input) {
  File.write(reinterpret_cast<char *>(&input), sizeof(input));
}

template <typename T>
void Saver::readElement(std::ifstream &File, vector<T> &inputVector) {
  size_t size = inputVector.size();
  readElement(File, size);
  File.read(reinterpret_cast<char *>(inputVector.data()), size * sizeof(T));
}

template <typename T>
void Saver::readElement(std::ifstream &File, std::stack<T> &inputStack) {
  size_t size{0};
  readElement(File, size);
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
template <typename T> void Saver::readElement(std::ifstream &File, T &input) {
  File.read(reinterpret_cast<char *>(&input), sizeof(input));
}

template <typename Key, typename Value>
void Saver::saveElement(std::ofstream &File, std::map<Key, Value> &inputMap) {
  size_t size{0};
  saveElement(File, size);
  for (size_t i = 0; i < size; ++i) {
    Key _key;
    Value _value;
    saveElement(File, _key);
    saveElement(File, _value);
    inputMap[_key] = _value;
  }
}
template <typename Key, typename Value>
void Saver::saveElement(std::ofstream &File,
                        std::unordered_map<Key, Value> &inputMap) {

  size_t size{0};
  saveElement(File, size);
  for (size_t i = 0; i < size; ++i) {
    Key _key;
    Value _value;
    saveElement(File, _key);
    saveElement(File, _value);
    inputMap[_key] = _value;
  }
}

template <typename Key, typename Value>
void Saver::readElement(std::ifstream &File, std::map<Key, Value> &inputMap) {
  size_t size{0};
  readElement(File, size);
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
  for (size_t i = 0; i < size; ++i) {
    Key _key;
    Value _value;
    readElement(File, _key);
    readElement(File, _value);
    inputMap[_key] = _value;
  }
}

template <typename T> void Saver::saveClass(T &inputClass) {
  if (std::is_class_v<T>) {
    auto File = saveFile();
    if (!File) {
      cout << "Error in saveClass() File, file not found";
      exit(ERROR_FILE);
    }
    auto allMembers = inputClass.getAllMembers();
    saveElement(File, allMembers);

  } else {
    notClass();
  }
}
template <typename T> void Saver::readClass(T &inputClass) {
  if (std::is_class_v<T>) {
    auto File = readFile();
    if (!File) {
      cout << "Error in readClass() File, file not found";
      exit(ERROR_FILE);
    }
    auto allMembers = inputClass.getAllMembers();
    readElement(File, allMembers);
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
  forEachInTuple(inputStruct.toTuple(),
                 [&](auto &it) { readElement(File, it); });
}

template <typename... Args> void Saver::saveAllClasses(Args &&...args) {
  truncFile();
  ((saveClass(std::forward<Args>(args)), ...));
}
template <typename... Args> void Saver::readAllClasses(Args &&...args) {
  ((readClass(std::forward<Args>(args)), ...));
}

template <IsStruct T>
void Saver::saveElement(std::ofstream &File, shared_ptr<T> &inputClass) {
  if (std::is_class_v<T>) {
    if (!File) {
      cout << "Error in saveClass() File, file not found";
      exit(ERROR_FILE);
    }
    auto allMembers = inputClass->getAllMembers();
    saveElement(File, allMembers);

  } else {
    notClass();
  }
}
template <IsStruct T>
void Saver::readElement(std::ifstream &File, shared_ptr<T> &inputClass) {
  if (std::is_class_v<T>) {
    if (!File) {
      cout << "Error in readClass() File, file not found";
      exit(ERROR_FILE);
    }
    auto allMembers = inputClass->getAllMembers();
    readElement(File, allMembers);
  } else {
    notClass();
  }
}
