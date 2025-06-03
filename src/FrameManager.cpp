#include "FrameManager.h"
#include <filesystem>
#include <sstream>
#include <iostream>
namespace fs = std::filesystem;

std::vector<std::string> FrameManager::getFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;
    if (!fs::exists(directory) || !fs::is_directory(directory)) {
        std::cerr << "Директория " << directory << " не существует!" << std::endl;
        return files;
    }
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::cout << entry.path().filename().string();
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

FrameManager::FrameManager(Room* room, DBworker* dbworker) : currentRoom(room), status(room->getAnimatronics()), dbworker(dbworker){
    std::vector<std::string> files = getFilesInDirectory("img");
    if (files.empty()) {
        throw std::runtime_error("Нет файлов в папке img!");
    }

    for (const std::string& file : files) {
        sf::Texture tex;
        std::string path = "img/" + file;
        std::cout << "[DEBUG] Загрузка: " << path << std::endl;

        if (tex.loadFromFile(path)) {
            std::cout << "[OK] Успешно: " << path << std::endl;
            framebase[file] = tex;
        } else {
            std::cerr << "[ERROR] Не удалось загрузить: " << path << std::endl;
        }
    }
    currentFrame = getCurrentFrame();
}

sf::Texture* FrameManager::getCurrentFrame() {
    std::string file = dbworker->getCurrentFrame(currentRoom);
    auto it = framebase.find(file);
    return &(it->second);
}

void FrameManager::update() {
    auto current_status = currentRoom->getAnimatronics();
    if (current_status != status) {
        currentFrame = getCurrentFrame();
        status = current_status;
    }
}

void FrameManager::updateRoom(Room* room) {
    if (currentRoom != room){
        currentRoom = room;   
        currentFrame = getCurrentFrame();
        status = currentRoom->getAnimatronics();
    }
}
