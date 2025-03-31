#include <cassert>
#include <cstring>

#include <iostream>
#include <tuple>
#include <stdexcept>
#include <string>
#include <sstream>

#include <PR3PL.hpp>

void test_unit()
{
    Environment env;
    auto unit = std::make_shared<Unit>();
    auto eval_result = std::dynamic_pointer_cast<Unit>(unit->eval(env));
    assert(eval_result != nullptr);
}

void test_int()
{
    Environment env;
    auto number_ten = std::make_shared<Int>(10);
    auto eval_result = std::dynamic_pointer_cast<Int>(number_ten->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 10);
}

void test_id()
{
    Environment env;
    auto id = std::make_shared<Id>("x");
    auto eval_result = std::dynamic_pointer_cast<Id>(id->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == "x");
}

void test_is_unit()
{
    Environment env;
    auto is_unit_true = std::make_shared<IsUnit>(std::make_shared<Unit>());
    auto eval_result_true = std::dynamic_pointer_cast<Int>(is_unit_true->eval(env));
    assert(eval_result_true != nullptr);
    assert(eval_result_true->get_value() == 1);
    
    auto is_unit_false = std::make_shared<IsUnit>(std::make_shared<Int>(10));
    auto eval_result_false = std::dynamic_pointer_cast<Int>(is_unit_false->eval(env));
    assert(eval_result_false != nullptr);
    assert(eval_result_false->get_value() == 0);
}

void test_pair()
{
    Environment env;
    auto number_four = std::make_shared<Int>(4);
    auto number_five = std::make_shared<Int>(5);
    auto pair = std::make_shared<Pair>(number_four, number_five);
    auto eval_result = std::dynamic_pointer_cast<Pair>(pair->eval(env));
    assert(eval_result != nullptr);
    assert(std::dynamic_pointer_cast<Int>(eval_result->get_left_expression())->get_value() == 4);
    assert(std::dynamic_pointer_cast<Int>(eval_result->get_right_expression())->get_value() == 5);
}

void test_fst()
{
    Environment env;
    auto number_four = std::make_shared<Int>(4);
    auto number_five = std::make_shared<Int>(5);
    auto pair = std::make_shared<Pair>(number_four, number_five);
    auto fst = std::make_shared<Fst>(pair);
    auto eval_result = std::dynamic_pointer_cast<Int>(fst->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 4);
}

void test_fst_exception()
{
    auto fst = std::make_shared<Fst>(std::make_shared<Unit>());
    try
    {
        Environment env;
        fst->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "fst applied to non-pair") == 0);
    }
}

void test_snd()
{
    Environment env;
    auto number_four = std::make_shared<Int>(4);
    auto number_five = std::make_shared<Int>(5);
    auto pair = std::make_shared<Pair>(number_four, number_five);
    auto snd = std::make_shared<Snd>(pair);
    auto eval_result = std::dynamic_pointer_cast<Int>(snd->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 5);
}

void test_snd_exception()
{
    auto snd = std::make_shared<Snd>(std::make_shared<Unit>());
    try
    {
        Environment env;
        snd->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "snd applied to non-pair") == 0);
    }
}

void test_neg()
{
    Environment env;
    auto number_four = std::make_shared<Int>(4);
    auto neg = std::make_shared<Neg>(number_four);
    auto eval_result = std::dynamic_pointer_cast<Int>(neg->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == -4);
}

void test_neg_exception()
{
    auto neg = std::make_shared<Neg>(std::make_shared<Unit>());
    try
    {
        Environment env;
        neg->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "negation applied to non-int") == 0);
    }
}

void test_add()
{
    Environment env;
    auto add = std::make_shared<Add>(std::make_shared<Int>(5), std::make_shared<Int>(2));
    auto eval_result = std::dynamic_pointer_cast<Int>(add->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 7);
}

void test_add_exception()
{
    auto add = std::make_shared<Add>(std::make_shared<Int>(5), std::make_shared<Unit>());
    try
    {
        Environment env;
        add->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "addition applied to non-int") == 0);
    }
}

void test_mul()
{
    Environment env;
    auto mul = std::make_shared<Mul>(std::make_shared<Int>(5), std::make_shared<Int>(2));
    auto eval_result = std::dynamic_pointer_cast<Int>(mul->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 10);
}

void test_mul_exception()
{
    auto mul = std::make_shared<Mul>(std::make_shared<Int>(5), std::make_shared<Unit>());
    try
    {
        Environment env;
        mul->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "multiplication applied to non-int") == 0);
    }
}

void test_div()
{
    Environment env;
    auto div = std::make_shared<Div>(std::make_shared<Int>(5), std::make_shared<Int>(2));
    auto eval_result = std::dynamic_pointer_cast<Int>(div->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 2);
}

void test_div_exception()
{
    auto div = std::make_shared<Div>(std::make_shared<Int>(5), std::make_shared<Unit>());
    try
    {
        Environment env;
        div->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "division applied to non-int") == 0);
    }
}

void test_mod()
{
    Environment env;
    auto mod = std::make_shared<Mod>(std::make_shared<Int>(5), std::make_shared<Int>(2));
    auto eval_result = std::dynamic_pointer_cast<Int>(mod->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 1);
}

void test_mod_exception()
{
    auto mod = std::make_shared<Mod>(std::make_shared<Int>(5), std::make_shared<Unit>());
    try
    {
        Environment env;
        mod->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "module applied to non-int") == 0);
    }
}

void test_iflesser()
{
    Environment env;
    auto number_five = std::make_shared<Int>(5);
    auto number_two = std::make_shared<Int>(2);
    auto true_exp = std::make_shared<Pair>(std::make_shared<Unit>(), std::make_shared<Unit>());
    auto false_exp = std::make_shared<Unit>();
    auto iflesser_true = std::make_shared<IfLesser>(number_two, number_five, true_exp, false_exp);
    auto eval_result_true = std::dynamic_pointer_cast<Pair>(iflesser_true->eval(env));
    assert(eval_result_true != nullptr);
    auto iflesser_false = std::make_shared<IfLesser>(number_five, number_two, true_exp, false_exp);
    auto eval_result_false = std::dynamic_pointer_cast<Unit>(iflesser_false->eval(env));
    assert(eval_result_false != nullptr);
}

void test_iflesser_exception()
{
    Environment env;
    auto number_five = std::make_shared<Int>(5);
    auto unit = std::make_shared<Unit>();
    auto true_exp = std::make_shared<Pair>(std::make_shared<Unit>(), std::make_shared<Unit>());
    auto false_exp = std::make_shared<Unit>();
    auto iflesser = std::make_shared<IfLesser>(number_five, unit, true_exp, false_exp);
    try
    {
        Environment env;
        iflesser->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "iflesser comparison applied to non-int") == 0);
    }
}

void test_val()
{
    Environment env;
    auto id = std::make_shared<Id>("x");
    auto ten = std::make_shared<Int>(10);
    auto val = std::make_shared<Val>(id, ten);
    auto eval_result = std::dynamic_pointer_cast<Unit>(val->eval(env));
    assert(eval_result != nullptr);
    assert(env.lookup("x") != nullptr);
}

void test_val_exception()
{
    Environment env;
    auto id = std::make_shared<Int>(10);
    auto ten = std::make_shared<Int>(10);
    auto val = std::make_shared<Val>(id, ten);
    try
    {
        Environment env;
        val->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "val applied to non-identifier") == 0);
        assert(env.lookup("x") == nullptr);
    }
}

void test_var()
{
    Environment env;
    env.add("x", std::make_shared<Int>(10));
    auto id = std::make_shared<Id>("x");
    auto var = std::make_shared<Var>(id);
    auto eval_result = std::dynamic_pointer_cast<Int>(var->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 10);
}

void test_var_exception()
{
    Environment env;
    env.add("x", std::make_shared<Int>(10));
    auto unit = std::make_shared<Unit>();
    auto id = std::make_shared<Id>("y");

    try
    {
        auto var = std::make_shared<Var>(unit);
        var->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "var applied to non-identifier") == 0);
    }

    try
    {
        auto var = std::make_shared<Var>(id);
        var->eval(env);
        assert(false);
    }
    catch (const NotFoundError& e)
    {
        assert(strcmp(e.what(), "variable y does not exist") == 0);
    }
}

void test_let()
{
    Environment env;
    auto id = std::make_shared<Id>("x");
    auto ten = std::make_shared<Int>(10);
    auto body = std::make_shared<Add>(std::make_shared<Int>(5), std::make_shared<Var>(std::make_shared<Id>("x")));
    auto let = std::make_shared<Let>(id, ten, body);
    auto eval_result = std::dynamic_pointer_cast<Int>(let->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 15);
    assert(env.lookup("x") == nullptr);
}

void test_let_exception()
{
    auto id = std::make_shared<Unit>();
    auto ten = std::make_shared<Int>(10);
    auto body = std::make_shared<Add>(std::make_shared<Int>(5), std::make_shared<Var>(std::make_shared<Id>("x")));

    try
    {
        Environment env;
        auto let = std::make_shared<Let>(id, ten, body);
        let->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "let applied to non-identifier") == 0);
    }
}

void test_fun()
{
    Environment env;
    auto f_id = std::make_shared<Id>("pow2");
    auto p_id = std::make_shared<Id>("x");
    auto body = std::make_shared<Mul>(std::make_shared<Var>(std::make_shared<Id>("x")), std::make_shared<Var>(std::make_shared<Id>("x")));
    auto fun = std::make_shared<Fun>(f_id, p_id, body);
    auto eval_result = std::dynamic_pointer_cast<Unit>(fun->eval(env));
    assert(eval_result != nullptr);
    assert(env.lookup("pow2") != nullptr);
}

void test_fun_exception()
{
    auto f_id = std::make_shared<Id>("pow2");
    auto p_id = std::make_shared<Unit>();
    auto body = std::make_shared<Mul>(std::make_shared<Var>(std::make_shared<Id>("x")), std::make_shared<Var>(std::make_shared<Id>("x")));

    try
    {
        Environment env;
        auto fun = std::make_shared<Fun>(f_id, p_id, body);
        fun->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "fun applied to non-identifier") == 0);
    }
}

void test_call()
{
    Environment env;
    auto f_id = std::make_shared<Id>("pow2");
    auto p_id = std::make_shared<Id>("x");
    auto body = std::make_shared<Mul>(std::make_shared<Var>(std::make_shared<Id>("x")), std::make_shared<Var>(std::make_shared<Id>("x")));
    auto fun = std::make_shared<Fun>(f_id, p_id, body);
    fun->eval(env);

    auto call = std::make_shared<Call>(f_id, std::make_shared<Int>(8));
    auto eval_result = std::dynamic_pointer_cast<Int>(call->eval(env));
    assert(eval_result != nullptr);
    assert(eval_result->get_value() == 64);
}

void test_call_exception()
{
    Environment env;
    env.add("x", std::make_shared<Unit>());

    try
    {
        auto call = std::make_shared<Call>(std::make_shared<Unit>(), std::make_shared<Int>(8));
        call->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "call applied to non-identifier") == 0);
    }

    try
    {
        auto call = std::make_shared<Call>(std::make_shared<Id>("f"), std::make_shared<Int>(8));
        call->eval(env);
        assert(false);
    }
    catch (const NotFoundError& e)
    {
        assert(strcmp(e.what(), "function f does not exist") == 0);
    }

    try
    {
        auto call = std::make_shared<Call>(std::make_shared<Id>("x"), std::make_shared<Int>(8));
        call->eval(env);
        assert(false);
    }
    catch (const TypeError& e)
    {
        assert(strcmp(e.what(), "call applied to non-closure") == 0);
    }
}

void test_parser()
{
    // DIY 
}

int main()
{
    test_unit();
    test_int();
    test_id();
    test_is_unit();
    test_pair();
    test_fst();
    test_fst_exception();
    test_snd();
    test_snd_exception();
    test_neg();
    test_neg_exception();
    test_add();
    test_add_exception();
    test_mul();
    test_mul_exception();
    test_div();
    test_div_exception();
    test_mod();
    test_mod_exception();
    test_iflesser();
    test_iflesser_exception();
    test_val();
    test_val_exception();
    test_var();
    test_var_exception();
    test_let();
    test_let_exception();
    test_fun();
    test_fun_exception();
    test_call();
    test_call_exception();
    
    std::cout << "Everything ok!\n";

    return 0;
}
