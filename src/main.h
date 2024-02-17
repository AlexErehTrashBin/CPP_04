#pragma once

/**
 * 3) Описать структуру, содержащую информацию о сотруднике фирмы.
 * Поля структуры должны включать ФИО, пол, возраст, адрес проживания,
 * телефон, название отдела, должность, стаж, оклад и т.п. Создать файл данных,
 * содержащий сведения о нескольких сотрудниках. Написать программу,
 * позволяющую добавлять новых сотрудников (с сохранением данных в файл),
 * а также выбирать и выводить необходимую информацию об имеющихся
 * сотрудниках на экран. Например, вывести список сотрудников пенсионного
 * возраста. Формы запросов придумать самостоятельно.
 * */

#include "stdafx.h"
#include "input_utils.h"
#include "employee.h"


inline auto addEmployee(Employee** employees, size_t index) -> void;

auto saveData(Employee** employees, size_t size) -> void;

auto printEmployeesByAge(Employee** employees, size_t elements, int age) -> void;

auto printAllEmployees(Employee** employees, size_t size) -> void;

auto printEmployee(const Employee* employee) -> void;

auto getLinesInFile(wifstream* iss) -> size_t;

int main();

auto parseEmployeeFromLine(Employee* employee, wchar_t* line) -> void;

auto areStringsEqual(const wchar_t* first, const wchar_t* second) -> bool;

auto getStringSize(const wchar_t* str) -> int;
