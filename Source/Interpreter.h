#pragma once

#include "GC/Heap.h"
#include "Runtime/ArrayObjectShape.h"
#include "Runtime/ExceptionObject.h"
#include "Runtime/GlobalObject.h"
#include "Runtime/GlobalObjectShape.h"
#include "Runtime/Object.h"
#include "Runtime/Result.h"
#include <vector>

namespace Ore {
class Interpreter {

  public:
  Interpreter();

  struct ScopeFrame {
    AST::BlockStatement& block;
    std::map<std::string, Value> variables;
  };

  const GC::Heap& heap() const { return m_heap; }
  GC::Heap& heap() { return m_heap; }

  GlobalObject const* global_object() const { return m_global_object; }
  GlobalObject* global_object() { return m_global_object; }

  Result run(AST::BlockStatement&, std::map<std::string, Value> const& arguments = {});

  ScopeFrame& current_scope() { return m_scope_frames.back(); }

  Result throw_exception(std::string const& type, std::string const& message);

  void enter_scope(AST::BlockStatement&, std::map<std::string, Value> const& arguments);
  void leave_scope();

  Result get_variable(std::string const& name);
  void set_variable(std::string const& name, Value);

  void collect_roots(std::vector<GC::Cell*>& roots);

#define __ENUM_OBJECT_SHAPES(name, ObjectName) \
  ObjectName* name() const                     \
  {                                            \
    return m_object_shapes.name;               \
  }

  ENUMERATE_OBJECT_SHAPES
#undef __ENUM_OBJECT_SHAPES

  private:
  GC::Heap m_heap;

  GlobalObject* m_global_object;

  struct {
#define __ENUM_OBJECT_SHAPES(name, ObjectName) \
  ObjectName* name;

    ENUMERATE_OBJECT_SHAPES
#undef __ENUM_OBJECT_SHAPES
  } m_object_shapes;

  std::vector<ScopeFrame> m_scope_frames;
};

}
