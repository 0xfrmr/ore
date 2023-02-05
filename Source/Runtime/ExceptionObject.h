#pragma once
#include "Object.h"
#include "PrimitiveString.h"

namespace Ore {

#define ENUMERATE_EXCEPTION_TYPES                                             \
  __ENUM_EXCEPTION_TYPES(reference_exception, ReferenceException)             \
  __ENUM_EXCEPTION_TYPES(type_exception, TypeException)                       \
  __ENUM_EXCEPTION_TYPES(division_by_zero_exception, DivisionByZeroException) \
  __ENUM_EXCEPTION_TYPES(file_not_found_exception, FileNotFoundException)

class ExceptionObject : public Object {
  public:
  ExceptionObject(std::string const& type, std::string const& message);
  virtual ~ExceptionObject() { }

  virtual char const* class_name() const override { return "ExceptionObject"; }
  virtual bool is_exception() const override { return true; }

  std::string type() const { return m_type; }
  std::string message() const { return m_message; }

#define __ENUM_EXCEPTION_TYPES(exception_type, ExceptionType) \
  static char const* exception_type()                         \
  {                                                           \
    return #ExceptionType;                                    \
  }

  ENUMERATE_EXCEPTION_TYPES
#undef __ENUM_EXCEPTION_TYPES

  private:
  std::string m_type;
  std::string m_message;
};

}
