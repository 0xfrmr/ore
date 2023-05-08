#include <Ore.h>

using namespace Ore;
using std::make_unique;

int main(void)
{

  Interpreter interpreter;
  AST::Program program;

  std::vector<std::unique_ptr<AST::Expression>> import_args;
  import_args.push_back(make_unique<AST::StringLiteral>("./Modules/libtime.so"));

  std::vector<std::unique_ptr<AST::Expression>> cos_args;
  cos_args.push_back(make_unique<AST::NumberLiteral>(5000));

  std::vector<std::unique_ptr<AST::Expression>> print_args;
  print_args.push_back(make_unique<AST::CallExpression>(
      make_unique<AST::MemberExpression>(
          make_unique<AST::Identifier>("time"),
          make_unique<AST::Identifier>("sleep")),
      std::move(cos_args)));

  program.append<AST::AssignmentExpression>(
      make_unique<AST::Identifier>("time"),
      AST::AssignmentExpression::Op::Assignment,
      make_unique<AST::CallExpression>(
          make_unique<AST::Identifier>("import"),
          std::move(import_args)));

  program.append<AST::CallExpression>(
      make_unique<AST::Identifier>("print"),
      std::move(print_args));

  program.dump();
  auto retval = interpreter.run(program);

  if (retval.is_exception()) {
    auto* exception = static_cast<ExceptionObject*>(retval.value().as_object());
    std::cout << "Uncaught Exception(" << exception->type() << "): " << exception->message() << std::endl;
  }
}
