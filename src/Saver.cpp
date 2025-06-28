#include "../headers/Saver.h"

void Saver::saveElement(std::ofstream &File, const string &inputString) {
  if (!File.good()) {
    std::cerr << "Error: Output stream is not in good condition" << std::endl;
    File.setstate(std::ios::failbit);
    return;
  }

  size_t size = inputString.size();
  File.write(reinterpret_cast<const char *>(&size), sizeof(size));
  if (!File.good()) {
    std::cerr << "Error writing string size (" << size << ") to the file"
              << std::endl;
    return;
  }
  if (size > 0) {
    File.write(inputString.c_str(), size);
    if (!File.good()) {
      std::cerr << "Error writing string content to file" << std::endl;
      return;
    }
  }
}

void Saver::readElement(std::ifstream &File, string &inputString) {
  size_t size{0};
  readElement(File, size);
  inputString.resize(size);
  File.read(&inputString[0], size);
}

void Saver::truncFile() {
  std::ofstream Trunc(fileName,
                      std::ios::binary | std::ios::out | std::ofstream::trunc);
  Trunc.close();
}
void Saver::createFile() {
  std::ifstream File(fileName, std::ios::binary);
  if (File)
    return;
  File.close();
  std::ofstream newFile(fileName, std::ios::binary | std::ios::out);
  if (!newFile) {
    std::cout << "Error in Create File";
    exit(ERROR_FILE);
  }
  newFile.close();
}

std::ofstream Saver::saveFile() {
  createFile();
  std::ofstream File(fileName, std::ios::binary);
  if (!File) {
    std::cout << "error in saveFile";
    exit(ERROR_FILE);
  }
  return File;
}

std::ifstream Saver::readFile() {
  std::ifstream File(fileName, std::ios::binary | std::ios::in);
  if (!File) {
    std::cout << "error in readFile";
    exit(ERROR_FILE);
  }
  return File;
}

void Saver::notClass() {
  cout << "ERROR: Called saveClass but did not receive a class" << std::endl;
  exit(CLASS_NOT_RECEIVED);
}
