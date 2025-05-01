#include "../headers/Saver.h"
#include "../headers/Class1.h"

void Saver::saveElement(std::ofstream &File, string &inputString) {
  if (!File.good()) {
    std::cerr
        << "Erro: Stream de saída não está em bom estado para salvar string."
        << std::endl;
    File.setstate(std::ios::failbit);
    return;
  }

  size_t size = inputString.size();
  File.write(reinterpret_cast<const char *>(&size), sizeof(size));
  if (!File.good()) {
    std::cerr << "Erro ao escrever o tamanho da string (" << size
              << ") para o arquivo." << std::endl;
    return;
  }
  if (size > 0) {
    File.write(inputString.c_str(), size);
    if (!File.good()) {
      std::cerr << "Erro ao escrever o conteúdo da string para o arquivo."
                << std::endl;
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

/*
void Saver::_saveFile(Tst& inputClass){
    auto allMembers = inputClass.getAllMembers();
    auto File = saveFile();
    if(!File) { std::cout << "Error in _Save(Tst) File"; exit(ERROR_FILE);}
    saveVar(File,allMembers.data);
    // File.write(reinterpret_cast<char
*>(&allMembers.data),sizeof(allMembers.data));

    saveString(File,allMembers.hi);
}
*/

std::ofstream Saver::saveFile() {
  createFile();
  std::ofstream File(fileName, std::ios::binary | std::ios::in);
  if (!File) {
    std::cout << "error in save File";
    exit(ERROR_FILE);
  }
  return File;
}

std::ifstream Saver::readFile() {
  std::ifstream File(fileName, std::ios::binary | std::ios::out);
  if (!File) {
    std::cout << "error in read File";
    exit(ERROR_FILE);
  }
  return File;
}
/*
void Saver::_readFile(Tst &inputClass){
    auto File = readFile();
    _Tst::allMembers newStruct;
    readVar(File,newStruct.data);
    // File.read(reinterpret_cast<char *>(&newStruct.data),
sizeof(newStruct.data));

    readString(File,newStruct.hi);
    inputClass.setAllMembers(newStruct);
}
*/
