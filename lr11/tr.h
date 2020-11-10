#pragma once

#include <fstream>
#include <string>

#include "tree.h"

std::vector<std::string> load(Tree& tr);

void first(const Tree& tr, const std::vector<std::string>& v);

void second(const Tree& tr, const std::vector<std::string>& v);