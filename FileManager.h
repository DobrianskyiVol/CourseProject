
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <list>
#include <memory>
#include <fstream>
#include<algorithm>
#include<mutex>



class FileManager {
    std::mutex mutex_;
public:
    FileManager() = default;
    ~FileManager() = default;
    template<typename T>
    void ReadFromFile(const std::string &folder, const std::string &date, std::list<std::unique_ptr<T> > &items) {
        std::string nameoffile = folder + date + ".txt";
        std::ifstream of(nameoffile);
        if (!of) {
            //std::cout << "No events/tasks for current day\n";
            return;
        }

        while (!of.eof()) {
            std::unique_ptr<T> item = std::make_unique<T>();
            of >> *item;
            if (item->GetPriority() == 0)
                break;
            items.emplace_back(std::move(item));
        }
        of.close();
    }
    template<typename T>
    void WriteToFile(const std::string &folder, const std::string &date, std::list<std::unique_ptr<T> > &items) {
        std::string nameoffile = folder + date + ".txt";
        mutex_.lock();
        std::ofstream ifs(nameoffile);
        if (!ifs) {
            //std::cout << "No events/tasks for current day\n";
            return;
        }

        std::for_each(items.begin(),items.end(),[&ifs](const std::unique_ptr<T> &item) {
            ifs << *item;
        });
        ifs.close();
        mutex_.unlock();
    }
    template<typename T>
    void AppendToFile(const std::string &folder, const std::string &date, T &item) {
        std::string nameoffile = folder + date + ".txt";
        mutex_.lock();
        std::ofstream ifs(nameoffile,std::ios::app);
        if (!ifs) {
            //std::cout << "No events/tasks for current day\n";
            return;
        }

        ifs << item;
        ifs.close();
        mutex_.unlock();
    }
};



#endif //FILEMANAGER_H
