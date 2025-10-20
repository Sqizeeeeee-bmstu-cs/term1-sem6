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


void task2(const std::string& s) {

    std::stringstream ss(s);
    std::queue<std::string> words;
    std::string word;

    // Парсим строку по пробелам и добавляем в очередь
    while (ss >> word) {
        words.push(word);
    }
    
    // Выводим результат (или обрабатываем очередь дальше)
    std::cout << "Parsed words in queue:" << std::endl;
    while (!words.empty()) {
        std::cout << "Processing... "<< words.front() << '\n';
        words.pop();
    }


}


void task3(const std::string& s) {
    std::stringstream ss(s);
    std::deque<std::string> cache;
    
    std::string key;
    while (ss >> key) {
        // Проверяем, есть ли уже такой ключ в кэше
        auto it = std::find(cache.begin(), cache.end(), key);
        
        if (it != cache.end()) {
            // Если ключ уже есть, удаляем его оттуда
            cache.erase(it);
        }
        
        // Проверяем длину дека
        if (cache.size() >= 3) {
            // Если дек полный, удаляем самый правый (старый) элемент
            cache.pop_back();
        }
        
        // Вставляем новый элемент в начало (слева)
        cache.push_front(key);
        
        // Выводим текущее состояние
        for (size_t i = 0; i < cache.size(); ++i) {
            std::cout << cache[i];
            if (i != cache.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}



void task5() {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::string line;
    std::string startCommit;
    
    std::cout << "Введите граф коммитов (формат: C1: [], C2: [C1], START C4 для начала обхода):\n";
    
    // Читаем построчно пока не встретим START
    while (std::getline(std::cin, line)) {
        // Проверяем, не команда ли START
        if (line.find("START") == 0) {
            // Извлекаем стартовый коммит
            std::stringstream ss(line);
            std::string cmd;
            ss >> cmd >> startCommit;
            break;
        }
        
        // Парсим строку с коммитом
        size_t colonPos = line.find(':');
        std::string commit = line.substr(0, colonPos);
        
        std::string parentsStr = line.substr(colonPos + 1);
        
        // Парсим родителей
        std::vector<std::string> parents;
        size_t startBracket = parentsStr.find('[');
        size_t endBracket = parentsStr.find(']');
        
        if (startBracket != std::string::npos && endBracket != std::string::npos) {
            std::string parentsList = parentsStr.substr(startBracket + 1, endBracket - startBracket - 1);
            std::stringstream ss(parentsList);
            std::string parent;
            
            while (std::getline(ss, parent, ',')) {
                // Убираем пробелы
                parent.erase(0, parent.find_first_not_of(" "));
                parent.erase(parent.find_last_not_of(" ") + 1);
                if (!parent.empty()) {
                    parents.push_back(parent);
                }
            }
        }
        
        graph[commit] = parents;
    }
    
    std::cout << "\nРезультат обхода графа от коммита " << startCommit << ":\n";
    
    // DFS обход
    std::stack<std::pair<std::string, int>> stack;
    std::unordered_set<std::string> visited;
    
    stack.push({startCommit, 0});
    
    while (!stack.empty()) {
        auto [current, depth] = stack.top();
        stack.pop();
        
        if (visited.count(current)) continue;
        visited.insert(current);
        
        // Выводим коммит с отступами
        std::cout << std::string(depth * 2, ' ') << "Commit: " << current << std::endl;
        
        // Добавляем родителей в стек
        const auto& parents = graph[current];
        for (auto it = parents.rbegin(); it != parents.rend(); ++it) {
            if (!visited.count(*it)) {
                stack.push({*it, depth + 1});
            }
        }
    }
}