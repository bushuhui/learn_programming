#ifndef AVAR_AVAR_H
#define AVAR_AVAR_H

#define YAML_CPP false

#include "eigen3/Eigen/Dense"

#if YAML_CPP
#include "yaml-cpp/yaml.h"
#endif

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <list>
#include <map>
#include <assert.h>
// #include <unordered_map>

#define CONFIG_EXCEPTION
#define CONFIG_CONVERT
#define CONFIG_PARSER
#define CONFIG_NODE
#define CONFIG_MAT
#define CONFIG_IO

#define RegisterPtr(name, ptr) \
    class RegisterPtr##name { \
      public: \
        RegisterPtr##name(){avar.insertVoidPtr(#name, ptr);} \
    } RegisterPtr##name##_instance;

namespace AVAR {

CONFIG_EXCEPTION                          class ParseException;
CONFIG_CONVERT  template<typename _T>     struct converter;
CONFIG_NODE                               struct strNode;
CONFIG_NODE                               class Node;
CONFIG_IO                                 class Avar;
CONFIG_MAT      template <typename type>  struct Matrix;
CONFIG_MAT      template <typename type>  struct MatrixE;
CONFIG_PARSER                             class Parser;
// FIXME : i dont't want the inline function
CONFIG_PARSER  void LoadFile(Node & root, const char * filename);
CONFIG_PARSER  void LoadFile(Node & root, const std::string & filename);
CONFIG_PARSER  void LoadFile(Node & root, const char * buffer, const size_t size);
CONFIG_PARSER  void Parse(Node & root, std::iostream & stream);

class ParseException : public std::exception
{
 public:
  ParseException(std::string exp): mExp(exp){}
  virtual const char* what() const throw() {
    return mExp.c_str();
  } 
 private:
  std::string mExp;
};

template<typename _T> 
struct converter CONFIG_CONVERT
{
  static _T encode(const std::string &data) {
    std::istringstream is(data);
    _T var;
    if(is >> var) {
      return var;
    } else {
      throw ParseException(": parse var error!");
    }
  } 
};

template<typename _T> 
struct converter<std::vector<_T>> CONFIG_CONVERT
{
  static std::vector<_T> encode(const std::string &data) {
    std::istringstream is(data);
    std::vector<_T> var;
    _T tempVar;
    auto lam = [&](){
      size_t pos = is.tellg();
      if (pos == std::string::npos) return false;
      if (is >> tempVar) {
        return true;
      } else {
        throw ParseException(": parse vector error!");
        return false;
      }};
    while (lam()) var.push_back(tempVar);
    return var;
  } 
};

struct strNode CONFIG_NODE
{
  typedef std::shared_ptr<strNode> snPtr;
  strNode(const std::string &var): data(var) {}
  strNode(const std::string &_key, const std::string &var): key(_key), data(var) {}
  strNode (){}
  ~strNode(){}
  bool insert(const std::string &key, snPtr n);
  bool erase(const std::string &key);

  strNode& operator[] (const std::string &key) {
    std::map<std::string, snPtr>::iterator mIter;
    for (mIter = index.begin(); mIter != index.end(); ++mIter) {
      if (mIter->first != key) continue;
        break;
    }
    return *(mIter->second);
  }

  friend std::ostream& operator<< (std::ostream& os, const strNode& ns)
  {
    os << ns.data << std::endl;
    std::map<std::string, strNode::snPtr>::const_iterator mIter;
    for(mIter = ns.index.begin(); mIter != ns.index.end(); ++mIter) {
      os << "   " << mIter->first << ": " << mIter->second->data << std::endl;
    }
    return os;
  }

  template <typename type> type as() const;

 private:
  
  bool parseBoolean(const std::string &input, bool &val) const{
    std::string str = input;
    try {
      int ibool = std::stoi(str);
      if (ibool == 0) {val = false; return true;}
      else            {val = true;  return true;}
    } catch (std::invalid_argument const& ex) {
      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      if (str.compare("false")  == 0 || str.compare("no")  == 0
          || str.compare("n")   == 0 || str.compare("off") == 0) {
          val = false;
          return true;
      }
      if (str.compare("true")   == 0 || str.compare("yes") == 0
          || str.compare("y")   == 0 || str.compare("on")  == 0) {
          val = true;
          return true;
      }
      val = false;
      throw ParseException(": parse bool failed, please check the bool!");
    }
  }

  std::string key;
  std::string data;
  std::map<std::string, snPtr> index;
};

inline bool strNode::insert(const std::string &key, snPtr nP) 
{
  if (index.find(key) == index.end()) {
    index[key] = nP;
    return true;
  } else {
    std::cerr << "Repeat data!" << std::endl;
    return false;
  }
}

inline bool strNode::erase(const std::string &key)
{
  std::map<std::string, snPtr>::iterator iter = index.find(key);
  if (iter == index.end()) return false;
  index.erase(iter);
  return true;
}

template <typename type> type strNode::as() const
{
  try {
    return converter<type>::encode(data);
  } catch(const ParseException & e) {
    std::cerr << key << e.what() << std::endl;
    std::terminate();
  }
}

template <> inline bool strNode::as<bool>() const
{
  std::istringstream is(data);
  std::string input;
  is >> input;
  bool var;
  try {
    parseBoolean(input, var);
    return var;
  } catch (const ParseException & e){
      std::cerr << key << e.what() << std::endl;
      std::terminate();
  }
}


class Node CONFIG_NODE
{
 public:

  typedef std::map<std::string, std::string> mat;
  Node(){}
  ~Node(){}

  void clear() 
  {
    mmVar.clear();
  }

  strNode& operator[] (const std::string &key)
  {
    std::map<std::string, strNode>::iterator mIter;
    for (mIter = mmVar.begin(); mIter != mmVar.end(); ++mIter) {
      if (mIter->first != key) continue;
      break;
    }
    return mIter->second;
  }

  friend std::ostream& operator<< (std::ostream& os, const Node& ns)
  {
    std::map<std::string, strNode>::const_iterator mIter;
    for(mIter = ns.mmVar.begin(); mIter != ns.mmVar.end(); ++mIter) {
      os << mIter->first << ": " << mIter->second;
    }
    return os;
  }
  
  bool push(const std::string key, const std::string var)
  {
    if (mmVar.find(key) == mmVar.end()) {
      strNode n(key, var);
      mmVar[key] = n;
      return true;
    } else {
      std::cerr << "Repeat data!" << std::endl;
      return false;
    }
  }

  bool push(const std::string key, const strNode & n)
  {
    if (mmVar.find(key) == mmVar.end()) {
      mmVar[key] = n;
      return true;
    } else {
      std::cerr << "Repeat data!" << std::endl;
      return false;
    }
  }
  
 private:
  std::map<std::string, strNode>  mmVar;
};

class Parser CONFIG_PARSER
{
 public:
  Parser() = default;
  
  void Parse(Node &root, std::iostream &stream)
  {
    // root.clear();
    try {
      readLines(stream);
      procLines(root);
    } catch (const ParseException &e) {
      std::cerr << "Parse yaml error! " << std::endl << e.what() << std::endl;
    }
  }
  
 private:

  void readLines(std::iostream &stream)
  {
    std::string     line      = "";
    size_t          lineNum   = 0;
    std::streampos  streamPos = 0;
    
    while(!stream.eof() && !stream.fail()) {
      streamPos = stream.tellg();
      std::getline(stream, line);
      lineNum ++;
  
      const size_t notePos =  findNotCited(line, '#');
      if (notePos != std::string::npos) {
        line.resize(notePos);
      }
      
      if(line.size()) {
        if(line[line.size() - 1] == '\r' || line[line.size() - 1] == '\n') {
          line.resize(line.size() - 1);
        }
      } else continue;
  
      // make sure the char is valid
      for (size_t i = 0;i < line.size();++i) {
        if (line[i] == '\t' || (line[i] >= 32 && line[i] <= 126)) {
          continue;
        } else {
          throw ParseException("line " + std::to_string(lineNum) + ": char is non-valid");
        }
      }
  
      const size_t firstTabPos    = line.find_first_of('\t');
      size_t       startOffset    = line.find_first_not_of(" \t");
      if (startOffset != std::string::npos) {
        assert(startOffset >= firstTabPos || firstTabPos == std::string::npos);
        line = line.substr(startOffset);
      } else {
        startOffset = 0;
        line = "";
        continue;
      }
      if (line[0] == '%') continue;
  
      for (std::string::iterator sIter=line.begin();sIter != line.end();) {
        if (*sIter == '\"' || *sIter == '\'' || *sIter == ' ') sIter = line.erase(sIter);
        else if (*sIter == ',') {
          *sIter = ' ';
          sIter++; 
          continue;
        }
        else sIter++; 
      }
      mlines.push_back(line);
      // std::cout << line << std::endl;
    }
  }
    
  // FIXME: Quote in yaml
  size_t findNotCited(const std::string & input, char token)
  {
    size_t tokenPos = input.find_first_of(token);
    if (tokenPos == std::string::npos) return std::string::npos;
    return tokenPos;
  }

  void procLines(Node &root)
  {
    std::list<std::string>::iterator lIter;
    for (lIter = mlines.begin(); lIter != mlines.end(); lIter++){
      size_t tokenPos = findNotCited(*lIter, ':');
      assert(tokenPos != std::string::npos);
      // FIXME the cam.yaml
      if (lIter->substr(tokenPos+1, 2) == "!!") {
        parseType(root, tokenPos, lIter);
        continue;
      } else root.push(lIter->substr(0,tokenPos), lIter->substr(tokenPos+1));
    }
  }

  bool parseType(Node &root, size_t token, std::list<std::string>::iterator &lIter)
  {
    std::string key = lIter->substr(0,token);
    std::string var = lIter->substr(token+3);
    strNode n(key, var);
  
    std::string str = lIter->substr(token+3);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    //FIXME: Extend
    std::size_t nMat = str.find("mat");
    if (nMat == std::string::npos) return false;
    
    bool matParse = true;
    while(matParse && lIter != mlines.end()) {
      size_t tokenPos = findNotCited(*lIter, ':');
      assert(tokenPos != std::string::npos);
      std::string k_t = lIter->substr(0,tokenPos);
      
      size_t tokenPosMatL = findNotCited(*lIter, '[');
      if(tokenPosMatL == std::string::npos) {
        strNode::snPtr subN(new strNode(key, lIter->substr(tokenPos+1)));
        n.insert(k_t, subN);
        lIter ++;
        continue;
      } else {
        std::string vec = "";
        size_t tokenPosMatR = findNotCited(*lIter, ']');
        if (tokenPosMatR == std::string::npos) {
        vec = lIter->substr(tokenPosMatL+1);
        } else {
          vec = lIter->substr(tokenPosMatL+1, tokenPosMatR - tokenPosMatL - 1);
          strNode::snPtr subN(new strNode(key, vec));
          n.insert(k_t, subN);
          matParse = false;
          break;
        }
        lIter ++;
        while(lIter != mlines.end()) {
          tokenPosMatR = findNotCited(*lIter, ']');
          if (tokenPosMatR == std::string::npos) {
            vec += *lIter;
            lIter++;
          } else {
            vec += lIter->substr(0, tokenPosMatR);
            strNode::snPtr subN(new strNode(key, vec));
            n.insert(k_t, subN);
            matParse = false;
            break;
          }
        }
      }
    }
    root.push(key, n);
    return true;
  }

  std::list<std::string> mlines;
};

inline void LoadFile(Node & root, const std::string & filename)
{
  const char * filePtr = filename.c_str();
  LoadFile(root, filePtr);
}

inline void LoadFile(Node & root, const char * filename)
{
  std::ifstream file(filename, std::ifstream::binary);
  if (!file.is_open()) {
    std::cerr << "Wrong File Name!" << std::endl;
  }

  file.seekg(0,file.end);
  size_t fileSize = static_cast<size_t>(file.tellg());
  file.seekg(0,file.beg);

  std::unique_ptr<char[]> data(new char[fileSize]);
  file.read(data.get(), fileSize);
  file.close();

  LoadFile(root, data.get(),fileSize);
}

inline void LoadFile(Node & root, const char * buffer, const size_t size)
{
  std::stringstream ss(std::string(buffer, size));
  Parse(root, ss);
}

inline void Parse(Node & root, std::iostream & stream)
{
  Parser *pImp = nullptr;
  pImp = new Parser();
  pImp->Parse(root, stream);
  delete pImp;
}


template <typename type>
struct Matrix CONFIG_MAT
{
  Matrix(){}
  Matrix(int _rows, int _cols) : rows(_rows), cols(_cols) {}
  ~Matrix(){}
  Matrix<type> operator= (Matrix<type> &mat);

  int rows = 0;
  int cols = 0;
  char dt;
  std::vector<type> data;
};

template <typename type>
Matrix<type> Matrix<type>::operator= (Matrix<type> &mat)
{
  this->rows = mat.rows;
  this->cols = mat.cols;
  this->data = mat.data;
  this->dt   = mat.dt;
  return *this;
}

template <typename type>
struct MatrixE: public Matrix<type> CONFIG_MAT
{
  typedef Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> MatType;

  MatType toEigen();

  template <typename eigType>
  MatType toEigen(eigType &mat);
};

template <typename type>
typename MatrixE<type>::MatType MatrixE<type>::toEigen()
{
  Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic> eigMat;
  if ((!this->rows) || (!this->cols)) {
    std::cerr << "AVAR: Matrix rows or cols Wrong!" << std::endl;
    return eigMat;
  }
  eigMat = Eigen::Map<Eigen::Matrix<type, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>
                      (this->data.data(), this->rows, this->cols);
  return eigMat;
}

template <typename type>
template <typename eigType>
typename MatrixE<type>::MatType MatrixE<type>::toEigen(eigType &mat)
{
  int e_rows = mat.rows();
  int e_cols = mat.cols(); 
  if ((!e_rows && !e_cols) || (e_rows == this->rows && e_cols == this->cols)) {
    mat = toEigen();
  } else {
    std::cerr << "AVAR: The matrix shape in AVAR should be dynamic or the same as the target matrix! " << std::endl;
    try {
      mat = toEigen();
    } catch(std::invalid_argument const& ex) {
      std::cerr << " AVAR: Get Matrix failed!" << std::endl;
    }
  }

  return mat;
}

// Avar IO
#define avar AVAR::Avar::Instance()
class Avar CONFIG_IO
{

 public:
  
  explicit Avar(): mifileNum(0) {}
  virtual ~Avar(){}
  
  static inline Avar& Instance() 
  {
    static std::shared_ptr<Avar> spGlobalAvar(new Avar);
    return *spGlobalAvar;
  }

  bool ParseFile(const std::string& filePath="config.yaml", const bool print=false) {
    FILE *fh = fopen(filePath.c_str(),"r");
    if (fh == nullptr) {
      std::cerr << "AVAR: Config file doesn't  exist, please checkout the path." << std::endl;
      return false;
    }
    fclose(fh);
  
  #if YAML_CPP
    mConfig = YAML::LoadFile(filePath); //FIXME: how to remove the yaml-cpp
  #else
    AVAR::LoadFile(mConfig, filePath);
  #endif
    if (print) {
      std::cout << *this;
    } else {
        std::cout << "***********************************************************************************" << std::endl;
        std::cout << "Load Config: " + filePath + " Done." << std::endl;
        std::cout << "***********************************************************************************" << std::endl;
    }
      return true;
  }

  bool insertVoidPtr(const std::string &name, void* ptr){
    if (mmPtr.find(name) == mmPtr.end()) {
      mmPtr[name] = ptr;
      return true;
    } else {
      std::cerr << "Repeated Ptr" << std::endl;
      return false;
    }
  }

  void* getPtr(const std::string &name) {
    std::map<std::string, void *>::iterator iter = mmPtr.find(name);
    if (iter == mmPtr.end()) {
      std::cerr << "No such Ptr in avar!" << std::endl;
      return nullptr;
    } else {
      return iter->second;
    }
  }

  template<typename callType> Avar& call(const std::string &name, callType &var);
  template<typename callType> callType call(const std::string &name);

  template<typename callType> MatrixE<callType> callMatrix(const std::string &name); //matrix
  friend std::ostream& operator<< (std::ostream& os, const Avar& ns);

 private:

  bool callBoolean(const std::string &name);
  uint mifileNum;
  std::map<std::string, void *> mmPtr;
 
#if YAML_CPP
  YAML::Node  mConfig;
#else
  Node        mConfig;
#endif

};


inline std::ostream& operator<< (std::ostream& os, const Avar& ava) {
    std::cout << "===================================== Config =====================================" << std::endl;
    std::cout << std::endl << ava.mConfig << std::endl;
    std::cout << "===================================== Config =====================================" << std::endl;
    return os;
}

template<typename callType> 
callType Avar::call(const std::string &name)
{
  std::string sType(typeid(callType).name());
  size_t posV = sType.find("vector");
  if (posV == std::string::npos) {
    callType var;
    var = mConfig[name].as<callType>();
    return var;
  } else {
    return mConfig[name]["data"].as<callType>();
  }
}

template<typename callType>
Avar &Avar::call(const std::string &name, callType &var) {
  var = call<callType>(name);
  return *this;
}

template<typename callType> 
MatrixE<callType> Avar::callMatrix(const std::string &name)
{
  MatrixE<callType> mat;

  mat.dt   = mConfig[name]["dt"].as<char>();
  mat.rows = mConfig[name]["rows"].as<int>(); 
  mat.cols = mConfig[name]["cols"].as<int>();
  mat.data = mConfig[name]["data"].as<std::vector<callType>>();

  switch (mat.dt)
  {
    case 'd':
      if (!(std::is_same<double, callType>::value)){
        std::cerr << "AVAR: Matrix type is not same as yaml!" << std::endl;
      }
      break;

    case 'f':
      if (!(std::is_same<float, callType>::value)){
        std::cerr << "AVAR: Matrix type is not same as yaml!" << std::endl;
      }
      break;

    case 'i':
      if (!(std::is_same<int, callType>::value)){
        std::cerr << "AVAR: Matrix type is not same as yaml!" << std::endl;
      }
      break;

    default:
      std::cerr << "AVAR: Unknown matrix type!" << std::endl;
      break;
  }

  return mat;
}

//Plugin Manager
#ifndef SPtr
#define SPtr std::shared_ptr
#endif
#ifndef UPtr
#define UPtr std::unique_ptr
#endif

#define pluginManager AVAR::AvarPluginManager
#define Plugin(type) AVAR::AvarPluginManager<SPtr<type>>

#define REGISTER_PLUGIN(F, D, E) \
  extern "C" SPtr<F> create##F##D##E() {return SPtr<F>(new D());}\
  class F##D##E##_Register {\
   public:\
    F##D##E##_Register() {\
    pluginManager<SPtr<F>>::instance().insert(#E, create##F##D##E);}\
  } F##D##E##_instance;

template<typename Var_Type = void *>
class AvarPluginManager
{
 public:
  typedef Var_Type (*createPlugin)() ;
  typedef std::map<std::string, createPlugin>   DataMap;
  typedef typename DataMap::iterator            DataIter;

  AvarPluginManager(){};
  static AvarPluginManager& instance()
  {
    static UPtr<AvarPluginManager> ptrManager(new AvarPluginManager);
    return *ptrManager;
  }

  inline bool insert(const std::string &name, const createPlugin& var, bool overwrite = false)
  {
    std::cout << "plugin manager insert." << std::endl;
    DataIter iter = mmFactory.find(name);
    if (iter == mmFactory.end()) {
      mmFactory.insert(std::pair<std::string, createPlugin>(name, var));
      return true;
    } else {
      if (overwrite) iter->second = var;
      return false;
    }
  }

  static Var_Type create(const std::string &pluginName, std::string defaultP = "") 
  {
    DataMap datamap = AvarPluginManager<Var_Type>::instance().mmFactory;
    DataIter iter = datamap.find(pluginName);
    if (iter == datamap.end()) {
      return nullptr;
      if (defaultP.empty()) return nullptr;
      else {
        DataIter defaultIter = datamap.find(defaultP);
        if (defaultIter == datamap.end()) return nullptr;
        return defaultIter->second();
      }
    } else {
      return iter->second();
    }
  }

 public:
  DataMap mmFactory;
};

} // namespace AVAR

#endif //AVAR_AVAR_H
