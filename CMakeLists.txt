cmake_minimum_required(VERSION 3.5)
project(PubSub)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.c
        PubSub.c
        PubSub.h
        classes/core/ItemList/Item.c
        classes/core/ItemList/Item.h
        classes/core/ItemList/ItemList.c
        classes/core/ItemList/ItemList.h
        classes/core/Dictionary/Hash.c
        classes/core/Dictionary/Hash.h
        classes/core/Dictionary/Dictionary.c
        classes/core/Dictionary/Dictionary.h
)
add_executable(PubSub ${SOURCE_FILES})

