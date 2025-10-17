#include "helpers.h"

bool task1(const std::string& s) {
    std::vector<std::string> m;
    
    // Используем unordered_map для быстрого поиска
    std::unordered_map<std::string, std::string> tag_pairs = {
        {"<div>", "</div>"},
        {"<p>", "</p>"}
    };
    
    std::unordered_map<std::string, bool> allowed_tags = {
        {"<div>", true},
        {"<p>", true},
        {"</div>", true},
        {"</p>", true}
    };

    if (s.empty()) {
        throw std::invalid_argument("string is empty!");
    }

    std::stringstream ss(s);
    std::string tag;
    
    while (ss >> tag) {
        // Быстрая проверка через unordered_map
        if (allowed_tags.find(tag) == allowed_tags.end()) {
            throw std::invalid_argument("One of tags is not allowed: " + tag);
        }
        m.push_back(tag);
    }

    std::stack<std::string> stack;

    for (size_t i = 0; i < m.size(); i++) {  // исправлен тип на size_t
        // Проверяем, является ли тег открывающим
        if (tag_pairs.find(m[i]) != tag_pairs.end()) {
            stack.push(m[i]);
        }
        else {
            // Это закрывающий тег
            if (stack.empty()) {
                throw std::runtime_error("Unmatched closing tag: " + m[i]);
            }
            
            std::string last_open_tag = stack.top();
            std::string expected_close_tag = tag_pairs[last_open_tag];
            
            if (m[i] != expected_close_tag) {
                throw std::runtime_error("Tag mismatch: expected " + expected_close_tag + 
                                       ", but found " + m[i]);
            }
            stack.pop();
        }
    }
    
    if (!stack.empty()) {
        throw std::runtime_error("Unclosed tags found");
    }
    else {
        return true;
    }
}


