cmake_minimum_required(VERSION 3.28)
project(Course_Project_Final_Final)

set(CMAKE_CXX_STANDARD 17)

add_executable(Course_Project_Final_Final main.cpp
        Time.cpp
        Time.h
        Date.cpp
        Date.h
        Task.cpp
        Task.h
        Event.cpp
        Event.h
        ControllerInterface.h
        EventController.cpp
        EventController.h
        Validation.h
        FileManager.h
)
